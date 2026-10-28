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
// RELEASE
//   2026-10-28  v6.8.0
//   Step1_Joystick/main.cpp last changed: 2026-10-28  v6.8.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//
// ---------------------------------------------------------------
// Step1_Joystick, the joystick self test
// (Article 1009, Step1, The Joystick Self Test)
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
// The report gives PASS or FAIL for each test and the measured
// values. After a pass it prints a new include/JoystickCenter.h, the
// center of each axis, to be copied into the project (see the end of
// printReport()). A press of the button during Tests 3 to 5 also
// fails the self test (a floating D2). Which way A0 and A1 count does
// not matter; the Bits() value of L298N Setup corrects the
// orientation. After the report the program asks:
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
// Revised 20261025 (v6.4.0): the joystick center. Test 3 passes a
// center within 100 counts of 511 (25 up to v6.3.1), because
// Step4_Generated now moves each reading by the measured center
// (Step2_JUL keeps 511). After a pass the report prints
// include/JoystickCenter.h for Step3_Generator, in place of the map()
// calls of v6.0.0 to v6.3.1; the live values show each reading's
// offset from the measured center in place of the mapped value.
// Revised 20261025 (v6.5.0): Test 3 fails a center more than 50
// counts from 511 (100 in v6.4.0 and v6.4.1), and a center more than
// 25 counts from 511 passes with a warning that a new joystick is
// recommended (author decision).
// Revised 20261028 (v6.8.0): after a pass the Self Test Report is
// written into the printed include/JoystickCenter.h, under SELF TEST
// REPORT, so it no longer scrolls away above the file; the monitor
// shows the result, the centers, and the copy instructions. After a
// failure the report prints in the monitor, as before.
// ---------------------------------------------------------------
#include <Arduino.h>
#include "Button.h"
#include "Timer.h"
// the center now in the project (v6.4.0)
#include "JoystickCenter.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// ---------------------------------------------------------------
// Self test limits, in ADC counts. analogRead() returns 0 to 1023;
// the middle of that range is 511. A real joystick seldom rests at
// exactly 511 or reaches 0 and 1023 at its ends, so the self test
// measures both instead of assuming them.
//   ADC_MIDDLE               511, the middle of 0 to 1023.
//   CENTER_TOLERANCE         Test 3 fails a rest reading farther
//                            than this many counts from ADC_MIDDLE
//                            (50 since v6.5.0; 100 in v6.4.0 and
//                            v6.4.1; 25 up to v6.3.1). A center near
//                            0 or 1023 is a wiring fault.
//   CENTER_WARNING           Test 3 passes a rest reading farther
//                            than this many counts from ADC_MIDDLE
//                            with a warning: a new joystick is
//                            recommended (v6.5.0). The dead zone of
//                            Step2_JUL, X_OFFSET 0.05 of 511 counts,
//                            is about 25 counts, and Step2_JUL keeps
//                            the center 511, so beyond 25 counts its
//                            motors may turn slowly with the grip
//                            released. Step4_Generated moves each
//                            reading by the measured center
//                            (include/JoystickCenter.h), so a resting
//                            grip maps to 0 there.
//   MIN_TRAVEL               Each direction must reach this many
//                            counts from the center.
//   RETURN_TOLERANCE         The released grip must come back within
//                            this many counts of the center. The dead
//                            zone of Step2_JUL, X_OFFSET 0.05 of 511
//                            counts (about 25), covers this spread; a
//                            larger one would leave the motors turning
//                            with the grip released.
// ---------------------------------------------------------------
const int ADC_MIDDLE = 511;
// Test 3 FAIL above this (v6.5.0)
const int CENTER_TOLERANCE = 50;
// Test 3 PASS with a warning above this (v6.5.0)
const int CENTER_WARNING = 25;
const int MIN_TRAVEL = 200;
const int RETURN_TOLERANCE = 25;

// Test 4: 50 samples/s
const unsigned long SAMPLE_MS = 20;
// live values: 4 times/s
const unsigned long PRINT_MS = 250;
// live values: 20 seconds
const unsigned long LIVE_MS = 20000;

// One joystick axis: its pin and the values the self test measures.
struct Axis
{
    uint8_t pin;
    const __FlashStringHelper *name;
    // Test 3: rest reading
    int center;
    // Test 4: lowest reading
    int low;
    // Test 4: highest reading
    int high;
    // Test 5: reading after the release
    int rest;

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
};

// What the program does while it waits for Enter
enum class Wait
{
    // Tests 1 and 2: the button only (debounce and LED)
    Button,
    // Tests 3 and 5: also count the presses of the button
    Count,
    // Test 4: also count presses and record the ends
    Record,
};

// push button (SW) and indicator LED
Button button;
// paces the readings of Test 4
Timer timerSample;
// paces the live values
Timer timerPrint;
// length of the live values
Timer timerLive;
// repeats the start question
Timer timerStart;
// joystick VRx on A0
Axis axisA0;
// joystick VRy on A1
Axis axisA1;
// result of Tests 1 to 5
bool passed[5];
// presses during Tests 3 to 5 (0 expected)
int extraPresses;

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
        // Backspace or Delete
        if (c == 8 || c == 127)
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
// the simulation supplies its answers in order
#ifndef TEST_INPUT
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
    // arm the timer
    timerStart.isTimer(3000);
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
    // v6.3.0: nothing typed ahead counts
    discardInput();
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

void printResult(const __FlashStringHelper *prefix, int number,
                 const __FlashStringHelper *label)
{
    Serial.print(prefix);
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
    // the minus sign counts
    uint8_t digits = (value < 0) ? 2 : 1;
    for (long v = (value < 0) ? -value : value; v >= 10; v /= 10)
        digits++;
    for (uint8_t i = digits; i < width; i++)
        Serial.print(' ');
    Serial.print(value);
}

// Width of each column of the report, in characters
const uint8_t COLUMN = 8;

void printAxisRow(const __FlashStringHelper *prefix, const Axis &axis)
{
    Serial.print(prefix);
    Serial.print(axis.name);
    Serial.print(F(": "));
    printColumn(axis.low, COLUMN);
    printColumn(axis.center, COLUMN);
    printColumn(axis.high, COLUMN);
    printColumn(axis.rest, COLUMN);
    Serial.println();
}

// A signed number with its sign, for example +12, -7, or 0
void printSigned(int value)
{
    if (value > 0)
        Serial.print('+');
    Serial.print(value);
}

// The center of one axis and its offset from 511
void printCenterLine(const __FlashStringHelper *prefix,
                     const __FlashStringHelper *name, int center)
{
    Serial.print(prefix);
    Serial.print(F("  "));
    Serial.print(name);
    Serial.print(F(" center "));
    Serial.print(center);
    Serial.print(F(" (offset "));
    printSigned(center - ADC_MIDDLE);
    Serial.println(F(")"));
}

// v6.5.0: true when a measured center lies more than CENTER_WARNING
// counts from 511 (Test 3 PASS with a warning)
bool centerWarning()
{
    // abs() of Arduino is a macro, so the offsets are stored first
    int offsetA0 = axisA0.center - ADC_MIDDLE;
    int offsetA1 = axisA1.center - ADC_MIDDLE;
    return abs(offsetA0) > CENTER_WARNING || abs(offsetA1) > CENTER_WARNING;
}

// true when every test passed and no press was counted during Tests
// 3 to 5 (v6.2.1)
bool allPassed()
{
    bool all = extraPresses == 0;
    for (int i = 0; i < 5; i++)
        all = all && passed[i];
    return all;
}

// The lines of the Self Test Report (v6.8.0). prefix starts each line:
// nothing in the serial monitor, "// " inside the printed
// include/JoystickCenter.h, where the report becomes comments.
void printReportLines(const __FlashStringHelper *prefix)
{
    Serial.print(prefix);
    // "Axis" and each heading fill the width of the columns below
    Serial.println(F("Axis     low  center    high    rest"));
    printAxisRow(prefix, axisA0);
    printAxisRow(prefix, axisA1);
    printResult(prefix, 1, F("Button press                 "));
    printResult(prefix, 2, F("Button release               "));
    printResult(prefix, 3, F("Center (511, within 50)      "));
    printResult(prefix, 4, F("Ends (200 counts each way)   "));
    printResult(prefix, 5, F("Return (within 25 of center) "));
    Serial.print(prefix);
    Serial.print(F("Presses during Tests 3 to 5: "));
    Serial.print(extraPresses);
    Serial.println(F(" (0 expected)"));
    Serial.print(prefix);
    Serial.println(allPassed() ? F("Result: PASS") : F("Result: FAIL"));
    // v6.5.0: a center more than 25 counts from 511 passes with a warning
    if (allPassed() && centerWarning())
    {
        Serial.print(prefix);
        Serial.println(F( \
            "WARNING: a center lies more than 25 counts from 511."));
        Serial.print(prefix);
        Serial.println(F( \
            "A new joystick is recommended. Step4_Generated corrects"));
        Serial.print(prefix);
        Serial.println(F( \
            "the center; Step2_JUL does not, so its motors may turn"));
        Serial.print(prefix);
        Serial.println(F( \
            "slowly with the grip released (push button OFF stops them)."));
    }
    Serial.print(prefix);
    Serial.println(F("Joystick center measured by Test 3:"));
    printCenterLine(prefix, F("A0"), axisA0.center);
    printCenterLine(prefix, F("A1"), axisA1.center);
}

// ---------------------------------------------------------------
// The joystick center file (v6.4.0)
// After a pass, the report prints a complete include/JoystickCenter.h,
// with the same comments as the shipped file (v6.5.0),
// between two marker lines; since v6.8.0 it also holds the Self Test
// Report under SELF TEST REPORT. Copy every line between the markers and
// replace the whole file with them; the PlatformIO monitor also saves
// the output in a log file (monitor_filters = log2file), so the lines
// can be copied from that file. Step3_Generator writes its values into
// Step4_Generated. Step2_JUL does not use the file; it keeps the
// center 511. Run this self test again after the joystick is
// exchanged, and copy the new file.
// ---------------------------------------------------------------
void printCenterFile()
{
    Serial.println(F("// ----- BEGIN JoystickCenter.h -----"));
    Serial.println(F("//"));
    Serial.println(F("// Carpenter Software"));
    Serial.println(F("// File: JoystickCenter.h"));
    Serial.println(F("// Github: MageMCU"));
    Serial.println(F("// Repository: Joystick-Uno-L298N"));
    Serial.println(F("// Folder: Code-JUL"));
    Serial.println(F("//"));
    Serial.println(F("// By Jesse Carpenter (carpentersoftware.com)"));
    Serial.println(F("//"));
    Serial.println(F("// MIT LICENSE"));
    Serial.println(F("//"));
    Serial.println(F("// RELEASE"));
    Serial.println(F("//   2026-10-28  v6.8.0"));
    Serial.println(F("//   JoystickCenter.h printed by Step1_Joystick"));
    Serial.println(F( \
        "//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)"));
    Serial.println(F("//"));
    Serial.println(F("// The joystick center (added 20261025, v6.4.0)"));
    Serial.println(F("//"));
    Serial.println(F("// WHY THIS FILE WAS ADDED"));
    Serial.println(F( \
        "// A thumb joystick seldom rests at exactly 511, the middle of the"));
    Serial.println(F( \
        "// ADC range 0 to 1023. The rest reading of an axis is called its"));
    Serial.println(F( \
        "// center. When the center differs from 511, a released grip reads"));
    Serial.println(F( \
        "// as a small push in one direction, and the dead zone must be made"));
    Serial.println(F( \
        "// wider to hide it. The bench test of v6.3.1.a showed this: an old"));
    Serial.println(F( \
        "// joystick failed Step1_Joystick Test 3 with its x center more " \
        "than"));
    Serial.println(F( \
        "// 25 counts from 511. This file keeps the measured center of each"));
    Serial.println(F( \
        "// axis in one place, so each program reads the same two values and"));
    Serial.println(F("// a resting grip maps to 0."));
    Serial.println(F("//"));
    Serial.println(F("// WHERE IT IS USED"));
    Serial.println(F( \
        "//   Step1_Joystick     Includes it to show the center now in the"));
    Serial.println(F( \
        "//                      project. Test 3 measures the center; " \
        "after a"));
    Serial.println(F( \
        "//                      passing self test the report prints a " \
        "new copy"));
    Serial.println(F("//                      of this file."));
    Serial.println(F( \
        "//   Step3_Generator    Check 1 shows these two values for the " \
        "student"));
    Serial.println(F( \
        "//                      to confirm, rejects a value outside 461 " \
        "to 561"));
    Serial.println(F( \
        "//                      at compile time (#error), and writes " \
        "them into"));
    Serial.println(F( \
        "//                      Step4_Generated as X_CENTER and Y_CENTER."));
    Serial.println(F( \
        "//   Step4_Generated    Does not include this file. It holds the " \
        "copied"));
    Serial.println(F( \
        "//                      values, which claude/ace.h uses to move " \
        "each"));
    Serial.println(F( \
        "//                      reading by its offset from 511."));
    Serial.println(F( \
        "//   Lesson 17          DeadZone: prints the centers and " \
        "suggests the"));
    Serial.println(F( \
        "//                      dead zone offset about each center " \
        "(v6.4.1)."));
    Serial.println(F( \
        "//   Lesson 20          JoystickMap: the center of each two " \
        "segment map"));
    Serial.println(F("//                      (v6.4.1)."));
    Serial.println(F( \
        "//   Step2_JUL          Does not use it; it keeps the center 511"));
    Serial.println(F("//                      (author decision, v6.4.0)."));
    Serial.println(F("//"));
    Serial.println(F("// HOW TO UPDATE IT"));
    Serial.println(F( \
        "// Shipped with 511 and 511, which leave every reading unchanged."));
    Serial.println(F( \
        "// After a passing self test, replace the whole file with the lines"));
    Serial.println(F( \
        "// Step1_Joystick prints between its two marker lines. Then run"));
    Serial.println(F( \
        "// Step3_Generator again so Step4_Generated receives the new " \
        "values."));
    Serial.println(F( \
        "// Allowed range: 461 to 561 (Step1_Joystick, Test 3 fails a center"));
    Serial.println(F( \
        "// more than 50 counts from 511 and warns above 25 counts: a new"));
    Serial.println(F("// joystick is recommended; v6.5.0)."));
    Serial.println(F("//"));
    Serial.println(F("// SELF TEST REPORT"));
    printReportLines(F("// "));
    Serial.println(F("//"));
    Serial.println();
    Serial.println(F("#ifndef JoystickCenter_h"));
    Serial.println(F("#define JoystickCenter_h"));
    Serial.println();
    Serial.print(F("#define JOYSTICK_A0_CENTER "));
    Serial.println(axisA0.center);
    Serial.print(F("#define JOYSTICK_A1_CENTER "));
    Serial.println(axisA1.center);
    Serial.println();
    Serial.println(F("#endif"));
    Serial.println(F("// ----- END JoystickCenter.h -----"));
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
//           between those, but more than 50 counts from 511: the
//           module rests too far off center; exchange the joystick.
//           A PASS with a center more than 25 counts from 511 prints
//           a warning: a new joystick is recommended (v6.5.0).
//   Test 4  One direction short of MIN_TRAVEL: check that wire, and
//           move the grip all the way to the edge.
//   Test 5  The grip does not come back to center: try another
//           module, or enlarge the dead zone of Step2_JUL (X_OFFSET
//           and Y_OFFSET).
//   Presses during Tests 3 to 5: a floating D2 gives presses that no
//           one made. Any press fails the self test (v6.2.1). Check the
//           pull up resistor on D2.
// Joystick modules are not all built the same way.
// ---------------------------------------------------------------
void printReport()
{
    printDots();
    if (!allPassed())
    {
        Serial.println(F("Self Test Report"));
        printReportLines(F(""));
        if (extraPresses > 0)
            Serial.println(F( \
                "Presses were counted: check the pull up resistor on D2."));
        Serial.println(F("See the notes above printReport() in"));
        Serial.println(F( \
            "src/Step1_Joystick/main.cpp, then run the test again."));
        return;
    }
    // v6.8.0: after a pass the report is written into the printed file
    Serial.println(F( \
        "Result: PASS. The joystick is ready for L298N Setup."));
    if (centerWarning())
        Serial.println(F( \
            "WARNING: a center lies more than 25 counts from 511."));
    Serial.println(F("Joystick center measured by Test 3:"));
    printCenterLine(F(""), F("A0"), axisA0.center);
    printCenterLine(F(""), F("A1"), axisA1.center);
    Serial.println(F("Joystick center now in include/JoystickCenter.h:"));
    printCenterLine(F(""), F("A0"), JOYSTICK_A0_CENTER);
    printCenterLine(F(""), F("A1"), JOYSTICK_A1_CENTER);
    if (axisA0.center == JOYSTICK_A0_CENTER &&
        axisA1.center == JOYSTICK_A1_CENTER)
        Serial.println(F("They match; the file needs no change."));
    Serial.println(F( \
        "The Self Test Report is written into the file below, under"));
    Serial.println(F("SELF TEST REPORT."));
    printDots();
    Serial.println(F( \
        "Copy every line between the two marker lines and replace"));
    Serial.println(F( \
        "all of include/JoystickCenter.h with them (Step3_Generator"));
    Serial.println(F("uses the file). The PlatformIO monitor also"));
    Serial.println(F("saves this output in a log file (log2file)."));
    Serial.println();
    printCenterFile();
}

// ---------------------------------------------------------------
// The five tests, in the order they run. Each prints its instruction,
// waits for Enter, measures, and prints its result.
// ---------------------------------------------------------------

// Test 1: the button must be ON while held (momentary mode)
void testPress()
{
    printDots();
    Serial.println(F( \
        "Test 1 of 5: Press the push button and hold it. The LED turns on."));
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
    Serial.println(F( \
        "Test 2 of 5: Release the push button. The LED turns off."));
    waitForEnter(Wait::Button);
    // A release after a failed press proves nothing
    passed[1] = passed[0] && !button.isButtonOn();
    Serial.print(button.isButtonOn() ? F("  SW: ON  ") : F("  SW: OFF  "));
    printPass(passed[1]);
    // clear the press of Test 1
    button.wasPressed();
}

// Test 3: the average reading at rest is the center
void testCenter()
{
    printDots();
    Serial.println(F( \
        "Test 3 of 5: Leave the grip at rest. Do not touch the joystick."));
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
    // v6.5.0: a center more than 25 counts from 511 passes with a warning
    if (passed[2] && centerWarning())
        Serial.println(F( \
            "  WARNING: more than 25 counts from 511; a new joystick is " \
            "recommended."));
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
    Serial.println(F( \
        "Test 5 of 5: Release the grip. Let it return to center."));
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

// A0 and A1, raw (offset from the measured center), and SW, four
// times a second for LIVE_MS. At rest both offsets stay near 0.
void printLiveValues()
{
    printDots();
    Serial.println(F( \
        "Live values: A0 and A1, raw (offset from center), and SW,"));
    Serial.println(F("four times a second for 20 seconds."));
    timerPrint.resetTimer();
    timerLive.resetTimer();
    // arm both timers
    timerPrint.isTimer(PRINT_MS);
    timerLive.isTimer(LIVE_MS);
    while (!timerLive.isTimer(LIVE_MS))
    {
        button.updateButton();
        if (timerPrint.isTimer(PRINT_MS))
        {
            // Columns of fixed width (v6.3.0): raw 4 characters,
            // offset 5 characters inside the parentheses (v6.4.0)
            int rawA0 = analogRead(axisA0.pin);
            int rawA1 = analogRead(axisA1.pin);
            Serial.print(F("A0: "));
            printColumn(rawA0, 4);
            Serial.print(F(" ("));
            printColumn(rawA0 - axisA0.center, 5);
            Serial.print(F(")"));
            Serial.print(F("  A1: "));
            printColumn(rawA1, 4);
            Serial.print(F(" ("));
            printColumn(rawA1 - axisA1.center, 5);
            Serial.print(F(")"));
            Serial.println(button.isButtonOn() ? F("  SW: ON")
                                               : F("  SW: OFF"));
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
        Serial.print(F( \
            "Type r to run the self test again, or v to view the live " \
            "values (20 s): "));
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
    // v6.4.1: program title
    Serial.println(F( \
        "\n................................................" \
        "\nStep1_Joystick: the joystick self test" \
        "\nSelected in platformio.ini: +<Step1_Joystick/>"));
    // Button class: SW on D2, indicator LED on D12
    // UNO D2 (CHIP-PD2), joystick SW
    int buttonPin = 2;
    // UNO D12 (CHIP-PB4), indicator LED
    int ledPin = 12;
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
    // D2 as INPUT_PULLUP, LED as OUTPUT
    button.begin();
    // internal pull up off: external 10 kOhm
    pinMode(buttonPin, INPUT);
    // Internal pull up instead: comment out the line above.

    // L298N pins D5 to D10: outputs, LOW (enable inputs held LOW)
    for (int pin = 5; pin <= 10; pin++)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }

    // Joystick axes
    // joystick VRx
    axisA0 = Axis{A0, F("A0"), 0, 0, 0, 0};
    // joystick VRy
    axisA1 = Axis{A1, F("A1"), 0, 0, 0, 0};

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
