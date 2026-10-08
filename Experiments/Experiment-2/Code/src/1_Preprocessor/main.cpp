//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: Experiments/Experiment-2/Code/src/1_Preprocessor
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
// Experiment-2, Lab 1: Common.h, Headers.h, and the preprocessor.
// Uno and USB cable only.
//
// The preprocessor runs before the compiler. Each #ifdef block below
// keeps or removes its lines according to the debug flags of Common.h.
// A flag can be defined in Common.h or, without editing Common.h, on the
// build_flags line of platformio.ini, for example:
//   build_flags = -std=gnu++11 -D DEBUG_JOYSTICK

#include <Arduino.h>
#include "Common.h"
#include "Headers.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

void printFlag(const char *name, bool defined)
{
    Serial.print(name);
    Serial.println(defined ? ": defined" : ": not defined");
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");

#ifdef DEBUG_MAIN
    printFlag("DEBUG_MAIN", true);
#else
    printFlag("DEBUG_MAIN", false);
#endif

#ifdef DEBUG_JOYSTICK
    printFlag("DEBUG_JOYSTICK", true);
#else
    printFlag("DEBUG_JOYSTICK", false);
#endif

#ifdef DEBUG_L298N
    printFlag("DEBUG_L298N", true);
#else
    printFlag("DEBUG_L298N", false);
#endif

#ifdef DEBUG_SERIAL_ON
    printFlag("DEBUG_SERIAL_ON", true);
#else
    printFlag("DEBUG_SERIAL_ON", false);
#endif

    Serial.print("BUTTON_TIMER_mS: ");
    Serial.println(BUTTON_TIMER_mS);
}

void loop()
{
}
