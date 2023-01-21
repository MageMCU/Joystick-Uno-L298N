//
// Carpenter Software
// File: Class Joystick.h
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

#ifndef SJUL_Uno_Joystick_Algorithm_h
#define SJUL_Uno_Joystick_Algorithm_h

#include <Arduino.h>

namespace uno
{
  // Joystick Class (Simplified for upcoming projects...)
  template<typename real>
  class Joystick
  {
  private:
    // PROPERTIES
    real j_ZERO;
    // INPUT
    real j_inputX;
    real j_inputY;
    // OUTPUT
    real j_outputLeft;
    real j_outputRight;
    // METHODS
    void j_joystick();

  public:
    // Constructor
    Joystick();
    ~Joystick() = default;
    // Getters
    bool IsLeftForward();
    bool IsRightForward();
    // METHODS
    void UpdateInputs(real inputX, real inputY);
    real OutLeft();
    real OutRight();
  };

  // Constructor
  template<typename real>
  Joystick<real>::Joystick()
  {
    j_ZERO = (real)0;
  }

  // Getters
  template<typename real>
  bool Joystick<real>::IsLeftForward()
  {
    return j_outputLeft > (real)0;
  }

  template<typename real>
  bool Joystick<real>::IsRightForward()
  {
    return j_outputRight > (real)0;
  }

  // Method update
  template<typename real>
  void Joystick<real>::UpdateInputs(real inputX, real inputY)
  {
    // Input values -1 <= X <= 1
    if (inputX >= -1 && inputX <= 1)
      j_inputX = inputX;
    // Input values -1 <= Y <= 1
    if (inputY >= -1 && inputY <= 1)
      j_inputY = inputY;

    // Private
    j_joystick();
  }

  // Method output
  template<typename real>
  real Joystick<real>::OutLeft()
  {
    return j_outputLeft;
  }

  // Method output
  template<typename real>
  real Joystick<real>::OutRight()
  {
    return j_outputRight;
  }

  // Private Method
  template<typename real>
  void Joystick<real>::j_joystick()
  {
    // Assume Noisy Analogs
    real const _tol = 0.04;

    // Input Values
    real const _inputX = j_inputX;
    real const _inputY = j_inputY;

    // Initialize x & y
    real _x = 0;
    real _y = 0;

    // Delta Equation
    real delta = abs(abs(_inputX) - abs(_inputY));

    // Consitionals
    if (abs(_inputX) > _tol && abs(_inputY) > _tol)
    {
      // Y-Dominator
      if (abs(_inputX) <= abs(_inputY))
      {
        if (_inputX > j_ZERO && _inputY > j_ZERO)
        {
          _x = _inputY;
          _y = delta;
        }
        else if (_inputX > j_ZERO && _inputY < j_ZERO)
        {
          _x = -delta;
          _y = _inputY;
        }
        else if (_inputX < j_ZERO && _inputY > j_ZERO)
        {
          _x = delta;
          _y = _inputY;
        }
        else if (_inputX < j_ZERO && _inputY < j_ZERO)
        {
          _x = _inputY;
          _y = -delta;
        }
      } // X-Dominator
      else if (abs(_inputX) > abs(_inputY))
      {
        if (_inputX > j_ZERO && _inputY > j_ZERO)
        {
          _x = _inputX;
          _y = -delta;
        }
        else if (_inputX > j_ZERO && _inputY < j_ZERO)
        {
          _x = delta;
          _y = -_inputX;
        }
        else if (_inputX < j_ZERO && _inputY > j_ZERO)
        {
          _x = -delta;
          _y = -_inputX;
        }
        else if (_inputX < j_ZERO && _inputY < j_ZERO)
        {
          _x = _inputX;
          _y = delta;
        }
      }
    }
    else if (abs(_inputX) > _tol && abs(_inputY) < _tol)
    {
      // Left & Right Turns
      _x = _inputX;
      _y = -_inputX;
    }
    else if (abs(_inputX) < _tol && abs(_inputY) > _tol)
    {
      // Forward & Backward
      _x = _inputY;
      _y = _inputY;
    }
    else if (abs(_inputX) < _tol && abs(_inputY) < _tol)
    {
      // Stop
      _x = 0;
      _y = 0;
    }

    j_outputLeft = _x;
    j_outputRight = _y;
  }
}
#endif
