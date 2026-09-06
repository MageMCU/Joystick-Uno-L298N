//
// Carpenter Software
// File: Class Button.h
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

#ifndef SJUL_Uno_Button_h
#define SJUL_Uno_Button_h

#include <Arduino.h>

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    // Debounced push button with an optional indicator LED.
    //
    // The hardware is a momentary-contact switch: it conducts only while
    // it is physically pressed and springs open when released. The class
    // turns that raw contact into a clean, debounced on/off state.
    //
    // Debouncing: a mechanical contact does not close cleanly. For a few
    // milliseconds after a press or release the pin level chatters between
    // HIGH and LOW. The class ignores a new pin level until it has held
    // steady for debounceMs milliseconds, then accepts it as the real state.
    //
    // On/off state: isButtonOn() reports an internal on/off flag, and the
    // indicator LED follows that flag. How the flag behaves depends on the
    // mode selected with setLatching():
    //
    //   Latching mode        Each accepted press toggles the flag. Press
    //   (default)            once for ON, press again for OFF. The flag
    //                        holds its value while the button is released,
    //                        like a push-on, push-off power switch.
    //
    //   Momentary mode       The flag is ON only while the button is held
    //                        down and returns to OFF on release (after the
    //                        debounce window, like the press). This is the
    //                        dead-man arrangement: motors run only while the
    //                        operator keeps the button pressed.
    //
    // In both modes the flag starts OFF after power-up or a reset, so
    // nothing driven by isButtonOn() is enabled until a deliberate press.
    //
    // isPressed() reports the debounced held-down state regardless of mode,
    // wasPressed() reports a single press event and then clears it, and
    // heldForMs() reports how long the button has been held down.
    //
    // Wiring (default, activeLow = true): the joystick SW pin closes to GND
    // when pressed. The button pin is configured INPUT_PULLUP, so it reads
    // LOW while pressed and HIGH when released. No external resistor is
    // required. For a button wired to 5V with an external pulldown resistor,
    // construct with activeLow = false; the pin is then configured INPUT and
    // HIGH means pressed.
    //
    // Lifecycle: construct at global scope, call begin() once in setup(),
    // and call updateButton() once per pass through loop(). pinMode() is
    // deferred to begin() so that no hardware is touched before the Arduino
    // runtime has initialized. If begin() is not called, the first
    // updateButton() calls it.
    //
    // All timing uses unsigned long and subtraction, so the class is safe
    // across the millis() rollover (about every 49.7 days).
    //
    // Standalone usage (no other header required):
    //
    //   Button button(2, 3);   // SW on D2, indicator LED on D3
    //
    //   void setup()
    //   {
    //       button.begin();
    //   }
    //
    //   void loop()
    //   {
    //       button.updateButton();
    //
    //       if (button.isButtonOn())
    //       {
    //           // insert your code here (runs every pass while ON)
    //       }
    //   }
    //
    // Usage with Timer (see Timer.h). The timer paces the work so that it
    // runs at a fixed interval instead of on every pass:
    //
    //   Button button(2, 3);   // SW on D2, indicator LED on D3
    //   Timer  timer;
    //
    //   void setup()
    //   {
    //       button.begin();
    //   }
    //
    //   void loop()
    //   {
    //       // Sample the button on every pass. updateButton() is cheap
    //       // (one digitalRead) and must run often for debouncing to work.
    //       button.updateButton();
    //
    //       // Run the timed work once per interval (milliseconds).
    //       if (timer.isTimer(250))
    //       {
    //           if (button.isButtonOn())
    //           {
    //               // insert your timed code here (latched ON)
    //           }
    //           else
    //           {
    //               // insert your timed code here (latched OFF)
    //           }
    //       }
    //
    //       // Optional: react to the press itself, independent of the timer.
    //       if (button.wasPressed())
    //       {
    //           // insert your press-event code here
    //       }
    //   }
    //
    // Alternate: momentary (dead-man) mode. Call setLatching(false) once in
    // setup(). The loop() above is unchanged; isButtonOn() is now true only
    // while the button is held down, so the timed code runs while the
    // operator holds the button and stops as soon as it is released.
    //
    //   void setup()
    //   {
    //       button.begin();
    //       button.setLatching(false);
    //   }
    //
    // Note that the timed block sees the on/off state only at each timer
    // tick. In momentary mode a tap shorter than the timer interval can
    // begin and end between two ticks and never be seen there. That is
    // the intended behavior for a dead-man control, which responds to
    // sustained pressure. To react to a tap, use wasPressed() outside the
    // timer as shown above; it holds the event until it is read.
    //
    // Alternate: hold-to-arm. heldForMs() returns how long the button has
    // been held down (0 when released). Requiring a hold of, say, one second
    // guards against an accidental tap enabling the motors. Use momentary
    // mode here as well: in latching mode a tap would still toggle the
    // on/off flag and the indicator LED even though nothing was armed.
    //
    //   void setup()
    //   {
    //       button.begin();
    //       button.setLatching(false);
    //   }
    //
    //   void loop()
    //   {
    //       button.updateButton();
    //
    //       if (timer.isTimer(250))
    //       {
    //           if (button.heldForMs() >= 1000)
    //           {
    //               // insert your timed code here (armed after a 1 s hold)
    //           }
    //       }
    //   }
    //
    // Do not gate updateButton() behind the timer. If it is only called
    // once per interval, a press shorter than that interval is missed
    // and the debounce window is no longer meaningful.
    class Button
    {
    public:
        static const int NO_LED = -1;

    private:
        // Configuration
        int m_buttonPin;
        int m_ledPin;
        bool m_activeLow; // true: pressed reads LOW; false: pressed reads HIGH
        bool m_latching;  // true: press toggles; false: on only while held
        unsigned long m_debounceMs;

        // Debounce state
        int m_lastReading;              // raw pin level at previous update
        int m_stableState;              // debounced pin level
        unsigned long m_lastChangeTime; // millis() when the raw level last changed
        unsigned long m_stableSince;    // millis() when the debounced level last changed

        // Outputs
        bool m_latched;      // the on/off flag reported by isButtonOn()
        bool m_pressedEvent; // set on an accepted press, cleared by wasPressed()
        bool m_begun;

        // Pin level that means "pressed" for the configured wiring.
        int pressedLevel() const
        {
            return m_activeLow ? LOW : HIGH;
        }

        // Pin level that means "released".
        int releasedLevel() const
        {
            return m_activeLow ? HIGH : LOW;
        }

        // Drive the indicator LED from the on/off flag. Does nothing until
        // begin() has configured the pin, so the public methods may be
        // called in any order relative to begin().
        void writeLed() const
        {
            if (m_begun && m_ledPin != NO_LED)
            {
                digitalWrite(m_ledPin, m_latched ? HIGH : LOW);
            }
        }

    public:
        // Constructors
        //
        // buttonPin  Digital input pin. Default D2.
        // ledPin     Digital output pin for the indicator LED, or NO_LED.
        // activeLow  true: pressed reads LOW (INPUT_PULLUP, switch to GND).
        //            false: pressed reads HIGH (INPUT, external pulldown).
        // debounceMs Time a new level must hold before it is accepted.
        //
        // The button starts in latching mode; see setLatching().
        //
        // The two level members are initialized from the activeLow
        // parameter rather than from releasedLevel(), so their correctness
        // does not depend on the order in which the members are declared.
        Button(int buttonPin = 2,
               int ledPin = NO_LED,
               bool activeLow = true,
               unsigned long debounceMs = 50)
            : m_buttonPin(buttonPin),
              m_ledPin(ledPin),
              m_activeLow(activeLow),
              m_latching(true),
              m_debounceMs(debounceMs),
              m_lastReading(activeLow ? HIGH : LOW),
              m_stableState(activeLow ? HIGH : LOW),
              m_lastChangeTime(0),
              m_stableSince(0),
              m_latched(false),
              m_pressedEvent(false),
              m_begun(false)
        {
        }

        ~Button() = default;

        // Methods

        // Configure the pins. Call once from setup(). Calling it again
        // re-reads the pin and restarts the debounce window but leaves the
        // on/off flag alone; use resetButton() to clear that.
        void begin()
        {
            pinMode(m_buttonPin, m_activeLow ? INPUT_PULLUP : INPUT);
            if (m_ledPin != NO_LED)
            {
                pinMode(m_ledPin, OUTPUT);
            }
            // Take the current level as the starting point so that a button
            // held down at power-up is not reported as a press. The first
            // press is counted only after the button has been released.
            m_lastReading = digitalRead(m_buttonPin);
            m_stableState = m_lastReading;
            m_lastChangeTime = millis();
            m_stableSince = m_lastChangeTime;
            m_begun = true;
            writeLed();
        }

        // Change the debounce window at run time.
        void setDebounce(unsigned long debounceMs)
        {
            m_debounceMs = debounceMs;
        }

        // Select the on/off behavior reported by isButtonOn().
        //
        //   setLatching(true)   Latching mode (the default). Each press
        //                       toggles the flag: press for ON, press again
        //                       for OFF. Use this when the button acts as an
        //                       enable switch that the operator sets and
        //                       then leaves alone.
        //
        //   setLatching(false)  Momentary mode. The flag is ON only while the
        //                       button is held down and returns to OFF once
        //                       the release has passed the debounce window.
        //                       Use this as a dead-man
        //                       control: if the operator lets go, whatever
        //                       isButtonOn() enables (for example the motors)
        //                       stops.
        //
        // Changing the mode clears the on/off flag and any pending press
        // event, so the new mode starts from OFF and the next press is
        // handled cleanly. If the button happens to be held down at the
        // moment of the call, the flag stays OFF until the button is
        // released and pressed again. Intended to be called once from
        // setup(); it may be called before or after begin().
        void setLatching(bool latching)
        {
            m_latching = latching;
            m_latched = false;
            m_pressedEvent = false;
            writeLed();
        }

        // Current mode. True is latching, false is momentary.
        bool isLatching() const
        {
            return m_latching;
        }

        // On/off flag. In latching mode it toggles on each press. In
        // momentary mode it is true only while the button is held down.
        bool isButtonOn() const
        {
            return m_latched;
        }

        // Debounced held-down state.
        bool isPressed() const
        {
            return m_stableState == pressedLevel();
        }

        // Returns true once per accepted press, then clears the event.
        bool wasPressed()
        {
            bool event = m_pressedEvent;
            m_pressedEvent = false;
            return event;
        }

        // Milliseconds the button has been held down, measured from the
        // moment the debounced state became pressed. Returns 0 while the
        // button is released. Works in either mode. Compare against a
        // threshold to implement a hold-to-arm or long-press action:
        //
        //   if (button.heldForMs() >= 1000) { ... }
        //
        // The value keeps growing for as long as the button is held, so a
        // long-press action that should fire only once needs its own flag
        // in the sketch, cleared when isPressed() returns false.
        unsigned long heldForMs() const
        {
            if (!isPressed())
            {
                return 0;
            }
            return millis() - m_stableSince;
        }

        // Clear the on/off flag and any pending press event. Does not
        // change the mode or the debounce state. As with setLatching(),
        // a button held down at the moment of the call is not counted as
        // pressed again until it is released and pressed.
        void resetButton()
        {
            m_latched = false;
            m_pressedEvent = false;
            writeLed();
        }

        // Sample the pin. Call once per pass through loop().
        void updateButton()
        {
            if (!m_begun)
            {
                begin();
            }

            int reading = digitalRead(m_buttonPin);
            unsigned long now = millis();

            // Any change in the raw level restarts the debounce window.
            if (reading != m_lastReading)
            {
                m_lastChangeTime = now;
                m_lastReading = reading;
            }

            // The level has held for the full window: accept it.
            if ((now - m_lastChangeTime) >= m_debounceMs && reading != m_stableState)
            {
                m_stableState = reading;
                m_stableSince = now;

                if (m_stableState == pressedLevel())
                {
                    // Accepted press.
                    m_latched = m_latching ? !m_latched : true;
                    m_pressedEvent = true;
                    writeLed();
                }
                else if (!m_latching)
                {
                    // Accepted release in momentary mode.
                    m_latched = false;
                    writeLed();
                }
            }
        }
    };
}
#endif
