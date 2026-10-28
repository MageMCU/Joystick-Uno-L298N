//
// Carpenter Software
// File: main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons
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
// Step5_MathLessons: the program of the 20 math lessons (v6.1.0,
// 20261022). Each lesson is a header file in the folder lessons/, and
// this file compiles ONE of them. Each lesson is divided into topics,
// one function per topic, and this file also selects ONE topic, or all.
//
// INSTRUCTIONS
//   1. In platformio.ini, select Step5_MathLessons in
//        build_src_filter (one folder per line since
//        v6.4.0): +<Step5_MathLessons/>, and - before the other four
//        folders.
//   2. Below, set LESSON to the number of ONE lesson, 1 to 20.
//   3. Below, set TOPIC to the number of ONE topic of that lesson, or
//      to 0 for every topic of the lesson, in order. The number of
//      topics is LESSON_TOPICS in each lesson file.
//   4. Build, upload, and open the Serial Monitor at 9600 baud. The
//      first lines name the program, the lesson, and the topic (v6.4.1);
//      another program name there means platformio.ini still selects
//      that program.
//      Lessons 1 to 16 run the selected topics once. Lessons 17 to 19
//      use the bench of Article 1004, Experiments 6 to 8; lesson 20
//      reads the joystick of Article 1009, Circuit-1, motor supply off.
//   5. Restore the Step2_JUL setting in platformio.ini before uploading
//      to the robot.
//
// TOPIC NAMES
//   A topic is one function of a lesson that demonstrates one operation
//   of one class. Its name has three fields separated by underscores:
//     LessonName_Tnn_Operation()       example: Vector3_T16_Copy()
//   LessonName is the class or subject of the lesson (Vector3), Tnn is
//   the topic number with two digits (T01 to T17), and Operation names
//   what the topic demonstrates. Each topic prints the same name as
//   its title, for example "Vector3 T16 Copy using the equal sign".
//
// WHY ONE LESSON AT A TIME
//   The ATmega328P has 32256 bytes of flash for the program (32768
//   bytes less the 512 bytes of the bootloader) and 2048 bytes of RAM.
//   Flash holds the program code. RAM holds the global variables and
//   the stack, the memory of the function calls and their local
//   variables. Text printed with Serial.print("...") is also copied
//   into RAM when the board starts; text written as F("...") stays in
//   flash.
//   The #if chain below (see COMPILER DIRECTIVES) keeps the selected
//   lesson and drops the others. Only that lesson is compiled; the others
//   use no flash and no RAM. All 20 lessons in one program would need
//   about 150 KB of flash and about 10 KB of RAM, four to five times
//   what the chip holds.
//
// COMPILER DIRECTIVES
//   A compiler directive is a line that begins with #. The
//   preprocessor, the step that reads the # lines before the compiler
//   runs, carries out the directives and passes the remaining code on.
//   This file and the lessons use five of them:
//     #define NAME value   gives NAME a value; the preprocessor puts
//                          the value wherever NAME appears.
//     #include "file"      inserts the text of the file at this line.
//     #if condition        keeps the lines up to the next #elif, #else,
//                          or #endif when the condition is true, and
//                          drops them when it is false.
//     #elif, #else, #endif the other branches and the end of an #if.
//     #error "text"        stops the build and prints the text.
//   LESSON selects one #include in the #if chain below. In the Setup()
//   of the lesson, each topic call sits inside its own #if:
//     #if TOPIC == 0 || TOPIC == 16
//         Vector3_T16_Copy();
//     #endif
//   The operator || means OR: the call is kept when TOPIC is 0 or 16.
//   The compiler never sees a call that was dropped, and the linker,
//   the step that joins the compiled code into one program, leaves out
//   every function that is never called. A single topic therefore uses
//   less flash and RAM than the whole lesson.
//
// MEMORY OF EACH LESSON (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, -Os, link
//   time optimization; all lessons rebuilt 20261025 for v6.4.1, with the
//   program title of setup() below and the new output lines of v6.4.1).
//   Built in the review environment, where the v6.4.0 code measured 20
//   bytes of flash less than in the earlier tables; pio run may show
//   about 20 bytes more. RAM matched.
//   TOPIC 0 is the whole lesson; the last two columns are the largest
//   single topic of the lesson. Flash is of 32256 bytes, RAM of 2048.
//                    Topics   TOPIC 0              One topic, largest
//   Lesson                  Flash      RAM         Flash   RAM
//   L01_Bitwise         6   6636  21%   456  22%    5034   258
//   L02_TypeConv        2   4824  15%   392  19%    4370   326
//   L03_LinearMap       3   9898  31%   328  16%    7048   236
//   L04_MiscMath        6  10114  31%   542  26%    6368   282
//   L05_RandomNumber    1   6574  20%   224  11%    6574   224
//   L06_Statistics      6  12174  38%   422  21%    8762   390
//   L07_Vector2        17  14464  45%   994  49%    7440   488
//   L08_Point2          4   7270  23%   428  21%    6346   314
//   L09_Vector3        16  15952  49%  1086  53%    8074   320
//   L10_Point3          4   7460  23%   464  23%    6420   324
//   L11_Matrix2x2      13  15012  47%   786  38%    7716   264
//   L12_Matrix3x3      15  19134  59%   810  40%   11982   376
//   L13_Matrix4x4       2   8072  25%   378  18%    7282   336
//   L14_Quaternion      9  16194  50%   494  24%   11260   252
//   L15_LineFit         3   8184  25%   338  17%    6746   274
//   L16_Rotation        5  16132  50%   246  12%    8882   234
//   L17_DeadZone        1   6762  21%  1112  54%    6762  1112
//   L18_MotorLineFit    1  11668  36%   338  17%   11668   338
//   L19_JoystickFrame   2   7526  23%   261  13%    5892   259
//   L20_JoystickMap     1   6316  20%   289  14%    6316   289
//   RAM is the global variables only; the stack needs the rest.
//   Since v5.1.0 every topic title is written as F("..."), so it stays
//   in flash: lessons 7 and 9 dropped from more than 70 percent of RAM
//   to about 52 percent. Write new text in the lessons with F("...").
//

#include <Arduino.h>

// ---------- Select ONE lesson here (1 to 20) ----------
#define LESSON 7
// ---------- Select ONE topic here (0 runs every topic) -
#define TOPIC 0
// -------------------------------------------------------

#if   LESSON == 1
#include "lessons/L01_Bitwise.h"
#define LESSON_NS L01_Bitwise
#elif LESSON == 2
#include "lessons/L02_TypeConv.h"
#define LESSON_NS L02_TypeConv
#elif LESSON == 3
#include "lessons/L03_LinearMap.h"
#define LESSON_NS L03_LinearMap
#elif LESSON == 4
#include "lessons/L04_MiscMath.h"
#define LESSON_NS L04_MiscMath
#elif LESSON == 5
#include "lessons/L05_RandomNumber.h"
#define LESSON_NS L05_RandomNumber
#elif LESSON == 6
#include "lessons/L06_Statistics.h"
#define LESSON_NS L06_Statistics
#elif LESSON == 7
#include "lessons/L07_Vector2.h"
#define LESSON_NS L07_Vector2
#elif LESSON == 8
#include "lessons/L08_Point2.h"
#define LESSON_NS L08_Point2
#elif LESSON == 9
#include "lessons/L09_Vector3.h"
#define LESSON_NS L09_Vector3
#elif LESSON == 10
#include "lessons/L10_Point3.h"
#define LESSON_NS L10_Point3
#elif LESSON == 11
#include "lessons/L11_Matrix2x2.h"
#define LESSON_NS L11_Matrix2x2
#elif LESSON == 12
#include "lessons/L12_Matrix3x3.h"
#define LESSON_NS L12_Matrix3x3
#elif LESSON == 13
#include "lessons/L13_Matrix4x4.h"
#define LESSON_NS L13_Matrix4x4
#elif LESSON == 14
#include "lessons/L14_Quaternion.h"
#define LESSON_NS L14_Quaternion
#elif LESSON == 15
#include "lessons/L15_LineFit.h"
#define LESSON_NS L15_LineFit
#elif LESSON == 16
#include "lessons/L16_Rotation.h"
#define LESSON_NS L16_Rotation
#elif LESSON == 17
#include "lessons/L17_DeadZone.h"
#define LESSON_NS L17_DeadZone
#elif LESSON == 18
#include "lessons/L18_MotorLineFit.h"
#define LESSON_NS L18_MotorLineFit
#elif LESSON == 19
#include "lessons/L19_JoystickFrame.h"
#define LESSON_NS L19_JoystickFrame
#elif LESSON == 20
#include "lessons/L20_JoystickMap.h"
#define LESSON_NS L20_JoystickMap
#else
#error "Set LESSON to a number from 1 to 20"
#endif

// Each lesson file defines LESSON_TOPICS, its number of topics.
#if TOPIC < 0 || TOPIC > LESSON_TOPICS
#error "Set TOPIC to 0 or to a topic of this lesson (its LESSON_TOPICS)"
#endif

// v6.4.1: the program title, printed before the lesson starts, names
// the program, the lesson, and the topic, so the serial monitor shows
// which program platformio.ini selected. STEP5_TEXT() turns a name
// into text: #x is the preprocessor stringizing operator, and the two
// steps let LESSON_NS be replaced by its value before #x is applied.
#define STEP5_TEXT2(x) #x
#define STEP5_TEXT(x) STEP5_TEXT2(x)

void setup()
{
    // SAFETY: the L298N pins D5 to D10 as outputs and LOW before the
    // title is printed, as lessons 17 to 20 do first in their Setup(),
    // so the L298N inputs do not float while the title is sent.
    for (int pin = 5; pin <= 10; pin++)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println();
    Serial.println(F("................................................"));
    Serial.println(F( \
        "Step5_MathLessons: lesson " STEP5_TEXT(LESSON) \
        " (" STEP5_TEXT(LESSON_NS) "), topic " STEP5_TEXT(TOPIC) \
        " (0: every topic)"));
    Serial.println(F("Selected in platformio.ini: +<Step5_MathLessons/>"));
    // send the title before the lesson calls Serial.begin() again
    Serial.flush();
    LESSON_NS::Setup();
}

void loop()
{
    LESSON_NS::Loop();
}
