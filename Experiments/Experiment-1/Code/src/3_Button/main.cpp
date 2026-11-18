//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: Experiments/Experiment-1/Code/src/3_Button
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
// RELEASE
//   Last reviewed: 2026-11-18  v7.5.1
//   3_Button/main.cpp last changed: 2026-11-13  v7.4.1
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//
// Experiment-1, Lab 3: The Button Class with the Timer Class.
// Wiring: Circuit-1: push button from D2 to 5 V, 10 kOhm pull down
// resistor from D2 to GND (active high). Circuit-1b: 10 kOhm pull up
// resistor from D2 to 5 V, push button from D2 to GND (active low);
// use the pull up form of the Button line in setup() (Article 1004,
// The Signal of the Push Button). Both circuits take 5 V from the 5V
// pin of the Uno, powered by its USB cable.
// Header added 20261028 (v6.8.0). Revised 20261113 (v7.4.1): the pull
// up form added in comments; the shipped program is unchanged.
//

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

    // PULL UP FORM (Circuit-1b, v7.4.1): place comment marks on the
    // Button line above and remove them from the three lines below.
    // The pressed level is LOW, so activeLow keeps its default, true.
    // button = Button(buttonPin, buttonLED);
    // begin() configures the pins at once (INPUT_PULLUP for D2).
    // button.begin();
    // Turn the internal pull up off: only the 10 kOhm resistor of
    // Circuit-1b sets the level, as in the drive programs.
    // pinMode(buttonPin, INPUT);

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
// Number of Loops counts the passes made during the LOW half before
// it, 1000 ms; the first count after a press includes the OFF time.
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
                Serial.print("Number of Loops/1000mS: ");
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
    // Button OFF (Should always
    else
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
