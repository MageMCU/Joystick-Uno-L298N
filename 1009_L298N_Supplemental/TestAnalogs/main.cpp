#include <Arduino.h>

#include "Joystick.h"
#include "LinearMap.h"
#include "Timer.h"

uno::Joystick<float> joystick;
nmr::LinearMap<float> ADCtoJoystickInputs;
nmr::Timer timerAnalogs;

void setup()
{
    Serial.begin(9600);
    while (!Serial) {}
    // Joystick Algorithm
    joystick = uno::Joystick<float>();
    // ADC digital values to joystick inputs
    ADCtoJoystickInputs = nmr::LinearMap<float>(0, 1023, -1.0, 1.0);
    // Utilities
    timerAnalogs = nmr::Timer();
}

void TestAnalogs()
{
    // Testing the correct behavior of the joystick
    // when using Analogs A0 and A1
    // (1) Move Control Stick LEFT and RIGHT 
    // Should see x-values changing only...
    int xDigital = analogRead(A1);
    // (2) Move Control Stick UP  and DOWN
    // Should see y-values changing only...
    int yDigital = analogRead(A0);
    // Need negative and positive values for testing...
    float inputX = ADCtoJoystickInputs.Map((float)xDigital);
    float inputY = ADCtoJoystickInputs.Map((float)yDigital);
    // Monitor
    Serial.print("x:");
    Serial.print(inputX);
    Serial.print(" y: ");
    Serial.println(inputY);
    // (3) If the values are opposite than expected,
    // switch A0 and A1 around in the analogRead()
    // functions... Then repeat steps 1, 2 and 3...
}

void loop()
{
    if (timerAnalogs.isTimer(1000))
    {
        TestAnalogs();
    }
}
