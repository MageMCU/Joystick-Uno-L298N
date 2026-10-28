//
// Carpenter Software
// File: L05_RandomNumber.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L05_RandomNumber, selected with LESSON 5 in
// Step5_MathLessons/main.cpp
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestRandomNumber.h (merged
// 20261008)
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

// TEACHING NOTES (v6.1.1)
// Lesson 5: pseudorandom numbers. The seed, the interval [min, max), and
// the scaling of a fraction into the interval are explained in
// include/numerics/RandomNumber.h.
#ifndef Lesson_L05_RandomNumber_h
#define Lesson_L05_RandomNumber_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 1

#include <Arduino.h>
#include "Debug.h"
#include "numerics/RandomNumber.h"

namespace L05_RandomNumber
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// T01: 100 values in [0, 10), printed with 2 decimals. They change on
// every run because the seed mixes analog noise and micros(). A value
// of exactly 10.00 should never appear. Lesson 6 measures such values:
// for [0, 10) the mean is near 5 and the standard deviation near 2.9
// (10 / sqrt(12) for a uniform distribution).
// ---------------------------------------------------------------
// RandomNumber_T01_Random (teaching notes, v6.3.0)
// Hint: Random, draw the next pseudorandom value.
// Purpose: how to declare a RandomNumber object for an interval and draw
// values from it, the test data of lessons 3 and 6.
// What is learnt:
//   Instantiation  RandomNumber<float>((float)0, (float)10): the template
//                  argument <float> gives fractional values; <int> would
//                  give whole numbers. The casts make both bounds float.
//   Pseudorandom   a sequence computed by a formula that only looks
//                  random; the seed, its starting value, decides the whole
//                  sequence. The class seeds from analog noise and
//                  micros(), so each run differs.
//   Half open interval [0, 10): 0 can appear, 10 cannot.
//   Method call    randomNumber.Random() returns the next value; it takes
//                  no argument because the bounds are stored in the object.
//   String(x)      a float printed through String() has 2 decimals.
// Expected output (different on each run):
//   RandomNumber<float>(0, 10): 100 values, 0 up to (not including) 10
//   then 100 lines:
//   values such as 6.89, 7.44, 6.27, all from 0.00 to 9.99
// ---------------------------------------------------------------
void RandomNumber_T01_Random()
{
    printTitle(F("RandomNumber T01 Random"));

    RandomNumber<float> randomNumber = RandomNumber<float>((float)0, (float)10);
    // v6.4.1: print the interval and the number of values.
    Serial.println(F( \
        "RandomNumber<float>(0, 10): 100 values, 0 up to (not including) 10"));

    int cnt = 0;
    while (cnt < 100)
    {
        // Small range - buggy - OK
        Serial.println(String(randomNumber.Random()));
        cnt++;
    }
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    RandomNumber_T01_Random();
#endif
}

void Loop()
{
}
// namespace L05_RandomNumber
}

// Lesson_L05_RandomNumber_h
#endif
