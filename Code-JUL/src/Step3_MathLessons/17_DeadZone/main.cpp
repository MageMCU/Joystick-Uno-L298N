//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: src/Step3_MathLessons/17_DeadZone
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
// Wiring: the joystick of Article 1004, Experiment-2 (no motor power).
// Leave the grip at rest. The program takes 100 readings of each axis,
// maps them into the range -1 to 1 exactly as Step2_JUL does, and prints
// the average, the standard deviation, and the median of each axis. The
// suggested offset is |average| + 3 standard deviations: a resting grip
// then falls inside the dead zone for nearly every reading. Compare it
// with X_OFFSET (0.05) and Y_OFFSET (0.06) in Step2_JUL.
//
// Press the Uno reset button to repeat the measurement.

#include <Arduino.h>
#include "numerics/LinearMap.h"
#include "numerics/Statistics.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

const int size = 100;
float xs[size];
float ys[size];
LinearMap<float> mapInput(0, 1023, -1.0, 1.0);

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

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println(F("Lesson 17: joystick at rest, 100 readings per axis"));

    for (int i = 0; i < size; i++)
    {
        // Use the two analogRead() lines recorded in Experiment-2
        int xDigital = analogRead(A1);
        int yDigital = analogRead(A0);
        xs[i] = mapInput.Map((float)xDigital);
        ys[i] = mapInput.Map((float)yDigital);
        delay(10); // 100 readings over about one second
    }

    report("x", xs, 0.05);
    report("y", ys, 0.06);
}

void loop()
{
}
