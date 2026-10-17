//
// Carpenter Software
// File: main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step3_MathLessons/01_Bitwise
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestBitwise.h (merged 20261008)
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

#include <Arduino.h>
#include "Debug.h"
#include "numerics/Bitwise.h"
#include "Timer.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// ReverseBits() was a member of the Numerics Bitwise class. The
// Code-JUL Bitwise.h is kept unchanged for Step1 and Step2, so this
// lesson defines the function itself. It returns bitsValue with its
// bit order reversed: bit 0 becomes the highest bit, and so on.
template <typename integer>
integer ReverseBits(integer bitsValue)
{
    int numBits = sizeof(bitsValue) * 8;
    integer bitsVal = bitsValue;
    integer result = (integer)0;
    for (int i = 0; i < numBits; i++)
    {
        // Shift result left by 1
        result <<= 1;
        // Set the least significant bit of result
        // to the least significant bit of bitsVal.
        result |= (bitsVal & 1);
        // Shift bitsVal right by 1
        bitsVal >>= 1;
    }
    return result;
}

void Bitwise_T6_ReverseBits()
{
    printTitle("Bitwise T6 Reverse Bits");

    Bitwise<int> bw;
    int a = 0b1011001000000000;
    bw.SetBitsValue(a);
    Serial.println(bw.PrintBinaryBits());
    int b = ReverseBits(a);
    bw.SetBitsValue(b);
    Serial.println(bw.PrintBinaryBits());
}

void Bitwise_T5_GetBitsValue()
{
    printTitle("Bitwise T5 GetBitsValue");

    Bitwise<int> bw;
    bw.SetBitsValue(99);
    // Timer Instantiation
    Timer testTimer = Timer();
    // Test
    int cnt = 10;
    do
    {
        if (testTimer.isTimer(500))
        {
            bw.SetBitsValue(cnt);
            printSpecial("Bits Value: ", bw.GetBitsValue(), bw.PrintBinaryBits());
            // counter
            cnt--;
        }
        // Iterates less than a minute
    } while (cnt >= 0);
}

void Bitwise_T4_SetBitsValue()
{
    printTitle("Bitwise T4 SetBitsValue");

    Bitwise<int> bw;
    // Timer Instantiation
    Timer testTimer = Timer();
    // Test
    int cnt = 0;
    do
    {
        if (testTimer.isTimer(500))
        {
            bw.SetBitsValue(cnt);
            printSpecial("Bits Value: ", cnt, bw.PrintBinaryBits());
            // counter
            cnt++;
        }
        // Iterates less than a minute
    } while (cnt < 10);
}

void Bitwise_T3_ClearBitNUmber()
{
    printTitle("Bitwise T3_ClearBitNUmber");

    Bitwise<int> bw;
    bw.SetBitNumber(0);
    Serial.println("bw.SetBitNumber(0) ");
    Serial.print("bw.GetBitsValue(): ");
    Serial.println(bw.GetBitsValue());
    Serial.print("bw.IsBitNumberSet(0): ");
    if (bw.IsBitNumberSet(0))
    {
        Serial.println("true");
    }
    else
    {
        Serial.println("false");
    }
    Serial.println(bw.PrintBinaryBits());

    bw.ClearBitNumber(0);
    Serial.println("bw.ClearBitNumber(0) ");
    Serial.print("bw.GetBitsValue(): ");
    Serial.println(bw.GetBitsValue());
    Serial.print("bw.IsBitNumberSet(0): ");
    if (bw.IsBitNumberSet(0))
    {
        Serial.println("true");
    }
    else
    {
        Serial.println("false");
    }
    Serial.println(bw.PrintBinaryBits());
}

void Bitwise_T2_SetBitNumber()
{
    printTitle("Bitwise T2_SetBitNumber");

    Bitwise<int> bw;
    bw.SetBitNumber(0);
    Debug("bw.SetBitNumber(0)");

    Serial.print("bw.IsBitNumberSet(0): ");
    if (bw.IsBitNumberSet(0))
        Serial.println("true");
    else
        Serial.println("false");

    bw.SetBitNumber(3);
    Debug("bw.SetBitNumber(3)");

    Serial.print("bw.IsBitNumberSet(3): ");
    if (bw.IsBitNumberSet(3))
        Serial.println("true");
    else
        Serial.println("false");
    //
    Debug("bw.GetBitsValue(): ", bw.GetBitsValue());
    Serial.println(bw.PrintBinaryBits());
}

void Bitwise_T1_Constructor()
{
    printTitle("Bitwise T1 Constructor");
    // Constructor
    Bitwise<int> bw;
    Serial.println("Bitwise<int> bw; ");
    //
    Serial.print("bw.GetBitsValue(): ");
    Serial.println(bw.GetBitsValue());

    Serial.print("bw.IsBitNumberSet(0): ");
    if (bw.IsBitNumberSet(0))
        Serial.println("true");
    else
        Serial.println("false");
    Serial.println(bw.PrintBinaryBits());
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Bitwise tests, in order
    Bitwise_T1_Constructor();
    Bitwise_T2_SetBitNumber();
    Bitwise_T3_ClearBitNUmber();
    Bitwise_T4_SetBitsValue();
    Bitwise_T5_GetBitsValue();
    Bitwise_T6_ReverseBits();
}

void loop()
{
}
