//
// Carpenter Software
// File: L01_Bitwise.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L01_Bitwise, selected with LESSON 1 in Step5_MathLessons/main.cpp
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
// RELEASE
//   2026-10-30  v7.3.0
//   L01_Bitwise.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

// TEACHING NOTES (v6.1.1)
// Lesson 1: bits and the Bitwise class. The terms (bit, bit number,
// least significant bit, mask, the operators | & ~) are defined at the
// top of include/numerics/Bitwise.h; read them first.
// Why it matters for the robot: the Bits() value of L298N.h is four
// bits, and each bit corrects one wiring choice of Article 1009, L298N
// Setup (Motor Movement Checklist).
// The topics run in the order T01 to T06 (see Setup() at the end); the
// functions are written in the file in the reverse order.
// Bitwise<int> uses an int, 16 bits on the Uno, so PrintBinaryBits()
// prints 16 digits in four groups of 4.
#ifndef Lesson_L01_Bitwise_h
#define Lesson_L01_Bitwise_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 6

#include <Arduino.h>
#include "Debug.h"
#include "numerics/Bitwise.h"
#include "Timer.h"

namespace L01_Bitwise
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// ReverseBits() was a member of the Numerics Bitwise class. The
// Code-JUL Bitwise.h is kept unchanged for Step2_JUL, so this
// lesson defines the function itself. It returns bitsValue with its
// bit order reversed: bit 0 becomes the highest bit, and so on.
// Each pass moves the lowest bit of bitsVal into the lowest bit of
// result, after result has moved up one place: the bit that leaves first
// ends highest. Example (8 bits): 0000 0110 becomes 0110 0000.
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

// T06: 0b introduces a binary constant. Expected output:
//   bits: 1011 0010 0000 0000
//   bits: 0000 0000 0100 1101     (the value 77)
// ---------------------------------------------------------------
// Bitwise_T06_ReverseBits (teaching notes, v6.3.0)
// Hint: ReverseBits, mirror the order of the bits.
// Purpose: a worked loop of shifts that moves each bit to the mirror
// position: bit 0 to bit 15, bit 1 to bit 14, and so on.
// What is learnt:
//   Binary literal 0b1011001000000000: the prefix 0b writes a constant
//                  in binary (a GNU extension in C++11, standard in C++14).
//   Shift operators  result <<= 1 moves every bit one place left;
//                  bitsVal >>= 1 one place right.
//   bitsVal & 1    isolates the lowest bit, the one that leaves next.
//   Function template ReverseBits<integer>() works for any integer type;
//                  sizeof(bitsValue) * 8 gives its number of bits.
//   Range of int  on the ATmega328P an int has 16 bits and holds
//                  -32768 to 32767. 0b1011001000000000 is 45568, more
//                  than 32767, so int a stores 45568 - 65536 = -19968:
//                  the same 16 bits, read with the top bit as the sign
//                  (two's complement). The bit pattern is unchanged.
//   unsigned int   16 bits that hold 0 to 65535; 45568 fits, and the
//                  shifts never reach a sign bit. v6.4.1 adds this case
//                  and prints each value with a label.
// Expected output:
//   int a = -19968
//   bits: 1011 0010 0000 0000
//   int b = ReverseBits(a) = 77
//   bits: 0000 0000 0100 1101     (the value 77 = 64 + 8 + 4 + 1)
//    ** unsigned int holds 0 to 65535 **
//   unsigned int ua = 45568
//   bits: 1011 0010 0000 0000
//   unsigned int ub = ReverseBits(ua) = 77
//   bits: 0000 0000 0100 1101
// ---------------------------------------------------------------
void Bitwise_T06_ReverseBits()
{
    printTitle(F("Bitwise T06 Reverse Bits"));

    Bitwise<int> bw;
    int a = 0b1011001000000000;
    // v6.4.1: label and value of a
    Serial.print(F("int a = "));
    Serial.println(a);
    bw.SetBitsValue(a);
    Serial.println(bw.PrintBinaryBits());
    int b = ReverseBits(a);
    // v6.4.1
    Serial.print(F("int b = ReverseBits(a) = "));
    Serial.println(b);
    bw.SetBitsValue(b);
    Serial.println(bw.PrintBinaryBits());

    // v6.4.1: the same bits in an unsigned int, which holds 45568.
    printSubTitle(F("unsigned int holds 0 to 65535"));
    Bitwise<unsigned int> ubw;
    unsigned int ua = 0b1011001000000000;
    Serial.print(F("unsigned int ua = "));
    Serial.println(ua);
    ubw.SetBitsValue(ua);
    Serial.println(ubw.PrintBinaryBits());
    unsigned int ub = ReverseBits(ua);
    Serial.print(F("unsigned int ub = ReverseBits(ua) = "));
    Serial.println(ub);
    ubw.SetBitsValue(ub);
    Serial.println(ubw.PrintBinaryBits());
}

// T05: counts down from 10 to 0, one value every 0.5 s (Timer.h); each
// line shows the value read back with GetBitsValue() and its bits.
// Example: 10 is 0000 0000 0000 1010 (8 + 2).
// ---------------------------------------------------------------
// Bitwise_T05_GetBitsValue (teaching notes, v6.3.0)
// Hint: GetBitsValue, read back the whole stored value.
// Purpose: to show that the getter returns exactly what the setter
// wrote, while counting down from 10 to 0.
// What is learnt:
//   A setter and a getter work as a pair: SetBitsValue(cnt) followed by
//   GetBitsValue() returns cnt. The first SetBitsValue(99) is replaced
//   before it is ever printed, because each new value overwrites the
//   old one.
//   printSpecial() prints a label, an integer, and a String on one line.
// Expected output (11 lines, 10 to 0):
//   Bits Value: 10 - bits: 0000 0000 0000 1010
//   ...
//   Bits Value: 0 - bits: 0000 0000 0000 0000
// ---------------------------------------------------------------
void Bitwise_T05_GetBitsValue()
{
    printTitle(F("Bitwise T05 GetBitsValue"));

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
            printSpecial("Bits Value: ", bw.GetBitsValue(),
                         bw.PrintBinaryBits());
            // counter
            cnt--;
        }
        // Iterates less than a minute
    } while (cnt >= 0);
}

// T04: counts up from 0 to 9, one value every 0.5 s; watch bit 0
// change on every line and bit 1 on every second line.
// ---------------------------------------------------------------
// Bitwise_T04_SetBitsValue (teaching notes, v6.3.0)
// Hint: SetBitsValue, write a whole value at once, all 16 bits.
// Purpose: how a decimal count looks in binary, one line every 0.5 s.
// What is learnt:
//   SetBitsValue(cnt) replaces every bit; SetBitNumber() changes one.
//   Binary counting: bit 0 changes on every line, bit 1 every second
//   line, bit 2 every fourth line; each bit is worth twice the one to
//   its right.
//   Timer.h paces the loop without delay(): isTimer(500) returns true
//   once every 500 ms, and the loop keeps running between the lines.
// Expected output (10 lines, 0 to 9):
//   Bits Value: 0 - bits: 0000 0000 0000 0000
//   Bits Value: 1 - bits: 0000 0000 0000 0001
//   ...
//   Bits Value: 9 - bits: 0000 0000 0000 1001
// ---------------------------------------------------------------
void Bitwise_T04_SetBitsValue()
{
    printTitle(F("Bitwise T04 SetBitsValue"));

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

// T03: sets bit 0 (value 1, IsBitNumberSet(0) true), then clears it
// (value 0, false).
// ---------------------------------------------------------------
// Bitwise_T03_ClearBitNumber (teaching notes, v6.3.0)
// Hint: ClearBitNumber, clear (make 0) one bit chosen by its number.
// Purpose: how to turn a single bit off again, the opposite of T02.
// What is learnt:
//   Clearing a bit is an AND with the inverted mask, value & ~(2^n):
//   every bit of the mask is 1 except bit n, so only bit n changes.
//   Set, test, clear: the three basic bit operations used for flags,
//   where one bit records one yes or no condition.
// Expected output:
//   bw.GetBitsValue(): 1      bw.IsBitNumberSet(0): true
//   bits: 0000 0000 0000 0001
//   bw.GetBitsValue(): 0      bw.IsBitNumberSet(0): false
//   bits: 0000 0000 0000 0000
// ---------------------------------------------------------------
void Bitwise_T03_ClearBitNumber()
{
    printTitle(F("Bitwise T03 ClearBitNumber"));

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

// T02: sets bit 0 and bit 3: 2^0 + 2^3 = 1 + 8 = 9, binary 1001.
// ---------------------------------------------------------------
// Bitwise_T02_SetBitNumber (teaching notes, v6.3.0)
// Hint: SetBitNumber, set (make 1) one bit chosen by its bit number.
// Purpose: how to turn on single bits and read the value they make.
// What is learnt:
//   Bit number     the position of a bit, counted from 0 at the right
//                  (the least significant bit, worth 2^0 = 1).
//   Setter         SetBitNumber(n) writes to the object: it sets bit n
//                  and leaves the other bits unchanged (an OR with the
//                  mask 2^n). A setter (also called a mutator) changes a
//                  private member through a member function.
//   Place value    each set bit adds 2^n: bits 0 and 3 give 1 + 8 = 9.
//   Debug(msg, a)  a helper of MiscMath.h that prints a label and values;
//                  it names its first value a, so a: 9 reads "the value
//                  is 9".
// Expected output:
//   bw.IsBitNumberSet(0): true
//   bw.IsBitNumberSet(3): true
//   bw.GetBitsValue():  a: 9
//   bits: 0000 0000 0000 1001
// ---------------------------------------------------------------
void Bitwise_T02_SetBitNumber()
{
    printTitle(F("Bitwise T02 SetBitNumber"));

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

// T01: a new Bitwise starts with every bit 0: value 0, bit 0 false.
// ---------------------------------------------------------------
// Bitwise_T01_Constructor (teaching notes, v6.3.0)
// Hint: Constructor, the special member function that runs when an
// object is created and sets its starting values.
// Purpose: how to declare and instantiate a Bitwise object, and what a
// new object holds before any bit is set.
// What is learnt:
//   Declaration    Bitwise<int> bw; names the variable bw and its type.
//   Template       Bitwise is a class template: a class written once for
//                  any integer type. The template argument in the angle
//                  brackets, <int>, selects the type that stores the bits
//                  (int is 16 bits on the Uno; uint8_t would give 8).
//   Instantiation  creating the object in memory. Bitwise<int> bw; with
//                  no parentheses calls the default constructor, the one
//                  that takes no arguments. Bitwise<int> bw(); would
//                  declare a function named bw instead (the rule of C++
//                  known as the most vexing parse).
//   Getter         GetBitsValue() reads the stored value; a getter (also
//                  called an accessor) reads a private member without
//                  changing it.
//   Query          IsBitNumberSet(0) answers true or false for one bit.
//   PrintBinaryBits() returns a String of 16 digits in groups of four.
// Expected output:
//   Bitwise<int> bw;
//   bw.GetBitsValue(): 0
//   bw.IsBitNumberSet(0): false
//   bits: 0000 0000 0000 0000
// ---------------------------------------------------------------
void Bitwise_T01_Constructor()
{
    printTitle(F("Bitwise T01 Constructor"));
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

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    Bitwise_T01_Constructor();
#endif
#if TOPIC == 0 || TOPIC == 2
    Bitwise_T02_SetBitNumber();
#endif
#if TOPIC == 0 || TOPIC == 3
    Bitwise_T03_ClearBitNumber();
#endif
#if TOPIC == 0 || TOPIC == 4
    Bitwise_T04_SetBitsValue();
#endif
#if TOPIC == 0 || TOPIC == 5
    Bitwise_T05_GetBitsValue();
#endif
#if TOPIC == 0 || TOPIC == 6
    Bitwise_T06_ReverseBits();
#endif
}

void Loop()
{
}
// namespace L01_Bitwise
}

// Lesson_L01_Bitwise_h
#endif
