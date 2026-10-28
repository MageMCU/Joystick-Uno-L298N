//
// Carpenter Software
// File: L10_Point3.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L10_Point3, selected with LESSON 10 in Step5_MathLessons/main.cpp
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestPoint3.h (merged 20261008)
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
// Lesson 10: points and vectors in space, the 3D form of lesson 8 (the
// rules are in include/numerics/Point2.h and Point3.h).
// The topics run T01 to T04 (see Setup()).
#ifndef Lesson_L10_Point3_h
#define Lesson_L10_Point3_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 4

#include <Arduino.h>
#include "Debug.h"

namespace L10_Point3
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// T04: the point (8, -4, 21) moved by the vector (6, 2, -10) is
// (14.00, -2.00, 11.00).
// ---------------------------------------------------------------
// Point3_T04_PointFromPointVectorAddition (teaching notes, v6.3.0)
// Hint: PointFromPointVectorAddition, point plus vector gives a point.
// Purpose: move a point in space by a step.
// What is learnt:
//   operator+(Vector3) returns a Point3. In a simulation, position +
//   velocity x time step = the next position uses exactly this rule.
//   Check: (8 + 6, -4 + 2, 21 - 10) = (14, -2, 11).
// Expected output:
//   p2 = p1 + v = (14.00, -2.00, 11.00)
// ---------------------------------------------------------------
void Point3_T04_PointFromPointVectorAddition()
{
    printTitle(F("Point3 T04 Point from Point Vector Addition"));

    Point3<float> p1(8, -4, 21);
    printPoint3("p1(8, -4, 21) =", p1);

    Vector3<float> v(6, 2, -10);
    printVector3("v(6, 2, -10) =", v);

    printSubTitle("Point = Point + Vector");

    Point3<float> p2 = p1 + v;
    printPoint3("p2 = p1 + v =", p2);
}

// T03: from (2, 7, 6) to (8, -4, 12) the step is (6.00, -11.00, 6.00).
// ---------------------------------------------------------------
// Point3_T03_VectorFromPointPointSubtraction (teaching notes, v6.3.0)
// Hint: VectorFromPointPointSubtraction, point minus point gives a
// vector.
// Purpose: the displacement from p2 to p1 in space.
// What is learnt:
//   operator-(Point3) returns a Vector3: the difference of two locations
//   is a step, not a location.
//   Check: (8 - 2, -4 - 7, 12 - 6) = (6, -11, 6).
// Expected output:
//   v = p1 - p2 = (6.00, -11.00, 6.00)
// ---------------------------------------------------------------
void Point3_T03_VectorFromPointPointSubtraction()
{
    printTitle(F("Point3 T03 Vector from Point Point Subtraction"));

    Point3<float> p1(8, -4, 12);
    printPoint3("p1(8, -4, 12) =", p1);

    Point3<float> p2(2, 7, 6);
    printPoint3("p2(2, 7, 6) =", p2);

    printSubTitle("Vector = Point - Point");

    Vector3<float> v = p1 - p2;
    printVector3("v = p1 - p2 =", v);
}

// T02: GetPoint() returns a copy, (3.00, 7.00, 4.00).
// ---------------------------------------------------------------
// Point3_T02_GetPoint (teaching notes, v6.3.0)
// Hint: GetPoint, return a copy of the point.
// Purpose: a member function that returns a new, separate object.
// What is learnt:
//   p2 holds its own coordinates; the same as Point3<float> p2 = p1;
//   through the compiler written copy constructor.
// Expected output:
//   p1 (3.00, 7.00, 4.00)
//   p2 (3.00, 7.00, 4.00)
// ---------------------------------------------------------------
void Point3_T02_GetPoint()
{
    printTitle(F("Point3 T02 GetPoint"));

    Point3<float> p1(3, 7, 4);
    printPoint3("p1", p1);

    Point3<float> p2 = p1.GetPoint();
    printPoint3("p2", p2);
}

// ---------------------------------------------------------------
// Point3_T01_Constructor (teaching notes, v6.3.0)
// Hint: Constructor, build a point in space.
// Purpose: how to declare and instantiate Point3 variables, the four
// constructors, and the getters and setters of the coordinates.
// What is learnt:
//   Point3 is the 3D form of Point2 (lesson 8): a location (x, y, z).
//   Four constructors (overloads):
//     Point3<float> p1;              default, the origin (0, 0, 0)
//     Point3<float> p2(1, 2, 3);     from three values
//     Point3<float> p3(array);       from an array, in the order x, y, z
//     Point3<float> p4(v);           the point reached by the step v from
//                                    the origin
//   Getters        p2.x(), p2.y(), p2.z(), p3.Element(2).
//   Setters        p1.x(5), p1.y(-3), p1.z(2).
// Expected output:
//   p1 = (0.00, 0.00, 0.00)   p2(1, 2, 3) = (1.00, 2.00, 3.00)
//   p3(array) = (4.00, 5.00, 6.00)   p4(v) = (1.00, 2.00, 3.00)
//   p2.x() 1.00   p2.y() 2.00   p2.z() 3.00   p3.Element(2) 6.00
//   p1 = (5.00, -3.00, 2.00)   (after the setters)
// ---------------------------------------------------------------
void Point3_T01_Constructor()
{
    printTitle(F("Point3 T01 Constructor"));

    Point3<float> p1;
    printPoint3("p1 =", p1);

    Point3<float> p2(1, 2, 3);
    printPoint3("p2(1, 2, 3) =", p2);

    printSubTitle("array[] = {4, 5, 6};");
    float array[] = {4, 5, 6};
    Point3<float> p3(array);
    printPoint3("p3(array) =", p3);

    Vector3<float> v(1, 2, 3);
    printVector3("v(1, 2, 3) =", v);
    Point3<float> p4(v);
    printPoint3("p4(v) =", p4);

    // Getters and setters (v6.3.0). x(), y(), z() and Element(index)
    // read a coordinate; x(value), y(value), z(value) write one. One name
    // serves the getter and the setter; an argument selects the setter
    // (overload resolution).
    printSubTitle(F("Getters: p2.x(), p2.y(), p2.z(), p3.Element(2)"));
    Serial.print(F("p2.x() "));
    Serial.println(p2.x());
    Serial.print(F("p2.y() "));
    Serial.println(p2.y());
    Serial.print(F("p2.z() "));
    Serial.println(p2.z());
    Serial.print(F("p3.Element(2) "));
    Serial.println(p3.Element(2));
    printSubTitle(F("Setters: p1.x(5); p1.y(-3); p1.z(2);"));
    p1.x(5);
    p1.y(-3);
    p1.z(2);
    printPoint3("p1 =", p1);
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    Point3_T01_Constructor();
#endif
#if TOPIC == 0 || TOPIC == 2
    Point3_T02_GetPoint();
#endif
#if TOPIC == 0 || TOPIC == 3
    Point3_T03_VectorFromPointPointSubtraction();
#endif
#if TOPIC == 0 || TOPIC == 4
    Point3_T04_PointFromPointVectorAddition();
#endif
}

void Loop()
{
}
// namespace L10_Point3
}

// Lesson_L10_Point3_h
#endif
