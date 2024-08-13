//
// Carpenter Software
// File: Class LinearMap.h
// Github: MageMCU
// Repository: Joystick-UNO-L298N
// Folder: Code
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
        LinearMap(T x1, T x2, T y1, T y2);
        ~LinearMap() = default;

        // Methods
        T Map(T x);
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
