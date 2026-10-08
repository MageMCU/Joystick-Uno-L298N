//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: Class LinearMap.h
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

// LinearMap<T>: straight line mapping of x in [x1, x2] onto y in [y1, y2].
// Step2_JUL uses LinearMap<float> for ADC to unit range and unit range to PWM.

#ifndef Numerics_Linear_Map_h
#define Numerics_Linear_Map_h

#include <Arduino.h>

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    // typename T can be either a real or an integer
    template <typename T>
    class LinearMap
    {
    private:
        // Private Properties
        // Point-1
        T m_x1;
        T m_y1;
        // Point-2
        T m_x2;
        T m_y2;

    public:
        // Constructor
        LinearMap() = default;
        // REVIEW 20261008: argument order is (x1, x2, y1, y2): both x values first,
        // then both y values. It is not the point order (x1, y1, x2, y2).
        // x1 must differ from x2 (Map divides by x2 - x1), and y1 must differ
        // from y2 for Reverse().
        LinearMap(T x1, T x2, T y1, T y2);
        ~LinearMap() = default;

        // Methods
        T Map(T x);
        // REVIEW 20261008: the parameter is a y value; the definition below names it y.
        T Reverse(T x);
        T Map(T x, T x1, T x2, T y1, T y2);
    };

    template <typename T>
    LinearMap<T>::LinearMap(T x1, T x2, T y1, T y2)
    {
        // Point-1
        m_x1 = x1;
        m_y1 = y1;
        // Point-2
        m_x2 = x2;
        m_y2 = y2;
    }

    // REVIEW 20261008: with an integer type the product (y2 - y1) * (x - x1) is
    // computed in that type. On the Uno an int is 16 bits, so
    // LinearMap<int>(0, 1023, -255, 255).Map(65) overflows (510 * 65 = 33150
    // > 32767). Use float, or long for integer maps of ADC values. Integer
    // division also truncates toward zero.
    template <typename T>
    T LinearMap<T>::Map(T x)
    {
        return (m_y2 - m_y1) * (x - m_x1) / (m_x2 - m_x1) + m_y1;
    }

    template <typename T>
    T LinearMap<T>::Reverse(T y)
    {
        return (m_x2 - m_x1) * (y - m_y1) / (m_y2 - m_y1) + m_x1;
    }

    // REVIEW 20261008: same formula as Map() in MiscMath.h.
    template <typename T>
    T LinearMap<T>::Map(T x, T x1, T x2, T y1, T y2)
    {
        // Assume linear functions
        // Point-1 (x1, y1)
        // Point-2 (x2, y2)
        // Slope: m = (y2 - y1)/(x2 - x1)
        // Point-Slope: (y - y1) = m(x - x1)
        //               y = m(x - x1) + y1
        return (y2 - y1) * (x - x1) / (x2 - x1) + y1;
    }
}

#endif
