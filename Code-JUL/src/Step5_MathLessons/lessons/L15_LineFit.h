//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: L15_LineFit.h
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L15_LineFit, selected with LESSON 15 in Step5_MathLessons/main.cpp
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

// TEACHING NOTES (v6.1.1)
// The least squares line, the residual, the covariance, the intercepts,
// and the RMS error are explained in include/numerics/LineFit2.h, with
// an example to work by hand.
// Self checking: check() compares an observed value with the expected
// one within a tolerance, the largest difference accepted. Floats are
// rounded to about 7 digits, so two computations of the same number
// seldom agree to the last digit; a tolerance of 0.0001 accepts that
// rounding and still catches a wrong formula. The lesson ends with
// "Failures: 0" when every check passes.
// The topics run T01 to T03 (see Setup()).
#ifndef Lesson_L15_LineFit_h
#define Lesson_L15_LineFit_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 3

#include <Arduino.h>
#include "Debug.h"
#include "numerics/LineFit2.h"

namespace L15_LineFit
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

int failures = 0;

// v6.4.1: prints the data of a fit, one labelled row for x and one for
// y, so the output shows every input of the topic.
void printData(const __FlashStringHelper *xLabel, const float *x,
               const __FlashStringHelper *yLabel, const float *y, int n)
{
    Serial.print(xLabel);
    for (int i = 0; i < n; i++)
    {
        Serial.print(' ');
        Serial.print(x[i], 0);
    }
    Serial.println();
    Serial.print(yLabel);
    for (int i = 0; i < n; i++)
    {
        Serial.print(' ');
        Serial.print(y[i], 0);
    }
    Serial.println();
}

void check(const __FlashStringHelper *label, float observed,
           float expected, float tolerance)
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

// T01: five points exactly on y = 2x + 1: the fit finds slope 2 and
// intercept 1, and the RMS error is 0 (no scatter).
// ---------------------------------------------------------------
// LineFit_T01_ExactLine (teaching notes, v6.3.0)
// Hint: ExactLine, fit data that lie exactly on a known line.
// Purpose: how to declare a LineFit2 object, fit it to data, and read the
// results; with exact data the answer is known in advance.
// What is learnt:
//   Declaration    LineFit2<float> fit; the object starts empty; Fit()
//                  fills it.
//   Fit(x, y, n)   computes the least squares line from two arrays of n
//                  values and returns true on success; the line is kept
//                  inside the object.
//   Least squares  the line that makes the sum of the squared vertical
//                  distances (residuals) from the points as small as
//                  possible.
//   Getters        Slope() and Intercept() read the fitted line
//                  y = slope x + intercept.
//   RMS error      root mean square of the residuals; 0 when every point
//                  lies on the line.
//   Ternary to number  fit.Fit(...) ? 1 : 0 turns the bool into 1 or 0 so
//                  check() can compare it.
// Expected output:
//   x: 0 1 2 3 4
//   y: 1 3 5 7 9
//   every line ends in PASS: Slope 2.0000, Intercept 1.0000, RMS 0.0000
// ---------------------------------------------------------------
void LineFit_T01_ExactLine()
{
    printTitle(F("LineFit T01 Exact Line y = 2x + 1"));
    float x[] = {0, 1, 2, 3, 4};
    float y[] = {1, 3, 5, 7, 9};
    // v6.4.1
    printData(F("x:"), x, F("y:"), y, 5);
    LineFit2<float> fit;
    check(F("Fit() returns true"), fit.Fit(x, y, 5) ? 1 : 0, 1, 0);
    check(F("Slope"), fit.Slope(), 2.0, 0.0001);
    check(F("Intercept"), fit.Intercept(), 1.0, 0.0001);
    check(F("RMS error"), fit.RmsError(x, y, 5), 0.0, 0.0001);
}

// T02: wheel speed against PWM; the fit gives 0.63 RPM per PWM step and
// crosses 0 RPM at PWM 40.95: below that the motor does not turn (its
// dead band). Lesson 18 measures the same on the bench.
// ---------------------------------------------------------------
// LineFit_T02_MotorCalibration (teaching notes, v6.3.0)
// Hint: MotorCalibration, a straight line through measured motor data.
// Purpose: turn five measurements of wheel speed at five PWM commands
// into a model of the motor.
// What is learnt:
//   Calibration    measuring a device to find the numbers of its model;
//                  here RPM = 0.63 PWM - 25.8.
//   XIntercept()   the x where the line crosses y = 0: PWM 40.95, the dead
//                  band, below which the motor does not turn.
//   Evaluate(x)    the fitted y at any x: 134.85 RPM at PWM 255, an
//                  extrapolation beyond the measured range.
//   RMS error 0.75 RPM: the typical scatter of the measurements about the
//   line.
// Expected output (all PASS):
//   PWM: 60 100 140 180 220
//   RPM: 12 38 61 88 113
//   Slope 0.6300  Intercept -25.8000  Dead band 40.9524
//   Predicted RPM at PWM 255 134.8500  RMS error 0.7483
// ---------------------------------------------------------------
void LineFit_T02_MotorCalibration()
{
    printTitle(F("LineFit T02 Motor Calibration (PWM to RPM)"));
    float pwm[] = {60, 100, 140, 180, 220};
    float rpm[] = {12, 38, 61, 88, 113};
    // v6.4.1
    printData(F("PWM:"), pwm, F("RPM:"), rpm, 5);
    LineFit2<float> fit;
    fit.Fit(pwm, rpm, 5);
    check(F("Slope (RPM per PWM step)"), fit.Slope(), 0.63, 0.0001);
    check(F("Intercept (RPM at PWM 0)"), fit.Intercept(), -25.8, 0.001);
    check(F("Dead band (PWM at 0 RPM)"), fit.XIntercept(), 40.9524, 0.001);
    check(F("Predicted RPM at PWM 255"), fit.Evaluate(255), 134.85, 0.001);
    check(F("RMS error (RPM)"), fit.RmsError(pwm, rpm, 5), 0.7483, 0.0001);
}

// T03: degenerate data, data from which no line can be found: all x
// equal (a vertical line is not a function of x), or a single point.
// Fit() returns false instead of dividing by zero.
// ---------------------------------------------------------------
// LineFit_T03_Degenerate (teaching notes, v6.3.0)
// Hint: Degenerate, data from which no line can be found.
// Purpose: defensive code: Fit() reports failure instead of dividing by
// zero.
// What is learnt:
//   Degenerate case  input for which the formula breaks down: all x equal
//                  (the variance of x is 0, the slope would be infinite),
//                  or a single point (any line passes through it).
//   Return value as an error report: false means the object holds no
//                  valid line; always test it before reading Slope().
// Expected output (both PASS):
//   x: 3 3 3
//   y: 1 2 3
//   All x equal: Fit() returns false ... PASS
//   One point: Fit() returns false ... PASS
//   Failures: 0
// ---------------------------------------------------------------
void LineFit_T03_Degenerate()
{
    printTitle(F("LineFit T03 Degenerate Data"));
    float x[] = {3, 3, 3};
    float y[] = {1, 2, 3};
    // v6.4.1
    printData(F("x:"), x, F("y:"), y, 3);
    LineFit2<float> fit;
    check(F("All x equal: Fit() returns false"),
          fit.Fit(x, y, 3) ? 1 : 0, 0, 0);
    check(F("One point: Fit() returns false"), fit.Fit(x, y, 1) ? 1 : 0, 0, 0);
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    LineFit_T01_ExactLine();
#endif
#if TOPIC == 0 || TOPIC == 2
    LineFit_T02_MotorCalibration();
#endif
#if TOPIC == 0 || TOPIC == 3
    LineFit_T03_Degenerate();
#endif

    Serial.print(F("Failures: "));
    Serial.println(failures);
}

void Loop()
{
}
// namespace L15_LineFit
}

// Lesson_L15_LineFit_h
#endif
