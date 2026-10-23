//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: L18_MotorLineFit.h
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L18_MotorLineFit, selected with LESSON 18 in Step5_MathLessons/main.cpp
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
// Lesson 18: motor calibration with a least squares line fit.
// Added 20261008 for Article 1004, Experiment-7.
// CREDIT: LineFit2.h is adapted from the work of David Eberly, Geometric
// Tools Engine, GTE/Mathematics/ApprHeightLine2.h (Boost Software License
// 1.0); see the credit and adaptation notes in that file.
//
// Wiring: the complete Joystick-Uno-L298N bench of Article 1009,
// Circuit-1, with the drive raised so that both wheels turn freely.
//
// The joystick push button (latching) enables the motors. While it is
// ON, both motors turn forward at one PWM value at a time. Count the
// revolutions of one wheel in 10 s, type the count in the serial monitor
// and press Enter; the program moves to the next PWM value. After the
// last value it fits RPM = slope * PWM + intercept and prints the slope,
// the intercept, the PWM at which the fitted speed is zero (the dead
// band of the motor), and the RMS error. Send n to start a new set of
// five measurements: the motors stop and the button state returns to OFF,
// so a new set starts only after a deliberate press. Do not press the Uno
// reset button while the motor supply is applied; D5 to D10 float between
// a reset and PinsL298N().
//
// SAFETY COMES FIRST (WATCH YOUR FINGERS)

#ifndef Lesson_L18_MotorLineFit_h
#define Lesson_L18_MotorLineFit_h

// Common.h (v6.0.0): this lesson defines no debug switch, so it
// prints only its own output and keeps the 100 ms tick. Up to
// v5.1.0 a line here defined DEBUG_ALL_OFF, which
// turned off the flags Common.h then defined itself.

#include <Arduino.h>
#include "Common.h"
#include "Button.h"
#include "Timer.h"
#include "L298N.h"
#include "numerics/LineFit2.h"

namespace L18_MotorLineFit
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

L298N motors;
Button button;
Timer timerUpdate;

const int points = 5;
float pwm[points] = {60, 100, 140, 180, 220};
float rpm[points];
int step = 0;
String entry = "";

void prompt()
{
    Serial.print(F("PWM "));
    Serial.print((int)pwm[step]);
    Serial.println(F(": count revolutions in 10 s, type the count, press Enter"));
}

void finish()
{
    motors.PowerDownL298N();
    LineFit2<float> fit;
    if (!fit.Fit(pwm, rpm, points))
    {
        Serial.println(F("Fit failed: the PWM values must differ"));
        return;
    }
    Serial.print(F("Slope (RPM per PWM step): "));
    Serial.println(fit.Slope(), 4);
    Serial.print(F("Intercept (RPM at PWM 0): "));
    Serial.println(fit.Intercept(), 2);
    Serial.print(F("Dead band (PWM at 0 RPM): "));
    Serial.println(fit.XIntercept(), 1);
    Serial.print(F("Predicted RPM at PWM 255: "));
    Serial.println(fit.Evaluate(255), 1);
    Serial.print(F("RMS error (RPM): "));
    Serial.println(fit.RmsError(pwm, rpm, points), 2);
    Serial.println(F("Send n to start a new set"));
}

// FIXED 20261012: n starts a new set without a reset of the Uno, so the
// motor supply can stay applied (Article 1004, Experiment-3, Powering the
// Joystick after Experiment-3). The button state returns to OFF.
void newSet()
{
    motors.PowerDownL298N();
    button.resetButton();
    step = 0;
    entry = "";
    Serial.println(F("New set: press the joystick button to start the motors"));
    prompt();
}

void readEntry()
{
    while (Serial.available() > 0)
    {
        char c = Serial.read();
        if (c == 'n' || c == 'N')
        {
            newSet();
            continue;
        }
        if (c == '\n' || c == '\r')
        {
            if (entry.length() == 0)
                continue;
            if (step >= points)
            {
                entry = "";
                Serial.println(F("Set complete: send n to start a new set"));
                continue;
            }
            if (!button.isButtonOn())
            {
                entry = "";
                Serial.println(F("Button OFF: count discarded; press button and re-enter"));
                prompt();
                continue;
            }
            float revolutions = entry.toFloat();
            entry = "";
            rpm[step] = revolutions * 6.0; // revolutions in 10 s to RPM
            Serial.print(F("RPM: "));
            Serial.println(rpm[step], 1);
            step++;
            if (step < points)
                prompt();
            else
                finish();
        }
        else
        {
            entry += c;
        }
    }
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println(F("Lesson 18: motor calibration"));

    int buttonPin = 2; // UNO D2, joystick SW
    int ledPin = 12;   // UNO D12, indicator LED (3 in the advanced wiring)
    button = Button(buttonPin, ledPin);
    // FIXED 20261018 (v3.2.0): internal pull up off, as in Step2_JUL.
    // begin() configures D2 as INPUT_PULLUP; pinMode(INPUT) after it
    // turns the internal pull up off. The joystick module has no
    // resistor on SW, so the external 10 kOhm pull up from D2 to 5 V
    // (Circuit-2 of Article 1004) is required.
    button.begin();
    pinMode(buttonPin, INPUT);

    motors = L298N(5, 6, 7, 8, 9, 10);
    motors.PinsL298N();
    // Replace bits_0000 with the value found with the Motor Movement
    // Checklist (Article 1009, L298N Setup; Article 1004, Experiment-5).
    motors.Bits(BitsL298N::bits_0000);

    Serial.println(F("Press the joystick button to start the motors"));
    prompt();
}

void Loop()
{
    button.updateButton();
    readEntry();

    if (timerUpdate.isTimer(BUTTON_TIMER_mS))
    {
        if (!button.isButtonOn() || step >= points)
        {
            // SAFETY COMES FIRST
            motors.PowerDownL298N();
            return;
        }
        int command = (int)pwm[step];
        motors.UpdateL298N(command, command, true);
    }
}
} // namespace L18_MotorLineFit

// Number of topics of this lesson; main.cpp checks TOPIC against it.
// One topic: the bench program of Setup() and Loop(); TOPIC 0 and 1
// both run it. Placed at the end of the file so that the line numbers
// cited by the Experiment lab cards do not change.
#define LESSON_TOPICS 1

// TEACHING NOTES (v6.1.1), placed at the end of the file so that the
// line numbers cited by Experiment-7 (168, 174, 175) do not change.
// RPM is revolutions per minute: a count of revolutions in 10 s times 6.
// The fit (include/numerics/LineFit2.h) gives the slope, the extra RPM
// for each PWM step, and the x intercept, the PWM at which the fitted
// line reaches 0 RPM: the dead band, the range of small PWM values that
// do not overcome the friction of the motor and gearbox. Below it the
// robot does not move however long the joystick is held.
// Lesson 15, topic 2, works the same fit with fixed data; compare the
// two dead bands. A mean of several counts per PWM value reduces the
// error of a single count.
// FUNCTION NOTES (v6.3.0), placed at the end of the file so that the
// line numbers cited by the lab cards do not change. One block for each
// function of the lesson, in the order of the file.
// ---------------------------------------------------------------
// prompt (teaching notes, v6.3.0)
// Hint: prompt, ask for the next count.
// Purpose: print the PWM value of the current step and the instruction.
// What is learnt:
//   (int)pwm[step] casts the float to int so it prints without decimals.
// ---------------------------------------------------------------
// ---------------------------------------------------------------
// finish (teaching notes, v6.3.0)
// Hint: finish, fit the line and print the motor model.
// Purpose: stop the motors, fit RPM against PWM, and print the results.
// What is learnt:
//   The motors are stopped first: safety before calculation.
//   if (!fit.Fit(...)) return; an early return when the fit fails, so no
//   invalid line is printed (lesson 15, T03).
//   Getters of LineFit2: Slope(), Intercept(), XIntercept() (the dead
//   band), Evaluate(255), RmsError().
// ---------------------------------------------------------------
// ---------------------------------------------------------------
// newSet (teaching notes, v6.3.0)
// Hint: newSet, start again without a reset.
// Purpose: begin five new measurements while the motor supply stays on.
// What is learnt:
//   button.resetButton() returns the latched state to OFF, so the motors
//   start only after a deliberate press.
// ---------------------------------------------------------------
// ---------------------------------------------------------------
// readEntry (teaching notes, v6.3.0)
// Hint: readEntry, collect a typed number one character at a time.
// Purpose: a nonblocking reader: it takes the characters that have
// arrived and returns at once, so Loop() keeps the motors serviced.
// What is learnt:
//   String entry   collects the characters; entry += c appends one.
//   entry.toFloat()  converts the text to a number (0 if it is not one).
//   continue       skips to the next character of the while loop.
//   revolutions * 6.0  counts in 10 s times 6 give revolutions per minute.
//   A count typed while the button is OFF is discarded.
// ---------------------------------------------------------------
// ---------------------------------------------------------------
// Setup (teaching notes, v6.3.0)
// Hint: Setup, wire the objects to their pins.
// Purpose: configure the button, the L298N pins, and the Bits() value.
// What is learnt:
//   button = Button(buttonPin, ledPin); assigns a new object built by the
//   constructor with arguments to the global button.
//   motors.PinsL298N() sets D5 to D10 as outputs, LOW.
//   motors.Bits(BitsL298N::bits_0000) selects the wiring correction; the
//   scope operator :: names a value inside the enumeration BitsL298N.
// ---------------------------------------------------------------
// ---------------------------------------------------------------
// Loop (teaching notes, v6.3.0)
// Hint: Loop, service the button, the keyboard, and the motors.
// Purpose: the cooperative loop: every task gets a short turn on every
// pass, and none waits.
// What is learnt:
//   timerUpdate.isTimer(BUTTON_TIMER_mS) runs the motor update once per
//   tick (100 ms, Common.h).
//   return inside the if leaves Loop() early after the motors stop.
//   UpdateL298N(command, command, true) drives both motors forward at
//   the PWM value of the current step.
// ---------------------------------------------------------------
#endif // Lesson_L18_MotorLineFit_h
