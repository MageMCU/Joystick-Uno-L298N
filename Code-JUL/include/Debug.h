//
// Carpenter Software
// File: Debug.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/include
// Origin: MageMCU/Numerics, Algebra/include (merged 20261008)
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

#ifndef Numerics_Debug_h
#define Numerics_Debug_h

#include <Arduino.h>
// Debug(msg) to Debug(msg, a, b, c) are defined in numerics/MiscMath.h
// (the Joystick-Uno-L298N version). This file adds the four and five
// value overloads and the print helpers used by the Numerics tests.
#include "numerics/MiscMath.h"
#include "numerics/Matrix.h"
#include "numerics/Matrix2x2.h"
#include "numerics/Matrix3x3.h"
#include "numerics/Matrix4x4.h"
#include "numerics/Point2.h"
#include "numerics/Point3.h"
#include "numerics/Quaternion.h"
#include "numerics/Vector2.h"
#include "numerics/Vector3.h"

namespace csjc
{
    template <typename T>
    void Debug(String msg, T a, T b, T c, T d)
    {
        Serial.print(msg);
        Serial.print(" a: ");
        Serial.print(a);
        Serial.print(" b: ");
        Serial.print(b);
        Serial.print(" c: ");
        Serial.print(c);
        Serial.print(" d: ");
        Serial.println(d);
    }

    template <typename T>
    void Debug(String msg, T a, T b, T c, T d, T e)
    {
        Serial.print(msg);
        Serial.print(" a: ");
        Serial.print(a);
        Serial.print(" b: ");
        Serial.print(b);
        Serial.print(" c: ");
        Serial.print(c);
        Serial.print(" d: ");
        Serial.print(d);
        Serial.print(" e: ");
        Serial.println(e);
    }

    template <typename real>
    void printResult(String s, real result)
    {
        Serial.print(s);
        Serial.println(String(result, 2));
    }

    template <typename real>
    void printResults(String s1, real result1, String s2, real result2)
    {
        Serial.print(s1);
        Serial.print(result1);
        Serial.print(s2);
        Serial.println(result2);
    }

    template <typename integer>
    void printSpecial(String s1, integer integerNumber, String s2)
    {
        Serial.print(s1);
        Serial.print(integerNumber);
        Serial.print(" - ");
        Serial.println(s2);
    }

    template <typename real>
    void printAngle(String s, int deg, real x, real y, real result)
    {
        Serial.print(s);
        Serial.print(" deg: ");
        Serial.print(deg);
        Serial.print(" v(");
        Serial.print(x);
        Serial.print(", ");
        Serial.print(y);
        Serial.print(") ");
        Serial.print("result: ");
        Serial.println(result);
    }

    template <typename real>
    void printAngle(String s, int deg, real x, real y, real z, real result)
    {
        Serial.print(s);
        Serial.print(" deg: ");
        Serial.print(deg);
        Serial.print(" dv(");
        Serial.print(x);
        Serial.print(", ");
        Serial.print(y);
        Serial.print(", ");
        Serial.print(z);
        Serial.print(") ");
        Serial.print("result: ");
        Serial.println(result);
    }

    template <typename real>
    void printAngle(String s, int deg, Vector3<real> v, real result)
    {
        Serial.print(s);
        Serial.print(" deg: ");
        Serial.print(deg);
        Serial.print(" dv(");
        Serial.print(v.x());
        Serial.print(", ");
        Serial.print(v.y());
        Serial.print(", ");
        Serial.print(v.z());
        Serial.print(") ");
        Serial.print("result: ");
        Serial.println(result);
    }

    template <typename real>
    void printQuaternion(Quaternion<real> q)
    {
        // Float to String takes time (SLOW)
        for (int i = 0; i < 4; i++)
        {
            // Source: Arduino's float data-types
            // The float data type has only 6-7 decimal digits of precision.
            // NOTE: Since the floats printed are mostly less-than the value of one (<1.0)
            //       than 7 decimal digits were used...
            // https://www.arduino.cc/reference/en/language/variables/data-types/float/
            //
            // Source: Arduino's String Object data-types (see note above...)
            // https://www.arduino.cc/reference/en/language/variables/data-types/stringobject/
            //
            // To 7 decimal places
            Serial.print(String(q.Element(i), 7));
            if (i < 3)
            {
                Serial.print(",");
            }
        }
        Serial.println("");
    }

    template <typename real>
    void printQuaternion(String s, Quaternion<real> q, real angle) // -------------- Experimental
    {
        // Float to String takes time (SLOW)
        Serial.print(s);
        for (int i = 0; i < 4; i++)
        {
            // Source: Arduino's float data-types
            // The float data type has only 6-7 decimal digits of precision.
            // NOTE: Since the floats printed are mostly less-than the value of one (<1.0)
            //       than 7 decimal digits were used...
            // https://www.arduino.cc/reference/en/language/variables/data-types/float/
            //
            // Source: Arduino's String Object data-types (see note above...)
            // https://www.arduino.cc/reference/en/language/variables/data-types/stringobject/
            //
            // To 7 decimal places
            Serial.print(String(q.Element(i), 3));
            if (i < 3)
            {
                Serial.print(",");
            }
        }
        Serial.print(" angle: ");
        Serial.println(String(angle, 3));
    }

    template <typename real>
    void printQuaternion(String s, Quaternion<real> q)
    {
        Serial.print(s);
        for (int i = 0; i < 4; i++)
        {
            // only prints 2 decimal places
            Serial.print(q.Element(i));
            Serial.print(" ");
        }
        Serial.println("");
    }

    template <typename real>
    void printMatrix(String s, Matrix<real> M)
    {
        Serial.println(s);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                Serial.print(M.Element(i, j));
                Serial.print(" ");
            }
            Serial.println("");
        }
    }

    template <typename real>
    void printMatrix4x4(String s, Matrix4x4<real> M)
    {
        Serial.println(s);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                Serial.print(M.GetElement(i, j));
                Serial.print(" ");
            }
            Serial.println("");
        }
    }

    template <typename real>
    void printMatrix3x3(String s, Matrix3x3<real> M)
    {
        Serial.println(s);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                Serial.print(M.GetElement(i, j));
                Serial.print(" ");
            }
            Serial.println("");
        }
    }

    template <typename real>
    void printMatrix2x2(String s, Matrix2x2<real> M)
    {
        Serial.println(s);

        Serial.print(String(M.E00(), 2));
        Serial.print(" ");
        Serial.println(String(M.E01(), 2));

        Serial.print(String(M.E10(), 2));
        Serial.print(" ");
        Serial.println(String(M.E11(), 2));
    }

    template <typename real>
    void printVector3(String s, Vector3<real> v)
    {
        Serial.print(s);
        Serial.print(" (");
        Serial.print(v.x());
        Serial.print(", ");
        Serial.print(v.y());
        Serial.print(", ");
        Serial.print(v.z());
        Serial.println(") ");
    }

    template <typename real>
    void printVector2(String s, Vector2<real> v)
    {
        Serial.print(s);
        Serial.print(" (");
        Serial.print(v.x());
        Serial.print(", ");
        Serial.print(v.y());
        Serial.println(") ");
    }

    template <typename real>
    void printPoint3(String s, Point3<real> p)
    {
        Serial.print(s);
        Serial.print(" (");
        Serial.print(p.x());
        Serial.print(", ");
        Serial.print(p.y());
        Serial.print(", ");
        Serial.print(p.z());
        Serial.println(") ");
    }

    template <typename real>
    void printPoint2(String s, Point2<real> p)
    {
        Serial.print(s);
        Serial.print(" (");
        Serial.print(p.x());
        Serial.print(", ");
        Serial.print(p.y());
        Serial.println(") ");
    }

    void printTitle(String s)
    {
        Serial.print("---------------- + ");
        Serial.print(s);
        Serial.println(" +");
    }

    void printSubTitle(String s)
    {
        Serial.print(" ** ");
        Serial.print(s);
        Serial.println(" **");
    }

    void printNewLine()
    {
        Serial.println("");
    }
}

#endif
