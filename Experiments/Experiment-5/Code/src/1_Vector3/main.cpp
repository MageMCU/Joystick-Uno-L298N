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
// Experiment-5, Lab 1: Vector3.h and the joystick vector.
//
// Wiring: the joystick of Experiment-2 (Table-1). No motor power.
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
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");

    const float points[6][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 0}, {0, -1}, {0, 0}};
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
        // Use the two analogRead() lines recorded in Experiment-2
        int xDigital = analogRead(A1);
        int yDigital = analogRead(A0);
        printVector(mapInput.Map((float)xDigital), mapInput.Map((float)yDigital));
    }
}
