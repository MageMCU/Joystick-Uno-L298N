//
// Carpenter Software
// File: Class L298NPins.h
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
// Added 20261017 for Step2_Generator.
//
// FOLDER include/claude
// The files in include/claude were written with Claude (Anthropic),
// an AI assistant, at the request of Jesse Carpenter, on 20261017.
// They are kept apart from the original header files of include/ and
// include/numerics/, which they do not change, so that a reader can
// tell at once which code is original and which was generated. Each
// file was tested against the original code as stated below; the
// bench test on hardware is pending.
//
// L298NPins resolves one Bits() value of L298N.h into fixed pin
// assignments. L298N.h decides at run time, on every call of
// UpdateL298N(), which enable pin and which IN pair follow each
// command. Once the Bits value of a bench is known, that decision
// never changes, so it can be made once and written into the program
// as constants. This class makes that decision with the same four
// rules as L298N::Bits() and L298N::UpdateL298N():
//
//   Bit 3, EN:      1 = _EN_A with the left IN pair, _EN_B with
//                       the right; 0 = enable pins crossed
//   Bit 2, PWM:     1 = left IN pair follows the left command;
//                   0 = left and right commands swapped
//   Bit 1, LeftIN:  1 = positive command sets IN_A LOW, IN_B HIGH;
//                   0 = positive command sets IN_A HIGH, IN_B LOW
//   Bit 0, RightIN: same as bit 1, for the right IN pair
//
// The result is one MotorPins record for each command:
//   EN:  the enable pin that receives the duty cycle of the command
//   FWD: the IN pin set HIGH when the command is zero or positive
//   REV: the IN pin set HIGH when the command is negative
// The other pin of the pair is always written LOW first.
//
// KEEP IN STEP WITH L298N.h: these rules repeat those of L298N.h. If
// L298N::Bits() or L298N::UpdateL298N() is changed, change Resolve()
// to match. Tested 20261017: for all 16 Bits values and seven command
// pairs, L298NPins with the printed driveMotor() sets the same pin
// levels and duty cycles as L298N::UpdateL298N().

#ifndef L298NPins_h
#define L298NPins_h

#include <Arduino.h>
#include "L298N.h"
#include "numerics/Bitwise.h"

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    struct MotorPins
    {
        uint8_t EN;
        uint8_t FWD;
        uint8_t REV;
    };

    class L298NPins
    {
        // Same constructor order and names as L298N.h
        uint8_t _EN_A;
        uint8_t _LeftIN_A;
        uint8_t _LeftIN_B;
        uint8_t _RightIN_A;
        uint8_t _RightIN_B;
        uint8_t _EN_B;

        int _bitsValue;
        MotorPins _left;  // pins that follow the left command
        MotorPins _right; // pins that follow the right command

    public:
        L298NPins();
        L298NPins(uint8_t LeftEN,
                  uint8_t LeftA,
                  uint8_t LeftB,
                  uint8_t RightA,
                  uint8_t RightB,
                  uint8_t RightEN);

        void Resolve(BitsL298N bitsValue);
        int GetBitsValue() { return _bitsValue; }
        MotorPins Left() { return _left; }
        MotorPins Right() { return _right; }
    };

    // Default pins, the same as the L298N default constructor
    L298NPins::L298NPins()
    {
        _EN_A = 5;
        _LeftIN_A = 6;
        _LeftIN_B = 7;
        _RightIN_A = 8;
        _RightIN_B = 9;
        _EN_B = 10;
        Resolve(BitsL298N::bits_1111);
    }

    L298NPins::L298NPins(uint8_t LeftEN,
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
        Resolve(BitsL298N::bits_1111);
    }

    void L298NPins::Resolve(BitsL298N bitsValue)
    {
        Bitwise<int> bWise;
        _bitsValue = (int)bitsValue - (int)BitsL298N::bits_0000;

        bool bitEN = bWise.IsBitNumberSetToBitsValue((int)BitsL298N::bitEN, _bitsValue);
        bool bitPWM = bWise.IsBitNumberSetToBitsValue((int)BitsL298N::bitPWM, _bitsValue);
        bool bitLeftIN = bWise.IsBitNumberSetToBitsValue((int)BitsL298N::bitLeftIN, _bitsValue);
        bool bitRightIN = bWise.IsBitNumberSetToBitsValue((int)BitsL298N::bitRightIN, _bitsValue);

        // Channel A: the left IN pair and the enable pin chosen by bit 3.
        // Channel B: the right IN pair and the other enable pin.
        MotorPins channelA;
        channelA.EN = bitEN ? _EN_A : _EN_B;
        channelA.FWD = bitLeftIN ? _LeftIN_B : _LeftIN_A;
        channelA.REV = bitLeftIN ? _LeftIN_A : _LeftIN_B;

        MotorPins channelB;
        channelB.EN = bitEN ? _EN_B : _EN_A;
        channelB.FWD = bitRightIN ? _RightIN_B : _RightIN_A;
        channelB.REV = bitRightIN ? _RightIN_A : _RightIN_B;

        // Bit 2 decides which command drives channel A.
        _left = bitPWM ? channelA : channelB;
        _right = bitPWM ? channelB : channelA;
    }
}

#endif
