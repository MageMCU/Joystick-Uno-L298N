//
// Carpenter Software
// File: Class L298N.h
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

#ifndef L298N_h
#define L298N_h

#include <Arduino.h>
#include "numerics/Bitwise.h"
#include "numerics/MiscMath.h"
#include "Common.h"

#define ZERO 0x0

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    enum BitsL298N
    {
        // See the Bits() method and Article 1009, Table-3
        // Bit order: 3, 2, 1, 0 (decimal value: 8+4+2+1 = 15)
        // Right IN pair direction convention (bit 0)
        bitRightIN = 0,
        // Left IN pair direction convention (bit 1)
        bitLeftIN,
        // 1: left IN pair follows the left command (bit 2)
        bitPWM,
        // 1: enable pins straight; 0: crossed (bit 3)
        bitEN,
        // Enable pins crossed (bit 3 = 0)
        bits_0000, // enumeration value 4; Bits() subtracts it
        bits_0001,
        bits_0010,
        bits_0011,
        bits_0100,
        bits_0101,
        bits_0110,
        bits_0111,
        // Enable pins straight (bit 3 = 1)
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
        bool _bitRightIN_Flag; // Bit 0: right IN pair convention
        bool _bitLeftIN_Flag;  // Bit 1: left IN pair convention
        bool _bitPWM_Flag;     // Bit 2: false swaps the commands
        bool _bitEN_Flag;      // Bit 3: false crosses the enable pins

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

    // Article 1009, L298N Setup, finds the value for a bench.
    void L298N::Bits(BitsL298N bitsValue)
    {
        // DO NOT STORE THE _bitsValue VARIABLE IN THE CLASS Bitwise.h.
        // USE IT IN THIS CLASS ONLY...
        _bitsValue = (int)bitsValue - (int)BitsL298N::bits_0000;

        // 16 patterns, written bit 3, 2, 1, 0 (Article 1009, Table-3)
        // USE: analogWrite(EN, PWM) and digitalWrite(IN, LOW or HIGH)
        // Bit 3, EN:      1 = _EN_A with the left IN pair, _EN_B with
        //                     the right; 0 = enable pins crossed
        // Bit 2, PWM:     1 = left IN pair follows the left command;
        //                 0 = left and right commands swapped
        // Bit 1, LeftIN:  1 = positive command sets IN_A LOW, IN_B HIGH;
        //                 0 = positive command sets IN_A HIGH, IN_B LOW
        // Bit 0, RightIN: same as bit 1, for the right IN pair
        // Enable pins crossed (bit 3 = 0) --------------------------
        // Bits value:  0     1     2     3     4     5     6     7
        // Bits:       0000  0001  0010  0011  0100  0101  0110  0111
        // Enable pins straight (bit 3 = 1) -------------------------
        // Bits value:  8     9     10    11    12    13    14    15
        // Bits:       1000  1001  1010  1011  1100  1101  1110  1111
        // -----------------------------------------------------------
        // Changing the value is easier than moving wires on the L298N.
        // The author's bench uses bits_1010.

        // Bit 3: 1 = enable pins straight, 0 = crossed
        _bitEN_Flag = _bWise.IsBitNumberSetToBitsValue((int)BitsL298N::bitEN, _bitsValue);
        // Bit 2: 1 = commands straight, 0 = swapped
        _bitPWM_Flag = _bWise.IsBitNumberSetToBitsValue((int)BitsL298N::bitPWM, _bitsValue);
        // Bit 1: left IN pair direction convention
        _bitLeftIN_Flag = _bWise.IsBitNumberSetToBitsValue((int)BitsL298N::bitLeftIN, _bitsValue);
        // Bit 0: right IN pair direction convention
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

        // Bit 2: 1 = commands straight, 0 = swapped
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
