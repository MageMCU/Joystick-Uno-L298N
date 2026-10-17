//
// Carpenter Software
// Folder: src/Step5_Generated: File: main.cpp
// Drive program printed by Step4_Generator
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
// STEPS 1 TO 5
//   Step1_Joystick:  finds the analog pin and the direction of each
//                    joystick axis (Article 1009, Joystick Setup).
//   Step2_JUL:       finds the Bits() value of the L298N wiring with
//                    the Motor Movement Checklist (Article 1009,
//                    L298N Setup).
//   Step4_Generator: asks four questions in the serial monitor about
//                    the results of Step 1 and Step 2, and prints this
//                    file with the answers written in as constants.
//   Step5_Generated: this file. It drives the robot as Step2_JUL does,
//                    with the bench results fixed when it is built.
//
// ANSWERS GIVEN TO STEP4_GENERATOR
//   1. x pin:        A1 (y on A0)
//   2. x equation:   xDigital = analogRead(A1);
//   3. y equation:   yDigital = analogRead(A0);
//   4. Bits value:   10 (1010), motors.Bits(BitsL298N::bits_1010);
//      Left command:  EN D10, D8 HIGH for +, D9 HIGH for -
//      Right command: EN D5, D7 HIGH for +, D6 HIGH for -
//
// include/claude/ace.h holds everything this program needs in one
// file: the joystick algorithm, the mapping and dead zone, the push
// button, the timer, and the L298N pins. It includes Arduino.h only
// and is never edited; a new run of Step4 changes only this file.
// For the same joystick readings it sets the same pin states as
// Step2_JUL, with a control tick about 2.5 times faster (see ace.h).
//
// Build: environment env:step5 (platformio.ini), which defines
// STEP5_GENERATED. In a project of its own, copy include/claude/ace.h
// and remove the #ifdef line and the #endif line at the end.
//
// SAFETY COMES FIRST (WATCH YOUR FINGERS): the motors run only while
// the push button state is ON (indicator LED on D3).

#ifdef STEP5_GENERATED

#include <Arduino.h>
#include "claude/ace.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// Answers 1 to 3: joystick pins and reversals (true = 1023 - analogRead)
const uint8_t X_PIN = A1;
const bool X_REVERSED = false;
const uint8_t Y_PIN = A0;
const bool Y_REVERSED = false;

// Answer 4: L298N pins resolved from bits_1010
// FWD is HIGH when the command is zero or positive,
// REV is HIGH when the command is negative.
const uint8_t LEFT_EN = 10;
const uint8_t LEFT_FWD = 8;
const uint8_t LEFT_REV = 9;
const uint8_t RIGHT_EN = 5;
const uint8_t RIGHT_FWD = 7;
const uint8_t RIGHT_REV = 6;

// Push button and indicator LED, as in Step2_JUL
const uint8_t BUTTON_PIN = 2;
const uint8_t LED_PIN = 3;

Ace<X_PIN, X_REVERSED, Y_PIN, Y_REVERSED,
    LEFT_EN, LEFT_FWD, LEFT_REV,
    RIGHT_EN, RIGHT_FWD, RIGHT_REV,
    BUTTON_PIN, LED_PIN> robot;

void setup()
{
    robot.begin();
}

void loop()
{
    // Button, 100 ms timer, and one control tick when the timer fires
    robot.update();
}

#endif // STEP5_GENERATED
