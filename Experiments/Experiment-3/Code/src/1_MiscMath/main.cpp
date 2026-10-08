//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: Experiments/Experiment-3/Code/src/1_MiscMath
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
// Experiment-3, Lab 1: MiscMath.h, sign and magnitude.
// Uno and USB cable only.
//
// The L298N class writes the sign of each motor command to a pair of
// direction inputs and absT() of the command, its magnitude, to an
// enable input with analogWrite(). This lab tests absT(), the Map()
// function template, and the overloaded Debug() functions of MiscMath.h.

#include <Arduino.h>
#include "MiscMath.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");

    // absT<int>() on the 16 bit int of the Uno
    const int values[] = {255, -255, 0, -32767, -32768};
    for (int i = 0; i < 5; i++)
    {
        Serial.print("absT<int>(");
        Serial.print(values[i]);
        Serial.print(") = ");
        Serial.println(absT<int>(values[i]));
    }

    // Map() with int arguments and with float arguments, ADC value 512
    int mapInt = Map(512, 0, 1023, -255, 255);
    float mapFloat = Map(512.0f, 0.0f, 1023.0f, -255.0f, 255.0f);
    Serial.print("Map int:   ");
    Serial.println(mapInt);
    Serial.print("Map float: ");
    Serial.println(mapFloat, 2);
    // Step 3: change one argument of the int call to 0.0f, build, and
    // record the compiler error. Then restore the line.

    // Overloaded Debug(): the compiler selects the version whose
    // parameter types match the arguments.
    Debug("One message");
    Debug("One int", 7);
    Debug("Two ints", 3, 4);
    Debug("Int and float", 3, 4.5f);
}

void loop()
{
}
