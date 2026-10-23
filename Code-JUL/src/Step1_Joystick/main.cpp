//
// Carpenter Software
// Folder: src/Step1_Joystick: File: main.cpp
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
// ---------------------------------------------------------------
// The Initial Joystick Setup Code for Step1_Joystick
// (Article 1009, Joystick Setup)
// A self test of the joystick connections: the push button (SW on
// D2), A0 (VRx), and A1 (VRy). Wire all of Circuit-1 first; Step 1
// to Step 4 use that wiring unchanged. Keep the motor supply off for
// this step.
// Purpose: find faults that no Bits() value corrects (an open wire,
// a dead axis, a floating D2) before the motors get power.
// Open the serial monitor at 9600 baud. Each test gives one
// instruction and waits: follow it, then press Enter. Nothing is
// timed, so each value can be read before the next test starts.
// The program first asks for Enter to start (repeated every 3 s).
//   Test 1  Press the push button and hold it
//   Test 2  Release the push button
//   Test 3  Leave the grip at rest       (measures the center)
//   Test 4  Move the grip to every edge  (measures the ends)
//   Test 5  Release the grip             (measures the return)
// The report gives PASS or FAIL for each test, the measured values,
// and the map() calls that fit this joystick. A press of the button
// during Tests 3 to 5 also fails the self test (a floating D2). Which way A0 and A1
// count does not matter; the Bits() value of L298N Setup corrects
// the orientation. After the report the program asks:
//   r  run the self test again
//   v  view the live values of A0, A1, and SW four times a second
//      for 20 seconds; then the question is asked again
// Revised 20261022 (v6.2.0): questions answered with Enter replace
// the timed tests of v6.0.0, the button is tested first, and the
// live values are printed on request (DEBUG_STEP1_LIVE is removed;
// the serial monitor output of this program is always on).
// Revised 20261022 (v6.3.0): the program asks for Enter before
// Test 1 and repeats the question every 3 seconds, so the first
// instruction is seen whenever the serial monitor connects (up to
// v6.2.3 the first Enter could end Test 1 before it was read).
// Characters typed ahead are discarded before each question. The
// report and the live values print in columns of spaces, not tabs.
// ---------------------------------------------------------------
#include <Arduino.h>
#include "Button.h"
#include "Timer.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// ---------------------------------------------------------------
// Self test limits, in ADC counts. analogRead() returns 0 to 1023;
// the middle of that range is 511. A real joystick seldom rests at
// exactly 511 or reaches 0 and 1023 at its ends, so the self test
// measures both instead of assuming them.
//   ADC_MIDDLE               511, the middle of 0 to 1023.
//   CENTER_TOLERANCE         The rest reading must lie within this
//                            many counts of ADC_MIDDLE. Step2_JUL and
//                            Step4_Generated map 0 to 1023 onto -1 to
//                            1 and assume the rest reading is 511;
//                            their dead zone, X_OFFSET 0.05 of 511
//                            counts (about 25), absorbs a smaller
//                            offset. A larger one would leave the
//                            motors turning with the grip released.
//   MIN_TRAVEL               Each direction must reach this many
//                            counts from the center.
//   RETURN_TOLERANCE         The released grip must come back within
//                            this many counts of the center, for the
//                            same reason.
// ---------------------------------------------------------------
const int ADC_MIDDLE = 511;
const int CENTER_TOLERANCE = 25;
const int MIN_TRAVEL = 200;
const int RETURN_TOLERANCE = 25;

const unsigned long SAMPLE_MS = 20;  // Test 4: 50 samples/s
const unsigned long PRINT_MS = 250;  // live values: 4 times/s
const unsigned long LIVE_MS = 20000; // live values: 20 seconds

// One joystick axis: its pin and the values the self test measures.
struct Axis
{
    uint8_t pin;
    const __FlashStringHelper *name;
    int center; // Test 3: rest reading
    int low;    // Test 4: lowest reading
    int high;   // Test 4: highest reading
    int rest;   // Test 5: reading after the release

    // Average of 16 readings, which smooths the ADC noise
    int readAverage() const
    {
        long sum = 0;
        for (int i = 0; i < 16; i++)
            sum += analogRead(pin);
        return (int)(sum / 16);
    }

    // Both directions reached MIN_TRAVEL from the center
    bool travelPassed() const
    {
        return (center - low) >= MIN_TRAVEL && (high - center) >= MIN_TRAVEL;
    }

    // Map a raw reading to -100 to 100 with Arduino map(). The
    // center seldom lies halfway between low and high, so each side
    // of the center has its own map() call: low to center gives
    // -100 to 0, and center to high gives 0 to 100. constrain()
    // holds the result inside -100 to 100, because map() does not.
    int mapped(int raw) const
    {
        long value;
        if (raw < center)
            value = map(raw, low, center, -100, 0);
        else
            value = map(raw, center, high, 0, 100);
        return (int)constrain(value, -100, 100);
    }
};

// What the program does while it waits for Enter
enum class Wait
{
    Button,  // Tests 1 and 2: the button only (debounce and LED)
    Count,   // Tests 3 and 5: also count the presses of the button
    Record,  // Test 4: also count presses and record the ends
};

Button button;     // push button (SW) and indicator LED
Timer timerSample; // paces the readings of Test 4
Timer timerPrint;  // paces the live values
Timer timerLive;   // length of the live values
Timer timerStart;  // repeats the start question
Axis axisA0;       // joystick VRx on A0
Axis axisA1;       // joystick VRy on A1
bool passed[5];    // result of Tests 1 to 5
int extraPresses;  // presses during Tests 3 to 5 (0 expected)

// ---------------------------------------------------------------
// Serial input (the same line rules as Step3_Generator)
// ---------------------------------------------------------------
#ifdef TEST_INPUT
// Simulation only (not defined by platformio.ini): typed answers
// supplied as a string, as a student would send them
const char *testInput = TEST_INPUT;
int readChar()
{
    return *testInput ? *testInput++ : -1;
}
#else
int readChar()
{
    return Serial.read();
}
#endif

// Track the lowest and highest reading of one axis
void recordEnds(Axis &axis)
{
    int raw = analogRead(axis.pin);
    if (raw < axis.low)
        axis.low = raw;
    if (raw > axis.high)
        axis.high = raw;
}

// The work done on every pass while the program waits for a key
void serviceWait(Wait wait)
{
    // Read the button on every pass (debounce and LED)
    button.updateButton();

    if (wait != Wait::Button && button.wasPressed())
        extraPresses++;

    if (wait == Wait::Record && timerSample.isTimer(SAMPLE_MS))
    {
        recordEnds(axisA0);
        recordEnds(axisA1);
    }
}

// Reads one line typed in the serial monitor and echoes it.
// Enter (CR or LF) ends the line; Backspace removes one character.
// Line endings: LF (Arduino IDE, Newline), CR, and CR LF (PlatformIO)
// all end a line. The LF of a CR LF pair is skipped, so it does not
// end the next line as an empty answer.
bool lastWasCR = false;

void readLine(char *line, int size, Wait wait)
{
    int n = 0;
    while (true)
    {
        serviceWait(wait);
        int c = readChar();
        if (c < 0)
            continue;
        if (c == '\n' && lastWasCR)
        {
            lastWasCR = false;
            continue;
        }
        lastWasCR = (c == '\r');
        if (c == '\r' || c == '\n')
            break;
        if (c == 8 || c == 127) // Backspace or Delete
        {
            if (n > 0)
            {
                n--;
                Serial.print(F("\b \b"));
            }
            continue;
        }
        if (n < size - 1)
        {
            line[n++] = (char)c;
            Serial.print((char)c);
        }
    }
    line[n] = '\0';
    Serial.println();
}

// Discards every character waiting in the serial input. Called
// before each question, so a stray character or an Enter typed
// ahead (a double Enter, the LF of a CR LF pair) cannot answer a
// question that has not been asked yet (v6.3.0).
void discardInput()
{
#ifndef TEST_INPUT // the simulation supplies its answers in order
    while (readChar() >= 0)
    {
    }
#endif
    lastWasCR = false;
}

// Asks for Enter before Test 1 and repeats the question every 3
// seconds (v6.3.0). The board starts the program as soon as it is
// powered or reset, which can be before the serial monitor listens;
// text sent then is lost. The repeated question is seen whenever the
// monitor connects, and Test 1 starts only after a deliberate Enter.
void waitForStart()
{
    discardInput();
    timerStart.resetTimer();
    timerStart.isTimer(3000); // arm the timer
    Serial.println(F("Press Enter to start the joystick self test."));
    while (true)
    {
        button.updateButton();
        if (timerStart.isTimer(3000))
            Serial.println(F("Press Enter to start the joystick self test."));
        int c = readChar();
        if (c == '\r' || c == '\n')
            break;
    }
}

// Waits for Enter; anything typed before it is ignored
void waitForEnter(Wait wait)
{
    char line[8];
    discardInput(); // v6.3.0: nothing typed ahead counts
    Serial.print(F("  Press Enter: "));
    readLine(line, sizeof(line), wait);
}

// Reads a one letter answer; returns it in lower case, or 0 when the
// line is not one of the two letters a and b
char readLetter(char a, char b)
{
    char line[8];
    readLine(line, sizeof(line), Wait::Button);
    char c = tolower(line[0]);
    if (line[1] == '\0' && (c == a || c == b))
        return c;
    return 0;
}

// ---------------------------------------------------------------
// Printing
// ---------------------------------------------------------------

// A blank line and a dotted line mark the start of each new output
// in the serial monitor, so the newest instruction or report is found
// at a glance.
void printDots()
{
    Serial.println();
    Serial.println(F("................................................"));
}

void printPass(bool pass)
{
    Serial.println(pass ? F("PASS") : F("FAIL"));
}

void printResult(int number, const __FlashStringHelper *label)
{
    Serial.print(F("Test "));
    Serial.print(number);
    Serial.print(F("  "));
    Serial.print(label);
    printPass(passed[number - 1]);
}

// Prints a number right aligned in a column of the given width
// (v6.3.0). The report used tabs up to v6.2.3; a tab jumps to the
// next tab stop, every 8 columns, and the row label "A0:   " (6
// characters) put each value one column left of its heading. Serial
// monitors may also place tab stops differently. Spaces print the
// same in every monitor.
// Note: String(value, 3) is not a column width. For a float the
// second argument is the number of decimal places; for an int it is
// the base, so String(508, 3) gives 200211 (508 in base 3).
void printColumn(long value, uint8_t width)
{
    uint8_t digits = (value < 0) ? 2 : 1; // the minus sign counts
    for (long v = (value < 0) ? -value : value; v >= 10; v /= 10)
        digits++;
    for (uint8_t i = digits; i < width; i++)
        Serial.print(' ');
    Serial.print(value);
}

// Width of each column of the report, in characters
const uint8_t COLUMN = 8;

void printAxisRow(const Axis &axis)
{
    Serial.print(axis.name);
    Serial.print(F(": "));
    printColumn(axis.low, COLUMN);
    printColumn(axis.center, COLUMN);
    printColumn(axis.high, COLUMN);
    printColumn(axis.rest, COLUMN);
    Serial.println();
}

// The two map() calls of one axis, with the measured values
void printMapCalls(const Axis &axis)
{
    Serial.print(F("  below center: map("));
    Serial.print(axis.name);
    Serial.print(F(", "));
    Serial.print(axis.low);
    Serial.print(F(", "));
    Serial.print(axis.center);
    Serial.println(F(", -100, 0)"));
    Serial.print(F("  above center: map("));
    Serial.print(axis.name);
    Serial.print(F(", "));
    Serial.print(axis.center);
    Serial.print(F(", "));
    Serial.print(axis.high);
    Serial.println(F(", 0, 100)"));
}

// The readings of both axes, after each axis test
void printAxisReadings(int valueA0, int valueA1)
{
    Serial.print(F("  A0: "));
    Serial.print(valueA0);
    Serial.print(F("  A1: "));
    Serial.print(valueA1);
    Serial.print(F("  "));
}

// ---------------------------------------------------------------
// If a test fails:
//   Test 1  No press seen: check the SW wire and the 10 kOhm pull up
//           on D2. PASS, but the LED stayed off: check the LED wiring
//           (D12 and its resistor).
//   Test 2  No release seen: check the pull up resistor on D2.
//   Test 3  A center near 0 or 1023: check the VRx (A0) or VRy (A1)
//           wire, then the 5V and GND wires of the module. A center
//           between those, but more than 25 counts from 511: the
//           module rests off center; try another module.
//   Test 4  One direction short of MIN_TRAVEL: check that wire, and
//           move the grip all the way to the edge.
//   Test 5  The grip does not come back to center: try another
//           module, or enlarge the dead zone of Step2_JUL.
//   Presses during Tests 3 to 5: a floating D2 gives presses that no
//           one made. Any press fails the self test (v6.2.1). Check the
//           pull up resistor on D2.
// Joystick modules are not all built the same way.
// ---------------------------------------------------------------
void printReport()
{
    printDots();
    Serial.println(F("Self Test Report"));
    // "Axis" and each heading fill the width of the columns below
    Serial.println(F("Axis     low  center    high    rest"));
    printAxisRow(axisA0);
    printAxisRow(axisA1);
    printResult(1, F("Button press                 "));
    printResult(2, F("Button release               "));
    printResult(3, F("Center (511, within 25)      "));
    printResult(4, F("Ends (200 counts each way)   "));
    printResult(5, F("Return (within 25 of center) "));
    Serial.print(F("Presses during Tests 3 to 5: "));
    Serial.print(extraPresses);
    Serial.println(F(" (0 expected)"));

    // Any press during Tests 3 to 5 fails the self test (v6.2.1)
    bool all = extraPresses == 0;
    for (int i = 0; i < 5; i++)
        all = all && passed[i];

    if (all)
    {
        Serial.println(F("Result: PASS. The joystick is ready for L298N Setup."));
        Serial.println(F("map() for this joystick (output -100 to 100):"));
        printMapCalls(axisA0);
        printMapCalls(axisA1);
    }
    else
    {
        if (extraPresses > 0)
            Serial.println(F("Presses were counted: check the pull up resistor on D2."));
        Serial.println(F("Result: FAIL. See the notes above printReport() in"));
        Serial.println(F("src/Step1_Joystick/main.cpp, then run the test again."));
    }
}

// ---------------------------------------------------------------
// The five tests, in the order they run. Each prints its instruction,
// waits for Enter, measures, and prints its result.
// ---------------------------------------------------------------

// Test 1: the button must be ON while held (momentary mode)
void testPress()
{
    printDots();
    Serial.println(F("Test 1 of 5: Press the push button and hold it. The LED turns on."));
    Serial.println(F("  While holding it, press Enter with the other hand."));
    waitForEnter(Wait::Button);
    passed[0] = button.isButtonOn();
    Serial.print(button.isButtonOn() ? F("  SW: ON  ") : F("  SW: OFF  "));
    printPass(passed[0]);
}

// Test 2: the button must be OFF after the release
void testRelease()
{
    printDots();
    Serial.println(F("Test 2 of 5: Release the push button. The LED turns off."));
    waitForEnter(Wait::Button);
    // A release after a failed press proves nothing
    passed[1] = passed[0] && !button.isButtonOn();
    Serial.print(button.isButtonOn() ? F("  SW: ON  ") : F("  SW: OFF  "));
    printPass(passed[1]);
    button.wasPressed(); // clear the press of Test 1
}

// Test 3: the average reading at rest is the center
void testCenter()
{
    printDots();
    Serial.println(F("Test 3 of 5: Leave the grip at rest. Do not touch the joystick."));
    waitForEnter(Wait::Count);
    axisA0.center = axisA0.readAverage();
    axisA1.center = axisA1.readAverage();
    // Test 4 starts its search for the ends from the center
    axisA0.low = axisA0.high = axisA0.center;
    axisA1.low = axisA1.high = axisA1.center;

    // abs() of Arduino is a macro that evaluates its argument twice,
    // so the offsets are stored first
    int offsetA0 = axisA0.center - ADC_MIDDLE;
    int offsetA1 = axisA1.center - ADC_MIDDLE;
    passed[2] = abs(offsetA0) <= CENTER_TOLERANCE &&
                abs(offsetA1) <= CENTER_TOLERANCE;
    printAxisReadings(axisA0.center, axisA1.center);
    printPass(passed[2]);
}

// Test 4: the ends are recorded until Enter is pressed
void testMove()
{
    printDots();
    Serial.println(F("Test 4 of 5: Move the grip slowly to every edge,"));
    Serial.println(F("  around the full circle, two times. Then press Enter."));
    timerSample.resetTimer();
    waitForEnter(Wait::Record);
    passed[3] = axisA0.travelPassed() && axisA1.travelPassed();
    Serial.print(F("  low and high, A0: "));
    Serial.print(axisA0.low);
    Serial.print(F(" "));
    Serial.print(axisA0.high);
    Serial.print(F("  A1: "));
    Serial.print(axisA1.low);
    Serial.print(F(" "));
    Serial.print(axisA1.high);
    Serial.print(F("  "));
    printPass(passed[3]);
}

// Test 5: the released grip must return to the center
void testReturn()
{
    printDots();
    Serial.println(F("Test 5 of 5: Release the grip. Let it return to center."));
    waitForEnter(Wait::Count);
    axisA0.rest = axisA0.readAverage();
    axisA1.rest = axisA1.readAverage();
    // A return after a failed Test 4 proves nothing: an axis that
    // never moved is always back at its center
    int returnA0 = axisA0.rest - axisA0.center;
    int returnA1 = axisA1.rest - axisA1.center;
    passed[4] = passed[3] &&
                abs(returnA0) <= RETURN_TOLERANCE &&
                abs(returnA1) <= RETURN_TOLERANCE;
    printAxisReadings(axisA0.rest, axisA1.rest);
    printPass(passed[4]);
}

// The five tests and the report
void runSelfTest()
{
    extraPresses = 0;
    printDots();
    Serial.println(F("Joystick Self Test (Step1_Joystick)"));
    Serial.println(F("Follow each instruction, then press Enter."));
    testPress();
    testRelease();
    testCenter();
    testMove();
    testReturn();
    printReport();
}

// ---------------------------------------------------------------
// After the report
// ---------------------------------------------------------------

// A0 and A1, raw (mapped), and SW, four times a second for LIVE_MS.
// An axis that failed Test 4 is printed raw only, because its map()
// has no measured ends.
void printLiveValues()
{
    printDots();
    Serial.println(F("Live values: A0 and A1, raw (mapped), and SW,"));
    Serial.println(F("four times a second for 20 seconds."));
    timerPrint.resetTimer();
    timerLive.resetTimer();
    timerPrint.isTimer(PRINT_MS); // arm both timers
    timerLive.isTimer(LIVE_MS);
    while (!timerLive.isTimer(LIVE_MS))
    {
        button.updateButton();
        if (timerPrint.isTimer(PRINT_MS))
        {
            // Columns of fixed width (v6.3.0): raw 4 characters,
            // mapped 4 characters inside the parentheses
            int rawA0 = analogRead(axisA0.pin);
            int rawA1 = analogRead(axisA1.pin);
            Serial.print(F("A0: "));
            printColumn(rawA0, 4);
            if (axisA0.travelPassed())
            {
                Serial.print(F(" ("));
                printColumn(axisA0.mapped(rawA0), 4);
                Serial.print(F(")"));
            }
            else
                Serial.print(F("       ")); // keeps A1 in its column
            Serial.print(F("  A1: "));
            printColumn(rawA1, 4);
            if (axisA1.travelPassed())
            {
                Serial.print(F(" ("));
                printColumn(axisA1.mapped(rawA1), 4);
                Serial.print(F(")"));
            }
            else
                Serial.print(F("       "));
            Serial.println(button.isButtonOn() ? F("  SW: ON") : F("  SW: OFF"));
        }
    }
    // Keys typed during the live values are discarded
    while (readChar() >= 0)
    {
    }
    lastWasCR = false;
}

// Asks until r or v is typed; returns the letter
char askNext()
{
    printDots();
    while (true)
    {
        Serial.print(F("Type r to run the self test again, or v to view the live values (20 s): "));
        char c = readLetter('r', 'v');
        if (c)
            return c;
        Serial.println(F("  Type r or v."));
    }
}

void setup()
{
    Serial.begin(9600);
    while (!Serial) { }

    // Button class: SW on D2, indicator LED on D12
    int buttonPin = 2; // UNO D2 (CHIP-PD2), joystick SW
    int ledPin = 12;   // UNO D12 (CHIP-PB4), indicator LED
    button = Button(buttonPin, ledPin);
    // -----------------------------------------------------------
    // setLatching() selects how isButtonOn() and the LED follow the
    // button (Button.h):
    //   setLatching(true)   Latching mode, the default of the class.
    //                       Each press toggles ON and OFF, like a
    //                       push on, push off power switch.
    //   setLatching(false)  Momentary mode. ON only while the button
    //                       is held down; OFF on release.
    // This program uses momentary mode: Test 1 must see the press and
    // Test 2 the release. In latching mode the release changes
    // nothing, so a release could not be tested, and the LED would
    // stay on after the finger is lifted. Step2_JUL uses latching
    // mode instead (see its setup()).
    // -----------------------------------------------------------
    button.setLatching(false);
    button.begin();            // D2 as INPUT_PULLUP, LED as OUTPUT
    pinMode(buttonPin, INPUT); // internal pull up off: external 10 kOhm
    // Internal pull up instead: comment out the line above.

    // L298N pins D5 to D10: outputs, LOW (enable inputs held LOW)
    for (int pin = 5; pin <= 10; pin++)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }

    // Joystick axes
    axisA0 = Axis{A0, F("A0"), 0, 0, 0, 0}; // joystick VRx
    axisA1 = Axis{A1, F("A1"), 0, 0, 0, 0}; // joystick VRy

    // Timer class: the timers arm on their first isTimer() call
    timerSample = Timer();
    timerPrint = Timer();
    timerLive = Timer();
    timerStart = Timer();

    // v6.3.0: Test 1 starts only after Enter (see waitForStart())
    waitForStart();
    runSelfTest();
}

void loop()
{
    if (askNext() == 'r')
        runSelfTest();
    else
        printLiveValues();
}
