//
// Carpenter Software
// File: Class Switch.h
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

#ifndef Switch_h
#define Switch_h

#include <Arduino.h>

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    class Switch
    {
    private:
        int m_ledPin;
        int m_ledState;

        // Switch
        // Use a GND single wire as a switch
        int m_switchPin;
        bool m_switchOn;

        void m_data();
        void m_pins();
        void m_switch();

    public:
        Switch();
        Switch(int switchPin);
        Switch(int switchPin, int ledPin);
        ~Switch() = default;

        bool isSwitchOn();
        void updateSwitch();
    };

    // Constructor
    Switch::Switch()
    {
        m_pins();
        m_data();
    }

    // Constructor
    Switch::Switch(int switchPin)
    {
        m_pins();
        m_data();
        m_switchPin = switchPin;
    }

    // Constructor
    Switch::Switch(int switchPin, int ledPin)
    {
        m_pins();
        m_data();
        m_switchPin = switchPin;
        m_ledPin = ledPin;
    }

    // PUBLIC method: Is the Switch On = HIGH
    bool Switch::isSwitchOn()
    {
        return m_switchOn;
    }

    // PUBLIC method: updateButton (used in the Arduino loop() function)
    void Switch::updateSwitch()
    {
        m_switch();
    }

    // Private Method
    void Switch::m_data()
    {
        m_switchPin = 2;
        m_ledPin = 13;
    }

    // Private Method
    void Switch::m_pins()
    {
        // INSTRUCTIONS ------------------------- README
        // (1) Use 10K Ohm resistor as pulldown
        // to GND with wire attached to
        // m_switchPin as OFF...
        // (2) Use 5V wire as switch placed
        // between m_switchPin-wire and
        // resistor as ON... Pull-Out
        // 5V wire to switch off...
        pinMode(m_switchPin, INPUT);
        pinMode(m_ledPin, OUTPUT);
    }

    // Private Method
    void Switch::m_switch()
    {
        // Digital Read
        m_ledState = digitalRead(m_switchPin);

        if (m_ledState == HIGH)
        {
            // Switch is ON
            // wire is attached
            m_switchOn = true;
            digitalWrite(m_ledPin, HIGH);
        }
        else
        {
            // Switch is OFF
            // wire is not attached
            m_switchOn = false;
            digitalWrite(m_ledPin, LOW);
        }
    }
}
#endif