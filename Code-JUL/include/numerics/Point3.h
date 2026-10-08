//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: Class Point3.h
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

// Point3<real>: a 3D position. Point - Point gives a Vector3; Point + Vector3
// gives a Point3. Merged from MageMCU/Numerics (Algebra/include, 20241202).

#ifndef Numerics_Point3_h
#define Numerics_Point3_h

#include "Arduino.h"
#include "Vector3.h"

namespace csjc
{
    template <typename real>
    // FIXED 20261008: Point3 no longer inherits from Vector3 (it used none of
    // its members and stored a second set of coordinates).
    class Point3
    {
    private:
        // MEMBERS
        int m_size;
        real m_x;
        real m_y;
        real m_z;

    public:
        // CONSTRUCTORS
        Point3();
        Point3(real x, real y, real z);
        Point3(const real array[]);
        Point3(Vector3<real>);

        // DESTRUCTOR
        ~Point3() {}

        // GETTERS & SETTERS
        void x(real x);
        real x();
        void y(real y);
        real y();
        void z(real z);
        real z();
        int Size();
        real Element(int index);

        // METHODS (there are only two)
        Point3 GetPoint();
        Vector3<real> operator-(Point3<real> p);
        Point3 operator+(Vector3<real> p);
    };

    template <typename real>
    Point3<real>::Point3()
    {
        m_size = 3;
        m_x = (real)0;
        m_y = (real)0;
        m_z = (real)0;
    }

    template <typename real>
    Point3<real>::Point3(real x, real y, real z)
    {
        m_size = 3;
        m_x = x;
        m_y = y;
        m_z = z;
    }

    template <typename real>
    Point3<real>::Point3(const real array[])
    {
        m_size = 3;
        m_x = array[0];
        m_y = array[1];
        m_z = array[2];
    }

    template <typename real>
    Point3<real>::Point3(Vector3<real> v)
    {
        m_size = 3;
        m_x = v.x();
        m_y = v.y();
        m_z = v.z();
    }

    // GETTERS & SETTERS
    template <typename real>
    void Point3<real>::x(real x) { m_x = x; }
    template <typename real>
    real Point3<real>::x() { return m_x; }

    template <typename real>
    void Point3<real>::y(real y) { m_y = y; }
    template <typename real>
    real Point3<real>::y() { return m_y; }

    template <typename real>
    void Point3<real>::z(real z) { m_z = z; }
    template <typename real>
    real Point3<real>::z() { return m_z; }

    template <typename real>
    int Point3<real>::Size() { return m_size; }

    template <typename real>
    real Point3<real>::Element(int index)
    {
        real value = m_x;
        if (index == 1)
            value = m_y;
        if (index == 2)
            value = m_z;
        return value;
    }

    // PUBLIC METHODS
    template <typename real>
    Point3<real> Point3<real>::GetPoint()
    {
        Point3<real> p(m_x, m_y, m_z);
        return p;
    }

    template <typename real>
    Vector3<real> Point3<real>::operator-(Point3<real> p)
    {
        // Vector = Point - Point
        real x = m_x - p.x();
        real y = m_y - p.y();
        real z = m_z - p.z();

        // Constructed
        Vector3<real> vector(x, y, z);
        return vector;
    }

    template <typename real>
    Point3<real> Point3<real>::operator+(Vector3<real> v)
    {
        // Point = Point + Vector
        real x = m_x + v.x();
        real y = m_y + v.y();
        real z = m_z + v.z();

        Point3<real> point(x, y, z);
        return point;
    }
}

#endif /* Numerics_Point3_h */