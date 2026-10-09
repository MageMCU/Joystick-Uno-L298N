//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: src/Step3_MathLessons/19_JoystickFrame
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
// Article 1009, Joystick Setup, corrects a joystick mounted in any of
// eight orientations by exchanging or reversing the analogRead() lines.
// A counterclockwise mount by theta rotates the joystick's coordinate frame
// by theta, so its raw readings are rotated by -theta from the robot frame.
// Multiplying by the rotation matrix of theta returns them to the robot frame.
//
// Part 1 (Uno and USB cable only) checks the rotation with test vectors.
// Part 2 reads the live joystick once per second and prints the raw
// vector, the corrected vector, and the octant from Joystick.h.
// Set MOUNT_ANGLE_DEG to the angle at which the joystick is mounted,
// counterclockwise, as seen from above.

#include <Arduino.h>
#include "Timer.h"
#include "Joystick.h"
#include "numerics/LinearMap.h"
#include "numerics/Vector2.h"
#include "numerics/Matrix2x2.h"

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

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println(F("Lesson 19 Part 1: rotation test vectors"));

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

    correction = correction.Rotation(MOUNT_ANGLE_DEG * DEG_TO_RAD);
    Serial.println(F("Part 2: live joystick, once per second"));
    timer.resetTimer();
}

void loop()
{
    if (timer.isTimer(1000))
    {
        // Use the two analogRead() lines recorded in Experiment-2
        int xDigital = analogRead(A1);
        int yDigital = analogRead(A0);
        Vector2<float> raw(mapInput.Map((float)xDigital), mapInput.Map((float)yDigital));
        Vector2<float> robot = correction * raw;
        joystick.UpdateInputs(robot.x(), robot.y());
        printVector(F("raw "), raw);
        printVector(F("robot "), robot);
        Serial.print(F("octant "));
        Serial.println(joystick.Octant());
    }
}
