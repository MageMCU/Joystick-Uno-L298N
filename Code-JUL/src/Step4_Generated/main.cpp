//
// Carpenter Software
// Folder: src/Step4_Generated: File: main.cpp
// Drive program printed by Step3_Generator
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
// STEPS 2 TO 4
//   Step2_JUL:       the drive program; the Motor Movement Checklist
//                    finds its Bits() value (Article 1009, L298N
//                    Setup). The joystick lines stay as written,
//                    x on A0 and y on A1.
//   Step3_Generator: checks the pins and the joystick lines, asks for
//                    the Bits() value, and prints this file with the
//                    answers written in as constants.
//   Step4_Generated: this file. It drives the robot as Step2_JUL does,
//                    with the Bits() value fixed when it is built.
//
// DATA CHECKED IN STEP3_GENERATOR
//   Joystick center (include/JoystickCenter.h, Step1_Joystick)
//     A0 center 511 (offset 0)
//     A1 center 511 (offset 0)
//   L298N pins (Step2_JUL, lines 66 to 71)
//     ENB  D5   (PD5)
//     IN4  D6   (PD6)
//     IN3  D7   (PD7)
//     IN2  D8   (PB0)
//     IN1  D9   (PB1)
//     ENA  D10  (PB2)
//   Push button and LED (Step2_JUL, lines 47 and 50)
//     SW   D2   (PD2)
//     LED  D12  (PB4)
//   Joystick (Step2_JUL, lines 114 and 115)
//     int xDigital = analogRead(A0);  x on A0 (PC0)
//     int yDigital = analogRead(A1);  y on A1 (PC1)
//   Bits value (Step2_JUL, line 103)
//     motors.Bits(BitsL298N::bits_0000);
//     Left command:  EN D5, D8 HIGH for +, D9 HIGH for -
//     Right command: EN D10, D6 HIGH for +, D7 HIGH for -
//
// DEBUG_GENERATED (below the include lines): while it is defined,
// setup() prints the same data in the serial monitor (9600 baud)
// once, before the motors can run. Comment the line out to leave
// the serial port unused; the drive is the same either way.
// The push button is read after the last line, Ready; a press
// made while the data is printing (about 1 s) is not seen.
//
// include/claude/ace.h holds everything this program needs in one
// file: the joystick algorithm, the mapping and dead zone, the push
// button, the timer, and the L298N pins. It includes Arduino.h only
// and is never edited; a new run of Step3 changes only this file.
// For the same joystick readings it sets the same pin states as
// Step2_JUL, with a control tick about 2.5 times faster (see ace.h).
// ace.h also moves each reading by the joystick center (X_CENTER
// and Y_CENTER below); Step2_JUL keeps the center 511.
// The tick repeats every 50 ms (TICK_MS of ace.h); Step2_JUL uses
// 100 ms.
//
// Push button: SW on D2 with the external 10 kOhm pull up to 5 V
// (pressed reads LOW), line 58 of Step2_JUL as written. The
// internal pull up is off.
//
// Build: in platformio.ini, select this program with
//   build_src_filter, lines 31 to 37: +<Step4_Generated/>, and - before the
//   other four folders
// In a project of its own, copy include/claude/ace.h with this file.
//
// SAFETY COMES FIRST (WATCH YOUR FINGERS): the motors run only while
// the push button state is ON (indicator LED on D12).

#include <Arduino.h>
#include "claude/ace.h"

// Serial verification of the data checked in Step3_Generator.
// Comment this line out to turn the output off.
#define DEBUG_GENERATED

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// Joystick pins, the same as Step2_JUL
const uint8_t X_PIN = A0;
const uint8_t Y_PIN = A1;

// L298N pins resolved from bits_0000
// FWD is HIGH when the command is zero or positive,
// REV is HIGH when the command is negative.
const uint8_t LEFT_EN = 5;
const uint8_t LEFT_FWD = 8;
const uint8_t LEFT_REV = 9;
const uint8_t RIGHT_EN = 10;
const uint8_t RIGHT_FWD = 6;
const uint8_t RIGHT_REV = 7;

// Push button and indicator LED, the same as Step2_JUL
const uint8_t BUTTON_PIN = 2;
const uint8_t LED_PIN = 12;

// Control tick and debounce, in ms (the defaults of ace.h)
const uint16_t TICK_MS = 50;
const uint16_t DEBOUNCE_MS = 50;

// Joystick center measured by Step1_Joystick (JoystickCenter.h)
const uint16_t X_CENTER = 511; // A0
const uint16_t Y_CENTER = 511; // A1

Ace<X_PIN, Y_PIN,
    LEFT_EN, LEFT_FWD, LEFT_REV,
    RIGHT_EN, RIGHT_FWD, RIGHT_REV,
    BUTTON_PIN, LED_PIN, TICK_MS, DEBOUNCE_MS,
    X_CENTER, Y_CENTER> robot;

void setup()
{
    // D5 to D10 as outputs and LOW before anything else (SAFETY)
    robot.begin();
#ifdef DEBUG_GENERATED
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println(F("\n................................................\nStep4_Generated: the drive program printed by Step3_Generator\nSelected in platformio.ini: +<Step4_Generated/>"));
    Serial.println(F("Step4_Generated: data checked in Step3_Generator"));
    Serial.println(F("Joystick center (include/JoystickCenter.h, Step1_Joystick)"));
    Serial.println(F("  A0 center 511 (offset 0)"));
    Serial.println(F("  A1 center 511 (offset 0)"));
    Serial.println(F("L298N pins (Step2_JUL, lines 66 to 71)"));
    Serial.println(F("  ENB  D5   (PD5)"));
    Serial.println(F("  IN4  D6   (PD6)"));
    Serial.println(F("  IN3  D7   (PD7)"));
    Serial.println(F("  IN2  D8   (PB0)"));
    Serial.println(F("  IN1  D9   (PB1)"));
    Serial.println(F("  ENA  D10  (PB2)"));
    Serial.println(F("Push button and LED (Step2_JUL, lines 47 and 50)"));
    Serial.println(F("  SW   D2   (PD2)"));
    Serial.println(F("  LED  D12  (PB4)"));
    Serial.println(F("Joystick (Step2_JUL, lines 114 and 115)"));
    Serial.println(F("  int xDigital = analogRead(A0);  x on A0 (PC0)"));
    Serial.println(F("  int yDigital = analogRead(A1);  y on A1 (PC1)"));
    Serial.println(F("Bits value (Step2_JUL, line 103)"));
    Serial.println(F("  motors.Bits(BitsL298N::bits_0000);"));
    Serial.println(F("  Left command:  EN D5, D8 HIGH for +, D9 HIGH for -"));
    Serial.println(F("  Right command: EN D10, D6 HIGH for +, D7 HIGH for -"));
    Serial.println(F("Ready: press the push button; the LED on D12 shows ON."));
#endif
}

void loop()
{
    // Button, 50 ms timer, and one control tick when the timer fires
    robot.update();
}
