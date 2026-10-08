#include <Arduino.h>
#include "Joystick.h"
#include "LinearMap.h"
#include "L298N.h"
#include "Button.h"
#include "Timer.h"

using namespace csjc;

namespace
{
    const unsigned long CONTROL_INTERVAL_MS = 100;
    const float X_CENTER_TOLERANCE = 0.05f;
    const float Y_CENTER_TOLERANCE = 0.06f;

    L298N motors;
    Button enableButton(2, 3);
    Timer controlTimer;
    Joystick<float> joystick;
    LinearMap<float> adcToUnit(0.0f, 1023.0f, -1.0f, 1.0f);
    LinearMap<float> unitToPwm(-1.0f, 1.0f, -255.0f, 255.0f);
    uint8_t selectedBits = 0;

    float centerInput(float value, float tolerance)
    {
        return absT<float>(value) < tolerance ? 0.0f : value;
    }

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

    void printSelectedBits()
    {
        Serial.print(F("Bits "));
        if (selectedBits < 10)
        {
            Serial.print((char)('0' + selectedBits));
        }
        else
        {
            Serial.print((char)('a' + selectedBits - 10));
        }
        Serial.print(F("  E/P/L/R: "));
        Serial.print((selectedBits & 0x08) ? '1' : '0');
        Serial.print('/');
        Serial.print((selectedBits & 0x04) ? '1' : '0');
        Serial.print('/');
        Serial.print((selectedBits & 0x02) ? '1' : '0');
        Serial.print('/');
        Serial.println((selectedBits & 0x01) ? '1' : '0');
    }

    void readBitsSelection()
    {
        while (Serial.available() > 0)
        {
            const int value = hexValue((char)Serial.read());
            if (value < 0)
            {
                continue;
            }

            selectedBits = (uint8_t)value;
            motors.Bits((BitsL298N)((int)BitsL298N::bits_0000 + value));
            printSelectedBits();
        }
    }
}

void setup()
{
    Serial.begin(9600);
    enableButton.setLatching(false);
    enableButton.begin();
    motors.PinsL298N();
    motors.Bits(BitsL298N::bits_0000);
    controlTimer.resetTimer();

    Serial.println(F("Experiment 5 draft: Article 1009 L298N Setup / Code-2."));
    Serial.println(F("Hold joystick SW to enable. Send hex 0-f to select Bits()."));
    Serial.println(F("Test all 8 joystick positions; release SW to stop."));
    printSelectedBits();
}

void loop()
{
    enableButton.updateButton();
    if (!enableButton.isButtonOn())
    {
        readBitsSelection();
    }

    if (!enableButton.isButtonOn())
    {
        motors.PowerDownL298N();
        return;
    }

    if (!controlTimer.isTimer(CONTROL_INTERVAL_MS))
    {
        return;
    }

    float x = adcToUnit.Map((float)analogRead(A1));
    float y = adcToUnit.Map((float)analogRead(A0));
    x = centerInput(x, X_CENTER_TOLERANCE);
    y = centerInput(y, Y_CENTER_TOLERANCE);

    joystick.UpdateInputs(x, y);
    const int leftPwm = (int)unitToPwm.Map(joystick.Left());
    const int rightPwm = (int)unitToPwm.Map(joystick.Right());
    motors.UpdateL298N(leftPwm, rightPwm, true);

    Serial.print(F("Octant "));
    Serial.print(joystick.Octant());
    Serial.print(F("  PWM L/R "));
    Serial.print(leftPwm);
    Serial.print('/');
    Serial.println(rightPwm);
}
