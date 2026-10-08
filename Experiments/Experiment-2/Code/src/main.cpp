#include <Arduino.h>
#include "Button.h"
#include "Timer.h"

using namespace csjc;

namespace
{
    const unsigned long SAMPLE_MS = 500;

    Button joystickButton(2, 3);
    Timer sampleTimer;
}

void setup()
{
    Serial.begin(9600);
    joystickButton.begin();
    Serial.println(F("Experiment 2: Joystick Setup (no motor driver connected)"));
    Serial.println(F("X=A1, Y=A0. Press SW to toggle analog readings."));
}

void loop()
{
    joystickButton.updateButton();

    if (joystickButton.wasPressed())
    {
        Serial.println(joystickButton.isButtonOn()
                           ? F("Joystick button ON")
                           : F("Joystick button OFF"));
    }

    if (!joystickButton.isButtonOn() || !sampleTimer.isTimer(SAMPLE_MS))
    {
        return;
    }

    // Change only the analogRead assignments below if testing shows that the
    // module's axes are exchanged or have reversed polarity.
    const int xValue = analogRead(A1);
    const int yValue = analogRead(A0);
    // Example for reversed X polarity: 1023 - analogRead(A1)
    // Example for exchanged axes: swap the A1 and A0 assignments above.

    Serial.print(F("X(A1): "));
    Serial.print(xValue);
    Serial.print(F("  Y(A0): "));
    Serial.println(yValue);
}
