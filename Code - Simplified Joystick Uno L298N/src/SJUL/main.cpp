//
// Carpenter Software
// File: Class main.cpp
// Folder: Simplified-Joystick-Uno-L298N (SJUL)
//
// Purpose: Github Depository (MageMCU)
//
// Algebra OOP Library
// The math is underneath the namespace
// nmr for Numerics as in numeric computation.
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
// Using Adruino Uno

#include "L298N.h"
#include "Joystick.h"
#include "LinearMap.h"
#include "Timer.h"
#include "Button.h"

// Declaration of GLOBAL VARIABLES
uno::L298N motors;
uno::Joystick<float> joystick;
nmr::LinearMap<float> ADCtoJoystickInputs;
nmr::LinearMap<float> joystickOutputsToMotors;
nmr::Timer timerMotors;
uno::Button buttonMotors;

void setup()
{
    // Debug Only ------------------------------------- DEBUG DISABLED
    Serial.begin(9600);
    while (!Serial) {}
    // Note: Serial Print uses a lot of memory..., use it sparingly.

    // Scope - Temporary Variables
    // New Change for upcoming projects...
    // Need Arduino Uno interrupt pins 2 & 3....
    int buttonPin = 4; // buttonPin was Arduino pin 2. 
    int ledPin = 12;
    int8_t ENA = 10;
    int8_t IN1 = 9;
    int8_t IN2 = 8;
    int8_t IN3 = 7;
    int8_t IN4 = 6;
    int8_t ENB = 5;
    int8_t LeftMotorPWM = ENB;
    int8_t LeftMotorIN1 = IN4;
    int8_t LeftMotorIN2 = IN3;
    int8_t RightMotorIN1 = IN1;
    int8_t RightMotorIN2 = IN2;
    int8_t RightMotorPWM = ENA;

    // Instantiation of Global Variables and Setup
    motors = uno::L298N(LeftMotorPWM, LeftMotorIN1, LeftMotorIN2,
        RightMotorIN1, RightMotorIN2, RightMotorPWM);
    // Required
    motors.PinsL298N();
    // ---------------------------------------------------- NEW METHOD
    // There are 8 combinations for Reverse-Inputs and Direction-Motors
    // The Boolean Order 
        // (1)         Reverse Inputs: T/F
        // (2)   Direction Left Motor: T/F
        // (3) Direction Right Motoer: T/F
        // Check conditions:    FFF, FFT, FTF, FTT, TFF, TFT, TTF, TTT
        // Bits Value:           0    1    2    3    4    5    6    7
        // Used 3 Bit Numbers:  000  001  010  011  100  101  110  111
        // DO NOT USE the private constants belonging to MotorBits...
    // Changing the truth table is much easier than switching the actual 
    // wires around.... For my setup, FFF was used...
    motors.Bits(uno::MotorBits::motorsFFF);

    // Joystick Algorithm
    joystick = uno::Joystick<float>();

    // ADC digital values to joystick inputs
    ADCtoJoystickInputs = nmr::LinearMap<float>(0, 1023, -1.0, 1.0);

    // joystick outputs to motor inputs
    // Remember that the L298N Class requires the negative sign
    // values but the L298N only uses values from 0 to 255...
    // See L298N Class for details...
    joystickOutputsToMotors = nmr::LinearMap<float>(-1.0, 1.0, -255, 255);

    // Utilities
    timerMotors = nmr::Timer();
    buttonMotors = uno::Button(buttonPin, ledPin);
}

// -------------------------------------------------  DEBUG DISABLED
// All debug statements occur here in the main.cpp file
template<typename T>
void Debug(T x, T y)
{
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.println(y);
}

void updateMotors()
{
    if (buttonMotors.isButtonOn())
    {
        // Analog to Digital (10-bit) Conversion 
        // Digital Values from 0 to 1023
        int xDigital = analogRead(A1);
        int yDigital = analogRead(A0);
        // In order for the Joystick Algorithm to
        // work properly, the following INPUT has to occur:
        //                 (y-axis)
        //         FORWARD  | 1023
        //                  |
        //                  |
        //                  |
        //  0               | (511, 511)    1023
        //  ------------------------------------ (x-axis)
        //  LEFT TURN       |         RIGHT TURN         
        //                  |
        //                  |
        //                  |
        //         BACKWARD | 0
        //                 
        // If the input(s) are reversed, for example,
        // use the following: xDigital = 1023 - analogRead(A1);
        Debug<int>(xDigital, yDigital); // ----------- DEBUG DISABLED

        // Map Analogs to Joystick Inputs
        // Values from -1 to 1
        float inputX = ADCtoJoystickInputs.Map((float)xDigital);
        float inputY = ADCtoJoystickInputs.Map((float)yDigital);
        // Debug<float>(inputX, inputY); // ----------- DEBUG DISABLED

        // Assume Joystick Potentiometers are not electrically centered to
        // exactly 2.5 volts... What this means the motors might move
        // while the joystick handle is in its neutral position.
        // Use the OFFSET by increasing its value starting from zero (0) 
        // and slowly increase its value towards one (1) until both motors stop...
        float OFFSET = 0.15; // (0 <= OFFSET <= 1)
        // Joystick X-Input
        if (abs(inputX) < OFFSET)
            inputX = 0;
        // Joystick Y-Input
        if (abs(inputY) < OFFSET)
            inputY = 0;
        // Debug<float>(inputX, inputY); // ----------- DEBUG DISABLED

        // Process Joystick Inputs
        joystick.UpdateInputs(inputX, inputY);

        // Joystick Outputs
        float outputX = joystick.OutLeft();
        float outputY = joystick.OutRight();
        // Debug<float>(outputX, outputY); // ----------- DEBUG DISABLED

        // Map Joystick Outputs to Motor Inputs
        int motorLeft = (int)joystickOutputsToMotors.Map(outputX);
        int motorRight = (int)joystickOutputsToMotors.Map(outputY);
        // Debug<int>(motorLeft, motorRifgt); // ----------- DEBUG DISABLED

        // ------------------------------------------ FLAG_WATCH
        // For safety reasons, the UpdateL298N() method has a 
        // Power Motors Flag set to false which deavtivates
        // the motors...
        motors.UpdateL298N(motorLeft, motorRight, true);
    }
    else
    {
        // L298N Class
        motors.PowerDownL298N();
    }
}

void loop()
{
    // Button Class
    buttonMotors.updateButton();
    // Timer Class
    // (4 ticks per second) update Motors (250ms)
    // While Debugging increase time to 1000ms...
    if (timerMotors.isTimer(250))
    {
        // Local Function
        updateMotors();
    }
}
