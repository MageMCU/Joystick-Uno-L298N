//
// Carpenter Software
// File: Class L298N.h
// Folder: Simplified-Joystick-Uno-L298N (SJUL)
//
// Purpose: Github Depository (MageMCU)
//
// Algebra OOP Library
// The math is underneath the namespace
// nmr for Numerics as in numeric computation.
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

#ifndef SJUL_Uno_L298N_h
#define SJUL_Uno_L298N_h

#include <Arduino.h>
// Using Adruino Uno

#include "Bitwise.h"

namespace uno
{
    enum MotorBits {
        // Bit-Numbers
        motors_bitZero = 0,
        motors_bitOne,
        motors_bitTwo,
        // Bits-Values
        motors_FFF = 0,
        motors_FFT,
        motors_FTF,
        motors_FTT,
        motors_TFF,
        motors_TFT,
        motors_TTF,
        motors_TTT
    };

    class L298N
    {
    private:
        // Private Properties
        nmr::Bitwise<int> L_bWise;
        bool L_ReverseInputs;
        bool L_DirectionLeftMotor;
        bool L_DirectionRightMotor;

        uint8_t L_ZERO;

        uint8_t L_LeftMotorPWM;
        uint8_t L_LeftMotorIN1;
        uint8_t L_LeftMotorIN2;

        uint8_t L_RightMotorIN1;
        uint8_t L_RightMotorIN2;
        uint8_t L_RightMotorPWM;

        // Private Methods
        int L_PWM_LeftMotor;
        int L_PWM_RightMotor;

        void L_SetDirectionPins();
        void L_PowerDownL298N();

        void L_LeftMotor();
        void L_RightMotor();

    public:
        // Contructors
        L298N();
        L298N(uint8_t LeftMotorPWM,
            uint8_t LeftMotorIN1,
            uint8_t LeftMotorIN2,
            uint8_t RightMotorIN1,
            uint8_t RightMotorIN2,
            uint8_t RightMotorPWM);
        ~L298N() = default;

        // Methods
        void PinsL298N();
        void ReverseLeftRight(int conditions);
        void UpdateL298N(int UnoPWM_ToENA, int UnoPWM_ToENB, bool PowerMotors);
        void PowerDownL298N();
    };

    L298N::L298N()
    {
        L_ZERO = 0;
        L_LeftMotorPWM = 10;
        L_LeftMotorIN1 = 9;
        L_LeftMotorIN2 = 8;
        L_RightMotorIN1 = 7;
        L_RightMotorIN2 = 6;
        L_RightMotorPWM = 5;
        L_ReverseInputs = true;
        L_DirectionLeftMotor = true;
        L_DirectionRightMotor = true;
    }

    L298N::L298N(uint8_t LeftMotorPWM,
        uint8_t LeftMotorIN1,
        uint8_t LeftMotorIN2,
        uint8_t RightMotorIN1,
        uint8_t RightMotorIN2,
        uint8_t RightMotorPWM)
    {
        L_ZERO = 0;
        L_LeftMotorPWM = LeftMotorPWM;
        L_LeftMotorIN1 = LeftMotorIN1;
        L_LeftMotorIN2 = LeftMotorIN2;
        L_RightMotorIN1 = RightMotorIN1;
        L_RightMotorIN2 = RightMotorIN2;
        L_RightMotorPWM = RightMotorPWM;
        L_ReverseInputs = true;
        L_DirectionLeftMotor = true;
        L_DirectionRightMotor = true;
    }

    void L298N::PinsL298N()
    {
        pinMode(L_LeftMotorPWM, OUTPUT);
        pinMode(L_LeftMotorIN1, OUTPUT);
        pinMode(L_LeftMotorIN2, OUTPUT);
        pinMode(L_RightMotorIN1, OUTPUT);
        pinMode(L_RightMotorIN2, OUTPUT);
        pinMode(L_RightMotorPWM, OUTPUT);
        L_PowerDownL298N();
    }

    void L298N::ReverseLeftRight(int bitsValue = (int)MotorBits::motors_TTT)
    {
        // The boolean Order 
        // (1)         Reverse Inouts: T/F
        // (2)   Direction Left Motor: T/F
        // (3) Direction Right Motoer: T/F
        // where TTT is the default setting...
        // Check conditions:    FFF, FFT, FTF, FTT, TFF, TFT, TTF, TTT
        // Bits Value:           0    1    2    3    4    5    6    7
        // Used 3 Bit Numbers:  000  001  010  011  100  101  110  111
        if (bitsValue >= (int)MotorBits::motors_FFF)
        {
            // Set Bits-Value 
            L_bWise.SetBitsValue(bitsValue);
            // DEBUG Bit Places
            // Serial.println(L_bWise.PrintBinaryBits());
            // Reverse L298N Inputs
            L_ReverseInputs = L_bWise.IsBitNumberSet((int)MotorBits::motors_bitZero);
            // Change the Direction Left Motor
            L_DirectionLeftMotor = L_bWise.IsBitNumberSet((int)MotorBits::motors_bitOne);
            // Change the Direction Right Motor
            L_DirectionRightMotor = L_bWise.IsBitNumberSet((int)MotorBits::motors_bitTwo);
        }
    }

    void L298N::UpdateL298N(int PWM_LeftMotor, int PWM_RightMotor, bool PowerMotors = false)
    {
        if (L_ReverseInputs)
        {
            L_PWM_LeftMotor = PWM_LeftMotor;
            L_PWM_RightMotor = PWM_RightMotor;
        }
        else
        {
            L_PWM_LeftMotor = PWM_RightMotor;
            L_PWM_RightMotor = PWM_LeftMotor;
        }

        // Requires the Negative values (-/+)
        L_SetDirectionPins();

        // Takes the Absolute values (+) only
        if (PowerMotors)
        {
            analogWrite(L_LeftMotorPWM, abs(PWM_LeftMotor));
            analogWrite(L_RightMotorPWM, abs(PWM_RightMotor));
        }
    }

    void L298N::PowerDownL298N()
    {
        L_PowerDownL298N();
    }

    void L298N::L_PowerDownL298N()
    {
        // Experimental
        UpdateL298N((int)L_ZERO, (int)L_ZERO);
    }

    void L298N::L_SetDirectionPins()
    {
        if (L_PWM_LeftMotor >= L_ZERO)
        {
            if (L_DirectionLeftMotor)
            {
                digitalWrite(L_LeftMotorIN1, LOW);
                digitalWrite(L_LeftMotorIN2, HIGH);
            }
            else
            {
                digitalWrite(L_LeftMotorIN2, LOW);
                digitalWrite(L_LeftMotorIN1, HIGH);
            }
        }
        else if (L_PWM_LeftMotor < L_ZERO)
        {
            if (L_DirectionLeftMotor)
            {
                digitalWrite(L_LeftMotorIN2, LOW);
                digitalWrite(L_LeftMotorIN1, HIGH);
            }
            else
            {
                digitalWrite(L_LeftMotorIN1, LOW);
                digitalWrite(L_LeftMotorIN2, HIGH);
            }
        }

        if (L_PWM_RightMotor >= L_ZERO)
        {
            if (L_DirectionRightMotor)
            {
                digitalWrite(L_RightMotorIN1, LOW);
                digitalWrite(L_RightMotorIN2, HIGH);
            }
            else
            {
                digitalWrite(L_RightMotorIN2, LOW);
                digitalWrite(L_RightMotorIN1, HIGH);
            }
        }
        else if (L_PWM_RightMotor < L_ZERO)
        {
            if (L_DirectionRightMotor)
            {
                digitalWrite(L_RightMotorIN2, LOW);
                digitalWrite(L_RightMotorIN1, HIGH);
            }
            else
            {
                digitalWrite(L_RightMotorIN1, LOW);
                digitalWrite(L_RightMotorIN2, HIGH);
            }
        }
    }
}

#endif
