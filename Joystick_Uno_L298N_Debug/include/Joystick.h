//
// Carpenter Software
// File: Class Joystick.h (debug version)
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

#ifndef __UNO_JOYSTICK_H__
#define __UNO_JOYSTICK_H__

#include <Arduino.h>
#include "DEBUG.h"

// INPUT ADC READINGS
#define _ZERO 0
#define _MIDPOINT_LO 511
#define _MIDPOINT_HI 512
#define _1023 1023

// Using Adruino Uno
namespace uno
{
  class Joystick
  {
  private:
    // Properties /////////////////////////////////
    bool _ready;
    // Temp Debug Value
    int _octant;

    // Raw ADC Values
    int _rawX;
    int _rawY;
    // _1_alignRawInput()
    int _alignX;
    int _alignY;
    // _2_shiftFromZeroToMidpoint()
    int _shiftX;
    int _shiftY;
    // _3_adjustToDynamicFriction()
    int _dynamicX;
    int _dynamicY;
    // _4_convertToDouble
    double _doubleX;
    double _doubleY;
    // Motors Speeds
    double _normalLeft;
    double _normalRight;

    // Calibrate RAW Analog Data
    int _cntCalibration21;
    // Offset Joystick Center
    int _xCenterOffset;
    int _yCenterOffset;
    // Offset Static Friction
    int _xDynamicOffset;
    int _yDynamicOffset;
    // Methods ///////////////////////////////////
    void _dataJoystick();
    // Center Joystick
    boolean _centerCalibrated();
    // Align Raw Data
    void _1_alignRawInput();
    // Shift To Zero
    void _2_shiftFromZeroToMidpoint();
    // Adjust for static friction
    void _3_adjustToDynamicFriction();
    // Convert from integer to double
    void _4_convertToDouble();
    // Calculate Motors Speeds
    void _5_joystick();
    // Setup for Constructors
    void _debugConstructor(/* Debug Parameters */);
    void _allDebug(/* Debug Parameters */);

  public:
    // Constructor
    Joystick();
    // Methods ///////////////////////////////////
    // Debug Octants
    bool Ready();
    int GetOctantCondition();
    // Input - Analog Readings - ADC
    void UpdateInputs(int rawX, int rawY);
    double GetRawX();
    double GetRawY();
    // Output Motors Speeds with maximum PWM value
    // Arduino Uno & L298N = 255
    int GetOutputLeftInteger(int maxL298N_PWM);
    int GetOutputRightInteger(int maxL298N_PWM);
    // Output - Motors Speeds (for debug)
    double GetOutputLeft();
    double GetOutputRight();
  };

  // PUBLIC ///////////////////////////////////////////////
  Joystick::Joystick()
  {
    _dataJoystick();
  }

  bool Joystick::Ready()
  {
    return _ready;
  }

  int Joystick::GetOctantCondition()
  {
    // Used for Debugging
    return _octant;
  }

  double Joystick::GetRawX()
  {
    return _rawX;
  }

  double Joystick::GetRawY()
  {
    return _rawY;
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

  void Joystick::UpdateInputs(int const rawX, int const rawY)
  {
    // Assign Inputs
    _rawX = rawX;
    _rawY = rawY;

    // Ready (or not here we go)
    if (_cntCalibration21 < 22)
      _ready = false;
    else
      _ready = true;

#ifdef _dJ_
    if (_cntCalibration21 == 0)
      Serial.println("*** Calibrating ***");
#endif

    if (_centerCalibrated()) // Simple 21 count two point averaging
    {
      // Keep each step simple.
      _1_alignRawInput();           // IN - Align Center to MIDPOINT
      _2_shiftFromZeroToMidpoint(); // IN - Shift Center to ZERO
      _3_adjustToDynamicFriction(); // IN - Jump over static friction
      _4_convertToDouble();         // IN - Convert Integers to Doubles
      _5_joystick();                // OUT - Transform to normalized output
      _allDebug();
    }
  }

  // PRIVATE ////////////////////////////////////////////
  void Joystick::_dataJoystick()
  {
    _ready = false;
    // Calibration and Offsets
    _cntCalibration21 = 0;
    _debugConstructor(/* Debug Arguments */);
  }

  boolean Joystick::_centerCalibrated()
  {
    // Simple 21 count two point averaging
    if (_cntCalibration21 <= 21)
    {
      _xCenterOffset = ((_xCenterOffset + _rawX) / 2) + 1;
      _yCenterOffset = ((_yCenterOffset + _rawY) / 2) + 1;

#ifdef _dJ_
      Serial.print(_cntCalibration21);
      Serial.print(" _xC:");
      Serial.print(_xCenterOffset);
      Serial.print(" _yC:");
      Serial.println(_yCenterOffset);
#endif

      _cntCalibration21++;
      return false;
    }

    // Increment Value Remains at 22..., unless
    // MCU Reset.
    return true;
  }

  void Joystick::_1_alignRawInput()
  {
    int _x = _rawX;
    int _y = _rawY;

    if (_x >= _xCenterOffset)
    {
      // _x = (int)_util.Map(_x, _xCenterOffset, _1023, _MIDPOINT_HI, _1023);
      _x = (int)map(_x, _xCenterOffset, _1023, _MIDPOINT_HI, _1023);
    }
    else if (_x < _xCenterOffset)
    {
      // _x = (int)_util.Map(_x, _ZERO, (_xCenterOffset - 1), _ZERO, _MIDPOINT_LO);
      _x = (int)map(_x, _ZERO, (_xCenterOffset - 1), _ZERO, _MIDPOINT_LO);
    }

    if (_y >= _yCenterOffset)
    {
      // _y = (int)_util.Map(_y, _yCenterOffset, _1023, _MIDPOINT_HI, _1023);
      _y = (int)map(_y, _yCenterOffset, _1023, _MIDPOINT_HI, _1023);
    }
    else if (_y < _yCenterOffset)
    {
      // _y = (int)_util.Map(_y, _ZERO, (_yCenterOffset - 1), _ZERO, _MIDPOINT_LO);
      _y = (int)map(_y, _ZERO, (_yCenterOffset - 1), _ZERO, _MIDPOINT_LO);
    }

    _alignX = _x;
    _alignY = _y;
  }
  void Joystick::_2_shiftFromZeroToMidpoint()
  {
    // Offset to Center from 511 to zero
    _shiftX = _alignX - _MIDPOINT_LO;
    _shiftY = _alignY - _MIDPOINT_LO;
    // Center should now be (0,0)
  }

  void Joystick::_3_adjustToDynamicFriction()
  {
    int const _centerTolerance = 5;
    int _x = _shiftX;
    int _y = _shiftY;

    //  ------------------------------------------------------
    //  (Experimental Step)
    //  Calibrate by stepping over static friction (whinning
    //  motors) to dynamic friction (when motors actually start
    //  moving the robot under full load weight). The threshold
    //  values ought to be considered for other smooth solid
    //  surfaces (sss) like carpet. (Whinning motors uses a
    //  lot of energy.)
    //  RECORD digital ADC reading values as follows:
    //  -------------------------------------------------------
    //  motor      -      static      -      dynamic
    //                   whinning        movement for sss
    //  -------------------------------------------------------
    //  _xDynamicOffset (-)
    //                  (+)
    //  _yDynamicOffset (-)
    //                  (+)
    //  --------------------------------------------------------
    //
    // _xDynamicOffset = _centerTolerance; // Comment-out _centerTolerance and replace with
    // emperical dynamic value..., otherwise do not
    // touch
    _xDynamicOffset = 260; // Author's  (suggest you change this)
    if (_x >= _centerTolerance)
    {
      // _x = (int)_util.Map(_x, 0, 512, _xDynamicOffset, 512);
      _x = (int)map(_x, 0, 512, _xDynamicOffset, 512);
    }
    else if (_x < -_centerTolerance)
    {
      // _x = (int)_util.Map(_x, 0, -511, -_xDynamicOffset, -511);
      _x = (int)map(_x, 0, -511, -_xDynamicOffset, -511);
    }
    else
    {
      _x = 0;
    }
    //
    // _yDynamicOffset = _centerTolerance; // Comment-out _centerTolerance and replace with
    // emperical dynamic value..., otherwise do not
    // touch.
    _yDynamicOffset = 260; // Author's  (suggest you change this)
    if (_y >= _centerTolerance)
    {
      // _y = (int)_util.Map(_y, _ZERO, _MIDPOINT_HI, _yDynamicOffset, _MIDPOINT_HI);
      _y = (int)map(_y, _ZERO, _MIDPOINT_HI, _yDynamicOffset, _MIDPOINT_HI);
    }
    else if (_y < -_centerTolerance)
    {
      // _y = (int)_util.Map(_y, _ZERO, -_MIDPOINT_LO, -_yDynamicOffset, -_MIDPOINT_LO);
      _y = (int)map(_y, _ZERO, -_MIDPOINT_LO, -_yDynamicOffset, -_MIDPOINT_LO);
    }
    else
    {
      _y = 0;
    }

    _dynamicX = _x;
    _dynamicY = _y;
  }

  void Joystick::_4_convertToDouble()
  {
    _doubleX = (double)_dynamicX / (double)_MIDPOINT_HI;
    _doubleY = (double)_dynamicY / (double)_MIDPOINT_HI;
  }

  void Joystick::_5_joystick()
  {
    double const _tol = 0.04;
    // Assign Processed Doubles
    double const _inputX = _doubleX;
    double const _inputY = _doubleY;
    // The Method uses DOUBLE TYPE so
    // the method should be tested for
    // performance. OK...
    double _x = 0;
    double _y = 0;

    // (1) Delta
    // Absolute difference of the absolute values of the inputs.
    double delta = abs(abs(_inputX) - abs(_inputY));

    // (2) Conditionals
    if (abs(_inputX) > _tol && abs(_inputY) > _tol)
    {
      // Y-Dominator
      if (abs(_inputX) <= abs(_inputY))
      {
        if (_inputX > _ZERO && _inputY > _ZERO)
        {
          _x = _inputY;
          _y = delta;
          // Octant 2
          _octant = 2;
        }
        else if (_inputX > _ZERO && _inputY < _ZERO)
        {
          _x = -delta;
          _y = _inputY;
          // Octant 7
          _octant = 7;
        }
        else if (_inputX < _ZERO && _inputY > _ZERO)
        {
          _x = delta;
          _y = _inputY;
          // Octant 3
          _octant = 3;
        }
        else if (_inputX < _ZERO && _inputY < _ZERO)
        {
          _x = _inputY;
          _y = -delta;
          // Octant 6
          _octant = 6;
        }
        // X-Dominator
      }
      else if (abs(_inputX) > abs(_inputY))
      {
        if (_inputX > _ZERO && _inputY > _ZERO)
        {
          _x = _inputX;
          _y = -delta;
          // Octant 1
          _octant = 1;
        }
        else if (_inputX > _ZERO && _inputY < _ZERO)
        {
          _x = delta;
          _y = -_inputX;
          // Octant 8
          _octant = 8;
        }
        else if (_inputX < _ZERO && _inputY > _ZERO)
        {
          _x = -delta;
          _y = -_inputX;
          // Octant 4
          _octant = 4;
        }
        else if (_inputX < _ZERO && _inputY < _ZERO)
        {
          _x = _inputX;
          _y = delta;
          // Octant 5
          _octant = 5;
        }
      }
    }
    else if (abs(_inputX) > _tol && abs(_inputY) < _tol)
    {
      _x = _inputX;
      _y = -_inputX;
      // input x is greater than zero and input y is zero
      _octant = 110;
    }
    else if (abs(_inputX) < _tol && abs(_inputY) > _tol)
    {
      _x = _inputY;
      _y = _inputY;
      // input x is zero and y is greater than zero
      _octant = 101;
    }
    else if (abs(_inputX) < _tol && abs(_inputY) < _tol)
    {
      _x = 0;
      _y = 0;
      // input x and y are zero
      _octant = 100;
    }

    _normalLeft = _x;
    _normalRight = _y;
  }

  void Joystick::_debugConstructor(/* Debug Parameters */)
  {
#ifdef _dJ_

    // Used simply whether or not
    // Constructor Instantiated Joystick CLASS
    Serial.println("Joystick");
// Write Serial Prints Here...
#endif
  }

  void Joystick::_allDebug(/* Debug Parameters */)
  {
#ifdef _dJ_
    Serial.println("*** Joystick ***");
    // Write Serial Prints Here...

    Serial.println("ANALOG IN");
    Serial.print(" X:");
    Serial.print(_rawX);
    Serial.print(" Y:");
    Serial.println(_rawY);

#ifdef _ALIGN_
    Serial.println("1 ALIGN IN");
    Serial.print(" X:");
    Serial.print(_alignX);
    Serial.print(" Y:");
    Serial.println(_alignY);
#endif
#ifdef _SHIFT_
    Serial.println("2 SHIFT IN");
    Serial.print(" X:");
    Serial.print(_shiftX);
    Serial.print(" Y:");
    Serial.println(_shiftY);
#endif
#ifdef _DYNAMIC_
    Serial.println("3 DYNAMIC IN");
    Serial.print(" X:");
    Serial.print(_dynamicX);
    Serial.print(" Y:");
    Serial.println(_dynamicY);
#endif
#ifdef _DOUBLE_
    Serial.println("4 DOUBLE IN");
    Serial.print(" X:");
    Serial.print(_doubleX);
    Serial.print(" Y:");
    Serial.println(_doubleY);
#endif
#ifdef _NORMAL_
    // Joystick NORMALIZED Readings
    // from -1 to 1...
    // OK if Test Values.
    // Hands-Off          ---------
    // (x, y) = (0, 0)    not-Octant 100 = (0, 0)
    // Up (Forward)       ---------
    // (x, y) = (1, 1))   not-Octant 101 = (0, y)
    // Down (Backward)    ---------
    // (x, y) = (-1, -1)) not-Octant 101 = (0, y)
    // Left               ---------
    // (x, y) = (-1, 1))  not-Octant 110 = (x, 0)
    // Right              ---------
    // (x, y) = (1, -1))  not-Octant 110 = (x, 0)
    // Starting Right, octants should read CCW(1 to 8).
    // Octant values - ignore
    // If OK - Go To L298N
    // SEE DEBUG.h

    Serial.println("5 MOTORS OUT");
    Serial.print(" Octant:");
    Serial.print(_octant);
    Serial.print(" X:");
    Serial.print(_normalLeft);
    Serial.print(" Y:");
    Serial.println(_normalRight);
#endif
#endif
  }
}
#endif
