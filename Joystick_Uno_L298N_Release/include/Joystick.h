//
// Carpenter Software
// File: Joystick.h (release version)
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

#ifndef __UNO_JOYSTICK_H__
#define __UNO_JOYSTICK_H__

#include <Arduino.h>

#define _ZERO 0
#define _MIDPOINT_LO 511
#define _MIDPOINT_HI 512
#define _1023 1023

namespace uno
{
  class Joystick
  {
  private:
    bool _ready;

    int _processX;
    int _processY;

    double _normalLeft;
    double _normalRight;
    int _cntCalibration21;
    int _xCenterOffset;
    int _yCenterOffset;
    int _xDynamicOffset;
    int _yDynamicOffset;

    void _dataJoystick();
    bool _centerCalibrated();
    void _alignRawInput();
    void _shiftFromZeroToMidpoint();
    void _adjustToDynamicFriction();
    void _joystick();

  public:
    Joystick();
    bool UpdateInputs(int rawX, int rawY);
    int GetOutputLeftInteger(int maxL298N_PWM);
    int GetOutputRightInteger(int maxL298N_PWM);
    double GetOutputLeft();
    double GetOutputRight();
  };
  Joystick::Joystick()
  {
    _dataJoystick();
  }

  double Joystick::GetOutputLeft()
  {
    return _normalLeft;
  }

  double Joystick::GetOutputRight()
  {
    return _normalRight;
  }

  int Joystick::GetOutputLeftInteger(int maxL298N_PWM)
  {
    return (int)(_normalLeft * (double)maxL298N_PWM);
  }

  int Joystick::GetOutputRightInteger(int maxL298N_PWM)
  {
    return (int)(_normalRight * (double)maxL298N_PWM);
  }

  bool Joystick::UpdateInputs(int const rawX, int const rawY)
  {
    _processX = rawX;
    _processY = rawY;
    if (_cntCalibration21 < 22)
      _ready = false;
    else
      _ready = true;
    if (_centerCalibrated())
    {
      _alignRawInput();
      _shiftFromZeroToMidpoint();
      _adjustToDynamicFriction();
      _joystick();
    }
    return _ready;
  }

  void Joystick::_dataJoystick()
  {
    _ready = false;
    _cntCalibration21 = 0;
  }

  boolean Joystick::_centerCalibrated()
  {
    if (_cntCalibration21 <= 21)
    {
      _xCenterOffset = ((_xCenterOffset + _processX) / 2) + 1;
      _yCenterOffset = ((_yCenterOffset + _processY) / 2) + 1;
      _cntCalibration21++;
      return false;
    }
    return true;
  }

  void Joystick::_alignRawInput()
  {
    int _x = _processX;
    int _y = _processY;
    if (_x >= _xCenterOffset)
    {
      _x = (int)map(_x, _xCenterOffset, _1023, _MIDPOINT_HI, _1023);
    }
    else if (_x < _xCenterOffset)
    {
      _x = (int)map(_x, _ZERO, (_xCenterOffset - 1), _ZERO, _MIDPOINT_LO);
    }

    if (_y >= _yCenterOffset)
    {
      _y = (int)map(_y, _yCenterOffset, _1023, _MIDPOINT_HI, _1023);
    }
    else if (_y < _yCenterOffset)
    {
      _y = (int)map(_y, _ZERO, (_yCenterOffset - 1), _ZERO, _MIDPOINT_LO);
    }
    _processX = _x;
    _processY = _y;
  }
  void Joystick::_shiftFromZeroToMidpoint()
  {
    _processX -= _MIDPOINT_LO;
    _processY -= _MIDPOINT_LO;
  }

  void Joystick::_adjustToDynamicFriction()
  {
    int const _centerTolerance = 5;
    int _x = _processX;
    int _y = _processY;

    _xDynamicOffset = 260;
    if (_x >= _centerTolerance)
    {
      _x = (int)map(_x, 0, 512, _xDynamicOffset, 512);
    }
    else if (_x < -_centerTolerance)
    {
      _x = (int)map(_x, 0, -511, -_xDynamicOffset, -511);
    }
    else
    {
      _x = 0;
    }
    _yDynamicOffset = 260;
    if (_y >= _centerTolerance)
    {
      _y = (int)map(_y, _ZERO, _MIDPOINT_HI, _yDynamicOffset, _MIDPOINT_HI);
    }
    else if (_y < -_centerTolerance)
    {
      _y = (int)map(_y, _ZERO, -_MIDPOINT_LO, -_yDynamicOffset, -_MIDPOINT_LO);
    }
    else
    {
      _y = 0;
    }
    _processX = _x;
    _processY = _y;
  }

  void Joystick::_joystick()
  {
    double const _tol = 0.04;

    double const _inputX = (double)_processX / (double)_MIDPOINT_HI;
    double const _inputY = (double)_processY / (double)_MIDPOINT_HI;

    double _x = 0;
    double _y = 0;
    double delta = abs(abs(_inputX) - abs(_inputY));
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

    _normalLeft = _x;
    _normalRight = _y;
  }
}
#endif
