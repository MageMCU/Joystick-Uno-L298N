//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: Experiments/Experiment-5/Code/src/1_Vector3
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
// RELEASE
//   2026-10-30  v7.3.0
//   1_Vector3/main.cpp last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//
// Experiment-5, Lab 1: Vector3.h and the joystick vector.
//
// Wiring: the drive as wired since Experiment-3; power the joystick as in
// Article 1004, Experiment-3, Powering the Joystick after Experiment-3.
// setup() holds D5 to D10 LOW. Do not reset the Uno while the bench
// supply is applied.
//
// The two normalized joystick inputs (x, y) are stored as a Vector3 with
// z = 0. For six test points, and then for the live joystick once per
// second, the program prints the magnitude, the angle from the two angle
// functions of MiscMath.h in degrees, and the octant computed from the
// angle as the whole part of (angle / 45) plus 1.

#include <Arduino.h>
#include "Timer.h"
#include "LinearMap.h"
#include "Vector3.h"
#include "MiscMath.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

Timer timer;
LinearMap<float> mapInput(0, 1023, -1.0, 1.0);

void printVector(float x, float y)
{
    Vector3<float> v(x, y, 0.0);
    float a1 = AngleRadian(x, y) * RAD_TO_DEG;
    float a2 = Angle2Radian(x, y) * RAD_TO_DEG;
    Serial.print("(");
    Serial.print(x, 2);
    Serial.print(", ");
    Serial.print(y, 2);
    Serial.print(")  Magnitude: ");
    Serial.print(v.Magnitude(), 3);
    Serial.print("  AngleRadian: ");
    Serial.print(a1, 1);
    Serial.print("  Angle2Radian: ");
    Serial.print(a2, 1);
    Serial.print("  octant from angle: ");
    Serial.println((int)(a2 / 45.0) + 1);
}

void setup()
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
        /* code */
    }
    Serial.println("Serial 9600 baudrate");

    const float points[6][2] = {{1, 0}, {1, 1}, {0, 1},
                                {-1, 0}, {0, -1}, {0, 0}};
    for (int i = 0; i < 6; i++)
    {
        printVector(points[i][0], points[i][1]);
    }

    // The dot product of two unit vectors is the cosine of the angle
    // between them: (1, 0, 0) * (0, 1, 0) = 0, so the angle is 90 degrees.
    Vector3<float> u(1, 0, 0);
    Vector3<float> w(0, 1, 0);
    Serial.print("u * w = ");
    Serial.println(u * w, 3);

    Serial.println("Live joystick, once per second:");
    timer.resetTimer();
}

void loop()
{
    if (timer.isTimer(1000))
    {
        // The two analogRead() lines of Step2_JUL since v3.1.0
        // (x A0, y A1; changed here 20261018, v3.2.0)
        int xDigital = analogRead(A0);
        int yDigital = analogRead(A1);
        printVector(mapInput.Map((float)xDigital),
                    mapInput.Map((float)yDigital));
    }
}
