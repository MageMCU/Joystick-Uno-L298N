//
// Carpenter Software
// File: Class Timer.h
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

#ifndef SJUL_Uno_Timer_h
#define SJUL_Uno_Timer_h

#include <Arduino.h>

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    class Timer
    {
    private:
        // Private Properties
        long t_currentTime;
        long t_elapsedTime;
        long t_deltaTime;

    public:
        // Constructors
        Timer();
        ~Timer() = default;

        // Methods
        void resetTimer();
        float DeltaTimeSeconds();
        boolean isTimer(long incrementedTime);
    };

    Timer::Timer()
    {
        t_elapsedTime = 0;
    }

    void Timer::resetTimer()
    {
        t_elapsedTime = -1;
    }

    float Timer::DeltaTimeSeconds()
    {
        return (float)t_deltaTime * 0.0010;
    }

    boolean Timer::isTimer(long incrementedTime)
    {
        t_currentTime = millis();
        if (t_elapsedTime == -1)
        {
            t_elapsedTime = t_currentTime + incrementedTime;
        }
        else if (t_currentTime > t_elapsedTime)
        {
            t_elapsedTime = t_currentTime + incrementedTime;
            // DeltaTime at incremmentedTime
            t_deltaTime = t_elapsedTime - t_currentTime;
            return true;
        }
        return false;
    }
}
#endif
