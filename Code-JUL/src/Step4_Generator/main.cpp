//
// Carpenter Software
// Folder: src/Step4_Generator: File: Class main.cpp
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
// see include/claude/README.md.
//
// STEPS 1 TO 5
//   Step1_Joystick:  finds the analog pin and the direction of each
//                    joystick axis (Article 1009, Joystick Setup).
//   Step2_JUL:       finds the Bits() value of the L298N wiring with
//                    the Motor Movement Checklist (Article 1009,
//                    L298N Setup).
//   Step3_MathLessons: math lessons, not used by Steps 4 and 5.
//   Step4_Generator: this program. It asks four questions in the
//                    serial monitor about the results of Step 1 and
//                    Step 2, and prints a main.cpp for Step 5.
//   Step5_Generated: the printed program. It drives the robot as
//                    Step2_JUL does, with the bench results fixed when
//                    it is built, through include/claude/ace.h.
//
// THE FOUR QUESTIONS (choices are typed as a or b, A and B accepted)
//   1. Which analog pin does x use in Step1_Joystick?  a: A1  b: A0
//      (the joystick uses A0 and A1 only, so y takes the other pin)
//   2. Which x equation is used?
//      a: xDigital = analogRead(A1);  b: xDigital = 1023 - analogRead(A1);
//   3. Which y equation is used?
//      a: yDigital = analogRead(A0);  b: yDigital = 1023 - analogRead(A0);
//      (questions 2 and 3 show the pins chosen in question 1)
//   4. Which Bits value is used in Step2_JUL? A table of the 16 values,
//      decimal and binary, is printed with the question. One or two
//      digits are read as decimal (0 to 15); four digits of 0 and 1
//      are read as binary.
//   A summary follows; p prints the program, r asks again. Backspace
//   corrects a typing error. After the program, r and Enter starts
//   over.
//
// HOW THE PINS ARE FOUND
//   Class L298NPins (include/claude/L298NPins.h) applies the four rules
//   of L298N::Bits() and L298N::UpdateL298N() to the Uno pins below
//   once, so the printed program needs no L298N class. If the L298N
//   wires move to other pins, change ENA, IN1 to IN4, and ENB below,
//   then run Step2_JUL and this program again.
//
// Uno and USB cable only. This program writes nothing to D5 to D10.
//
// Build: select the PlatformIO environment step4 (platformio.ini),
// for example: pio run -e step4 -t upload -t monitor
// Serial monitor: 9600 baud. The PlatformIO monitor also saves the
// output in a log file (monitor_filters = log2file in env:step4), so
// the printed program can be copied from that file. Arduino IDE
// monitor: set the line ending to Newline.
// Copy every line between the two marker lines into
// src/Step5_Generated/main.cpp and build it with the environment step5.

#ifdef STEP4_GENERATOR

#include <Arduino.h>
#include "L298N.h"
#include "claude/L298NPins.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// Uno pins of the L298N, the same as Step2_JUL
const uint8_t ENA = 5;
const uint8_t IN1 = 6;
const uint8_t IN2 = 7;
const uint8_t IN3 = 8;
const uint8_t IN4 = 9;
const uint8_t ENB = 10;
// Push button and indicator LED, the same as Step2_JUL
const uint8_t BUTTON_PIN = 2;
const uint8_t LED_PIN = 3;
// Circuit-1 of Article 1009 wires the indicator LED to D12:
// const uint8_t LED_PIN = 12;

// Filled by the four answers
uint8_t xPin = A1;
bool xReversed = false;
uint8_t yPin = A0;
bool yReversed = false;
L298NPins pins;

void printBits(int value)
{
    for (int b = 3; b >= 0; b--)
        Serial.print((value >> b) & 1);
}

// Prints A0 to A5 for the analog pins
void printAnalogPin(uint8_t pin)
{
    Serial.print('A');
    Serial.print(pin - A0);
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
void readLine(char *line, int size)
{
    int n = 0;
    while (true)
    {
        int c = readChar();
        if (c < 0)
            continue;
        if (c == '\r' || c == '\n')
        {
            // A CR LF pair sends two characters; skip the second
            if (n == 0 && c == '\n')
                continue;
            break;
        }
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

// Prints the prompt and reads a or b (A and B accepted).
// After any other answer only the prompt is repeated.
char askChoice()
{
    char line[8];
    while (true)
    {
        Serial.print(F("Type a or b: "));
        readLine(line, sizeof(line));
        char c = tolower(line[0]);
        if (line[1] == '\0' && (c == 'a' || c == 'b'))
            return c;
        Serial.println(F("  Type a or b."));
    }
}

// The eight equations of Step1_Joystick, lines 82 to 85 and the
// same lines with A0 and A1 exchanged
const __FlashStringHelper *xEquation(bool reversed)
{
    if (xPin == A1)
        return reversed ? F("xDigital = 1023 - analogRead(A1);")
                        : F("xDigital = analogRead(A1);");
    return reversed ? F("xDigital = 1023 - analogRead(A0);")
                    : F("xDigital = analogRead(A0);");
}

const __FlashStringHelper *yEquation(bool reversed)
{
    if (yPin == A0)
        return reversed ? F("yDigital = 1023 - analogRead(A0);")
                        : F("yDigital = analogRead(A0);");
    return reversed ? F("yDigital = 1023 - analogRead(A1);")
                    : F("yDigital = analogRead(A1);");
}

void printEquations(const __FlashStringHelper *label)
{
    Serial.print(label);
    Serial.println(xEquation(xReversed));
    Serial.print(F("          "));
    Serial.println(yEquation(yReversed));
    Serial.println();
}

// Questions 1 to 3: the results of Step1_Joystick
void askStep1()
{
    xReversed = false;
    yReversed = false;

    Serial.println(F("1. Which analog pin does x use in Step1_Joystick?"));
    Serial.println(F("  a: A1   (xDigital uses A1, yDigital uses A0)"));
    Serial.println(F("  b: A0   (xDigital uses A0, yDigital uses A1)"));
    bool xOnA0 = askChoice() == 'b';
    xPin = xOnA0 ? A0 : A1;
    yPin = xOnA0 ? A1 : A0; // the joystick uses A0 and A1 only
    Serial.print(F("  Pins:   x on "));
    printAnalogPin(xPin);
    Serial.print(F(", y on "));
    printAnalogPin(yPin);
    Serial.println();
    Serial.println();

    Serial.println(F("2. Which x equation is used?"));
    Serial.print(F("  a: "));
    Serial.println(xEquation(false));
    Serial.print(F("  b: "));
    Serial.println(xEquation(true));
    xReversed = askChoice() == 'b';
    Serial.print(F("  Result: "));
    Serial.println(xEquation(xReversed));
    Serial.println();

    Serial.println(F("3. Which y equation is used?"));
    Serial.print(F("  a: "));
    Serial.println(yEquation(false));
    Serial.print(F("  b: "));
    Serial.println(yEquation(true));
    yReversed = askChoice() == 'b';
    printEquations(F("  Result: "));
}

// The 16 Bits values in the two groups of the Step2_JUL comment
void printBitsTable()
{
    Serial.println(F("  Decimal  Binary"));
    for (int v = 0; v < 16; v++)
    {
        if (v == 0)
            Serial.println(F("  enable pins crossed (bit 3 = 0)"));
        if (v == 8)
            Serial.println(F("  enable pins straight (bit 3 = 1)"));
        Serial.print(v < 10 ? F("     ") : F("    "));
        Serial.print(v);
        Serial.print(F("      "));
        printBits(v);
        Serial.println();
    }
}

// One or two digits are read as decimal, 0 to 15; four digits of
// 0 and 1 are read as binary. Returns -1 for anything else.
int readBitsValue()
{
    char line[8];
    readLine(line, sizeof(line));
    int n = strlen(line);
    int value = 0;
    if (n == 4)
    {
        for (int i = 0; i < 4; i++)
        {
            if (line[i] != '0' && line[i] != '1')
                return -1;
            value = value * 2 + (line[i] - '0');
        }
        return value;
    }
    if (n == 1 || n == 2)
    {
        for (int i = 0; i < n; i++)
        {
            if (line[i] < '0' || line[i] > '9')
                return -1;
            value = value * 10 + (line[i] - '0');
        }
        return value <= 15 ? value : -1;
    }
    return -1;
}

void printBitsLine(int value)
{
    Serial.print(F("motors.Bits(BitsL298N::bits_"));
    printBits(value);
    Serial.println(F(");"));
}

// Question 4: the result of Step2_JUL
void askStep2()
{
    Serial.println(F("4. Which Bits value is used in Step2_JUL?"));
    // Split so that ??) is not read as a trigraph by strict C++ modes
    Serial.println(F("  motors.Bits(BitsL298N::bits_???" "?);"));
    Serial.println();
    printBitsTable();
    Serial.println();

    int value = -1;
    while (true)
    {
        Serial.print(F("Type the decimal (0 to 15) or the binary (four digits): "));
        value = readBitsValue();
        if (value >= 0)
            break;
        Serial.println(F("  Type 0 to 15, or four digits of 0 and 1."));
    }

    pins.Resolve((BitsL298N)((int)BitsL298N::bits_0000 + value));
    MotorPins left = pins.Left();
    MotorPins right = pins.Right();

    Serial.print(F("  Result: "));
    printBitsLine(value);
    Serial.print(F("          Decimal "));
    Serial.print(value);
    Serial.print(F(", binary "));
    printBits(value);
    Serial.println();
    Serial.print(F("          Left command:  EN D"));
    Serial.print(left.EN);
    Serial.print(F(", D"));
    Serial.print(left.FWD);
    Serial.print(F(" HIGH for +, D"));
    Serial.print(left.REV);
    Serial.println(F(" HIGH for -"));
    Serial.print(F("          Right command: EN D"));
    Serial.print(right.EN);
    Serial.print(F(", D"));
    Serial.print(right.FWD);
    Serial.print(F(" HIGH for +, D"));
    Serial.print(right.REV);
    Serial.println(F(" HIGH for -"));
    Serial.println();
}

// The summary; returns true for p (print), false for r (again)
bool askConfirm()
{
    Serial.println(F("Summary"));
    Serial.print(F("  "));
    Serial.println(xEquation(xReversed));
    Serial.print(F("  "));
    Serial.println(yEquation(yReversed));
    Serial.print(F("  "));
    printBitsLine(pins.GetBitsValue());
    char line[8];
    while (true)
    {
        Serial.print(F("Type p to print the program, or r to answer again: "));
        readLine(line, sizeof(line));
        char c = tolower(line[0]);
        if (line[1] == '\0' && c == 'p')
            return true;
        if (line[1] == '\0' && c == 'r')
            return false;
        Serial.println(F("  Type p or r."));
    }
}

void printIntro()
{
    char line[8];
    Serial.println(F("Step4_Generator: 4 questions about Step1_Joystick and Step2_JUL."));
    Serial.println(F("Answer each one and press Enter. Backspace corrects a typing error."));
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

void printPinName(uint8_t pin)
{
    Serial.print(pin == A0 ? F("A0") : F("A1"));
}

// Prints the Step5_Generated main.cpp for the four answers
void printProgram()
{
    MotorPins left = pins.Left();
    MotorPins right = pins.Right();
    int bits = pins.GetBitsValue();

    Serial.println(F("// ----- BEGIN main.cpp -----"));
    Serial.println(F("//"));
    Serial.println(F("// Carpenter Software"));
    Serial.println(F("// Folder: src/Step5_Generated: File: main.cpp"));
    Serial.println(F("// Drive program printed by Step4_Generator"));
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
    Serial.println(F("// STEPS 1 TO 5"));
    Serial.println(F("//   Step1_Joystick:  finds the analog pin and the direction of each"));
    Serial.println(F("//                    joystick axis (Article 1009, Joystick Setup)."));
    Serial.println(F("//   Step2_JUL:       finds the Bits() value of the L298N wiring with"));
    Serial.println(F("//                    the Motor Movement Checklist (Article 1009,"));
    Serial.println(F("//                    L298N Setup)."));
    Serial.println(F("//   Step4_Generator: asks four questions in the serial monitor about"));
    Serial.println(F("//                    the results of Step 1 and Step 2, and prints this"));
    Serial.println(F("//                    file with the answers written in as constants."));
    Serial.println(F("//   Step5_Generated: this file. It drives the robot as Step2_JUL does,"));
    Serial.println(F("//                    with the bench results fixed when it is built."));
    Serial.println(F("//"));
    Serial.println(F("// ANSWERS GIVEN TO STEP4_GENERATOR"));
    Serial.print(F("//   1. x pin:        "));
    printPinName(xPin);
    Serial.print(F(" (y on "));
    printPinName(yPin);
    Serial.println(')');
    Serial.print(F("//   2. x equation:   "));
    Serial.println(xEquation(xReversed));
    Serial.print(F("//   3. y equation:   "));
    Serial.println(yEquation(yReversed));
    Serial.print(F("//   4. Bits value:   "));
    Serial.print(bits);
    Serial.print(F(" ("));
    printBits(bits);
    Serial.print(F("), motors.Bits(BitsL298N::bits_"));
    printBits(bits);
    Serial.println(F(");"));
    Serial.print(F("//      Left command:  EN D"));
    Serial.print(left.EN);
    Serial.print(F(", D"));
    Serial.print(left.FWD);
    Serial.print(F(" HIGH for +, D"));
    Serial.print(left.REV);
    Serial.println(F(" HIGH for -"));
    Serial.print(F("//      Right command: EN D"));
    Serial.print(right.EN);
    Serial.print(F(", D"));
    Serial.print(right.FWD);
    Serial.print(F(" HIGH for +, D"));
    Serial.print(right.REV);
    Serial.println(F(" HIGH for -"));
    Serial.println(F("//"));
    Serial.println(F("// include/claude/ace.h holds everything this program needs in one"));
    Serial.println(F("// file: the joystick algorithm, the mapping and dead zone, the push"));
    Serial.println(F("// button, the timer, and the L298N pins. It includes Arduino.h only"));
    Serial.println(F("// and is never edited; a new run of Step4 changes only this file."));
    Serial.println(F("// For the same joystick readings it sets the same pin states as"));
    Serial.println(F("// Step2_JUL, with a control tick about 2.5 times faster (see ace.h)."));
    Serial.println(F("//"));
    Serial.println(F("// Build: environment env:step5 (platformio.ini), which defines"));
    Serial.println(F("// STEP5_GENERATED. In a project of its own, copy include/claude/ace.h"));
    Serial.println(F("// and remove the #ifdef line and the #endif line at the end."));
    Serial.println(F("//"));
    Serial.println(F("// SAFETY COMES FIRST (WATCH YOUR FINGERS): the motors run only while"));
    Serial.print(F("// the push button state is ON (indicator LED on D"));
    Serial.print(LED_PIN);
    Serial.println(F(")."));
    Serial.println();
    Serial.println(F("#ifdef STEP5_GENERATED"));
    Serial.println();
    Serial.println(F("#include <Arduino.h>"));
    Serial.println(F("#include \"claude/ace.h\""));
    Serial.println();
    Serial.println(F("// Carpenter Software - Jesse Carpenter"));
    Serial.println(F("using namespace csjc;"));
    Serial.println();
    Serial.println(F("// Answers 1 to 3: joystick pins and reversals (true = 1023 - analogRead)"));
    Serial.print(F("const uint8_t X_PIN = "));
    printPinName(xPin);
    Serial.println(';');
    Serial.print(F("const bool X_REVERSED = "));
    Serial.print(xReversed ? F("true") : F("false"));
    Serial.println(';');
    Serial.print(F("const uint8_t Y_PIN = "));
    printPinName(yPin);
    Serial.println(';');
    Serial.print(F("const bool Y_REVERSED = "));
    Serial.print(yReversed ? F("true") : F("false"));
    Serial.println(';');
    Serial.println();
    Serial.print(F("// Answer 4: L298N pins resolved from bits_"));
    printBits(bits);
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
    Serial.println(F("// Push button and indicator LED, as in Step2_JUL"));
    printConst(F("BUTTON_PIN"), BUTTON_PIN);
    printConst(F("LED_PIN"), LED_PIN);
    Serial.println();
    Serial.println(F("Ace<X_PIN, X_REVERSED, Y_PIN, Y_REVERSED,"));
    Serial.println(F("    LEFT_EN, LEFT_FWD, LEFT_REV,"));
    Serial.println(F("    RIGHT_EN, RIGHT_FWD, RIGHT_REV,"));
    Serial.println(F("    BUTTON_PIN, LED_PIN> robot;"));
    Serial.println();
    Serial.println(F("void setup()"));
    Serial.println(F("{"));
    Serial.println(F("    robot.begin();"));
    Serial.println(F("}"));
    Serial.println();
    Serial.println(F("void loop()"));
    Serial.println(F("{"));
    Serial.println(F("    // Button, 100 ms timer, and one control tick when the timer fires"));
    Serial.println(F("    robot.update();"));
    Serial.println(F("}"));
    Serial.println();
    Serial.println(F("#endif // STEP5_GENERATED"));
    Serial.println(F("// ----- END main.cpp -----"));
}

// All questions, the summary, and the program
void runGenerator()
{
    while (true)
    {
        askStep1();
        askStep2();
        if (askConfirm())
            break;
        Serial.println();
    }
    Serial.println();
    Serial.println(F("Copy every line between the two marker lines. The PlatformIO"));
    Serial.println(F("monitor also saves this output in a log file (log2file)."));
    Serial.println();
    printProgram();
    Serial.println(F("Type r and Enter to answer again."));
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    pins = L298NPins(ENA, IN1, IN2, IN3, IN4, ENB);

    printIntro();
    runGenerator();
}

void loop()
{
    // r prints the questions again
    if (Serial.available() > 0)
    {
        char c = Serial.read();
        if (c == 'r' || c == 'R')
        {
            Serial.println();
            runGenerator();
        }
    }
}

#endif // STEP4_GENERATOR
