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
        // Article 1009, Joystick Setup, steps 6 to 8.
        // For the joystick algorithm to work, the readings
        // must follow this graph:
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
        // Move the joystick as shown on the graph.
        // Step 6: left and right must change the x value (a:)
        //   only; if y (b:) changes, exchange A0 and A1 in
        //   lines 82 and 84.
        // Step 7: x goes from 0 (left) to 1023 (right).
        // Step 8: y goes from 0 (backward, down) to 1023
        //   (forward, up).
        // If an axis is reversed, 1023 to 0, comment out its
        // line (82 or 84) and use the line below it (83 or 85):
        // xDigital = 1023 - analogRead(A1); // could be A0
        // yDigital = 1023 - analogRead(A0); // could be A1
        //
        // Step 9: record the pins and reversals in the notebook.
        // Debug() is defined in numerics/MiscMath.h.
#ifdef DEBUG_MAIN
        Debug<int>("Analogs: ", xDigital, yDigital); 
#endif

        // Expected output at rest, for example:
        // Button ON
        // Analogs:  a: 512 b: 509
        // Readings at rest near 511 are expected; small offsets
        // from center are normal and are removed by the dead zone.
        // When every step passes, record the result in the lab
        // notebook and go to L298N Setup, which selects Step2_JUL
        // in platformio.ini, line 31.
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
