//
// Carpenter Software
// Folder: src/Step1_Joystick: File: Class main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL
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
#include "Headers.h"
#include "Common.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// Declaration of GLOBAL VARIABLES
L298N motors;
Joystick<float> joystick;
LinearMap<float> mapInputFromDigital;
LinearMap<float> mapOutFromJoystick;
Timer timerDebug;
Button buttonDebug;

void setup()
{
#ifdef DEBUG_MAIN
    Serial.begin(9600);
    while (!Serial) {}
#endif

    // Scoped Variables (arbitrary pins)
    // Joystick Assignment
    joystick = Joystick<float>();

    // Utilities
    timerDebug = Timer();

    // Button & Button-LED
    int buttonPin = 2; // UNO D2 (CHIP-PD2), joystick SW
    int ledPin = 3;    // UNO D3 (CHIP-PD3)
    // Circuit-1 of Article 1009 wires the indicator LED to D12:
    // int ledPin = 12; // UNO D12 (CHIP-PB4)
    buttonDebug = Button(buttonPin, ledPin);
}

// For an ATmega328P on a breadboard with a 16 MHz crystal, check
// the circuit first with the Blink sketch. If the LED blinks, the
// circuit is good. If not, check the wiring; if the wiring is good,
// replace the crystal with one known to work. If Blink still fails
// on a new chip, install a bootloader. Finally, try a different
// ATmega328P and repeat the steps.
//
// Joystick Setup, Article 1009: the button state is read on line 68,
// the axes on lines 82 and 84; lines 83 and 85 are the reversed forms.
//
// STEP1: Setup Joystick-UNO
void determineXY_Output()
{   
    //
    bool buttonFlag = buttonDebug.isButtonOn();

#ifdef DEBUG_MAIN
    if (buttonFlag)
        Debug("Button ON");
    else
        Debug("Button OFF");
#endif

    //
    if (buttonFlag)
    {
        // Analog to Digital (10-bit) Conversion 
        // Digital Values from 0 to 1023
        int xDigital = analogRead(A1);
        // int xDigital = 1023 - analogRead(A1);
        int yDigital = analogRead(A0);
        // int yDigital = 1023 - analogRead(A0);
        // -------------------------------------------------
        // See articles at Carpenter Software (carpentersoftware.com)
        // especially, 1009 Parent, Teacher, and Student Guide, in the
        // section Joystick Setup.
        // In order for the Joystick Algorithm to
        // work properly, the following values has to occur:
        //                 (y-axis)
        //         FORWARD  | 1023
        //                  |
        //                  |
        //                  |
        //  0           (511, 511)            1023
        //  ------------------------------------ (x-axis)
        //  LEFT TURN       |         RIGHT TURN         
        //                  |
        //                  |
        //                  |
        //         BACKWARD | 0
        // -------------------------------------------------
        //
        // MOVE the joystick as shown on the graph.
        // Test x-axis values changes
        // Test y-axis values changes
        // Next,
        // Test x-axis from left 0 to right 1023
        // Test y-axis from backward (down) 0 to forward (up) 1023
        // If the values are reversed, for example, 1023 to 0,
        // use the following equation tested for each:
        // xDigital = 1023 - analogRead(A1); // could be A0
        // yDigital = 1023 - analogRead(A0); // could be A1
        //
        // Debug the output... (See MiscMath.h for Debug() functions)
#ifdef DEBUG_MAIN
        Debug<int>("Analogs: ", xDigital, yDigital); 
#endif
    }
}

void loop()
{
    // Button Class
    buttonDebug.updateButton();
    // Timer Class
    // See Common.h file for definitions
    if (timerDebug.isTimer(BUTTON_TIMER_mS))
    {
        // Joystick Function
        determineXY_Output();
    }
}
