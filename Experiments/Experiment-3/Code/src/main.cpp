#include <Arduino.h>
#include "L298N.h"
#include "Button.h"
#include "Timer.h"

using namespace csjc;

namespace
{
    const int MOTOR_TEST_PWM = 80;
    const unsigned long NEUTRAL_INTERVAL_MS = 300;

    L298N motors;
    Button enableButton(2, 3);
    Timer neutralTimer;
    int requestedCommand = 0;
    int motorCommand = 0;
    int lastDirection = 0;
    bool waitingAtNeutral = false;

    void readSerialCommand()
    {
        while (Serial.available() > 0)
        {
            const char command = (char)Serial.read();
            if (command == 'w' || command == 'W')
            {
                requestedCommand = MOTOR_TEST_PWM;
            }
            else if (command == 's' || command == 'S')
            {
                requestedCommand = -MOTOR_TEST_PWM;
            }
            else if (command == 'x' || command == 'X')
            {
                requestedCommand = 0;
            }
        }
    }
}

void setup()
{
    Serial.begin(9600);
    enableButton.setLatching(false);
    enableButton.begin();
    motors.PinsL298N();
    motors.Bits(BitsL298N::bits_1100);
    neutralTimer.resetTimer();

    Serial.println(F("Experiment 3 draft: one motor, low-speed familiarization."));
    Serial.println(F("Hold D2 to enable; w=forward, s=reverse, x=stop."));
    Serial.println(F("The program inserts 300 ms at zero before reversing."));
}

void loop()
{
    enableButton.updateButton();

    if (!enableButton.isButtonOn())
    {
        motors.PowerDownL298N();
        requestedCommand = 0;
        motorCommand = 0;
        lastDirection = 0;
        waitingAtNeutral = false;
        neutralTimer.resetTimer();
        return;
    }

    readSerialCommand();

    if (waitingAtNeutral)
    {
        if (requestedCommand == 0)
        {
            waitingAtNeutral = false;
            motorCommand = 0;
        }
        else if (neutralTimer.isTimer(NEUTRAL_INTERVAL_MS))
        {
            waitingAtNeutral = false;
            motorCommand = requestedCommand;
            lastDirection = requestedCommand > 0 ? 1 : -1;
        }
    }
    else if (requestedCommand == 0)
    {
        motorCommand = 0;
    }
    else if (lastDirection != 0 &&
             ((lastDirection > 0) != (requestedCommand > 0)))
    {
        motorCommand = 0;
        waitingAtNeutral = true;
        neutralTimer.resetTimer();
    }
    else
    {
        motorCommand = requestedCommand;
        lastDirection = requestedCommand > 0 ? 1 : -1;
    }

    motors.UpdateL298N(motorCommand, 0, true);
}
