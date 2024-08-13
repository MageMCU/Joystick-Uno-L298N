//
// Carpenter Software
// Folder: src/Step4_JUL: File: Class main.cpp
// Github: MageMCU
// Repository: Joystick-UNO-L298N
// Folder: Code
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
#ifdef DEBUG_MAIN
    Serial.begin(9600);
    while (!Serial)
    {
    }
#endif

    // Button & Button-LED
    int buttonPin = 2; // UNO D2 (CHIP-PD2)
    int ledPin = 3;    // UNO D3 (CHIP-PD3)
    buttonDebug = Button(buttonPin, ledPin);

    // Joystick Algorithm
    joystick = Joystick<float>();

    // Constructor setup the x-range and the y-range
    mapInputFromDigital = LinearMap<float>(0, 1023, -1.0, 1.0);
    mapOutFromJoystick = LinearMap<float>(-1.0, 1.0, -255, 255);

    // New Code ----------------------------------L298N Setup
    // Arduino PINS
    int8_t ENA = 5;
    int8_t IN1 = 6;
    int8_t IN2 = 7;
    int8_t IN3 = 8;
    int8_t IN4 = 9;
    int8_t ENB = 10;
    // L298N PINS
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

    // There are 16 combinations for EN, PWM, LeftIN & RightIN
    // USE: analogWrite(EN, PWM) & digitalWrite(LeftIN1, LOW)...
    // The Boolean Order (3, 2, 1, 0)
    // (3) EN (AB):         (Bit-3)
    // (2) PWM Inputs (AB): (Bit-2)
    // (1) LeftIN (1 & 2): ( Bit-1)
    // (0) Right N (3 & 4): (Bit-0)
    // EN A & B ---------------------------------------------
    // Bits-Value:  0     1     2     3     4     5     6     7
    // Bits:       0000  0001  0010  0011  0100  0101  0110  0111
    // EN B & A ----------------------------------------------
    // Bits-Value:  8     9     10    11    12    13    14    15
    // Bits:       1000  1001  1010  1011  1100  1101  1110  1111
    // -----------------------------------------------------------
    // NOTICE: Changing the BITS is much easier than switching
    // the actual wires around on the L298N module....
    // For my setup, bits 1010 was used...
    motors.Bits(BitsL298N::bits_1010);
}

void updateJoystick()
{
    if (buttonDebug.isButtonOn())
    {
#ifdef DEBUG_MAIN
        Debug("Button ON");
#endif

        int xDigital = analogRead(A1);
        int yDigital = analogRead(A0);

#ifdef DEBUG_MAIN
        Debug<int>("Analogs", xDigital, yDigital);
#endif

        // MAP
        float inputX = mapInputFromDigital.Map((float)xDigital);
        float inputY = mapInputFromDigital.Map((float)yDigital);

#ifdef DEBUG_MAIN
        Debug<float>("Joystick Map Out: ", inputX, inputY);
#endif

        // Center Joystick to Zero
        float X_OFFSET = 0.05; // (0 < OFFSET < 1)
        float Y_OFFSET = 0.06; // (0 < OFFSET < 1)
        if (absT<float>(inputX) < X_OFFSET)
            inputX = 0;
        if (absT<float>(inputY) < Y_OFFSET)
            inputY = 0;

#ifdef DEBUG_MAIN
        Debug<float>("Joystick Input with OFFSET: ", inputX, inputY);
#endif

        // Process Joystick Inputs
        joystick.UpdateInputs(inputX, inputY);
        // Process Joystick Outputs
        float outputLeft = joystick.OutLeft();
        float outputRight = joystick.OutRight();

#ifdef DEBUG_MAIN
        Debug<float>("Joystick Process Out: ", outputLeft, outputRight);
#endif

        // MAP
        int outMapLeft = (int)mapOutFromJoystick.Map(outputLeft);
        int outMapRight = (int)mapOutFromJoystick.Map(outputRight);

#ifdef DEBUG_MAIN
        Debug<int>("L298N Input: ", outMapLeft, outMapRight);
#endif

        // NEW CODE ------------------------------- FLAG_WATCH
        // For safety reasons, the UpdateL298N() method has a
        // Power Motors Flag set to false which de-activates
        // the motors...
        // SAFETY COMES FIRST (WATCH YOUR FINGERS)
        motors.UpdateL298N(outMapLeft, outMapRight, true);
    }
    else
    {
#ifdef DEBUG_MAIN
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
    // (4 ticks per second) update Motors (250ms)
    // While Debugging increase time to 1000ms...
    if (timerDebug.isTimer(BUTTON_TIMER_mS))
    {
        // Local Function
        updateJoystick();
    }
}
