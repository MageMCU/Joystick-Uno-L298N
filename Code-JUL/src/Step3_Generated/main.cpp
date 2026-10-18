//
// Carpenter Software
// Folder: src/Step3_Generated: File: main.cpp
// Drive program printed by Step2_Generator
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
// STEPS 1 TO 3
//   Step1_JUL:       the drive program; the Motor Movement Checklist
//                    finds its Bits() value (Article 1009, L298N
//                    Setup). The joystick lines stay as written,
//                    x on A0 and y on A1.
//   Step2_Generator: checks the pins and the joystick lines, asks for
//                    the Bits() value, and prints this file with the
//                    answers written in as constants.
//   Step3_Generated: this file. It drives the robot as Step1_JUL does,
//                    with the Bits() value fixed when it is built.
//
// DATA CHECKED IN STEP2_GENERATOR
//   L298N pins (Step1_JUL, lines 55 to 60)
//     ENA  D5   (PD5)
//     IN1  D6   (PD6)
//     IN2  D7   (PD7)
//     IN3  D8   (PB0)
//     IN4  D9   (PB1)
//     ENB  D10  (PB2)
//   Push button and LED (Step1_JUL, lines 41 and 42)
//     SW   D2   (PD2)
//     LED  D3   (PD3)
//   Joystick (Step1_JUL, lines 103 and 104)
//     int xDigital = analogRead(A0);  x on A0 (PC0)
//     int yDigital = analogRead(A1);  y on A1 (PC1)
//   Bits value (Step1_JUL, line 92)
//     motors.Bits(BitsL298N::bits_0000);
//     Left command:  EN D5, D8 HIGH for +, D9 HIGH for -
//     Right command: EN D10, D6 HIGH for +, D7 HIGH for -
//
// DEBUG_GENERATED (below the include lines): while it is defined,
// setup() prints the same data in the serial monitor (9600 baud)
// once, before the motors can run. Comment the line out to leave
// the serial port unused; the drive is the same either way.
//
// include/claude/ace.h holds everything this program needs in one
// file: the joystick algorithm, the mapping and dead zone, the push
// button, the timer, and the L298N pins. It includes Arduino.h only
// and is never edited; a new run of Step2 changes only this file.
// For the same joystick readings it sets the same pin states as
// Step1_JUL, with a control tick about 2.5 times faster (see ace.h).
// The tick repeats every 50 ms (TICK_MS of ace.h); Step1_JUL uses
// 100 ms.
//
// Push button: SW on D2 with the external 10 kOhm pull up to 5 V
// (pressed reads LOW), line 45 of Step1_JUL as written. The
// internal pull up is off.
//
// Build: in platformio.ini, select this program with
//   build_src_filter = +<*> -<Step1_JUL/> -<Step2_Generator/> +<Step3_Generated/> -<Step4_MathLessons/>
// In a project of its own, copy include/claude/ace.h with this file.
//
// SAFETY COMES FIRST (WATCH YOUR FINGERS): the motors run only while
// the push button state is ON (indicator LED on D3).

#include <Arduino.h>
#include "claude/ace.h"

// Serial verification of the data checked in Step2_Generator.
// Comment this line out to turn the output off.
#define DEBUG_GENERATED

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// Joystick pins, the same as Step1_JUL
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

// Push button and indicator LED, the same as Step1_JUL
const uint8_t BUTTON_PIN = 2;
const uint8_t LED_PIN = 3;

Ace<X_PIN, Y_PIN,
    LEFT_EN, LEFT_FWD, LEFT_REV,
    RIGHT_EN, RIGHT_FWD, RIGHT_REV,
    BUTTON_PIN, LED_PIN> robot;

void setup()
{
#ifdef DEBUG_GENERATED
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println(F("Step3_Generated: data checked in Step2_Generator"));
    Serial.println(F("L298N pins (Step1_JUL, lines 55 to 60)"));
    Serial.println(F("  ENA  D5   (PD5)"));
    Serial.println(F("  IN1  D6   (PD6)"));
    Serial.println(F("  IN2  D7   (PD7)"));
    Serial.println(F("  IN3  D8   (PB0)"));
    Serial.println(F("  IN4  D9   (PB1)"));
    Serial.println(F("  ENB  D10  (PB2)"));
    Serial.println(F("Push button and LED (Step1_JUL, lines 41 and 42)"));
    Serial.println(F("  SW   D2   (PD2)"));
    Serial.println(F("  LED  D3   (PD3)"));
    Serial.println(F("Joystick (Step1_JUL, lines 103 and 104)"));
    Serial.println(F("  int xDigital = analogRead(A0);  x on A0 (PC0)"));
    Serial.println(F("  int yDigital = analogRead(A1);  y on A1 (PC1)"));
    Serial.println(F("Bits value (Step1_JUL, line 92)"));
    Serial.println(F("  motors.Bits(BitsL298N::bits_0000);"));
    Serial.println(F("  Left command:  EN D5, D8 HIGH for +, D9 HIGH for -"));
    Serial.println(F("  Right command: EN D10, D6 HIGH for +, D7 HIGH for -"));
#endif
    robot.begin();
}

void loop()
{
    // Button, 50 ms timer, and one control tick when the timer fires
    robot.update();
}
