//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: Experiments/Experiment-3/Code/src/2_DutyCycle
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
// Experiment-3, Lab 2: one motor and the duty cycle.
//
// Wiring: Table-1 of Article 1004 (Article 1009, Circuit-1). One motor on
// either output of the L298N; the joystick SW on D2 with its external
// 10 kOhm resistor; the indicator LED on D12 through 220 Ohm.
//
// The joystick push button (latching) enables the output. While the
// button state is OFF, PowerDownL298N() holds both enable inputs LOW.
// While it is ON, a key typed in the serial monitor sets the command:
//   0, 1, 2, 3, 4   duty cycle of 0, 25, 50, 75, or 100 percent
//   f, r            forward or reverse
// The same command is sent to the left and the right inputs of the
// L298N class, so the one motor turns on either output for any Bits()
// value. A change of direction holds the command at zero for 300 ms
// before the new direction is applied.
//
// SAFETY COMES FIRST (WATCH YOUR FINGERS)

#include <Arduino.h>
#include "Common.h"
#include "Button.h"
#include "Timer.h"
#include "L298N.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

L298N motors;
Button button;
Timer timerUpdate;

// analogWrite() values for 0, 25, 50, 75, and 100 percent duty cycle
const int dutyValue[] = {0, 64, 128, 191, 255};
const int dutyPercent[] = {0, 25, 50, 75, 100};

int level = 0;          // index into dutyValue[]
int direction = 1;      // 1 forward, -1 reverse
int newDirection = 1;   // requested by the f or r key
unsigned long zeroStart = 0;
bool holdingZero = false;
const unsigned long ZERO_HOLD_mS = 300;

void printCommand()
{
    Serial.print("Duty: ");
    Serial.print(dutyPercent[level]);
    Serial.print(" %  analogWrite: ");
    Serial.print(dutyValue[level]);
    Serial.println(newDirection > 0 ? "  forward" : "  reverse");
}

void readKeys()
{
    while (Serial.available() > 0)
    {
        char key = Serial.read();
        if (key >= '0' && key <= '4')
        {
            level = key - '0';
            printCommand();
        }
        else if (key == 'f' || key == 'r')
        {
            newDirection = (key == 'f') ? 1 : -1;
            printCommand();
        }
    }
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println("Serial 9600 baudrate");

    // Button & Button-LED
    int buttonPin = 2; // UNO D2 (CHIP-PD2), joystick SW
    int ledPin = 12;   // UNO D12 (CHIP-PB4), indicator LED
    button = Button(buttonPin, ledPin);

    // L298N: Uno pins D5 to D10 in the order of the class defaults
    motors = L298N(5, 6, 7, 8, 9, 10);
    motors.PinsL298N();
    // Any value works here, because left and right receive the same
    // command; bits_1111 keeps every flag at its straight setting.
    motors.Bits(BitsL298N::bits_1111);

    Serial.println("Press the joystick button, then send 0-4, f, r");
}

void loop()
{
    // Sample the button on every pass
    button.updateButton();
    readKeys();

    if (timerUpdate.isTimer(BUTTON_TIMER_mS))
    {
        if (!button.isButtonOn())
        {
            // SAFETY COMES FIRST
            motors.PowerDownL298N();
            return;
        }

        // A change of direction passes through zero first
        if (newDirection != direction && !holdingZero)
        {
            holdingZero = true;
            zeroStart = millis();
        }
        if (holdingZero && (millis() - zeroStart) >= ZERO_HOLD_mS)
        {
            holdingZero = false;
            direction = newDirection;
        }

        int command = holdingZero ? 0 : direction * dutyValue[level];
        motors.UpdateL298N(command, command, true);
    }
}
