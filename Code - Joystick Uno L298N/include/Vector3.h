//
// Carpenter Software
// File: Class Vector3.h
// Github: MageMCU
// Repository: Joystick-UNO-L298N
// Folder: Code
//
// By Jesse Carpenter (carpentersoftware.com)
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//

#ifndef Numerics_Vector3_h
#define Numerics_Vector3_h

#include "Arduino.h"

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    template <typename real>
    class Vector3
    {
    private:
        // MEMBERS
        int m_size;
        real m_x;
        real m_y;
        real m_z;

    public:
        // CONSTRUCTORS
        Vector3();
        Vector3(real x, real y, real z);
        Vector3(const real array[]);

        // DESTRUCTOR
        ~Vector3() {}

        // GETTERS & SETTERS
        void x(real x);
        real x();
        void y(real y);
        real y();
        void z(real z);
        real z();
        int Size();
        real Element(int index);
        Vector3<real> GetVector();

        // METHODS
        real Magnitude();
        Vector3<real> UnitVector();
        real Distance();
        Vector3<real> Normalize();
        real Dot(Vector3<real> v);
        Vector3<real> Cross(Vector3<real> v);
        Vector3<real> UnitCross(Vector3<real> v);
        real Angle(Vector3<real> v);
        Vector3<real> ProjV(Vector3<real> v);

        // OPERATORS
        Vector3<real> operator-();
        Vector3<real> operator*(real s);
        Vector3<real> operator+(Vector3<real> v);
        Vector3<real> operator-(Vector3<real> v);
        real operator*(Vector3<real> v);
        Vector3<real> operator^(Vector3<real> v);
    };

    template <typename real>
    Vector3<real>::Vector3()
    {
        m_size = 3;
        m_x = (real)0;
        m_y = (real)0;
        m_z = (real)0;
    }

    template <typename real>
    Vector3<real>::Vector3(real x, real y, real z)
    {
        m_size = 3;
        m_x = x;
        m_y = y;
        m_z = z;
    }

    template <typename real>
    Vector3<real>::Vector3(const real array[])
    {
        m_size = 3;
        m_x = array[0];
        m_y = array[1];
        m_z = array[2];
    }

    // GETTERS & SETTERS
    template <typename real>
    void Vector3<real>::x(real x) { m_x = x; }
    template <typename real>
    real Vector3<real>::x() { return m_x; }

    template <typename real>
    void Vector3<real>::y(real y) { m_y = y; }
    template <typename real>
    real Vector3<real>::y() { return m_y; }

    template <typename real>
    void Vector3<real>::z(real z) { m_z = z; }
    template <typename real>
    real Vector3<real>::z() { return m_z; }

    template <typename real>
    int Vector3<real>::Size() { return m_size; }

    template <typename real>
    real Vector3<real>::Element(int index)
    {
        real value = m_x;
        if (index == 1)
            value = m_y;
        if (index == 2)
            value = m_z;
        return value;
    }

    template <typename real>
    Vector3<real> Vector3<real>::GetVector()
    {
        Vector3<real> vector(m_x, m_y, m_z);
        return vector;
    }

    // METHODS
    template <typename real>
    real Vector3<real>::Magnitude()
    {
        real sum = 0;
        sum += m_x * m_x;
        sum += m_y * m_y;
        sum += m_z * m_z;
        return (real)sqrt(sum);
    }

    template <typename real>
    Vector3<real> Vector3<real>::UnitVector()
    {
        real x = (real)0;
        real y = (real)0;
        real z = (real)0;
        real magnitude = Magnitude();
        if (magnitude > (real)__FLT_EPSILON__)
        {
            x = m_x / magnitude;
            y = m_y / magnitude;
            z = m_z / magnitude;
        }
        Vector3<real> vector(x, y, z);
        return vector;
    }

    template <typename real>
    real Vector3<real>::Distance()
    {
        return Magnitude();
    }

    template <typename real>
    Vector3<real> Vector3<real>::Normalize()
    {
        return UnitVector();
    }

    template <typename real>
    real Vector3<real>::Dot(Vector3<real> v)
    {
        // DOT Product
        // yeilds a Scalar
        real sum = (real)0;
        sum += m_x * v.x();
        sum += m_y * v.y();
        sum += m_z * v.z();
        return sum;
    }

    template <typename real>
    Vector3<real> Vector3<real>::Cross(Vector3<real> v)
    {
        // CROSS Product
        // non-commutative property
        // Note: (Cross products must be 3D vectors)

        // a2b3 - a3b2
        real x = (m_y * v.z()) - (m_z * v.y());
        // a3b1 -a1b3
        real y = (m_z * v.x()) - (m_x * v.z());
        // a1b2 - a2b1
        real z = (m_x * v.y()) - (m_y * v.x());

        // Constructed
        Vector3<real> vector(x, y, z);
        return vector;
    }

    template <typename real>
    Vector3<real> Vector3<real>::UnitCross(Vector3<real> v)
    {
        Vector3<real> cross = Cross(v);
        return cross.Normalize();
    }

    template <typename real>
    real Vector3<real>::Angle(Vector3<real> v)
    {
        // Angle between 3D vecotrs
        Vector3<real> u = GetVector();
        // ref: [ELA] by Shields, 1980. p.213.
        // The returned value is in the range [0, pi]
        // radians. A domain error occurs for arguments
        // not in the range [-1, +1]. Therefore the vectors
        // must be normalized...
        return acos((real)(u.Normalize() * v.Normalize()));
    }

    template <typename real>
    Vector3<real> Vector3<real>::ProjV(Vector3<real> v)
    {
        // Project this.vector u onto v...
        // Constructed
        Vector3<real> u = GetVector();
        // real magnitude = v.Magnitude();

        // real dotUV = u * v;
        // real dotVV = v * v;
        // real quot = dotUV / dotVV;
        // where dotVV is equivalent to Square(v.Magnitude())...
        // ref: (1) [ELA] by Shields, 1980. p.237.
        //      (2) [Mf3DG&CG] 2nd Ed. by Lengyel, 2004. p19.
        real quot = (u * v) / (v * v);

        // Constructed
        Vector3<real> vector = v * quot;
        return vector;
    }

    // OPERATORS
    template <typename real>
    Vector3<real> Vector3<real>::operator-()
    {
        real x = m_x * (real)-1.0;
        real y = m_y * (real)-1.0;
        real z = m_z * (real)-1.0;

        // Constructed
        Vector3<real> vector(x, y, z);
        return vector;
    }

    template <typename real>
    Vector3<real> Vector3<real>::operator*(real s)
    {
        real x = m_x * s;
        real y = m_y * s;
        real z = m_z * s;

        // Constructed
        Vector3<real> vector(x, y, z);
        return vector;
    }

    template <typename real>
    Vector3<real> Vector3<real>::operator+(Vector3<real> v)
    {
        real x = m_x + v.x();
        real y = m_y + v.y();
        real z = m_z + v.z();

        // Constructed
        Vector3<real> vector(x, y, z);
        return vector;
    }

    template <typename real>
    Vector3<real> Vector3<real>::operator-(Vector3<real> v)
    {
        real x = m_x - v.x();
        real y = m_y - v.y();
        real z = m_z - v.z();

        // Constructed
        Vector3<real> vector(x, y, z);
        return vector;
    }

    template <typename real>
    real Vector3<real>::operator*(Vector3<real> v)
    {
        // DOT Product
        // yeilds a Scalar
        real sum = 0;

        sum += m_x * v.x();
        sum += m_y * v.y();
        sum += m_z * v.z();

        return sum;
    }

    template <typename real>
    Vector3<real> Vector3<real>::operator^(Vector3<real> v)
    {
        // a2b3 - a3b2
        real x = (m_y * v.z()) - (m_z * v.y());
        // a3b1 -a1b3
        real y = (m_z * v.x()) - (m_x * v.z());
        // a1b2 - a2b1
        real z = (m_x * v.y()) - (m_y * v.x());

        // Constructed
        Vector3<real> vector(x, y, z);
        return vector;
    }

}
#endif /* Numerics_Vector3_h */