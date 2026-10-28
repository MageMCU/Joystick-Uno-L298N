//
// Carpenter Software
// Folder: src/Step3_Generator: File: Class main.cpp
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
// Added 20261017. Written with Claude (Anthropic), an AI assistant;
// see include/claude/README.md. Revised 20261017: Step1_Joystick was
// removed and the steps renumbered. Revised 20261017 (v3.0.1): the
// Bits value is typed as four binary digits, and the program is
// selected with build_src_filter in env:uno.
// Revised 20261018 (v3.1.0): renamed from Step3_Generator. Before the
// Bits value, the student checks the L298N pins (Uno pin and
// ATmega328P port pin) and the joystick lines against Step2_JUL. The
// last question decides whether the printed program shows the same
// data in the serial monitor (DEBUG_GENERATED) or is printed without
// it, as before.
// Revised 20261018 (v3.2.0): the printed program names the 50 ms
// control tick of include/claude/ace.h (TICK_MS, 100 ms before) and
// the external 10 kOhm pull up that the push button requires.
// Revised 20261019 (v3.2.1): the printed setup() calls robot.begin()
// first, so the L298N pins are outputs and LOW before the debug data
// is printed (Discrepancies.md, entry 85).
// Revised 20261021 (v4.0.0): the steps are renumbered (Step1_Joystick
// is new; this program is Step3_Generator again), and the indicator
// LED is on D12, as in Circuit-1 and Step2_JUL (the ledPin line).
// Revised 20261025 (v6.4.0): a new first check shows the joystick
// center of include/JoystickCenter.h, printed by Step1_Joystick; the
// printed program passes it to ace.h as X_CENTER and Y_CENTER. The
// checks and questions are numbered 1 to 5.
// Revised 20261025 (v6.5.0): the allowed center is 461 to 561, the
// Test 3 limit of Step1_Joystick (50 counts from 511).
//
// STEPS 1 TO 5
//   Step1_Joystick:    checks the joystick connections first and
//                      prints include/JoystickCenter.h.
//   Step2_JUL:         the drive program. The Motor Movement Checklist
//                      finds its Bits() value (Article 1009, L298N
//                      Setup). The joystick lines stay as written,
//                      xDigital = analogRead(A0) and
//                      yDigital = analogRead(A1); the Bits() value
//                      corrects any joystick orientation as well as
//                      the L298N wiring.
//   Step3_Generator:   this program. Three checks and two questions in
//                      the serial monitor; it prints a main.cpp for
//                      Step4_Generated.
//   Step4_Generated:   the printed program. It drives the robot as
//                      Step2_JUL does, with the Bits() value fixed
//                      when it is built, through include/claude/ace.h.
//   Step5_MathLessons: math lessons, not used by Steps 2 to 4.
//
// THE CHECKS AND THE QUESTIONS
//   Check 1: the joystick center of include/JoystickCenter.h, the
//            rest reading of A0 and A1. Type y if it matches the
//            report of Step1_Joystick (511 and 511 as shipped). For n,
//            replace include/JoystickCenter.h with the lines printed
//            by Step1_Joystick and upload this program again.
//   Check 2: the six L298N pins, the push button, and the LED, each
//            as an Uno pin and an ATmega328P port pin, for example
//            D5 (PD5). Type y if they match the buttonPin, ledPin, and
//            six pin lines of Step2_JUL. For n, change the constants below to
//            the
//            pins of Step2_JUL and upload this program again.
//   Check 3: the joystick lines, x on A0 (PC0) and y on A1 (PC1).
//            Type y if the analogRead() lines of Step2_JUL read the same.
//            For n, restore those two lines in Step2_JUL and find the
//            Bits() value again with the checklist.
//   Question 4: the four binary digits of the Bits() line of Step2_JUL,
//            motors.Bits(BitsL298N::bits_????); typed as four
//            characters of 0 and 1.
//   Question 5: debug data in Step4_Generated, y or n. For y the
//            printed program defines DEBUG_GENERATED and its setup()
//            prints the checked data once in the serial monitor; the
//            line can be commented out later. For n the program is
//            printed without the debug data, as before v3.1.0.
//   A summary of all five follows; p prints the program, r starts
//   over. Backspace corrects a typing error. After the program, or
//   after a check answered n, r and Enter starts over.
//
// WHY THE JOYSTICK LINES ARE FIXED
//   The joystick algorithm satisfies F(-x, y) = (R, L),
//   F(x, -y) = (-R, -L), and F(y, x) = (L, -R): exchanging or
//   reversing a joystick axis swaps or negates the two commands, and
//   bit 2 swaps them while bits 1 and 0 negate each IN pair. For each
//   of the 8 joystick orientations and 16 L298N wirings (128 benches)
//   exactly one Bits() value drives correctly (Discrepancies.md,
//   entry 53). That value belongs to the joystick lines it was found
//   with, so Step2_JUL and the printed program use the same lines,
//   x on A0 and y on A1, with no reversal.
//
// HOW THE PINS ARE FOUND
//   Class L298NPins (include/claude/L298NPins.h) applies the four rules
//   of L298N::Bits() and L298N::UpdateL298N() to the Uno pins below
//   once, so the printed program needs no L298N class.
//
// Uno and USB cable only. This program writes nothing to D5 to D10.
//
// Build: in platformio.ini, select this program with
//   build_src_filter: +<Step3_Generator/>, and - before the
//   other four folders
// then Upload and Monitor. Serial monitor: 9600 baud. The PlatformIO
// monitor also saves the output in a log file (monitor_filters =
// log2file in platformio.ini), so the printed program can be copied
// from that file. Arduino IDE monitor: set the line ending to Newline.
// Copy every line between the two marker lines into
// src/Step4_Generated/main.cpp and select Step4_Generated with its
// build_src_filter line in platformio.ini.

// Common.h (v6.0.0): this program defines no debug switch, so the
// L298N.h it includes for the BitsL298N values prints nothing.
// Up to v5.1.0 a line here defined DEBUG_ALL_OFF,
// which turned off the flags Common.h then defined itself.

#include <Arduino.h>
#include "L298N.h"
#include "claude/L298NPins.h"
#include "JoystickCenter.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// Uno pins of the L298N, the same as the six pin lines of Step2_JUL
// L298N ENB (Article 1009, Circuit-1)
const uint8_t ENB = 5;
// L298N IN4
const uint8_t IN4 = 6;
// L298N IN3
const uint8_t IN3 = 7;
// L298N IN2
const uint8_t IN2 = 8;
// L298N IN1
const uint8_t IN1 = 9;
// L298N ENA
const uint8_t ENA = 10;
// Push button and indicator LED, the same as Step2_JUL (buttonPin, ledPin)
const uint8_t BUTTON_PIN = 2;
const uint8_t LED_PIN = 12;
// Advanced wiring of Article 1003 (LED on D3):
// const uint8_t LED_PIN = 3;
// Joystick, the same as the analogRead() lines of Step2_JUL;
// not changed
const uint8_t X_PIN = A0;
const uint8_t Y_PIN = A1;
// Joystick center, from include/JoystickCenter.h (v6.4.0)
const uint16_t X_CENTER = JOYSTICK_A0_CENTER;
const uint16_t Y_CENTER = JOYSTICK_A1_CENTER;
#if JOYSTICK_A0_CENTER < 461 || JOYSTICK_A0_CENTER > 561 || \
    JOYSTICK_A1_CENTER < 461 || JOYSTICK_A1_CENTER > 561
#error "JoystickCenter.h: each center must be 461 to 561 (Step1, Test 3)"
#endif

// Filled by the answers
L298NPins pins;
bool withDebug = true;

// ---------------------------------------------------------------
// Output of the answer lines
// The same lines are shown in the checks and the summary (MONITOR),
// written into the header of the printed program (COMMENT), and
// written as print statements into its setup() (CODE), so that
// Step4_Generated shows in the serial monitor exactly what was
// checked here.
// ---------------------------------------------------------------
enum LineMode
{
    MONITOR,
    COMMENT,
    CODE
};

char lineBuffer[72];

void emit(LineMode mode)
{
    if (mode == COMMENT)
    {
        Serial.print(F("//   "));
        Serial.println(lineBuffer);
    }
    else if (mode == CODE)
    {
        // A printed line over 80 characters is continued: the string
        // moves to the next line after a backslash (coding rules)
        if (strlen(lineBuffer) + 26 > 80)
        {
            Serial.println(F("    Serial.println(F( \\"));
            Serial.print(F("        \""));
        }
        else
        {
            Serial.print(F("    Serial.println(F(\""));
        }
        Serial.print(lineBuffer);
        Serial.println(F("\"));"));
    }
    else
    {
        Serial.println(lineBuffer);
    }
}

// Port pin of an Uno pin: D0 to D7 are PD0 to PD7, D8 to D13 are
// PB0 to PB5, A0 to A5 (14 to 19) are PC0 to PC5
char portLetter(uint8_t pin)
{
    return pin < 8 ? 'D' : (pin < 14 ? 'B' : 'C');
}

uint8_t portBit(uint8_t pin)
{
    return pin < 8 ? pin : (pin < 14 ? pin - 8 : pin - 14);
}

void pinLine(LineMode mode, const char *name, uint8_t pin)
{
    char uno[5];
    snprintf_P(uno, sizeof(uno), PSTR("D%u"), pin);
    snprintf_P(lineBuffer, sizeof(lineBuffer), PSTR("  %-4s %-4s (P%c%u)"),
               name, uno, portLetter(pin), portBit(pin));
    emit(mode);
}

// Check 1 data: the joystick center (v6.4.0)
void centerLines(LineMode mode)
{
    snprintf_P(lineBuffer, sizeof(lineBuffer),
               PSTR( \
                   "Joystick center (include/JoystickCenter.h, " \
                   "Step1_Joystick)"));
    emit(mode);
    snprintf_P(lineBuffer, sizeof(lineBuffer),
               PSTR( \
                   "  A0 center %u (offset " \
                   "%d)"), X_CENTER, (int)X_CENTER - 511);
    emit(mode);
    snprintf_P(lineBuffer, sizeof(lineBuffer),
               PSTR( \
                   "  A1 center %u (offset " \
                   "%d)"), Y_CENTER, (int)Y_CENTER - 511);
    emit(mode);
}

// Check 2 data: the L298N pins, the push button, and the LED
void pinLines(LineMode mode)
{
    snprintf_P(lineBuffer, sizeof(lineBuffer),
               PSTR("L298N pins (Step2_JUL, the six pin lines)"));
    emit(mode);
    pinLine(mode, "ENB", ENB);
    pinLine(mode, "IN4", IN4);
    pinLine(mode, "IN3", IN3);
    pinLine(mode, "IN2", IN2);
    pinLine(mode, "IN1", IN1);
    pinLine(mode, "ENA", ENA);
    snprintf_P(lineBuffer, sizeof(lineBuffer),
               PSTR("Push button and LED (Step2_JUL, buttonPin and ledPin)"));
    emit(mode);
    pinLine(mode, "SW", BUTTON_PIN);
    pinLine(mode, "LED", LED_PIN);
}

void analogLine(LineMode mode, char axis, uint8_t pin)
{
    snprintf_P(lineBuffer, sizeof(lineBuffer),
               PSTR("  int %cDigital = analogRead(A%u);  %c on A%u (P%c%u)"),
               axis, pin - A0, axis, pin - A0, portLetter(pin), portBit(pin));
    emit(mode);
}

// Check 3 data: the joystick lines
void analogLines(LineMode mode)
{
    snprintf_P(lineBuffer, sizeof(lineBuffer),
               PSTR("Joystick (Step2_JUL, the analogRead() lines)"));
    emit(mode);
    analogLine(mode, 'x', X_PIN);
    analogLine(mode, 'y', Y_PIN);
}

void commandLine(LineMode mode, const char *name, MotorPins m)
{
    snprintf_P(lineBuffer, sizeof(lineBuffer),
               PSTR("  %s EN D%u, D%u HIGH for +, D%u HIGH for -"),
               name, m.EN, m.FWD, m.REV);
    emit(mode);
}

// The answer: the Bits value and the pins it resolves to
void bitsLines(LineMode mode)
{
    int value = pins.GetBitsValue();
    snprintf_P(lineBuffer, sizeof(lineBuffer),
               PSTR("Bits value (Step2_JUL, the Bits() line)"));
    emit(mode);
    snprintf_P(lineBuffer, sizeof(lineBuffer),
               PSTR("  motors.Bits(BitsL298N::bits_%u%u%u%u);"),
               (value >> 3) & 1, (value >> 2) & 1, (value >> 1) & 1, value & 1);
    emit(mode);
    commandLine(mode, "Left command: ", pins.Left());
    commandLine(mode, "Right command:", pins.Right());
}

// ---------------------------------------------------------------
// Serial questions
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

// Reads one line typed in the serial monitor and echoes it.
// Enter (CR or LF) ends the line; Backspace removes one character.
// An empty line is returned as "" (used by Press Enter to begin).
// Line endings: LF (Arduino IDE, Newline), CR, and CR LF (PlatformIO)
// all end a line. The LF of a CR LF pair is skipped, so it does not
// end the next line as an empty answer.
bool lastWasCR = false;

void readLine(char *line, int size)
{
    int n = 0;
    while (true)
    {
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

// Reads a one letter answer; returns it in lower case, or 0 when the
// line is not one of the two letters a and b
char readLetter(char a, char b)
{
    char line[8];
    readLine(line, sizeof(line));
    char c = tolower(line[0]);
    if (line[1] == '\0' && (c == a || c == b))
        return c;
    return 0;
}

// Asks until y or n is typed; returns true for y
bool askYesNo()
{
    while (true)
    {
        Serial.print(F("Type y (yes) or n (no): "));
        char c = readLetter('y', 'n');
        if (c)
            return c == 'y';
        Serial.println(F("  Type y or n."));
    }
}

// Four digits of 0 and 1 are read as the binary Bits value, 0000 to
// 1111. Returns -1 for anything else.
int readBitsValue()
{
    char line[8];
    readLine(line, sizeof(line));
    if (strlen(line) != 4)
        return -1;
    int value = 0;
    for (int i = 0; i < 4; i++)
    {
        if (line[i] != '0' && line[i] != '1')
            return -1;
        value = value * 2 + (line[i] - '0');
    }
    return value;
}

// A dotted line marks the start of each new output in the serial
// monitor, so the newest check or question is found at a glance. The
// blank line above it is printed by the answer before it.
void printDots()
{
    Serial.println(F("................................................"));
}

// Check 1: returns true when the student confirms the center
bool checkCenter()
{
    printDots();
    Serial.println(F( \
        "Check 1 of 5: the joystick center measured by Step1_Joystick"));
    centerLines(MONITOR);
    Serial.println(F("Does it match the report of Step1_Joystick?"));
    if (askYesNo())
    {
        Serial.println();
        return true;
    }
    Serial.println(F( \
        "  Replace include/JoystickCenter.h with the lines printed by"));
    Serial.println(F("  Step1_Joystick, then upload this program again."));
    return false;
}

// Check 2: returns true when the student confirms the pins
bool checkPins()
{
    printDots();
    Serial.println(F( \
        "Check 2 of 5: the pins of Step2_JUL, Uno pin (ATmega328P pin)"));
    pinLines(MONITOR);
    Serial.println(F("Are these the pins of Step2_JUL?"));
    if (askYesNo())
    {
        Serial.println();
        return true;
    }
    Serial.println(F( \
        "  Change ENB, IN4 to IN1, ENA, BUTTON_PIN, and LED_PIN at the"));
    Serial.println(F( \
        "  top of Step3_Generator/main.cpp to the pins of Step2_JUL,"));
    Serial.println(F("  then upload this program again."));
    return false;
}

// Check 3: returns true when the student confirms the joystick lines
bool checkJoystick()
{
    printDots();
    Serial.println(F("Check 3 of 5: the joystick lines of Step2_JUL"));
    analogLines(MONITOR);
    Serial.println(F("Do the analogRead() lines of Step2_JUL read the same?"));
    if (askYesNo())
    {
        Serial.println();
        return true;
    }
    Serial.println(F( \
        "  Restore the analogRead() lines of Step2_JUL as shown above, " \
        "upload"));
    Serial.println(F( \
        "  it, and find the Bits() value again with the Motor Movement"));
    Serial.println(F( \
        "  Checklist. The value found belongs to the lines it was found " \
        "with."));
    return false;
}

// The question: the Bits() value of Step2_JUL
void askBits()
{
    printDots();
    Serial.println(F( \
        "Question 4 of 5: which Bits value is used in Step2_JUL?"));
    // Split so that ??) is not read as a trigraph by strict C++ modes
    Serial.println(F( \
        "  The Bits() line: motors.Bits(BitsL298N::bits_???" "?);"));

    int value = -1;
    while (true)
    {
        Serial.print(F("Type the four binary digits: "));
        value = readBitsValue();
        if (value >= 0)
            break;
        Serial.println(F("  Type four digits of 0 and 1."));
    }
    pins.Resolve((BitsL298N)((int)BitsL298N::bits_0000 + value));
    Serial.println();
}

// Question 5: the debug data in the printed program
void askDebug()
{
    printDots();
    Serial.println(F( \
        "Question 5 of 5: show this data in the serial monitor when"));
    Serial.println(F("  Step4_Generated starts (DEBUG_GENERATED)?"));
    withDebug = askYesNo();
    Serial.println();
}

// The summary; returns true for p (print), false for r (again)
bool askConfirm()
{
    printDots();
    Serial.println(F("Summary: the data for Step4_Generated"));
    centerLines(MONITOR);
    pinLines(MONITOR);
    analogLines(MONITOR);
    bitsLines(MONITOR);
    if (withDebug)
        Serial.println(F( \
            "Debug data in Step4_Generated: yes (DEBUG_GENERATED)"));
    else
        Serial.println(F("Debug data in Step4_Generated: no"));
    while (true)
    {
        Serial.print(F("Type p to print the program, or r to start again: "));
        char c = readLetter('p', 'r');
        if (c)
            return c == 'p';
        Serial.println(F("  Type p or r."));
    }
}

void printIntro()
{
    char line[8];
    // v6.4.1: program title
    Serial.println(F( \
        "\n................................................" \
        "\nStep3_Generator: prints the program Step4_Generated" \
        "\nSelected in platformio.ini: +<Step3_Generator/>" \
        "\nStep3_Generator: three checks and two questions about Steps 1 " \
        "and 2."));
    Serial.println(F( \
        "Answer and press Enter. Backspace corrects a typing error."));
    Serial.println(F("Arduino IDE monitor: set the line ending to Newline."));
    Serial.print(F("Press Enter to begin."));
    readLine(line, sizeof(line));
    Serial.println();
}

void printConst(const __FlashStringHelper *name, uint8_t value)
{
    Serial.print(F("const uint8_t "));
    Serial.print(name);
    Serial.print(F(" = "));
    Serial.print(value);
    Serial.println(';');
}

// Prints the Step4_Generated main.cpp for the answers
void printProgram()
{
    MotorPins left = pins.Left();
    MotorPins right = pins.Right();
    int bits = pins.GetBitsValue();

    Serial.println(F("// ----- BEGIN main.cpp -----"));
    Serial.println(F("//"));
    Serial.println(F("// Carpenter Software"));
    Serial.println(F("// Folder: src/Step4_Generated: File: main.cpp"));
    Serial.println(F("// Drive program printed by Step3_Generator"));
    Serial.println(F("// Github: MageMCU"));
    Serial.println(F("// Repository: Joystick-Uno-L298N"));
    Serial.println(F("// Folder: Code-JUL"));
    Serial.println(F("//"));
    Serial.println(F("// By Jesse Carpenter (carpentersoftware.com)"));
    Serial.println(F("//"));
    Serial.println(F("// Testing Platform:"));
    Serial.println(F("//  * MCU:Atmega328P"));
    Serial.println(F("//  * IDE:PlatformIO"));
    Serial.println(F("//  * Editor: VSCode"));
    Serial.println(F("//"));
    Serial.println(F("// MIT LICENSE"));
    Serial.println(F("//"));
    Serial.println(F("// STEPS 2 TO 4"));
    Serial.println(F( \
        "//   Step2_JUL:       the drive program; the Motor Movement " \
        "Checklist"));
    Serial.println(F( \
        "//                    finds its Bits() value (Article 1009, L298N"));
    Serial.println(F( \
        "//                    Setup). The joystick lines stay as written,"));
    Serial.println(F("//                    x on A0 and y on A1."));
    Serial.println(F( \
        "//   Step3_Generator: checks the pins and the joystick lines, " \
        "asks for"));
    Serial.println(F( \
        "//                    the Bits() value, and prints this file " \
        "with the"));
    Serial.println(F("//                    answers written in as constants."));
    Serial.println(F( \
        "//   Step4_Generated: this file. It drives the robot as " \
        "Step2_JUL does,"));
    Serial.println(F( \
        "//                    with the Bits() value fixed when it is built."));
    Serial.println(F("//"));
    Serial.println(F("// DATA CHECKED IN STEP3_GENERATOR"));
    centerLines(COMMENT);
    pinLines(COMMENT);
    analogLines(COMMENT);
    bitsLines(COMMENT);
    Serial.println(F("//"));
    if (withDebug)
    {
        Serial.println(F( \
            "// DEBUG_GENERATED (below the include lines): while it is " \
            "defined,"));
        Serial.println(F( \
            "// setup() prints the same data in the serial monitor (9600 " \
            "baud)"));
        Serial.println(F( \
            "// once, before the motors can run. Comment the line out to " \
            "leave"));
        Serial.println(F( \
            "// the serial port unused; the drive is the same either way."));
        Serial.println(F( \
            "// The push button is read after the last line, Ready; a press"));
        Serial.println(F( \
            "// made while the data is printing (about 1 s) is not seen."));
        Serial.println(F("//"));
    }
    Serial.println(F( \
        "// include/claude/ace.h holds everything this program needs in one"));
    Serial.println(F( \
        "// file: the joystick algorithm, the mapping and dead zone, the " \
        "push"));
    Serial.println(F( \
        "// button, the timer, and the L298N pins. It includes Arduino.h " \
        "only"));
    Serial.println(F( \
        "// and is never edited; a new run of Step3 changes only this file."));
    Serial.println(F( \
        "// For the same joystick readings it sets the same pin states as"));
    Serial.println(F( \
        "// Step2_JUL, with a control tick about 2.5 times faster (see " \
        "ace.h)."));
    Serial.println(F( \
        "// ace.h also moves each reading by the joystick center (X_CENTER"));
    Serial.println(F( \
        "// and Y_CENTER below); Step2_JUL keeps the center 511."));
    Serial.println(F( \
        "// The tick repeats every 50 ms (TICK_MS of ace.h); Step2_JUL uses"));
    Serial.println(F("// 100 ms."));
    Serial.println(F("//"));
    Serial.print(F("// Push button: SW on D"));
    Serial.print(BUTTON_PIN);
    Serial.println(F(" with the external 10 kOhm pull up to 5 V"));
    Serial.println(F( \
        "// (pressed reads LOW), the shipped form of Step2_JUL. The"));
    Serial.println(F("// internal pull up is off."));
    Serial.println(F("//"));
    Serial.println(F("// Build: in platformio.ini, select this program with"));
    Serial.println(F( \
        "//   build_src_filter: +<Step4_Generated/>, and - before the"));
    Serial.println(F("//   other four folders"));
    Serial.println(F( \
        "// In a project of its own, copy include/claude/ace.h with this " \
        "file."));
    Serial.println(F("//"));
    Serial.println(F( \
        "// SAFETY COMES FIRST (WATCH YOUR FINGERS): the motors run only " \
        "while"));
    Serial.print(F("// the push button state is ON (indicator LED on D"));
    Serial.print(LED_PIN);
    Serial.println(F(")."));
    Serial.println();
    Serial.println(F("#include <Arduino.h>"));
    Serial.println(F("#include \"claude/ace.h\""));
    Serial.println();
    if (withDebug)
    {
        Serial.println(F( \
            "// Serial verification of the data checked in Step3_Generator."));
        Serial.println(F("// Comment this line out to turn the output off."));
        Serial.println(F("#define DEBUG_GENERATED"));
        Serial.println();
    }
    Serial.println(F("// Carpenter Software - Jesse Carpenter"));
    Serial.println(F("using namespace csjc;"));
    Serial.println();
    Serial.println(F("// Joystick pins, the same as Step2_JUL"));
    Serial.print(F("const uint8_t X_PIN = A"));
    Serial.print(X_PIN - A0);
    Serial.println(';');
    Serial.print(F("const uint8_t Y_PIN = A"));
    Serial.print(Y_PIN - A0);
    Serial.println(';');
    Serial.println();
    Serial.print(F("// L298N pins resolved from bits_"));
    for (int b = 3; b >= 0; b--)
        Serial.print((bits >> b) & 1);
    Serial.println();
    Serial.println(F("// FWD is HIGH when the command is zero or positive,"));
    Serial.println(F("// REV is HIGH when the command is negative."));
    printConst(F("LEFT_EN"), left.EN);
    printConst(F("LEFT_FWD"), left.FWD);
    printConst(F("LEFT_REV"), left.REV);
    printConst(F("RIGHT_EN"), right.EN);
    printConst(F("RIGHT_FWD"), right.FWD);
    printConst(F("RIGHT_REV"), right.REV);
    Serial.println();
    Serial.println(F( \
        "// Push button and indicator LED, the same as Step2_JUL"));
    printConst(F("BUTTON_PIN"), BUTTON_PIN);
    printConst(F("LED_PIN"), LED_PIN);
    Serial.println();
    Serial.println(F( \
        "// Control tick and debounce, in ms (the defaults of ace.h)"));
    Serial.println(F("const uint16_t TICK_MS = 50;"));
    Serial.println(F("const uint16_t DEBOUNCE_MS = 50;"));
    Serial.println();
    Serial.println(F( \
        "// Joystick center measured by Step1_Joystick (JoystickCenter.h):"));
    Serial.println(F("// X_CENTER of A0, Y_CENTER of A1"));
    Serial.print(F("const uint16_t X_CENTER = "));
    Serial.print(X_CENTER);
    Serial.println(';');
    Serial.print(F("const uint16_t Y_CENTER = "));
    Serial.print(Y_CENTER);
    Serial.println(';');
    Serial.println();
    Serial.println(F("Ace<X_PIN, Y_PIN,"));
    Serial.println(F("    LEFT_EN, LEFT_FWD, LEFT_REV,"));
    Serial.println(F("    RIGHT_EN, RIGHT_FWD, RIGHT_REV,"));
    Serial.println(F("    BUTTON_PIN, LED_PIN, TICK_MS, DEBOUNCE_MS,"));
    Serial.println(F("    X_CENTER, Y_CENTER> robot;"));
    Serial.println();
    Serial.println(F("void setup()"));
    Serial.println(F("{"));
    Serial.println(F( \
        "    // D5 to D10 as outputs and LOW before anything else (SAFETY)"));
    Serial.println(F("    robot.begin();"));
    if (withDebug)
    {
        Serial.println(F("#ifdef DEBUG_GENERATED"));
        Serial.println(F("    Serial.begin(9600);"));
        Serial.println(F("    while (!Serial)"));
        Serial.println(F("    {"));
        Serial.println(F("    }"));
        // The title, one statement over four lines (coding rules)
        Serial.println(F("    Serial.println(F( \\"));
        Serial.print(F("        \"\\n"));
        Serial.print(F("................................................"));
        Serial.println(F("\" \\"));
        Serial.println(F( \
            "        \"\\nStep4_Generated: the drive program printed by " \
            "Step3_Generator\" \\"));
        Serial.println(F( \
            "        \"\\nSelected in platformio.ini: " \
            "+<Step4_Generated/>\"));"));
        Serial.println(F( \
            "    Serial.println(F(\"Step4_Generated: data checked in " \
            "Step3_Generator\"));"));
        centerLines(CODE);
        pinLines(CODE);
        analogLines(CODE);
        bitsLines(CODE);
        Serial.print(F( \
            "    Serial.println(F(\"Ready: press the push button; the LED " \
            "on D"));
        Serial.print(LED_PIN);
        Serial.println(F(" shows ON.\"));"));
        Serial.println(F("#endif"));
    }
    Serial.println(F("}"));
    Serial.println();
    Serial.println(F("void loop()"));
    Serial.println(F("{"));
    Serial.println(F( \
        "    // Button, 50 ms timer, and one control tick when the timer " \
        "fires"));
    Serial.println(F("    robot.update();"));
    Serial.println(F("}"));
    Serial.println(F("// ----- END main.cpp -----"));
}

// The checks, the question, the summary, and the program
void runGenerator()
{
    while (true)
    {
        if (!checkCenter() || !checkPins() || !checkJoystick())
        {
            Serial.println(F("Type r and Enter to start again."));
            return;
        }
        askBits();
        askDebug();
        if (askConfirm())
            break;
        Serial.println();
    }
    Serial.println();
    printDots();
    Serial.println(F( \
        "Copy every line between the two marker lines. The PlatformIO"));
    Serial.println(F( \
        "monitor also saves this output in a log file (log2file)."));
    Serial.println();
    printProgram();
    Serial.println(F("Type r and Enter to start again."));
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    pins = L298NPins(ENB, IN4, IN3, IN2, IN1, ENA);

    printIntro();
    runGenerator();
}

void loop()
{
    // r and Enter starts again; readLine() reads the whole line, so
    // its line ending is not left for the next question
    char line[8];
    readLine(line, sizeof(line));
    if (line[1] == '\0' && tolower(line[0]) == 'r')
    {
        Serial.println();
        runGenerator();
    }
}
