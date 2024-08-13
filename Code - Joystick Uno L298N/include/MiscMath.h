//
// Carpenter Software
// File: Class MiscMath.h
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

#ifndef Numerics_MiscMath_h
#define Numerics_MiscMath_h

#include "Arduino.h"
#include "Vector3.h"

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    enum Plane2D
    {
        XY = 1,
        XZ,
        YZ
    };

    // FUNCTION-TEMPLATES

    template <typename real>
    real Square(real value)
    {
        return value * value;
    }

    template <typename real>
    real AngleRadian(real a, real b)
    {
        // Division by zero requires no check
        // QuadI (refAngle)
        real refAngle = atan((double)b / (double)a);
        // QuadII
        if (a < (real)0 && b >= (real)0)
        {
            refAngle = (real)PI + refAngle;
        }
        // QuadIII
        if (a < (real)0 && b < (real)0)
        {
            refAngle = (real)PI + refAngle;
        }
        // QuadIV
        if (a >= (real)0 && b < (real)0)
        {
            refAngle = (real)2.0 * (real)PI + refAngle;
        }

        return refAngle;
    }

    template <typename real>
    real Angle2Radian(real a, real b)
    {
        // Division by zero requires no check when using Mathf
        // Quad I & II (refAngle)
        real refAngle = atan2((double)b, (double)a);
        // Quad III & IV
        if (b < (real)0)
        {
            refAngle = refAngle + (real)2.0 * (real)PI;
        }

        return refAngle;
    }

    template <typename real>
    void DirectionComponents(real angleRadian, real &x, real &y, real &z, Plane2D plane2D)
    {
        Vector3<real> vector = DirectionVector(angleRadian, plane2D);
        x = vector.x();
        y = vector.y();
        z = vector.z();
    }

    template <typename real>
    Vector3<real> DirectionVector(real angleRadian, Plane2D plane2D)
    {

        real a = cos(angleRadian);
        real b = sin(angleRadian);
        real x = (real)0;
        real y = (real)0;
        real z = (real)0;
        switch (plane2D)
        {
        case XY:
            x = a; // X
            y = b; // Y
            break;
        case XZ:
            x = a; // X
            z = b; // Z
            break;
        case YZ:
            y = a; // Y
            z = b; // Z
            break;
        default:
            x = a; // X
            y = b; // Y
            break;
        }
        Vector3<real> vector(x, y, z);
        return vector;
    }

    // See also LinearMap.h
    template <typename real>
    real Map(real x, real x1, real x2, real y1, real y2)
    {
        // Assume linear functions
        // m = (y2 - y1)/(x2 - x1)
        // (y - y1) = m(x - x1)
        return (y2 - y1) * (x - x1) / (x2 - x1) + y1;
    }

    template <typename T>
    T absT(T val)
    {
        T zero = (T)0;
        if (val < zero)
            val *= (T)-1;
        return val;
    }

    void Debug(String msg)
    {
        Serial.println(msg);
    }

    template <typename T>
    void Debug(String msg, T a)
    {
        Serial.print(msg);
        Serial.print(" a: ");
        Serial.println(a);
    }

    template <typename T>
    void Debug(String msg, T a, T b)
    {
        Serial.print(msg);
        Serial.print(" a: ");
        Serial.print(a);
        Serial.print(" b: ");
        Serial.println(b);
    }

    template <typename S, typename T>
    void Debug(String msg, S a, T b)
    {
        Serial.print(msg);
        Serial.print(" a: ");
        Serial.print(a);
        Serial.print(" b: ");
        Serial.println(b);
    }

    template <typename T>
    void Debug(String msg, T a, T b, T c)
    {
        Serial.print(msg);
        Serial.print(" a: ");
        Serial.print(a);
        Serial.print(" b: ");
        Serial.print(b);
        Serial.print(" c: ");
        Serial.println(c);
    }
}

#endif /* Numerics_Misc_h */