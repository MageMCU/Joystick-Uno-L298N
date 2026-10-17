//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: Rotation.h
// Folder: include/numerics
// Github: MageMCU
// Repository: Joystick-Uno-L298N
//
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//
// CREDIT: the conversion and interpolation methods are by David Eberly,
// Geometric Tools (https://www.geometrictools.com), from the Geometric
// Tools Engine files GTE/Mathematics/Rotation.h (quaternion to matrix and
// matrix to quaternion) and GTE/Mathematics/Slerp.h. His notice follows,
// as the Boost Software License requires:
//
//   David Eberly, Geometric Tools, Redmond WA 98052
//   Copyright (c) 1998-2026
//   Distributed under the Boost Software License, Version 1.0.
//   https://www.boost.org/LICENSE_1_0.txt
//   https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// ADAPTATION: adapted by Jesse Carpenter, Carpenter Software, 20261008.
// Changes from the original: rewritten without the C++ standard library
// (the Uno has none); the quaternion component order changed from GTE's
// (x, y, z, w) to this repository's (w, x, y, z); only the matrix vector
// convention GTE_USE_MAT_VEC (R * v) is kept; the conversions are free
// function templates on Quaternion<real> and Matrix3x3<real>; Slerp() uses
// sin() and acos() and a linear fallback for nearly equal quaternions in
// place of GTE's ChebyshevRatio; added QuaternionDot(). The adapted
// portions remain under the Boost Software License, Version 1.0; Carpenter
// Software's additions are released under the MIT License. This file is
// not endorsed by David Eberly or Geometric Tools, and any error in the
// adaptation is Carpenter Software's.
//

// Rotation.h: conversions between unit quaternions and 3 x 3 rotation
// matrices, and spherical linear interpolation (slerp) of unit quaternions.
//
// Conventions (the same as Matrix3x3.h and Quaternion.h in this folder):
//   * Quaternion<real> stores (w, x, y, z); GTE stores (x, y, z, w).
//   * Matrices are row major and act on column vectors: v' = R * v
//     (GTE_USE_MAT_VEC, the GTE default).
//   * q and -q represent the same rotation.
//
// These are free function templates rather than members, because
// Quaternion.h cannot include Matrix3x3.h (Matrix.h includes Quaternion.h).

#ifndef Numerics_Rotation_h
#define Numerics_Rotation_h

#include <Arduino.h>
#include "Matrix3x3.h"

namespace csjc
{
    // Unit quaternion q = (w, x, y, z) to rotation matrix:
    //     | 1-2y^2-2z^2  2(xy-zw)     2(xz+yw)    |
    // R = | 2(xy+zw)     1-2x^2-2z^2  2(yz-xw)    |
    //     | 2(xz-yw)     2(yz+xw)     1-2x^2-2y^2 |
    // R * v equals q.Rotate(v). q must have unit length.
    template <typename real>
    Matrix3x3<real> QuaternionToMatrix(Quaternion<real> q)
    {
        real w = q.w();
        real x = q.x();
        real y = q.y();
        real z = q.z();
        real twoX = (real)2 * x;
        real twoY = (real)2 * y;
        real twoZ = (real)2 * z;
        real twoXX = twoX * x;
        real twoXY = twoX * y;
        real twoXZ = twoX * z;
        real twoXW = twoX * w;
        real twoYY = twoY * y;
        real twoYZ = twoY * z;
        real twoYW = twoY * w;
        real twoZZ = twoZ * z;
        real twoZW = twoZ * w;
        real tuples[9];
        tuples[0] = (real)1 - twoYY - twoZZ;
        tuples[1] = twoXY - twoZW;
        tuples[2] = twoXZ + twoYW;
        tuples[3] = twoXY + twoZW;
        tuples[4] = (real)1 - twoXX - twoZZ;
        tuples[5] = twoYZ - twoXW;
        tuples[6] = twoXZ - twoYW;
        tuples[7] = twoYZ + twoXW;
        tuples[8] = (real)1 - twoXX - twoYY;
        Matrix3x3<real> R(tuples);
        return R;
    }

    // Rotation matrix to unit quaternion. GTE chooses the largest of
    // x^2, y^2, z^2, w^2 from the diagonal and computes that component first,
    // which avoids dividing by a small number. R must be a rotation matrix
    // (orthonormal, determinant 1). The result has unit length; its sign is
    // whichever the largest component case produces.
    template <typename real>
    Quaternion<real> MatrixToQuaternion(Matrix3x3<real> R)
    {
        // r(row, col) = R.GetElement(row * 3 + col)
        real r00 = R.GetElement(0), r01 = R.GetElement(1), r02 = R.GetElement(2);
        real r10 = R.GetElement(3), r11 = R.GetElement(4), r12 = R.GetElement(5);
        real r20 = R.GetElement(6), r21 = R.GetElement(7), r22 = R.GetElement(8);
        real qx, qy, qz, qw;
        if (r22 <= (real)0) // x^2 + y^2 >= z^2 + w^2
        {
            real dif10 = r11 - r00;
            real omr22 = (real)1 - r22;
            if (dif10 <= (real)0) // x^2 >= y^2
            {
                real fourXSqr = omr22 - dif10;
                real inv4x = (real)0.5 / (real)sqrt(fourXSqr);
                qx = fourXSqr * inv4x;
                qy = (r01 + r10) * inv4x;
                qz = (r02 + r20) * inv4x;
                qw = (r21 - r12) * inv4x;
            }
            else // y^2 >= x^2
            {
                real fourYSqr = omr22 + dif10;
                real inv4y = (real)0.5 / (real)sqrt(fourYSqr);
                qx = (r01 + r10) * inv4y;
                qy = fourYSqr * inv4y;
                qz = (r12 + r21) * inv4y;
                qw = (r02 - r20) * inv4y;
            }
        }
        else // z^2 + w^2 >= x^2 + y^2
        {
            real sum10 = r11 + r00;
            real opr22 = (real)1 + r22;
            if (sum10 <= (real)0) // z^2 >= w^2
            {
                real fourZSqr = opr22 - sum10;
                real inv4z = (real)0.5 / (real)sqrt(fourZSqr);
                qx = (r02 + r20) * inv4z;
                qy = (r12 + r21) * inv4z;
                qz = fourZSqr * inv4z;
                qw = (r10 - r01) * inv4z;
            }
            else // w^2 >= z^2
            {
                real fourWSqr = opr22 + sum10;
                real inv4w = (real)0.5 / (real)sqrt(fourWSqr);
                qx = (r21 - r12) * inv4w;
                qy = (r02 - r20) * inv4w;
                qz = (r10 - r01) * inv4w;
                qw = fourWSqr * inv4w;
            }
        }
        Quaternion<real> q(qw, qx, qy, qz);
        return q;
    }

    // Four dimensional dot product of two quaternions (the cosine of the
    // angle between them when both have unit length).
    template <typename real>
    real QuaternionDot(Quaternion<real> a, Quaternion<real> b)
    {
        return a.w() * b.w() + a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
    }

    // Spherical linear interpolation of unit quaternions, t in [0, 1]:
    //     slerp(t, q0, q1) = [sin((1 - t) A) q0 + sin(t A) q1] / sin(A)
    // where cos(A) = q0 . q1. Slerp(0) = q0, Slerp(1) = q1, and the rotation
    // turns at a constant rate as t increases.
    //   * When q0 . q1 < 0, q1 is negated so the interpolation takes the
    //     shorter path (q and -q are the same rotation), as recommended in
    //     GTE Slerp.h.
    //   * When the quaternions are nearly equal, sin(A) is near zero; linear
    //     interpolation followed by normalization is used instead.
    template <typename real>
    Quaternion<real> Slerp(real t, Quaternion<real> q0, Quaternion<real> q1)
    {
        real cosA = QuaternionDot(q0, q1);
        if (cosA < (real)0)
        {
            q1 = q1.Scale((real)-1);
            cosA = -cosA;
        }
        if (cosA > (real)1)
            cosA = (real)1;

        real c0, c1;
        if (cosA > (real)0.9995)
        {
            c0 = (real)1 - t;
            c1 = t;
        }
        else
        {
            real A = (real)acos(cosA);
            real invSinA = (real)1 / (real)sin(A);
            c0 = (real)sin(((real)1 - t) * A) * invSinA;
            c1 = (real)sin(t * A) * invSinA;
        }
        Quaternion<real> q(c0 * q0.w() + c1 * q1.w(),
                           c0 * q0.x() + c1 * q1.x(),
                           c0 * q0.y() + c1 * q1.y(),
                           c0 * q0.z() + c1 * q1.z());
        return q.UnitQuaternion();
    }
}

#endif /* Numerics_Rotation_h */
