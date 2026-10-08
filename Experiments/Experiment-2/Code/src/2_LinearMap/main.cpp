//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: Experiments/Experiment-2/Code/src/2_LinearMap
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
// Experiment-2, Lab 2: LinearMap.h, one formula, three types.
// Uno and USB cable only.
//
// LinearMap is a class template: the type T decides how the formula
// (y2 - y1) * (x - x1) / (x2 - x1) + y1 is computed. The same ADC to
// PWM map is built for float, long, and int, and the results are
// printed side by side. On the Uno an int is 16 bits.

#include <Arduino.h>
#include "LinearMap.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// ADC range 0 to 1023 mapped onto the PWM range -255 to 255
LinearMap<float> mapFloat(0, 1023, -255, 255);
LinearMap<long> mapLong(0, 1023, -255, 255);
LinearMap<int> mapInt(0, 1023, -255, 255);

// ADC range 0 to 1023 mapped onto the joystick range -1 to 1
LinearMap<float> mapInput(0, 1023, -1.0, 1.0);

const int inputs[] = {0, 64, 65, 511, 512, 1023};
const int numberOfInputs = sizeof(inputs) / sizeof(inputs[0]);

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");

    Serial.println("x\tfloat\tlong\tint");
    for (int i = 0; i < numberOfInputs; i++)
    {
        int x = inputs[i];
        Serial.print(x);
        Serial.print('\t');
        Serial.print(mapFloat.Map((float)x), 2);
        Serial.print('\t');
        Serial.print(mapLong.Map((long)x));
        Serial.print('\t');
        Serial.println(mapInt.Map(x));
    }

    // Reverse() undoes Map(): joystick value back to the ADC value
    Serial.println("Reverse: y\tx");
    const float ys[] = {-1.0, 0.0, 1.0};
    for (int i = 0; i < 3; i++)
    {
        Serial.print(ys[i], 2);
        Serial.print('\t');
        Serial.println(mapInput.Reverse(ys[i]), 2);
    }
}

void loop()
{
}
