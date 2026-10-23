//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: Class Point2.h
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

// Point2<real>: a 2D position. Point - Point gives a Vector2; Point + Vector2
// gives a Point2. Merged from MageMCU/Numerics (Algebra/include, 20241202).

#ifndef Numerics_Point2_h
#define Numerics_Point2_h

#include "Arduino.h"
#include "Vector2.h"

namespace csjc
{
    template <typename real>
    // FIXED 20261008: Point2 no longer inherits from Vector2 (it used none of
    // its members and stored a second set of coordinates).
    // TEACHING NOTES (v6.1.1)
    // A point is a position; a vector is a displacement, a step with a size
    // and a direction (Vector2.h). Both are written (x, y), but they follow
    // different rules, the rules of affine geometry:
    //   point - point   = vector  (the step from one position to another)
    //   point + vector  = point   (a position moved by a step)
    //   point + point   has no meaning, so this class does not define it.
    // Keeping the two types apart lets the compiler catch such mistakes.
    // Example: from P = (1, 2) to Q = (4, 6) the step is Q - P = (3, 4),
    // of length 5, and P + (3, 4) = Q.
    class Point2
    {
    private:
        // MEMBERS
        int m_size;
        real m_x;
        real m_y;

    public:
        // CONSTRUCTORS
        Point2();
        Point2(real x, real y);
        Point2(const real array[]);
        Point2(Vector2<real> v);

        // DESTRUCTOR
        ~Point2() {}

        // GETTERS & SETTERS
        void x(real x);
        real x();
        void y(real y);
        real y();
        int Size();
        real Element(int index);
        // METHODS (there are only two)
        Point2 GetPoint();
        Vector2<real> operator-(Point2<real> p);
        Point2 operator+(Vector2<real> p);
    };

    template <typename real>
    Point2<real>::Point2()
    {
        m_size = 2;
        m_x = (real)0;
        m_y = (real)0;
    }

    template <typename real>
    Point2<real>::Point2(real x, real y)
    {
        m_size = 2;
        m_x = x;
        m_y = y;
    }

    template <typename real>
    Point2<real>::Point2(const real array[])
    {
        m_size = 2;
        m_x = array[0];
        m_y = array[1];
    }

    template <typename real>
    Point2<real>::Point2(Vector2<real> v)
    {
        m_size = 2;
        m_x = v.x();
        m_y = v.y();
    }

    // GETTERS & SETTERS
    template <typename real>
    void Point2<real>::x(real x) { m_x = x; }
    template <typename real>
    real Point2<real>::x() { return m_x; }

    template <typename real>
    void Point2<real>::y(real y) { m_y = y; }
    template <typename real>
    real Point2<real>::y() { return m_y; }

    template <typename real>
    int Point2<real>::Size() { return m_size; }

    template <typename real>
    real Point2<real>::Element(int index)
    {
        real value = m_x;
        if (index == 1)
            value = m_y;
        return value;
    }

    // PUBLIC METHODS
    template <typename real>
    Point2<real> Point2<real>::GetPoint()
    {
        Point2<real> p(m_x, m_y);
        return p;
    }

    // Q - P: the vector that leads from P to Q.
    template <typename real>
    Vector2<real> Point2<real>::operator-(Point2<real> p)
    {
        // Vector = Point - Point
        real x = m_x - p.x();
        real y = m_y - p.y();

        // Constructed
        Vector2<real> vector(x, y);
        return vector;
    }

    // P + v: the point reached from P by the step v.
    template <typename real>
    Point2<real> Point2<real>::operator+(Vector2<real> v)
    {
        // Point = Point + Vector
        real x = m_x + v.x();
        real y = m_y + v.y();

        Point2<real> point(x, y);
        return point;
    }
}

#endif /* Numerics_Point2_h */