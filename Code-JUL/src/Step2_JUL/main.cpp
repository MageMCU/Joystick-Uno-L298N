//
// Carpenter Software
// Folder: src/Step2_JUL: File: Class main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL
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
#include "Common.h"
#include "Joystick.h"
#include "Headers.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

L298N motors;
Joystick<float> joystick;
LinearMap<float> mapInputFromDigital;
LinearMap<float> mapOutFromJoystick;
Timer timerDebug;
Button buttonDebug;

void setup()
{
#ifdef DEBUG_SERIAL_ON
    Serial.begin(9600);
    while (!Serial) {}
#endif

    // Button & Button-LED
    int buttonPin = 2; // UNO D2 (CHIP-PD2)
    int ledPin = 3;    // UNO D3 (CHIP-PD3)
    // Circuit-1 of Article 1009 wires the indicator LED to D12:
    // int ledPin = 12; // UNO D12 (CHIP-PB4)
    buttonDebug = Button(buttonPin, ledPin);

    // Joystick Algorithm
    joystick = Joystick<float>();

    // Constructor setup the x-range and the y-range
    mapInputFromDigital = LinearMap<float>(0, 1023, -1.0, 1.0);
    mapOutFromJoystick = LinearMap<float>(-1.0, 1.0, -255, 255);

    // L298N Setup: Uno pins D5 to D10 in the class default order
    int8_t ENA = 5;
    int8_t IN1 = 6;
    int8_t IN2 = 7;
    int8_t IN3 = 8;
    int8_t IN4 = 9;
    int8_t ENB = 10;
    // Constructor names, not the L298N silkscreen labels (1009, Table-2)
    int8_t LeftEN = ENA;
    int8_t LeftA = IN1;
    int8_t LeftB = IN2;
    int8_t RightA = IN3;
    int8_t RightB = IN4;
    int8_t RightEN = ENB;

    // L298N Constructor
    motors = L298N(LeftEN, LeftA, LeftB,
                   RightA, RightB, RightEN);
    // Initiate L298N Pins
    motors.PinsL298N();

    // Bits() selects one of 16 patterns, written bit 3, 2, 1, 0
    // (Article 1009, Table-3). Value 1 and value 0 of each bit:
    // Bit 3, EN:      1 = _EN_A with the left IN pair, _EN_B with
    //                     the right; 0 = enable pins crossed
    // Bit 2, PWM:     1 = left IN pair follows the left command;
    //                 0 = left and right commands swapped
    // Bit 1, LeftIN:  1 = positive command sets IN_A LOW, IN_B HIGH;
    //                 0 = positive command sets IN_A HIGH, IN_B LOW
    // Bit 0, RightIN: same as bit 1, for the right IN pair
    // -----------------------------------------------------------
    // Enable pins crossed (bit 3 = 0):
    //   bits_0000 to bits_0111, values 0 to 7
    // Enable pins straight (bit 3 = 1):
    //   bits_1000 to bits_1111, values 8 to 15
    // -----------------------------------------------------------
    // Change this value, not the wires (Article 1009, L298N Setup,
    // Motor Movement Checklist). The author's bench uses bits_1010.
    motors.Bits(BitsL298N::bits_1010);
}

void updateJoystick()
{
    if (buttonDebug.isButtonOn())
    {
#ifdef DEBUG_JOYSTICK
        Debug("Button ON");
#endif

        int xDigital = analogRead(A1);
        int yDigital = analogRead(A0);

#ifdef DEBUG_JOYSTICK
        Debug<int>("Analogs", xDigital, yDigital);
#endif

        // MAP
        float inputX = mapInputFromDigital.Map((float)xDigital);
        float inputY = mapInputFromDigital.Map((float)yDigital);

#ifdef DEBUG_JOYSTICK
        Debug<float>("Joystick Map Out: ", inputX, inputY);
#endif

        // Center Joystick to Zero
        float X_OFFSET = 0.05; // (0 < OFFSET < 1)
        float Y_OFFSET = 0.06; // (0 < OFFSET < 1)
        if (absT<float>(inputX) < X_OFFSET)
            inputX = 0;
        if (absT<float>(inputY) < Y_OFFSET)
            inputY = 0;

#ifdef DEBUG_JOYSTICK
        Debug<float>("Joystick Input with OFFSET: ", inputX, inputY);
#endif

        // Process Joystick Inputs
        joystick.UpdateInputs(inputX, inputY);
        // Process Joystick Outputs
        float outputLeft = joystick.Left();
        float outputRight = joystick.Right();

#ifdef DEBUG_JOYSTICK
        Debug<float>("Joystick Process Out: ", outputLeft, outputRight);
#endif

        // MAP
        int outMapLeft = (int)mapOutFromJoystick.Map(outputLeft);
        int outMapRight = (int)mapOutFromJoystick.Map(outputRight);

#ifdef DEBUG_L298N
        Debug<int>("L298N Input: ", outMapLeft, outMapRight);
#endif

        // The third argument of UpdateL298N() is the safety flag.
        // It defaults to false, which keeps the enable pins LOW;
        // true lets the motors run. Here the push button state
        // (ON) decides whether this line is reached at all.
        // SAFETY COMES FIRST (WATCH YOUR FINGERS)
        motors.UpdateL298N(outMapLeft, outMapRight, true);
    }
    else
    {
#ifdef DEBUG_JOYSTICK
        Debug("Button OFF");
#endif
        // SAFETY COMES FIRST (WATCH YOUR FINGERS)
        motors.PowerDownL298N();
    }
}

void loop()
{
    // Button Class
    buttonDebug.updateButton();
    // Timer Class
    // BUTTON_TIMER_mS (Common.h) is 100 ms; while any debug flag is
    // defined it is 3000 ms, so the serial output can be read.
    if (timerDebug.isTimer(BUTTON_TIMER_mS))
    {
        // Local Function
        updateJoystick();
    }
}
