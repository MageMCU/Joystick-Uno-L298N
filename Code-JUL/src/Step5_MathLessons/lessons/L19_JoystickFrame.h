//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: L19_JoystickFrame.h
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L19_JoystickFrame, selected with LESSON 19 in Step5_MathLessons/main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//
// Lesson 19: rotating the joystick frame with Matrix2x2 and Vector2.
// Added 20261008 for Article 1004, Experiment-8.
//
// Article 1009, L298N Setup, corrects a joystick mounted in any of
// eight orientations with the Bits() value alone (90 degree turns).
// A counterclockwise mount by theta rotates the joystick's coordinate frame
// by theta, so its raw readings are rotated by -theta from the robot frame.
// Multiplying by the rotation matrix of theta returns them to the robot frame.
//
// Topic 1, Part 1 (Uno and USB cable only), checks the rotation with
// test vectors. Topic 2, Part 2, reads the live joystick once per second
// and prints the raw vector, the corrected vector, and the octant from
// Joystick.h. TOPIC 0 runs both, as before v5.1.0.
// Set MOUNT_ANGLE_DEG to the angle at which the joystick is mounted,
// counterclockwise, as seen from above.

#ifndef Lesson_L19_JoystickFrame_h
#define Lesson_L19_JoystickFrame_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 2

// Common.h (v6.0.0): this lesson defines no debug switch, so it
// prints only its own output and keeps the 100 ms tick. Up to
// v5.1.0 a line here defined DEBUG_ALL_OFF, which
// turned off the flags Common.h then defined itself.

#include <Arduino.h>
#include "Timer.h"
#include "Joystick.h"
#include "numerics/LinearMap.h"
#include "numerics/Vector2.h"
#include "numerics/Matrix2x2.h"

namespace L19_JoystickFrame
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

const float MOUNT_ANGLE_DEG = 0.0;

Timer timer;
Joystick<float> joystick;
LinearMap<float> mapInput(0, 1023, -1.0, 1.0);
Matrix2x2<float> correction;
int failures = 0;

void check(const __FlashStringHelper *label, float observed, float expected)
{
    bool pass = fabs(observed - expected) <= 0.0001;
    if (!pass)
        failures++;
    Serial.print(label);
    Serial.print(F(" expected "));
    Serial.print(expected, 4);
    Serial.print(F(" observed "));
    Serial.print(observed, 4);
    Serial.println(pass ? F("  PASS") : F("  FAIL"));
}

void printVector(const __FlashStringHelper *label, Vector2<float> v)
{
    Serial.print(label);
    Serial.print(F("("));
    Serial.print(v.x(), 2);
    Serial.print(F(", "));
    Serial.print(v.y(), 2);
    Serial.print(F(")  "));
}

// Topic 1 (Part 1): the rotation checked with test vectors
void JoystickFrame_T01_RotationChecks()
{
    Serial.println(F("JoystickFrame T01 Part 1: rotation test vectors"));

    Matrix2x2<float> R;
    // Rotate (1, 0) by 90 degrees: (0, 1)
    R = R.Rotation(HALF_PI);
    Vector2<float> v = R * Vector2<float>(1, 0);
    check(F("90 deg: x"), v.x(), 0);
    check(F("90 deg: y"), v.y(), 1);
    // A 90 degree mount exchanges the axes and reverses one of them:
    // one of the eight orientations of Article 1009.
    R = R.Rotation(-HALF_PI);
    v = R * Vector2<float>(0, 1);
    check(F("-90 deg undoes it: x"), v.x(), 1);
    check(F("-90 deg undoes it: y"), v.y(), 0);
    // A 45 degree mount, which no exchange or reversal can correct
    R = R.Rotation(-PI / 4.0);
    v = R * Vector2<float>(0.7071068, 0.7071068);
    check(F("-45 deg: x"), v.x(), 1);
    check(F("-45 deg: y"), v.y(), 0);
    // A rotation keeps the length of the vector
    check(F("Magnitude kept"), v.Magnitude(), 1);
    Serial.print(F("Failures: "));
    Serial.println(failures);
}

// Topic 2 (Part 2): the live joystick, called from Loop()
void JoystickFrame_T02_LiveJoystick()
{
    if (timer.isTimer(1000))
    {
        // The two analogRead() lines of Step2_JUL since v3.1.0
        // (x A0, y A1; changed here 20261018, v3.2.0)
        int xDigital = analogRead(A0);
        int yDigital = analogRead(A1);
        Vector2<float> raw(mapInput.Map((float)xDigital), mapInput.Map((float)yDigital));
        Vector2<float> robot = correction * raw;
        joystick.UpdateInputs(robot.x(), robot.y());
        printVector(F("raw "), raw);
        printVector(F("robot "), robot);
        Serial.print(F("octant "));
        Serial.println(joystick.Octant());
    }
}

void Setup()
{
    // Hold the six L298N inputs LOW before the motor supply is applied
    // (Article 1004, Experiment-3, Powering the Joystick after
    // Experiment-3; Article 1009, Safety and Supervision, item 4)
    for (int pin = 5; pin <= 10; pin++)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    JoystickFrame_T01_RotationChecks();
#endif
#if TOPIC == 0 || TOPIC == 2
    correction = correction.Rotation(MOUNT_ANGLE_DEG * DEG_TO_RAD);
    Serial.println(F("JoystickFrame T02 Part 2: live joystick, once per second"));
    timer.resetTimer();
#endif
}

void Loop()
{
#if TOPIC == 0 || TOPIC == 2
    JoystickFrame_T02_LiveJoystick();
#endif
}
} // namespace L19_JoystickFrame

// TEACHING NOTES (v6.1.1), placed at the end of the file so that the
// line numbers cited by Experiment-8 do not change.
// Coordinate frame: a set of axes in which positions and directions are
// measured. The joystick has its own frame, fixed to the module; the
// robot has another, fixed to its body. When the module is mounted
// turned by an angle, a push straight ahead on the grip reads as a
// direction turned the other way in the joystick frame.
// The 2 x 2 rotation matrix of the mount angle (Matrix2x2.h, Rotation())
// turns the reading back into the robot frame: robot = correction * raw.
// Example: a module mounted 90 degrees counterclockwise reads a push
// ahead, robot (0, 1), as raw (1, 0); the rotation by 90 degrees turns
// (1, 0) back into (0, 1).
// A 90 degree mount only exchanges the axes and reverses one, which the
// Bits() value of L298N Setup already corrects; a 45 degree mount needs
// the rotation (Topic 1, the last checks).
// Octant: one of the eight directions of Joystick.h, 45 degrees apart
// (1 to 8; 0 is stop).
// FUNCTION NOTES (v6.3.0), placed at the end of the file so that the
// line numbers cited by the lab cards do not change. One block for each
// topic function.
// ---------------------------------------------------------------
// JoystickFrame_T01_RotationChecks (teaching notes, v6.3.0)
// Hint: RotationChecks, test the rotation with known vectors.
// Purpose: confirm that the rotation matrix turns test vectors where the
// mount correction needs them, before the live joystick is used.
// What is learnt:
//   R = R.Rotation(HALF_PI); reuses one matrix object: the new rotation
//   replaces the old one through operator=.
//   HALF_PI and PI are Arduino constants (pi / 2 and pi).
//   Temporary vector  R * Vector2<float>(1, 0) needs no named variable.
//   A rotation keeps length: |v| stays 1.
//   0.7071068 = cos 45 degrees = sin 45 degrees.
// Expected output (Uno and USB cable only):
//   every check PASS, then Failures: 0
// ---------------------------------------------------------------
// ---------------------------------------------------------------
// JoystickFrame_T02_LiveJoystick (teaching notes, v6.3.0)
// Hint: LiveJoystick, correct the live reading for the mount angle.
// Purpose: map the readings, rotate them into the robot frame, and print
// the octant of Joystick.h.
// What is learnt:
//   Vector2<float> raw(mapInput.Map(...), mapInput.Map(...)); constructs
//   a vector from two function results.
//   robot = correction * raw; the matrix built once in Setup() is applied
//   on every reading.
//   joystick.UpdateInputs(x, y) and joystick.Octant(): the same octant
//   logic the drive program uses.
//   Called from Loop(); timer.isTimer(1000) limits it to once per second.
// Expected output (bench):
//   raw (0.00, 0.00)  robot (0.00, 0.00)  octant 0   at rest
// ---------------------------------------------------------------
#endif // Lesson_L19_JoystickFrame_h
