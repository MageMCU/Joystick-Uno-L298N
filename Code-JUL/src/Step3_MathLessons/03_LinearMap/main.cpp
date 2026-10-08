//
// Carpenter Software
// File: main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step3_MathLessons/03_LinearMap
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestLinearMap.h (merged 20261008)
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
#include "numerics/LinearMap.h"
#include "numerics/RandomNumber.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

void LinearMap_T2_Reverse()
{
    printTitle("LinearMap T2 Reverse Test");

    // Constructor 
    LinearMap<float> mapCelcius =
        LinearMap<float>(32, 212, 0, 100);
    // Random Float
    // The constructor inputs an integer (int) type 
    // while RandomReal() outpuits a real (float)...
    RandomNumber<float> random =
        RandomNumber<float>((float)-100, (float)1000);
    // Test - Looking for negative values
    float celcius;
    float fahrenheit;
    for (int i = 0; i < 50; i++)
    {
        fahrenheit = random.Random();
        // Space
        Serial.println("");
        // Map
        Serial.print(" map: ");
        celcius = mapCelcius.Map(fahrenheit); // Save Values
        printResults("Fahrenheit: ", fahrenheit, " -> Celsius: ", celcius);
        // Reverse
        Serial.print(" reverse: ");
        fahrenheit = mapCelcius.Reverse(celcius); // Reverse Values
        printResults("Celsius: ", celcius, " -> Fahrenheit: ", fahrenheit);
    }
}

void LinearMap_T1_Inclusive_Test()
{
    printTitle("LinearMap T1 Inclusive Test");

    // Constructor 
    LinearMap<float> mapCelcius =
        LinearMap<float>(32, 212, 0, 100);
    // Random Float
    // The constructor inputs an integer (int) type 
    // while RandomReal() outpuits a real (float)...
    RandomNumber<float> random =
        RandomNumber<float>((float)-100, (float)1000);
    // Test
    float celcius;
    float fahrenheit;
    for (int i = 0; i < 10; i++)
    {
        fahrenheit = random.Random();
        celcius = mapCelcius.Map(fahrenheit); // ---------------- Normal Mapping
        printResults("fahrenheit: ", fahrenheit, " - Celsius: ", celcius);
    }
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // LinearMap tests, in order
    LinearMap_T1_Inclusive_Test();
    LinearMap_T2_Reverse();
}

void loop()
{
}
