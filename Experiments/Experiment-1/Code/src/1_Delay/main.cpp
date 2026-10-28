//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: Experiments/Experiment-1/Code/src/1_Delay
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
//   2026-10-28  v6.8.0
//   1_Delay/main.cpp last changed: 2026-10-28  v6.8.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//
// Experiment-1, Lab 1: The delay() Function.
// Wiring: Uno and USB cable.
// Header added 20261028 (v6.8.0); the code is unchanged.
//

#include <Arduino.h>

#define LED_PIN 13

// Global
int counter = 0;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");
    pinMode(LED_PIN, OUTPUT);
}

// loop() prints and then increments counter, so the first line
// reads Number of Loops: 0. delay(1000) is a blocking call: nothing
// else in the program runs for 1000 ms, so one pass takes about 2 s.
void loop()
{
    Serial.print("Number of Loops: ");
    Serial.println(counter++);

    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED HIGH");
    delay(1000);

    digitalWrite(LED_PIN, LOW);
    Serial.println("LED LOW");
    delay(1000);

    Serial.println("-----------");
}
