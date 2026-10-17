//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: Class Vector2.h
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

// Vector2<real>: two component vector with magnitude, unit vector, dot product
// (operator*), perpendicular, perp dot product, angle, and projection.
// Merged from MageMCU/Numerics (Algebra/include, 20241202).

#ifndef Numerics_Vector2_h
#define Numerics_Vector2_h

#include "Arduino.h"

namespace csjc
{
    template <typename real>
    class Vector2
    {
    private:
        // MEMBERS
        // int m_size; NOT USED
        real m_x;
        real m_y;

    public:
        // CONSTRUCTORS
        Vector2();
        Vector2(real x, real y);
        Vector2(const real array[]);

        // DESTRUCTOR
        ~Vector2() {}

        // GETTERS & SETTERS
        void x(real x);
        real x();
        void y(real y);
        real y();
        // int Size();  NOT USED
        real Element(int index);

        // METHODS
        Vector2<real> GetVector();
        real Magnitude();
        Vector2<real> UnitVector();
        real Distance();
        Vector2<real> Normalize();
        real Dot(Vector2<real> v);
        real Angle(Vector2<real> v);
        Vector2<real> Perp();
        Vector2<real> UnitPerp();
        real DotPerp(Vector2<real> v);
        real ZComp(Vector2<real> v);
        Vector2<real> ProjV(Vector2<real> v);

        // OPERATORS
        Vector2<real> operator-();
        Vector2<real> operator*(real s);
        Vector2<real> operator+(Vector2<real> v);
        Vector2<real> operator-(Vector2<real> v);
        real operator*(Vector2<real> v);
    };

    template <typename real>
    Vector2<real>::Vector2()
    {
        // m_size = 2;  NOT USED
        m_x = (real)0;
        m_y = (real)0;
    }

    template <typename real>
    Vector2<real>::Vector2(real x, real y)
    {
        // m_size = 2;  NOT USED
        m_x = x;
        m_y = y;
    }

    template <typename real>
    Vector2<real>::Vector2(const real array[])
    {
        // m_size = 2;  NOT USED
        m_x = array[0];
        m_y = array[1];
    }

    // GETTERS & SETTERS
    template <typename real>
    void Vector2<real>::x(real x) { m_x = x; }
    template <typename real>
    real Vector2<real>::x() { return m_x; }

    template <typename real>
    void Vector2<real>::y(real y) { m_y = y; }
    template <typename real>
    real Vector2<real>::y() { return m_y; }

    // template <typename real>  NOT USED
    // int Vector2<real>::Size() { return m_size; }

    // NOTE 20261008: an index other than 1 returns x without warning.
    template <typename real>
    real Vector2<real>::Element(int index)
    {
        real value = m_x;
        if (index == 1)
            value = m_y;
        return value;
    }

    // METHODS

    template <typename real>
    Vector2<real> Vector2<real>::GetVector()
    {
        Vector2<real> vector(m_x, m_y);
        return vector;
    }

    template <typename real>
    real Vector2<real>::Magnitude()
    {
        real sum = 0;
        sum += m_x * m_x;
        sum += m_y * m_y;
        return (real)sqrt(sum);
    }

    template <typename real>
    Vector2<real> Vector2<real>::UnitVector()
    {
        real x = (real)0;
        real y = (real)0;
        real magnitude = Magnitude();
        if (magnitude > (real)__FLT_EPSILON__)
        {
            x = m_x / magnitude;
            y = m_y / magnitude;
        }
        Vector2<real> vector(x, y);
        return vector;
    }

    template <typename real>
    real Vector2<real>::Distance()
    {
        return Magnitude();
    }

    template <typename real>
    Vector2<real> Vector2<real>::Normalize()
    {
        return UnitVector();
    }

    template <typename real>
    real Vector2<real>::Dot(Vector2<real> v)
    {
        // DOT Product
        // yeilds a Scalar
        real sum = (real)0;
        sum += m_x * v.x();
        sum += m_y * v.y();
        return sum;
    }

    // Angle between two 2D vectors, 0 to pi radians.
    // FIXED 20261008: the dot product of the unit vectors is clamped to
    // -1 to 1 before acos(); rounding could push it slightly outside and
    // acos() then returned NaN. A zero vector gives pi/2.
    // ref: [ELA] by Shields, 1980. p.213.
    template <typename real>
    real Vector2<real>::Angle(Vector2<real> v)
    {
        Vector2<real> u = GetVector();
        real c = u.Normalize() * v.Normalize();
        if (c > (real)1)
            c = (real)1;
        if (c < (real)-1)
            c = (real)-1;
        return (real)acos(c);
    }

    template <typename real>
    Vector2<real> Vector2<real>::Perp()
    {
        // BUGFIX
        // Notes - This can be a little tricky.
        // (1) 90 degrees CW (x, y) = Perp(y, -x) LHR
        // (x, y) * | 0  -1| = (y, -x)
        //          | 1   0|
        // (2) 90 degrees CCW (x, y) = Perp(-y, x) RHR*
        // (x, y) * |  0  1| = (-y, x)
        //          | -1  0|
        // * Right-handed rule
        // Rule: The z-component of the Cross-product
        //       SHOULD equal the DotPerp-product...
        //       Change 2-component to 3-component
        //       vectors by adding zeros.
        // (x1, y1, 0) Cross (x2, y2, 0) = z(X1Y2 - Y1X2)
        // This could be used as the DotPerp...

        // Constructed
        // WAS: Vector2<real> vector(m_y, -m_x);
        Vector2<real> vector(-m_y, m_x);
        return vector;
    }

    template <typename real>
    Vector2<real> Vector2<real>::UnitPerp()
    {
        // Constructed
        Vector2<real> vector = Perp();
        return vector.Normalize();
    }

    // DotPerp() and ZComp() return the same value.
    template <typename real>
    real Vector2<real>::DotPerp(Vector2<real> v)
    {
        // BUGFIX
        // Notes - This can be a little tricky.
        // (1) 90 degrees CW (x, y) = Perp(y, -x) LHR
        // (x, y) * | 0  -1| = (y, -x)
        //          | 1   0|
        // (2) 90 degrees CCW (x, y) = Perp(-y, x) RHR*
        // (x, y) * |  0  1| = (-y, x)
        //          | -1  0|
        // * Right-handed rule
        // Rule: The z-component of the Cross-product
        //       SHOULD equal the DotPerp-product...
        //       Change 2-component to 3-component
        //       vectors by adding zeros.
        // (x1, y1, 0) Cross (x2, y2, 0) = x0, y0, z(X1Y2 - Y1X2)
        // This could be used as the DotPerp...

        // Perpendicular Vector
        Vector2<real> u = Perp();
        // Dot Product
        real value = u * v; // FIXED 20261008: was float

        return value;
    }

    template <typename real>
    real Vector2<real>::ZComp(Vector2<real> v)
    {
        // BUGFIX
        // Notes - This can be a little tricky.
        // (1) 90 degrees CW (x, y) = Perp(y, -x) LHR
        // (x, y) * | 0  -1| = (y, -x)
        //          | 1   0|
        // (2) 90 degrees CCW (x, y) = Perp(-y, x) RHR*
        // (x, y) * |  0  1| = (-y, x)
        //          | -1  0|
        // * Right-handed rule
        // Rule: The z-component of the Cross-product
        //       SHOULD equal the DotPerp-product...
        //       Change 2-component to 3-component
        //       vectors by adding zeros.
        // (x1, y1, 0) Cross (x2, y2, 0) = x0, y0, z(X1Y2 - Y1X2)
        // This could be used as the DotPerp...

        // z-component
        return (m_x * v.y()) - (m_y * v.x());
    }

    // Projection of this vector u onto v: v * (u . v) / (v . v).
    // ref: (1) [ELA] by Shields, 1980. p.237.
    //      (2) [Mf3DG&CG] 2nd Ed. by Lengyel, 2004. p19.
    // FIXED 20261008: a zero vector v returns the zero vector (it divided
    // by zero).
    template <typename real>
    Vector2<real> Vector2<real>::ProjV(Vector2<real> v)
    {
        Vector2<real> u = GetVector();
        real vv = v * v;
        if (vv == (real)0)
        {
            Vector2<real> zero;
            return zero;
        }
        real quot = (u * v) / vv;
        Vector2<real> vector = v * quot;
        return vector;
    }

    // OPERATORS
    template <typename real>
    Vector2<real> Vector2<real>::operator-()
    {
        real x = m_x * (real)-1.0;
        real y = m_y * (real)-1.0;

        // Constructed
        Vector2<real> vector(x, y);
        return vector;
    }

    template <typename real>
    Vector2<real> Vector2<real>::operator*(real s)
    {
        real x = m_x * s;
        real y = m_y * s;

        // Constructed
        Vector2<real> vector(x, y);
        return vector;
    }

    template <typename real>
    Vector2<real> Vector2<real>::operator+(Vector2<real> v)
    {
        real x = m_x + v.x();
        real y = m_y + v.y();

        // Constructed
        Vector2<real> vector(x, y);
        return vector;
    }

    template <typename real>
    Vector2<real> Vector2<real>::operator-(Vector2<real> v)
    {
        real x = m_x - v.x();
        real y = m_y - v.y();

        // Constructed
        Vector2<real> vector(x, y);
        return vector;
    }

    template <typename real>
    real Vector2<real>::operator*(Vector2<real> v)
    {
        // DOT Product
        // yeilds a Scalar
        real sum = 0;

        sum += m_x * v.x();
        sum += m_y * v.y();

        return sum;
    }
}

#endif /* Numerics_Vector2_h */
