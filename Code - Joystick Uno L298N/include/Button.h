//
// Carpenter Software
// File: Class Button.h
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

#ifndef SJUL_Uno_Button_h
#define SJUL_Uno_Button_h

#include <Arduino.h>

#define DEBOUNCE_TIME 75

// Carpenter Software - Jesse Carpenter
namespace csjc
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

    public:
        Button();
        Button(int buttonPin);
        Button(int buttonPin, int ledPin);
        ~Button() = default;

        bool isButtonOn();
        void updateButton();
    };

    // Constructor
    Button::Button()
    {
        // Setup Private DATA Variables
        _data();
        // Arduino pins should the last setup step
        _pins();
    }

    // Constructor
    Button::Button(int buttonPin)
    {
        // Setup Private Variables
        _data();
        _buttonPin = buttonPin;
        // Arduino pins should the last setup step
        _pins();
    }

    // Constructor
    Button::Button(int buttonPin, int ledPin)
    {
        // Setup Private Variables
        _data();
        _buttonPin = buttonPin;
        _ledPin = ledPin;
        // Arduino pins should the last setup step
        _pins();
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
    }

    // Private Method
    void Button::_data()
    {
        // Default Button and LED
        _buttonPin = 2;
        _ledPin = 13;
        // Begin the current state LOW of the output pin
        _ledState = LOW;
        // the previous reading from the input pin
        _lastButtonState = HIGH;
        _lastDebounceTime = 0;
        // DEBOUNCE_TIME : arbitrary definition
        _debounceDelay = DEBOUNCE_TIME;
    }

    // Private Method
    void Button::_pins()
    {
        // Arduino pins should the last setup step
        // Arduino.h wiring pins pinMode()
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
}
#endif
