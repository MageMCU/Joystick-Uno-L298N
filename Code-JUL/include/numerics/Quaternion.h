//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: Class Quaternion.h
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

// Quaternion<real>: w + xi + yj + zk, stored as q_tuples[4] = {w, x, y, z},
// for rotations about an axis. Verified on a desktop 20261008: the product,
// conjugate, and q p q* rotation of a vector agree with reference values.
// Merged from MageMCU/Numerics (Algebra/include, 20241202).

#ifndef Numerics_Quaternion_h
#define Numerics_Quaternion_h

#include "Arduino.h"
#include "Point2.h"
#include "Point3.h"
#include "RandomNumber.h"

namespace csjc
{
    template <typename real>
    // FIXED 20261008: Quaternion no longer inherits from Point2, Point3, and
    // RandomNumber (it used none of them), and the unused m_size member was
    // removed. Quaternion<float> is now 16 bytes on the Uno instead of 76.
    // TEACHING NOTES (v6.1.1)
    // A quaternion q = w + x i + y j + z k has a scalar part w and a vector
    // part (x, y, z). It extends the complex numbers with three imaginary
    // units that obey i^2 = j^2 = k^2 = ijk = -1, so ij = k but ji = -k:
    // the product depends on the order (it is not commutative).
    // A unit quaternion (norm 1) describes a rotation in 3D: for a turn by
    // the angle a about the unit axis n,
    //   q = (cos(a/2), n sin(a/2))
    // and a vector v is turned by v' = q v q*, where v is written as the
    // pure quaternion (0, v) (scalar part 0). Terms used below:
    //   norm |q|       sqrt(w^2 + x^2 + y^2 + z^2), the length of the four
    //                  components
    //   conjugate q*   (w, -x, -y, -z); for a unit quaternion it is also the
    //                  inverse, the turn back
    //   inverse q^-1   q* / |q|^2, so q q^-1 = 1
    //   product q p    the turn p followed by the turn q, in one quaternion
    // Compared with three angles about x, y, and z (Matrix3x3.h, Rotation()),
    // a quaternion has no order of axes to choose, uses four numbers instead
    // of nine, and two turns combine with one product.
    // Example: a = 90 degrees about z, n = (0, 0, 1):
    // q = (cos 45, 0, 0, sin 45) = (0.7071, 0, 0, 0.7071), and q (1, 0, 0) q*
    // = (0, 1, 0).
    class Quaternion
    {
    private:
        // PRIVATE MEMBERS
        real q_tuples[4]; // w, x, y, z
        // Drift correction for products of unit quaternions
        Quaternion<real> m_driftCorrect(Quaternion<real> quat);

    public:
        // CONSTRUCTORS
        Quaternion();
        Quaternion(real w, real x, real y, real z);
        // Quaternion(x, y, z) and Quaternion(vector) make the pure quaternion
        // (0, x, y, z) that carries a vector into the product q v q*.
        Quaternion(real x, real y, real z);
        Quaternion(Vector3<real> vector);
        // Quaternion(axis, angle): the unit quaternion of a turn by the angle
        // about the axis (the formula above).
        Quaternion(Vector3<real> axis, real angleRadian);

        // DESTRUCTOR
        ~Quaternion() {}

        // GETTERS & SETTERS
        real w();
        void w(real w);
        real x();
        void x(real x);
        real y();
        void y(real y);
        real z();
        void z(real z);
        real Element(int index);
        Quaternion<real> ToQuaternion();
        Vector3<real> ToVector();

        // PUBLIC Methods
        bool NormDeviation(real test);
        real NormSquared();
        real Norm();
        Quaternion<real> Scale(real scalar);
        Quaternion<real> UnitQuaternion();
        Quaternion<real> Conjugate();
        Quaternion<real> Inverse();

        // Rotate a vector: the vector part of q v q* (q a unit quaternion)
        Vector3<real> Rotate(Vector3<real> v);

        // Experimental ///////////////
        real GetRadianAngle();
        real GetEulerAngle();
        Vector3<real> GetAxis();
        //////////////////////////////

        Quaternion<real> Multiply(Quaternion<real> c);

        // OPERATORS
        Quaternion<real> operator*(Quaternion<real> c);
    };

    template <typename real>
    Quaternion<real>::Quaternion()
    {
        q_tuples[0] = (real)0; // w
        q_tuples[1] = (real)0; // x
        q_tuples[2] = (real)0; // y
        q_tuples[3] = (real)0; // z
    }

    template <typename real>
    Quaternion<real>::Quaternion(real w, real x, real y, real z)
    {
        q_tuples[0] = w;
        q_tuples[1] = x;
        q_tuples[2] = y;
        q_tuples[3] = z;
    }

    template <typename real>
    Quaternion<real>::Quaternion(real x, real y, real z)
    {
        // Pure Quaternion
        q_tuples[0] = (real)0;
        q_tuples[1] = x;
        q_tuples[2] = y;
        q_tuples[3] = z;
    }

    template <typename real>
    Quaternion<real>::Quaternion(Vector3<real> vector)
    {
        // Pure Quaternion
        q_tuples[0] = (real)0;
        q_tuples[1] = vector.x();
        q_tuples[2] = vector.y();
        q_tuples[3] = vector.z();
    }

    template <typename real>
    Quaternion<real>::Quaternion(Vector3<real> axis, real angleRadian)
    {
        Vector3<real> normalized = axis.Normalize();
        real s = (real)sin((double)angleRadian / (double)2);
        real w = (real)cos((double)angleRadian / (double)2);
        q_tuples[0] = w;
        q_tuples[1] = normalized.x() * s;
        q_tuples[2] = normalized.y() * s;
        q_tuples[3] = normalized.z() * s;
    }

    // GETTERS & SETTERS

    template <typename real>
    real Quaternion<real>::w() { return q_tuples[0]; }
    template <typename real>
    void Quaternion<real>::w(real w) { q_tuples[0] = w; }

    template <typename real>
    real Quaternion<real>::x() { return q_tuples[1]; };
    template <typename real>
    void Quaternion<real>::x(real x) { q_tuples[1] = x; }

    template <typename real>
    real Quaternion<real>::y() { return q_tuples[2]; }
    template <typename real>
    void Quaternion<real>::y(real y) { q_tuples[2] = y; }

    template <typename real>
    real Quaternion<real>::z() { return q_tuples[3]; }
    template <typename real>
    void Quaternion<real>::z(real z) { q_tuples[3] = z; }

    // FIXED 20261008: an index outside 0 to 3 returns NaN (no bounds check
    // before).
    template <typename real>
    real Quaternion<real>::Element(int index)
    {
        if (index >= 0 && index < 4)
            return q_tuples[index];
        return NAN;
    }

    template <typename real>
    Quaternion<real> Quaternion<real>::ToQuaternion()
    {
        Quaternion<real> quat(q_tuples[0], q_tuples[1], q_tuples[2], q_tuples[3]);
        return quat;
    }

    template <typename real>
    Vector3<real> Quaternion<real>::ToVector()
    {
        Vector3<real> vector(q_tuples[1], q_tuples[2], q_tuples[3]);
        return vector;
    }

    // Returns true when a squared norm (or norm) deviates from 1 by more than
    // FLT_EPSILON, in either direction.
    // FIXED 20261008: restored the two sided test abs(test - 1). The one
    // sided form reported only values above 1.
    // NormDeviation(): true when a norm is not 1 within FLT_EPSILON, that
    // is, when a quaternion is no longer a unit quaternion.
    template <typename real>
    bool Quaternion<real>::NormDeviation(real testUnitLength)
    {
        real testEpsilon = abs(testUnitLength - (real)1.0);
        // Return true if norm deviates
        if (testEpsilon > (real)__FLT_EPSILON__)
            return true;
        // otherwise return false
        return false;
    }

    // |q|^2 = w^2 + x^2 + y^2 + z^2; it avoids the square root when only a
    // comparison with 1 is needed.
    template <typename real>
    real Quaternion<real>::NormSquared()
    {
        // Positive Value
        real SqMag = q_tuples[0] * q_tuples[0];
        SqMag += q_tuples[1] * q_tuples[1];
        SqMag += q_tuples[2] * q_tuples[2];
        SqMag += q_tuples[3] * q_tuples[3];
        return SqMag;
    }

    template <typename real>
    real Quaternion<real>::Norm()
    {
        // Positive Value
        return (real)sqrt((double)NormSquared());
    }

    template <typename real>
    Quaternion<real> Quaternion<real>::Scale(real scalar)
    {
        real wS = q_tuples[0] * scalar;
        real xS = q_tuples[1] * scalar;
        real yS = q_tuples[2] * scalar;
        real zS = q_tuples[3] * scalar;
        Quaternion<real> quat(wS, xS, yS, zS);
        // scaled quaternion may not be a unit-quaternion...
        return quat;
    }

    // q / |q|: the same direction in four dimensions, scaled to norm 1.
    template <typename real>
    Quaternion<real> Quaternion<real>::UnitQuaternion()
    {
        // FIXED 20261008: a zero quaternion stays zero (no division by zero).
        if (NormSquared() == (real)0)
            return ToQuaternion();
        // Assume norm is approx 1.0
        // This not change the sign-values
        // of the original quaternion...
        return Scale((real)1.0 / Norm());
    }

    // q* = (w, -x, -y, -z): the vector part reversed, the turn undone.
    template <typename real>
    Quaternion<real> Quaternion<real>::Conjugate()
    {
        real x = q_tuples[1] * (real)-1;
        real y = q_tuples[2] * (real)-1;
        real z = q_tuples[3] * (real)-1;
        Quaternion<real> quat(q_tuples[0], x, y, z);
        return quat;
    }

    // FIXED 20261008: a zero quaternion returns the zero quaternion instead
    // of dividing by zero. CREDIT: as in David Eberly, Geometric Tools
    // Engine, GTE/Mathematics/Quaternion.h (Boost Software License 1.0).
    template <typename real>
    Quaternion<real> Quaternion<real>::Inverse()
    {
        real n2 = NormSquared();
        if (n2 == (real)0)
        {
            Quaternion<real> zero;
            return zero;
        }
        return Conjugate().Scale((real)1.0 / n2);
    }

    // Rotation angle 2 acos(w), 0 to 2 pi radians, of a unit quaternion.
    // FIXED 20261008: w is clamped to -1 to 1 before acos(); rounding could
    // make it slightly greater than 1 and acos() then returned NaN.
    // From w = cos(a/2): a = 2 acos(w).
    template <typename real>
    real Quaternion<real>::GetRadianAngle()
    {
        // y = acos(x) if cos(y) = x, where (-1 <= x <= 1) & (0 <= y <= pi)
        real w = q_tuples[0];
        if (w > (real)1)
            w = (real)1;
        if (w < (real)-1)
            w = (real)-1;
        real radianAngle = (real)(2.0 * acos(w));
        return radianAngle;
    }

    // NOTE 20261012: returns the rotation angle of the unit quaternion in
    // degrees, 0 to 360 (GetRadianAngle() converted). It is not a set of
    // Euler angles; the name is kept so that existing programs compile.
    template <typename real>
    real Quaternion<real>::GetEulerAngle()
    {
        real angle = GetRadianAngle() * (real)RAD_TO_DEG;

        return angle;
    }

    // Unit rotation axis of a unit quaternion. When the angle is 0 (w = 1 or
    // -1) the axis is undefined and the zero vector is returned.
    // FIXED 20261008: uses the Vector3 setters; vector.x() = ... assigned to
    // the value returned by a getter and did not compile when called.
    // From (x, y, z) = n sin(a/2) and sin(a/2) = sqrt(1 - w^2): the axis
    // n = (x, y, z) / sqrt(1 - w^2).
    template <typename real>
    Vector3<real> Quaternion<real>::GetAxis()
    {
        Vector3<real> vector; // Zero Vector
        if (abs(q_tuples[0]) < (real)1)
        {
            real den = sqrt((real)1 - (q_tuples[0] * q_tuples[0]));
            vector.x(q_tuples[1] / den);
            vector.y(q_tuples[2] / den);
            vector.z(q_tuples[3] / den);
        }
        return vector.Normalize();
    }

    // Rotate v by this unit quaternion q: the vector part of q v q*, where v
    // is the pure quaternion (0, v). Added 20261008. For a unit quaternion
    // q* (the conjugate) is the inverse.
    // v' = q v q*: the product of three quaternions; its vector part is the
    // turned vector and its scalar part is 0.
    template <typename real>
    Vector3<real> Quaternion<real>::Rotate(Vector3<real> v)
    {
        Quaternion<real> p(v);
        Quaternion<real> q = ToQuaternion();
        Quaternion<real> r = (q * p) * q.Conjugate();
        return r.ToVector();
    }

    /*
    // Although different, the result is the same...
    // The product q c written out component by component, from the rules
    // for i, j, and k above.
    template <typename real>
    Quaternion<real> Quaternion<real>::Multiply(Quaternion<real> c)
    {
        // Quaternion Multiplication (qc) - Unit Quaternions
        Quaternion<real> q = ToQuaternion();
        real w = q.w() * c.w() - q.x() * c.x() - q.y() * c.y() - q.z() * c.z();
        real x = q.w() * c.x() + q.x() * c.w() + q.y() * c.z() - q.z() * c.y();
        real y = q.w() * c.y() - q.x() * c.z() + q.y() * c.w() + q.z() * c.x();
        real z = q.w() * c.z() + q.x() * c.y() - q.y() * c.x() + q.z() * c.w();
        // Quaternion
        Quaternion<real> quat(w, x, y, z);
        return m_driftCorrect(quat);
    }
    */

    // Although different, the result is the same...
    template <typename real>
    Quaternion<real> Quaternion<real>::Multiply(Quaternion<real> c)
    {
        // Quaternion Multiplication (qc) - Unit Quaternions
        Quaternion<real> q = ToQuaternion();
        real w = q.w() * c.w() - q.x() * c.x() - q.y() * c.y() - q.z() * c.z();
        real x = q.x() * c.w() + q.w() * c.x() - q.z() * c.y() + q.y() * c.z();
        real y = q.y() * c.w() + q.z() * c.x() + q.w() * c.y() - q.x() * c.z();
        real z = q.z() * c.w() - q.y() * c.x() + q.x() * c.y() + q.w() * c.z();
        // Quaternion
        Quaternion<real> quat(w, x, y, z);
        return m_driftCorrect(quat);
    }

    // OPERATORS

    // The same product written with vectors: for q = (w1, v1), c = (w2, v2),
    //   q c = (w1 w2 - v1.v2, w1 v2 + w2 v1 + v1 x v2)
    // with the dot product (.) and the cross product (x) of Vector3.h. The
    // cross product is why q c differs from c q.
    template <typename real>
    Quaternion<real> Quaternion<real>::operator*(Quaternion<real> c)
    {
        // Quaternion Multiplication - Unit Quaternions
        Quaternion<real> q = ToQuaternion();
        Vector3<real> qV = q.ToVector();
        Vector3<real> cV = c.ToVector();
        // Quaternion Product
        real wS = q.w() * c.w(); // Scalar Multiplication
        wS -= qV * cV;           // Vector Dot Product
        // Vector-Scalar Products & Vector-Cross Product (^)
        // includes vector additions...
        Vector3<real> v = (qV * c.w()) + (cV * q.w()) + (qV ^ cV);
        // Quaternion
        Quaternion<real> quat(wS, v.x(), v.y(), v.z());
        return m_driftCorrect(quat);
    }

    // PRIVATE

    // FIXED 20261008: Multiply() and operator* renormalize the product only
    // when its squared norm is within 0.01 of 1, that is, when both factors
    // were unit quaternions and the product has drifted by rounding (the
    // purpose of the original code in the "game loop" tests). The earlier
    // one sided test also rescaled products of non unit quaternions:
    // (2)(2) returned 1. Products far from unit length are now returned
    // unchanged: (2)(2) = 4 and (0.5)(0.5) = 0.25.
    // Rounding drift: every float operation rounds, so after many products a
    // unit quaternion slowly loses its norm of 1. Dividing by the norm again
    // (renormalizing) restores it.
    template <typename real>
    Quaternion<real> Quaternion<real>::m_driftCorrect(Quaternion<real> quat)
    {
        real n2 = quat.NormSquared();
        real d = abs(n2 - (real)1);
        if (d > (real)__FLT_EPSILON__ && d < (real)0.01)
            return quat.UnitQuaternion();
        return quat;
    }
}

#endif
