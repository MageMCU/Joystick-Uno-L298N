//
// Carpenter Software
// File: L08_Point2.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L08_Point2, selected with LESSON 8 in Step5_MathLessons/main.cpp
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestPoint2.h (merged 20261008)
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
// RELEASE
//   2026-10-28  v6.8.0
//   L08_Point2.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

// TEACHING NOTES (v6.1.1)
// Lesson 8: points and vectors in the plane. The two rules,
// point - point = vector and point + vector = point, and why points and
// vectors are kept apart, are explained in include/numerics/Point2.h.
// The topics run T01 to T04 (see Setup()).
#ifndef Lesson_L08_Point2_h
#define Lesson_L08_Point2_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 4

#include <Arduino.h>
#include "Debug.h"

namespace L08_Point2
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// T04: the point (8, -4) moved by the vector (6, 2) is (14.00, -2.00).
// ---------------------------------------------------------------
// Point2_T04_PointFromPointVectorAddition (teaching notes, v6.3.0)
// Hint: PointFromPointVectorAddition, point plus vector gives a point.
// Purpose: move a point by a step.
// What is learnt:
//   Rule 2         point + vector = point: a location moved by a
//                  displacement is a new location.
//   operator+(Vector2) is a member of Point2; the right operand must be a
//   vector.
//   Check: (8 + 6, -4 + 2) = (14, -2).
// Expected output:
//   p2 = p1 + v = (14.00, -2.00)
// ---------------------------------------------------------------
void Point2_T04_PointFromPointVectorAddition()
{
    printTitle(F("Point2 T04 Point from Point Vector Addition"));

    Point2<float> p1(8, -4);
    printPoint2("p1(8, -4) =", p1);

    Vector2<float> v(6, 2);
    printVector2("v(6, 2) =", v);

    printSubTitle("Point = Point + Vector");

    Point2<float> p2 = p1 + v;
    printPoint2("p2 = p1 + v =", p2);
}

// T03: from (2, 7) to (8, -4) the step is (8, -4) - (2, 7) =
// (6.00, -11.00).
// ---------------------------------------------------------------
// Point2_T03_VectorFromPointPointSubtraction (teaching notes, v6.3.0)
// Hint: VectorFromPointPointSubtraction, point minus point gives a
// vector.
// Purpose: the step from one point to another, p1 - p2.
// What is learnt:
//   Rule 1         point - point = vector: the difference of two locations
//                  is a displacement, a step with a direction and a length.
//   Return type    operator-(Point2) returns a Vector2, not a Point2, so
//                  the result is stored in Vector2<float> v.
//   Type safety    the classes let the compiler reject meaningless sums
//                  such as point + point.
//   Check: (8 - 2, -4 - 7) = (6, -11): from p2 to p1.
// Expected output:
//   v = p1 - p2 = (6.00, -11.00)
// ---------------------------------------------------------------
void Point2_T03_VectorFromPointPointSubtraction()
{
    printTitle(F("Point2 T03 Vector from Point Point Subtraction"));

    Point2<float> p1(8, -4);
    printPoint2("p1(8, -4) =", p1);

    Point2<float> p2(2, 7);
    printPoint2("p2(2, 7) =", p2);

    printSubTitle("Vector = Point - Point");

    Vector2<float> v = p1 - p2;
    printVector2("v = p1 - p2 =", v);
}

// T02: GetPoint() returns a copy, (3.00, 7.00).
// ---------------------------------------------------------------
// Point2_T02_GetPoint (teaching notes, v6.3.0)
// Hint: GetPoint, return a copy of the point.
// Purpose: a member function that returns a new object equal to the
// original.
// What is learnt:
//   Return by value  p2 is a separate object; changing p2 later leaves p1
//                  as it is.
//   Point2<float> p2 = p1; would give the same result through the copy
//   constructor the compiler writes (see lesson 7, T17).
// Expected output:
//   p1 (3.00, 7.00)
//   p2 (3.00, 7.00)
// ---------------------------------------------------------------
void Point2_T02_GetPoint()
{
    printTitle(F("Point2 T02 GetPoint"));

    Point2<float> p1(3, 7);
    printPoint2("p1", p1);

    Point2<float> p2 = p1.GetPoint();
    printPoint2("p2", p2);
}

// ---------------------------------------------------------------
// Point2_T01_Constructor (teaching notes, v6.3.0)
// Hint: Constructor, build a point in the plane.
// Purpose: how to declare and instantiate Point2 variables, the four
// constructors, and the getters and setters of the coordinates.
// What is learnt:
//   Point          a location, (x, y); a vector (lesson 7) is a step with
//                  a direction and a length. They hold the same two
//                  numbers but follow different rules (T03, T04).
//   Four constructors (overloads):
//     Point2<float> p1;           default, the origin (0, 0)
//     Point2<float> p2(1, 2);     from two values
//     Point2<float> p3(array);    from an array of two values
//     Point2<float> p4(v);        from a vector: the point reached by the
//                                 step v from the origin
//   Getters        p2.x(), p2.y(), p2.Element(1) (index 0 is x, 1 is y).
//   Setters        p1.x(5), p1.y(-3) write the coordinates.
// Expected output:
//   p1 = (0.00, 0.00)   p2(1, 2) = (1.00, 2.00)   p3(array) = (3.00, 4.00)
//   v(1, 2) = (1.00, 2.00)   p4(v) = (1.00, 2.00)
//   p2.x() 1.00   p2.y() 2.00   p2.Element(1) 2.00
//   p1 = (5.00, -3.00)   (after the setters)
// ---------------------------------------------------------------
void Point2_T01_Constructor()
{
    printTitle(F("Point2 T01 Constructor"));

    Point2<float> p1;
    printPoint2("p1 =", p1);

    Point2<float> p2(1, 2);
    printPoint2("p2(1, 2) =", p2);

    printSubTitle("array[] = {3, 4};");
    float array[] = {3, 4};
    Point2<float> p3(array);
    printPoint2("p3(array) =", p3);

    // v6.4.1: the name is v (it read v1)
    printSubTitle(F("Vector2<float> v(1, 2);"));
    Vector2<float> v(1, 2);
    printVector2("v(1, 2) =", v);
    Point2<float> p4(v);
    printPoint2("p4(v) =", p4);

    // Getters and setters (v6.3.0). x() and y() read a coordinate,
    // Element(0) and Element(1) read it by index, and x(value) and
    // y(value) write it. One name serves the getter and the setter; an
    // argument selects the setter (overload resolution).
    printSubTitle(F("Getters: p2.x(), p2.y(), p2.Element(1)"));
    Serial.print(F("p2.x() "));
    Serial.println(p2.x());
    Serial.print(F("p2.y() "));
    Serial.println(p2.y());
    Serial.print(F("p2.Element(1) "));
    Serial.println(p2.Element(1));
    printSubTitle(F("Setters: p1.x(5); p1.y(-3);"));
    p1.x(5);
    p1.y(-3);
    printPoint2("p1 =", p1);
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    Point2_T01_Constructor();
#endif
#if TOPIC == 0 || TOPIC == 2
    Point2_T02_GetPoint();
#endif
#if TOPIC == 0 || TOPIC == 3
    Point2_T03_VectorFromPointPointSubtraction();
#endif
#if TOPIC == 0 || TOPIC == 4
    Point2_T04_PointFromPointVectorAddition();
#endif
}

void Loop()
{
}
// namespace L08_Point2
}

// Lesson_L08_Point2_h
#endif
