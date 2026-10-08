//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: Experiments/Experiment-4/Code/src/2_TypeConv
// Github: MageMCU
// Repository: Joystick-Uno-L298N
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//
// Experiment-4, Lab 2: TypeConv.h, bytes and words.
// Uno and USB cable only.
//
// A 10 bit ADC reading is stored in a 16 bit word. A link that carries
// one byte at a time, such as I2C, sends it as a high byte and a low
// byte, and the receiver joins them again.

#include <Arduino.h>
#include "Bitwise.h"
#include "TypeConv.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

TypeConv conv;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");

    // Split 1023 into two bytes
    conv.WordTo2Bytes(1023);
    uint8_t hi = conv.GetHiByte();
    uint8_t lo = conv.GetLoByte();
    Bitwise<uint8_t> bits;
    Serial.print("1023 high byte: 0x");
    Serial.print(hi, HEX);
    bits.SetBitsValue(hi);
    Serial.print("  ");
    Serial.println(bits.PrintBinaryBits());
    Serial.print("1023 low byte:  0x");
    Serial.print(lo, HEX);
    bits.SetBitsValue(lo);
    Serial.print("  ");
    Serial.println(bits.PrintBinaryBits());
    Serial.print("Joined: ");
    Serial.println(conv.BytesToWord());

    // Round trip of every ADC value
    int mismatches = 0;
    for (uint16_t word = 0; word <= 1023; word++)
    {
        conv.WordTo2Bytes(word);
        if (conv.BytesToWord(conv.GetHiByte(), conv.GetLoByte()) != word)
            mismatches++;
    }
    Serial.print("Round trip 0 to 1023, mismatches: ");
    Serial.println(mismatches);

    // A 32 bit value in four bytes
    uint32_t now = millis();
    conv.DWordTo4Bytes(now);
    Serial.print("millis(): ");
    Serial.print(now);
    Serial.print("  bytes: ");
    Serial.print(conv.GetByte3());
    Serial.print(' ');
    Serial.print(conv.GetByte2());
    Serial.print(' ');
    Serial.print(conv.GetByte1());
    Serial.print(' ');
    Serial.print(conv.GetByte0());
    Serial.print("  joined: ");
    Serial.println(conv.BytesToDWord());
}

void loop()
{
    // Step 2: declare a second TypeConv object here and print
    // BytesToWord() before any conversion has been made, for example:
    //   TypeConv local;
    //   Serial.println(local.BytesToWord());
    //   delay(1000);
}
