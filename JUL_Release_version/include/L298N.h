//
// Carpenter Software
// File: L298N.h (release version)
// Updated: 20211109 (See 1003 L298N Article)
// Updated: 20210910
// Date: 20210830
// Folder: bluBot_02_Release_Version
// Purpose: Github Depository (MageMCU)
//
// Student Use...
//
// Hardware (For further information, see Debug Version)
//
// RAM : [] 3.6 % (used 73 bytes from 2048 bytes)
// Flash : [==] 15.6 % (used 5038 bytes from 32256 bytes)
//
// MIT LICENSE
//

#ifndef __UNO_L298N_H__
#define __UNO_L298N_H__

#include <Arduino.h>
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

        int _PWM_LeftMotor;
        int _PWM_RightMotor;

        void _setDirectionPins();
        void _powerDownL298N();

    public:
        L298N();
        L298N(uint8_t LeftMotorPWM,
              uint8_t LeftMotorIN1,
              uint8_t LeftMotorIN2,
              uint8_t RightMotorIN1,
              uint8_t RightMotorIN2,
              uint8_t RightMotorPWM);
        void SetupPinsL298N();
        void UpdateL298N(int UnoPWM_ToENA, int UnoPWM_ToENB); // FIXME 20221017 jc
        void PowerDownL298N();
    };

    L298N::L298N()
    {
        _ZERO = 0;
        _LeftMotorPWM = 10;
        _LeftMotorIN1 = 9;
        _LeftMotorIN2 = 8;
        _RightMotorIN1 = 7;
        _RightMotorIN2 = 6;
        _RightMotorPWM = 5;
    }

    L298N::L298N(uint8_t LeftMotorPWM,
                 uint8_t LeftMotorIN1,
                 uint8_t LeftMotorIN2,
                 uint8_t RightMotorIN1,
                 uint8_t RightMotorIN2,
                 uint8_t RightMotorPWM)
    {
        _ZERO = 0;
        _LeftMotorPWM = LeftMotorPWM;
        _LeftMotorIN1 = LeftMotorIN1;
        _LeftMotorIN2 = LeftMotorIN2;
        _RightMotorIN1 = RightMotorIN1;
        _RightMotorIN2 = RightMotorIN2;
        _RightMotorPWM = RightMotorPWM;
    }

    void L298N::SetupPinsL298N()
    {
        pinMode(_LeftMotorPWM, OUTPUT);
        pinMode(_LeftMotorIN1, OUTPUT);
        pinMode(_LeftMotorIN2, OUTPUT);
        pinMode(_RightMotorIN1, OUTPUT);
        pinMode(_RightMotorIN2, OUTPUT);
        pinMode(_RightMotorPWM, OUTPUT);
        _powerDownL298N();
    }

    void L298N::UpdateL298N(int PWM_LeftMotor, int PWM_RightMotor)
    {
        _PWM_LeftMotor = PWM_LeftMotor;
        _PWM_RightMotor = PWM_RightMotor;

        _setDirectionPins();

        analogWrite(_LeftMotorPWM, abs(PWM_LeftMotor));
        analogWrite(_RightMotorPWM, abs(PWM_RightMotor));
    }

    void L298N::PowerDownL298N()
    {
        _powerDownL298N();
    }

    void L298N::_powerDownL298N()
    {
        // Experimental
        UpdateL298N((int)_ZERO, (int)_ZERO);

        // NOT RECOMMENDED - READ ARTICLE 1003
        // digitalWrite(_LeftMotorIN1, LOW);
        // digitalWrite(_LeftMotorIN2, LOW);
        // digitalWrite(_RightMotorIN1, LOW);
        // digitalWrite(_RightMotorIN2, LOW);
    }

    void L298N::_setDirectionPins()
    {
        if (_PWM_LeftMotor >= _ZERO)
        {
            digitalWrite(_LeftMotorIN1, LOW);
            digitalWrite(_LeftMotorIN2, HIGH);
        }
        else if (_PWM_LeftMotor < _ZERO)
        {
            digitalWrite(_LeftMotorIN2, LOW);
            digitalWrite(_LeftMotorIN1, HIGH);
        }

        /* Not recommended
        else
        {
            digitalWrite(_LeftMotorIN1, LOW);
            digitalWrite(_LeftMotorIN2, LOW);
        }
        */

        if (_PWM_RightMotor >= _ZERO)
        {
            digitalWrite(_RightMotorIN1, LOW);
            digitalWrite(_RightMotorIN2, HIGH);
        }
        else if (_PWM_RightMotor < _ZERO)
        {
            digitalWrite(_RightMotorIN2, LOW);
            digitalWrite(_RightMotorIN1, HIGH);
        }

        /*  Not recommended
        else
        {
            digitalWrite(_RightMotorIN1, LOW);
            digitalWrite(_RightMotorIN2, LOW);
        }
        */
    }
}

#endif
