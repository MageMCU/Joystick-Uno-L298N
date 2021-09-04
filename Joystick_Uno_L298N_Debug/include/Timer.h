//
// Carpenter Software
// File: Class Timer.h (debug version)
// Folder: joystick_L298N_debug
// Purpose: Github Depository (MageMCU)
//
// Teacher's and Parent's copy...
// Dedicated to Parents and Teachers of the USA.
// Teachers Note: The _BEGIN_DEBUG is defined (see
//                DEBUG.h file), also MAIN _ANALOG_
//                is defined for debugging the
//                analog readings. For safety
//                reasons while debugging, the
//                motors are conditioned not to
//                operate. Be warned. the Student's
//                copy has no safety feature.
//
// Hardware
// MCU: Atmega328P (Microchip)
// * Board: Arduino Uno (Italy)
// Thumb Joystick: (China)
// Motor Driver: L298N (ST)
// * Motor Module: (China)
// 12V Geared Motors (ratio 1:75) (China)
// Note: motors: current peaks on average 1.14 amps
//       for static friction, and it levels down to
//       about 0.29 amps for dynamic friction. When
//       joystick with hands-off (center position),
//       is about 0.10 amps. The robot was sitting
//       on stand with no weight on wheels, otherwise,
//       the electrical currents would have increased.
// Battery 12V - APX1250 (12V 5.0Ah) Sealed Lead-Acid
// Note: battery: with five years design life (using
//       now for 7 years.) Requires special battery
//       charger from APEX.
//
// By Jesse Carpenter (Github as MageMCU)
//
// CHANGELOG
// August 30, 2021 - debug comments
// August 24, 2021 - editing
// June 19, 2021 - programming debug version
//
// Atmega328P Total Usgae
// RAM : [==] 15.3 % (used 314 bytes from 2048 bytes)
// Flash : [==] 21.2 % (used 6846 bytes from 32256 bytes)
//
// MIT LICENSE
//

#ifndef __UNO_TIMER_H__
#define __UNO_TIMER_H__

#include <Arduino.h>
#include "DEBUG.h"

// Using Adruino Uno
namespace uno
{
  class Timer
  {
  private:
    long _elapsedTime;
    long _lastMillisecond;

    void _debugConstructor(/* Debug Parameters */);
    void _allDebug(/* Debug Parameters */);

  public:
    Timer();
    void resetTimer();
    boolean isTimer(int incrementedTime);
  };

  Timer::Timer()
  {
    _elapsedTime = -1;
    _lastMillisecond = 0;

    _debugConstructor(/* Debug Arguments */);
  }

  void Timer::resetTimer()
  {
    _elapsedTime = -1;
  }

  boolean Timer::isTimer(int incrementedTime)
  {
    long currentTime = millis();
    if (_elapsedTime == -1)
    {
      _elapsedTime = currentTime + (long)incrementedTime;
    }
    else if (currentTime > _elapsedTime)
    {
      _elapsedTime = currentTime + (long)incrementedTime;
      return true;
    }
    return false;
  }

  void Timer::_debugConstructor(/* Debug Parameters */)
  {
#ifdef _dT_
    // Used simply whether or not
    // Constructor Instantiated Timer CLASS
    Serial.println("Timer");
    // Write Serial Prints Here...
#endif
  }

  void Timer::_allDebug(/* Debug Parameters */)
  {
#ifdef _dT_
    // Write Serial Prints Here...
#endif
  }
}
#endif
