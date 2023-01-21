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

// Experimantal Interrupts & Variables ////////////////
float dT;                                            //
float LeftPPS;                                       //
volatile int leftPulseCounter = 0;                   //
float RightPPS;                                      //
volatile int rightPulseCounter = 0;                  //
void LeftMotor()                                     //
{                                                    //
    // Arduino Uno Pin-2                             //
    if (digitalRead(2) == 0)                         //
    {                                                //
        if (joystick.IsLeftForward())                //
            leftPulseCounter++;                      //
        else                                         //
            leftPulseCounter--;                      //
    }                                                //
}                                                    //
void RightMotor()                                    //
{                                                    //
    // Arduino Uno Pin-3                             //
    if (digitalRead(3) == 0)                         //
    {                                                //
        if (joystick.IsRightForward())               //
            rightPulseCounter++;                     //
        else                                         //
            rightPulseCounter--;                     //
    }                                                //
}                                                    //
///////////////////////////////////////////////////////

void setup()
{
    // Debug Only
    Serial.begin(9600);
    while (!Serial) {}
    // Note: Serial Print uses a lot of memory..., use it sparingly.

    // Scope - Temporary Variables
    // Change for upcoming projects...
    // Need Arduino Uno interrupt pins 2 & 3....
    int buttonPin = 4; // WAS: PIN-2
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
    // Motors
    motors = uno::L298N(LeftMotorPWM, LeftMotorIN1, LeftMotorIN2,
        RightMotorIN1, RightMotorIN2, RightMotorPWM);
    // Setup the L298N Pins
    motors.PinsL298N();

    // ----------------------------------------------------------------- NEW PLUGIN METHOD
    // There are 8 combinations for Reverse-Inputs and Direction-Motors
        // The Boolean Order 
            // (1)         Reverse Inouts: T/F (Bit-2)
            // (2)   Direction Left Motor: T/F (Bit-1)
            // (3) Direction Right Motoer: T/F (Bit-0)
            // Check conditions:    FFF, FFT, FTF, FTT, TFF, TFT, TTF, TTT
            // Local-Bits-Value:     0    1    2    3    4    5    6    7
            // Used 3 Bit Numbers:  000  001  010  011  100  101  110  111
            // DO NOT USE the private constants belonging to MotorBits...
        // Changing the truth table is much easier than switching the actual 
        // wires around on the L298N module.... For my setup, FFF was used...
        //
    motors.Bits(uno::MotorBits::motorsFFF); // -------------------------- NEW PLUGIN METHOD

    // Joystick Algorithm
    joystick = uno::Joystick<float>();

    // Map ADC digital values to joystick inputs
    ADCtoJoystickInputs = nmr::LinearMap<float>(0, 1023, -1.0, 1.0);

    // Map joystick outputs to motor inputs
    // Remember that the L298N Class requires the negative sign
    // values but the L298N only uses values from 0 to 255...
    // See L298N Class for details...
    joystickOutputsToMotors = nmr::LinearMap<float>(-1.0, 1.0, -255, 255);

    // Utilities
    timerMotors = nmr::Timer();
    buttonMotors = uno::Button(buttonPin, ledPin);

    // Interrupts
    // Left Motor
    pinMode(2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(2), LeftMotor, CHANGE);
    // Right Motor
    pinMode(3, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(3), RightMotor, CHANGE);
}

// -------------------------------------------------  DEBUG DISABLED
// All debug statements occur here in the main.cpp file
// template<typename T>
// void Debug(T x, T y)
// {
//     Serial.print("X: ");
//     Serial.print(x);
//     Serial.print(" Y: ");
//     Serial.println(y);
// }

void updateMotors()
{
    if (buttonMotors.isButtonOn())
    {
        // Analog to Digital (10-bit) Conversion 
        // Uno's Digital Values from 0 to 1023
        // When using the default reference voltage settings, a 
        // return value of digit-0 would represent approximately 0V, 
        // and a return value of digit-1023 (the maximum) would 
        // represent approximately 5V.
        // The precision from using the default settings 
        // is more than adequate for this project...
        int xDigital = analogRead(A1);
        int yDigital = analogRead(A0);
        // Debug<int>(xDigital, yDigital); // ----------- DEBUG DISABLED

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
        bool TurnOnMotors = true;
        motors.UpdateL298N(motorLeft, motorRight, TurnOnMotors);
    }
    else
    {
        // L298N Class
        motors.PowerDownL298N();
    }
}

void DebugPrint()
{
    // Debug - Experimantal Intterrupts & Variables
    // DeltaTime
    Serial.print(" - dT: ");
    Serial.print(String(dT, 3));
    // LEFT Pulses Per Sencond (PPS)
    Serial.print(" - LEFT Pulses : ");
    Serial.print(leftPulseCounter);
    Serial.print(" - PPS : ");
    Serial.print(String(LeftPPS, 3));
    // RIGHT Pulses Per Sencond (PPS)
    Serial.print(" - RIGHT Pulses : ");
    Serial.print(rightPulseCounter);
    Serial.print(" - PPS: ");
    Serial.println(String(RightPPS, 3));
}


void loop()
{
    // Button Update
    buttonMotors.updateButton();

    // Timer is set to 250 milliseconds
    if (timerMotors.isTimer(250))
    {
        // MOTORS
        updateMotors();
        // Motor Speeds
        dT = timerMotors.DeltaTimeSeconds();
        // Left & Right Pulses Per Second (PPS)
        LeftPPS = (float)leftPulseCounter * dT;
        RightPPS = (float)rightPulseCounter * dT;
        // Debug
        DebugPrint();
        // Clear Number of Pulses
        leftPulseCounter = 0;
        rightPulseCounter = 0;
    }
}
