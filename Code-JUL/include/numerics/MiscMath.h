//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: MiscMath.h
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

// MiscMath.h: function templates (Square, angle functions, direction vectors,
// Map, absT) and the Debug() serial print helpers.
// Step1_Joystick and Step2_JUL use absT() and Debug().

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

    // REVIEW 20261008: angle of the vector (a, b) in radians, 0 to 2 pi.
    // b / a relies on floating point division by zero: at a = 0 the quotient
    // is plus or minus infinity and atan() returns plus or minus pi/2, so the
    // y axis is still correct. At (0, 0) the quotient is 0/0 = NaN and the
    // result is NaN. Angle2Radian() below uses atan2() and returns 0 there.
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

    // REVIEW 20261008: calls DirectionVector(), which is defined after this function.
    // It compiles because the Plane2D argument lets the compiler find
    // DirectionVector() in namespace csjc when the template is instantiated
    // (argument dependent lookup). Defining DirectionVector() first is clearer.
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
    // REVIEW 20261008: same formula as LinearMap::Map(). With int arguments it
    // overflows on the Uno exactly as LinearMap<int> does.
    template <typename real>
    real Map(real x, real x1, real x2, real y1, real y2)
    {
        // Assume linear functions
        // m = (y2 - y1)/(x2 - x1)
        // (y - y1) = m(x - x1)
        return (y2 - y1) * (x - x1) / (x2 - x1) + y1;
    }

    // REVIEW 20261008: for a signed integer type the most negative value has no
    // positive counterpart (int: -32768 on the Uno), so absT<int>(-32768)
    // cannot return +32768. L298N.h passes values in -255 to 255.
    template <typename T>
    T absT(T val)
    {
        T zero = (T)0;
        if (val < zero)
            val *= (T)-1;
        return val;
    }

    // REVIEW 20261008: an ordinary (non template) function defined in a header.
    // If two .cpp files in one program include this header, the linker
    // reports a multiple definition. Marking it inline removes the problem.
    // The Debug() overloads use Arduino String, which allocates heap memory.
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
