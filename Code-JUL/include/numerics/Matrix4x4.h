//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: Class Matrix4x4.h
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

// Matrix4x4<real>: 4 x 4 matrix, row major (index = row * 4 + col), for
// homogeneous translation and rotation.
// Merged from MageMCU/Numerics (Algebra/include, 20241202).

#ifndef Numerics_Matrix4x4_h
#define Numerics_Matrix4x4_h

#include "Arduino.h"
#include "Matrix3x3.h"

namespace csjc
{
    template <typename real>
    // FIXED 20261008: Matrix4x4 inherits from the empty Matrix class, not
    // from Matrix3x3. Matrix4x4<float> is now 64 bytes on the Uno instead
    // of 192.
    class Matrix4x4 : Matrix<real>
    {
    private:
        // Properties
        // SIZE: 4x4 = 16
        real m_tuples[16];

        // Private Methods
        void m_identity();
        bool m_limits(int index);

    public:
        Matrix4x4();
        Matrix4x4(const real tuples[]);
        Matrix4x4(real minRandom, real maxRandom);
        Matrix4x4(Matrix2x2<real> m2);
        Matrix4x4(Matrix3x3<real> m3);
        ~Matrix4x4() = default;

        // GETTERS
        real GetElement(int index);
        // FIXED 20261008: row and col are int (they were real).
        real GetElement(int row, int col);
        int GetIndex(int row, int col);

        // Setter
        void SetElement(int index, real value);

        // Methods
        // FIXED 20261008: Translation() and Rotation() are member functions
        // (they were declared here but defined as free functions, so
        // M.Translation(v) failed to link). Like Matrix2x2::Rotation(), they
        // return a new matrix and do not use the object they are called on:
        //   Matrix4x4<float> T = T.Translation(v);
        // The free functions Translation<real>(v) and Rotation<real>(axis,
        // angle) remain for existing code and call these members.
        Matrix4x4<real> Translation(Vector3<real> v);
        Matrix4x4<real> Rotation(Vector3<real> axis, real angleRadian);

        // Operators
    };

    template <typename real>
    Matrix4x4<real>::Matrix4x4()
    {
        m_identity();
    }

    template <typename real>
    Matrix4x4<real>::Matrix4x4(const real tuples[])
    {
        for (int i = 0; i < 16; i++)
        {
            m_tuples[i] = tuples[i];
        }
    }

    template <typename real>
    Matrix4x4<real>::Matrix4x4(real minRandNum, real maxRandNum)
    {
        RandomNumber<real> rdm(minRandNum, maxRandNum);
        for (int i = 0; i < 16; i++)
        {
            m_tuples[i] = rdm.Random();
        }
    }
    // FIXED 20261008: the 2x2 and 3x3 constructors start from the identity
    // and copy the smaller matrix into the upper left corner of THIS matrix.
    // They filled a local matrix and discarded it, leaving this one
    // uninitialized.
    template <typename real>
    Matrix4x4<real>::Matrix4x4(Matrix2x2<real> m2)
    {
        m_identity();
        //  0  1  2  3
        //  4  5  6  7
        //  8  9 10 11
        // 12 13 14 15
        SetElement(0, m2.GetElement(0));
        SetElement(1, m2.GetElement(1));
        SetElement(4, m2.GetElement(2));
        SetElement(5, m2.GetElement(3));
    }

    template <typename real>
    Matrix4x4<real>::Matrix4x4(Matrix3x3<real> m3)
    {
        m_identity();
        //  0  1  2  3
        //  4  5  6  7
        //  8  9 10 11
        // 12 13 14 15
        SetElement(0, m3.GetElement(0));
        SetElement(1, m3.GetElement(1));
        SetElement(2, m3.GetElement(2));
        SetElement(4, m3.GetElement(3));
        SetElement(5, m3.GetElement(4));
        SetElement(6, m3.GetElement(5));
        SetElement(8, m3.GetElement(6));
        SetElement(9, m3.GetElement(7));
        SetElement(10, m3.GetElement(8));
    }

    template <typename real>
    real Matrix4x4<real>::GetElement(int index)
    {
        if (m_limits(index))
        {
            return m_tuples[index];
        }
        return NAN;
    }

    template <typename real>
    real Matrix4x4<real>::GetElement(int row, int col)
    {
        int index = GetIndex(row, col);
        if (m_limits(index))
        {
            return m_tuples[index];
        }
        return NAN;
    }

    template <typename real>
    int Matrix4x4<real>::GetIndex(int row, int col)
    {
        return (row * 4) + col;
    }

    template <typename real>
    void Matrix4x4<real>::SetElement(int index, real value)
    {
        if (m_limits(index))
        {
            m_tuples[index] = value;
        }
    }

    // Methods

    // Homogeneous translation by v (row major, column vectors):
    //  1 0 0 vx
    //  0 1 0 vy
    //  0 0 1 vz
    //  0 0 0 1
    template <typename real>
    Matrix4x4<real> Matrix4x4<real>::Translation(Vector3<real> v)
    {
        // Identity
        Matrix4x4<real> T;
        //  0  1  2  3
        //  4  5  6  7
        //  8  9 10 11
        // 12 13 14 15
        T.SetElement(3, v.x());
        T.SetElement(7, v.y());
        T.SetElement(11, v.z());
        return T;
    }

    // Free function kept for existing code.
    template <typename real>
    Matrix4x4<real> Translation(Vector3<real> v)
    {
        Matrix4x4<real> M;
        return M.Translation(v);
    }

    // Rotation by angleRadian about axis (any length), built from the unit
    // quaternion q(axis, angle). Verified on a desktop 20261008.
    template <typename real>
    Matrix4x4<real> Matrix4x4<real>::Rotation(Vector3<real> axis, real angleRadian)
    {
        real tuples[16];
        //  0  1  2  3
        //  4  5  6  7
        //  8  9 10 11
        // 12 13 14 15

        // quaternion components
        Quaternion<real> q(axis, angleRadian);
        real w = q.w();
        real x = q.x();
        real y = q.y();
        real z = q.z();

        // Row1
        real ww = w * w;
        real xx = x * x;
        real yy = y * y;
        real zz = z * z;
        tuples[0] = ww + xx - yy - zz;
        real xy = 2 * x * y;
        real wz = 2 * w * z;
        tuples[1] = xy - wz;
        real xz = 2 * x * z;
        real wy = 2 * w * y;
        tuples[2] = xz + wy;
        tuples[3] = (real)0;
        // Row2
        tuples[4] = xy + wz;
        tuples[5] = ww - xx + yy - zz;
        real yz = 2 * y * z;
        real wx = 2 * w * x;
        tuples[6] = yz - wx;
        tuples[7] = (real)0;
        // Row3
        tuples[8] = xz - wy;
        tuples[9] = yz + wx;
        tuples[10] = ww - xx - yy + zz;
        tuples[11] = (real)0;
        // Row4
        tuples[12] = (real)0;
        tuples[13] = (real)0;
        tuples[14] = (real)0;
        tuples[15] = (real)1;

        // Matrix
        Matrix4x4<real> m4(tuples);
        return m4;
    }

    // Free function kept for existing code.
    template <typename real>
    Matrix4x4<real> Rotation(Vector3<real> axis, real angleRadian)
    {
        Matrix4x4<real> M;
        return M.Rotation(axis, angleRadian);
    }

    // Private Methods

    template <typename real>
    void Matrix4x4<real>::m_identity()
    {
        int idx = 0;
        for (int r = 0; r < 4; r++)
        {
            for (int c = 0; c < 4; c++)
            {
                idx = GetIndex(r, c);
                if (r == c)
                    m_tuples[idx] = (real)1;
                else
                    m_tuples[idx] = (real)0;
            }
        }
    }

    template <typename real>
    bool Matrix4x4<real>::m_limits(int index)
    {
        if (index >= 0 && index < 16)
            return true;
        return false;
    }
}
#endif