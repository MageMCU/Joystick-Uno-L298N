# Step5_MathLessons

Math lessons, namespace **csjc** ([Carpenter Software](https://carpentersoftware.com), Jesse Carpenter).

This folder holds the test programs of the MageMCU **Numerics** repository (Algebra, last updated 20241202), merged into Joystick-Uno-L298N on 20261008 as lessons 01 to 14, plus lessons 15 and 16, which use code adapted from David Eberly's Geometric Tools Engine (see Credits), and the hardware lessons 17 to 19 of Article 1004, Experiments 6 to 8, and lesson 20 (v6.1.0), the full range and two segment maps on the live joystick, which follows the Step1_Joystick self test (Article 1009, Step1, The Joystick Self Test). The lessons use the math headers in `Code-JUL/include/numerics/` and the print helpers in `Code-JUL/include/Debug.h`.

## Quick Use (PlatformIO)

1. Open the folder `Code-JUL/` in VS Code (not the repository root).
2. In `platformio.ini`, select Step5_MathLessons with `build_src_filter` (one folder per line since v6.4.0):
   ```
   build_src_filter =
       +<*>
       -<Step1_Joystick/>
       -<Step2_JUL/>
       -<Step3_Generator/>
       -<Step4_Generated/>
       +<Step5_MathLessons/>
       -<Step6_Circuit/>
   ```
3. In `main.cpp` of this folder, set `#define LESSON` to the number of ONE lesson, 1 to 20.
4. On the line below it, set `#define TOPIC` to the number of ONE topic of that lesson, or to 0 for every topic, in order (since v5.1.0).
5. Build, upload, and open the Serial Monitor at 9600 baud. The first lines name the program, the lesson, and the topic (since v6.4.1), for example `Step5_MathLessons: lesson 7 (L07_Vector2), topic 13`; another program name there means `platformio.ini` still selects that program. Lessons 1 to 16 run the selected topics once, from `Setup()`; lessons 17 to 19 use the bench of Article 1004, Experiments 6 to 8; lesson 20 reads the joystick of Article 1009, Circuit-1, with the motor supply off.
6. Restore the Step2_JUL setting before uploading to the robot.

## One Lesson at a Time (since v5.0.0)

The ATmega328P has 32256 bytes of flash for the program and 2048 bytes of RAM. The 20 lessons together would need about 150 KB of flash and about 10 KB of RAM, so `main.cpp` compiles one lesson only. The preprocessor, the step that reads the `#` lines before the compiler runs, keeps one branch of the `#if` chain of `main.cpp` and drops the others; the lessons not selected use no flash and no RAM. A number outside 1 to 20 stops the build with `#error`. The comments of `main.cpp` give the instructions and the flash and RAM of each lesson.

Each lesson is a header file in `lessons/` with a namespace of the same name, for example `L07_Vector2.h` and `namespace L07_Vector2`. The namespace keeps the names of one lesson apart from the others; `main.cpp` calls `Setup()` from `setup()` and `Loop()` from `loop()`. Up to v4.0.1 each lesson was a folder with its own `main.cpp` (`07_Vector2/main.cpp`), selected with a sixth entry of `build_src_filter`.

## One Topic at a Time (since v5.1.0)

A lesson printed all of its tests in one run, up to 17 in lesson 7, more than a reader can follow on the Serial Monitor. Each lesson is now divided into **topics**: a topic is one function of the lesson that demonstrates one operation of one class. `#define TOPIC` in `main.cpp`, the line below `#define LESSON`, selects one topic; `TOPIC 0` runs every topic, in order, as before.

**Topic names.** `LessonName_Tnn_Operation()`, three fields separated by underscores:

| Field | Rule | Example |
|---|---|---|
| LessonName | The class or subject of the lesson | `Vector3` |
| Tnn | Topic number, two digits, in the order of the calls in `Setup()` | `T16` |
| Operation | What the topic demonstrates, in PascalCase without underscores | `Copy` |

Example: `Vector3_T16_Copy()`, the 16th topic of lesson 9, prints the title `Vector3 T16 Copy using the equal sign`. Every topic number is used once in its lesson, and the title of each topic carries the same lesson name and topic number as its function.

**Compiler directives.** Each topic call in `Setup()` sits inside its own `#if`:

```cpp
#if TOPIC == 0 || TOPIC == 16
    Vector3_T16_Copy();
#endif
```

The preprocessor keeps the call when TOPIC is 0 or 16 and drops it otherwise. The linker leaves out every function that is never called, so one topic uses less flash and RAM than the whole lesson (the table in the comments of `main.cpp`). Each lesson defines `LESSON_TOPICS`, its number of topics, and `main.cpp` stops the build with `#error` when TOPIC is below 0 or above that number. Lessons 17 and 18 are one topic each, the bench program of `Setup()` and `Loop()`; TOPIC 0 and 1 both run it, and their `LESSON_TOPICS` is at the end of the file so that the line numbers cited by the lab cards do not change. The lab cards name the lines they cite (the `analogRead()` lines, the Button lines) instead of giving line numbers (v6.8.0), so added lines do not make a citation wrong. Lesson 19 has two topics: `JoystickFrame_T01_RotationChecks()` (Part 1) and `JoystickFrame_T02_LiveJoystick()` (Part 2, called from `Loop()`).

The renamed functions of v5.1.0 (old name, new name) are listed in `RELEASES.md`, v5.1.0.

## Layout

```
Code-JUL/src/Step5_MathLessons/
├── README.md                    This file
├── CodeChangeLog.md             Change log of the original Numerics repository
├── main.cpp                     Selects ONE lesson (#define LESSON 1 to 20) and ONE topic (#define TOPIC, 0 for all)
└── lessons/
    ├── L01_Bitwise.h             6 topics
    ├── L02_TypeConv.h            2 topics
    ├── L03_LinearMap.h           3 topics (T03, the two segment map, v6.1.0, self checking)
    ├── L04_MiscMath.h            6 topics
    ├── L05_RandomNumber.h        1 topic
    ├── L06_Statistics.h          6 topics
    ├── L07_Vector2.h            17 topics
    ├── L08_Point2.h              4 topics
    ├── L09_Vector3.h            16 topics
    ├── L10_Point3.h              4 topics
    ├── L11_Matrix2x2.h          13 topics
    ├── L12_Matrix3x3.h          15 topics
    ├── L13_Matrix4x4.h           2 topics
    ├── L14_Quaternion.h          9 topics
    ├── L15_LineFit.h             3 topics, self checking
    ├── L16_Rotation.h            5 topics, self checking
    ├── L17_DeadZone.h            1 topic: joystick at rest, Article 1004 Experiment-6 (hardware; any key repeats)
    ├── L18_MotorLineFit.h        1 topic: motor calibration, Article 1004 Experiment-7 (hardware; n starts a new set)
    ├── L19_JoystickFrame.h       2 topics: rotated joystick frame, Article 1004 Experiment-8 (4 checks plus hardware)
    └── L20_JoystickMap.h         1 topic: full range and two segment maps on the live joystick (hardware, v6.1.0; since v7.0.0 all six values of `include/JoystickMeasurements.h`; up to v6.8.0 the four low and high values were copied from a Step1_Joystick report and, since v6.4.1, the centers read from `include/JoystickCenter.h`)
```

Each lesson header holds the topic functions of one class, moved from the original `TestClass.h` file, and a `Setup()` that calls them in order of their topic number, each call inside an `#if` on TOPIC. Since v5.1.0 the functions carry the topic names above and print their titles with `F("...")`; their code is otherwise unchanged. The Button and Timer tests of the original repository were not carried over; those classes are studied in Experiment-1.

## Known Items for Review

- Lessons 01 to 14 print values but do not compare them with expected values; lessons 15 and 16 show the self checking form (expected, observed, PASS or FAIL).
- Lesson 16 relates to Article 1005, Study of Quaternions (20221207); conventions should be checked against the article.

## Credits

Lessons 15, 16, and 18 use code adapted from the Geometric Tools Engine by **David Eberly**, Geometric Tools (https://www.geometrictools.com, https://github.com/davideberly/GeometricTools), distributed under the Boost Software License, Version 1.0:

- `include/numerics/LineFit2.h`, adapted from GTE/Mathematics/ApprHeightLine2.h (lessons 15 and 18)
- `include/numerics/Rotation.h`, adapted from GTE/Mathematics/Rotation.h and Slerp.h (lesson 16)

Each file carries David Eberly's copyright notice, the Boost license reference, and an adaptation clause listing the changes. The matrix inverse and quaternion inverse fixes follow the approach of GTE Matrix2x2.h, Matrix3x3.h, and Quaternion.h, credited in those headers. These adaptations are not endorsed by David Eberly or Geometric Tools.

## Disclaimer and License

MIT License. See the repository [`LICENSE`](../../../LICENSE) and [`DISCLAIMER.md`](../../../DISCLAIMER.md). The original Numerics repository carried an MIT License, Copyright (c) 2022, Carpenter Software. The portions adapted from the Geometric Tools Engine remain under the Boost Software License, Version 1.0 (https://www.boost.org/LICENSE_1_0.txt).
