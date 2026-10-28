//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: Class RandomNumber.h
// Folder: include/numerics
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
// RELEASE
//   2026-10-28  v6.8.0
//   RandomNumber.h last changed: 2026-10-22  v6.3.1
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

// RandomNumber<real>: random real numbers between a minimum and a maximum.
// Merged from MageMCU/Numerics (Algebra/include, 20241202).

#ifndef Numerics_Random_Number_h
#define Numerics_Random_Number_h

#include <Arduino.h>

namespace csjc
{
    // FIXED 20261008:
    // (1) The generator is seeded once, on the first call to Random(), from
    //     analogRead(A0) + analogRead(A1) + micros(). It was reseeded twice
    //     on every call, which was slow (two analogRead() calls, about
    //     0.2 ms) and made successive values correlated. Seeding at the
    //     first call (not in the constructor) also works for a global
    //     object, which is constructed before the ADC is enabled.
    // (2) The result is a real number in [min, max). The bounds were
    //     truncated to long, so (-1.9, 2.3) returned values in [-1, 2).
    // (3) The default constructor gives the range [0, 1); m_lastRandom
    //     (unused) was removed.
    // TEACHING NOTES (v6.1.1)
    // A computer makes pseudorandom numbers: a fixed formula produces a
    // sequence that looks random, and the seed, the number the sequence
    // starts from, decides which sequence. The same seed always gives the
    // same sequence. randomSeed() sets the seed; random(n) returns the next
    // whole number from 0 to n - 1.
    // Interval notation: [min, max) includes min and excludes max.
    // A uniform distribution gives every value in the interval the same
    // chance; lesson 6 (Statistics) measures the average and the standard
    // deviation of such values.
    template <typename real>
    class RandomNumber
    {
    public:
        // Constructor
        RandomNumber();
        RandomNumber(real minValue, real maxValue);
        ~RandomNumber() = default;

        // Methods
        real Random();

    private:
        // Properties
        real m_Min;
        real m_Max;
        bool m_seeded;

        // Methods
        void m_seed();
    };

    template <typename real>
    RandomNumber<real>::RandomNumber()
        : m_Min((real)0), m_Max((real)1), m_seeded(false)
    {
    }

    template <typename real>
    RandomNumber<real>::RandomNumber(real minValue, real maxValue)
        : m_Min(minValue), m_Max(maxValue), m_seeded(false)
    {
    }

    // Scaling: u is a fraction from 0 up to (not including) 1, and
    // min + (max - min) u moves it into [min, max). Example: min = -100,
    // max = 1000, u = 0.5 gives -100 + 1100 (0.5) = 450.
    template <typename real>
    real RandomNumber<real>::Random()
    {
        if (!m_seeded)
        {
            m_seed();
            m_seeded = true;
        }
        // random(n) returns a long in [0, n). Dividing by n gives a uniform
        // fraction u in [0, 1); the result is min + (max - min) * u.
        // FIXED 20261012: n is 2^24. A float holds every integer below 2^24
        // exactly, so u is always below 1. With n = 2^31 - 1 the division
        // could round up to exactly 1 and return max.
        const long n = 16777216L;
        real u = (real)random(n) / (real)n;
        return m_Min + (m_Max - m_Min) * u;
    }

    // Private Methods

    // The seed mixes two analog readings (they change a little with noise)
    // and micros(), the microseconds since reset, so each run starts a
    // different sequence.
    template <typename real>
    void RandomNumber<real>::m_seed()
    {
        unsigned long seed = (unsigned long)analogRead(A0);
        seed += (unsigned long)analogRead(A1);
        seed += micros();
        randomSeed(seed);
    }
}

#endif
