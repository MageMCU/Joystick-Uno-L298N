//
// Carpenter Software
// File: L03_LinearMap.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L03_LinearMap, selected with LESSON 3 in
// Step5_MathLessons/main.cpp
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestLinearMap.h (merged 20261008)
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
// RELEASE
//   2026-10-28  v6.8.0
//   L03_LinearMap.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

// TEACHING NOTES (v6.1.1)
// Lesson 3: the linear map. The formula, its terms (slope, point slope
// form), and an example from Step2_JUL are in
// include/numerics/LinearMap.h, at Map() and Reverse().
// The example map is the temperature scale: water freezes at 32 F and
// 0 C and boils at 212 F and 100 C, so LinearMap<float>(32, 212, 0, 100)
// turns Fahrenheit into Celsius: C = (F - 32) 100 / 180.
// Inclusive means the map also works outside the two points: -40 F gives
// -40 C, and 1000 F gives 537.8 C.
// The topics run T01 to T03 (see Setup()); T01 and T02 use random
// values (lesson 5), so the numbers differ on each run.
#ifndef Lesson_L03_LinearMap_h
#define Lesson_L03_LinearMap_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 3

#include <Arduino.h>
#include "Debug.h"
#include "numerics/LinearMap.h"
#include "numerics/RandomNumber.h"

namespace L03_LinearMap
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// T02: each value goes through Map() and back through Reverse(); the
// second line of each pair should show the original Fahrenheit value
// again (to the 2 decimals printed).
// ---------------------------------------------------------------
// LinearMap_T02_Reverse (teaching notes, v6.3.0)
// Hint: Reverse, the inverse map, from y back to x.
// Purpose: to show that Reverse() undoes Map(), the test of an inverse
// function: Reverse(Map(F)) = F.
// What is learnt:
//   Inverse        x = x1 + (y - y1) (x2 - x1) / (y2 - y1), the same line
//                  solved for x. One object holds both directions.
//   Round trip test: convert, convert back, compare with the start. Any
//                  difference is rounding of float (about 7 digits).
//   The loop runs 50 times with random inputs, so negative Fahrenheit
//   values (below 32 F, below 0 C) are tested as well.
// Expected output (random values; 50 pairs), after the same two input
// lines as T01 (v6.4.1):
//    map: Fahrenheit: 556.80 -> Celsius: 291.56
//    reverse: Celsius: 291.56 -> Fahrenheit: 556.80
//   The second line of each pair repeats the first Fahrenheit value.
// ---------------------------------------------------------------
void LinearMap_T02_Reverse()
{
    printTitle(F("LinearMap T02 Reverse"));

    // Constructor
    LinearMap<float> mapCelcius =
        LinearMap<float>(32, 212, 0, 100);
    // Random Float
    // The constructor inputs an integer (int) type
    // while RandomReal() outputs a real (float)...
    RandomNumber<float> random =
        RandomNumber<float>((float)-100, (float)1000);
    // v6.4.1: print the two points of the map and the input range.
    Serial.println(F( \
        "LinearMap<float>(32, 212, 0, 100): 32 F -> 0 C, 212 F -> 100 C"));
    Serial.println(F( \
        "RandomNumber<float>(-100, 1000): Fahrenheit inputs from -100 to " \
        "1000"));
    // Test - Looking for negative values
    float celcius;
    float fahrenheit;
    for (int i = 0; i < 50; i++)
    {
        fahrenheit = random.Random();
        // Space
        Serial.println("");
        // Map
        Serial.print(" map: ");
        // Save Values
        celcius = mapCelcius.Map(fahrenheit);
        printResults("Fahrenheit: ", fahrenheit, " -> Celsius: ", celcius);
        // Reverse
        Serial.print(" reverse: ");
        // Reverse Values
        fahrenheit = mapCelcius.Reverse(celcius);
        printResults("Celsius: ", celcius, " -> Fahrenheit: ", fahrenheit);
    }
}

// T01: ten random Fahrenheit values from -100 to 1000 and their Celsius
// values. Check one by hand with C = (F - 32) 100 / 180.
// ---------------------------------------------------------------
// LinearMap_T01_Inclusive (teaching notes, v6.3.0)
// Hint: Inclusive, the map holds for every input, also outside the two
// points that define it.
// Purpose: how to declare a LinearMap and use Map() to convert values
// from one scale to another (Fahrenheit to Celsius).
// What is learnt:
//   Instantiation with arguments: LinearMap<float>(32, 212, 0, 100)
//                  calls the constructor with the two points (x1, y1) =
//                  (32, 0) and (x2, y2) = (212, 100). The form
//                  LinearMap<float> m = LinearMap<float>(...); builds a
//                  temporary object and copies it into m; the shorter
//                  form LinearMap<float> m(32, 212, 0, 100); does the same.
//   Linear map     y = y1 + (x - x1) (y2 - y1) / (x2 - x1); the slope here
//                  is 100 / 180.
//   Extrapolation  using the line beyond x1 and x2; inclusive means the
//                  class allows it (-40 F gives -40 C).
//   RandomNumber<float>(-100, 1000) supplies test inputs (lesson 5).
// Expected output (random values, different on each run):
//   LinearMap<float>(32, 212, 0, 100): 32 F -> 0 C, 212 F -> 100 C
//   RandomNumber<float>(-100, 1000): Fahrenheit inputs from -100 to 1000
//   (v6.4.1: the inputs of the topic, printed first), then
//   ten lines of the form  fahrenheit: 680.18 - Celsius: 360.10
//   Check one: (680.18 - 32) x 100 / 180 = 360.10.
// ---------------------------------------------------------------
void LinearMap_T01_Inclusive()
{
    printTitle(F("LinearMap T01 Inclusive"));

    // Constructor
    LinearMap<float> mapCelcius =
        LinearMap<float>(32, 212, 0, 100);
    // Random Float
    // The constructor inputs an integer (int) type
    // while RandomReal() outputs a real (float)...
    RandomNumber<float> random =
        RandomNumber<float>((float)-100, (float)1000);
    // v6.4.1: print the two points of the map and the input range.
    Serial.println(F( \
        "LinearMap<float>(32, 212, 0, 100): 32 F -> 0 C, 212 F -> 100 C"));
    Serial.println(F( \
        "RandomNumber<float>(-100, 1000): Fahrenheit inputs from -100 to " \
        "1000"));
    // Test
    float celcius;
    float fahrenheit;
    for (int i = 0; i < 10; i++)
    {
        fahrenheit = random.Random();
        // ---------------- Normal Mapping
        celcius = mapCelcius.Map(fahrenheit);
        printResults("fahrenheit: ", fahrenheit, " - Celsius: ", celcius);
    }
}

// Topic 3 (v6.1.0): the two segment map. A joystick axis seldom rests
// at 511 or reaches 0 and 1023 at its ends; the Step1_Joystick self
// test measures the low, center, and high readings of each axis. One
// straight line cannot pass through all three points, so the map has
// two segments: low to center onto -1 to 0, and center to high onto 0
// to 1. constrain() keeps a reading beyond low or high inside -1 to 1.
// Step2_JUL maps the full range instead, 0 to 1023 onto -1 to 1, and
// its dead zone (X_OFFSET 0.05) absorbs a small center offset; the
// table compares the two maps. Lesson 20 shows both on the live joystick.
// ---------------------------------------------------------------
// LinearMap_T03_TwoSegment (teaching notes, v6.3.0)
// Hint: TwoSegment, a map made of two straight lines joined at the
// center reading.
// Purpose: to compare the full range map of Step2_JUL with the measured
// two segment map of the Step1_Joystick report, for one joystick axis.
// What is learnt:
//   Piecewise linear map: a different line on each side of a break
//                  point; here the break point is the center reading.
//   const float    a named constant; the compiler refuses any change.
//   Array initializer  const int raws[] = {...}; the compiler counts the
//                  elements.
//   constrain(v, a, b)  Arduino function that limits v to a to b.
//   Self check     the topic counts its own failures: the two segment
//                  map must give exactly -1, 0, and 1 at low, center, and
//                  high.
//   dtostrf()      the AVR C library function that writes a float as
//                  text, right aligned in a field of fixed width, so the
//                  table lines up in every serial monitor (v6.3.1).
// Expected output:
//   low 12  center 498  high 1010
//      raw  full range  two segment
//        0      -1.000       -1.000
//      498      -0.026        0.000
//     1010       0.975        1.000
//   (eight rows in all)
//   Failures: 0
// ---------------------------------------------------------------
void LinearMap_T03_TwoSegment()
{
    printTitle(F("LinearMap T03 Two Segment"));

    // Example values of a Step1_Joystick report for one axis
    const float low = 12;
    const float center = 498;
    const float high = 1010;

    LinearMap<float> fullRange = LinearMap<float>(0, 1023, -1, 1);
    LinearMap<float> belowCenter = LinearMap<float>(low, center, -1, 0);
    LinearMap<float> aboveCenter = LinearMap<float>(center, high, 0, 1);

    Serial.print(F("low "));
    Serial.print(low, 0);
    Serial.print(F("  center "));
    Serial.print(center, 0);
    Serial.print(F("  high "));
    Serial.println(high, 0);
    // Columns of fixed width (v6.3.1; tabs up to v6.3.0, Discrepancies.md,
    // 192): raw 6 characters, full range 12, two segment 13.
    Serial.println(F("   raw  full range  two segment"));

    const int raws[] = {0, 12, 255, 498, 511, 754, 1010, 1023};
    int failures = 0;
    for (int i = 0; i < 8; i++)
    {
        float raw = (float)raws[i];
        float full = fullRange.Map(raw);
        float two;
        if (raw < center)
            two = belowCenter.Map(raw);
        else
            two = aboveCenter.Map(raw);
        two = constrain(two, -1.0, 1.0);

        // dtostrf(value, width, decimals, buffer), of the AVR C library,
        // writes a number as text right aligned in a field of the given
        // width, so each column lines up under its heading.
        char text[16];
        Serial.print(dtostrf(raw, 6, 0, text));
        Serial.print(dtostrf(full, 12, 3, text));
        Serial.println(dtostrf(two, 13, 3, text));

        // The two segment map gives exactly -1, 0, and 1 at the
        // measured low, center, and high readings
        if (raw == low && two != -1.0)
            failures++;
        if (raw == center && two != 0.0)
            failures++;
        if (raw == high && two != 1.0)
            failures++;
    }
    // At the center the full range map gives -0.026, inside the dead
    // zone of 0.05; at the high end it gives 0.975, or 248 of the 255
    // PWM steps. The two segment map gives 0 and 1.
    Serial.print(F("Failures: "));
    Serial.println(failures);
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    LinearMap_T01_Inclusive();
#endif
#if TOPIC == 0 || TOPIC == 2
    LinearMap_T02_Reverse();
#endif
#if TOPIC == 0 || TOPIC == 3
    LinearMap_T03_TwoSegment();
#endif
}

void Loop()
{
}
// namespace L03_LinearMap
}

// Lesson_L03_LinearMap_h
#endif
