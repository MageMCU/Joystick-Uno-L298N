//
// Carpenter Software
// Folder: src/Step1_Joystick: File: Class main.cpp
// Github: MageMCU
// Repository: Joystick-UNO-L298N
// Folder: Code
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
    int buttonPin = 2; // UNO D2 (CHIP-PD2)
    // The joystick has a button with pin SW, so wire
    // the pin SW to UNO pin D2.
    int ledPin = 3; // UNO D3 (CHIP-PD3)
    buttonDebug = Button(buttonPin, ledPin);
}

// If you're using a breadboard with Atmega328p and a 16MHz Crystal,
// To check the circuit, install the Blink Sketch. If the LED is 
// blinking, then your circuit is good. 
// If not, check your wiring...
// If your wiring is good, replace the crystal with one that you know
// that works.
// If it still does not work with the Blink sketch and if the chip is 
// new, have you installed a bootloader?
// Fianlly use a different Atmega328p chip repeat the steps.
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
        // SEE ARTICLES AT GITHUB (especially Joystick Setup - L298N Supplemental)
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
        // Text x-axis values changes
        // Text y-axis values changes
        // Next,
        // Text x-axis from left 0 to right 1023
        // Text y-axis from backward (down) 0 to forward (up) 1023
        // If the values are reversed, for example, 1023 to 0,
        // use the following equation tested for each: 
        // xDigital = 1023 - analogRead(A1); // could be A0
        // yDigital = 1023 - analogRead(A0); // could be A1
        //
        // Debug the output... (See MiscMath.h for Debug() functions)
#ifdef DEBUG_MAIN
        Debug<int>("Analogs: ", xDigital, yDigital); 
#endif

        // You should the following results:
        // Button ON␍␊
        // Analogs:X:509:Y:527␍␊
        // Depending on the Joystick Potentiometers, the values 
        // may not accurate. 
        // Once the values display the correct ouput, then the
        // wiring between the Joysticj & UNO is good.
        // Go to Step-2. Remember to setup the PlatformIO.ini file
        // for the next step.
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
