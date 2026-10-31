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
//   2026-10-30  v7.3.0
//   Step1_Joystick/main.cpp last changed: 2026-10-30  v7.3.0
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
//   Test 3  Leave the grip at rest       (CENTER: the center)
//   Test 4  Hold UP, DOWN, LEFT, RIGHT   (first entry: the ends)
//   Test 5  Move the grip in a circle,   (second entry: verifies
//           slowly, two times             the ends)
//   Test 6  Release the grip             (Return)
// The report prints the blocks of the bench test check list in the
// same lines: a heading, the equations with the names of its key
// (A0C, A0CO, A0O, A0L, A0H, A0SL, A0SH, A0HD, A0LD, and the same for
// A1), then the values in a table, raw first, then calculated; a star
// marks each line of values for the check list. After a pass it
// prints a new include/JoystickMeasurements.h, the low end, center,
// and high end of each axis, to be copied into the project (see the
// end of printReport()). A press of the button during Tests 3 to 6 also
// fails the self test (a floating D2). Which way A0 and A1 count
// does not matter; the Bits() value of L298N Setup corrects the
// orientation. After the report the program asks:
//   r  run the self test again
//   v  view the live values of A0, A1, and SW four times a second
//      for 20 seconds: raw, offset from the measured center, and the
//      calculated N of THE JOYSTICK EQUATIONS (v7.0.0); then the
//      question is asked again
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
// Revised 20261028 (v7.0.0): requested by the author. The printed
// file is include/JoystickMeasurements.h (in place of
// include/JoystickCenter.h) with the low end, center, and high end
// of each axis, the three points of THE JOYSTICK EQUATIONS of
// include/claude/ace.h. The report compares all six values with the
// file now in the project. The live values add the calculated N
// (-1023 to 1023) from the values in that file, with the dead zone
// and inset of Step4_Generated (25 and 10 counts).
// Revised 20261028 (v7.1.0): requested by the author; the bench test
// check list leads. The tests follow its order: Test 4, the first
// entry, holds the grip UP, DOWN, LEFT, and RIGHT (each an average of
// 16 readings); the smallest and the largest held reading of each
// axis are its low end and high end, written into the file. Test 5,
// the second entry, moves the grip in a circle twice and verifies
// those ends: the circle end minus the held reading nearest to it
// (A0HD, A0LD, A1HD, A1LD), with the direction named, so each number
// can be matched by eye. Return is Test 6. The file matches when the
// centers lie within 1 count and each end within 10 counts.
// Revised 20261029 (v7.2.0): requested by the author after his bench
// test of v7.1.0; the check list and the report share one format.
// Each block (CENTER, FIRST ENTRY, ENDS, SECOND ENTRY, VERIFICATION,
// RETURN, RESULTS) prints its equations once, with names only, then
// its values in a table, raw columns first, each value under the
// first character of its column name. A star marks the lines with
// values for the check list. The directions of the held ends are in
// the ENDS table; RESULTS gives the result and the warning of each
// test in a table. The tests and the calculations are unchanged.
// ---------------------------------------------------------------
#include <Arduino.h>
#include "Button.h"
#include "Timer.h"
// the measurements now in the project (v7.0.0)
#include "JoystickMeasurements.h"

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
//                            released. Step4_Generated corrects each
//                            reading with the measured center
//                            (include/JoystickMeasurements.h), so a
//                            resting grip gives 0 there.
//   MIN_TRAVEL               Each direction must reach this many
//                            counts from the center: the held
//                            readings of Test 4 and the circle of
//                            Test 5.
//   CROSS_WARNING            Test 4: while one axis is held at an
//                            edge, the other axis lying farther than
//                            this from its center prints a warning
//                            (v7.1.0).
//   VERIFY_LOW, VERIFY_HIGH  Test 5: an end difference outside this
//                            range prints a warning (v7.1.0). The
//                            circle keeps its single extreme reading,
//                            so it reaches a few counts past the held
//                            average; a negative value means the held
//                            push went past the circle.
//   CENTER_MATCH             The report compares the measured values
//                            with the file now in the project: the
//                            centers match within this many counts,
//                            the ends within INSET (v7.1.0).
//   RETURN_TOLERANCE         The released grip must come back within
//                            this many counts of the center. The dead
//                            zone of Step2_JUL, X_OFFSET 0.05 of 511
//                            counts (about 25), and DEAD_ZONE of
//                            Step4_Generated (25 counts, v7.0.0) cover
//                            this spread; a larger one would leave the
//                            motors turning with the grip released.
//   DEAD_ZONE, INSET         The dead zone and the inset of the ends
//                            in THE JOYSTICK EQUATIONS of ace.h, used
//                            for the calculated N of the live values
//                            (v7.0.0).
// ---------------------------------------------------------------
const int ADC_MIDDLE = 511;
// Test 3 FAIL above this (v6.5.0)
const int CENTER_TOLERANCE = 50;
// Test 3 PASS with a warning above this (v6.5.0)
const int CENTER_WARNING = 25;
const int MIN_TRAVEL = 200;
const int RETURN_TOLERANCE = 25;
// the same values as Step4_Generated and ace.h (v7.0.0)
const int DEAD_ZONE = 25;
const int INSET = 10;
// v7.1.0
const int CROSS_WARNING = 25;
const int VERIFY_LOW = -5;
const int VERIFY_HIGH = 10;
const int CENTER_MATCH = 1;

// Test 4: 50 samples/s
const unsigned long SAMPLE_MS = 20;
// live values: 4 times/s
const unsigned long PRINT_MS = 250;
// live values: 20 seconds
const unsigned long LIVE_MS = 20000;

// The four directions of Test 4, in the order of the check list
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

// One joystick axis: its pin and the values the self test measures.
struct Axis
{
    uint8_t pin;
    const __FlashStringHelper *name;
    // Test 3: rest reading
    int center;
    // Test 4: held reading of UP, DOWN, LEFT, and RIGHT
    int held[4];
    // Test 4: smallest held reading, and its direction
    int low;
    int lowDir;
    // Test 4: largest held reading, and its direction
    int high;
    int highDir;
    // Test 5: lowest and highest reading of the circle
    int circleLow;
    int circleHigh;
    // Test 6: reading after the release
    int rest;

    // Average of 16 readings, which smooths the ADC noise
    int readAverage() const
    {
        long sum = 0;
        for (int i = 0; i < 16; i++)
            sum += analogRead(pin);
        return (int)(sum / 16);
    }

    // Test 4: the ends are the smallest and largest held reading
    void findEnds()
    {
        low = held[0];
        high = held[0];
        lowDir = 0;
        highDir = 0;
        for (int d = 1; d < 4; d++)
        {
            if (held[d] < low)
            {
                low = held[d];
                lowDir = d;
            }
            if (held[d] > high)
            {
                high = held[d];
                highDir = d;
            }
        }
    }

    // Test 4: both held ends reach MIN_TRAVEL from the center
    bool travelPassed() const
    {
        return (center - low) >= MIN_TRAVEL &&
               (high - center) >= MIN_TRAVEL;
    }

    // Test 5: both circle ends reach MIN_TRAVEL from the center
    bool circlePassed() const
    {
        return (center - circleLow) >= MIN_TRAVEL &&
               (circleHigh - center) >= MIN_TRAVEL;
    }

    // Test 5: A0HD, the circle high end minus the held high end
    int highDifference() const
    {
        return circleHigh - high;
    }

    // Test 5: A0LD, the held low end minus the circle low end
    int lowDifference() const
    {
        return low - circleLow;
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
// result of Tests 1 to 6 (v7.1.0)
bool passed[6];
// presses during Tests 3 to 6 (0 expected)
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

// Test 5: track the lowest and highest reading of one axis
void recordEnds(Axis &axis)
{
    int raw = analogRead(axis.pin);
    if (raw < axis.circleLow)
        axis.circleLow = raw;
    if (raw > axis.circleHigh)
        axis.circleHigh = raw;
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

// v7.1.0: the name of a direction of Test 4
const __FlashStringHelper *directionName(int d)
{
    if (d == UP)
        return F("UP");
    if (d == DOWN)
        return F("DOWN");
    if (d == LEFT)
        return F("LEFT");
    return F("RIGHT");
}

// v7.1.0: the edge the grip is held at for a direction
const __FlashStringHelper *edgeName(int d)
{
    if (d == UP)
        return F("top");
    if (d == DOWN)
        return F("bottom");
    if (d == LEFT)
        return F("left");
    return F("right");
}

// ---------------------------------------------------------------
// v7.2.0: the report tables, the format of the bench test check list
// Each block has a heading, its equations (one per line, names only),
// a row of column names, and the rows of values. The raw columns come
// first, the calculated columns after them. A star in the equation
// column marks a line that holds values for the check list:
//   CENTER (Test 3, grip at rest)
//     A0CO = A0C - 511
//     A1CO = A1C - 511
//               A0C    A1C    A0CO   A1CO
//     *         511    498    0      -13
// Each value starts under the first character of its column name.
// The check list prints the same lines with blanks for the values.
// ---------------------------------------------------------------

// v7.2.0: the width of a column of values, and of the row name
const uint8_t COLUMN_WIDTH = 7;
const uint8_t ROW_NAME_WIDTH = 8;

// v7.2.0: the number of characters Serial.print() gives a number,
// the minus sign included
uint8_t numberWidth(long value)
{
    uint8_t digits = (value < 0) ? 2 : 1;
    for (long v = (value < 0) ? -value : value; v >= 10; v /= 10)
        digits++;
    return digits;
}

// v7.2.0: spaces from the given count up to the width
void printSpaces(uint8_t count, uint8_t width)
{
    for (uint8_t i = count; i < width; i++)
        Serial.print(' ');
}

// v7.2.0: a text left aligned in a column; width 0 for the last
// column of a row, so that no line ends with spaces
void printText(const __FlashStringHelper *text, uint8_t width)
{
    Serial.print(text);
    // strlen_P counts the characters of a string kept in flash
    printSpaces(strlen_P(reinterpret_cast<PGM_P>(text)), width);
}

// v7.2.0: a number left aligned in a column; width 0 for the last
// column of a row
void printNumber(long value, uint8_t width)
{
    Serial.print(value);
    printSpaces(numberWidth(value), width);
}

// v7.2.0: a heading, at the start of the line after the prefix
void printHeading(const __FlashStringHelper *prefix,
                  const __FlashStringHelper *heading)
{
    Serial.print(prefix);
    Serial.println(heading);
}

// v7.2.0: an equation, in the equation column
void printFormula(const __FlashStringHelper *prefix,
                  const __FlashStringHelper *formula)
{
    Serial.print(prefix);
    Serial.print(F("  "));
    Serial.println(formula);
}

// v7.2.0: an empty line between two blocks; "//" inside the printed
// file, an empty line in the serial monitor
void printBlank(const __FlashStringHelper *prefix)
{
    if (pgm_read_byte(reinterpret_cast<PGM_P>(prefix)) != '\0')
        Serial.print(F("//"));
    Serial.println();
}

// v7.2.0: the start of a row: the prefix, the star of a line with
// values for the check list (spaces on a row of column names), and
// the row name, or spaces when the row has none
void printRowStart(const __FlashStringHelper *prefix, bool star,
                   const __FlashStringHelper *name)
{
    Serial.print(prefix);
    Serial.print(star ? F("  * ") : F("    "));
    if (name)
        printText(name, ROW_NAME_WIDTH);
    else
        printSpaces(0, ROW_NAME_WIDTH);
}

// v7.2.0: a row of four texts: column names (no star), or the
// directions of the ENDS block (star)
void printTextRow(const __FlashStringHelper *prefix, bool star,
                  const __FlashStringHelper *name,
                  const __FlashStringHelper *a,
                  const __FlashStringHelper *b,
                  const __FlashStringHelper *c,
                  const __FlashStringHelper *d)
{
    printRowStart(prefix, star, name);
    printText(a, COLUMN_WIDTH);
    printText(b, COLUMN_WIDTH);
    printText(c, COLUMN_WIDTH);
    printText(d, 0);
    Serial.println();
}

// v7.2.0: a row of four values, marked with the star
void printValueRow(const __FlashStringHelper *prefix,
                   const __FlashStringHelper *name,
                   long a, long b, long c, long d)
{
    printRowStart(prefix, true, name);
    printNumber(a, COLUMN_WIDTH);
    printNumber(b, COLUMN_WIDTH);
    printNumber(c, COLUMN_WIDTH);
    printNumber(d, 0);
    Serial.println();
}

// v7.2.0: CENTER, Test 3
void printCenterBlock(const __FlashStringHelper *prefix)
{
    printHeading(prefix, F("CENTER (Test 3, grip at rest)"));
    printFormula(prefix, F("A0CO = A0C - 511"));
    printFormula(prefix, F("A1CO = A1C - 511"));
    printTextRow(prefix, false, nullptr, F("A0C"), F("A1C"), F("A0CO"),
                 F("A1CO"));
    printValueRow(prefix, nullptr, axisA0.center, axisA1.center,
                  axisA0.center - ADC_MIDDLE,
                  axisA1.center - ADC_MIDDLE);
}

// v7.2.0: the column names of the first entry
void printDirectionNames(const __FlashStringHelper *prefix)
{
    printTextRow(prefix, false, F("dir"), F("A0"), F("A1"), F("A0O"),
                 F("A1O"));
}

// v7.2.0: one direction of the first entry, A0, A1, A0O, A1O
void printDirectionRow(const __FlashStringHelper *prefix, int d)
{
    printValueRow(prefix, directionName(d), axisA0.held[d],
                  axisA1.held[d], axisA0.held[d] - axisA0.center,
                  axisA1.held[d] - axisA1.center);
}

// v7.2.0: FIRST ENTRY, Test 4, and the ENDS found from it
void printFirstEntryBlock(const __FlashStringHelper *prefix)
{
    printHeading(prefix, F("FIRST ENTRY (Test 4, grip held at each edge)"));
    printFormula(prefix, F("A0O = A0 - A0C"));
    printFormula(prefix, F("A1O = A1 - A1C"));
    printDirectionNames(prefix);
    for (int d = 0; d < 4; d++)
        printDirectionRow(prefix, d);
    printHeading(prefix, F("ENDS: the smallest and largest held reading"));
    printTextRow(prefix, false, F("end"), F("A0L"), F("A0H"), F("A1L"),
                 F("A1H"));
    printValueRow(prefix, F("value"), axisA0.low, axisA0.high, axisA1.low,
                  axisA1.high);
    printTextRow(prefix, true, F("dir"), directionName(axisA0.lowDir),
                 directionName(axisA0.highDir),
                 directionName(axisA1.lowDir),
                 directionName(axisA1.highDir));
}

// v7.2.0: SECOND ENTRY, Test 5, and the VERIFICATION of the ends
void printSecondEntryBlock(const __FlashStringHelper *prefix)
{
    printHeading(prefix, F("SECOND ENTRY (Test 5, circle twice)"));
    printTextRow(prefix, false, F("end"), F("A0SL"), F("A0SH"), F("A1SL"),
                 F("A1SH"));
    printValueRow(prefix, F("value"), axisA0.circleLow,
                  axisA0.circleHigh, axisA1.circleLow,
                  axisA1.circleHigh);
    printHeading(prefix, F("VERIFICATION: circle end and held end"));
    printFormula(prefix, F("A0HD = A0SH - A0H"));
    printFormula(prefix, F("A0LD = A0L - A0SL"));
    printFormula(prefix, F("A1HD = A1SH - A1H"));
    printFormula(prefix, F("A1LD = A1L - A1SL"));
    printTextRow(prefix, false, nullptr, F("A0HD"), F("A0LD"), F("A1HD"),
                 F("A1LD"));
    printValueRow(prefix, nullptr, axisA0.highDifference(),
                  axisA0.lowDifference(), axisA1.highDifference(),
                  axisA1.lowDifference());
}

// v7.2.0: RETURN, Test 6
void printReturnBlock(const __FlashStringHelper *prefix)
{
    printHeading(prefix, F("RETURN (Test 6, grip released)"));
    printFormula(prefix, F("A0O = A0 - A0C"));
    printFormula(prefix, F("A1O = A1 - A1C"));
    printTextRow(prefix, false, nullptr, F("A0"), F("A1"), F("A0O"),
                 F("A1O"));
    printValueRow(prefix, nullptr, axisA0.rest, axisA1.rest,
                  axisA0.rest - axisA0.center,
                  axisA1.rest - axisA1.center);
}

// v7.0.0: THE JOYSTICK EQUATIONS of include/claude/ace.h for one
// axis, a raw reading to N (-1023 to 1023). ace.h computes the same
// integer without a division; here the division is plain to read.
long calculatedN(int raw, int low, int center, int high)
{
    int start = center + DEAD_ZONE;
    int stop = center - DEAD_ZONE;
    if (raw > start)
    {
        long den = (high - INSET) - start;
        long dr = min((long)(raw - start), den);
        return 1023L * dr / den;
    }
    if (raw < stop)
    {
        long den = stop - (low + INSET);
        long dr = min((long)(stop - raw), den);
        return -(1023L * dr / den);
    }
    return 0;
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

// v7.1.0: true when, in a direction of Test 4, the axis that moved
// less lies more than CROSS_WARNING counts from its center
bool crossWarning()
{
    for (int d = 0; d < 4; d++)
    {
        int offsetA0 = axisA0.held[d] - axisA0.center;
        int offsetA1 = axisA1.held[d] - axisA1.center;
        int other = abs(offsetA0) < abs(offsetA1) ? offsetA0 : offsetA1;
        if (abs(other) > CROSS_WARNING)
            return true;
    }
    return false;
}

// v7.1.0: true when a difference lies outside VERIFY_LOW to VERIFY_HIGH
bool outsideVerify(int difference)
{
    return difference < VERIFY_LOW || difference > VERIFY_HIGH;
}

// v7.1.0: true when an end difference of Test 5 lies outside the range
bool verifyWarning()
{
    return outsideVerify(axisA0.highDifference()) ||
           outsideVerify(axisA0.lowDifference()) ||
           outsideVerify(axisA1.highDifference()) ||
           outsideVerify(axisA1.lowDifference());
}

// v7.0.0: one row of low end, center, and high end
void printEndsLine(const __FlashStringHelper *name, int low, int center,
                   int high)
{
    Serial.print(F("  "));
    Serial.print(name);
    Serial.print(F("                       "));
    printColumn(low, 4);
    printColumn(center, 8);
    printColumn(high, 8);
    Serial.println();
}

// v7.0.0: true when one measured value lies within the given number
// of counts of the value in the file
bool valueMatches(int measured, int inFile, int counts)
{
    int difference = measured - inFile;
    return abs(difference) <= counts;
}

// v7.0.0: true when one measured end lies within INSET counts of the
// end in the file
bool endMatches(int measured, int inFile)
{
    return valueMatches(measured, inFile, INSET);
}

// v7.1.0: true when the centers lie within CENTER_MATCH counts (equal
// up to v7.0.0) and every end within INSET counts
bool fileMatches()
{
    return valueMatches(axisA0.center, JOYSTICK_A0_CENTER,
                        CENTER_MATCH) &&
           valueMatches(axisA1.center, JOYSTICK_A1_CENTER,
                        CENTER_MATCH) &&
           endMatches(axisA0.low, JOYSTICK_A0_LOW) &&
           endMatches(axisA0.high, JOYSTICK_A0_HIGH) &&
           endMatches(axisA1.low, JOYSTICK_A1_LOW) &&
           endMatches(axisA1.high, JOYSTICK_A1_HIGH);
}

// true when every test passed and no press was counted during Tests
// 3 to 6 (v6.2.1; Tests 3 to 5 up to v7.0.0)
bool allPassed()
{
    bool all = extraPresses == 0;
    for (int i = 0; i < 6; i++)
        all = all && passed[i];
    return all;
}

// v7.2.0: YES or NO for the warning row of RESULTS
const __FlashStringHelper *yesNo(bool warning)
{
    return warning ? F("YES") : F("NO");
}

// v7.2.0: RESULTS, the result of each test, its warning (Tests 3 to
// 5), the presses, and the result of the self test
void printResultsBlock(const __FlashStringHelper *prefix)
{
    printHeading(prefix, F("RESULTS"));
    printRowStart(prefix, false, F("test"));
    for (int i = 1; i <= 6; i++)
    {
        Serial.print('T');
        Serial.print(i);
        if (i < 6)
            printSpaces(2, COLUMN_WIDTH);
    }
    Serial.println();
    printRowStart(prefix, true, F("result"));
    for (int i = 0; i < 6; i++)
        printText(passed[i] ? F("PASS") : F("FAIL"),
                  (i < 5) ? COLUMN_WIDTH : 0);
    Serial.println();
    printRowStart(prefix, true, F("warning"));
    printText(F("-"), COLUMN_WIDTH);
    printText(F("-"), COLUMN_WIDTH);
    printText(yesNo(centerWarning()), COLUMN_WIDTH);
    printText(yesNo(crossWarning()), COLUMN_WIDTH);
    printText(yesNo(verifyWarning()), COLUMN_WIDTH);
    printText(F("-"), 0);
    Serial.println();
    Serial.print(prefix);
    Serial.print(F("  * Presses during Tests 3 to 6: "));
    Serial.print(extraPresses);
    Serial.println(F(" (0 expected)"));
    Serial.print(prefix);
    Serial.println(allPassed() ? F("  * Result: PASS")
                               : F("  * Result: FAIL"));
}

// The lines of the Self Test Report (v6.8.0). prefix starts each line:
// nothing in the serial monitor, "// " inside the printed
// include/JoystickMeasurements.h (v7.0.0), where the report becomes
// comments. Since v7.1.0 the lines follow the bench test check list;
// since v7.2.0 in its table format: CENTER, FIRST ENTRY and ENDS,
// SECOND ENTRY and VERIFICATION, RETURN, and RESULTS, each block with
// its equations, then its values, raw first, then calculated.
void printReportLines(const __FlashStringHelper *prefix)
{
    printHeading(prefix, F("A * holds values for the check list."));
    printBlank(prefix);
    printCenterBlock(prefix);
    printBlank(prefix);
    printFirstEntryBlock(prefix);
    printBlank(prefix);
    printSecondEntryBlock(prefix);
    printBlank(prefix);
    printReturnBlock(prefix);
    printBlank(prefix);
    printResultsBlock(prefix);
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
    // v7.1.0: the other axis moved while one axis was held
    if (crossWarning())
    {
        Serial.print(prefix);
        Serial.println(F( \
            "WARNING: in Test 4 the other axis lay more than 25 counts"));
        Serial.print(prefix);
        Serial.println(F( \
            "from its center; hold the grip straight at each edge."));
    }
    // v7.1.0: an end difference outside -5 to 10
    if (verifyWarning())
    {
        Serial.print(prefix);
        Serial.println(F( \
            "WARNING: an end difference lies outside -5 to 10; repeat"));
        Serial.print(prefix);
        Serial.println(F( \
            "Test 4 at the edges and Test 5 slowly to every edge."));
    }
}

// ---------------------------------------------------------------
// The joystick measurements file (v7.0.0; the center file of
// v6.4.0 to v6.8.0 was include/JoystickCenter.h)
// After a pass, the report prints a complete
// include/JoystickMeasurements.h, with the same comments as the
// shipped file, between two marker lines, and the Self Test Report
// under SELF TEST REPORT. Copy every line between the markers and
// replace the whole file with them; the PlatformIO monitor also
// saves the output in a log file (monitor_filters = log2file), so
// the lines can be copied from that file. Step3_Generator writes its
// values into Step4_Generated. Step2_JUL does not use the file; it
// keeps the center 511. Run this self test again after the
// joystick is exchanged, and copy the new file.
// ---------------------------------------------------------------
void printMeasurementsFile()
{
    Serial.println(F("// ----- BEGIN JoystickMeasurements.h -----"));
    Serial.println(F("//"));
    Serial.println(F("// Carpenter Software"));
    Serial.println(F("// File: JoystickMeasurements.h"));
    Serial.println(F("// Github: MageMCU"));
    Serial.println(F("// Repository: Joystick-Uno-L298N"));
    Serial.println(F("// Folder: Code-JUL"));
    Serial.println(F("//"));
    Serial.println(F("// By Jesse Carpenter (carpentersoftware.com)"));
    Serial.println(F("//"));
    Serial.println(F("// MIT LICENSE"));
    Serial.println(F("//"));
    Serial.println(F("// RELEASE"));
    Serial.println(F("//   2026-10-30  v7.3.0"));
    Serial.println(F("//   JoystickMeasurements.h printed by Step1_Joystick"));
    Serial.println(F( \
        "//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)"));
    Serial.println(F("//"));
    Serial.println(F( \
        "// The joystick measurements (v7.0.0; include/JoystickCenter.h, " \
        "added"));
    Serial.println(F("// in v6.4.0, held the two centers only)"));
    Serial.println(F("//"));
    Serial.println(F("// WHY THIS FILE EXISTS"));
    Serial.println(F( \
        "// A thumb joystick seldom rests at exactly 511, the middle of the"));
    Serial.println(F( \
        "// ADC range 0 to 1023, and seldom reaches 0 and 1023 at its ends."));
    Serial.println(F( \
        "// Step1_Joystick measures three points of each axis in raw ADC"));
    Serial.println(F( \
        "// counts: the center, the rest reading (Test 3), and the low end " \
        "and"));
    Serial.println(F( \
        "// the high end, the smallest and largest reading with the grip " \
        "held"));
    Serial.println(F( \
        "// UP, DOWN, LEFT, and RIGHT (Test 4), verified by a circle (Test " \
        "5)."));
    Serial.println(F( \
        "// This file keeps those six measured values in one place."));
    Serial.println(F( \
        "// Step4_Generated corrects each axis at the center and at both " \
        "ends"));
    Serial.println(F( \
        "// with two linear equations, one on each side of the center"));
    Serial.println(F( \
        "// (include/claude/ace.h, THE JOYSTICK EQUATIONS), so a resting " \
        "grip"));
    Serial.println(F( \
        "// gives 0 and a full push gives the full command on both sides."));
    Serial.println(F("//"));
    Serial.println(F("// WHERE IT IS USED"));
    Serial.println(F( \
        "//   Step1_Joystick     Includes it to compare the values now in " \
        "the"));
    Serial.println(F( \
        "//                      project with a new self test, and to print"));
    Serial.println(F( \
        "//                      the calculated N in the live values. After " \
        "a"));
    Serial.println(F( \
        "//                      passing self test the report prints a new " \
        "copy"));
    Serial.println(F("//                      of this file."));
    Serial.println(F( \
        "//   Step3_Generator    Check 1 shows the six values for the " \
        "student"));
    Serial.println(F( \
        "//                      to confirm, rejects values outside the " \
        "Step1"));
    Serial.println(F( \
        "//                      limits when it is built (#error), and " \
        "writes"));
    Serial.println(F("//                      them into Step4_Generated."));
    Serial.println(F( \
        "//   Step4_Generated    Does not include this file. It holds the " \
        "copied"));
    Serial.println(F( \
        "//                      values, which claude/ace.h uses in THE " \
        "JOYSTICK"));
    Serial.println(F("//                      EQUATIONS."));
    Serial.println(F( \
        "//   Lesson 17          DeadZone: prints the centers and suggests " \
        "the"));
    Serial.println(F( \
        "//                      dead zone offset about each center."));
    Serial.println(F( \
        "//   Lesson 20          JoystickMap: the low end, center, and high " \
        "end"));
    Serial.println(F("//                      of each two segment map."));
    Serial.println(F( \
        "//   Step2_JUL          Does not use it; it keeps the center 511"));
    Serial.println(F("//                      (author decision, v6.4.0)."));
    Serial.println(F("//"));
    Serial.println(F("// HOW TO UPDATE IT"));
    Serial.println(F( \
        "// Shipped with 0, 511, and 1023 for each axis; these were not"));
    Serial.println(F( \
        "// measured. After a passing self test, replace the whole file with"));
    Serial.println(F( \
        "// the lines Step1_Joystick prints between its two marker lines. " \
        "Then"));
    Serial.println(F( \
        "// run Step3_Generator again so Step4_Generated receives the new"));
    Serial.println(F( \
        "// values. Limits (Step1_Joystick): each center 461 to 561 (Test 3"));
    Serial.println(F( \
        "// fails a center more than 50 counts from 511 and warns above 25"));
    Serial.println(F( \
        "// counts: a new joystick is recommended); each end at least 200"));
    Serial.println(F("// counts from its center (Tests 4 and 5)."));
    Serial.println(F("//"));
    Serial.println(F("// SELF TEST REPORT"));
    printReportLines(F("// "));
    Serial.println(F("//"));
    Serial.println();
    Serial.println(F("#ifndef JoystickMeasurements_h"));
    Serial.println(F("#define JoystickMeasurements_h"));
    Serial.println();
    Serial.println(F( \
        "// Raw ADC counts (0 to 1023): low end, center, high end of each " \
        "axis"));
    Serial.print(F("#define JOYSTICK_A0_LOW "));
    Serial.println(axisA0.low);
    Serial.print(F("#define JOYSTICK_A0_CENTER "));
    Serial.println(axisA0.center);
    Serial.print(F("#define JOYSTICK_A0_HIGH "));
    Serial.println(axisA0.high);
    Serial.print(F("#define JOYSTICK_A1_LOW "));
    Serial.println(axisA1.low);
    Serial.print(F("#define JOYSTICK_A1_CENTER "));
    Serial.println(axisA1.center);
    Serial.print(F("#define JOYSTICK_A1_HIGH "));
    Serial.println(axisA1.high);
    Serial.println();
    Serial.println(F("#endif"));
    Serial.println(F("// ----- END JoystickMeasurements.h -----"));
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
//   Test 4  A held end short of MIN_TRAVEL: hold the grip all the
//           way at that edge; if it stays short, check that wire.
//   Test 5  A circle end short of MIN_TRAVEL: move the grip slowly,
//           all the way to every edge, two times.
//   Test 6  The grip does not come back to center: try another
//           module, or enlarge the dead zone of Step2_JUL (X_OFFSET
//           and Y_OFFSET) and of Step4_Generated (DEAD_ZONE).
//   Presses during Tests 3 to 6: a floating D2 gives presses that no
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
    // v6.8.0: after a pass the report is written into the printed file;
    // v7.2.0: the monitor shows RESULTS first
    printResultsBlock(F(""));
    Serial.println(F("The joystick is ready for L298N Setup."));
    if (centerWarning())
        Serial.println(F( \
            "WARNING: a center lies more than 25 counts from 511."));
    // v7.1.0: the warnings of Tests 4 and 5
    if (crossWarning())
        Serial.println(F( \
            "WARNING: in Test 4 the other axis lay more than 25 counts."));
    if (verifyWarning())
        Serial.println(F( \
            "WARNING: an end difference lies outside -5 to 10."));
    Serial.println(F("Measured by Tests 3 and 4:   low  center    high"));
    // v7.1.0: the low and high ends are the held ends of Test 4
    printEndsLine(F("A0"), axisA0.low, axisA0.center, axisA0.high);
    printEndsLine(F("A1"), axisA1.low, axisA1.center, axisA1.high);
    Serial.println(F("Now in JoystickMeasurements.h:"));
    printEndsLine(F("A0"), JOYSTICK_A0_LOW, JOYSTICK_A0_CENTER,
                  JOYSTICK_A0_HIGH);
    printEndsLine(F("A1"), JOYSTICK_A1_LOW, JOYSTICK_A1_CENTER,
                  JOYSTICK_A1_HIGH);
    // v7.1.0: two measurements differ by a few counts, so a center
    // within 1 count and an end within INSET counts of the file match
    if (fileMatches())
        Serial.println(F("They match; the file needs no change."));
    else
        Serial.println(F("They differ; copy the new file below."));
    Serial.println(F( \
        "The Self Test Report is written into the file below, under"));
    Serial.println(F("SELF TEST REPORT."));
    printDots();
    Serial.println(F( \
        "Copy every line between the two marker lines and replace"));
    Serial.println(F( \
        "all of include/JoystickMeasurements.h with them (Step3_Generator"));
    Serial.println(F("uses the file). The PlatformIO monitor also"));
    Serial.println(F("saves this output in a log file (log2file)."));
    Serial.println();
    printMeasurementsFile();
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
        "Test 1 of 6: Press the push button and hold it. The LED turns on."));
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
        "Test 2 of 6: Release the push button. The LED turns off."));
    waitForEnter(Wait::Button);
    // A release after a failed press proves nothing
    passed[1] = passed[0] && !button.isButtonOn();
    Serial.print(button.isButtonOn() ? F("  SW: ON  ") : F("  SW: OFF  "));
    printPass(passed[1]);
    // clear the press of Test 1
    button.wasPressed();
}

// Test 3: the average reading at rest is the center (CENTER)
void testCenter()
{
    printDots();
    Serial.println(F( \
        "Test 3 of 6: Leave the grip at rest. Do not touch the joystick."));
    waitForEnter(Wait::Count);
    axisA0.center = axisA0.readAverage();
    axisA1.center = axisA1.readAverage();

    // abs() of Arduino is a macro that evaluates its argument twice,
    // so the offsets are stored first
    int offsetA0 = axisA0.center - ADC_MIDDLE;
    int offsetA1 = axisA1.center - ADC_MIDDLE;
    passed[2] = abs(offsetA0) <= CENTER_TOLERANCE &&
                abs(offsetA1) <= CENTER_TOLERANCE;
    printCenterBlock(F(""));
    Serial.print(F("  "));
    printPass(passed[2]);
    // v6.5.0: a center more than 25 counts from 511 passes with a warning
    if (passed[2] && centerWarning())
        Serial.println(F( \
            "  WARNING: more than 25 counts from 511; a new joystick is " \
            "recommended."));
}

// Test 4: the first entry, the grip held at each edge (v7.1.0)
void testDirections()
{
    for (int d = 0; d < 4; d++)
    {
        printDots();
        Serial.print(F("Test 4 of 6, first entry, "));
        Serial.print(directionName(d));
        Serial.print(F(": hold the grip at the "));
        Serial.print(edgeName(d));
        Serial.println(F(" edge."));
        Serial.println(F( \
            "  Keep it there and press Enter with the other hand."));
        waitForEnter(Wait::Count);
        axisA0.held[d] = axisA0.readAverage();
        axisA1.held[d] = axisA1.readAverage();
        // v7.2.0: the row of this direction under its column names
        printDirectionNames(F(""));
        printDirectionRow(F(""), d);
    }
    axisA0.findEnds();
    axisA1.findEnds();
    passed[3] = axisA0.travelPassed() && axisA1.travelPassed();
    // v7.2.0: the four directions together, and the ends
    Serial.println();
    printFirstEntryBlock(F(""));
    Serial.print(F("  "));
    printPass(passed[3]);
    if (crossWarning())
        Serial.println(F( \
            "  WARNING: the other axis lay more than 25 counts from its " \
            "center."));
}

// Test 5: the second entry, the circle verifies the held ends; its
// ends are recorded until Enter is pressed
void testCircle()
{
    printDots();
    Serial.println(F( \
        "Test 5 of 6, second entry: move the grip slowly to every edge,"));
    Serial.println(F("  around the full circle, two times. Then press Enter."));
    // the search for the ends starts from the center
    axisA0.circleLow = axisA0.circleHigh = axisA0.center;
    axisA1.circleLow = axisA1.circleHigh = axisA1.center;
    timerSample.resetTimer();
    waitForEnter(Wait::Record);
    passed[4] = axisA0.circlePassed() && axisA1.circlePassed();
    printSecondEntryBlock(F(""));
    Serial.print(F("  "));
    printPass(passed[4]);
    if (verifyWarning())
        Serial.println(F( \
            "  WARNING: an end difference lies outside -5 to 10."));
}

// Test 6: the released grip must return to the center (Return)
void testReturn()
{
    printDots();
    Serial.println(F( \
        "Test 6 of 6: Release the grip. Let it return to center."));
    waitForEnter(Wait::Count);
    axisA0.rest = axisA0.readAverage();
    axisA1.rest = axisA1.readAverage();
    // A return after a failed Test 4 proves nothing: an axis that
    // never moved is always back at its center
    int returnA0 = axisA0.rest - axisA0.center;
    int returnA1 = axisA1.rest - axisA1.center;
    passed[5] = passed[3] &&
                abs(returnA0) <= RETURN_TOLERANCE &&
                abs(returnA1) <= RETURN_TOLERANCE;
    printReturnBlock(F(""));
    Serial.print(F("  "));
    printPass(passed[5]);
}

// The six tests and the report
void runSelfTest()
{
    extraPresses = 0;
    printDots();
    Serial.println(F("Joystick Self Test (Step1_Joystick)"));
    Serial.println(F("Follow each instruction, then press Enter."));
    testPress();
    testRelease();
    testCenter();
    testDirections();
    testCircle();
    testReturn();
    printReport();
}

// ---------------------------------------------------------------
// After the report
// ---------------------------------------------------------------

// A0 and A1, raw (offset from the measured center) and the
// calculated N, and SW, four times a second for LIVE_MS. At rest both
// offsets stay near 0 and N is 0; at an edge N reaches -1023 or 1023
// (v7.0.0). N uses the values of include/JoystickMeasurements.h, the
// values Step4_Generated receives.
void printLiveValues()
{
    printDots();
    Serial.println(F( \
        "Live values: A0 and A1, raw (offset from center) and N,"));
    Serial.println(F("and SW, four times a second for 20 seconds."));
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
            // offset 5 characters inside the parentheses (v6.4.0),
            // N 6 characters (v7.0.0)
            int rawA0 = analogRead(axisA0.pin);
            int rawA1 = analogRead(axisA1.pin);
            Serial.print(F("A0: "));
            printColumn(rawA0, 4);
            Serial.print(F(" ("));
            printColumn(rawA0 - axisA0.center, 5);
            Serial.print(F(") N"));
            printColumn(calculatedN(rawA0, JOYSTICK_A0_LOW,
                                    JOYSTICK_A0_CENTER, JOYSTICK_A0_HIGH),
                        6);
            Serial.print(F("  A1: "));
            printColumn(rawA1, 4);
            Serial.print(F(" ("));
            printColumn(rawA1 - axisA1.center, 5);
            Serial.print(F(") N"));
            printColumn(calculatedN(rawA1, JOYSTICK_A1_LOW,
                                    JOYSTICK_A1_CENTER, JOYSTICK_A1_HIGH),
                        6);
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
    axisA0 = Axis{};
    axisA0.pin = A0;
    axisA0.name = F("A0");
    // joystick VRy
    axisA1 = Axis{};
    axisA1.pin = A1;
    axisA1.name = F("A1");

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
