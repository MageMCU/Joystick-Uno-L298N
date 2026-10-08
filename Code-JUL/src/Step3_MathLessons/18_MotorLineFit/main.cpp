//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: src/Step3_MathLessons/18_MotorLineFit
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
// Lesson 18: motor calibration with a least squares line fit.
// Added 20261008 for Article 1004, Experiment-7.
// CREDIT: LineFit2.h is adapted from the work of David Eberly, Geometric
// Tools Engine, GTE/Mathematics/ApprHeightLine2.h (Boost Software License
// 1.0); see the credit and adaptation notes in that file.
//
// Wiring: the complete Joystick-Uno-L298N bench of Article 1009,
// Circuit-1, with the drive raised so that both wheels turn freely.
//
// The joystick push button (latching) enables the motors. While it is
// ON, both motors turn forward at one PWM value at a time. Count the
// revolutions of one wheel in 10 s, type the count in the serial monitor
// and press Enter; the program moves to the next PWM value. After the
// last value it fits RPM = slope * PWM + intercept and prints the slope,
// the intercept, the PWM at which the fitted speed is zero (the dead
// band of the motor), and the RMS error.
//
// SAFETY COMES FIRST (WATCH YOUR FINGERS)

#include <Arduino.h>
#include "Common.h"
#include "Button.h"
#include "Timer.h"
#include "L298N.h"
#include "numerics/LineFit2.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

L298N motors;
Button button;
Timer timerUpdate;

const int points = 5;
float pwm[points] = {60, 100, 140, 180, 220};
float rpm[points];
int step = 0;
String entry = "";

void prompt()
{
    Serial.print(F("PWM "));
    Serial.print((int)pwm[step]);
    Serial.println(F(": count revolutions in 10 s, type the count, press Enter"));
}

void finish()
{
    motors.PowerDownL298N();
    LineFit2<float> fit;
    if (!fit.Fit(pwm, rpm, points))
    {
        Serial.println(F("Fit failed: the PWM values must differ"));
        return;
    }
    Serial.print(F("Slope (RPM per PWM step): "));
    Serial.println(fit.Slope(), 4);
    Serial.print(F("Intercept (RPM at PWM 0): "));
    Serial.println(fit.Intercept(), 2);
    Serial.print(F("Dead band (PWM at 0 RPM): "));
    Serial.println(fit.XIntercept(), 1);
    Serial.print(F("Predicted RPM at PWM 255: "));
    Serial.println(fit.Evaluate(255), 1);
    Serial.print(F("RMS error (RPM): "));
    Serial.println(fit.RmsError(pwm, rpm, points), 2);
}

void readEntry()
{
    while (Serial.available() > 0 && step < points)
    {
        char c = Serial.read();
        if (c == '\n' || c == '\r')
        {
            if (entry.length() == 0)
                continue;
            float revolutions = entry.toFloat();
            entry = "";
            rpm[step] = revolutions * 6.0; // revolutions in 10 s to RPM
            Serial.print(F("RPM: "));
            Serial.println(rpm[step], 1);
            step++;
            if (step < points)
                prompt();
            else
                finish();
        }
        else
        {
            entry += c;
        }
    }
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println(F("Lesson 18: motor calibration"));

    int buttonPin = 2; // UNO D2, joystick SW
    int ledPin = 12;   // UNO D12, indicator LED (3 in the advanced wiring)
    button = Button(buttonPin, ledPin);

    motors = L298N(5, 6, 7, 8, 9, 10);
    motors.PinsL298N();
    // Use the value found with the Motor Movement Checklist in
    // Article 1004, Experiment-5. The author's bench uses bits_1010.
    motors.Bits(BitsL298N::bits_1010);

    Serial.println(F("Press the joystick button to start the motors"));
    prompt();
}

void loop()
{
    button.updateButton();
    readEntry();

    if (timerUpdate.isTimer(BUTTON_TIMER_mS))
    {
        if (!button.isButtonOn() || step >= points)
        {
            // SAFETY COMES FIRST
            motors.PowerDownL298N();
            return;
        }
        int command = (int)pwm[step];
        motors.UpdateL298N(command, command, true);
    }
}
