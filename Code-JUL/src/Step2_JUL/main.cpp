//
// Carpenter Software
// Folder: src/Step2_JUL: File: Class main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL
//
// By Jesse Carpenter (carpentersoftware.com)
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//
// RELEASE
//   2026-10-28  v6.8.0
//   Step2_JUL/main.cpp last changed: 2026-10-27  v6.6.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//
// Layout (v6.6.0): every line fits the code listings of Article 1009
// (cutoff 80 characters), and each comment is written on its own line
// above the statement it explains.
//

// DEBUG SWITCHES (see Common.h): shipped on. While either is defined, the
// motors respond once every 3000 ms, so the output can be read. Comment out
// both to drive at 100 ms.
// The joystick signal chain
#define DEBUG_STEP2_JOYSTICK
// The L298N inputs and pin states
#define DEBUG_STEP2_L298N

#include <Arduino.h>
#include "Common.h"
#include "Joystick.h"
#include "Headers.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

L298N motors;
Joystick<float> joystick;
LinearMap<float> mapInputFromDigital;
LinearMap<float> mapOutFromJoystick;
Timer timerDebug;
Button buttonDebug;

void setup()
{
#ifdef DEBUG_SERIAL_ON
    Serial.begin(9600);
    while (!Serial) { }
    // Program title (v6.4.1). Each backslash joins the next line to this
    // statement. Each string starts with \n and is closed before its
    // backslash, so the indentation is not printed.
    Serial.println(F(                                         \
        "\n................................................"  \
        "\nStep2_JUL: the diagnostic program (L298N Setup)"   \
        "\nSelected in platformio.ini: +<Step2_JUL/>"));
#endif
    // Push button and indicator LED
    // UNO D2 (CHIP-PD2)
    int buttonPin = 2;
    // Advanced wiring: UNO D3 (CHIP-PD3)
    // int ledPin = 3;
    // Circuit-1 of Article 1009: UNO D12 (CHIP-PB4)
    int ledPin = 12;
    buttonDebug = Button(buttonPin, ledPin);
    // Latching mode (the Button.h default): press once for ON, the motors
    // may run; press again for OFF. The thumb that steers the grip need not
    // hold the button down. Step1_Joystick uses the momentary mode.
    buttonDebug.setLatching(true);
    // D2 as INPUT_PULLUP, the LED pin as OUTPUT
    buttonDebug.begin();
    // Internal pull up off (THE PUSH BUTTON, end of file)
    pinMode(buttonPin, INPUT);
    joystick = Joystick<float>();

    // Joystick reading (0 to 1023) to joystick input (-1 to 1)
    mapInputFromDigital = LinearMap<float>(0, 1023, -1.0, 1.0);
    // Joystick output (-1 to 1) to PWM command (-255 to 255)
    mapOutFromJoystick = LinearMap<float>(-1.0, 1.0, -255, 255);

    // Uno pins, named after the L298N input each is wired to in Circuit-1
    // of Article 1009
    int8_t ENB = 5;
    int8_t IN4 = 6;
    int8_t IN3 = 7;
    int8_t IN2 = 8;
    int8_t IN1 = 9;
    int8_t ENA = 10;
    // L298N PINS
    int8_t LeftEN = ENB;
    int8_t LeftA = IN4;
    int8_t LeftB = IN3;
    int8_t RightA = IN2;
    int8_t RightB = IN1;
    int8_t RightEN = ENA;

    // L298N Constructor
    motors = L298N(LeftEN, LeftA, LeftB,
                   RightA, RightB, RightEN);
    // Initiate L298N Pins: outputs, LOW
    motors.PinsL298N();

    // There are 16 combinations for EN, PWM, LeftIN, RightIN
    // USE: analogWrite(EN, PWM) & digitalWrite(LeftIN1, LOW)
    // The Boolean Order (3, 2, 1, 0)
    // (3) EN (AB):         (Bit-3)
    // (2) PWM Inputs (AB): (Bit-2)
    // (1) LeftIN (1 & 2):  (Bit-1)
    // (0) RightIN (3 & 4): (Bit-0)
    // EN B & A ---------------------------------------------
    // Bits-Value:  0    1    2    3    4    5    6    7
    // Bits:      0000 0001 0010 0011 0100 0101 0110 0111
    // EN A & B ---------------------------------------------
    // Bits-Value:  8    9   10   11   12   13   14   15
    // Bits:      1000 1001 1010 1011 1100 1101 1110 1111
    // ------------------------------------------------------
    // NOTICE: Whatever the joystick orientation and the L298N connections
    // (rules at the end of this file), one four digit value corrects a
    // working bench. Start at bits_0000. This is the Bits() line.
    motors.Bits(BitsL298N::bits_0000);
}

void updateJoystick()
{
    if (buttonDebug.isButtonOn())
    {
#ifdef DEBUG_JOYSTICK
        Debug("Button ON");
#endif

        // The two analogRead() lines: leave them as written
        // (Step3_Generator uses A0 and A1). The Bits() value corrects any
        // joystick orientation.
        int xDigital = analogRead(A0);
        int yDigital = analogRead(A1);

#ifdef DEBUG_JOYSTICK
        Debug<int>("Analogs", xDigital, yDigital);
#endif

        // MAP
        float inputX = mapInputFromDigital.Map((float)xDigital);
        float inputY = mapInputFromDigital.Map((float)yDigital);

#ifdef DEBUG_JOYSTICK
        Debug<float>("Joystick Map Out: ", inputX, inputY);
#endif

        // Center Joystick to Zero: the dead zone (0 < OFFSET < 1)
        float X_OFFSET = 0.05;
        float Y_OFFSET = 0.06;
        if (absT<float>(inputX) < X_OFFSET)
            inputX = 0;
        if (absT<float>(inputY) < Y_OFFSET)
            inputY = 0;

#ifdef DEBUG_JOYSTICK
        Debug<float>("Joystick Input with OFFSET: ", inputX, inputY);
#endif

        // Process Joystick Inputs
        joystick.UpdateInputs(inputX, inputY);
        // Process Joystick Outputs
        float outputLeft = joystick.Left();
        float outputRight = joystick.Right();

#ifdef DEBUG_JOYSTICK
        Debug<float>("Joystick Process Out: ", outputLeft, outputRight);
#endif

        // MAP
        int outMapLeft = (int)mapOutFromJoystick.Map(outputLeft);
        int outMapRight = (int)mapOutFromJoystick.Map(outputRight);

#ifdef DEBUG_L298N
        Debug<int>("L298N Input: ", outMapLeft, outMapRight);
#endif

        // The third argument of UpdateL298N() is the safety flag. It
        // defaults to false, which keeps the enable pins LOW; true lets the
        // motors run. Here the push button state (ON) decides whether this
        // line is reached at all.
        // SAFETY COMES FIRST (WATCH YOUR FINGERS)
        motors.UpdateL298N(outMapLeft, outMapRight, true);
    }
    else
    {
#ifdef DEBUG_JOYSTICK
        Debug("Button OFF");
#endif
        // SAFETY COMES FIRST (WATCH YOUR FINGERS)
        motors.PowerDownL298N();
    }
}

void loop()
{
    // Button Class
    buttonDebug.updateButton();
    // OFF stops the motors at once, not at the next control tick, which is
    // 3000 ms while a debug switch is defined
    if (!buttonDebug.isButtonOn())
        motors.PowerDownL298N();
    // Timer Class
    // BUTTON_TIMER_mS (Common.h) is 100 ms; while a debug switch is defined
    // (top of this file) it is 3000 ms.
    if (timerDebug.isTimer(BUTTON_TIMER_mS))
    {
#ifdef DEBUG_SERIAL_ON
        // A blank line and a dotted line start each new output (v6.1.0)
        Serial.println();
        Serial.println(F(                                     \
            "................................................"));
#endif
        // Local Function
        updateJoystick();
    }
}

// -------------------------------------------------------------------------
// CONNECTIONS THAT ONE Bits() VALUE CORRECTS
// Find the value with the Motor Movement Checklist (Article 1009, L298N
// Setup) and place it in the Bits() line. The value corrects every bench
// that keeps these rules; checked in simulation for all 720 ways of
// connecting D5 to D10 to the six L298N inputs
// (Motor-Movement-Checklist/BitsProof.py).
//   1. D5 and D10, the two PWM pins, go to ENA and ENB, either way.
//   2. D6 and D7 go together to one IN pair, IN1 and IN2 or IN3 and IN4, in
//      either order; D8 and D9 go to the other IN pair, in either order. A
//      pair split between the two channels cannot be corrected: of the 720
//      ways, only these 16 can.
//   3. The two leads of each motor go to one output pair, OUT1 and OUT2 or
//      OUT3 and OUT4. Either motor may use either output, with either
//      polarity.
//   4. The ENA and ENB jumpers are removed. Power, the 5 V logic supply,
//      and the common ground are wired as in Circuit-1; no Bits() value
//      corrects a power or ground fault.
//   5. The joystick: VRx and VRy on A0 and A1, either way; SW on D2. The
//      two analogRead() lines stay as written, x on A0 and y on A1.
// Other Uno pins for the L298N: change the six pin lines in setup(), not
// the wires, and the same six pins in Step3_Generator. The enable pins must
// be PWM pins (D3, D5, D6, D9, D10, D11); keep clear of D0 and D1 (serial),
// D2 (button), and the LED pin. Then rules 1 to 5 apply.
// -------------------------------------------------------------------------
// THE PUSH BUTTON (revised 20261022 for v6.0.0)
// The push button is the joystick switch, SW, on D2; pressed, it connects
// SW to GND. D2 needs a pull up resistor (Article 1009, The Thumb
// Joystick, The Push Button):
//   * External 10 kOhm pull up from D2 to the 5V pin of the Uno
//     (Circuit-1a): keep the line pinMode(buttonPin, INPUT) as written.
//     begin() sets D2 to INPUT_PULLUP, and that line sets it to INPUT,
//     which turns the internal pull up off. Step4_Generated reads the
//     button this way only.
//   * Internal pull up: place comment marks on the line
//     pinMode(buttonPin, INPUT).
// Use the same choice as in Step1_Joystick. Step1_Joystick checks the push
// button before this program is used (Article 1009, Step1). A floating D2
// can turn the motors on.
// -------------------------------------------------------------------------
