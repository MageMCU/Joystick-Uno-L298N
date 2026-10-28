//
// Carpenter Software
// File: L07_Vector2.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L07_Vector2, selected with LESSON 7 in Step5_MathLessons/main.cpp
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestVector2.h (merged 20261008)
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
//   L07_Vector2.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

// TEACHING NOTES (v6.1.1)
// Lesson 7: vectors in the plane. Every term used here (component,
// magnitude, unit vector, dot product, angle, perpendicular, perp dot
// product, projection, the operators) is defined at the top of
// include/numerics/Vector2.h; read it first.
// Most topics use the same two vectors, v1 = (1, 2) and v2 = (3, 4), so
// each result can be checked by hand:
//   |v1| = sqrt(5) = 2.24        v1 . v2 = 3 + 8 = 11
//   angle = acos(11 / (2.24 x 5)) = 10.30 degrees
//   v1 x v2 (z part) = 1 (4) - 2 (3) = -2: v2 lies clockwise from v1
// Why it matters: a joystick reading is a 2D vector (lesson 19), and the
// robot's direction on the floor is one too.
// The topics run T01 to T17 (see Setup()).
#ifndef Lesson_L07_Vector2_h
#define Lesson_L07_Vector2_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 17

#include <Arduino.h>
#include "Debug.h"

namespace L07_Vector2
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// T17: v2 = v1 copies the two components; v2 prints (1.00, 2.00).
// ---------------------------------------------------------------
// Vector2_T17_Copy (teaching notes, v6.3.0)
// Hint: Copy, make a second vector with the same components.
// Purpose: the two ways C++ copies an object: in a declaration and in an
// assignment.
// What is learnt:
//   Copy constructor  Vector2<float> v2 = v1; builds the new object v2
//                  from v1. The = in a declaration is not an assignment.
//   Copy assignment operator  v3 = v1; with v3 already built, operator=
//                  overwrites its components.
//   Implicit members  the class declares neither; the compiler writes
//                  both, copying each member. That is correct for a class
//                  that holds only values, as Vector2 does. A class that
//                  owns memory through a pointer would need its own
//                  versions (the rule of three).
//   The first subtitle printed by this topic is from the original test
//   and is too cautious: for Vector2 the copy always works.
// Expected output:
//   v1 (1.00, 2.00)
//   v2 (1.00, 2.00)
//   v3 (1.00, 2.00)
// ---------------------------------------------------------------
void Vector2_T17_Copy()
{
    printTitle(F("Vector2 T17 Copy using the equal sign"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    printSubTitle("This does not always work unless using an operator=");
    Vector2<float> v2 = v1;
    printVector2("v2", v2);

    // v6.3.0: the line above is a declaration, so v2 is built by the copy
    // constructor, not by operator=. Vector2 declares neither; the
    // compiler writes both, and each copies m_x and m_y. For a class of
    // plain values (no pointers) that copy is always correct. The
    // assignment below, into a vector that already exists, uses the
    // copy assignment operator, operator=.
    printSubTitle(F("Declaration: copy constructor. Assignment: operator="));
    Vector2<float> v3;
    v3 = v1;
    printVector2("v3", v3);
}

// T16: v1 * v2 with two vectors is the dot product: 11.00.
// ---------------------------------------------------------------
// Vector2_T16_DotOperator (teaching notes, v6.3.0)
// Hint: DotOperator, the dot product written with the * symbol.
// Purpose: operator overloading: one symbol, two meanings chosen by the
// type of the right operand.
// What is learnt:
//   v1 * 3.0       a vector times a scalar gives a vector (T13).
//   v1 * v2        a vector times a vector gives a scalar, the dot
//                  product (T05).
//   The return type differs: Vector2<real> for the first, real for the
//   second; float dot = v1 * v2; stores a number.
// Expected output:
//   dot = v1 * v2 11.00
// ---------------------------------------------------------------
void Vector2_T16_DotOperator()
{
    printTitle(F("Vector2 T16 Dot Product with operator*"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    float dot = v1 * v2;
    Serial.print("dot = v1 * v2 ");
    Serial.println(dot);
}

// T15: v1 - v2 = (1 - 3, 2 - 4) = (-2.00, -2.00).
// ---------------------------------------------------------------
// Vector2_T15_VectorVectorSubtraction (teaching notes, v6.3.0)
// Hint: VectorVectorSubtraction, subtract two vectors.
// Purpose: u - v = (x1 - x2, y1 - y2).
// What is learnt:
//   Difference vector  v1 - v2 points from the tip of v2 to the tip of
//                  v1; for two positions it is the step from one to the
//                  other, and its magnitude is their distance apart.
// Expected output:
//   v3 = v1 - v2 (-2.00, -2.00)
// ---------------------------------------------------------------
void Vector2_T15_VectorVectorSubtraction()
{
    printTitle(F("Vector2 T15 Vector Vector Subtraction"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    Vector2<float> v3 = v1 - v2;
    printVector2("v3 = v1 - v2", v3);
}

// T14: v1 + v2 = (4.00, 6.00).
// ---------------------------------------------------------------
// Vector2_T14_VectorVectorAddition (teaching notes, v6.3.0)
// Hint: VectorVectorAddition, add two vectors.
// Purpose: u + v adds component by component: (x1 + x2, y1 + y2).
// What is learnt:
//   Binary operator  an operator with two operands; operator+(v) is a
//                  member function, so v1 + v2 calls v1.operator+(v2).
//   Geometry       place v2 at the tip of v1; the sum reaches from the
//                  start of v1 to the tip of v2.
// Expected output:
//   v3 = v1 + v2 (4.00, 6.00)
// ---------------------------------------------------------------
void Vector2_T14_VectorVectorAddition()
{
    printTitle(F("Vector2 T14 Vector Vector Addition"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    Vector2<float> v3 = v1 + v2;
    printVector2("v3 = v1 + v2", v3);
}

// T13: v1 * 3 = (3.00, 6.00): three times as long, same direction.
// ---------------------------------------------------------------
// Vector2_T13_VectorScalarProduct (teaching notes, v6.3.0)
// Hint: VectorScalarProduct, multiply a vector by a number.
// Purpose: v * s scales the length by s and keeps the direction (s > 0).
// What is learnt:
//   Scalar         a single number, here float scalar = 3.
//   operator*(real s)  multiplies each component: (1 x 3, 2 x 3).
//   Order matters in this class: v1 * scalar is defined, scalar * v1 is
//   not (it would need a free operator* outside the class).
//   v6.4.1: the scalar is printed before the product, as in lesson 9,
//   topic 11, so every input of the product appears in the output.
// Expected output:
//   v1 (1.00, 2.00)
//   scalar: 3.00
//   v2 = v1 * scalar (3.00, 6.00)
// ---------------------------------------------------------------
void Vector2_T13_VectorScalarProduct()
{
    printTitle(F("Vector2 T13 Vector Scalar Product"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    float scalar = 3;
    // v6.4.1: print the input
    printResult(F("scalar: "), scalar);

    Vector2<float> v2 = v1 * scalar;
    printVector2("v2 = v1 * scalar", v2);
}

// T12: -v1 = (-1.00, -2.00): same length, opposite direction.
// ---------------------------------------------------------------
// Vector2_T12_NegateVector (teaching notes, v6.3.0)
// Hint: NegateVector, the unary minus.
// Purpose: -v, the same length in the opposite direction.
// What is learnt:
//   Unary operator  an operator with one operand. operator-() with no
//                  parameter is the negation; operator-(v) with one
//                  parameter is the subtraction of T15. The parameter list
//                  tells the compiler which is meant.
// Expected output:
//   v2 = -v1 (-1.00, -2.00)
// ---------------------------------------------------------------
void Vector2_T12_NegateVector()
{
    printTitle(F("Vector2 T12 Negate Vector"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2 = -v1;
    printVector2("v2 = -v1", v2);
}

// T11: the projection of v1 onto v2 is v2 (11 / 25) = (1.32, 1.76). It
// points along v2, so the angle between v2 and the projection is 0 and
// the dot product of their unit vectors is 1.00; the angle from v1 is
// 10.30 degrees, as for v2.
// ---------------------------------------------------------------
// Vector2_T11_ProjV (teaching notes, v6.3.0)
// Hint: ProjV, the projection of one vector onto another.
// Purpose: the part of v1 that points along v2:
// proj = v2 (v1 . v2) / (v2 . v2).
// What is learnt:
//   Projection     a vector parallel to v2; its length is how far v1
//                  reaches along the direction of v2.
//   Check: (3, 4) x 11 / 25 = (1.32, 1.76).
//   The projection has the direction of v2, so the angle between v2 and
//   v3 is 0, and the dot product of their unit vectors is 1.
// Expected output:
//   v3 = v1.ProjV(v2) (1.32, 1.76)
//   angle = v1.Angle(v2) * RAD_TO_DEG 10.30
//   angle = v1.Angle(v3) * RAD_TO_DEG 10.30
//   angle = v2.Angle(v3) * RAD_TO_DEG 0.00
//    dot = v2.Normalize() * v3.Normalize() 1.00
// ---------------------------------------------------------------
void Vector2_T11_ProjV()
{
    printTitle(F("Vector2 T11 Project v1 onto v2"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    Vector2<float> v3 = v1.ProjV(v2);
    printVector2("v3 = v1.ProjV(v2)", v3);

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

// T10: the z component of the cross product, -2.00 (see the notes at
// the top).
// ---------------------------------------------------------------
// Vector2_T10_ZComp (teaching notes, v6.3.0)
// Hint: ZComp, the z component of the cross product.
// Purpose: a second name for the perp dot product, for readers who think
// in terms of the 3D cross product.
// What is learnt:
//   ZComp(v) gives the same number as DotPerp(v): -2.00 here.
//   Use: the sign decides the turn direction, for example whether the
//   robot must turn left (positive) or right (negative) toward a target.
// Expected output:
//   ZComp = v1.ZComp(v2) -2.00
// ---------------------------------------------------------------
void Vector2_T10_ZComp()
{
    printTitle(F("Vector2 T10 z component of a cross product"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    float ZComp = v1.ZComp(v2);
    Serial.print("ZComp = v1.ZComp(v2) ");
    Serial.println(ZComp);
}

// T09: the perp dot product of v1 and v2 is -2.00, and the cross product
// of (1, 2, 0) and (3, 4, 0) has the same z component: two ways to the
// same number.
// ---------------------------------------------------------------
// Vector2_T09_DotPerp (teaching notes, v6.3.0)
// Hint: DotPerp, the perp dot product.
// Purpose: x1 y2 - y1 x2, the 2D product whose sign tells on which side of
// u the vector v lies.
// What is learnt:
//   Perp dot product  Perp(u) . v = |u| |v| sin(angle): positive when v
//                  lies counterclockwise from u, negative when clockwise,
//                  0 when the two are parallel.
//   Link to 3D     place both vectors in the plane z = 0 and take the
//                  cross product, operator^ of Vector3 (lesson 9): its z
//                  component is the same number.
//   Check: 1 (4) - 2 (3) = -2: v2 lies clockwise from v1.
// Expected output:
//   DotPerp = v1.DotPerp(v2) -2.00
//   v3 (1.00, 2.00, 0.00)   v4 (3.00, 4.00, 0.00)
//   v5 = v3 ^ v4 (0.00, 0.00, -2.00)
//   zComponent = v5.z() -2.00
//   v6.4.1: the cross product v5 is printed in full; its x and y
//   components are 0 because v3 and v4 lie in the plane z = 0.
// ---------------------------------------------------------------
void Vector2_T09_DotPerp()
{
    printTitle(F("Vector2 T09 Dot Perpendicular Product"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    float DotPerp = v1.DotPerp(v2);
    Serial.print("DotPerp = v1.DotPerp(v2) ");
    Serial.println(DotPerp);

    Vector3<float> v3(1, 2, 0);
    printVector3("v3", v3);

    Vector3<float> v4(3, 4, 0);
    printVector3("v4", v4);

    Vector3<float> v5 = v3 ^ v4;
    // v6.4.1: print the whole result
    printVector3(F("v5 = v3 ^ v4"), v5);
    float zComponent = v5.z();
    Serial.print("zComponent = v5.z() ");
    Serial.println(zComponent);

    // v6.4.1: name of the function
    printSubTitle(F("Notice DotPerp and zComponent must be equal..."));
}

// T08: Perp(v1) = (-2.00, 1.00), length 2.24; UnitPerp(v1) =
// (-0.89, 0.45). Both dot products with v1 are 0.00: perpendicular.
// ---------------------------------------------------------------
// Vector2_T08_UnitPerp (teaching notes, v6.3.0)
// Hint: UnitPerp, the perpendicular vector of length 1.
// Purpose: to compare Perp(), which keeps the length, with UnitPerp(),
// which normalizes it.
// What is learnt:
//   UnitPerp() = Perp() / |v|: the same direction, length 1.
//   Perp() keeps the length of v1: |(-2, 1)| = 2.24.
//   Both results are perpendicular to v1: both dot products are 0.
// Expected output:
//   v2 = v1.Perp() (-2.00, 1.00)   mag = v2.Magnitude() = 2.24
//   v3 = v1.UnitPerp() (-0.89, 0.45)
//   dot = v1 * v2 = 0.00   dot = v1 * v3 = 0.00
//   (v6.4.1: the label read mag = v1 * v2 up to v6.4.0; the value is
//   v2.Magnitude(), the length of v2.)
// ---------------------------------------------------------------
void Vector2_T08_UnitPerp()
{
    printTitle(F("Vector2 T08 Unit Perpendicular"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2 = v1.Perp();
    printVector2("v2 = v1.Perp()", v2);

    float mag = v2.Magnitude();
    // v6.4.1: label of the value
    Serial.print(F("mag = v2.Magnitude() = "));
    Serial.println(mag);

    // Comparison with Perp()
    Vector2<float> v3 = v1.UnitPerp();
    printVector2("v3 = v1.UnitPerp()", v3);

    printSubTitle( \
        "The dot product of perpendicular vectors ought to be zero...");
    float dot = v1 * v2;
    Serial.print("dot = v1 * v2 = ");
    Serial.println(dot);
    // zero result
    dot = v1 * v3;
    Serial.print("dot = v1 * v3 = ");
    Serial.println(dot);
}

// T07: Perp(v1) = (-2, 1), v1 turned 90 degrees counterclockwise; its dot
// product with v1 is 0.00.
// ---------------------------------------------------------------
// Vector2_T07_Perp (teaching notes, v6.3.0)
// Hint: Perp, the perpendicular vector.
// Purpose: Perp() turns a vector 90 degrees counterclockwise: (x, y)
// becomes (-y, x).
// What is learnt:
//   Perpendicular  at 90 degrees; the test is a dot product of 0.
//   Counterclockwise  the positive direction of angles in mathematics,
//                  from the x axis toward the y axis.
//   Check: (1, 2) gives (-2, 1), and 1 (-2) + 2 (1) = 0.
// Expected output:
//   v2 = v1.Perp() (-2.00, 1.00)
//   dot = v1 * v2 0.00
// ---------------------------------------------------------------
// ----------------------- BUGFIX ok
void Vector2_T07_Perp()
{
    printTitle(F("Vector2 T07 Perpendicular"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2 = v1.Perp();
    printVector2("v2 = v1.Perp()", v2);

    printSubTitle( \
        "The dot product of perpendicular vectors ought to be zero...");
    float dot = v1 * v2;
    Serial.print("dot = v1 * v2 ");
    Serial.println(dot);
}

// T06: the angle between v1 and v2, 10.30 degrees. RAD_TO_DEG (180 / pi)
// turns the radians of Angle() into degrees.
// ---------------------------------------------------------------
// Vector2_T06_Angle (teaching notes, v6.3.0)
// Hint: Angle, the angle between two vectors.
// Purpose: angle = acos(u . v / (|u| |v|)), from the dot product.
// What is learnt:
//   acos()         the inverse cosine, returns 0 to pi radians, so the
//                  angle has no sign; the sign comes from the perp dot
//                  product (T09).
//   RAD_TO_DEG     180 / pi, an Arduino constant; radians times RAD_TO_DEG
//                  gives degrees.
//   Check: acos(11 / (2.24 x 5)) = 10.30 degrees.
// Expected output:
//   angle = v1.Angle(v2) * RAD_TO_DEG 10.30
// ---------------------------------------------------------------
void Vector2_T06_Angle()
{
    printTitle(F("Vector2 T06 Angle"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    float angle = v1.Angle(v2) * RAD_TO_DEG;
    Serial.print("angle = v1.Angle(v2) * RAD_TO_DEG ");
    Serial.println(angle);
}

// T05: Dot() and the operator * give the same result, 11.00.
// ---------------------------------------------------------------
// Vector2_T05_DotProduct (teaching notes, v6.3.0)
// Hint: DotProduct, multiply two vectors to a single number.
// Purpose: u . v = x1 x2 + y1 y2, the product that measures how much two
// vectors point the same way.
// What is learnt:
//   Dot product    a scalar: positive when the angle is under 90 degrees,
//                  0 at exactly 90, negative beyond.
//   Member function and operator: v1.Dot(v2) and v1 * v2 give the same
//                  result; operator* with a vector argument is defined to
//                  call the dot product (T16).
//   Check: 1 (3) + 2 (4) = 11.
// Expected output:
//   dot = v1.Dot(v2) 11.00
//   dot = v1 * v2 11.00
// ---------------------------------------------------------------
void Vector2_T05_DotProduct()
{
    printTitle(F("Vector2 T05 Dot Product"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    float dot = v1.Dot(v2);
    Serial.print("dot = v1.Dot(v2) ");
    Serial.println(dot);

    dot = v1 * v2;
    Serial.print("dot = v1 * v2 ");
    Serial.println(dot);
}

// T04: the unit vector of v1 is (1, 2) / 2.24 = (0.45, 0.89), of length
// 1.00; UnitVector() and Normalize() are the same function.
// ---------------------------------------------------------------
// Vector2_T04_UnitVectorNormalize (teaching notes, v6.3.0)
// Hint: UnitVectorNormalize, scale a vector to length 1.
// Purpose: to keep only the direction of a vector.
// What is learnt:
//   Unit vector    v / |v|, length 1. Normalizing a vector means dividing
//                  it by its own magnitude.
//   Alias          Normalize() and UnitVector() are the same function.
//   A zero vector has no direction; the class returns (0, 0) instead of
//   dividing by zero.
//   Check: v1 / 2.24 = (0.45, 0.89), and 0.45^2 + 0.89^2 = 1.
// Expected output:
//   v2 = v1.UnitVector (0.45, 0.89)   magnitude = v2.Magnitude 1.00
//   v3 = v1.Normalize (0.45, 0.89)    distance = v3.Distance 1.00
// ---------------------------------------------------------------
void Vector2_T04_UnitVectorNormalize()
{
    printTitle(F("Vector2 T04 UnitVector & Normalize"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2 = v1.UnitVector();
    printVector2("v2 = v1.UnitVector", v2);

    float magnitude = v2.Magnitude();
    Serial.print("magnitude = v2.Magnitude ");
    Serial.println(magnitude);

    Vector2<float> v3 = v1.Normalize();
    printVector2("v3 = v1.Normalize", v3);

    float distance = v3.Distance();
    Serial.print("distance = v3.Distance ");
    Serial.println(distance);
}

// T03: |v1| = sqrt(1 + 4) = 2.24; Distance() is the same function.
// ---------------------------------------------------------------
// Vector2_T03_MagnitudeDistance (teaching notes, v6.3.0)
// Hint: MagnitudeDistance, the length of a vector, under two names.
// Purpose: |v| = sqrt(x^2 + y^2), the theorem of Pythagoras.
// What is learnt:
//   Magnitude      the length of the vector; a scalar, so the result is a
//                  float, not a Vector2.
//   Alias          Distance() calls Magnitude(): two names for one
//                  calculation. Distance reads better for a position, the
//                  distance from the origin.
//   Check by hand: sqrt(1 + 4) = sqrt(5) = 2.24.
// Expected output:
//   v1 (1.00, 2.00)   magnitude 2.24   distance 2.24
// ---------------------------------------------------------------
void Vector2_T03_MagnitudeDistance()
{
    printTitle(F("Vector2 T03 Magnitude & Distance"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    float magnitude = v1.Magnitude();
    Serial.print("magnitude ");
    Serial.println(magnitude);

    float distance = v1.Distance();
    Serial.print("distance ");
    Serial.println(distance);
}

// T02: GetVector() returns a copy, (1.00, 2.00).
// ---------------------------------------------------------------
// Vector2_T02_GetVector (teaching notes, v6.3.0)
// Hint: GetVector, return a copy of the whole vector.
// Purpose: how a member function returns a new object.
// What is learnt:
//   Return by value  GetVector() builds a new Vector2 from m_x and m_y and
//                  returns it; v2 is a separate object, so a later change
//                  to v2 leaves v1 unchanged.
//   The same result as v2 = v1 (T17); GetVector() is used inside the
//   class, for example by Angle(), to work on a copy.
// Expected output:
//   v1 (1.00, 2.00)
//   v2 = v1.GetVector (1.00, 2.00)
// ---------------------------------------------------------------
void Vector2_T02_GetVector()
{
    printTitle(F("Vector2 T02 GetVector"));

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);
    Vector2<float> v2 = v1.GetVector();
    printVector2("v2 = v1.GetVector", v2);
}

// T01: Vector2<float> v1 is the zero vector (0, 0); v2(1, 2) sets the
// components, read back with x() and y().
// ---------------------------------------------------------------
// Vector2_T01_Constructor (teaching notes, v6.3.0)
// Hint: Constructor, the function that builds a new object.
// Purpose: how to declare and instantiate Vector2 variables, and how to
// read and write their components.
// What is learnt:
//   Declaration    Vector2<float> v1; names the variable and its type.
//                  <float> is the template argument: it selects the number
//                  type of the components (float, or double; on the Uno a
//                  double is also 32 bits).
//   Instantiation  creating the object in memory; the constructor runs at
//                  that moment and sets the components.
//   Three constructors (overloads: one name, different parameters):
//     Vector2<float> v1;          default, the zero vector (0, 0)
//     Vector2<float> v2(1, 2);    from two values
//     Vector2<float> v3(array);   from an array of two values
//   Getter (accessor)  reads a private member: v2.x(), v3.y(),
//                  v3.Element(0) (index 0 is x, 1 is y).
//   Setter (mutator)   writes a private member: v1.x(5), v1.y(6).
//   Encapsulation  m_x and m_y are private, so code outside the class
//                  reaches them only through the getters and setters.
// Expected output:
//   v1 (0.00, 0.00)   v2 (1.00, 2.00)   v2.x 1.00
//   v3 (3.00, 4.00)   v3.y 4.00         v3 element(0) 3.00
//   v1 (5.00, 6.00)   (after the setters)
// ---------------------------------------------------------------
void Vector2_T01_Constructor()
{
    printTitle(F("Vector2 T01 Constructor"));

    Vector2<float> v1;
    printVector2("v1", v1);

    // float size = v1.Size();  NOT USED
    // Serial.print("v1 size ");
    // Serial.println(size);

    Vector2<float> v2(1, 2);
    printVector2("v2", v2);

    float x = v2.x();
    Serial.print("v2.x ");
    Serial.println(x);

    printSubTitle("array[] = {3, 4};");
    float array[] = {3, 4};
    Vector2<float> v3(array);
    printVector2("v3", v3);

    float y = v3.y();
    Serial.print("v3.y ");
    Serial.println(y);

    float element = v3.Element(0);
    Serial.print("v3 element(0) ");
    Serial.println(element);

    // Setters (v6.3.0). x(value) and y(value) write the components of an
    // existing vector. The getter x() and the setter x(value) share one
    // name; the compiler picks the setter because an argument is given
    // (overload resolution).
    printSubTitle(F("Setters: v1.x(5); v1.y(6);"));
    v1.x(5);
    v1.y(6);
    printVector2("v1", v1);
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    Vector2_T01_Constructor();
#endif
#if TOPIC == 0 || TOPIC == 2
    Vector2_T02_GetVector();
#endif
#if TOPIC == 0 || TOPIC == 3
    Vector2_T03_MagnitudeDistance();
#endif
#if TOPIC == 0 || TOPIC == 4
    Vector2_T04_UnitVectorNormalize();
#endif
#if TOPIC == 0 || TOPIC == 5
    Vector2_T05_DotProduct();
#endif
#if TOPIC == 0 || TOPIC == 6
    Vector2_T06_Angle();
#endif
#if TOPIC == 0 || TOPIC == 7
    Vector2_T07_Perp();
#endif
#if TOPIC == 0 || TOPIC == 8
    Vector2_T08_UnitPerp();
#endif
#if TOPIC == 0 || TOPIC == 9
    Vector2_T09_DotPerp();
#endif
#if TOPIC == 0 || TOPIC == 10
    Vector2_T10_ZComp();
#endif
#if TOPIC == 0 || TOPIC == 11
    Vector2_T11_ProjV();
#endif
#if TOPIC == 0 || TOPIC == 12
    Vector2_T12_NegateVector();
#endif
#if TOPIC == 0 || TOPIC == 13
    Vector2_T13_VectorScalarProduct();
#endif
#if TOPIC == 0 || TOPIC == 14
    Vector2_T14_VectorVectorAddition();
#endif
#if TOPIC == 0 || TOPIC == 15
    Vector2_T15_VectorVectorSubtraction();
#endif
#if TOPIC == 0 || TOPIC == 16
    Vector2_T16_DotOperator();
#endif
#if TOPIC == 0 || TOPIC == 17
    Vector2_T17_Copy();
#endif
}

void Loop()
{
}
// namespace L07_Vector2
}

// Lesson_L07_Vector2_h
#endif
