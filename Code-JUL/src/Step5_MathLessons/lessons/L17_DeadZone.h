//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: L17_DeadZone.h
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L17_DeadZone, selected with LESSON 17 in Step5_MathLessons/main.cpp
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
// Lesson 17: statistics of the joystick at rest and the dead zone.
// Added 20261008 for Article 1004, Experiment-6.
//
// Wiring: the drive as wired since Article 1004, Experiment-3, with the
// joystick powered as in Experiment-3, Powering the Joystick after
// Experiment-3 (bench supply applied, D5 to D10 held LOW). Leave the grip
// at rest. The program takes 100 readings of each axis, maps them into
// the range -1 to 1 exactly as Step2_JUL does, and prints
// the average, the standard deviation, and the median of each axis. The
// suggested offset is |average| + 3 standard deviations: a resting grip
// then falls inside the dead zone for nearly every reading. Compare it
// with X_OFFSET (0.05) and Y_OFFSET (0.06) in Step2_JUL.
//
// Send any key in the serial monitor to repeat the measurement. Do not
// press the Uno reset button while the bench supply is applied: D5 to D10
// float between a reset and the first statement of setup().

#ifndef Lesson_L17_DeadZone_h
#define Lesson_L17_DeadZone_h

#include <Arduino.h>
#include "numerics/LinearMap.h"
#include "numerics/Statistics.h"

namespace L17_DeadZone
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

const int size = 100;
float xs[size];
float ys[size];
LinearMap<float> mapInput(0, 1023, -1.0, 1.0);

void measure();

void report(const char *axis, float *data, float stepOffset)
{
    Statistics<float> stats(data, size); // note: sorts data in place
    float average = stats.Average();
    float deviation = stats.StandardDeviation();
    float suggested = fabs(average) + 3.0 * deviation;
    Serial.print(axis);
    Serial.print("  average: ");
    Serial.print(average, 4);
    Serial.print("  std dev: ");
    Serial.print(deviation, 4);
    Serial.print("  median: ");
    Serial.print(stats.Median(), 4);
    Serial.print("  min: ");
    Serial.print(stats.GetSorted(0), 4);
    Serial.print("  max: ");
    Serial.println(stats.GetSorted(size - 1), 4);
    Serial.print(axis);
    Serial.print("  suggested offset: ");
    Serial.print(suggested, 3);
    Serial.print("  (Step2_JUL uses ");
    Serial.print(stepOffset, 2);
    Serial.println(")");
}

void Setup()
{
    // Hold the six L298N inputs LOW before the motor supply is applied
    // (Article 1004, Experiment-3, Powering the Joystick after
    // Experiment-3; Article 1009, Safety and Supervision, item 4)
    for (int pin = 5; pin <= 10; pin++)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println(F("Lesson 17: joystick at rest, 100 readings per axis"));
    measure();
}

// FIXED 20261012: a key typed in the serial monitor repeats the
// measurement, so the Uno is not reset with the bench supply applied.
void Loop()
{
    if (Serial.available() > 0)
    {
        delay(20); // let a line ending arrive, then discard the input
        while (Serial.available() > 0)
            Serial.read();
        measure();
    }
}

void measure()
{
    for (int i = 0; i < size; i++)
    {
        // The two analogRead() lines of Step2_JUL since v3.1.0
        // (x A0, y A1; changed here 20261018, v3.2.0)
        int xDigital = analogRead(A0);
        int yDigital = analogRead(A1);
        xs[i] = mapInput.Map((float)xDigital);
        ys[i] = mapInput.Map((float)yDigital);
        delay(10); // 100 readings over about one second
    }

    report("x", xs, 0.05);
    report("y", ys, 0.06);
    Serial.println(F("Send any key to repeat"));
}
} // namespace L17_DeadZone

// Number of topics of this lesson; main.cpp checks TOPIC against it.
// One topic: the bench program of Setup() and Loop(); TOPIC 0 and 1
// both run it. Placed at the end of the file so that the line numbers
// cited by the Experiment lab cards do not change.
#define LESSON_TOPICS 1

// TEACHING NOTES (v6.1.1), placed at the end of the file so that the
// line numbers cited by the lab cards do not change.
// Noise: a joystick at rest does not give one fixed reading; each ADC
// conversion differs by a few counts. The mean (average) of 100 readings
// estimates where the grip rests, and the standard deviation how much
// the readings scatter (include/numerics/Statistics.h).
// Dead zone: the band around zero in which Step2_JUL sets the input to
// zero, so the motors stop when the grip is released. It must cover the
// offset of the rest position and its noise: with a normal distribution,
// the common bell shaped spread of measurement noise, 99.7 percent of
// readings lie within 3 standard deviations of the mean, so
// |mean| + 3 standard deviations covers nearly every reading.
// Example: mean 0.012 and standard deviation 0.004 suggest
// 0.012 + 0.012 = 0.024, inside X_OFFSET 0.05.
// The values are in the mapped range -1 to 1; one ADC count is
// 2 / 1023 = 0.002.
// FUNCTION NOTES (v6.3.0), placed at the end of the file so that the
// line numbers cited by the lab cards do not change. One block for each
// function of the lesson, in the order of the file.
// ---------------------------------------------------------------
// report (teaching notes, v6.3.0)
// Hint: report, print the statistics of one axis.
// Purpose: summarize 100 readings of one axis and suggest a dead zone.
// What is learnt:
//   Parameters     const char *axis is the text "x" or "y"; float *data
//                  points to the first of the 100 values; stepOffset is the
//                  offset of Step2_JUL for comparison.
//   Statistics<float> stats(data, size); declared inside the function:
//                  the object exists only until the function returns (a
//                  local, automatic object on the stack).
//   Getters        Average(), StandardDeviation(), Median(), GetSorted(0)
//                  (the minimum) and GetSorted(size - 1) (the maximum).
//   Rule of 3 sigma  |average| + 3 standard deviations covers about 99.7
//                  percent of the readings of a normal distribution.
// Expected output (bench, values depend on the joystick):
//   x  average: 0.0120  std dev: 0.0040  median: ...  min: ...  max: ...
//   x  suggested offset: 0.024  (Step2_JUL uses 0.05)
// ---------------------------------------------------------------
// ---------------------------------------------------------------
// Setup (teaching notes, v6.3.0)
// Hint: Setup, make the pins safe, then measure once.
// Purpose: the order of a safe start on the bench.
// What is learnt:
//   D5 to D10 are set to OUTPUT and LOW before anything else, so the
//   L298N inputs never float while the motor supply is on.
//   measure() is declared at the top of the file (a forward declaration,
//   void measure();) so Setup() can call it before its definition.
// ---------------------------------------------------------------
// ---------------------------------------------------------------
// Loop (teaching notes, v6.3.0)
// Hint: Loop, repeat on request.
// Purpose: a key typed in the serial monitor repeats the measurement.
// What is learnt:
//   Serial.available() returns the number of characters waiting.
//   The input is read and discarded so that the line ending does not
//   trigger a second measurement; delay(20) lets it arrive first.
// ---------------------------------------------------------------
// ---------------------------------------------------------------
// measure (teaching notes, v6.3.0)
// Hint: measure, take 100 readings of each axis.
// Purpose: sample the resting joystick, map it like Step2_JUL, and report.
// What is learnt:
//   Global arrays xs[] and ys[] (100 floats each, 800 bytes of RAM) hold
//   the samples; they are global so the stack stays small.
//   mapInput.Map() is the full range map of Step2_JUL, 0 to 1023 onto -1
//   to 1 (lesson 3); one ADC count is 0.002 after the map.
//   delay(10) spreads the 100 readings over about one second.
// ---------------------------------------------------------------
#endif // Lesson_L17_DeadZone_h
