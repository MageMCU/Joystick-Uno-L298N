//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: Experiments/Experiment-1/Code/src/4_Switch
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
// Experiment-1, Lab 4: Switch.h and contact bounce.
// Wiring: the circuit of Lab 3, unchanged. Push button from D2 to 5 V,
// 10 kOhm pull-down resistor from D2 to GND, indicator LED on D3
// through 220 Ohm to GND.
//
// The Switch class reads the pin on every call to updateSwitch() and
// does not debounce. The program counts every change of isSwitchOn()
// from false to true and prints the count once per second. Compare the
// count with the number of presses, then repeat with Lab 3.

#include <Arduino.h>
#include "Timer.h"
#include "Switch.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// Objects (global: constructed before setup() runs)
Switch pushSwitch(2, 3); // D2 switch, D3 indicator LED
Timer timer;

// Global Variables
unsigned long pressCount = 0;
unsigned long lastPrinted = 0;
bool lastState = false;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");
    Serial.println("Lab 4: press the button ten times");
    timer.resetTimer();
}

void loop()
{
    // Sample the switch on every pass, as Lab 3 samples the button
    pushSwitch.updateSwitch();
    bool state = pushSwitch.isSwitchOn();

    // Count each change from released (false) to pressed (true)
    if (state && !lastState)
    {
        pressCount++;
    }
    lastState = state;

    // Print once per second, only when the count has changed
    if (timer.isTimer(1000) && pressCount != lastPrinted)
    {
        Serial.print("Switch closures counted: ");
        Serial.println(pressCount);
        lastPrinted = pressCount;
    }
}
