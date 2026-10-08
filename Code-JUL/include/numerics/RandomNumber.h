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
        const long n = 2147483647L;
        real u = (real)random(n) / (real)n;
        return m_Min + (m_Max - m_Min) * u;
    }

    // Private Methods

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
