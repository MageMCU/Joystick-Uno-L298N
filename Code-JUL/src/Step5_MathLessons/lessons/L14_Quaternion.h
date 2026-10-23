//
// Carpenter Software
// File: L14_Quaternion.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L14_Quaternion, selected with LESSON 14 in Step5_MathLessons/main.cpp
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestQuaternion.h (merged 20261008)
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
// Lesson 14: quaternions, the four number description of a rotation in
// 3D. The rules for i, j, and k, the unit quaternion of a turn,
// q = (cos(a/2), n sin(a/2)), the norm, the conjugate, the inverse, and
// the product are explained in include/numerics/Quaternion.h.
// Several topics use q = (1, 2, 3, 4):
//   |q|^2 = 1 + 4 + 9 + 16 = 30, |q| = 5.48
//   unit quaternion q / |q| = (0.18, 0.37, 0.55, 0.73)
//   conjugate (1, -2, -3, -4)
// A game loop, as the comments below call it, repeats one small step
// many times, as a game or a robot updates its state on every pass.
// The topics run T01 to T09 (see Setup()).
#ifndef Lesson_L14_Quaternion_h
#define Lesson_L14_Quaternion_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 9

#include <Arduino.h>
#include "Debug.h"

namespace L14_Quaternion
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// Undergoing further TESTS 20230114 jc
// T09: a 2 degree turn about the x axis applied 180 times; each line
// shows the step, the quaternion, and its angle in degrees. The angle
// climbs 0, 2, 4, ... to 358: the quaternion has added up the turns.
// ---------------------------------------------------------------
// Quaternion_T09_ToAngleAxis (teaching notes, v6.3.0)
// Hint: ToAngleAxis, read the angle back out of a quaternion.
// Purpose: GetEulerAngle() returns the angle, in degrees, of the turn that
// q holds, while q collects turns of 2 degrees about the x axis.
// What is learnt:
//   Angle from w   angle = 2 acos(w), because w = cos(angle / 2).
//   The printed angle climbs 0, 2, 4, ... 358: the product has added the
//   turns, and the x component reaches 1.000 at 180 degrees.
//   String concatenation  String(iAngle) + " " joins two pieces of text.
// Expected output (180 lines):
//   0 1.000,0.000,0.000,0.000 angle: 0.000
//   180 0.000,1.000,0.000,0.000 angle: 180.000
//   358 -1.000,0.017,0.000,0.000 angle: 358.000
// ---------------------------------------------------------------
void Quaternion_T09_ToAngleAxis()
{
    printTitle(F("Quaternion T09 Quaternion to Angle Axis"));

    // Initialization
    // This becomes a half-angle in
    // quaternion multiplication...
    float radian = 2.0 * DEG_TO_RAD;
    float angle;
    Vector3<float> axis(1, 0, 0);
    // Constant
    Quaternion<float> c(axis, radian); // Constant set to 2-degrees
    // Multiplicative
    Quaternion<float> q(axis, 0.0);

    // Game Loop 1 with first quaternion multiplication
    int iAngle = 0;
    do
    {
        String s = String(iAngle) + " ";
        // Prints four columns with 7 decimal digits
        // data for a csv-file
        angle = q.GetEulerAngle();
        printQuaternion(s, q, angle);
        // Quaternion Multiplication --- FIRST method
        q = q * c;
        // Counter
        iAngle += 2; // --------------------- Constant set to 2-degrees
    } while (iAngle < 360);
}

// T08: a 1 degree turn about (1, 2, 3) applied 720 times, four columns
// per line (w, x, y, z; it takes a minute or two). After 360 steps w is
// -1: q = (-1, 0, 0, 0) is the same rotation as (1, 0, 0, 0), because q
// and -q turn every vector alike. After 720 steps w returns to 1. The
// rows can be copied into a spreadsheet (CSV, comma separated values)
// and plotted.
// ---------------------------------------------------------------
// Quaternion_T08_Multiplication (teaching notes, v6.3.0)
// Hint: Multiplication, combine rotations by multiplying quaternions.
// Purpose: q = q c, repeated, adds one turn of 1 degree on every pass.
// What is learnt:
//   Product of quaternions  the product of two turns is one turn that does
//                  both; the order matters (not commutative).
//   Two methods    operator* and Multiply() compute the product with the
//                  terms in a different order; the commented first loop
//                  uses operator*.
//   Double cover   q and -q are the same rotation: after 360 steps w is
//                  -1, after 720 steps it is 1 again.
//   CSV            comma separated values; the four columns can be pasted
//                  into a spreadsheet and plotted as four curves.
//   Game loop      do { } while (i < 721); one small update per pass.
// Expected output (721 lines, about a minute):
//   1.0000000,0.0000000,0.0000000,0.0000000
//   0.9999619,0.0023323,0.0046645,0.0069968
//   line 361 (step 360): -0.9999999,-0.0000002,0.0000005,0.0000001
// ---------------------------------------------------------------
void Quaternion_T08_Multiplication()
{
    printTitle(F("Quaternion T08 Quaternion Multiplication"));
    // This prints out a stream of 4-columns of data
    // it could take a minute or two to finish...

    // Initialization
    // This becomes a half-angle in
    // quaternion multiplication...
    float radian = 1.0 * DEG_TO_RAD;
    Vector3<float> axis(1, 2, 3);
    // Constant
    Quaternion<float> c(axis, radian);
    // Multiplicative
    Quaternion<float> q(axis, 0.0);

    // Game Loop 1 with first quaternion multiplication
    int i = 0;
    /*
    do
    {
        // Prints four columns with 7 decimal digits
        // data for a csv-file
        printQuaternion(q);
        // Quaternion Multiplication --- FIRST method
        q = q * c;
        // Counter
        i++;
    } while (i < 721);
    */

    // Game Loop 2 with second quaternion multiplication
    // int i = 0;
    do
    {
        // Prints four columns with 7 decimal digits
        // data for a csv-file
        printQuaternion(q);
        // Quaternion Multiplication --- SECOND method
        q = q.Multiply(c);
        // Counter
        i++;
    } while (i < 721);
}

// T07: a 30 degree turn about (1, 1, 1): q = (0.97, 0.15, 0.15, 0.15).
// Its inverse turns back, and q q^-1 = (1, 0, 0, 0), the identity (no
// turn).
// ---------------------------------------------------------------
// Quaternion_T07_Inverse (teaching notes, v6.3.0)
// Hint: Inverse, the quaternion that undoes q.
// Purpose: q^-1 = q* / |q|^2, and the check q q^-1 = identity.
// What is learnt:
//   Identity quaternion  (1, 0, 0, 0), no turn at all.
//   For the unit quaternion of a turn, the inverse equals the conjugate
//   (T06); the general formula also covers quaternions of other lengths.
//   Check: 30 degrees about (1, 1, 1): w = cos(15 degrees) = 0.97.
// Expected output:
//   q(axis, angleRadian)0.97 0.15 0.15 0.15
//   qI = q.Inverse(): 0.97 -0.15 -0.15 -0.15
//   identity = q * qI: 1.00 0.00 0.00 0.00
// ---------------------------------------------------------------
void Quaternion_T07_Inverse()
{
    printTitle(F("Quaternion T07 Inverse"));

    float angleRadian = 30.0 * DEG_TO_RAD;
    Vector3<float> axis(1, 1, 1);
    printVector3("axis(1, 1, 1)", axis);
    Quaternion<float> q(axis, angleRadian);
    printQuaternion("q(axis, angleRadian)", q);

    Quaternion<float> qI = q.Inverse();
    printQuaternion("qI = q.Inverse(): ", qI);

    Quaternion<float> identity = q * qI;
    printQuaternion("identity = q * qI: ", identity);
}

// T06: the conjugate of (1, 2, 3, 4) is (1, -2, -3, -4).
// ---------------------------------------------------------------
// Quaternion_T06_Conjugate (teaching notes, v6.3.0)
// Hint: Conjugate, negate the vector part.
// Purpose: q* = (w, -x, -y, -z).
// What is learnt:
//   For a unit quaternion the conjugate is the inverse: the same turn
//   backward (the same axis, the opposite direction).
//   q v q* rotates the vector v (Rotate()).
// Expected output:
//   conjugate = q.Conjugate(): 1.00 -2.00 -3.00 -4.00
// ---------------------------------------------------------------
void Quaternion_T06_Conjugate()
{
    printTitle(F("Quaternion T06 Conjugate"));

    Quaternion<float> q(1, 2, 3, 4);
    printQuaternion("q: ", q);
    Quaternion<float> conjugate = q.Conjugate();
    printQuaternion("conjugate = q.Conjugate(): ", conjugate);
}

// T05: (1, 2, 3, 4) / 5.48 = (0.18, 0.37, 0.55, 0.73), of norm 1.00.
// ---------------------------------------------------------------
// Quaternion_T05_UnitQuaternion (teaching notes, v6.3.0)
// Hint: UnitQuaternion, scale to norm 1.
// Purpose: q / |q|, the normalization of a quaternion.
// What is learnt:
//   As for a unit vector: divide each component by the norm.
//   Check: (1, 2, 3, 4) / 5.48 = (0.18, 0.37, 0.55, 0.73).
// Expected output:
//   uQ = q.UnitQuaternion(): 0.18 0.37 0.55 0.73
//   n = uQ.Norm(): 1.0000
// ---------------------------------------------------------------
void Quaternion_T05_UnitQuaternion()
{
    printTitle(F("Quaternion T05 Unit Quaternion"));

    Quaternion<float> q(1, 2, 3, 4);
    printQuaternion("q: ", q);
    Quaternion<float> uQ = q.UnitQuaternion();
    printQuaternion("uQ = q.UnitQuaternion(): ", uQ);
    // The norm ought to be 1
    float n = uQ.Norm();
    Serial.print("n = uQ.Norm(): ");
    Serial.println(String(n, 4));
}

// T04: (1, 2, 3, 4) scaled by 0.5 is (0.5, 1, 1.5, 2); a scaled
// quaternion is no longer a unit quaternion.
// ---------------------------------------------------------------
// Quaternion_T04_Scale (teaching notes, v6.3.0)
// Hint: Scale, multiply all four components by a number.
// Purpose: q s, and why a scaled quaternion is no longer a rotation.
// What is learnt:
//   Scale(0.5) halves each component and the norm. Only a unit quaternion
//   is a pure rotation, so a scaled one must be normalized again (T05)
//   before use.
// Expected output:
//   s = 0.5: 0.5000
//   p = q.Scale(s): 0.50 1.00 1.50 2.00
// ---------------------------------------------------------------
void Quaternion_T04_Scale()
{
    printTitle(F("Quaternion T04 Scale"));

    Quaternion<float> q(1, 2, 3, 4);
    printQuaternion("q: ", q);

    float s = 0.5;
    Serial.print("s = 0.5: ");
    Serial.println(String(s, 4));
    Quaternion<float> p = q.Scale(s);
    printQuaternion("p = q.Scale(s): ", p);
}

// T03: |(1, 2, 3, 4)| = sqrt(30) = 5.48.
// ---------------------------------------------------------------
// Quaternion_T03_Norm (teaching notes, v6.3.0)
// Hint: Norm, the length of the quaternion.
// Purpose: |q| = sqrt(w^2 + x^2 + y^2 + z^2).
// What is learnt:
//   The same formula as the magnitude of a vector, with four components.
//   Check: sqrt(1 + 4 + 9 + 16) = sqrt(30) = 5.4772.
//   String(n, 4) prints 4 decimals.
// Expected output:
//   n = q.Norm(): 5.4772
// ---------------------------------------------------------------
void Quaternion_T03_Norm()
{
    printTitle(F("Quaternion T03 Norm"));

    Quaternion<float> q(1, 2, 3, 4);
    printQuaternion("q: ", q);

    float n = q.Norm();
    Serial.print("n = q.Norm(): ");
    Serial.println(String(n, 4));
}

// T02: (-1, -2, -3, -4) made a unit quaternion has |q|^2 = 1.00, so
// NormDeviation() reports no deviation (within rounding).
// ---------------------------------------------------------------
// Quaternion_T02_NormSquared (teaching notes, v6.3.0)
// Hint: NormSquared, the squared length, the test of a unit quaternion.
// Purpose: |q|^2 = w^2 + x^2 + y^2 + z^2, and the drift test.
// What is learnt:
//   NormSquared() avoids the square root; for a unit quaternion it is 1,
//   so it is the cheap test.
//   Drift          repeated float products slowly move |q| away from 1.
//                  NormDeviation(n) returns true when n differs from 1 by
//                  more than a tolerance; FALSE here means no correction
//                  is needed.
//   q = q.UnitQuaternion(); replaces q with its normalized copy.
// Expected output:
//   q: -0.18 -0.37 -0.55 -0.73
//   n = q.NormSquared(): 1.0000
//   Norm Deviation: FALSE
// ---------------------------------------------------------------
void Quaternion_T02_NormSquared()
{
    printTitle(F("Quaternion T02 Norm Squared"));

    Quaternion<float> q(-1, -2, -3, -4);
    printQuaternion("q: ", q);
    q = q.UnitQuaternion();
    printQuaternion("q: ", q);

    float n = q.NormSquared();
    Serial.print("n = q.NormSquared(): ");
    Serial.println(String(n, 4));

    bool flag = q.NormDeviation(n);
    Serial.print("Norm Deviation: ");
    if (flag) Serial.println("TRUE");
    else Serial.println("FALSE");
}

// T01: the zero quaternion, (1, 2, 3, 4) given directly, a turn of 0
// degrees (always (1, 0, 0, 0)), and a 45 degree turn about (1, 2, 3):
// (0.92, 0.10, 0.20, 0.31).
// ---------------------------------------------------------------
// Quaternion_T01_Constructor (teaching notes, v6.3.0)
// Hint: Constructor, five ways to build a quaternion.
// Purpose: how to declare and instantiate Quaternion variables, and how to
// read and write the four components.
// What is learnt:
//   Quaternion     four numbers (w, x, y, z): w is the scalar part, (x, y,
//                  z) the vector part. A unit quaternion describes one
//                  rotation in 3D.
//   Constructors (overloads):
//     Quaternion<float> q1;              all four components 0
//     Quaternion<float> q2(1, 2, 3, 4);  w, x, y, z given directly
//     Quaternion<float> q3(axis, angle); the unit quaternion of a turn by
//                                        angle (radians) about axis:
//                                        (cos(a/2), n sin(a/2)), n the
//                                        unit axis
//     Quaternion<float> q5(5, 6, 7);     the pure quaternion (0, 5, 6, 7)
//     Quaternion<float> q6(axis2);       the pure quaternion of a vector
//   The argument list decides which constructor runs: three numbers give
//   a pure quaternion, a vector and a number give a turn.
//   Half angle     a turn of 0 degrees always gives (1, 0, 0, 0) whatever
//                  the axis; 45 degrees about (1, 2, 3) gives w = cos(22.5
//                  degrees) = 0.92.
//   Getters        q2.w(), q2.x(), q2.y(), q2.z(), q2.Element(3).
//   Setters        q1.w(1), q1.x(0.5), q1.y(0.25), q1.z(0.125).
// Expected output:
//   q10.00 0.00 0.00 0.00
//   q21.00 2.00 3.00 4.00
//   q3(axis1, angleRadian)1.00 0.00 0.00 0.00
//   q4(axis2, angleRadian)0.92 0.10 0.20 0.31
//   q5(5, 6, 7) 0.00 5.00 6.00 7.00
//   q6(axis2) 0.00 1.00 2.00 3.00
//   q2.w() 1.00  q2.x() 2.00  q2.y() 3.00  q2.z() 4.00  q2.Element(3) 4.00
//   q1 1.00 0.50 0.25 0.12   (after the setters; Serial.print() shows
//   2 decimals, and 0.125 prints as 0.12)
// ---------------------------------------------------------------
void Quaternion_T01_Constructor()
{
    printTitle(F("Quaternion T01 Constructors"));

    Quaternion<float> q1;
    printQuaternion("q1", q1);

    Quaternion<float> q2(1, 2, 3, 4);
    printQuaternion("q2", q2);

    float angleRadian = 0.0 * DEG_TO_RAD;
    Vector3<float> axis1(1, 1, 1);
    printVector3("axis1(1, 1, 1)", axis1);
    Quaternion<float> q3(axis1, angleRadian);
    printQuaternion("q3(axis1, angleRadian)", q3);

    angleRadian = 45.0 * DEG_TO_RAD;
    Vector3<float> axis2(1, 2, 3);
    printVector3("axis2(1, 2, 3)", axis2);
    Quaternion<float> q4(axis2, angleRadian);
    printQuaternion("q4(axis2, angleRadian)", q4);

    // v6.3.0: the pure quaternion constructors make (0, x, y, z), the
    // form that carries a vector into a rotation (Rotate()).
    Quaternion<float> q5(5, 6, 7);
    printQuaternion(F("q5(5, 6, 7) "), q5);
    Quaternion<float> q6(axis2);
    printQuaternion(F("q6(axis2) "), q6);

    // v6.3.0: getters and setters. w(), x(), y(), z() and Element(index)
    // read a component; w(value), x(value), y(value), z(value) write one.
    // An argument selects the setter (overload resolution).
    printSubTitle(F("Getters: q2.w(), q2.x(), q2.y(), q2.z(), q2.Element(3)"));
    Serial.print(F("q2.w() "));
    Serial.println(q2.w());
    Serial.print(F("q2.x() "));
    Serial.println(q2.x());
    Serial.print(F("q2.y() "));
    Serial.println(q2.y());
    Serial.print(F("q2.z() "));
    Serial.println(q2.z());
    Serial.print(F("q2.Element(3) "));
    Serial.println(q2.Element(3));
    printSubTitle(F("Setters: q1.w(1); q1.x(0.5); q1.y(0.25); q1.z(0.125);"));
    q1.w(1);
    q1.x(0.5);
    q1.y(0.25);
    q1.z(0.125);
    printQuaternion(F("q1 "), q1);
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    Quaternion_T01_Constructor();
#endif
#if TOPIC == 0 || TOPIC == 2
    Quaternion_T02_NormSquared();
#endif
#if TOPIC == 0 || TOPIC == 3
    Quaternion_T03_Norm();
#endif
#if TOPIC == 0 || TOPIC == 4
    Quaternion_T04_Scale();
#endif
#if TOPIC == 0 || TOPIC == 5
    Quaternion_T05_UnitQuaternion();
#endif
#if TOPIC == 0 || TOPIC == 6
    Quaternion_T06_Conjugate();
#endif
#if TOPIC == 0 || TOPIC == 7
    Quaternion_T07_Inverse();
#endif
#if TOPIC == 0 || TOPIC == 8
    Quaternion_T08_Multiplication();
#endif
#if TOPIC == 0 || TOPIC == 9
    Quaternion_T09_ToAngleAxis();
#endif
}

void Loop()
{
}
} // namespace L14_Quaternion

#endif // Lesson_L14_Quaternion_h
