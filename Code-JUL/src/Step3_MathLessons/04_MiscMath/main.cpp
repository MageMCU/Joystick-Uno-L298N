//
// Carpenter Software
// File: main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step3_MathLessons/04_MiscMath
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestMiscMath.h (merged 20261008)
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

#include <Arduino.h>
#include "Debug.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

void MiscMath_T6_AbsoluteValue()
{
    printTitle("Misc Math T6 Absolute Value");

    float value = -4.9384;
    value = absT<float>(value);
    Debug<String>("absT<float>(-4.9384): ", String(value, 6));

}

void MiscMath_T5_DirectionVector()
{
    printTitle("Misc Math T2 Direction Components");

    float rad;
    Vector3<float> vector;

    // Covers an entire unit circle
    for (int deg = 0; deg < 360; deg += 5)
    {
        rad = (float)deg * DEG_TO_RAD;
        // angle to 3D directional unit vector
        // Note: x, y, and z are referenced as outputs....
        vector = DirectionVector(rad, XZ);
        // 2D-Vector back to radian using XZ...
        rad = AngleRadian(vector.x(), vector.z());
        // Debug Test
        printAngle("DirectionVector: ", deg, vector, rad);
    }
}

void MiscMath_T4_DirectionComponents()
{
    printTitle("Misc Math T2 Direction Components");

    float x;
    float y;
    float z;
    float rad;

    // Covers an entire unit circle
    for (int deg = 0; deg < 360; deg += 5)
    {
        rad = (float)deg * DEG_TO_RAD;
        // angle to 3D directional unit vector
        // Note: x, y, and z are referenced as outputs....
        DirectionComponents(rad, x, y, z, XY);
        // 2D-Vector back to radian using XY...
        rad = AngleRadian(x, y);
        // Debug Test
        printAngle("DirectionComponents: ", deg, x, y, z, rad);
    }
}

void MiscMath_T3_Angle2Radian()
{
    float x;
    float y;
    float rad;

    // Covers an entire unit circle
    for (int deg = 0; deg < 360 + 1; deg += 5)
    {
        rad = (float)deg * DEG_TO_RAD;
        // create a unit-vector
        x = cos(rad);
        y = sin(rad);
        // convert vector to angle
        rad = Angle2Radian(x, y);
        // Debug Test
        printAngle(" Angle2Radian: ", deg, x, y, rad);
    }
}

void MiscMath_T2_AngleRadian()
{
    float x;
    float y;
    float rad;

    // Covers an entire unit circle
    for (int deg = 0; deg < 360 + 1; deg += 5)
    {
        rad = (float)deg * DEG_TO_RAD;
        x = cos(rad);
        y = sin(rad);
        rad = AngleRadian(x, y);
        // Debug Test
        printAngle("AngleRadian: ", deg, x, y, rad);
    }
}

void MiscMath_T1_Map()
{
    printTitle("Misc Math T1 Map");

    printSubTitle("Fahrenheit to Celcius");
    // fahrenheit to celcius
    float fahrenheit = 77;
    Serial.print("fahrenheit: ");
    Serial.println(fahrenheit);
    float celcius = Map<float>(fahrenheit, (float)32, (float)212, (float)0, (float)100);
    Serial.print("celcius = dM.map(fahrenheit, 32, 212, 0, 100): ");
    Serial.println(celcius);

    printSubTitle("Celcius to Fahrenheit");
    celcius = 25;
    Serial.print("celcius: ");
    Serial.println(celcius);
    fahrenheit = Map<float>(celcius, (float)0, (float)100, (float)32, (float)212);
    Serial.print("fahrenheit = dM.map(celcius, 0, 100, 32, 212): ");
    Serial.println(fahrenheit);
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // MiscMath tests, in order
    MiscMath_T1_Map();
    MiscMath_T2_AngleRadian();
    MiscMath_T3_Angle2Radian();
    MiscMath_T4_DirectionComponents();
    MiscMath_T5_DirectionVector();
    MiscMath_T6_AbsoluteValue();
}

void loop()
{
}
