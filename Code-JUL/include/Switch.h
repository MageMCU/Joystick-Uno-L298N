//
// Carpenter Software
// File: Class Switch.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL
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

#ifndef Switch_h
#define Switch_h

#include <Arduino.h>

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    // Reads an active-high switch wired with an external pull-down resistor.
    // Pin setup is deferred until begin() or the first updateSwitch() call.
    class Switch
    {
    private:
        int m_ledPin;
        int m_switchPin;
        bool m_switchOn;
        bool m_begun;

    public:
        Switch()
            : m_ledPin(13), m_switchPin(2), m_switchOn(false), m_begun(false)
        {
        }

        explicit Switch(int switchPin)
            : m_ledPin(13), m_switchPin(switchPin), m_switchOn(false), m_begun(false)
        {
        }

        Switch(int switchPin, int ledPin)
            : m_ledPin(ledPin), m_switchPin(switchPin), m_switchOn(false), m_begun(false)
        {
        }

        ~Switch() = default;

        void begin()
        {
            pinMode(m_switchPin, INPUT);
            pinMode(m_ledPin, OUTPUT);
            m_begun = true;
            updateSwitch();
        }

        bool isSwitchOn() const
        {
            return m_switchOn;
        }

        void updateSwitch()
        {
            if (!m_begun)
            {
                begin();
                return;
            }

            m_switchOn = digitalRead(m_switchPin) == HIGH;
            digitalWrite(m_ledPin, m_switchOn ? HIGH : LOW);
        }
    };
}
#endif
