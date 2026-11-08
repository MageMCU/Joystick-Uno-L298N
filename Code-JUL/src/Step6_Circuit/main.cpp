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
//   2026-11-07  v7.4.0
//   Step6_Circuit/main.cpp last changed: 2026-11-07  v7.4.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//
// Layout: every line fits the cutoff of 80 characters, and each comment
// is written on its own line above the statement it explains.
//
// Revised 20261107 (v7.4.0): Circuit-4A and Circuit-4B, version
// 20261106.1221. The bus monitor on A2 decides with the push button when
// D4 connects VS; a switch selects the Electronics Lab supply or the
// robot supply; P2, the Uno programmer, replaces the USB serial adapter.
//
// -------------------------------------------------------------------------
// CIRCUIT-4 AND THIS PROGRAM GO TOGETHER: USE THEM WITH EACH OTHER ONLY
//   * Circuit-4, the Complete Wiring (Article 1009, Appendix C), drawn on
//     two sheets, Circuit-4A and Circuit-4B, is used with this program
//     ONLY. The other programs of Code-JUL do not set D4, so on Circuit-4
//     they leave the motor supply off; they are used with Circuit-1, the
//     basic wiring.
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
// THE TWO SHEETS
//   Circuit-4A  the power supplies, completely separate: the Electronics
//               Lab supply (bench) and the robot supply (battery). One is
//               connected at a time; each ends at B, the motor bus.
//   Circuit-4B  the common circuit: the bus monitor, U1 and the 5 V bus,
//               the motor power switch, U3 and its parts, P2, J1, U2, M1,
//               and M2.
//
// POWER: ONE SWITCH TURNS ON CIRCUIT-4
// On the bench S1, a double pole switch in the hot and the neutral
// conductors of the line cord, turns on the whole bench; on the robot S3
// at RUN does the same. The 7805 (U1) makes the 5 V bus, connector A,
// which powers U3, the joystick, and the logic of the L298N. U3 starts
// first while R4 holds Q1 off; this program then decides when Q1
// connects the motor bus to VS. P2, the Uno programmer (an Uno with its
// ATmega328P removed), carries only the upload and the serial monitor
// through RX, TX, and GND.
//
// THE BUS MONITOR (v7.4.0)
// R15, 68 kOhm, and R16, 10 kOhm, divide the motor bus by 7.8 into A2
// (PC2, pin 25 of U3), and C12 filters the reading:
//   V(A2) = V(bus) x R16 / (R15 + R16) = V(bus) x 10 / 78
//   count = V(A2) / 5 V x 1023
// The counts: 315 (12 V), 346 (13.2 V), 388 (14.8 V), 441 (16.8 V),
// 472 (18 V). The program averages ten readings taken 100 ms apart, about
// one second, and accepts the bus only while the average is in range:
//   STEP6_LAB    315 to 472 (12 V to 18 V): a supply that is off or a
//                variac set too high keeps VS off.
//   STEP6_ROBOT  above 346 (13.2 V): VS goes off at the cutoff of BT1;
//                the brief dip of a motor start does not trip it.
//
// TWO SWITCHES, TWO JOBS: THE POWER SWITCH AND SW
//   S1 or S3  the power switch (hardware). ON powers U3, the joystick, and
//             the L298N logic; the motor supply, VS, stays off.
//   SW        the push button of the joystick, read by this program (D2).
//             It does two things with one state, ON or OFF:
//               ON   the button state is ON (DS3 lights) AND, while the
//                    bus is in range, the motor supply is ON: D4 HIGH, Q2
//                    on, Q1 connects the motor bus to VS (DS2 lights).
//                    With STEP6_MOTORS the joystick then drives the
//                    motors.
//               OFF  the motors stop (ENA and ENB LOW), the motor supply
//                    is OFF (D4 LOW, VS 0 V), and the button state is OFF
//                    (DS3 and DS2 dark).
//   A bus out of range turns the button state OFF as well, and the serial
//   monitor prints the reason.
//
// THE ORDER ON THE BENCH
//   1. Power switch ON: U3 starts; VS stays at 0 V (DS1 on, DS2 dark).
//   2. Wait about one second for the bus average.
//   3. SW pressed: the motor supply comes on, and the motors may run.
//   4. SW pressed again: the motors stop, and the motor supply goes off.
//   5. Power switch OFF: everything stops.
//
// WHEN THE PROGRAM DOES NOT TURN THE MOTOR SUPPLY ON
// The motor supply comes on only when a program sets D4 HIGH. Before this
// program runs, during a reset or an upload, with another program of
// Code-JUL (they never set D4), or with the wire to R3 open, D4 is not
// HIGH: R4 holds Q2 off, R1 holds Q1 off, and VS stays at 0 V. U3, the
// joystick, and the L298N logic still run, but the motors cannot turn.
// While VS is 0 V the L298N has no motor supply, so ENA and ENB need no
// pull down resistors. Circuit-4 is safe by default.
//
// THE PROGRAM SWITCHES (precompiler switches, below)
//   The test, define exactly one:
//   STEP6_CIRCUIT  the circuit test (shipped setting). The motors stay
//                  stopped: ENA and ENB stay LOW for the whole program.
//                  Each press of SW turns VS on or off through D4, Q2,
//                  and Q1, and the serial monitor prints the bus monitor
//                  and the joystick.
//   STEP6_MOTORS   the motor test, run only after the circuit test
//                  passes. The joystick drives the motors through the
//                  L298N at a limited command, with the safety rules
//                  below.
//   The supply, define exactly one:
//   STEP6_LAB      the Electronics Lab supply (shipped setting)
//   STEP6_ROBOT    the robot supply, BT1
// With both or neither of a pair the build stops with an #error message.
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
//   4. VS is connected only while the bus monitor average is in range
//      (STEP6_LAB or STEP6_ROBOT). A press before the first average, or
//      with the bus out of range, is refused; a bus that leaves the range
//      turns everything OFF.
//   5. STEP6_MOTORS only: ON is accepted only with the joystick at its
//      center. A press with the grip pushed is refused, and the serial
//      monitor prints the reason.
//   6. STEP6_MOTORS only: after VS is connected, the motors wait
//      STEP6_SETTLE_mS before the first command, so the supply of the
//      L298N is steady first.
//   7. STEP6_MOTORS only: each motor command is limited to
//      STEP6_PWM_LIMIT, half of full power as shipped.
//   8. OFF stops the motors first (ENA and ENB LOW) and then sets D4 LOW,
//      in the same pass of loop().
// -------------------------------------------------------------------------

// STEP6 TEST SWITCHES: define exactly one.
// The circuit test, the motors stopped (shipped setting)
#define STEP6_CIRCUIT
// The motor test: place a comment mark on the line above and remove the
// comment mark from the line below
// #define STEP6_MOTORS

// STEP6 SUPPLY SWITCHES: define exactly one (v7.4.0).
// The Electronics Lab supply of Circuit-4A (shipped setting)
#define STEP6_LAB
// The robot supply of Circuit-4A, BT1: place a comment mark on the line
// above and remove the comment mark from the line below
// #define STEP6_ROBOT

// Stop the build unless exactly one switch of each pair is defined
#if defined(STEP6_CIRCUIT) == defined(STEP6_MOTORS)
#error "Step6_Circuit: define exactly one of STEP6_CIRCUIT, STEP6_MOTORS"
#endif
#if defined(STEP6_LAB) == defined(STEP6_ROBOT)
#error "Step6_Circuit: define exactly one of STEP6_LAB, STEP6_ROBOT"
#endif

// The limits of the motor test (STEP6_MOTORS)
// The largest motor command, 0 to 255; 128 is half of full power
#define STEP6_PWM_LIMIT 128
// The wait after VS is connected before the first command, in ms
#define STEP6_SETTLE_mS 500
// The dead zone about each measured center, in raw ADC counts
#define STEP6_DEAD_ZONE 25

// The bus monitor (v7.4.0), in raw ADC counts of A2
// The lowest accepted average: 315 is 12 V (LAB); 346 is 13.2 V (ROBOT)
#ifdef STEP6_LAB
#define STEP6_BUS_LOW 315
#else
#define STEP6_BUS_LOW 346
#endif
// The highest accepted average: 472 is 18 V (LAB); the robot has no upper
// limit, because BT1 is never above 16.8 V (441)
#ifdef STEP6_LAB
#define STEP6_BUS_HIGH 472
#else
#define STEP6_BUS_HIGH 1023
#endif
// Ten readings, one each 100 ms: an average over about one second
#define STEP6_BUS_SAMPLES 10
#define STEP6_BUS_SAMPLE_mS 100
// The divider of R15 and R16 times 1000: (68 + 10) / 10 = 7.8
#define STEP6_BUS_DIVIDER_x1000 7800L

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
Timer timerBus;
Button buttonPower;

// Q2 and Q1, the motor power switch of Circuit-4B, through R3:
// UNO D4 (CHIP-PD4)
int motorPowerPin = 4;
// true while D4 is HIGH and Q1 connects the motor bus to VS
bool powerOn = false;
// millis() when VS was connected, for the settle time
unsigned long powerOnTime = 0;
// The last motor commands, printed by printCheck()
int outLeft = 0;
int outRight = 0;

// The bus monitor (v7.4.0): the last ten readings of A2, their sum, the
// next place to write, and how many places hold a reading
int busReadings[STEP6_BUS_SAMPLES];
long busSum = 0;
uint8_t busIndex = 0;
uint8_t busCount = 0;

// The bus monitor: one reading of A2 into the average of the last ten
void sampleBus()
{
    int raw = analogRead(A2);
    if (busCount == STEP6_BUS_SAMPLES)
        busSum -= busReadings[busIndex];
    else
        busCount++;
    busReadings[busIndex] = raw;
    busSum += raw;
    busIndex = (busIndex + 1) % STEP6_BUS_SAMPLES;
}

// The bus monitor: the average count of A2, or -1 before ten readings
int busAverage()
{
    if (busCount < STEP6_BUS_SAMPLES)
        return -1;
    return (int)(busSum / STEP6_BUS_SAMPLES);
}

// The bus monitor: true while the average lies in the accepted range
bool busInRange()
{
    int average = busAverage();
    return average >= STEP6_BUS_LOW && average <= STEP6_BUS_HIGH;
}

// The bus monitor: a count of A2 to the motor bus in millivolts
long busMillivolts(int count)
{
    return (long)count * 5000L / 1023L * STEP6_BUS_DIVIDER_x1000 / 1000L;
}

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

    // UNO pins, named after the L298N input each is wired to in
    // Circuit-4B, the same as Step2_JUL
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
    // Joystick output (-1 to 1) to motor command, limited (SAFETY 7)
    mapOutFromJoystick = LinearMap<float>(-1.0, 1.0,
                                          -STEP6_PWM_LIMIT,
                                          STEP6_PWM_LIMIT);

    // P2, the Uno programmer, carries the serial monitor (9600 baud)
    Serial.begin(9600);
    while (!Serial) { }
    // Program title. Each backslash joins the next line to this
    // statement. Each string starts with \n and is closed before its
    // backslash, so the indentation is not printed.
    Serial.println(F(                                          \
        "\n................................................"   \
        "\nStep6_Circuit: the test of Circuit-4A and 4B"       \
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
#ifdef STEP6_LAB
    Serial.println(F(                                          \
        "\nSTEP6_LAB: bus accepted at A2 counts 315 to 472"));
#else
    Serial.println(F(                                          \
        "\nSTEP6_ROBOT: bus accepted above A2 count 346"));
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
    // R10 is the external pull up resistor of Circuit-4B: internal pull
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
    // Raw values first: the ADC counts of A2 (the bus monitor average),
    // VRx, and VRy, 0 to 1023
    int busCounts = busAverage();
    int xDigital = analogRead(A0);
    int yDigital = analogRead(A1);

    Serial.println();
    Serial.print(F("A2 (bus) "));
    Serial.print(busCounts);
    Serial.print(F("  A0 (VRx) "));
    Serial.print(xDigital);
    Serial.print(F("  A1 (VRy) "));
    Serial.println(yDigital);
    // Then the calculated values: the motor bus in volts, x and y
    Serial.print(F("bus "));
    if (busCounts < 0)
        Serial.print(F("averaging"));
    else
    {
        Serial.print(busMillivolts(busCounts) / 1000.0, 1);
        Serial.print(F(" V"));
    }
    Serial.print(busInRange() ? F(" in range") : F(" OUT OF RANGE"));
    Serial.print(F("  x "));
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
    // The bus monitor: one reading of A2 each STEP6_BUS_SAMPLE_mS
    if (timerBus.isTimer(STEP6_BUS_SAMPLE_mS))
        sampleBus();

    // Button Class: debounce, the latched state, and DS3
    buttonPower.updateButton();
    bool requested = buttonPower.isButtonOn();

    // SAFETY 4: ON is refused, and ON is ended, while the bus is out of
    // range
    if (requested && !busInRange())
    {
        buttonPower.resetButton();
        requested = false;
        Serial.println(F("Bus out of range: VS off (see A2 above)"));
    }

#ifdef STEP6_MOTORS
    // SAFETY 5: ON is refused unless the joystick is at its center
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
    // SAFETY 8: OFF stops the motors, then disconnects VS
    else if (!requested && powerOn)
    {
        powerDown();
    }

#ifdef STEP6_MOTORS
    // SAFETY 6: no command until VS has settled; then one control tick
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
// CONNECTIONS OF CIRCUIT-4B USED BY THIS PROGRAM (Circuit-4 ONLY)
//   D0   (PD0)  RXD, pin 2, through R13 from P2 (note below)
//   D1   (PD1)  TXD, pin 3, to P2 (note below)
//   D2   (PD2)  J1 SW, with the pull up resistor R10 to the 5 V bus (A)
//   D4   (PD4)  R3 to the base of Q2 (G); Q2 drives the gate of Q1
//   D5   (PD5)  ENB of the L298N
//   D6   (PD6)  IN4
//   D7   (PD7)  IN3
//   D8   (PB0)  IN2
//   D9   (PB1)  IN1
//   D10  (PB2)  ENA of the L298N
//   D12  (PB4)  DS3 through R11
//   A0   (PC0)  J1 VRx
//   A1   (PC1)  J1 VRy
//   A2   (PC2)  the bus monitor, R15 and R16, filtered by C12 (H)
//   DS1 shows the motor bus; DS2 shows VS. C11, 470 uF, holds VS steady
//   at the L298N during the surges of motor current. ENA and ENB have no
//   pull down resistors: while D4 is not driven, R4 keeps VS off, so the
//   L298N has no motor supply.
// P2, THE UNO PROGRAMMER: an Uno with its ATmega328P removed. P2 RX goes
// through R13, 10 kOhm, to RXD of U3 (pin 2); P2 TX goes to TXD of U3
// (pin 3); the grounds are joined. Press S2 (reset) as each upload
// starts. P2 may be disconnected once the program is tested and
// approved. The U2 jumpers 5V EN, ENA, and ENB are removed.
// -------------------------------------------------------------------------
// THE CIRCUIT TEST (STEP6_CIRCUIT)
//   1. Circuit-4A and Circuit-4B are wired as drawn, with Q1 between the
//      motor bus and VS. The motors are disconnected from OUT1 to OUT4.
//   2. Select STEP6_LAB or STEP6_ROBOT for the supply in use.
//   3. Turn on the power switch (S1, or S3 at RUN) and upload this
//      program through P2, pressing S2 as the upload starts. DS1 lights;
//      DS2 and DS3 stay dark; VS reads 0 V, also during the upload.
//   4. Read the bus: record the A2 count, then the bus voltage, and the
//      multimeter reading at test point (1) or (2). Each pair agrees
//      within about 0.2 V.
//   5. Move the joystick: A0 and A1 follow each axis, and x and y read
//      0.00 at rest and reach -1.00 and 1.00 at the ends.
//   6. Press SW once: DS3 and DS2 light, and VS reads the bus voltage.
//      Press SW again: DS3 and DS2 go dark, and VS falls to 0 V.
//   7. STEP6_LAB with the variac supply only: with SW ON, lower the
//      variac until the bus falls below 12 V. VS goes off and the serial
//      monitor prints "Bus out of range". Raise it to 14 V to 15 V again.
//   8. Record each reading, raw values first.
// -------------------------------------------------------------------------
// THE MOTOR TEST (STEP6_MOTORS)
//   1. The circuit test has passed. Turn off the power switch and connect
//      the motors.
//   2. Turn on the power switch, select STEP6_MOTORS, and upload; VS
//      stays at 0 V during the upload. Keep fingers clear of the wheels.
//   3. Push the grip and press SW: the press is refused, and the serial
//      monitor prints "Center the joystick, then press SW".
//   4. Release the grip and press SW: DS3 and DS2 light, and after
//      STEP6_SETTLE_mS the motors follow the joystick at no more than
//      STEP6_PWM_LIMIT.
//   5. Check each of the eight positions of the Motor Movement Checklist
//      at this limited command.
//   6. Measure the voltage from the source to the drain of Q1 with the
//      motors running: below 0.1 V (Article 1009, The gate of Q1). On the
//      robot repeat it near 13.2 V.
//   7. Press SW: the motors stop and VS falls to 0 V.
//   8. Turn off the power switch, and select STEP6_CIRCUIT again.
// -------------------------------------------------------------------------
