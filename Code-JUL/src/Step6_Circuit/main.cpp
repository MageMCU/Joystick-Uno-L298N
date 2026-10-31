//
// Carpenter Software
// Folder: src/Step6_Circuit: File: main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL
//
// By Jesse Carpenter (carpentersoftware.com)
// Designed: Jesse Carpenter and Claude (Anthropic)
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//
// RELEASE
//   2026-10-30  v7.3.0
//   Step6_Circuit/main.cpp last changed: 2026-10-30  v7.3.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//
// Layout: every line fits the cutoff of 80 characters, and each comment
// is written on its own line above the statement it explains.
//
// -------------------------------------------------------------------------
// CIRCUIT-4 AND THIS PROGRAM GO TOGETHER: USE THEM WITH EACH OTHER ONLY
//   * Circuit-4, the Complete Wiring (Article 1009, Appendix C), is used
//     with this program ONLY. The other programs of Code-JUL do not set
//     D4, so on Circuit-4 they leave the motor supply off; they are used
//     with Circuit-1, the basic wiring.
//   * This program is used with Circuit-4 ONLY. On Circuit-1 it has no
//     motor power switch to control, and D4 drives nothing.
// The program is listed in the repository only. Article 1009 describes
// the tests and refers to this file; the comments below explain each
// part of the program.
// -------------------------------------------------------------------------
// WHAT THIS PROGRAM IS
// Step6_Circuit tests Circuit-4. Circuit-4 replaces the Uno with its
// microcontroller, the ATmega328P (U3), and adds the motor power switch of
// Circuit-3: Q1, a P channel MOSFET, connects the motor bus to VS, the
// motor supply terminal of the L298N (U2), only while D4 is HIGH.
//
// POWER: ONE SWITCH TURNS ON CIRCUIT-4
// S1, a double pole switch in the hot and the neutral conductors of the
// line cord, turns on the whole bench. The 7805 (U1) makes the 5 V bus,
// connector A, which powers U3, the joystick, and the logic of the L298N.
// U3 starts first while R4 holds Q1 off; this program then decides when
// Q1 connects the motor bus to VS. J2, the USB serial adapter, carries
// only the upload and the serial monitor; its VCC pin is not connected.
//
// TWO SWITCHES, TWO JOBS: S1 AND SW
//   S1  the power switch of the bench (hardware). ON powers U3, the
//       joystick, and the L298N logic; the motor supply, VS, stays off.
//   SW  the push button of the joystick, read by this program (D2). It
//       does two things with one state, ON or OFF:
//         ON   the button state is ON (DS3 lights) AND the motor supply
//              is ON: D4 HIGH, Q2 on, Q1 connects the motor bus to VS
//              (DS2 lights). With STEP6_MOTORS the joystick then drives
//              the motors.
//         OFF  the motors stop (ENA and ENB LOW), the motor supply is OFF
//              (D4 LOW, VS 0 V), and the button state is OFF (DS3 and
//              DS2 dark).
//   The button state and the motor supply are always ON together and OFF
//   together. In Step2_JUL the button lets the motors run while the motor
//   supply is switched by hand; on Circuit-4 the same button also switches
//   the motor supply.
//
// THE ORDER ON THE BENCH
//   1. S1 ON: U3 starts; VS stays at 0 V (DS1 on, DS2 dark).
//   2. SW pressed: the motor supply comes on, and the motors may run.
//   3. SW pressed again: the motors stop, and the motor supply goes off.
//   4. S1 OFF: everything stops.
//
// WHEN THE PROGRAM DOES NOT TURN THE MOTOR SUPPLY ON
// The motor supply comes on only when a program sets D4 HIGH. Before this
// program runs, during a reset or an upload, with another program of
// Code-JUL (they never set D4), or with the wire to R3 open, D4 is not
// HIGH: R4 holds Q2 off, R1 holds Q1 off, and VS stays at 0 V. U3, the
// joystick, and the L298N logic still run, but the motors cannot turn.
// Circuit-4 is safe by default.
//
// THE TWO TESTS (precompiler switches, below)
//   STEP6_CIRCUIT  the circuit test (shipped setting). The motors stay
//                  stopped: ENA and ENB stay LOW for the whole program.
//                  Each press of SW turns VS on or off through D4, Q2,
//                  and Q1, and the serial monitor prints the joystick.
//   STEP6_MOTORS   the motor test, run only after the circuit test
//                  passes. The joystick drives the motors through the
//                  L298N at a limited command, with the safety rules
//                  below.
// Exactly one switch is defined; with both or neither the build stops
// with an #error message.
//
// WHAT STEP6 TAKES FROM THE EARLIER STEPS
//   Step1_Joystick  the joystick measurements, include/
//                   JoystickMeasurements.h: the low end, the center, and
//                   the high end of each axis in raw ADC counts. Step6
//                   uses the same joystick, so Step1 is run first.
//   Step2_JUL       the Bits() value found with the Motor Movement
//                   Checklist (L298N Setup). Copy the value of the Bits()
//                   line of Step2_JUL into the Bits() line of setup().
//
// SAFETY COMES FIRST (WATCH YOUR FINGERS)
//   1. D4 is set LOW before anything else, so Q1 keeps the motor bus off
//      VS while setup() runs. Before setup() runs, during a reset, and
//      during an upload, D4 is not driven, and R4 holds Q2 and Q1 off.
//   2. D5 to D10 are set LOW next: ENA and ENB are LOW, so no motor can
//      turn until a command is given.
//   3. VS is connected only while the state of the push button, SW, is
//      ON. One press turns it ON, the next press turns it OFF (latching
//      mode); DS3, the indicator LED on D12, shows the state.
//   4. STEP6_MOTORS only: ON is accepted only with the joystick at its
//      center. A press with the grip pushed is refused, and the serial
//      monitor prints the reason.
//   5. STEP6_MOTORS only: after VS is connected, the motors wait
//      STEP6_SETTLE_mS before the first command, so the supply of the
//      L298N is steady first.
//   6. STEP6_MOTORS only: each motor command is limited to
//      STEP6_PWM_LIMIT, half of full power as shipped.
//   7. OFF stops the motors first (ENA and ENB LOW) and then sets D4 LOW,
//      in the same pass of loop().
// -------------------------------------------------------------------------

// STEP6 SWITCHES: define exactly one.
// The circuit test, the motors stopped (shipped setting)
#define STEP6_CIRCUIT
// The motor test: place a comment mark on the line above and remove the
// comment mark from the line below
// #define STEP6_MOTORS

// Stop the build unless exactly one switch is defined
#if defined(STEP6_CIRCUIT) == defined(STEP6_MOTORS)
#error "Step6_Circuit: define exactly one of STEP6_CIRCUIT, STEP6_MOTORS"
#endif

// The limits of the motor test (STEP6_MOTORS)
// The largest motor command, 0 to 255; 128 is half of full power
#define STEP6_PWM_LIMIT 128
// The wait after VS is connected before the first command, in ms
#define STEP6_SETTLE_mS 500
// The dead zone about each measured center, in raw ADC counts
#define STEP6_DEAD_ZONE 25

#include <Arduino.h>
#include "Common.h"
#include "Joystick.h"
#include "Headers.h"
#include "JoystickMeasurements.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// The classes of the series (Headers.h)
L298N motors;
Joystick<float> joystick;
LinearMap<float> mapOutFromJoystick;
Timer timerTick;
Timer timerPrint;
Button buttonPower;

// Q2 and Q1, the motor power switch of Circuit-4, through R3:
// UNO D4 (CHIP-PD4)
int motorPowerPin = 4;
// true while D4 is HIGH and Q1 connects the motor bus to VS
bool powerOn = false;
// millis() when VS was connected, for the settle time
unsigned long powerOnTime = 0;
// The last motor commands, printed by printCheck()
int outLeft = 0;
int outRight = 0;

// One joystick axis, from raw ADC counts to -1.0 to 1.0. The measured
// center gives 0.0; a reading inside the dead zone also gives 0.0. Each
// side of the center is scaled to its own measured end, so a full push
// gives 1.0 or -1.0 even when the center is not 511.
float axis(int raw, int low, int center, int high)
{
    // Distance from the measured center, in counts
    int d = raw - center;
    // Inside the dead zone: the axis is at rest
    if (d > -STEP6_DEAD_ZONE && d < STEP6_DEAD_ZONE)
        return 0.0;
    // Above the center: scale by the high side; below: by the low side
    float v = (d > 0) ? (float)d / (float)(high - center)
                      : (float)d / (float)(center - low);
    // A reading past a measured end is held at the end
    return constrain(v, -1.0, 1.0);
}

// x of the joystick: VRx on A0, with the Step1 measurements of A0
float axisX()
{
    return axis(analogRead(A0), JOYSTICK_A0_LOW, JOYSTICK_A0_CENTER,
                JOYSTICK_A0_HIGH);
}

// y of the joystick: VRy on A1, with the Step1 measurements of A1
float axisY()
{
    return axis(analogRead(A1), JOYSTICK_A1_LOW, JOYSTICK_A1_CENTER,
                JOYSTICK_A1_HIGH);
}

// OFF: the motors stop first (ENA and ENB LOW), then Q1 disconnects VS
void powerDown()
{
    motors.PowerDownL298N();
    outLeft = 0;
    outRight = 0;
    digitalWrite(motorPowerPin, LOW);
    powerOn = false;
}

void setup()
{
    // SAFETY 1: D4 LOW before anything else; Q1 keeps VS off
    pinMode(motorPowerPin, OUTPUT);
    digitalWrite(motorPowerPin, LOW);

    // UNO pins, named after the L298N input each is wired to in Circuit-4,
    // the same as Step2_JUL
    int8_t ENB = 5;
    int8_t IN4 = 6;
    int8_t IN3 = 7;
    int8_t IN2 = 8;
    int8_t IN1 = 9;
    int8_t ENA = 10;
    // L298N Constructor, in the order of Step2_JUL
    motors = L298N(ENB, IN4, IN3, IN2, IN1, ENA);
    // SAFETY 2: D5 to D10 as outputs, LOW; no motor can turn
    motors.PinsL298N();
    // The Bits() line: copy the value of the Bits() line of Step2_JUL,
    // found with the Motor Movement Checklist (L298N Setup)
    motors.Bits(BitsL298N::bits_0000);

    // The joystick algorithm of the series (Joystick.h)
    joystick = Joystick<float>();
    // Joystick output (-1 to 1) to motor command, limited (SAFETY 6)
    mapOutFromJoystick = LinearMap<float>(-1.0, 1.0,
                                          -STEP6_PWM_LIMIT,
                                          STEP6_PWM_LIMIT);

    // J2, the USB serial adapter, carries the serial monitor (9600 baud)
    Serial.begin(9600);
    while (!Serial) { }
    // Program title. Each backslash joins the next line to this
    // statement. Each string starts with \n and is closed before its
    // backslash, so the indentation is not printed.
    Serial.println(F(                                          \
        "\n................................................"   \
        "\nStep6_Circuit: the test of Circuit-4"               \
        "\nUse with Circuit-4 ONLY"                            \
        "\nSelected in platformio.ini: +<Step6_Circuit/>"));
#ifdef STEP6_CIRCUIT
    Serial.println(F(                                          \
        "\nSTEP6_CIRCUIT: the motors stay stopped"             \
        "\nPress SW: Q1 connects VS; press again: VS off"));
#else
    Serial.println(F(                                          \
        "\nSTEP6_MOTORS: center the joystick, then press SW"   \
        "\nPress SW again to stop the motors and VS"));
#endif

    // Push button and indicator LED
    // J1 SW with R10: UNO D2 (CHIP-PD2)
    int buttonPin = 2;
    // DS3 with R11: UNO D12 (CHIP-PB4)
    int ledPin = 12;
    buttonPower = Button(buttonPin, ledPin);
    // SAFETY 3: latching mode; press once for ON, press again for OFF
    buttonPower.setLatching(true);
    // D2 as INPUT_PULLUP, the LED pin as OUTPUT
    buttonPower.begin();
    // R10 is the external pull up resistor of Circuit-4: internal pull
    // up off
    pinMode(buttonPin, INPUT);
}

// One control tick of the motor test: joystick to motor commands
void drive()
{
    // The two axes, corrected with the Step1 measurements
    joystick.UpdateInputs(axisX(), axisY());
    // The outputs of the algorithm, mapped to limited commands
    outLeft = (int)mapOutFromJoystick.Map(joystick.Left());
    outRight = (int)mapOutFromJoystick.Map(joystick.Right());
    // The third argument, true, lets the enable pins carry the commands
    motors.UpdateL298N(outLeft, outRight, true);
}

// The report of the serial monitor, once each second
void printCheck()
{
    // Raw values first: the ADC counts of VRx and VRy, 0 to 1023
    int xDigital = analogRead(A0);
    int yDigital = analogRead(A1);

    Serial.println();
    Serial.print(F("A0 (VRx) "));
    Serial.print(xDigital);
    Serial.print(F("  A1 (VRy) "));
    Serial.println(yDigital);
    // Then the calculated values: x and y, -1.00 to 1.00
    Serial.print(F("x "));
    Serial.print(axisX(), 2);
    Serial.print(F("  y "));
    Serial.println(axisY(), 2);
    // The state of the push button, and what the bench shows for it
    if (powerOn)
        Serial.println(F("SW ON: DS3 on, D4 HIGH, DS2 on, VS on"));
    else
        Serial.println(F("SW OFF: DS3 off, D4 LOW, DS2 off, VS 0 V"));
#ifdef STEP6_MOTORS
    // The last motor commands, at most STEP6_PWM_LIMIT
    Serial.print(F("Left "));
    Serial.print(outLeft);
    Serial.print(F("  Right "));
    Serial.println(outRight);
#endif
}

void loop()
{
    // Button Class: debounce, the latched state, and DS3
    buttonPower.updateButton();
    bool requested = buttonPower.isButtonOn();

#ifdef STEP6_MOTORS
    // SAFETY 4: ON is refused unless the joystick is at its center
    if (requested && !powerOn && (axisX() != 0.0 || axisY() != 0.0))
    {
        buttonPower.resetButton();
        requested = false;
        Serial.println(F("Center the joystick, then press SW"));
    }
#endif

    // ON: Q1 connects the motor bus to VS, and the settle time starts
    if (requested && !powerOn)
    {
        digitalWrite(motorPowerPin, HIGH);
        powerOnTime = millis();
        powerOn = true;
    }
    // SAFETY 7: OFF stops the motors, then disconnects VS
    else if (!requested && powerOn)
    {
        powerDown();
    }

#ifdef STEP6_MOTORS
    // SAFETY 5: no command until VS has settled; then one control tick
    // each BUTTON_TIMER_mS (Common.h, 100 ms)
    if (powerOn && millis() - powerOnTime >= STEP6_SETTLE_mS &&
        timerTick.isTimer(BUTTON_TIMER_mS))
    {
        drive();
    }
#endif

    // Timer Class: one report each second
    if (timerPrint.isTimer(1000))
    {
        printCheck();
    }
}

// -------------------------------------------------------------------------
// CONNECTIONS OF CIRCUIT-4 USED BY THIS PROGRAM (Circuit-4 ONLY)
//   D2   (PD2)  J1 SW, with the pull up resistor R10 to the 5 V bus (A)
//   D4   (PD4)  R3 to the base of Q2; Q2 drives the gate of Q1
//   D5   (PD5)  ENB of the L298N, with the pull down resistor R9
//   D6   (PD6)  IN4
//   D7   (PD7)  IN3
//   D8   (PB0)  IN2
//   D9   (PB1)  IN1
//   D10  (PB2)  ENA of the L298N, with the pull down resistor R8
//   D12  (PB4)  DS3 through R11
//   A0   (PC0)  J1 VRx
//   A1   (PC1)  J1 VRy
//   DS1 shows the fused bus; DS2 shows VS. C11, 470 uF, holds VS steady
//   at the L298N during the surges of motor current.
// -------------------------------------------------------------------------
// THE CIRCUIT TEST (STEP6_CIRCUIT)
//   1. Circuit-4 is wired as drawn, with Q1 between the fused bus and VS.
//      The motors are disconnected from OUT1 to OUT4.
//   2. Turn on S1 and upload this program through J2. DS1 lights; DS2 and
//      DS3 stay dark; VS reads 0 V, also during the upload.
//   3. Move the joystick: A0 and A1 follow each axis, and x and y read
//      0.00 at rest and reach -1.00 and 1.00 at the ends.
//   4. Press SW once: DS3 and DS2 light, and VS reads the bus voltage.
//      Press SW again: DS3 and DS2 go dark, and VS falls to 0 V.
//   5. Record each reading, raw values first.
// -------------------------------------------------------------------------
// THE MOTOR TEST (STEP6_MOTORS)
//   1. The circuit test has passed. Turn off S1 and connect the motors.
//   2. Turn on S1, select STEP6_MOTORS, and upload; VS stays at 0 V during
//      the upload. Keep fingers clear of the wheels.
//   3. Push the grip and press SW: the press is refused, and the serial
//      monitor prints "Center the joystick, then press SW".
//   4. Release the grip and press SW: DS3 and DS2 light, and after
//      STEP6_SETTLE_mS the motors follow the joystick at no more than
//      STEP6_PWM_LIMIT.
//   5. Check each of the eight positions of the Motor Movement Checklist
//      at this limited command.
//   6. Press SW: the motors stop and VS falls to 0 V.
//   7. Turn off S1, and select STEP6_CIRCUIT again.
// -------------------------------------------------------------------------
