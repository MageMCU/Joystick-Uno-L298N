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
// RELEASE
//   2026-10-30  v7.3.0
//   MiscMath.h last changed: 2026-10-28  v6.8.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

// MiscMath.h: function templates (Square, angle functions, direction vectors,
// Map, absT) and the Debug() serial print helpers.
// Step2_JUL uses absT() and Debug().

#ifndef Numerics_MiscMath_h
#define Numerics_MiscMath_h

#include "Arduino.h"
#include "Vector3.h"

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    // TEACHING NOTES (v6.1.1)
    // These are function templates: functions written once for a type
    // parameter (real is float or double; T any number type).
    // Angles are in radians: a full turn is 2 pi radians (360 degrees), so
    // 1 radian = 180 / pi = 57.3 degrees. Arduino defines PI, DEG_TO_RAD,
    // and RAD_TO_DEG.
    // A plane is a flat surface through the origin. Plane2D names the two
    // axes of a direction in 3D space: XY (the floor), XZ, or YZ.
    enum Plane2D
    {
        XY = 1,
        XZ,
        YZ
    };

    // FUNCTION-TEMPLATES

    // Square(v) = v * v; faster and exact for integers, unlike pow(v, 2).
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
    // AngleRadian(a, b): the angle of the vector (a, b) from the positive x
    // axis, counterclockwise, 0 to 2 pi. atan(b / a) gives the reference
    // angle, -pi/2 to pi/2, which cannot tell the quadrants apart (the four
    // quarters of the plane); the if statements add pi or 2 pi by the signs
    // of a and b. Example: (-1, 1) gives atan(-1) = -pi/4, plus pi = 3 pi/4
    // (135 degrees).
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

    // Angle2Radian(a, b): the same angle with atan2(b, a), which reads the
    // signs of both arguments and returns -pi to pi; adding 2 pi to a
    // negative result gives 0 to 2 pi.
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

    // REVIEW 20261008: calls DirectionVector(), which is defined after this
    // function.
    // It compiles because the Plane2D argument lets the compiler find
    // DirectionVector() in namespace csjc when the template is instantiated
    // (argument dependent lookup). Defining DirectionVector() first is clearer.
    // DirectionComponents(): the unit vector of DirectionVector() returned
    // through references (real &x): the function writes into the caller's
    // variables instead of returning a value.
    template <typename real>
    void DirectionComponents(real angleRadian, real &x, real &y, real &z,
                             Plane2D plane2D)
    {
        Vector3<real> vector = DirectionVector(angleRadian, plane2D);
        x = vector.x();
        y = vector.y();
        z = vector.z();
    }

    // DirectionVector(angle, plane): the unit vector (length 1) at the
    // angle, (cos, sin), placed on the two axes of the plane. cos gives the
    // part along the first axis and sin the part along the second.
    // Example: 90 degrees in XY gives (0, 1, 0).
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
            // X
            x = a;
            // Y
            y = b;
            break;
        case XZ:
            // X
            x = a;
            // Z
            z = b;
            break;
        case YZ:
            // Y
            y = a;
            // Z
            z = b;
            break;
        default:
            // X
            x = a;
            // Y
            y = b;
            break;
        }
        Vector3<real> vector(x, y, z);
        return vector;
    }

    // See also LinearMap.h
    // REVIEW 20261008: same formula as LinearMap::Map(). With int arguments it
    // overflows on the Uno exactly as LinearMap<int> does.
    // Map(): the straight line through (x1, y1) and (x2, y2) at x; the
    // formula and an example are in LinearMap.h, Map().
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
    // absT(v): the absolute value |v|, the distance from 0 without the sign.
    // Example: absT(-0.04) = 0.04; Step2_JUL compares it with the dead zone.
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
    // Debug(): print a message and one to three values on one line, for
    // reading the signal chain of Step2_JUL in the serial monitor. Several
    // functions share the name and differ in their parameters (overloads);
    // the compiler picks the one that matches the call.
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

// Numerics_Misc_h
#endif
