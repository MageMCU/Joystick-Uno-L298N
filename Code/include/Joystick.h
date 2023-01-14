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
  // The enumeration is used for Arduino Uno
  // for the 10-bit Analog Digital Conversion 
  // (ADC: 0 - 1023)...
  enum {
    _ZERO = 0,
    _MIDPOINT_LO = 511,
    _MIDPOINT_HI = 512,
    _1023 = 1023
  };
  // Joystick Class (Simplified for upcoming
  // projects...)
  template<typename real>
  class Joystick
  {
  private:
    // INPUT
    real j_inputX;
    real j_inputY;
    // OUTPUT
    real j_outputLeft;
    real j_outputRight;

    void j_joystick();

  public:
    Joystick();
    ~Joystick() = default;

    void UpdateInputs(real inputX, real inputY);

    real OutLeft();
    real OutRight();
  };

  template<typename real>
  Joystick<real>::Joystick() {}

  template<typename real>
  real Joystick<real>::OutLeft()
  {
    return j_outputLeft;
  }

  template<typename real>
  real Joystick<real>::OutRight()
  {
    return j_outputRight;
  }

  template<typename real>
  void Joystick<real>::UpdateInputs(real inputX, real inputY)
  {
    // Input values -1 <= X <= 1
    if (inputX >= -1 && inputX <= 1)
      j_inputX = inputX;
    // Input values -1 <= Y <= 1
    if (inputY >= -1 && inputY <= 1)
      j_inputY = inputY;

    //
    j_joystick();
  }

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
      if (abs(_inputX) <= abs(_inputY))
      {
        if (_inputX > _ZERO && _inputY > _ZERO)
        {
          _x = _inputY;
          _y = delta;
        }
        else if (_inputX > _ZERO && _inputY < _ZERO)
        {
          _x = -delta;
          _y = _inputY;
        }
        else if (_inputX < _ZERO && _inputY > _ZERO)
        {
          _x = delta;
          _y = _inputY;
        }
        else if (_inputX < _ZERO && _inputY < _ZERO)
        {
          _x = _inputY;
          _y = -delta;
        }
      }
      else if (abs(_inputX) > abs(_inputY))
      {
        if (_inputX > _ZERO && _inputY > _ZERO)
        {
          _x = _inputX;
          _y = -delta;
        }
        else if (_inputX > _ZERO && _inputY < _ZERO)
        {
          _x = delta;
          _y = -_inputX;
        }
        else if (_inputX < _ZERO && _inputY > _ZERO)
        {
          _x = -delta;
          _y = -_inputX;
        }
        else if (_inputX < _ZERO && _inputY < _ZERO)
        {
          _x = _inputX;
          _y = delta;
        }
      }
    }
    else if (abs(_inputX) > _tol && abs(_inputY) < _tol)
    {
      _x = _inputX;
      _y = -_inputX;
    }
    else if (abs(_inputX) < _tol && abs(_inputY) > _tol)
    {
      _x = _inputY;
      _y = _inputY;
    }
    else if (abs(_inputX) < _tol && abs(_inputY) < _tol)
    {
      _x = 0;
      _y = 0;
    }

    j_outputLeft = _x;
    j_outputRight = _y;
  }
}
#endif
