
#include <Arduino.h>
#include "Timer.h"
#include "Button.h"

#define LED_PIN 13

// Carpenter Software Jesse Carpenter
using namespace csjc;

// Object
Timer timer;
Button button;

// Global Variables
unsigned long lastCount = 0;
unsigned long currentCount = 0;
unsigned long counter = 0;
unsigned long timerMS = 1000;

// Assumes LOW to start counter...
bool toggle = true;
bool once = true;

// the setup function runs once when you press reset or power the board
void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");

    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_PIN, OUTPUT);

    // Temporary (local) variables
    int buttonPin = 2;
    int buttonLED = 3;

    // Instantiate Button Object
    // FIXED 20261008: external pull-down resistor, so the button reads
    // HIGH when pressed: activeLow = false. Button.h configures the pin
    // (INPUT) the first time updateButton() runs. With the default
    // activeLow = true, that first call would select INPUT_PULLUP and
    // replace a pinMode(buttonPin, INPUT) written here.
    button = Button(buttonPin, buttonLED, false);

    // 
    timer.resetTimer();
}

// The loop function runs over and over again forever.
// updateButton() samples the pin on every pass; called only once per
// timer interval, it would miss a short press. buttonON is the latched
// state, and tickON is true on the pass where the timer fires. The
// outer if takes the ON branch when the button is latched ON or when a
// blink is in its second half (!toggle), so a blink started while ON
// always finishes LOW and the LED never stays HIGH. The else branch
// runs while the button is OFF and no half cycle is pending: on one
// timer tick it forces the LED LOW, prints Button OFF once, and clears
// once. In the drive program this branch is where the motors stop.
void loop()
{
    counter++;
    // Essential Button Call
    button.updateButton();
    // Methods called once to reduce processing time
    bool buttonON = button.isButtonOn();
    bool tickON = timer.isTimer(timerMS);

    // Complete the cycle with LOW
    // by using (OR !toggle) 
    if (buttonON || !toggle)
    {
        if (tickON)
        {
            if (toggle)
            {
                Serial.println("Button ON...");

                currentCount = counter - lastCount;
                Serial.print("Number of Loops/2000mS: ");
                Serial.println(currentCount);

                digitalWrite(LED_PIN, HIGH);
                Serial.println("LED HIGH");

                toggle = false;

                //
            }
            else
            {
                digitalWrite(LED_PIN, LOW);
                Serial.println("LED LOW");

                toggle = true;
                once = true;

                lastCount = counter;
                Serial.println("-----------");
            }
        }
    } 
    else // Button OFF (Should always 
    // come first upon start-up)
    if (once && tickON)
    {
        // Simulate Motor Shutdown
        // Safety Comes First
        digitalWrite(LED_PIN, LOW);

        Serial.println("Button OFF...");
        Serial.println("-----------");
        once = false;
    }
}
