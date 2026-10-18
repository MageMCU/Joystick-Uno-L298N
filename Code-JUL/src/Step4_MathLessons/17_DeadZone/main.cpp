//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: src/Step4_MathLessons/17_DeadZone
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
// the range -1 to 1 exactly as Step1_JUL does, and prints
// the average, the standard deviation, and the median of each axis. The
// suggested offset is |average| + 3 standard deviations: a resting grip
// then falls inside the dead zone for nearly every reading. Compare it
// with X_OFFSET (0.05) and Y_OFFSET (0.06) in Step1_JUL.
//
// Send any key in the serial monitor to repeat the measurement. Do not
// press the Uno reset button while the bench supply is applied: D5 to D10
// float between a reset and the first statement of setup().

#include <Arduino.h>
#include "numerics/LinearMap.h"
#include "numerics/Statistics.h"

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
    Serial.print("  (Step1_JUL uses ");
    Serial.print(stepOffset, 2);
    Serial.println(")");
}

void setup()
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
void loop()
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
        // The two analogRead() lines of Step1_JUL since v3.1.0
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
