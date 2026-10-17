#include <Arduino.h>

#define LED_PIN 13

// Global
int counter = 0;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");
    pinMode(LED_PIN, OUTPUT);
}

// loop() prints and then increments counter, so the first line
// reads Number of Loops: 0. delay(1000) is a blocking call: nothing
// else in the program runs for 1000 ms, so one pass takes about 2 s.
void loop()
{
    Serial.print("Number of Loops: ");
    Serial.println(counter++);

    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED HIGH");
    delay(1000);

    digitalWrite(LED_PIN, LOW); 
    Serial.println("LED LOW");
    delay(1000); 

    Serial.println("-----------");
}
