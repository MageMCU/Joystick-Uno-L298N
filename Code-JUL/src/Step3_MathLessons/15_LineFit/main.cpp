//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: src/Step3_MathLessons/15_LineFit
// Github: MageMCU
// Repository: Joystick-Uno-L298N
//
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//
// Lesson 15: least squares line fit with LineFit2.h. Added 20261008.
// CREDIT: LineFit2.h is adapted from the work of David Eberly, Geometric
// Tools Engine, GTE/Mathematics/ApprHeightLine2.h (Boost Software License
// 1.0); see the credit and adaptation notes in that file.
//
// Each test prints the expected value, the observed value, and PASS or
// FAIL. Expected values were computed independently on a desktop.
//
// Robot use: the data in T2 stand for one motor, wheel speed (RPM) measured
// at five PWM commands. The slope is RPM per PWM step, and the x intercept
// is the PWM below which the motor does not turn (its dead band).

#include <Arduino.h>
#include "Debug.h"
#include "numerics/LineFit2.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

int failures = 0;

void check(const __FlashStringHelper *label, float observed, float expected, float tolerance)
{
    bool pass = fabs(observed - expected) <= tolerance;
    if (!pass)
        failures++;
    Serial.print(label);
    Serial.print(F(" expected "));
    Serial.print(expected, 4);
    Serial.print(F(" observed "));
    Serial.print(observed, 4);
    Serial.println(pass ? F("  PASS") : F("  FAIL"));
}

void LineFit_T1_ExactLine()
{
    printTitle("LineFit T1 Exact Line y = 2x + 1");
    float x[] = {0, 1, 2, 3, 4};
    float y[] = {1, 3, 5, 7, 9};
    LineFit2<float> fit;
    check(F("Fit() returns true"), fit.Fit(x, y, 5) ? 1 : 0, 1, 0);
    check(F("Slope"), fit.Slope(), 2.0, 0.0001);
    check(F("Intercept"), fit.Intercept(), 1.0, 0.0001);
    check(F("RMS error"), fit.RmsError(x, y, 5), 0.0, 0.0001);
}

void LineFit_T2_MotorCalibration()
{
    printTitle("LineFit T2 Motor Calibration (PWM to RPM)");
    float pwm[] = {60, 100, 140, 180, 220};
    float rpm[] = {12, 38, 61, 88, 113};
    LineFit2<float> fit;
    fit.Fit(pwm, rpm, 5);
    check(F("Slope (RPM per PWM step)"), fit.Slope(), 0.63, 0.0001);
    check(F("Intercept (RPM at PWM 0)"), fit.Intercept(), -25.8, 0.001);
    check(F("Dead band (PWM at 0 RPM)"), fit.XIntercept(), 40.9524, 0.001);
    check(F("Predicted RPM at PWM 255"), fit.Evaluate(255), 134.85, 0.001);
    check(F("RMS error (RPM)"), fit.RmsError(pwm, rpm, 5), 0.7483, 0.0001);
}

void LineFit_T3_Degenerate()
{
    printTitle("LineFit T3 Degenerate Data");
    float x[] = {3, 3, 3};
    float y[] = {1, 2, 3};
    LineFit2<float> fit;
    check(F("All x equal: Fit() returns false"), fit.Fit(x, y, 3) ? 1 : 0, 0, 0);
    check(F("One point: Fit() returns false"), fit.Fit(x, y, 1) ? 1 : 0, 0, 0);
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // LineFit tests, in order
    LineFit_T1_ExactLine();
    LineFit_T2_MotorCalibration();
    LineFit_T3_Degenerate();

    Serial.print(F("Failures: "));
    Serial.println(failures);
}

void loop()
{
}
