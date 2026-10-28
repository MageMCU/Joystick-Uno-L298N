//
// Carpenter Software
// File: L02_TypeConv.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L02_TypeConv, selected with LESSON 2 in Step5_MathLessons/main.cpp
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestTypeConv.h (merged 20261008)
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

// TEACHING NOTES (v6.1.1)
// Lesson 2: splitting numbers into bytes and joining them again. The
// terms (byte, word, double word, high and low byte, hexadecimal, the
// shift operators >> and <<) are defined at the top of
// include/numerics/TypeConv.h.
// Why it matters: a serial link, I2C, or EEPROM carries one byte at a
// time, so a 10 bit ADC reading (0 to 1023) travels as two bytes.
// INT16_MAX and INT32_MAX are the largest signed 16 and 32 bit values,
// 32767 and 2147483647 (2^15 - 1 and 2^31 - 1).
// The topics run T01 then T02 (see Setup()).
#ifndef Lesson_L02_TypeConv_h
#define Lesson_L02_TypeConv_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 2

#include <Arduino.h>
#include "Debug.h"
#include "numerics/TypeConv.h"

namespace L02_TypeConv
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// v6.4.1: prints a label, a byte in decimal, and the same byte in
// hexadecimal (base 16): Serial.print(value, HEX) prints 63 as 3F.
void printByte(const __FlashStringHelper *label, int value)
{
    Serial.print(label);
    Serial.print(value);
    Serial.print(F(" (0x"));
    Serial.print(value, HEX);
    Serial.print(F(")"));
}

// T02: 715827882 is 0x2AAAAAAA, so the four bytes are 42, 170, 170, 170
// (0x2A, 0xAA, 0xAA, 0xAA), and both joins return 715827882.
// ---------------------------------------------------------------
// TypeConv_T02_DWordTo4Bytes (teaching notes, v6.3.0)
// Hint: DWordTo4Bytes, split one 32 bit double word into four bytes.
// Purpose: the same split and join as T01, for a 32 bit value.
// What is learnt:
//   Double word    32 bits, four bytes: byte 3 is the highest (bits 24 to
//                  31), byte 0 the lowest (bits 0 to 7).
//   uint32_t, int32_t  fixed width integer types: u means unsigned, the
//                  number is the width in bits. A long is also 32 bits on
//                  the Uno, but the fixed width names state it.
//   Getters        GetByte3() to GetByte0().
//   Hexadecimal    one hex digit is four bits, so 0x2AAAAAAA shows the
//                  bytes directly: 2A AA AA AA = 42 170 170 170.
//   Debug labels   Debug() of MiscMath.h names its values a, b, c, d in
//                  the order passed; here a is b3 and d is b0. v6.4.1 adds
//                  a line that names each byte and prints it in hex.
// Expected output:
//   INT32_MAX a: 2147483647
//   DWordTo4Bytes(715827882):  a: 42 b: 170 c: 170 d: 170
//   b3 42 (0x2A)  b2 170 (0xAA)  b1 170 (0xAA)  b0 170 (0xAA)
//   BytesToDWord():  a: 715827882
//   BytesToDWord(b3, b2, b1, b0):  a: 715827882
// ---------------------------------------------------------------
void TypeConv_T02_DWordTo4Bytes()
{
    printTitle(F("TypeConv T02 DWordTo4Bytes"));
    // Notice no parenthesis...
    TypeConv typeConv;

    Debug("INT32_MAX", INT32_MAX);
    uint32_t a = 715827882;
    typeConv.DWordTo4Bytes(a);
    int b3 = typeConv.GetByte3();
    int b2 = typeConv.GetByte2();
    int b1 = typeConv.GetByte1();
    int b0 = typeConv.GetByte0();
    Debug("DWordTo4Bytes(715827882): ", b3, b2, b1, b0);
    // v6.4.1: name each byte and show it in hexadecimal.
    printByte(F("b3 "), b3);
    printByte(F("  b2 "), b2);
    printByte(F("  b1 "), b1);
    printByte(F("  b0 "), b0);
    Serial.println();
    // The Code-JUL TypeConv.h has no GetDWord(); BytesToDWord()
    // returns the same value.
    int32_t dWd = typeConv.BytesToDWord();
    Debug("BytesToDWord(): ", dWd);

    dWd = typeConv.BytesToDWord(b3, b2, b1, b0);
    Debug("BytesToDWord(b3, b2, b1, b0): ", dWd);
}

// T01: 16234 is 0x3F6A, so the high byte is 63 (0x3F) and the low byte
// 106 (0x6A); 63 * 256 + 106 = 16234, which both joins return.
// ---------------------------------------------------------------
// TypeConv_T01_WordTo2Bytes (teaching notes, v6.3.0)
// Hint: WordTo2Bytes, split one 16 bit word into its two bytes.
// Purpose: how a value larger than one byte is cut into bytes for a
// link that carries one byte at a time, and joined again.
// What is learnt:
//   Declaration and instantiation: TypeConv typeConv; TypeConv is an
//                  ordinary class, not a template, so it has no angle
//                  brackets, and no parentheses (the default constructor).
//   Word           16 bits; high byte = word >> 8, low byte = word & 0xFF.
//   Getters        GetHiByte() and GetLoByte() read the two bytes stored
//                  by WordTo2Bytes().
//   Overloads      BytesToWord() joins the stored bytes; BytesToWord(hi,
//                  lo) joins the two bytes passed to it. Two functions with
//                  one name and different parameters are overloads.
//   Join           word = hi * 256 + lo = (hi << 8) | lo.
//   Debug labels   Debug() names its values a and b in the order passed:
//                  a is hi, b is lo. v6.4.1 adds a line that names each
//                  byte and prints it in hex.
// Expected output:
//   INT16_MAX a: 32767
//   WordTo2Bytes(16234) a: 63 b: 106
//   hi 63 (0x3F)  lo 106 (0x6A)
//   BytesToWord:  a: 16234
//   BytesToWord(hi, lo):  a: 16234
// ---------------------------------------------------------------
void TypeConv_T01_WordTo2Bytes()
{
    printTitle(F("TypeConv T01 WordTo2Bytes"));
    // Notice no parenthesis...
    TypeConv typeConv;

    Debug("INT16_MAX", INT16_MAX);
    int a = 16234;
    typeConv.WordTo2Bytes(a);
    int hi = typeConv.GetHiByte();
    int lo = typeConv.GetLoByte();
    Debug("WordTo2Bytes(16234)", hi, lo);
    // v6.4.1: name each byte and show it in hexadecimal.
    printByte(F("hi "), hi);
    printByte(F("  lo "), lo);
    Serial.println();

    // The Code-JUL TypeConv.h has no GetWord(); BytesToWord()
    // returns the same value.
    int wd = typeConv.BytesToWord();
    Debug("BytesToWord: ", wd);

    wd = typeConv.BytesToWord(hi, lo);
    Debug("BytesToWord(hi, lo): ", wd);
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    TypeConv_T01_WordTo2Bytes();
#endif
#if TOPIC == 0 || TOPIC == 2
    TypeConv_T02_DWordTo4Bytes();
#endif
}

void Loop()
{
}
// namespace L02_TypeConv
}

// Lesson_L02_TypeConv_h
#endif
