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
//   1. In platformio.ini, select Step5_MathLessons on line 31:
//        build_src_filter = +<*> -<Step1_Joystick/> -<Step2_JUL/>
//          -<Step3_Generator/> -<Step4_Generated/> +<Step5_MathLessons/>
//      (one line in platformio.ini; it is shown here on two lines).
//   2. Below, set LESSON to the number of ONE lesson, 1 to 20.
//   3. Below, set TOPIC to the number of ONE topic of that lesson, or
//      to 0 for every topic of the lesson, in order. The number of
//      topics is LESSON_TOPICS in each lesson file.
//   4. Build, upload, and open the Serial Monitor at 9600 baud.
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
// MEMORY OF EACH LESSON (avr-gcc 7.3.0, -Os, built 20261022, v6.1.3;
//   lessons 7 to 10, 12, 13, and 14 rebuilt for v6.3.0; lessons 3, 4,
//   11, and 13 for v6.3.1)
//   TOPIC 0 is the whole lesson; the last two columns are the largest
//   single topic of the lesson. Flash is of 32256 bytes, RAM of 2048.
//                    Topics   TOPIC 0              One topic, largest
//   Lesson                  Flash      RAM         Flash   RAM
//   L01_Bitwise         6   5460  16%   446  21%    4050   370
//   L02_TypeConv        2   4116  12%   392  19%    3702   326
//   L03_LinearMap       3   9106  28%   328  16%    6552   286
//   L04_MiscMath        6   9184  28%   542  26%    5784   412
//   L05_RandomNumber    1   5956  18%   224  10%    5956   224
//   L06_Statistics      6  10810  33%   436  21%    8064   390
//   L07_Vector2        17  12152  38%  1058  51%    6902   488
//   L08_Point2          4   6770  21%   452  22%    5848   340
//   L09_Vector3        16  15436  48%  1086  53%    7536   488
//   L10_Point3          4   6960  22%   464  22%    5918   324
//   L11_Matrix2x2      13  14428  45%   786  38%    7234   348
//   L12_Matrix3x3      15  18098  56%   810  40%    9562   376
//   L13_Matrix4x4       2   7592  24%   378  18%    6780   336
//   L14_Quaternion      9  14936  46%   584  29%    8968   332
//   L15_LineFit         3   7446  23%   338  16%    6158   274
//   L16_Rotation        5  15026  46%   238  11%    8024   238
//   L17_DeadZone        1   5842  18%  1112  54%    5842  1112
//   L18_MotorLineFit    1   9798  30%   338  16%    9798   338
//   L19_JoystickFrame   2   7122  22%   261  12%    5522   259
//   L20_JoystickMap     1   5838  18%   289  14%    5838   289
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
#error "Set TOPIC to 0 or to a topic number of this lesson (LESSON_TOPICS in the lesson file)"
#endif

void setup()
{
    LESSON_NS::Setup();
}

void loop()
{
    LESSON_NS::Loop();
}
