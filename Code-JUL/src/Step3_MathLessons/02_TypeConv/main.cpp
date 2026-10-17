//
// Carpenter Software
// File: main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step3_MathLessons/02_TypeConv
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

#include <Arduino.h>
#include "Debug.h"
#include "numerics/TypeConv.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

#include "Arduino.h"

void TypeConv_T2_DWordTo4Bytes()
{
    printTitle("TypeConv T2 DWordTo4Bytes");
    // Notice no parenthsis...
    TypeConv typeConv;

    Debug("INT32_MAX", INT32_MAX);
    uint32_t a = 715827882;
    typeConv.DWordTo4Bytes(a);
    int b3 = typeConv.GetByte3();
    int b2 = typeConv.GetByte2();
    int b1 = typeConv.GetByte1();
    int b0 = typeConv.GetByte0();
    Debug("DWordTo4Bytes(715827882): ", b3, b2, b1, b0);
    // The Code-JUL TypeConv.h has no GetDWord(); BytesToDWord()
    // returns the same value.
    int32_t dWd = typeConv.BytesToDWord();
    Debug("BytesToDWord(): ", dWd);

    dWd = typeConv.BytesToDWord(b3, b2, b1, b0);
    Debug("BytesToDWord(b3, b2, b1, b0): ", dWd);
}

void TypeConv_T1_WordTo2Bytes()
{
    printTitle("TypeConv T1 WordTo2Bytes");
    // Notice no parenthsis...
    TypeConv typeConv;

    Debug("INT16_MAX", INT16_MAX);
    int a = 16234;
    typeConv.WordTo2Bytes(a);
    int hi = typeConv.GetHiByte();
    int lo = typeConv.GetLoByte();
    Debug("WordTo2Bytes(16234)", hi, lo);

    // The Code-JUL TypeConv.h has no GetWord(); BytesToWord()
    // returns the same value.
    int wd = typeConv.BytesToWord();
    Debug("BytesToWord: ", wd);

    wd = typeConv.BytesToWord(hi, lo);
    Debug("BytesToWord(hi, lo): ", wd);
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // TypeConv tests, in order
    TypeConv_T1_WordTo2Bytes();
    TypeConv_T2_DWordTo4Bytes();
}

void loop()
{
}
