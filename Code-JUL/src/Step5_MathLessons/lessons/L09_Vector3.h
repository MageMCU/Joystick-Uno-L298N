//
// Carpenter Software
// File: L09_Vector3.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L09_Vector3, selected with LESSON 9 in Step5_MathLessons/main.cpp
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestVector3.h (merged 20261008)
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
//   2026-10-30  v7.3.0
//   L09_Vector3.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

// TEACHING NOTES (v6.1.1)
// Lesson 9: vectors in space. The terms shared with the plane are
// defined in include/numerics/Vector2.h; the cross product and the right
// hand rule are explained in include/numerics/Vector3.h.
// Most topics use v1 = (1, 2, 3) and v2 = (4, 5, 6):
//   |v1| = sqrt(14) = 3.74       v1 . v2 = 4 + 10 + 18 = 32
//   angle = acos(32 / (3.74 x 8.77)) = 12.93 degrees
//   v1 x v2 = (2 (6) - 3 (5), 3 (4) - 1 (6), 1 (5) - 2 (4)) = (-3, 6, -3)
// The topics run T01 to T16 (see Setup()).
#ifndef Lesson_L09_Vector3_h
#define Lesson_L09_Vector3_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 16

#include <Arduino.h>
#include "Debug.h"

namespace L09_Vector3
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// T16: v2 = v1 copies the three components, (1.00, 2.00, 3.00).
// ---------------------------------------------------------------
// Vector3_T16_Copy (teaching notes, v6.3.0)
// Hint: Copy, a second vector with the same components.
// Purpose: the copy constructor (declaration) and the copy assignment
// operator (assignment), as in lesson 7, T17.
// What is learnt:
//   Vector3<float> v2 = v1;  builds v2 with the copy constructor.
//   v3 = v1;                 overwrites the existing v3 with operator=.
//   Both are written by the compiler and copy every member; for a class of
//   plain values this copy is always correct. The first subtitle is from
//   the original test and is too cautious.
// Expected output:
//   v2 = v1 (1.00, 2.00, 3.00)
//   v3 = v1 (1.00, 2.00, 3.00)
// ---------------------------------------------------------------
void Vector3_T16_Copy()
{
    printTitle(F("Vector3 T16 Copy using the equal sign"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);

    printSubTitle("v2 = v1; does not always work unless using an operator=");
    Vector3<float> v2 = v1;
    printVector3("v2 = v1", v2);

    // v6.3.0: the line above is a declaration, so v2 is built by the copy
    // constructor, not by operator=. Vector3 declares neither; the
    // compiler writes both, and each copies m_x, m_y, and m_z, which is
    // always correct for a class of plain values. The assignment below,
    // into a vector that already exists, uses operator=.
    printSubTitle(F("Declaration: copy constructor. Assignment: operator="));
    Vector3<float> v3;
    v3 = v1;
    printVector3("v3 = v1", v3);
}

// T15: v1 x v2 = (-3, 6, -3) is perpendicular to both: its dot product
// with v1 and with v2 is 0.00.
// ---------------------------------------------------------------
// Vector3_T15_CrossPerpendicular (teaching notes, v6.3.0)
// Hint: CrossPerpendicular, the cross product is perpendicular to both.
// Purpose: to verify the main property of the cross product with the
// dot product test.
// What is learnt:
//   (v1 x v2) . v1 = 0 and (v1 x v2) . v2 = 0 for any v1 and v2.
//   A property test: check a known law instead of one known answer.
// Expected output:
//   v3 = v1 ^ v2 (-3.00, 6.00, -3.00)
//   dot1 = v1 * v3 0.00
//   dot2 = v2 * v3 0.00
// ---------------------------------------------------------------
void Vector3_T15_CrossPerpendicular()
{
    printTitle(F("Vector3 T15 Cross Product is perpendicular"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);

    Vector3<float> v2(4, 5, 6);
    printVector3("v2", v2);

    Vector3<float> v3 = v1 ^ v2;
    printVector3("v3 = v1 ^ v2", v3);

    printSubTitle("Test for perpendicularity");

    float dot1 = v1 * v3;
    Serial.print("dot1 = v1 * v3 ");
    Serial.println(dot1);

    float dot2 = v2 * v3;
    Serial.print("dot2 = v2 * v3 ");
    Serial.println(dot2);
}

// T14: v1 * v2 with two vectors is the dot product, 32.00.
// ---------------------------------------------------------------
// Vector3_T14_DotOperator (teaching notes, v6.3.0)
// Hint: DotOperator, the dot product written with *.
// Purpose: the two meanings of * for Vector3, chosen by the right operand.
// What is learnt:
//   v * s (a scalar) returns a Vector3; v * u (a vector) returns a scalar.
//   The compiler selects the overload by the type of the argument.
// Expected output:
//   dot = v1 * v2 32.00
// ---------------------------------------------------------------
void Vector3_T14_DotOperator()
{
    printTitle(F("Vector3 T14 Dot Product with operator*"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);

    Vector3<float> v2(4, 5, 6);
    printVector3("v2", v2);

    float dot = v1 * v2;
    Serial.print("dot = v1 * v2 ");
    Serial.println(dot);
}

// T13: v1 - v2 = (-3.00, -3.00, -3.00).
// ---------------------------------------------------------------
// Vector3_T13_VectorVectorSubtraction (teaching notes, v6.3.0)
// Hint: VectorVectorSubtraction, subtract two vectors.
// Purpose: v1 - v2, the step from the tip of v2 to the tip of v1.
// What is learnt:
//   Each component subtracts: (1 - 4, 2 - 5, 3 - 6).
// Expected output:
//   v3 = v1 - v2 (-3.00, -3.00, -3.00)
// ---------------------------------------------------------------
void Vector3_T13_VectorVectorSubtraction()
{
    printTitle(F("Vector3 T13 Vector Vector Subtraction"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);

    Vector3<float> v2(4, 5, 6);
    printVector3("v2", v2);

    Vector3<float> v3 = v1 - v2;
    printVector3("v3 = v1 - v2", v3);
}

// T12: v1 + v2 = (5.00, 7.00, 9.00).
// ---------------------------------------------------------------
// Vector3_T12_VectorVectorAddition (teaching notes, v6.3.0)
// Hint: VectorVectorAddition, add two vectors.
// Purpose: component by component addition in space.
// What is learnt:
//   v1 + v2 calls v1.operator+(v2); tip to tail, as in 2D.
// Expected output:
//   v3 = v1 + v2 (5.00, 7.00, 9.00)
// ---------------------------------------------------------------
void Vector3_T12_VectorVectorAddition()
{
    printTitle(F("Vector3 T12 Vector Vector Addition"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);

    Vector3<float> v2(4, 5, 6);
    printVector3("v2", v2);

    Vector3<float> v3 = v1 + v2;
    printVector3("v3 = v1 + v2", v3);
}

// T11: v1 * 3 = (3.00, 6.00, 9.00).
// ---------------------------------------------------------------
// Vector3_T11_VectorScalarProduct (teaching notes, v6.3.0)
// Hint: VectorScalarProduct, scale a vector by a number.
// Purpose: v * s multiplies each component by s.
// What is learnt:
//   printResult() prints the scalar with 2 decimals.
//   Only v * s is defined in this class; s * v is not.
// Expected output:
//   scalar: 3.00
//   v2 = v1 * scalar (3.00, 6.00, 9.00)
// ---------------------------------------------------------------
void Vector3_T11_VectorScalarProduct()
{
    printTitle(F("Vector3 T11 Vector Scalar Product"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);

    float scalar = 3;
    printResult("scalar: ", scalar);

    Vector3<float> v2 = v1 * scalar;
    printVector3("v2 = v1 * scalar", v2);
}

// T10: -v1 = (-1.00, -2.00, -3.00).
// ---------------------------------------------------------------
// Vector3_T10_NegateVector (teaching notes, v6.3.0)
// Hint: NegateVector, the unary minus.
// Purpose: -v, the opposite direction with the same length.
// What is learnt:
//   operator-() without a parameter is the negation; operator-(v) with one
//   is the subtraction of T13.
// Expected output:
//   v2 = -v1 (-1.00, -2.00, -3.00)
// ---------------------------------------------------------------
void Vector3_T10_NegateVector()
{
    printTitle(F("Vector3 T10 Negate Vector"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);

    Vector3<float> v2 = -v1;
    printVector3("v2 = -v1", v2);
}

// T09: the projection of v1 onto v2 is v2 (32 / 77) = (1.66, 2.08, 2.49),
// along v2.
// ---------------------------------------------------------------
// Vector3_T09_ProjV (teaching notes, v6.3.0)
// Hint: ProjV, project one vector onto another.
// Purpose: the part of v1 along v2: v2 (v1 . v2) / (v2 . v2).
// What is learnt:
//   Check: (4, 5, 6) x 32 / 77 = (1.66, 2.08, 2.49).
//   The projection is parallel to v2: angle 0, unit vector dot product 1.
//   Use: the component of a force or a velocity along a chosen direction.
// Expected output:
//   v3 = v1.ProjV(v2) (1.66, 2.08, 2.49)
//   angle = v1.Angle(v2) * RAD_TO_DEG 12.93
//   angle = v1.Angle(v3) * RAD_TO_DEG 12.93
//   angle = v2.Angle(v3) * RAD_TO_DEG 0.00
//    dot = v2.Normalize() * v3.Normalize() 1.00
// ---------------------------------------------------------------
void Vector3_T09_ProjV()
{
    printTitle(F("Vector3 T09 Project v1 onto v2"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);

    Vector3<float> v2(4, 5, 6);
    printVector3("v2", v2);

    Vector3<float> v3 = v1.ProjV(v2);
    printVector3("v3 = v1.ProjV(v2)", v3);

    float angle = v1.Angle(v2) * RAD_TO_DEG;
    Serial.print("angle = v1.Angle(v2) * RAD_TO_DEG ");
    Serial.println(angle);

    angle = v1.Angle(v3) * RAD_TO_DEG;
    Serial.print("angle = v1.Angle(v3) * RAD_TO_DEG ");
    Serial.println(angle);

    printSubTitle("Zero Degrees");
    angle = v2.Angle(v3) * RAD_TO_DEG;
    Serial.print("angle = v2.Angle(v3) * RAD_TO_DEG ");
    Serial.println(angle);

    printSubTitle("Normalized v2 & v3 have identical directions if dot is ONE");
    float dot = v2.Normalize() * v3.Normalize();
    Serial.print(" dot = v2.Normalize() * v3.Normalize() ");
    Serial.println(dot);
}

// T08: the x axis (1, 0, 0) and the vector (0, 0, -1) meet at 90.00
// degrees (their dot product is 0). The angle between v1 and v2,
// 12.93 degrees, is printed in T09.
// ---------------------------------------------------------------
// Vector3_T08_Angle (teaching notes, v6.3.0)
// Hint: Angle, the angle between two vectors in space.
// Purpose: acos(u . v / (|u| |v|)), as in 2D.
// What is learnt:
//   Two axis directions, x and minus z, are perpendicular: the dot
//   product is 0 and acos(0) = 90 degrees.
//   In 3D the angle has no sign: there is no single clockwise direction
//   without a reference axis.
// Expected output:
//   angle = v1.Angle(v2) * RAD_TO_DEG 90.00
// ---------------------------------------------------------------
void Vector3_T08_Angle()
{
    printTitle(F("Vector3 T08 Angle"));

    Vector3<float> v1(1, 0, 0);
    printVector3("v1", v1);

    Vector3<float> v2(0, 0, -1);
    printVector3("v2", v2);

    float angle = v1.Angle(v2) * RAD_TO_DEG;
    Serial.print("angle = v1.Angle(v2) * RAD_TO_DEG ");
    Serial.println(angle);
}

// T07: v1 x v2 = (-3, 6, -3), of length sqrt(54) = 7.35; UnitCross()
// gives (-0.41, 0.82, -0.41), the same as normalizing the cross product.
// ---------------------------------------------------------------
// Vector3_T07_UnitCross (teaching notes, v6.3.0)
// Hint: UnitCross, the cross product scaled to length 1.
// Purpose: the unit normal, the direction perpendicular to the plane of
// two vectors.
// What is learnt:
//   UnitCross(v) = Cross(v).Normalize(): one call in place of two.
//   Normal         a vector perpendicular to a surface; the unit normal is
//                  used for lighting and collisions in a simulation.
//   Check: (-3, 6, -3) / sqrt(54) = (-0.41, 0.82, -0.41).
// Expected output:
//   v3 = v1.Cross(v2) (-3.00, 6.00, -3.00)
//   v4 = v1.UnitCross(v2) (-0.41, 0.82, -0.41)
//   v5 = v3.Normalize() (-0.41, 0.82, -0.41)
//   v5.Magnitude() 1.00
// ---------------------------------------------------------------
void Vector3_T07_UnitCross()
{
    printTitle(F("Vector3 T07 UnitCross Product"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);

    Vector3<float> v2(4, 5, 6);
    printVector3("v2", v2);

    Vector3<float> v3 = v1.Cross(v2);
    printVector3("v3 = v1.Cross(v2)", v3);

    Vector3<float> v4 = v1.UnitCross(v2);
    printVector3("v4 = v1.UnitCross(v2)", v4);

    Vector3<float> v5 = v3.Normalize();
    printVector3("v5 = v3.Normalize()", v5);

    float mag = v5.Magnitude();
    printResult("v5.Magnitude() ", mag);
}

// T06: the x axis cross the y axis is the z axis, (0.00, 0.00, 1.00),
// with Cross() and with the operator ^.
// ---------------------------------------------------------------
// Vector3_T06_CrossProduct (teaching notes, v6.3.0)
// Hint: CrossProduct, the vector product, which exists only in 3D.
// Purpose: u x v, a vector perpendicular to both u and v.
// What is learnt:
//   Cross product  (y1 z2 - z1 y2, z1 x2 - x1 z2, x1 y2 - y1 x2); its
//                  length is |u| |v| sin(angle).
//   Right hand rule  point the fingers along u, curl them toward v; the
//                  thumb shows the direction of u x v. x cross y is z.
//   operator^      Vector3 uses ^ as the cross product symbol. In C++, ^
//                  is the exclusive OR of integers; overloading gives it a
//                  new meaning for this class. Its precedence stays low, so
//                  write (v1 ^ v2) in parentheses inside larger
//                  expressions.
//   Order matters: v2 ^ v1 = -(v1 ^ v2).
// Expected output:
//   v3 = v1.Cross(v2) (0.00, 0.00, 1.00)
//   v4 = v1 ^ v2 (0.00, 0.00, 1.00)
// ---------------------------------------------------------------
void Vector3_T06_CrossProduct()
{
    printTitle(F("Vector3 T06 Cross Product"));

    Vector3<float> v1(1, 0, 0);
    printVector3("v1", v1);

    Vector3<float> v2(0, 1, 0);
    printVector3("v2", v2);

    Vector3<float> v3 = v1.Cross(v2);
    printVector3("v3 = v1.Cross(v2)", v3);

    Vector3<float> v4 = v1 ^ v2;
    printVector3("v4 = v1 ^ v2", v4);
}

// T05: Dot() and the operator * give 32.00.
// ---------------------------------------------------------------
// Vector3_T05_DotProduct (teaching notes, v6.3.0)
// Hint: DotProduct, the scalar product in space.
// Purpose: u . v = x1 x2 + y1 y2 + z1 z2.
// What is learnt:
//   The same meaning as in 2D: |u| |v| cos(angle); 0 means perpendicular.
//   Dot() and operator* give the same number.
//   Check: 4 + 10 + 18 = 32.
// Expected output:
//   dot = v1.Dot(v2) 32.00
//   dot = v1 * v2 32.00
// ---------------------------------------------------------------
void Vector3_T05_DotProduct()
{
    printTitle(F("Vector3 T05 Dot Product"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);

    Vector3<float> v2(4, 5, 6);
    printVector3("v2", v2);

    float dot = v1.Dot(v2);
    Serial.print("dot = v1.Dot(v2) ");
    Serial.println(dot);

    dot = v1 * v2;
    Serial.print("dot = v1 * v2 ");
    Serial.println(dot);
}

// T04: the unit vector of v1 is (0.27, 0.53, 0.80), of length 1.00.
// ---------------------------------------------------------------
// Vector3_T04_UnitVectorNormalize (teaching notes, v6.3.0)
// Hint: UnitVectorNormalize, scale the vector to length 1.
// Purpose: keep only the direction of v1.
// What is learnt:
//   v / |v| = (1, 2, 3) / 3.74 = (0.27, 0.53, 0.80).
//   UnitVector() and Normalize() are the same function; a zero vector
//   gives the zero vector instead of a division by zero.
// Expected output:
//   v2 = v1.UnitVector (0.27, 0.53, 0.80)   magnitude = v2.Magnitude 1.00
//   v3 = v1.Normalize (0.27, 0.53, 0.80)    distance = v3.Distance 1.00
// ---------------------------------------------------------------
void Vector3_T04_UnitVectorNormalize()
{
    printTitle(F("Vector3 T04 UnitVector & Normalize"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);

    Vector3<float> v2 = v1.UnitVector();
    printVector3("v2 = v1.UnitVector", v2);

    float magnitude = v2.Magnitude();
    Serial.print("magnitude = v2.Magnitude ");
    Serial.println(magnitude);

    Vector3<float> v3 = v1.Normalize();
    printVector3("v3 = v1.Normalize", v3);

    float distance = v3.Distance();
    Serial.print("distance = v3.Distance ");
    Serial.println(distance);
}

// T03: |v1| = sqrt(1 + 4 + 9) = 3.74.
// ---------------------------------------------------------------
// Vector3_T03_MagnitudeDistance (teaching notes, v6.3.0)
// Hint: MagnitudeDistance, the length of a vector in space.
// Purpose: |v| = sqrt(x^2 + y^2 + z^2), Pythagoras applied twice.
// What is learnt:
//   The 2D formula gains one term for each extra axis.
//   Distance() is another name for Magnitude().
//   Check: sqrt(1 + 4 + 9) = sqrt(14) = 3.74.
// Expected output:
//   magnitude 3.74
//   distance 3.74
// ---------------------------------------------------------------
void Vector3_T03_MagnitudeDistance()
{
    printTitle(F("Vector3 T03 Magnitude & Distance"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);

    float magnitude = v1.Magnitude();
    Serial.print("magnitude ");
    Serial.println(magnitude);

    float distance = v1.Distance();
    Serial.print("distance ");
    Serial.println(distance);
}

// T02: GetVector() returns a copy, (1.00, 2.00, 3.00).
// ---------------------------------------------------------------
// Vector3_T02_GetVector (teaching notes, v6.3.0)
// Hint: GetVector, return a copy of the whole vector.
// Purpose: a member function that returns a new, separate object.
// What is learnt:
//   Return by value: v2 holds its own components; a change to v2 leaves
//   v1 unchanged. Inside the class, Angle() and ProjV() call GetVector()
//   to work on a copy of the object itself.
// Expected output:
//   v2 = v1.GetVector (1.00, 2.00, 3.00)
// ---------------------------------------------------------------
void Vector3_T02_GetVector()
{
    printTitle(F("Vector3 T02 GetVector"));

    Vector3<float> v1(1, 2, 3);
    printVector3("v1", v1);
    Vector3<float> v2 = v1.GetVector();
    printVector3("v2 = v1.GetVector", v2);
}

// T01: the default is the zero vector; (1, 2, 3) sets the components;
// a float array {4, 5, 6} fills them in order x, y, z.
// ---------------------------------------------------------------
// Vector3_T01_Constructor (teaching notes, v6.3.0)
// Hint: Constructor, build a vector in space.
// Purpose: how to declare and instantiate Vector3 variables, and how to
// read and write their three components.
// What is learnt:
//   Declaration and instantiation as in lesson 7, with a third component:
//     Vector3<float> v1;             default, the zero vector (0, 0, 0)
//     Vector3<float> v2(1, 2, 3);    from three values
//     Vector3<float> v3(array);      from an array, in the order x, y, z
//   Default constructor without parentheses: Vector3<float> v1(); would
//                  declare a function returning a Vector3 (the most vexing
//                  parse), which is why the subtitle says no parenthesis.
//   Getters        v2.x(), v2.y(), v2.z(), v3.Element(2) (index 0 to 2).
//   Setters        v1.x(7), v1.y(8), v1.z(9).
// Expected output:
//   Vector3<float> v1 (0.00, 0.00, 0.00)
//   Vector3<float> v2(1, 2, 3) (1.00, 2.00, 3.00)
//   Vector3<float> v3(array) (4.00, 5.00, 6.00)
//   v2.x() 1.00   v2.y() 2.00   v2.z() 3.00   v3.Element(2) 6.00
//   v1 (7.00, 8.00, 9.00)   (after the setters)
// ---------------------------------------------------------------
void Vector3_T01_Constructor()
{
    printTitle(F("Vector3 T01 Constructor"));
    printSubTitle("Notice no parenthesis used in the default constructor.");

    Vector3<float> v1;
    printVector3("Vector3<float> v1", v1);

    Vector3<float> v2(1, 2, 3);
    printVector3("Vector3<float> v2(1, 2, 3)", v2);

    printSubTitle("float array[] = {4, 5, 6};");
    float array[] = {4, 5, 6};
    Vector3<float> v3(array);
    printVector3("Vector3<float> v3(array)", v3);

    // Getters and setters (v6.3.0). x(), y(), z() and Element(index)
    // read a component; x(value), y(value), z(value) write one. One
    // name serves the getter and the setter; an argument selects the
    // setter (overload resolution).
    printSubTitle(F("Getters: v2.x(), v2.y(), v2.z(), v3.Element(2)"));
    Serial.print(F("v2.x() "));
    Serial.println(v2.x());
    Serial.print(F("v2.y() "));
    Serial.println(v2.y());
    Serial.print(F("v2.z() "));
    Serial.println(v2.z());
    Serial.print(F("v3.Element(2) "));
    Serial.println(v3.Element(2));
    printSubTitle(F("Setters: v1.x(7); v1.y(8); v1.z(9);"));
    v1.x(7);
    v1.y(8);
    v1.z(9);
    printVector3("v1", v1);
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    Vector3_T01_Constructor();
#endif
#if TOPIC == 0 || TOPIC == 2
    Vector3_T02_GetVector();
#endif
#if TOPIC == 0 || TOPIC == 3
    Vector3_T03_MagnitudeDistance();
#endif
#if TOPIC == 0 || TOPIC == 4
    Vector3_T04_UnitVectorNormalize();
#endif
#if TOPIC == 0 || TOPIC == 5
    Vector3_T05_DotProduct();
#endif
#if TOPIC == 0 || TOPIC == 6
    Vector3_T06_CrossProduct();
#endif
#if TOPIC == 0 || TOPIC == 7
    Vector3_T07_UnitCross();
#endif
#if TOPIC == 0 || TOPIC == 8
    Vector3_T08_Angle();
#endif
#if TOPIC == 0 || TOPIC == 9
    Vector3_T09_ProjV();
#endif
#if TOPIC == 0 || TOPIC == 10
    Vector3_T10_NegateVector();
#endif
#if TOPIC == 0 || TOPIC == 11
    Vector3_T11_VectorScalarProduct();
#endif
#if TOPIC == 0 || TOPIC == 12
    Vector3_T12_VectorVectorAddition();
#endif
#if TOPIC == 0 || TOPIC == 13
    Vector3_T13_VectorVectorSubtraction();
#endif
#if TOPIC == 0 || TOPIC == 14
    Vector3_T14_DotOperator();
#endif
#if TOPIC == 0 || TOPIC == 15
    Vector3_T15_CrossPerpendicular();
#endif
#if TOPIC == 0 || TOPIC == 16
    Vector3_T16_Copy();
#endif
}

void Loop()
{
}
// namespace L09_Vector3
}

// Lesson_L09_Vector3_h
#endif
