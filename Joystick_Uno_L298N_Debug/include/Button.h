//
// Carpenter Software
// File: Class Button.h (debug version)
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
// Timer Class was adapted from Arduino's
// Debounce Sketch Example.

#ifndef __UNO_BUTTON_H__
#define __UNO_BUTTON_H__

#include <Arduino.h>

#define DEBOUNCE_TIME 75

namespace uno
{
  class Button
  {
  private:
    int _ledPin;
    int _ledState;
    int _buttonPin;
    int _buttonState;
    int _lastButtonState;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay;

    void _data();
    void _pins();
    void _button();

    void _debugConstructor(/* Debug Parameters */);
    void _allDebug(/* Debug Parameters */);

  public:
    Button();
    Button(int buttonPin);
    Button(int buttonPin, int ledPin);

    bool isButtonOn();
    void updateButton();
  };

  // Constructor
  Button::Button()
  {
    _pins();
    _data();
  }

  // Constructor
  Button::Button(int buttonPin)
  {
    _pins();
    _data();
    _buttonPin = buttonPin;
  }

  // Constructor
  Button::Button(int buttonPin, int ledPin)
  {
    _pins();
    _data();
    _buttonPin = buttonPin;
    _ledPin = ledPin;
  }

  // PUBLIC method: Is the Button On = HIGH
  bool Button::isButtonOn()
  {
    return _ledState == HIGH;
  }

  // PUBLIC method: updateButton (used in the Arduino loop() function)
  void Button::updateButton()
  {
    _button();

    _allDebug(/* Debug Arguments */);
  }

  // Private Method
  void Button::_data()
  {
    _buttonPin = 2;
    _ledPin = 13;
    // Begin the current state LOW of the output pin
    _ledState = LOW;
    // the previous reading from the input pin
    _lastButtonState = HIGH;
    _lastDebounceTime = 0;
    _debounceDelay = DEBOUNCE_TIME;
  }

  // Private Method
  void Button::_pins()
  {
    pinMode(_buttonPin, INPUT);
    pinMode(_ledPin, OUTPUT);
  }

  // Private Method
  void Button::_button()
  {
    int currentState = digitalRead(_buttonPin);
    long currentTime = millis();

    // If the switch changed, due to noise or pressing:
    if (currentState != _lastButtonState)
    {
      // reset the debouncing timer
      _lastDebounceTime = currentTime;
    }

    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    if ((currentTime - _lastDebounceTime) > _debounceDelay)
    {
      // if the button state has changed:
      if (currentState != _buttonState)
      {
        // Add the current reading from the input pin
        _buttonState = currentState;

        // only toggle the LED if the new button state is HIGH
        if (_buttonState == HIGH)
        {
          _ledState = !_ledState;
        }
      }
    }

    // set the LED:
    digitalWrite(_ledPin, _ledState);

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    _lastButtonState = currentState;
  }

  void Button::_debugConstructor(/* Debug Parameters */)
  {
#ifdef _dB_
    // Used simply whether or not
    // Constructor Instantiated Button CLASS
    Serial.println("Button");
    // Write Serial Prints Here...
#endif
  }

  void Button::_allDebug(/* Debug Parameters */)
  {
#ifdef _dB_
    // Write Serial Prints Here...
#endif
  }
}
#endif
