//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: src/Step3_MathLessons/16_Rotation
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

#include <Arduino.h>
#include "Debug.h"
#include "numerics/Rotation.h"

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

void Rotation_T1_RotateVector()
{
    printTitle("Rotation T1 Rotate (1, 0, 0) by 90 degrees about z");
    Quaternion<float> q(Vector3<float>(0, 0, 1), 90 * DEG_TO_RAD);
    // q = (cos 45, 0, 0, sin 45)
    check(F("q.w"), q.w(), 0.7071, 0.0001);
    check(F("q.z"), q.z(), 0.7071, 0.0001);
    Vector3<float> v = q.Rotate(Vector3<float>(1, 0, 0));
    check(F("Rotated x"), v.x(), 0, 0.0001);
    check(F("Rotated y"), v.y(), 1, 0.0001);
    check(F("Rotated z"), v.z(), 0, 0.0001);
}

void Rotation_T2_QuaternionToMatrix()
{
    printTitle("Rotation T2 Quaternion to Matrix, 120 degrees about (1, 1, 1)");
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

void Rotation_T3_MatrixToQuaternion()
{
    printTitle("Rotation T3 Matrix to Quaternion (round trip)");
    Quaternion<float> q(Vector3<float>(1, 2, 3), 75 * DEG_TO_RAD);
    Quaternion<float> q2 = MatrixToQuaternion(QuaternionToMatrix(q));
    // q2 equals q or -q; both are the same rotation, so |q . q2| = 1.
    check(F("|q . q2|"), fabs(QuaternionDot(q, q2)), 1, 0.0001);
    check(F("Angle of q2 (degrees)"), q2.GetEulerAngle(), 75, 0.01);
}

void Rotation_T4_Slerp()
{
    printTitle("Rotation T4 Slerp from 0 to 90 degrees about z");
    Vector3<float> z(0, 0, 1);
    Quaternion<float> q0(z, 0);
    Quaternion<float> q1(z, 90 * DEG_TO_RAD);
    check(F("t = 0.25 angle"), Slerp(0.25f, q0, q1).GetEulerAngle(), 22.5, 0.01);
    check(F("t = 0.50 angle"), Slerp(0.50f, q0, q1).GetEulerAngle(), 45, 0.01);
    check(F("t = 0.75 angle"), Slerp(0.75f, q0, q1).GetEulerAngle(), 67.5, 0.01);
    // -q1 is the same rotation; slerp still takes the shorter path.
    check(F("t = 0.50 with -q1"), Slerp(0.5f, q0, q1.Scale(-1)).GetEulerAngle(), 45, 0.01);
}

void Rotation_T5_Drift()
{
    printTitle("Rotation T5 720 products of a 1 degree rotation");
    // As in Quaternion_T8: multiplying a unit quaternion many times lets
    // rounding errors change its length. Multiply() renormalizes products
    // that have drifted, so the norm stays 1. 720 turns of 1 degree about
    // one axis is 720 degrees: back to the start (angle 0, or 360).
    Vector3<float> axis(1, 2, 3);
    Quaternion<float> c(axis, 1 * DEG_TO_RAD);
    Quaternion<float> q(axis, 0);
    for (int i = 0; i < 720; i++)
        q = q.Multiply(c);
    check(F("Norm after 720 products"), q.Norm(), 1, 0.0001);
    check(F("w after 720 degrees"), fabs(q.w()), 1, 0.001);
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Rotation tests, in order
    Rotation_T1_RotateVector();
    Rotation_T2_QuaternionToMatrix();
    Rotation_T3_MatrixToQuaternion();
    Rotation_T4_Slerp();
    Rotation_T5_Drift();

    Serial.print(F("Failures: "));
    Serial.println(failures);
}

void loop()
{
}
