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
        private_bitZero = 0,
        private_bitOne,
        private_bitTwo,
        // Primary Inputs(bit-2xx) Left(bit-x1x) Right(bit-xx0) Motors Flags
        motorsFFF, // 3
        motorsFFT,
        motorsFTF,
        motorsFTT,
        motorsTFF,
        motorsTFT,
        motorsTTF,
        motorsTTT
    };

    class L298N
    {
    private:
        // The names LEFT & RIGHT are misnomers and are 
        // used only for name differenation...

        // Private Properties
        // Although used, there are no saved-values
        nmr::Bitwise<int> L_bWise;

        // Used with Arduino's digitalWrite()
        bool L_IsLeftL1H2;
        bool L_IsRightL1H2;

        // Used for motors setup() which aligns the
        // correct left and right directions...
        bool L_bitRightFlag; // Right Motor Direction
        bool L_bitLeftFlag; // Left Motor Direction
        bool L_bitReverseInputsFlag; // Switch L298N Inputs

        // Used for L298N Pins
        uint8_t L_ZERO;
        uint8_t L_LeftMotorPWM;
        uint8_t L_LeftMotorIN1;
        uint8_t L_LeftMotorIN2;
        uint8_t L_RightMotorIN1;
        uint8_t L_RightMotorIN2;
        uint8_t L_RightMotorPWM;
        // Input Values
        int L_PWM_LeftMotor;
        int L_PWM_RightMotor;
        // Private Methods
        void L_SetDirectionPins();
        void L_LeftL1H2(); // Priority Left
        void L_LeftL2H1();
        void L_RightL1H2();
        void L_RightL2H1();

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

        // Public Methods
        void PinsL298N();
        void Bits(MotorBits bitsValue);
        // PowerMotors safety switch (OFF false, ON true)
        void UpdateL298N(int UnoPWM_ToENA, int UnoPWM_ToENB, bool PowerMotors);
        void PowerDownL298N();
    };

    // Default
    L298N::L298N()
    {
        L_ZERO = 0;
        L_LeftMotorPWM = 10;
        L_LeftMotorIN1 = 9;
        L_LeftMotorIN2 = 8;
        L_RightMotorIN1 = 7;
        L_RightMotorIN2 = 6;
        L_RightMotorPWM = 5;
    }

    // set L298N Pins in setup()
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
    }

    // Used in setup()
    void L298N::PinsL298N()
    {
        pinMode(L_LeftMotorPWM, OUTPUT);
        pinMode(L_LeftMotorIN1, OUTPUT);
        pinMode(L_LeftMotorIN2, OUTPUT);
        pinMode(L_RightMotorIN1, OUTPUT);
        pinMode(L_RightMotorIN2, OUTPUT);
        pinMode(L_RightMotorPWM, OUTPUT);
        PowerDownL298N();
    }

    // Follow instructions in Supplimental Article...
    void L298N::Bits(MotorBits bitsValue)
    {
        int localBitsValue = (int)bitsValue - (int)MotorBits::motorsFFF;
        // There are 8 combinations for Reverse-Inputs and Direction-Motors
        // The Boolean Order 
            // (1)         Reverse Inouts: T/F (Bit-2)
            // (2)   Direction Left Motor: T/F (Bit-1)
            // (3) Direction Right Motoer: T/F (Bit-0)
            // Check conditions:    FFF, FFT, FTF, FTT, TFF, TFT, TTF, TTT
            // Local-Bits-Value:     0    1    2    3    4    5    6    7
            // Used 3 Bit Numbers:  000  001  010  011  100  101  110  111
            // DO NOT USE the private constants belonging to MotorBits...
        // Changing the truth table is much easier than switching the actual 
        // wires around on the L298N module.... For my setup, FFF was used...
        //
        // Change the Direction Right Motor (Bit-0)
        L_bitRightFlag = L_bWise.IsBitNumberSetToBitsValue((int)MotorBits::private_bitZero, localBitsValue);
        // Change the Direction Left Motor (Bit-1)
        L_bitLeftFlag = L_bWise.IsBitNumberSetToBitsValue((int)MotorBits::private_bitOne, localBitsValue);
        // Reverse L298N Inputs (Bit-2)
        L_bitReverseInputsFlag = L_bWise.IsBitNumberSetToBitsValue((int)MotorBits::private_bitTwo, localBitsValue);
    }

    // Used with a timer within loop()
    void L298N::UpdateL298N(int PWM_LeftMotor, int PWM_RightMotor, bool PowerMotors = false)
    {
        // Reverse L298N Inputs (Bit-2 Flag)
        if (L_bitReverseInputsFlag)
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

    // Used with buttons-OFF
    void L298N::PowerDownL298N()
    {
        UpdateL298N((int)L_ZERO, (int)L_ZERO);
    }

    // Private Method
    void L298N::L_SetDirectionPins()
    {
        if (L_PWM_LeftMotor >= L_ZERO)
        {
            // Left Motor Bit-1 Flag
            if (L_bitLeftFlag)
                L_LeftL1H2();
            else
                L_LeftL2H1();
        }
        else if (L_PWM_LeftMotor < L_ZERO)
        {
            // Left Motor Bit-1 Flag
            if (L_bitLeftFlag)
                L_LeftL2H1();
            else
                L_LeftL1H2();
        }

        if (L_PWM_RightMotor >= L_ZERO)
        {
            // Right Motor Bit-0 Flag
            if (L_bitRightFlag)
                L_RightL1H2();
            else
                L_RightL2H1();
        }
        else if (L_PWM_RightMotor < L_ZERO)
        {
            // Right Motor Bit-0 Flag
            if (L_bitRightFlag)
                L_RightL2H1();
            else
                L_RightL1H2();
        }
    }

    // Private Method
    void L298N::L_LeftL1H2()
    {
        // Motors Output
        digitalWrite(L_LeftMotorIN1, LOW);
        digitalWrite(L_LeftMotorIN2, HIGH);
        L_IsLeftL1H2 = true;
    }

    // Private Method
    void L298N::L_LeftL2H1()
    {
        digitalWrite(L_LeftMotorIN2, LOW);
        digitalWrite(L_LeftMotorIN1, HIGH);
        L_IsLeftL1H2 = false;
    }

    // Private Method
    void L298N::L_RightL1H2()
    {
        digitalWrite(L_RightMotorIN1, LOW);
        digitalWrite(L_RightMotorIN2, HIGH);
        L_IsRightL1H2 = true;
    }

    // Private Method
    void L298N::L_RightL2H1()
    {
        digitalWrite(L_RightMotorIN2, LOW);
        digitalWrite(L_RightMotorIN1, HIGH);
        L_IsRightL1H2 = false;
    }
}

#endif
