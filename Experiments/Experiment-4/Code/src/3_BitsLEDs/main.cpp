//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: Experiments/Experiment-4/Code/src/3_BitsLEDs
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
// Experiment-4, Lab 3: L298N.h, reading the flags on the pins.
//
// Wiring: six LEDs, each through 220 Ohm to GND, on D5 to D10. The
// L298N logic header is disconnected and the bench supply is unplugged.
//
// Type one hexadecimal digit, 0 to f, in the serial monitor. The digit
// selects the Bits() value bits_0000 to bits_1111. The program then
// applies a fixed test command, left +255 and right -64, so that one
// enable LED is bright (255) and the other dim (64), and the four
// direction LEDs show which input of each pair is HIGH.

#include <Arduino.h>
#include "L298N.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

L298N motors;

const int TEST_LEFT = 255;
const int TEST_RIGHT = -64;

// The duty cycle on an enable pin, read from the timer registers of the
// ATmega328P (Article 1002). analogWrite(pin, 255) and analogWrite(pin, 0)
// write the pin HIGH or LOW without PWM, so the port bit is read instead.
int dutyD5()
{
    if (TCCR0A & _BV(COM0B1))
        return OCR0B;
    return (PORTD & _BV(PD5)) ? 255 : 0;
}

int dutyD10()
{
    if (TCCR1A & _BV(COM1B1))
        return OCR1B;
    return (PORTB & _BV(PB2)) ? 255 : 0;
}

int level(volatile uint8_t &port, uint8_t bit)
{
    return (port & _BV(bit)) ? 1 : 0;
}

int hexDigit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println("Serial 9600 baudrate");

    motors = L298N(5, 6, 7, 8, 9, 10);
    motors.PinsL298N();
    Serial.println("Send one hexadecimal digit, 0 to f");
}

void loop()
{
    if (Serial.available() > 0)
    {
        int value = hexDigit(Serial.read());
        if (value < 0)
            return;

        motors.Bits((BitsL298N)((int)BitsL298N::bits_0000 + value));
        motors.UpdateL298N(TEST_LEFT, TEST_RIGHT, true);

        Serial.print("Bits value ");
        Serial.print(value);
        Serial.print(" (");
        for (int b = 3; b >= 0; b--)
            Serial.print((value >> b) & 1);
        Serial.print(")  D5: ");
        Serial.print(dutyD5());
        Serial.print("  D6: ");
        Serial.print(level(PORTD, PD6));
        Serial.print("  D7: ");
        Serial.print(level(PORTD, PD7));
        Serial.print("  D8: ");
        Serial.print(level(PORTB, PB0));
        Serial.print("  D9: ");
        Serial.print(level(PORTB, PB1));
        Serial.print("  D10: ");
        Serial.println(dutyD10());
    }
}
