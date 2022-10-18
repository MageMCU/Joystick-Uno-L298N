//
// Carpenter Software
// File: Timer.h (release version)
// Date: 20210830
// Folder: joystick_L298N_debug
// Purpose: Github Depository (MageMCU)
//
// Student Use...
//
// Hardware (For further information, see Debug Version)
//
// RAM:   [          ]   3.4% (used 69 bytes from 2048 bytes)
// Flash: [==        ]  15.2% (used 4890 bytes from 32256 byt
//
// MIT LICENSE
//

#ifndef __UNO_TIMER_H__
#define __UNO_TIMER_H__

#include <Arduino.h>
// Using Adruino Uno

namespace uno
{
  class Timer
  {
  private:
    long _elapsedTime;
    long _lastMillisecond;

  public:
    Timer();
    void resetTimer();
    boolean isTimer(int incrementedTime);
  };

  Timer::Timer()
  {
    _elapsedTime = -1;
    _lastMillisecond = 0;
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
}
#endif
