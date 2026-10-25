//
// Carpenter Software
// File: L04_MiscMath.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L04_MiscMath, selected with LESSON 4 in Step5_MathLessons/main.cpp
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestMiscMath.h (merged 20261008)
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

// TEACHING NOTES (v6.1.1)
// Lesson 4: the function templates of include/numerics/MiscMath.h:
// Map(), the angle of a vector, the unit vector of an angle, and the
// absolute value. Radians, quadrants, atan(), atan2(), and the unit
// vector (cos, sin) are explained there, at each function.
// DEG_TO_RAD (pi / 180) turns degrees into radians. Each angle topic
// goes around the full circle in steps of 5 degrees: from the angle to
// a vector, then from the vector back to the angle, which should give
// the angle again, from 0 to 6.28 radians (2 pi).
// The topics run T01 to T06 (see Setup()).
#ifndef Lesson_L04_MiscMath_h
#define Lesson_L04_MiscMath_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 6

#include <Arduino.h>
#include "Debug.h"

namespace L04_MiscMath
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// T06: absT(-4.9384) = 4.938400.
// ---------------------------------------------------------------
// MiscMath_T06_AbsoluteValue (teaching notes, v6.3.0)
// Hint: AbsoluteValue, the size of a number without its sign.
// Purpose: absT<float>(), the template absolute value, and why it is
// used in place of the Arduino abs() macro.
// What is learnt:
//   |x|            x when x >= 0, otherwise -x.
//   Macro and template: Arduino abs() is a macro, a text substitution
//                  that evaluates its argument twice (abs(i++) adds 2).
//                  absT<T>() is a function template; its argument is
//                  evaluated once and its type is checked.
//   String(value, 6)  converts a float to text with 6 decimal places.
// Expected output:
//   value = -4.9384
//   absT<float>(-4.9384):  a: 4.938400
//   (v6.4.1: the input is printed first; Debug() names its value a.)
// ---------------------------------------------------------------
void MiscMath_T06_AbsoluteValue()
{
    printTitle(F("MiscMath T06 Absolute Value"));

    float value = -4.9384;
    Serial.print(F("value = ")); // v6.4.1: print the input
    Serial.println(value, 4);
    value = absT<float>(value);
    Debug<String>("absT<float>(-4.9384): ", String(value, 6));

}

// T05: DirectionVector() in the XZ plane: y stays 0 and the angle comes
// back from (x, z). Example: 90 degrees gives (0, 0, 1) and 1.57 rad.
// ---------------------------------------------------------------
// MiscMath_T05_DirectionVector (teaching notes, v6.3.0)
// Hint: DirectionVector, the angle returned as one Vector3 object.
// Purpose: the same as T04, but the result is a single object, and the
// plane is XZ, the floor plane of a robot simulation (y is up).
// What is learnt:
//   Return by value  DirectionVector(rad, XZ) returns a Vector3<float>;
//                  vector = ... copies it into the variable declared
//                  before the loop.
//   Getters        vector.x() and vector.z() read the components.
//   T04 and T05 compared: references give loose numbers; a returned
//   object keeps the three components together.
// Expected output (72 lines, after a line that names the columns,
// v6.4.1):
//   DirectionVector:  deg: 0 dv(1.00, 0.00, 0.00) result: 0.00
//   DirectionVector:  deg: 5 dv(1.00, 0.00, 0.09) result: 0.09
// ---------------------------------------------------------------
void MiscMath_T05_DirectionVector()
{
    printTitle(F("MiscMath T05 Direction Vector"));
    // v6.4.1: name the columns: the input angle, the vector, the result.
    Serial.println(F("deg: angle in degrees; dv = DirectionVector(rad, XZ); result: AngleRadian(x, z) in radians"));

    float rad;
    Vector3<float> vector;

    // Covers an entire unit circle
    for (int deg = 0; deg < 360; deg += 5)
    {
        rad = (float)deg * DEG_TO_RAD;
        // angle to 3D directional unit vector
        // Note: x, y, and z are referenced as outputs....
        vector = DirectionVector(rad, XZ);
        // 2D-Vector back to radian using XZ...
        rad = AngleRadian(vector.x(), vector.z());
        // Debug Test
        printAngle("DirectionVector: ", deg, vector, rad);
    }
}

// T04: the same in the XY plane, with the three components returned
// through references; z stays 0.
// ---------------------------------------------------------------
// MiscMath_T04_DirectionComponents (teaching notes, v6.3.0)
// Hint: DirectionComponents, the angle returned as three separate
// numbers through reference parameters.
// Purpose: how one function can hand back more than one result.
// What is learnt:
//   Reference parameter  DirectionComponents(rad, x, y, z, XY) receives
//                  x, y, and z as float&: the function writes into the
//                  caller's variables directly, so they are outputs.
//   Plane selector XY places the unit vector in the x y plane; z stays 0.
//   printAngle() overloads: this call passes five numbers (x, y, z, and
//                  the result) and prints dv(x, y, z).
// Expected output (72 lines, 0 to 355 degrees, after a line that names
// the columns, v6.4.1):
//   DirectionComponents:  deg: 0 dv(1.00, 0.00, 0.00) result: 0.00
//   DirectionComponents:  deg: 355 dv(1.00, -0.09, 0.00) result: 6.20
// ---------------------------------------------------------------
void MiscMath_T04_DirectionComponents()
{
    printTitle(F("MiscMath T04 Direction Components"));
    // v6.4.1: name the columns: the input angle, the vector, the result.
    Serial.println(F("deg: angle in degrees; dv = DirectionComponents(rad, x, y, z, XY); result: AngleRadian(x, y) in radians"));

    float x;
    float y;
    float z;
    float rad;

    // Covers an entire unit circle
    for (int deg = 0; deg < 360; deg += 5)
    {
        rad = (float)deg * DEG_TO_RAD;
        // angle to 3D directional unit vector
        // Note: x, y, and z are referenced as outputs....
        DirectionComponents(rad, x, y, z, XY);
        // 2D-Vector back to radian using XY...
        rad = AngleRadian(x, y);
        // Debug Test
        printAngle("DirectionComponents: ", deg, x, y, z, rad);
    }
}

// T03: Angle2Radian() with atan2(). At 360 degrees the result may read
// 0.00 or 6.28: cos and sin of 2 pi in float give y a tiny value just
// below or above 0, and both mean the same direction.
// ---------------------------------------------------------------
// MiscMath_T03_Angle2Radian (teaching notes, v6.3.0)
// Hint: Angle2Radian, the second way to the angle, with atan2().
// Purpose: the same round trip as T02 with the library function atan2(),
// so the two methods can be compared line by line.
// What is learnt:
//   atan2(y, x)    takes the two components separately, so it knows the
//                  quadrant itself and needs no correction; it is also
//                  defined at x = 0, where atan(y / x) divides by zero.
//   -0.00          float has a signed zero; cos(90 degrees) computes to
//                  a tiny negative number that prints as -0.00.
//   Two methods, one answer: a second calculation is a check on the first.
// Expected output: a line that names the columns (v6.4.1), then the
// same results as T02, for example
//    Angle2Radian:  deg: 90 v(-0.00, 1.00) result: 1.57
//    Angle2Radian:  deg: 360 v(1.00, 0.00) result: 0.00 (or 6.28)
// ---------------------------------------------------------------
void MiscMath_T03_Angle2Radian()
{
    printTitle(F("MiscMath T03 Angle2Radian"));
    // v6.4.1: name the columns: the input angle, the vector, the result.
    Serial.println(F("deg: angle in degrees; v = (cos, sin); result: Angle2Radian(x, y) in radians"));
    float x;
    float y;
    float rad;

    // Covers an entire unit circle
    for (int deg = 0; deg < 360 + 1; deg += 5)
    {
        rad = (float)deg * DEG_TO_RAD;
        // create a unit-vector
        x = cos(rad);
        y = sin(rad);
        // convert vector to angle
        rad = Angle2Radian(x, y);
        // Debug Test
        printAngle(" Angle2Radian: ", deg, x, y, rad);
    }
}

// T02: AngleRadian() with atan() and the quadrant corrections; it
// should agree with T03.
// ---------------------------------------------------------------
// MiscMath_T02_AngleRadian (teaching notes, v6.3.0)
// Hint: AngleRadian, the angle of a vector, found with atan().
// Purpose: to turn a vector (x, y) back into its angle around the whole
// circle, 0 to 2 pi, and check it against the angle that made it.
// What is learnt:
//   Radian         the angle unit of the math library; 2 pi rad = 360
//                  degrees, and DEG_TO_RAD = pi / 180 converts.
//   Unit vector of an angle: (cos a, sin a), length 1.
//   atan(y / x)    gives only -90 to 90 degrees; AngleRadian() adds the
//                  quadrant correction, the fix that depends on the signs
//                  of x and y, to cover the full circle.
//   Round trip test: angle to vector to angle.
// Expected output: a line that names the columns (v6.4.1), then 73
// lines, 0 to 360 degrees in steps of 5:
//   AngleRadian:  deg: 0 v(1.00, 0.00) result: 0.00
//   AngleRadian:  deg: 90 v(-0.00, 1.00) result: 1.57
//   AngleRadian:  deg: 180 v(-1.00, -0.00) result: 3.14
//   AngleRadian:  deg: 355 v(1.00, -0.09) result: 6.20
// ---------------------------------------------------------------
void MiscMath_T02_AngleRadian()
{
    printTitle(F("MiscMath T02 AngleRadian"));
    // v6.4.1: name the columns: the input angle, the vector, the result.
    Serial.println(F("deg: angle in degrees; v = (cos, sin); result: AngleRadian(x, y) in radians"));
    float x;
    float y;
    float rad;

    // Covers an entire unit circle
    for (int deg = 0; deg < 360 + 1; deg += 5)
    {
        rad = (float)deg * DEG_TO_RAD;
        x = cos(rad);
        y = sin(rad);
        rad = AngleRadian(x, y);
        // Debug Test
        printAngle("AngleRadian: ", deg, x, y, rad);
    }
}

// T01: Map() between the two temperature scales: 77 F = 25 C and
// 25 C = 77 F (the formula is in LinearMap.h).
// ---------------------------------------------------------------
// MiscMath_T01_Map (teaching notes, v6.3.0)
// Hint: Map, the linear map as a free function, not a class.
// Purpose: the same Fahrenheit and Celsius conversion as lesson 3,
// written with one function call that takes all five values.
// What is learnt:
//   Free function  a function outside any class; no object is declared.
//   Function template  Map<float>(x, x1, x2, y1, y2): <float> sets the
//                  type of every parameter, so each constant is cast,
//                  (float)32, to match it.
//   Swapping the scales reverses the map: (32, 212, 0, 100) goes from F
//   to C, and (0, 100, 32, 212) from C back to F.
//   When to use which: the free Map() for a one time conversion; the
//   LinearMap class of lesson 3 when one map is used many times.
// Expected output:
//   fahrenheit: 77.00
//   celcius = Map<float>(fahrenheit, 32, 212, 0, 100): 25.00
//   celcius: 25.00
//   fahrenheit = Map<float>(celcius, 0, 100, 32, 212): 77.00
//   (v6.3.1: the labels name Map<float>() as called, and the subtitles
//   spell Celsius; up to v6.3.0 they read dM.map() and Celcius. The
//   variable keeps its original name, celcius.)
// ---------------------------------------------------------------
void MiscMath_T01_Map()
{
    printTitle(F("MiscMath T01 Map"));

    printSubTitle("Fahrenheit to Celsius");
    // fahrenheit to celcius
    float fahrenheit = 77;
    Serial.print("fahrenheit: ");
    Serial.println(fahrenheit);
    float celcius = Map<float>(fahrenheit, (float)32, (float)212, (float)0, (float)100);
    Serial.print("celcius = Map<float>(fahrenheit, 32, 212, 0, 100): ");
    Serial.println(celcius);

    printSubTitle("Celsius to Fahrenheit");
    celcius = 25;
    Serial.print("celcius: ");
    Serial.println(celcius);
    fahrenheit = Map<float>(celcius, (float)0, (float)100, (float)32, (float)212);
    Serial.print("fahrenheit = Map<float>(celcius, 0, 100, 32, 212): ");
    Serial.println(fahrenheit);
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    MiscMath_T01_Map();
#endif
#if TOPIC == 0 || TOPIC == 2
    MiscMath_T02_AngleRadian();
#endif
#if TOPIC == 0 || TOPIC == 3
    MiscMath_T03_Angle2Radian();
#endif
#if TOPIC == 0 || TOPIC == 4
    MiscMath_T04_DirectionComponents();
#endif
#if TOPIC == 0 || TOPIC == 5
    MiscMath_T05_DirectionVector();
#endif
#if TOPIC == 0 || TOPIC == 6
    MiscMath_T06_AbsoluteValue();
#endif
}

void Loop()
{
}
} // namespace L04_MiscMath

#endif // Lesson_L04_MiscMath_h
