//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: Experiments/Experiment-4/Code/src/1_Bitwise
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
// Experiment-4, Lab 1: Bitwise.h, bits and masks.
// Uno and USB cable only.
//
// Bitwise<uint8_t> holds one 8 bit unsigned integer. Each call below is
// followed by the binary pattern and the decimal value. Write the
// prediction for every line before the program is run.

#include <Arduino.h>
#include "Bitwise.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

Bitwise<uint8_t> bits;

void show(const char *call)
{
    Serial.print(call);
    Serial.print("  ");
    Serial.print(bits.PrintBinaryBits());
    Serial.print("  value: ");
    Serial.println(bits.GetBitsValue());
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");

    bits.SetBitNumber(0);
    show("SetBitNumber(0)");
    bits.SetBitNumber(2);
    show("SetBitNumber(2)");
    Serial.print("GetBitNumber() = ");
    Serial.println(bits.GetBitNumber());
    bits.ClearBitNumber(0);
    show("ClearBitNumber(0)");
    Serial.print("GetBitNumber() = ");
    Serial.println(bits.GetBitNumber());
    // Bit 8 does not exist in an 8 bit integer (bits 0 to 7)
    bits.SetBitNumber(8);
    show("SetBitNumber(8)");

    // The same operations with the C operators, as used on the port
    // registers of Article 1002, for example PORTB |= (1 << PB5)
    uint8_t value = 0;
    value |= (1 << 0);
    value |= (1 << 2);
    Serial.print("value |= (1 << 0); value |= (1 << 2);  value: ");
    Serial.println(value);
    value &= ~(1 << 0);
    Serial.print("value &= ~(1 << 0);  value: ");
    Serial.println(value);
}

void loop()
{
}
