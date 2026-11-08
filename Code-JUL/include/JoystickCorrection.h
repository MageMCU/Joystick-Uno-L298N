//
// Carpenter Software
// File: Class JoystickCorrection.h
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
// RELEASE
//   2026-11-07  v7.4.0
//   JoystickCorrection.h added: 2026-11-07  v7.4.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//
// Layout: every line fits the cutoff of 80 characters, and each comment
// is written on its own line above the statement it explains.
//
// -------------------------------------------------------------------------
// THE JOYSTICK CORRECTION (v7.4.0)
// A thumb joystick seldom rests at exactly 511, the middle of the ADC
// range 0 to 1023, and seldom reaches 0 and 1023 at its ends.
// Step1_Joystick measures the low end, the center, and the high end of
// each axis and prints them in include/JoystickMeasurements.h. One
// JoystickCorrection object holds the three values of one axis and
// corrects each raw reading of that axis:
//   above the center  CENTER to HIGH - INSET becomes 511 to 1023
//   below the center  LOW + INSET to CENTER becomes 0 to 511
// A reading past an inset end is held at 0 or 1023, and the measured
// center reads 511. The ends are moved in by INSET (10 counts), as in
// Step1_Joystick and include/claude/ace.h, so a normal push still
// reaches the full reading.
//
// For a reading r of an axis with low end L, center C, and high end H:
//   r >= C   corrected = 511 + 512 * (r - C) / ((H - INSET) - C)
//   r <  C   corrected = 511 - 511 * (C - r) / (C - (L + INSET))
// The division is an integer division, which drops the fraction.
//
// WHY A SEPARATE FILE
// include/JoystickMeasurements.h is printed by Step1_Joystick and is
// replaced as a whole after each passing self test, so it holds the
// measured values only. This file holds the class and is never replaced.
//
// WHERE IT IS USED
//   Step2_JUL  two objects, correctX for A0 and correctY for A1, made in
//              setup() from the values of JoystickMeasurements.h, and
//              one call of Correct() for each reading in updateJoystick().
//
// THE CONTROL TICK
// The two spans are computed once, when the object is made in setup(),
// so each call of Correct() in the control tick is one multiplication
// and one division, a few tens of microseconds on the Uno, small beside
// the 100 ms tick of Step2_JUL (3000 ms with a debug switch defined).
//
// USAGE
//   #include "JoystickCorrection.h"
//   JoystickCorrection correctX;
//   void setup()
//   {
//       correctX = JoystickCorrection(JOYSTICK_A0_LOW,
//                                     JOYSTICK_A0_CENTER,
//                                     JOYSTICK_A0_HIGH);
//   }
//   int xDigital = correctX.Correct(analogRead(A0));
// -------------------------------------------------------------------------

#ifndef JoystickCorrection_h
#define JoystickCorrection_h

#include <Arduino.h>
// The Step1 measurements of the joystick
#include "JoystickMeasurements.h"

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    // The ends are moved in by this many counts
    const int JOYSTICK_INSET = 10;

    class JoystickCorrection
    {
    private:
        // The measured center of the axis, in raw ADC counts
        int m_center;
        // Counts from the center to the inset high end
        long m_spanHigh;
        // Counts from the inset low end to the center
        long m_spanLow;

    public:
        // Default: the uncorrected range 0, 511, 1023 with no inset
        JoystickCorrection()
        {
            m_center = 511;
            m_spanHigh = 512;
            m_spanLow = 511;
        }

        // One axis: its measured low end, center, and high end
        JoystickCorrection(int low, int center, int high)
        {
            m_center = center;
            m_spanHigh = (long)(high - JOYSTICK_INSET) - center;
            m_spanLow = (long)center - (low + JOYSTICK_INSET);
        }

        // A raw reading, 0 to 1023, to the corrected reading, 0 to 1023
        int Correct(int raw) const
        {
            long value;
            if (raw >= m_center)
                value = 511L + 512L * (raw - m_center) / m_spanHigh;
            else
                value = 511L - 511L * (m_center - raw) / m_spanLow;
            return (int)constrain(value, 0L, 1023L);
        }
    };
}

#endif
