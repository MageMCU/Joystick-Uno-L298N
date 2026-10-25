//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: L16_Rotation.h
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L16_Rotation, selected with LESSON 16 in Step5_MathLessons/main.cpp
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
// Lesson 16: quaternion rotations with Quaternion.h and Rotation.h. Added
// 20261008. CREDIT: Rotation.h is adapted from the work of David Eberly,
// Geometric Tools Engine, GTE/Mathematics/Rotation.h and Slerp.h (Boost
// Software License 1.0); see the credit and adaptation notes in that file.
//
// Each test prints the expected value, the observed value, and PASS or
// FAIL. Expected values were computed independently on a desktop.
//
// Conventions: Quaternion stores (w, x, y, z); matrices are row major and
// act on column vectors (v' = R * v); positive angles turn counterclockwise
// when viewed from the tip of the axis (right hand rule).

// TEACHING NOTES (v6.1.1)
// Rotations held as unit quaternions (include/numerics/Quaternion.h) and
// as rotation matrices (Matrix3x3.h), the conversions between them, and
// slerp are explained in include/numerics/Rotation.h. check() and the
// tolerance are explained in lesson 15; the lesson ends with
// "Failures: 0".
// The topics run T01 to T05 (see Setup()).
#ifndef Lesson_L16_Rotation_h
#define Lesson_L16_Rotation_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 5

#include <Arduino.h>
#include "Debug.h"
#include "numerics/Rotation.h"

namespace L16_Rotation
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

int failures = 0;

void check(const __FlashStringHelper *label, float observed, float expected, float tolerance)
{
    bool pass = fabs(observed - expected) <= tolerance;
    if (!pass)
        failures++;
    Serial.print(label);
    Serial.print(F(" expected "));
    Serial.print(expected, 4);
    Serial.print(F(" observed "));
    Serial.print(observed, 4);
    Serial.println(pass ? F("  PASS") : F("  FAIL"));
}

// T01: v' = q v q* turns the x axis 90 degrees about z onto the y axis.
// ---------------------------------------------------------------
// Rotation_T01_RotateVector (teaching notes, v6.3.0)
// Hint: RotateVector, turn a vector with a quaternion.
// Purpose: v' = q v q*, the way a unit quaternion rotates a vector.
// What is learnt:
//   Temporary object as an argument: Quaternion<float> q(Vector3<float>(0,
//                  0, 1), angle) builds the axis in place, without a named
//                  variable.
//   Half angle     a 90 degree turn stores cos 45 and sin 45, 0.7071.
//   Rotate(v)      wraps v as the pure quaternion (0, v), forms q v q*, and
//                  returns the vector part.
//   Getters q.w(), q.z() and v.x(), v.y(), v.z() feed the checks.
//   -0.0000        a signed zero from rounding; it passes the tolerance.
// Expected output (all PASS):
//   q (w x y z) 0.71 0.00 0.00 0.71
//   v = q.Rotate((1, 0, 0)) (-0.00, 1.00, 0.00)   (v6.4.1)
//   q.w 0.7071  q.z 0.7071  Rotated (0, 1, 0)
// ---------------------------------------------------------------
void Rotation_T01_RotateVector()
{
    printTitle(F("Rotation T01 Rotate (1, 0, 0) by 90 degrees about z"));
    Quaternion<float> q(Vector3<float>(0, 0, 1), 90 * DEG_TO_RAD);
    printQuaternion(F("q (w x y z) "), q); // v6.4.1: print the input
    // q = (cos 45, 0, 0, sin 45)
    check(F("q.w"), q.w(), 0.7071, 0.0001);
    check(F("q.z"), q.z(), 0.7071, 0.0001);
    Vector3<float> v = q.Rotate(Vector3<float>(1, 0, 0));
    printVector3(F("v = q.Rotate((1, 0, 0))"), v); // v6.4.1
    check(F("Rotated x"), v.x(), 0, 0.0001);
    check(F("Rotated y"), v.y(), 1, 0.0001);
    check(F("Rotated z"), v.z(), 0, 0.0001);
}

// T02: a turn of 120 degrees about the diagonal (1, 1, 1) moves each
// axis onto the next, so the matrix holds only 0s and 1s: a permutation
// matrix (one 1 in every row and every column).
// ---------------------------------------------------------------
// Rotation_T02_QuaternionToMatrix (teaching notes, v6.3.0)
// Hint: QuaternionToMatrix, the same rotation as a 3 x 3 matrix.
// Purpose: convert the quaternion form to the matrix form of a rotation.
// What is learnt:
//   Two forms of one rotation: a quaternion (4 numbers, cheap to combine
//   and to renormalize) and a matrix (9 numbers, fast to apply to many
//   vectors).
//   Free function  QuaternionToMatrix(q) belongs to Rotation.h, not to a
//                  class, so it is called without an object.
//   Permutation matrix  one 1 in every row and every column, 0 elsewhere:
//                  it reorders the axes (x to y, y to z, z to x).
//   A rotation matrix has determinant 1.
// Expected output:
//   R
//   0.00 0.00 1.00
//   1.00 0.00 0.00
//   0.00 1.00 0.00
//   all checks PASS
// ---------------------------------------------------------------
void Rotation_T02_QuaternionToMatrix()
{
    printTitle(F("Rotation T02 Quaternion to Matrix, 120 degrees about (1, 1, 1)"));
    // A 120 degree turn about (1, 1, 1) maps x to y, y to z, and z to x.
    Quaternion<float> q(Vector3<float>(1, 1, 1), 120 * DEG_TO_RAD);
    Matrix3x3<float> R = QuaternionToMatrix(q);
    printMatrix3x3("R ", R);
    check(F("R(1,0)"), R.GetElement(1, 0), 1, 0.0001);
    check(F("R(2,1)"), R.GetElement(2, 1), 1, 0.0001);
    check(F("R(0,2)"), R.GetElement(0, 2), 1, 0.0001);
    check(F("R(0,0)"), R.GetElement(0, 0), 0, 0.0001);
    check(F("Determinant"), R.Determinant(), 1, 0.0001);
}

// T03: quaternion to matrix and back. The result may be -q instead of q;
// |q . q2| = 1 shows that both describe the same 75 degree turn.
// ---------------------------------------------------------------
// Rotation_T03_MatrixToQuaternion (teaching notes, v6.3.0)
// Hint: MatrixToQuaternion, back from the matrix to a quaternion.
// Purpose: the round trip q to R to q2, and why q2 may be -q.
// What is learnt:
//   Double cover   q and -q give the same matrix, so the way back cannot
//                  know the sign; both are correct.
//   Comparison by dot product  |q . q2| = 1 means the two unit quaternions
//                  are equal or opposite: the same rotation.
//   Nested calls   MatrixToQuaternion(QuaternionToMatrix(q)): the inner
//                  call runs first.
// Expected output (all PASS):
//   q (w x y z) 0.79 0.16 0.33 0.49
//   q2 (w x y z) 0.79 0.16 0.33 0.49   (v6.4.1)
//   |q . q2| 1.0000   Angle of q2 (degrees) 75.0000
// ---------------------------------------------------------------
void Rotation_T03_MatrixToQuaternion()
{
    printTitle(F("Rotation T03 Matrix to Quaternion (round trip)"));
    Quaternion<float> q(Vector3<float>(1, 2, 3), 75 * DEG_TO_RAD);
    Quaternion<float> q2 = MatrixToQuaternion(QuaternionToMatrix(q));
    // v6.4.1: print both quaternions; q2 may be q or -q (the same
    // rotation), which is why the check uses |q . q2|.
    printQuaternion(F("q (w x y z) "), q);
    printQuaternion(F("q2 (w x y z) "), q2);
    // q2 equals q or -q; both are the same rotation, so |q . q2| = 1.
    check(F("|q . q2|"), fabs(QuaternionDot(q, q2)), 1, 0.0001);
    check(F("Angle of q2 (degrees)"), q2.GetEulerAngle(), 75, 0.01);
}

// T04: slerp from no turn to 90 degrees about z: a quarter of the way
// is 22.5 degrees, half 45, three quarters 67.5, at a constant rate.
// ---------------------------------------------------------------
// Rotation_T04_Slerp (teaching notes, v6.3.0)
// Hint: Slerp, spherical linear interpolation between two rotations.
// Purpose: find the rotations in between, at a constant angular rate.
// What is learnt:
//   Interpolation  values between two known ones; t = 0 gives q0, t = 1
//                  gives q1, t = 0.5 halfway.
//   Slerp          moves along the great circle of the unit sphere, so
//                  equal steps of t give equal steps of angle (a plain
//                  average of the components would not).
//   0.25f          the suffix f makes the constant a float; without it,
//                  0.25 is a double in C++ (32 bits on the Uno as well).
//   Shorter path   with -q1 slerp still turns 45 degrees, not 135.
// Expected output (all PASS):
//   q0 (w x y z) 1.00 0.00 0.00 0.00
//   q1 (w x y z) 0.71 0.00 0.00 0.71   (v6.4.1)
//   22.4999 (22.5 within the tolerance), 45.0000, 67.5000, 45.0000
// ---------------------------------------------------------------
void Rotation_T04_Slerp()
{
    printTitle(F("Rotation T04 Slerp from 0 to 90 degrees about z"));
    Vector3<float> z(0, 0, 1);
    Quaternion<float> q0(z, 0);
    Quaternion<float> q1(z, 90 * DEG_TO_RAD);
    printQuaternion(F("q0 (w x y z) "), q0); // v6.4.1: print the inputs
    printQuaternion(F("q1 (w x y z) "), q1);
    check(F("t = 0.25 angle"), Slerp(0.25f, q0, q1).GetEulerAngle(), 22.5, 0.01);
    check(F("t = 0.50 angle"), Slerp(0.50f, q0, q1).GetEulerAngle(), 45, 0.01);
    check(F("t = 0.75 angle"), Slerp(0.75f, q0, q1).GetEulerAngle(), 67.5, 0.01);
    // -q1 is the same rotation; slerp still takes the shorter path.
    check(F("t = 0.50 with -q1"), Slerp(0.5f, q0, q1.Scale(-1)).GetEulerAngle(), 45, 0.01);
}

// T05: rounding drift (Quaternion.h, m_driftCorrect()): after 720
// products the norm is still 1, and the turn is back at its start.
// ---------------------------------------------------------------
// Rotation_T05_Drift (teaching notes, v6.3.0)
// Hint: Drift, rounding error that builds up over many products.
// Purpose: show that Multiply() keeps the quaternion at unit length over
// 720 products.
// What is learnt:
//   Accumulated rounding  each float product rounds a little; thousands of
//                  products can move |q| away from 1, and the rotation
//                  then also scales.
//   Renormalization  Multiply() divides by the norm when it has drifted
//                  (m_driftCorrect()).
//   A for loop without braces repeats only the next statement.
//   fabs(q.w()) accepts w = 1 or w = -1: 720 degrees, back to the start
//   either way (double cover).
// Expected output (all PASS):
//   q after 720 products (w x y z) 1.00 0.00 -0.00 -0.00   (v6.4.1)
//   Norm after 720 products 1.0000
//   w after 720 degrees 1.0000
//   Failures: 0
// ---------------------------------------------------------------
void Rotation_T05_Drift()
{
    printTitle(F("Rotation T05 720 products of a 1 degree rotation"));
    // As in Quaternion_T8: multiplying a unit quaternion many times lets
    // rounding errors change its length. Multiply() renormalizes products
    // that have drifted, so the norm stays 1. 720 turns of 1 degree about
    // one axis is 720 degrees: back to the start (angle 0, or 360).
    Vector3<float> axis(1, 2, 3);
    Quaternion<float> c(axis, 1 * DEG_TO_RAD);
    Quaternion<float> q(axis, 0);
    for (int i = 0; i < 720; i++)
        q = q.Multiply(c);
    printQuaternion(F("q after 720 products (w x y z) "), q); // v6.4.1
    check(F("Norm after 720 products"), q.Norm(), 1, 0.0001);
    check(F("w after 720 degrees"), fabs(q.w()), 1, 0.001);
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    Rotation_T01_RotateVector();
#endif
#if TOPIC == 0 || TOPIC == 2
    Rotation_T02_QuaternionToMatrix();
#endif
#if TOPIC == 0 || TOPIC == 3
    Rotation_T03_MatrixToQuaternion();
#endif
#if TOPIC == 0 || TOPIC == 4
    Rotation_T04_Slerp();
#endif
#if TOPIC == 0 || TOPIC == 5
    Rotation_T05_Drift();
#endif

    Serial.print(F("Failures: "));
    Serial.println(failures);
}

void Loop()
{
}
} // namespace L16_Rotation

#endif // Lesson_L16_Rotation_h
