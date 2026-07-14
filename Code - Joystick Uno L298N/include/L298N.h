//
// Carpenter Software
// File: Class L298N.h
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

#ifndef L298N_h
#define L298N_h

#include <Arduino.h>
#include "Bitwise.h"
#include "MiscMath.h"
#include "Common.h"

#define ZERO 0x0

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    enum BitsL298N
    {
        // See the Bits() Method
        // Bit-Order: 3,2,1,0 (decimal value: 8+4+2+1 = 15)
        // Change the Direction Right Motor (Bit-0)
        bitRightIN = 0,
        // Change the Direction Left Motor (Bit-1)
        bitLeftIN,
        // Reverse L298N Inputs (Bit-2)
        bitPWM,
        // Swap motors
        bitEN,
        // Motors A&B
        bits_0000, // 4
        bits_0001,
        bits_0010,
        bits_0011,
        bits_0100,
        bits_0101,
        bits_0110,
        bits_0111,
        // Motors Swapped  B&A
        bits_1000,
        bits_1001,
        bits_1010,
        bits_1011,
        bits_1100,
        bits_1101,
        bits_1110,
        bits_1111
    };

    class L298N
    {
        // The names LEFT & RIGHT are misnomers and are
        // used only for name differenation...

        // Private Properties
        // Although used, there are no saved-values
        Bitwise<int> _bWise;
        int _bitsValue;

        // Used for motors setup() which aligns the
        // correct left and right directions...
        bool _bitRightIN_Flag; // Right Motor Direction
        bool _bitLeftIN_Flag;  // Left Motor Direction
        bool _bitPWM_Flag;     // Switch L298N Inputs
        bool _bitEN_Flag;      // Swap Motors

        // Used for L298N Pins
        uint8_t _EN_A;
        uint8_t _LeftIN_A;
        uint8_t _LeftIN_B;
        uint8_t _RightIN_A;
        uint8_t _RightIN_B;
        uint8_t _EN_B;

        // Input Values
        int _pwmA;
        int _pwmB;

        // Private Methods
        void _SetDirectionPins();
        void _LeftSet1(); // Priority Left
        void _LeftSet2();
        void _RightSet1();
        void _RightSet2();

    public:
        // Contructors
        L298N();
        L298N(uint8_t LeftEN,
              uint8_t LeftA,
              uint8_t LeftB,
              uint8_t RightA,
              uint8_t RightB,
              uint8_t RightEN);
        ~L298N() = default;

        // Public Methods
        void PinsL298N();
#ifdef DEBUG_L298N
        void DebugBits();
#endif
        void Bits(BitsL298N bitsValue);
        // PowerMotors safety switch (OFF false, ON true)
        void UpdateL298N(int outMapLeft, int outMapRight, bool SafetyMotorFlag);
        void PowerDownL298N();
    };

    // Default
    L298N::L298N()
    {
        _EN_A = 5;
        _LeftIN_A = 6;
        _LeftIN_B = 7;
        _RightIN_A = 8;
        _RightIN_B = 9;
        _EN_B = 10;
    }

    // set L298N Pins in setup()
    L298N::L298N(uint8_t LeftEN,
                 uint8_t LeftA,
                 uint8_t LeftB,
                 uint8_t RightA,
                 uint8_t RightB,
                 uint8_t RightEN)
    {
        _EN_A = LeftEN;
        _LeftIN_A = LeftA;
        _LeftIN_B = LeftB;
        _RightIN_A = RightA;
        _RightIN_B = RightB;
        _EN_B = RightEN;
    }

    // Used in setup()
    void L298N::PinsL298N()
    {
        pinMode(_EN_A, OUTPUT);
        pinMode(_LeftIN_A, OUTPUT);
        pinMode(_LeftIN_B, OUTPUT);
        pinMode(_RightIN_A, OUTPUT);
        pinMode(_RightIN_B, OUTPUT);
        pinMode(_EN_B, OUTPUT);
        PowerDownL298N();
    }

#ifdef DEBUG_L298N
    void L298N::DebugBits()
    {
        if (_bitEN_Flag)
            Serial.print("bit-order(3210): 1");
        else
            Serial.print("bit-order(3210): 0");
        if (_bitPWM_Flag)
            Serial.print("1");
        else
            Serial.print("0");
        if (_bitLeftIN_Flag)
            Serial.print("1");
        else
            Serial.print("0");
        if (_bitRightIN_Flag)
            Serial.print("1 val: ");
        else
            Serial.print("0 val: ");
        Serial.println(_bitsValue);
    }
#endif

    // Follow instructions in Supplimental Article...
    void L298N::Bits(BitsL298N bitsValue)
    {
        // DO NOT STORE THE _bitsValue VARIABLE IN THE CLASS Bitwise.h.
        // USE IT IN THIS CLASS ONLY...
        _bitsValue = (int)bitsValue - (int)BitsL298N::bits_0000;

        // There are 16 combinations for EN, PWM, LeftIN & RightIN
        // USE: analogWrite(EN, PWM) & digitalWrite(LeftIN1, LOW)...
        // The Boolean Order (3, 2, 1, 0)
        // (3) EN (AB):         (Bit-3)
        // (2) PWM Inputs (AB): (Bit-2)
        // (1) LeftIN (1 & 2): ( Bit-1)
        // (0) Right N (3 & 4): (Bit-0)
        // EN A & B ---------------------------------------------
        // Bits-Value:  0     1     2     3     4     5     6     7
        // Bits:       0000  0001  0010  0011  0100  0101  0110  0111
        // EN B & A ----------------------------------------------
        // Bits-Value:  8     9     10    11    12    13    14    15
        // Bits:       1000  1001  1010  1011  1100  1101  1110  1111
        // -----------------------------------------------------------
        // NOTICE: Changing the BITS is much easier than switching
        // the actual wires around on the L298N module....
        // For my setup, bits 1010 was used...

        // Swap motors (Bit-3)
        _bitEN_Flag = _bWise.IsBitNumberSetToBitsValue((int)BitsL298N::bitEN, _bitsValue);
        // Reverse L298N Inputs (Bit-2)
        _bitPWM_Flag = _bWise.IsBitNumberSetToBitsValue((int)BitsL298N::bitPWM, _bitsValue);
        // Change the Direction Left Motor (Bit-1)
        _bitLeftIN_Flag = _bWise.IsBitNumberSetToBitsValue((int)BitsL298N::bitLeftIN, _bitsValue);
        // Change the Direction Right Motor (Bit-0)
        _bitRightIN_Flag = _bWise.IsBitNumberSetToBitsValue((int)BitsL298N::bitRightIN, _bitsValue);

        // DEBUG
#ifdef DEBUG_L298N
        DebugBits();
#endif
    }

    // Used with a timer within loop()
    void L298N::UpdateL298N(int outMapLeft, int outMapRight, bool SafetyMotorFlag = false)
    {
        uint8_t ENA;
        uint8_t ENB;

        if (_bitEN_Flag)
        {
            ENA = _EN_A;
            ENB = _EN_B;
#ifdef DEBUG_L298N
            Serial.println("(A) Bit-EN");
#endif
        }
        else
        {
            ENA = _EN_B;
            ENB = _EN_A;
#ifdef DEBUG_L298N
            Serial.println("(B) Bit-EN");
#endif
        }

        // Reverse L298N Inputs (Bit-2 Flag)
        if (_bitPWM_Flag)
        {
            _pwmA = outMapLeft;
            _pwmB = outMapRight;
#ifdef DEBUG_L298N
            Serial.println("(A) Bit-PWM");
#endif
        }
        else
        {
            _pwmA = outMapRight;
            _pwmB = outMapLeft;
#ifdef DEBUG_L298N
            Serial.println("(B) Bit-PWM");
#endif
        }

        // Direction Pins require the Negative and Positive values (-/+)
        _SetDirectionPins();

        // L298N only receives positive integers (ABS_INTEGER)
        // SafetyMotorFlag = TRUE: MOTORS ACTIVE
        if (SafetyMotorFlag)
        {
            analogWrite(ENA, absT<int>(_pwmA));
            analogWrite(ENB, absT<int>(_pwmB));
        }
        else
        {
            analogWrite(ENA, LOW);
            analogWrite(ENB, LOW);
        }

        // DEBUG
#ifdef DEBUG_L298N
        DebugBits();
#endif
    }

    // Used with buttons-OFF
    void L298N::PowerDownL298N()
    {
        analogWrite(_EN_A, LOW);
        analogWrite(_EN_B, LOW);
    }

    // Private Method
    void L298N::_SetDirectionPins()
    {
        if (_pwmA >= ZERO)
        {
            // Left Motor Bit-1 Flag
            if (_bitLeftIN_Flag)
                _LeftSet1();
            else
                _LeftSet2();
        }
        else if (_pwmA < ZERO)
        {
            // Left Motor Bit-1 Flag
            if (_bitLeftIN_Flag)
                _LeftSet2();
            else
                _LeftSet1();
        }

        if (_pwmB >= ZERO)
        {
            // Right Motor Bit-0 Flag
            if (_bitRightIN_Flag)
                _RightSet1();
            else
                _RightSet2();
        }
        else if (_pwmB < ZERO)
        {
            // Right Motor Bit-0 Flag
            if (_bitRightIN_Flag)
                _RightSet2();
            else
                _RightSet1();
        }
    }

    // Private Method
    void L298N::_LeftSet1()
    {
        // Motors Output
        digitalWrite(_LeftIN_A, LOW);
        digitalWrite(_LeftIN_B, HIGH);
#ifdef DEBUG_L298N
        Serial.println("(1) LeftIn12");
#endif
    }

    // Private Method
    void L298N::_LeftSet2()
    {
        digitalWrite(_LeftIN_B, LOW);
        digitalWrite(_LeftIN_A, HIGH);
#ifdef DEBUG_L298N
        Serial.println("(2) LeftIn21");
#endif
    }

    // Private Method
    void L298N::_RightSet1()
    {
        digitalWrite(_RightIN_A, LOW);
        digitalWrite(_RightIN_B, HIGH);
#ifdef DEBUG_L298N
        Serial.println("(1) RightIn34");
#endif
    }

    // Private Method
    void L298N::_RightSet2()
    {
        digitalWrite(_RightIN_B, LOW);
        digitalWrite(_RightIN_A, HIGH);
#ifdef DEBUG_L298N
        Serial.println("(2) RightIn43");
#endif
    }
}

#endif