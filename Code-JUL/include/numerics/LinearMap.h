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
// RELEASE
//   2026-10-28  v6.8.0
//   LinearMap.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
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
    // TEACHING NOTES (v6.1.1)
    // A linear map turns a value x in one range into the value y at the
    // same proportion of another range: the straight line through the two
    // points (x1, y1) and (x2, y2). The constructor stores the two points;
    // Map() goes from x to y and Reverse() from y back to x.
    // Step2_JUL: LinearMap<float>(0, 1023, -1.0, 1.0) turns an ADC reading
    // into the joystick input -1 to 1, and LinearMap<float>(-1.0, 1.0,
    // -255, 255) turns the joystick output into a PWM command.
    // T is the type parameter of the template: float for fractions, or
    // long for whole numbers (see the overflow note at Map()).
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
        // REVIEW 20261008: argument order is (x1, x2, y1, y2): both x values
        // first,
        // then both y values. It is not the point order (x1, y1, x2, y2).
        // x1 must differ from x2 (Map divides by x2 - x1), and y1 must differ
        // from y2 for Reverse().
        LinearMap(T x1, T x2, T y1, T y2);
        ~LinearMap() = default;

        // Methods
        T Map(T x);
        // REVIEW 20261008: the parameter is a y value; the definition below
        // names it y.
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
    // Map(x): the straight line through the points (x1, y1) and (x2, y2),
    // evaluated at x.
    //   slope        m = (y2 - y1) / (x2 - x1), the change in y for a
    //                change of 1 in x
    //   point slope  y - y1 = m (x - x1), a line from one point and
    //                its slope
    // so y = (y2 - y1) (x - x1) / (x2 - x1) + y1. The multiplication
    // comes first and the division last, so an integer type keeps its
    // precision to the end (see the overflow note above).
    // Example (Step2_JUL): x1 = 0, x2 = 1023, y1 = -1, y2 = 1, so
    // Map(767) = 2 (767) / 1023 - 1 = 0.4995.
    template <typename T>
    T LinearMap<T>::Map(T x)
    {
        return (m_y2 - m_y1) * (x - m_x1) / (m_x2 - m_x1) + m_y1;
    }

    // Reverse(y): the inverse map, the same line solved for x:
    // x = (x2 - x1) (y - y1) / (y2 - y1) + x1. Map() and then Reverse()
    // returns the original value (lesson 3, topic 2). Example: with the
    // points above, Reverse(0.4995) = 767.
    template <typename T>
    T LinearMap<T>::Reverse(T y)
    {
        return (m_x2 - m_x1) * (y - m_y1) / (m_y2 - m_y1) + m_x1;
    }

    // REVIEW 20261008: same formula as Map() in MiscMath.h.
    // The same formula with the two points passed in each call, for a map
    // used once.
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
