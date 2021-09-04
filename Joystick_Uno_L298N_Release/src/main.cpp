//
// Carpenter Software
// File: main.cpp (release version)
// Date: 20210830
// Folder: joystick_L298N_debug
// Purpose: Github Depository (MageMCU)
//
// Student Copy...
//
// Hardware (For further information, see Debug Version)
//
// RAM:   [          ]   3.4% (used 69 bytes from 2048 bytes)
// Flash: [==        ]  15.2% (used 4890 bytes from 32256 byt
//
// MIT LICENSE
//

#include <Arduino.h>
// Using Adruino Uno

#include "L298N.h"
#include "Joystick.h"
#include "Timer.h"
#include "Button.h"

// Declaration of GLOBAL VARIABLES
uno::L298N mtr;
uno::Joystick stk;
uno::Timer tmrMotors;
uno::Button btnMotors;

void setup()
{
    // - Scope - Temp Variables
    int buttonPin = 2;
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

    // Instantiation of Global Variables
    mtr = uno::L298N(LeftMotorPWM, LeftMotorIN1, LeftMotorIN2,
                     RightMotorIN1, RightMotorIN2, RightMotorPWM);
    mtr.SetupPinsL298N();
    stk = uno::Joystick();
    tmrMotors = uno::Timer();
    btnMotors = uno::Button(buttonPin, ledPin);
}

void updateAnalog()
{
    if (btnMotors.isButtonOn())
    {
        int xAnalog = analogRead(A1);
        int yAnalog = analogRead(A0);
        stk.UpdateInputs(xAnalog, yAnalog);

        int left = stk.GetOutputLeftInteger(255);
        int right = stk.GetOutputRightInteger(255);
        mtr.updateL298N(left, right);
    }
}

void loop()
{
    btnMotors.updateButton();
    if (tmrMotors.isTimer(50))
    {
        updateAnalog();
    }
}