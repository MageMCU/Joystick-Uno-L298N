//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: L20_JoystickMap.h
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L20_JoystickMap, selected with LESSON 20 in
// Step5_MathLessons/main.cpp
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
// RELEASE
//   2026-10-28  v6.8.0
//   L20_JoystickMap.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//
// Lesson 20 (v6.1.0): the full range map and the two segment map on
// the live joystick. Wiring: Article 1009, Circuit-1, with the motor
// supply off; D5 to D10 are held LOW.
//
// Step2_JUL and Step4_Generated map each reading with one straight
// line, 0 to 1023 onto -1 to 1, which assumes the center is 511, and
// then set values inside the dead zone (X_OFFSET 0.05, Y_OFFSET 0.06)
// to 0. Since v6.4.0 Step4_Generated (ace.h) first moves each reading
// by the center of include/JoystickCenter.h; Step2_JUL does not. Lesson 3,
// topic 3, introduces the two segment map: low to
// center onto -1 to 0, center to high onto 0 to 1, from the readings
// that the Step1_Joystick self test measures.
//
// Before the upload, copy the low and high readings of A0 and A1 from
// a Step1_Joystick report into the four constants below; the two
// centers are read from include/JoystickCenter.h (v6.4.1), the file
// the reader copied from the same report.
// Once per second the lesson prints, for each axis, the raw reading,
// the full range map, the full range map after the dead zone, and the
// two segment map. Leave the grip at rest, then hold it at each edge.
// At rest the full range map gives 0.000 after the dead zone, and the
// two segment map gives about 0.000 once the values are copied in.
// At an edge the two segment map gives -1.000 or 1.000, and the full
// range map a little less when the end stops short of 0 or 1023.

#ifndef Lesson_L20_JoystickMap_h
#define Lesson_L20_JoystickMap_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 1

#include <Arduino.h>
#include "Timer.h"
#include "numerics/LinearMap.h"
// v6.4.1: the centers printed by Step1_Joystick
#include "JoystickCenter.h"

namespace L20_JoystickMap
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// ---------- Copy these from a Step1_Joystick report ----------
// v6.4.1: the two centers come from include/JoystickCenter.h, the
// file Step1_Joystick prints and the reader copies (shipped 511, 511);
// copy only the four low and high values below.
const float A0_LOW = 0;
const float A0_CENTER = JOYSTICK_A0_CENTER;
const float A0_HIGH = 1023;
const float A1_LOW = 0;
const float A1_CENTER = JOYSTICK_A1_CENTER;
const float A1_HIGH = 1023;
// --------------------------------------------------------------

// The dead zones of Step2_JUL (X_OFFSET and Y_OFFSET)
const float X_OFFSET = 0.05;
const float Y_OFFSET = 0.06;

Timer timer;
LinearMap<float> fullRange;
LinearMap<float> belowA0;
LinearMap<float> aboveA0;
LinearMap<float> belowA1;
LinearMap<float> aboveA1;

// Two segment map of one reading, held inside -1 to 1
// TEACHING NOTES (v6.1.1): a reference parameter (LinearMap<float> &)
// passes the caller's object itself instead of a copy, which saves RAM
// and time; the formula of each segment is LinearMap.h, Map(), and the
// two segment map is worked out in lesson 3, topic 3.
float twoSegment(float raw, float center, LinearMap<float> &below,
                 LinearMap<float> &above)
{
    float value;
    if (raw < center)
        value = below.Map(raw);
    else
        value = above.Map(raw);
    return constrain(value, -1.0, 1.0);
}

// The dead zone of Step2_JUL: a full range value closer to 0 than the
// offset is set to 0 (fabs() is the absolute value of a float).
void printAxis(const __FlashStringHelper *name, int raw, float full,
               float offset, float two)
{
    float dead = full;
    if (fabs(dead) < offset)
        dead = 0;
    Serial.print(name);
    Serial.print(F("  raw "));
    Serial.print(raw);
    Serial.print(F("  full range "));
    Serial.print(full, 3);
    Serial.print(F("  after dead zone "));
    Serial.print(dead, 3);
    Serial.print(F("  two segment "));
    Serial.println(two, 3);
}

// v6.4.1: prints the low, center, and high of one axis and its dead
// zone offset, the inputs of the maps compared below.
void printConstants(const __FlashStringHelper *name, float low, float center,
                    float high, float offset)
{
    Serial.print(name);
    Serial.print(F("  low "));
    Serial.print(low, 0);
    Serial.print(F("  center "));
    Serial.print(center, 0);
    Serial.print(F("  high "));
    Serial.print(high, 0);
    Serial.print(F("  dead zone offset "));
    Serial.println(offset, 2);
}

// Topic 1: the live joystick, called from Loop()
// ---------------------------------------------------------------
// JoystickMap_T01_LiveCompare (teaching notes, v6.3.0)
// Hint: LiveCompare, two maps of the same live reading side by side.
// Purpose: show on the real joystick why the measured two segment map
// reaches exactly -1, 0, and 1, and how the dead zone hides a small
// center offset in the full range map.
// What is learnt:
//   Two maps, one input: fullRange.Map() (Step2_JUL) and twoSegment()
//                  (the Step1_Joystick measurements, lesson 3, T03).
//   Constants from measurement: the four low and high values at the top
//                  of the file are copied from the Step1_Joystick report
//                  before upload; the two centers come from
//                  include/JoystickCenter.h (v6.4.1).
//   Objects declared globally and assigned in Setup(): belowA0 =
//                  LinearMap<float>(...); builds each map once.
//   F() text and a dotted line mark each new output.
//   Called from Loop(), once per second through timer.isTimer(1000).
// Expected output (bench, grip at rest, values copied in):
//   A0  low 12  center 498  high 1010  dead zone offset 0.05
//   A1  low 8  center 523  high 1015  dead zone offset 0.06
//   Centers: include/JoystickCenter.h; low and high: this file
//   (v6.4.1: the constants, printed once), then once per second
//   A0  raw 508  full range -0.007  after dead zone 0.000  two segment 0.000
//   At an edge the two segment column reads -1.000 or 1.000.
// ---------------------------------------------------------------
void JoystickMap_T01_LiveCompare()
{
    if (timer.isTimer(1000))
    {
        int rawA0 = analogRead(A0);
        int rawA1 = analogRead(A1);
        // A blank line and a dotted line mark the start of each new output
        Serial.println();
        Serial.println(F("................................................"));
        printAxis(F("A0"), rawA0, fullRange.Map((float)rawA0), X_OFFSET,
                  twoSegment((float)rawA0, A0_CENTER, belowA0, aboveA0));
        printAxis(F("A1"), rawA1, fullRange.Map((float)rawA1), Y_OFFSET,
                  twoSegment((float)rawA1, A1_CENTER, belowA1, aboveA1));
    }
}

void Setup()
{
    // Hold the six L298N inputs LOW before the motor supply is applied
    // (Article 1009, Safety and Supervision, item 4)
    for (int pin = 5; pin <= 10; pin++)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
    Serial.begin(9600);
    while (!Serial)
    {
    }

    fullRange = LinearMap<float>(0, 1023, -1, 1);
    belowA0 = LinearMap<float>(A0_LOW, A0_CENTER, -1, 0);
    aboveA0 = LinearMap<float>(A0_CENTER, A0_HIGH, 0, 1);
    belowA1 = LinearMap<float>(A1_LOW, A1_CENTER, -1, 0);
    aboveA1 = LinearMap<float>(A1_CENTER, A1_HIGH, 0, 1);

    Serial.println(F( \
        "JoystickMap T01 Live Compare: full range and two segment maps"));
    // v6.4.1: the constants of the two maps and of the dead zone.
    printConstants(F("A0"), A0_LOW, A0_CENTER, A0_HIGH, X_OFFSET);
    printConstants(F("A1"), A1_LOW, A1_CENTER, A1_HIGH, Y_OFFSET);
    Serial.println(F( \
        "Centers: include/JoystickCenter.h; low and high: this file"));
    timer.resetTimer();
}

void Loop()
{
#if TOPIC == 0 || TOPIC == 1
    JoystickMap_T01_LiveCompare();
#endif
}
// namespace L20_JoystickMap
}

// Lesson_L20_JoystickMap_h
#endif
