
#include <Arduino.h>
#include "Timer.h"

#define LED_PIN 13
// Carpenter Software Jesse Carpenter
using namespace csjc;
// Object
Timer timer;
// Global Variables
unsigned long lastCount = 0;
unsigned long currentCount = 0;
unsigned long counter = 0;
// Assumes LOW to start counter...
bool toggle = false;

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
    timer.resetTimer();
}

// The loop function runs over and over again forever.
// counter counts every pass through loop(). toggle records which half
// of the blink is due next. It starts false, so the second block acts
// first: when isTimer(1000) fires, the LED goes LOW, toggle becomes
// true, and lastCount saves counter. One second later the first block
// fires: it prints counter - lastCount, the passes made during the
// interval, sets the LED HIGH, and clears toggle. Each condition tests
// toggle before isTimer(); && evaluates its right operand only when
// the left operand is true, so isTimer() is called from one block per
// pass, and the two blocks share one timer.
void loop()
{
    counter++;

    if (toggle && timer.isTimer(1000))
    {
        currentCount = counter - lastCount;
        Serial.print("Number of Loops: ");
        Serial.println(currentCount);

        digitalWrite(LED_PIN, HIGH); // turn the LED on (HIGH is the voltage level)
        Serial.println("LED HIGH");

        toggle = false;
    }

    if (!toggle && timer.isTimer(1000))
    {
        digitalWrite(LED_PIN, LOW); // turn the LED off by making the voltage LOW
        Serial.println("LED LOW");

        toggle = true;

        lastCount = counter;
        Serial.println("-----------");
    }
}
