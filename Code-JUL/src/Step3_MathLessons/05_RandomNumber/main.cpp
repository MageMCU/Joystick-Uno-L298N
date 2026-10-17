//
// Carpenter Software
// File: main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step3_MathLessons/05_RandomNumber
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestRandomNumber.h (merged 20261008)
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
#include "numerics/RandomNumber.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

void RandomNumber_T1_RandomNumber_Test()
{
    printTitle("RandomNumber T1 Random Number");

    RandomNumber<float> randomNumber = RandomNumber<float>((float)0, (float)10);

    int cnt = 0;
    while (cnt < 100)
    {
        // Small range - buggy - OK
        Serial.println(String(randomNumber.Random()));
        cnt++;
    }
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // RandomNumber tests, in order
    RandomNumber_T1_RandomNumber_Test();
}

void loop()
{
}
