#include <Arduino.h>
#include "L298N.h"

using namespace csjc;

namespace
{
    Bitwise<uint8_t> flags;

    int hexValue(char digit)
    {
        if (digit >= '0' && digit <= '9')
        {
            return digit - '0';
        }
        if (digit >= 'a' && digit <= 'f')
        {
            return digit - 'a' + 10;
        }
        if (digit >= 'A' && digit <= 'F')
        {
            return digit - 'A' + 10;
        }
        return -1;
    }

    void printFlags(int value)
    {
        flags.SetBitsValue((uint8_t)value);

        Serial.print(F("bits_"));
        for (int bit = 3; bit >= 0; --bit)
        {
            Serial.print(flags.IsBitNumberSet((uint8_t)bit) ? '1' : '0');
        }

        Serial.print(F("  E/P/L/R: "));
        Serial.print(flags.IsBitNumberSet((uint8_t)3) ? '1' : '0');
        Serial.print('/');
        Serial.print(flags.IsBitNumberSet((uint8_t)2) ? '1' : '0');
        Serial.print('/');
        Serial.print(flags.IsBitNumberSet((uint8_t)1) ? '1' : '0');
        Serial.print('/');
        Serial.println(flags.IsBitNumberSet((uint8_t)0) ? '1' : '0');
    }
}

void setup()
{
    Serial.begin(9600);
    Serial.println(F("Experiment 4 draft: L298N Bits() table familiarization."));
    Serial.println(F("No L298N pins or motors are connected in this exercise."));
    Serial.println(F("Send one hexadecimal digit 0-f to decode a pattern."));
}

void loop()
{
    while (Serial.available() > 0)
    {
        const int value = hexValue((char)Serial.read());
        if (value >= 0)
        {
            printFlags(value);
        }
    }
}
