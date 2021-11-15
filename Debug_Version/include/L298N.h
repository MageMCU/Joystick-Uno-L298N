//
// Carpenter Software
// File: Class L298N.h (debug version)
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
// November 14, 2021 - New Lab Experiments 
//                     (See 1003 L298N Article)
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

#ifndef __UNO_L298N_H__
#define __UNO_L298N_H__

#include <Arduino.h>
#include "DEBUG.h"

// Using Adruino Uno
namespace uno
{
    class L298N
    {
    private:
        uint8_t _ZERO;

        uint8_t _LeftMotorPWM;
        uint8_t _LeftMotorIN1;
        uint8_t _LeftMotorIN2;

        uint8_t _RightMotorIN1;
        uint8_t _RightMotorIN2;
        uint8_t _RightMotorPWM;

        // Debug Variables
        int _PWM_LeftMotor;
        int _PWM_RightMotor;
        // used as boolean
        uint8_t _IN1_Flag;
        uint8_t _IN2_Flag;
        uint8_t _IN3_Flag;
        uint8_t _IN4_Flag;

        // Private method
        void _setDirectionPins();
        void _powerDownL298N();
        void _debugConstructor(/* Debug Parameters */);
        void _allDebug(/* Debug Parameters */);

    public:
        L298N();
        L298N(uint8_t LeftMotorPWM,
              uint8_t LeftMotorIN1,
              uint8_t LeftMotorIN2,
              uint8_t RightMotorIN1,
              uint8_t RightMotorIN2,
              uint8_t RightMotorPWM);

        // Getter Methods
        int GetIN1();
        int GetIN2();
        int GetIN3();
        int GetIN4();
        // Place inside setup() function
        void SetupPinsL298N();

        // Place inside loop() function
        void updateL298N(bool debugMotors, int UnoPWM_ToENA, int UnoPWM_ToENB);
    };

    // Default Constructor
    L298N::L298N()
    {
        _ZERO = 0;

        _LeftMotorPWM = 10; // Arduino Pin 10  wired to L298N Pin ENA
        _LeftMotorIN1 = 9;  // Arduino Pin 9  wired to L298N Pin IN1
        _LeftMotorIN2 = 8;  // Arduino Pin 8  wired to L298N Pin IN2
        _RightMotorIN1 = 7; // Arduino Pin 7  wired to L298N Pin IN3
        _RightMotorIN2 = 6; // Arduino Pin 6  wired to L298N Pin IN4
        _RightMotorPWM = 5; // Arduino Pin 5  wired to L298N Pin ENB

        _debugConstructor(/* Debug Arguments */);
    }

    // Assign Arduino Pins to Constructor
    L298N::L298N(uint8_t LeftMotorPWM,
                 uint8_t LeftMotorIN1,
                 uint8_t LeftMotorIN2,
                 uint8_t RightMotorIN1,
                 uint8_t RightMotorIN2,
                 uint8_t RightMotorPWM)
    {
        _ZERO = 0;
        // LEFT SET
        _LeftMotorPWM = LeftMotorPWM; // Uno-PWM-To-L298N-PWM
        _LeftMotorIN1 = LeftMotorIN1; // Uno-Output-To-L298N-Digital-Input
        _LeftMotorIN2 = LeftMotorIN2; // Uno-Output-To-L298N-Digital-Input
        // RIGHT SET
        _RightMotorIN1 = RightMotorIN1; // Uno-Output-To-L298N-Digital-Input
        _RightMotorIN2 = RightMotorIN2; // Uno-Output-To-L298N-Digital-Input
        _RightMotorPWM = RightMotorPWM; // Uno-PWM-To-L298N-PWM

        _debugConstructor(/* Debug Arguments */);
    }

    int L298N::GetIN1()
    {
        return (int)_IN1_Flag;
    }

    int L298N::GetIN2()
    {
        return (int)_IN2_Flag;
    }

    int L298N::GetIN3()
    {
        return (int)_IN3_Flag;
    }

    int L298N::GetIN4()
    {
        return (int)_IN4_Flag;
    }

    // Adjust  Motors
    void L298N::updateL298N(bool debugMotors, int PWM_LeftMotor, int PWM_RightMotor)
    {
        // Debug with Negative Values
        _PWM_LeftMotor = PWM_LeftMotor;
        _PWM_RightMotor = PWM_RightMotor;

        // L298N_DirectionPins requires negative numbers
        _setDirectionPins();

        // L298N does not use negative values
        // If both Input Pair Pins (IN1 & IN2, IN3 & IN4) are
        // all set to LOW then the motors will not RUN..., no matter
        // what the motor speed values might be.
        // See L298N_DirectionPins() method for details.

        if (debugMotors)
        {
            _allDebug();
        }
        else // Motors Off - Safety Reasons
        {
            // ENA Motor
            analogWrite(_LeftMotorPWM, abs(PWM_LeftMotor));
            // ENB Motor
            analogWrite(_RightMotorPWM, abs(PWM_RightMotor));
        }
    }

    void L298N::_powerDownL298N()
    {
        // Experimental
        UpdateL298N((int)_ZERO, (int)_ZERO);

        // NOT RECOMMENDED - READ ARTICLE 1003
        // digitalWrite(_LeftMotorIN1, LOW);
        // _IN1_Flag = LOW;
        // digitalWrite(_LeftMotorIN2, LOW);
        // _IN2_Flag = LOW;
        // digitalWrite(_RightMotorIN1, LOW);
        // _IN3_Flag = LOW;
        // digitalWrite(_RightMotorIN2, LOW);
        // _IN4_Flag = LOW;
    }

    void L298N::SetupPinsL298N()
    {
        // INTERFACE: Motors
        pinMode(_LeftMotorPWM, OUTPUT);
        pinMode(_LeftMotorIN1, OUTPUT);
        pinMode(_LeftMotorIN2, OUTPUT);
        pinMode(_RightMotorIN1, OUTPUT);
        pinMode(_RightMotorIN2, OUTPUT);
        pinMode(_RightMotorPWM, OUTPUT);
        //
        _powerDownL298N();
    }

    void L298N::_setDirectionPins()
    {
        // Center Tolerance is adjusted in Joystick Method
        // in the Manager Class (Header and Code Files)
        //
        // Note: IN1 and IN2 wheel direction can be changed
        //       by changing the conditionals "<" and ">"...,
        //       the order of the digitalWrite().
        //       Much easier changing code then wires on a motor.
        //
        // WARNING: Never set paired 1&2 values to HIGH at
        //          the same time. ALways set the FIRST-INPUT-PIN
        //          to LOW before setting the following PIN to HIGH.
        //          This will prevent two PINS from being HIGH at
        //          once.
        // This also includes IN3 and IN4 wheel direction pins below...

        // LEFT Motor //////////////////////////////////
        if (_PWM_LeftMotor > _ZERO)
        {
            digitalWrite(_LeftMotorIN1, LOW);
            _IN1_Flag = LOW;
            digitalWrite(_LeftMotorIN2, HIGH);
            _IN2_Flag = HIGH;
        }
        else if (_PWM_LeftMotor < _ZERO)
        {
            digitalWrite(_LeftMotorIN2, LOW);
            _IN2_Flag = LOW;
            digitalWrite(_LeftMotorIN1, HIGH);
            _IN1_Flag = HIGH;
        }

        /* Not recommended - READ ARTICLE 1003
        else
        {
            digitalWrite(_LeftMotorIN1, LOW);
            _IN1_Flag = LOW;
            digitalWrite(_LeftMotorIN2, LOW);
            _IN2_Flag = LOW;
        }
        */

        // RIGHT Motor //////////////////////////////////
        if (_PWM_RightMotor > _ZERO)
        {
            digitalWrite(_RightMotorIN1, LOW);
            _IN3_Flag = LOW;
            digitalWrite(_RightMotorIN2, HIGH);
            _IN4_Flag = HIGH;
        }
        else if (_PWM_RightMotor < _ZERO)
        {
            digitalWrite(_RightMotorIN2, LOW);
            _IN4_Flag = LOW;
            digitalWrite(_RightMotorIN1, HIGH);
            _IN3_Flag = HIGH;
        }

        /* Not recommended - READ ARTICLE 1003
        else
        {
            digitalWrite(_RightMotorIN1, LOW);
            _IN3_Flag = LOW;
            digitalWrite(_RightMotorIN2, LOW);
            _IN4_Flag = LOW;
        }
        */
    }

    void L298N::_debugConstructor(/* Debug Parameters */)
    {
#ifdef _dL_
        // Used simply whether or not
        // Constructor Instantiated L298N CLASS
        Serial.println("L298N");
        // Write Serial Prints Here...
#endif
    }

    void L298N::_allDebug(/* Debug Parameters */)
    {
        // The problem debugging L298N is the
        // confusion between Hardware and Software...
        // See L298N in the _debug() in the main.cpp
        // file before play with this code.

        // you want to DEBUG?
#ifdef _SOMETHING_
        // Serial Print Statements.
#endif
    }
}

#endif
