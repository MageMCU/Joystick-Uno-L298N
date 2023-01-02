//
// Carpenter Software
// File: Class Timer.h
// Folder: Simplified-Joystick-Uno-L298N (SJUL)
//
// Purpose: Github Depository (MageMCU)
//
// Algebra OOP Library
// The math is underneath the namespace
// nmr for Numerics as in numeric computation.
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
// Using Adruino Uno

namespace uno
{
  class Timer
  {
  private:
    // Private Properties
    long t_currentTime;
    long t_elapsedTime;

  public:
    // Constructors
    Timer();
    ~Timer() = default;

    // Methods
    void resetTimer();
    boolean isTimer(int incrementedTime);
  };

  Timer::Timer()
  {
    t_elapsedTime = 0;
  }

  void Timer::resetTimer()
  {
    t_elapsedTime = -1;
  }

  boolean Timer::isTimer(int incrementedTime)
  {
    t_currentTime = millis();

    if (t_elapsedTime == -1)
    {
      t_elapsedTime = t_currentTime + (long)incrementedTime;
    }
    else if (t_currentTime > t_elapsedTime)
    {
      t_elapsedTime = t_currentTime + (long)incrementedTime;
      return true;
    }
    return false;
  }
}
#endif
