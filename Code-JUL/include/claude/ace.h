//
// Carpenter Software
// File: Class ace.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/include/claude
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
// RELEASE
//   2026-10-28  v6.8.0
//   ace.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//
// Added 20261017 for Step4_Generated (named Step4_Generated until
// v3.1.0). Revised 20261018 (v3.1.0): the template parameters
// X_REVERSED and Y_REVERSED and the two reversal lines of tick() were
// removed; one Bits() value corrects any joystick orientation.
// Revised 20261018 (v3.1.1): the push button pin is an input with the
// internal pull up off, as in Step2_JUL; the joystick switch module
// supplies its own resistor, or an external 10 kOhm resistor is added.
// The button is read active LOW (pressed reads LOW), the form of line
// 45 of Step2_JUL as written.
// Revised 20261018 (v3.2.0): requested by the author after a bench
// test. The default control tick TICK_MS is 50 ms in place of the
// 100 ms of Step2_JUL (BUTTON_TIMER_mS of Common.h), for a faster
// response to the joystick. The bench test also showed that the
// joystick switch module has no resistor of its own, so the external
// 10 kOhm pull up from D2 to 5 V (Circuit-2 of Article 1004) is
// required; it matches the active LOW reading of this file.
// Revised 20261021 (v5.0.0): requested by the author. The default of
// LED_PIN is 12, the indicator LED of Article 1009, Circuit-1, in
// place of 3. Step4_Generated passes LED_PIN = 12 itself, so its
// compiled program is unchanged. The author's bench test of 20261021
// (release v4.0.1) passed: Step4_Generated drives the robot, and the
// LED on D12 follows the push button.
// Revised 20261025 (v6.4.0): requested by the author. Two template
// parameters at the end of the list, X_CENTER and Y_CENTER (default
// 511), hold the joystick center measured by Step1_Joystick
// (include/JoystickCenter.h). tick() moves each reading by the
// offset of its center from 511 before compute(); Step2_JUL keeps
// the center 511 (author decision). With the defaults the compiled program is
// unchanged, so a Step4_Generated printed before v6.4.0 still builds
// and drives as before.
// Revised 20261025 (v6.5.0): the allowed center is 461 to 561, the
// Test 3 limit of Step1_Joystick (50 counts from 511); Path B is
// now called Fast Drive (Article 1009). The compiled program is
// unchanged.
//
// FOLDER include/claude
// The files in include/claude were written with Claude (Anthropic),
// an AI assistant, at the request of Jesse Carpenter, on 20261017.
// They are kept apart from the original header files of include/ and
// include/numerics/, which they do not change, so that a reader can
// tell at once which code is original and which was generated. Each
// file was tested against the original code as stated below, and on
// the bench by the author on 20261021.
//
// PURPOSE
// ace.h is one file that holds everything the Step4_Generated drive
// program needs. It includes Arduino.h only. It is written for speed
// and size, not for reading; the original headers remain the
// reference for how the drive works. Article 1009 (revision
// 20261021d) uses Step2_JUL for L298N Setup and gives Step3_Generator
// and Step4_Generated as Fast Drive.
//
// ORIGINAL CODE INCORPORATED (rewritten, same behavior)
//   Joystick.h             class Joystick<float>: the octant algorithm,
//                          UpdateInputs(), Left(), Right(), tolerance
//   numerics/LinearMap.h   class LinearMap<float>: 0 to 1023 onto -1
//                          to 1, and -1 to 1 onto -255 to 255
//   numerics/MiscMath.h    function template absT()
//   Button.h               class Button: active LOW, latching, 50 ms
//                          debounce, LED; the internal pull up is off,
//                          as in Step2_JUL (THE PUSH BUTTON)
//   Timer.h                class Timer: isTimer(), armed on first call
//   Common.h               BUTTON_TIMER_mS, the control tick: 100 ms
//                          in Step2_JUL, 50 ms here (TICK_MS, v3.2.0)
//   L298N.h                UpdateL298N() and PowerDownL298N(), with the
//                          Bits() decision already made by Step3
//   Arduino core           analogRead(), digitalWrite(), analogWrite(),
//                          pinMode(), replaced by register access
// Not incorporated: the Debug() serial output of MiscMath.h, the
// DEBUG flags of Common.h, and the classes Step2_JUL does not use.
//
// STEPS 2 TO 4
//   Step2_JUL finds the Bits() value of the L298N wiring with the
//   Motor Movement Checklist; its joystick lines, x on A0 and y on
//   A1, stay as written, because that value also corrects the
//   joystick orientation. Step3_Generator checks the pins and the
//   joystick lines, asks for the Bits() value in the serial monitor,
//   and prints a main.cpp for Step4_Generated, which creates one Ace
//   object with the answers as template parameters. A new run of
//   Step3 changes only that main.cpp; this file is never edited.
//
// HOW IT IS FASTER
//   1. ADC: the analog inputs are read through the ADC registers with
//      the prescaler set by the Arduino core (125 kHz ADC clock), so
//      the readings and their accuracy are those of analogRead().
//   2. Integer math: the float chain of Step2_JUL is computed in
//      integers scaled by 1023 (see Scaled values below).
//   3. Pins: every pin is a template parameter, so each write is one
//      instruction on a port register or a timer compare register,
//      with the same pin states as digitalWrite() and analogWrite().
//
// PERFORMANCE (20261017, avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, simavr
// at 16 MHz, 1024 simulated joystick positions, bits_1010)
//   Stage, microseconds per tick       Step2_JUL   ace.h   times
//   Joystick math                          322.5     16.4    19.6
//   Motor output                            40.3      3.7    10.9
//   Math and output                        362.9     20.1    18.0
//   Two ADC readings                       212.3    211.9     1.0
//   Full control tick                      574.8    232.0     2.5
//   Flash, bytes                            6344     1420
//   RAM, bytes                               316       23
//   The two ADC conversions are 91 percent of the ace.h tick; they
//   are set by the ADC clock, kept at 125 kHz for full accuracy.
//   At one tick every 50 ms (TICK_MS since v3.2.0) ace.h uses about
//   0.46 percent of the processor time; Step2_JUL, at 100 ms, about
//   0.57 percent.
//
// VERIFIED (20261017)
//   * compute() gives the same left and right commands as the float
//     chain of Step2_JUL for all 1024 x 1024 pairs of readings.
//   * On the simulated Uno, the port, timer, and compare registers
//     after each motor update match Step2_JUL's driveMotor() code
//     for 12519 pairs, and the float results match the host test.
//   * Bench test 20261021 by the author (release v4.0.1): passed,
//     with the push button, the LED on D12, and the timer.
//   * 20261018 (v3.2.0): TICK_MS 50 changes only the time between
//     ticks; each tick sets the same pin states for the same
//     readings.
//
// PINS
//   X_PIN and Y_PIN: A0 to A5. LEFT_EN and RIGHT_EN: PWM pins 3, 5, 6,
//   9, 10, or 11 (checked when the program is built). Direction pins,
//   button, and LED: any other digital pin except D0 and D1 (serial).
//   PWM frequency: D5 and D6 about 980 Hz (Timer0); D9, D10, D3, D11
//   about 490 Hz (Timer1, Timer2).
//
// Scaled values: an ADC reading a (0 to 1023) gives N = 2a - 1023,
// so N / 1023 is the value LinearMap gives (-1 to 1). The dead zones
// 0.05 and 0.06 of Step2_JUL become |N| <= 51 and |N| <= 61. The
// output map gives 255 * N / 1023, truncated toward zero as the
// (int) cast of Step2_JUL does.

#ifndef ace_h
#define ace_h

#include <Arduino.h>

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    // Port register bit of an Uno pin: D0 to D7 on PORTD,
    // D8 to D13 on PORTB, A0 to A5 (14 to 19) on PORTC
    constexpr uint8_t aceBit(uint8_t pin)
    {
        return pin < 8 ? pin : (pin < 14 ? pin - 8 : pin - 14);
    }

    constexpr bool acePwmPin(uint8_t pin)
    {
        return pin == 3 || pin == 5 || pin == 6 ||
               pin == 9 || pin == 10 || pin == 11;
    }

    template <uint8_t P>
    struct AcePin
    {
        static inline void output()
        {
            if (P < 8)
                DDRD |= _BV(aceBit(P));
            else if (P < 14)
                DDRB |= _BV(aceBit(P));
            else
                DDRC |= _BV(aceBit(P));
        }
        // Input with the internal pull up off, as pinMode(P, INPUT)
        static inline void input()
        {
            if (P < 8)
            {
                DDRD &= ~_BV(aceBit(P));
                PORTD &= ~_BV(aceBit(P));
            }
            else if (P < 14)
            {
                DDRB &= ~_BV(aceBit(P));
                PORTB &= ~_BV(aceBit(P));
            }
            else
            {
                DDRC &= ~_BV(aceBit(P));
                PORTC &= ~_BV(aceBit(P));
            }
        }
        static inline void high()
        {
            if (P < 8)
                PORTD |= _BV(aceBit(P));
            else if (P < 14)
                PORTB |= _BV(aceBit(P));
            else
                PORTC |= _BV(aceBit(P));
        }
        static inline void low()
        {
            if (P < 8)
                PORTD &= ~_BV(aceBit(P));
            else if (P < 14)
                PORTB &= ~_BV(aceBit(P));
            else
                PORTC &= ~_BV(aceBit(P));
        }
        static inline bool read()
        {
            if (P < 8)
                return PIND & _BV(aceBit(P));
            else if (P < 14)
                return PINB & _BV(aceBit(P));
            return PINC & _BV(aceBit(P));
        }
        // Disconnects the timer output, as digitalWrite() does
        static inline void pwmOff()
        {
            if (P == 3)
                TCCR2A &= ~_BV(COM2B1);
            else if (P == 5)
                TCCR0A &= ~_BV(COM0B1);
            else if (P == 6)
                TCCR0A &= ~_BV(COM0A1);
            else if (P == 9)
                TCCR1A &= ~_BV(COM1A1);
            else if (P == 10)
                TCCR1A &= ~_BV(COM1B1);
            else if (P == 11)
                TCCR2A &= ~_BV(COM2A1);
        }
        // Same pin states as analogWrite(P, duty)
        static inline void pwm(uint8_t duty)
        {
            if (duty == 0)
            {
                pwmOff();
                low();
            }
            else if (duty == 255)
            {
                pwmOff();
                high();
            }
            else if (P == 3)
            {
                TCCR2A |= _BV(COM2B1);
                OCR2B = duty;
            }
            else if (P == 5)
            {
                TCCR0A |= _BV(COM0B1);
                OCR0B = duty;
            }
            else if (P == 6)
            {
                TCCR0A |= _BV(COM0A1);
                OCR0A = duty;
            }
            else if (P == 9)
            {
                TCCR1A |= _BV(COM1A1);
                OCR1A = duty;
            }
            else if (P == 10)
            {
                TCCR1A |= _BV(COM1B1);
                OCR1B = duty;
            }
            else if (P == 11)
            {
                TCCR2A |= _BV(COM2A1);
                OCR2A = duty;
            }
        }
    };

    template <uint8_t X_PIN, uint8_t Y_PIN,
              uint8_t LEFT_EN, uint8_t LEFT_FWD, uint8_t LEFT_REV,
              uint8_t RIGHT_EN, uint8_t RIGHT_FWD, uint8_t RIGHT_REV,
              uint8_t BUTTON_PIN = 2, uint8_t LED_PIN = 12,
              uint16_t TICK_MS = 50, uint16_t DEBOUNCE_MS = 50,
              uint16_t X_CENTER = 511, uint16_t Y_CENTER = 511>
    class Ace
    {
        static_assert(X_CENTER >= 461 && X_CENTER <= 561 &&
                          Y_CENTER >= 461 && Y_CENTER <= 561,
                      "each joystick center must be 461 to 561");
        static_assert(X_PIN >= A0 && X_PIN <= A5 && Y_PIN >= A0 && Y_PIN <= A5,
                      "joystick pins must be A0 to A5");
        static_assert(acePwmPin(LEFT_EN) && acePwmPin(RIGHT_EN),
                      "enable pins must be PWM pins 3, 5, 6, 9, 10, or 11");

        // Button (Button.h: active LOW, latching, 50 ms debounce)
        bool _begun = false;
        bool _lastReading = true;
        bool _stableState = true;
        bool _on = false;
        unsigned long _lastChange = 0;
        // Timer (Timer.h, isTimer()); TICK_MS 50 ms since v3.2.0
        bool _armed = false;
        unsigned long _previous = 0;

        // analogRead() without the call: same ADMUX, same prescaler
        template <uint8_t PIN>
        static inline uint16_t adc()
        {
            ADMUX = _BV(REFS0) | ((PIN - A0) & 0x07);
            ADCSRA |= _BV(ADSC);
            while (ADCSRA & _BV(ADSC))
            {
            }
            return ADC;
        }

        // |N| (0 to 1023) to the duty cycle 255 |N| / 1023, truncated.
        // 16336 / 65536 gives the same result as 255 / 1023 for every
        // N from 0 to 1023, with one multiplication and no division.
        static inline uint8_t duty(uint16_t n)
        {
            return (uint8_t)(((uint32_t)n * 16336u) >> 16);
        }

        // One command, -255 to 255; zero counts as forward
        static inline int16_t command(int16_t n)
        {
            return n < 0 ? -(int16_t)duty(-n) : (int16_t)duty(n);
        }

        template <uint8_t EN, uint8_t FWD, uint8_t REV>
        static inline void drive(int16_t cmd)
        {
            if (cmd >= 0)
            {
                AcePin<REV>::low();
                AcePin<FWD>::high();
                AcePin<EN>::pwm((uint8_t)cmd);
            }
            else
            {
                AcePin<FWD>::low();
                AcePin<REV>::high();
                AcePin<EN>::pwm((uint8_t)(-cmd));
            }
        }

        void beginButton()
        {
            AcePin<BUTTON_PIN>::input();
            AcePin<LED_PIN>::output();
            _lastReading = AcePin<BUTTON_PIN>::read();
            _stableState = _lastReading;
            _lastChange = millis();
            _begun = true;
            AcePin<LED_PIN>::low();
        }

        void updateButton()
        {
            if (!_begun)
                beginButton();
            bool reading = AcePin<BUTTON_PIN>::read();
            unsigned long now = millis();
            if (reading != _lastReading)
            {
                _lastChange = now;
                _lastReading = reading;
            }
            if ((now - _lastChange) >= DEBOUNCE_MS && reading != _stableState)
            {
                _stableState = reading;
                // pressed reads LOW
                if (!_stableState)
                {
                    _on = !_on;
                    if (_on)
                        AcePin<LED_PIN>::high();
                    else
                        AcePin<LED_PIN>::low();
                }
            }
        }

        bool isTimer()
        {
            unsigned long now = millis();
            if (!_armed)
            {
                _previous = now;
                _armed = true;
                return false;
            }
            if (now - _previous >= TICK_MS)
            {
                _previous = now;
                return true;
            }
            return false;
        }

    public:
        // The joystick chain of Step2_JUL from two readings (0 to
        // 1023) to the two commands (-255 to 255).
        static void compute(uint16_t xDigital, uint16_t yDigital,
                            int16_t &left, int16_t &right)
        {
            int16_t x = 2 * (int16_t)xDigital - 1023;
            int16_t y = 2 * (int16_t)yDigital - 1023;
            // Dead zones, X_OFFSET 0.05 and Y_OFFSET 0.06
            if (x >= -51 && x <= 51)
                x = 0;
            if (y >= -61 && y <= 61)
                y = 0;

            int16_t ax = x < 0 ? -x : x;
            int16_t ay = y < 0 ? -y : y;
            int16_t d = ax > ay ? ax - ay : ay - ax;
            int16_t l = 0;
            int16_t r = 0;

            // Joystick.h, the same tests in the same order
            if (x == 0 && y == 0)
            {
            }
            else if (ax >= ay)
            {
                if (x >= 0 && y >= 0)
                {
                    // octant 1
                    l = x;
                    r = -d;
                }
                else if (x <= 0 && y >= 0)
                {
                    // octant 4
                    l = -d;
                    r = -x;
                    // Step2_JUL computes this case in float as
                    // 84.99998 and truncates it to 84, not 85. At
                    // y = 341 its float test |x| >= |y| is false,
                    // octant 3 gives right = y, and the result is 85.
                    if (x == -341 && y != 341)
                    {
                        left = command(l);
                        right = 84;
                        return;
                    }
                }
                else if (x <= 0 && y <= 0)
                {
                    // octant 5
                    l = x;
                    r = d;
                }
                else
                {
                    // octant 8
                    l = d;
                    r = -x;
                }
            }
            else
            {
                if (x >= 0 && y >= 0)
                {
                    // octant 2
                    l = y;
                    r = d;
                }
                else if (x <= 0 && y >= 0)
                {
                    // octant 3
                    l = d;
                    r = y;
                }
                else if (x <= 0 && y <= 0)
                {
                    // octant 6
                    l = y;
                    r = -d;
                }
                else
                {
                    // octant 7
                    l = -d;
                    r = y;
                }
            }
            left = command(l);
            right = command(r);
        }

        // Pins as outputs and both motors off; call in setup()
        void begin()
        {
            AcePin<LEFT_EN>::output();
            AcePin<LEFT_FWD>::output();
            AcePin<LEFT_REV>::output();
            AcePin<RIGHT_EN>::output();
            AcePin<RIGHT_FWD>::output();
            AcePin<RIGHT_REV>::output();
            powerDown();
        }

        // SAFETY COMES FIRST (WATCH YOUR FINGERS)
        static inline void powerDown()
        {
            AcePin<LEFT_EN>::pwm(0);
            AcePin<RIGHT_EN>::pwm(0);
        }

        // The joystick center correction (v6.4.0): the reading moves
        // by CENTER - 511 and stays inside 0 to 1023, so a resting
        // grip reads 511 and gives the command 0. For CENTER 511 the test below
        // is
        // false when the program is built, and no code is added.
        template <uint16_t CENTER>
        static inline uint16_t centered(uint16_t reading)
        {
            if (CENTER == 511)
                return reading;
            int16_t moved = (int16_t)reading - ((int16_t)CENTER - 511);
            if (moved < 0)
                return 0;
            if (moved > 1023)
                return 1023;
            return (uint16_t)moved;
        }

        // One control tick: read, center, compute, drive
        static void tick()
        {
            uint16_t xd = centered<X_CENTER>(adc<X_PIN>());
            uint16_t yd = centered<Y_CENTER>(adc<Y_PIN>());
            int16_t left;
            int16_t right;
            compute(xd, yd, left, right);
            output(left, right);
        }

        // Writes two commands (-255 to 255) to the L298N pins
        static inline void output(int16_t left, int16_t right)
        {
            drive<LEFT_EN, LEFT_FWD, LEFT_REV>(left);
            drive<RIGHT_EN, RIGHT_FWD, RIGHT_REV>(right);
        }

        // Call from loop(): button, timer, and the tick
        void update()
        {
            updateButton();
            if (isTimer())
            {
                if (_on)
                    tick();
                else
                    powerDown();
            }
        }

        bool isButtonOn() const { return _on; }
    };
}

#endif
