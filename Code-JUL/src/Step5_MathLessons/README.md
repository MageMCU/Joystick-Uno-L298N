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
    └── L20_JoystickMap.h         1 topic: full range and two segment maps on the live joystick (hardware, v6.1.0; the four low and high values of a Step1_Joystick report, and since v6.4.1 the two centers of `include/JoystickCenter.h`)
```

Each lesson header holds the topic functions of one class, moved from the original `TestClass.h` file, and a `Setup()` that calls them in order of their topic number, each call inside an `#if` on TOPIC. Since v5.1.0 the functions carry the topic names above and print their titles with `F("...")`; their code is otherwise unchanged. The Button and Timer tests of the original repository were not carried over; those classes are studied in Experiment-1.

## Merge Notes (20261008)

> **Renumbered 20261017.** The dated notes below use the folder names of their date: Step1_Joystick (removed 20261017), Step2_JUL (now Step1_JUL), and Step3_MathLessons (now this folder, Step4_MathLessons). "Step1 and Step2" in these notes means those two drive programs. Renumbered again 20261021 (v4.0.0): this folder is Step5_MathLessons, the drive program is Step2_JUL, and Step1_Joystick is a new joystick connection check (a self test since v6.0.0), not the program of these notes.

- The program code that Step1 and Step2 compile was not changed: their Intel HEX files are byte for byte identical to commit f2307a1. Where a Numerics header already existed in Code-JUL (`Bitwise.h`, `TypeConv.h`, `LinearMap.h`, `MiscMath.h`, `Vector3.h`, `Button.h`, `Timer.h`), the lessons use the Code-JUL version.
- Two lessons were adjusted to the Code-JUL headers: `01_Bitwise` defines its own `ReverseBits()` (a member of the Numerics Bitwise class only), and `02_TypeConv` uses the return value of `BytesToWord()` and `BytesToDWord()` in place of `GetWord()` and `GetDWord()`.
- `Debug.h`: the `Debug()` overloads with one to three values are defined in `numerics/MiscMath.h`; `Debug.h` adds the four and five value overloads and the print helpers.
- Not merged: `TypeConv::FloatTo5Bytes()` of Numerics, which calls `_floatToBytes()`, a function declared but never defined; the archived `Joystick` and `L298N` text files. The `BusI2C` files are set aside for a later article.

## Bug Fixes (20261008)

Each fix is marked `FIXED 20261008` in the header. Most are in the ten headers added from Numerics, which Step1 and Step2 do not include. `Vector3.h` is included by Step1 and Step2 (through `Headers.h` and `MiscMath.h`), and two of its functions, `Angle()` and `ProjV()`, were corrected; neither function is called by Step1 or Step2, so their compiled code is unchanged. The code of `Bitwise.h`, `LinearMap.h`, `MiscMath.h`, and `TypeConv.h` is unchanged; their edge cases are marked `REVIEW 20261008` and are left as lesson exercises.

| Header | Fix |
|---|---|
| Matrix3x3.h | `Solve(b)` returns the solution of A x = b (it returned A × b) |
| Matrix2x2.h, Matrix3x3.h | `Inverse()` of a singular matrix returns the zero matrix (it returned the identity); optional `Inverse(&ok)` reports invertibility; row and col are `int` |
| Matrix3x3.h | `Cramer()` checks for a zero determinant; `m_swapRows()` comma operator corrected; `m_col()` initialized |
| Matrix4x4.h | Constructors from Matrix2x2 and Matrix3x3 fill the new matrix (they left it uninitialized); `Translation()` and `Rotation()` are defined as members (the free functions remain) |
| Matrix.h, Matrix3x3.h, Matrix4x4.h, Quaternion.h, Point2.h, Point3.h | Unused inheritance removed. Sizes on the Uno: Quaternion 76 to 16 bytes, Matrix2x2 92 to 16, Matrix3x3 128 to 36, Matrix4x4 192 to 64, Point2 18 to 10, Point3 28 to 14 |
| Quaternion.h | `GetAxis()` compiles; `NormDeviation()` is two sided again; `Multiply()` and `operator*` renormalize only products that drifted from unit length (within 0.01), so (2)(2) = 4; `GetRadianAngle()` clamps w; `Inverse()` and `UnitQuaternion()` handle zero; `Element()` bounds check; new `Rotate(v)` |
| Vector2.h, Vector3.h | `Angle()` clamps before `acos()`; `ProjV()` handles a zero vector; `DotPerp()` uses `real` |
| RandomNumber.h | Seeds once, at the first call; returns real values in [min, max) (bounds were truncated to integers). FIXED 20261012: the divisor is 2^24, so the fraction can no longer round up to 1 and return max |
| Statistics.h | Quicksort uses a fixed 64 entry stack (no variable length array); empty and one value sets handled. The constructor still sorts the caller's array in place (documented) |
| 06_Statistics lesson | `const int size` (the array was a variable length array) |

## Verification (20261008)

- Desktop tests against reference values: every function listed above, 2000 random rotations (quaternion to matrix and back, and R × v = q.Rotate(v)), slerp, and the line fit. All pass.
- AVR build (avr-gcc 7.3.0, `-Wall -Wextra -Wvla`): all 16 lessons compile with no warnings.
- AVR simulation (simavr, ATmega328P at 16 MHz): every lesson ran to its last test with no reset; lessons 15 and 16 report `Failures: 0`.
- Step1_Joystick and Step2_JUL: Intel HEX byte for byte identical to commit f2307a1.
- 20261012: all 19 lessons, Step1_Joystick, Step2_JUL, and every Experiment 1 to 5 lab compiled with avr-gcc 7.3.0 and ArduinoCore-avr 1.8.6 (`-Os`, `-Wall -Wextra`); the only warnings are the two unused variables of Step1_Joystick when `DEBUG_MAIN` is off. Lessons 15, 16, and 19 (Part 1) report `Failures: 0` in simavr. Sizes from PlatformIO may differ slightly with its core version; the table below gives the sizes of 20261019, lessons 17 to 19 included.

Sizes measured 20261019 (v3.2.1), avr-gcc 7.3.0 and ArduinoCore-avr 1.8.6, `-Os`, core linked as an archive, without link time optimization; Program is flash (code and initialized data), Data is RAM before the program runs. The sizes recorded on 20261012 were smaller for most lessons; PlatformIO may report slightly different sizes with its own core version.

This table is a record of v3.2.1; the current sizes of every lesson, for TOPIC 0 and for the largest single topic, are in the comments of `main.cpp` (updated for v6.3.1). The table uses the folder names of v3.2.1; since v5.0.0 the lessons are `lessons/L01_Bitwise.h` to `lessons/L19_JoystickFrame.h`, with the same code.

| Lesson | Program (bytes) | Data (bytes) |
|---|---|---|
| 01_Bitwise | 6140 | 592 |
| 02_TypeConv | 4750 | 442 |
| 03_LinearMap | 6886 | 366 |
| 04_MiscMath | 10198 | 696 |
| 05_RandomNumber | 6502 | 256 |
| 06_Statistics | 11754 | 578 |
| 07_Vector2 | 13614 | 1490 |
| 08_Point2 | 6942 | 570 |
| 09_Vector3 | 17024 | 1444 |
| 10_Point3 | 7220 | 582 |
| 11_Matrix2x2 | 14962 | 1114 |
| 12_Matrix3x3 | 19266 | 1236 |
| 13_Matrix4x4 | 6716 | 386 |
| 14_Quaternion | 15224 | 822 |
| 15_LineFit | 8252 | 440 |
| 16_Rotation | 15596 | 492 |
| 17_DeadZone | 6956 | 1114 |
| 18_MotorLineFit | 10730 | 338 |
| 19_JoystickFrame | 7860 | 261 |

- 20261018 (v3.2.0): `Common.h` ships with every debug flag on for Step2_JUL. Lessons 18 and 19 define `DEBUG_ALL_OFF` before their includes, so they build without the flags, with the 100 ms tick of lesson 18, and print only their own output (Intel HEX identical to a build with the flags commented out). Lessons 17 and 19 read the joystick as Step2_JUL does since v3.1.0, `xDigital = analogRead(A0)` and `yDigital = analogRead(A1)` (Discrepancies.md, 68). Lesson 18 turns the internal pull up of D2 off after `button.begin()`, as Step2_JUL does; the joystick switch requires the external 10 kOhm pull up from D2 to 5 V.

The Uno has 2048 bytes of RAM. Data is the RAM used before the program runs; in lessons 07, 09, 11, and 12 most of it is text printed by the tests (held in RAM because it is passed as `String`). Lessons 15 and 16 keep their text in program memory with `F()`.

- 20261021 (v5.0.0): the lessons moved into `lessons/` as headers, selected by one `main.cpp`. Built through `main.cpp` with avr-gcc 7.3.0 and ArduinoCore-avr 1.8.6 (`-Os -Wall -Wextra`, with link time optimization as `pio run` uses): every lesson builds with no warnings; 16 lessons build to the same Intel HEX as the folders of v4.0.1, and lessons 06, 11, and 14 to the same instructions in each function, placed in a different order in flash (Discrepancies.md, 128). Without link time optimization, `main.cpp` adds 4 to 8 bytes of flash, one jump from `setup()` and from `loop()` into the lesson. The flash and RAM of each lesson are in the comments of `main.cpp`; they are smaller than the table above, which was built without link time optimization.

- 20261021 (v5.1.0): topics. Built through `main.cpp` with avr-gcc 7.3.0 and ArduinoCore-avr 1.8.6 (`-Os -Wall -Wextra`, link time optimization): every lesson with TOPIC 0 and with each of its topic numbers, 134 programs, builds with no warnings; TOPIC 18 for lesson 7 and TOPIC -1 stop the build with the `#error` of `main.cpp`. Lessons 17 and 18 build to the same Intel HEX as in v5.0.0 with TOPIC 0 and TOPIC 1. In simavr, the output of every lesson with TOPIC 0 matches v5.0.0 line for line except the titles and the label Unary Minus of lessons 11 and 12; lessons 03, 06, and 12 print random values, which differ from run to run. Each single topic prints the same lines as its part of the TOPIC 0 output, apart from the random values and the sign of a value printed as -0.0000 or 0.0000 in lessons 16 and 19; lessons 15, 16, and 19 print `Failures: 0` in every run. The titles are written as `F("...")`, so they stay in flash: with TOPIC 0 the RAM of lesson 7 drops from 1490 to 1058 bytes and of lesson 9 from 1444 to 1078. One topic needs at most 9564 bytes of flash and 488 bytes of RAM in lessons 1 to 16; the table of `main.cpp` gives each lesson.
- 20261022 (v6.1.0): lesson 3 gains topic T03, `LinearMap_T03_TwoSegment()`, the two segment map around a measured center (self checking, `Failures: 0` in simavr), and lesson 20, `L20_JoystickMap.h`, compares the full range map of Step2_JUL (with its dead zone) and the two segment map on the live joystick, from the six values of a Step1_Joystick report. Each output of lesson 20 starts with a dotted line. Lessons 18 and 19 define no debug switch since v6.0.0 (the line that defined `DEBUG_ALL_OFF` is a comment of the same length). Built through `main.cpp` with avr-gcc 7.3.0 and ArduinoCore-avr 1.8.6 (`-Os -Wall -Wextra`, link time optimization) with no warnings; flash and RAM in `main.cpp`.
- 20261022 (v6.1.1): teaching comments. Each lesson opens with `TEACHING NOTES (v6.1.1)` (in lessons 17 to 19 at the end of the file, so the lines cited by the lab cards stay), and each topic function names its expected output; the numerics headers in `Code-JUL/include/numerics/` define the terms. Comments only: every lesson and topic builds to the same Intel HEX as in v6.1.0.
- 20261022 (v6.1.2): lesson 12, topics 8 and 15, call `A.Solve(b)` (they called `Ainv.Solve(b)`, which returned A b); lesson 13, topic 2, translates two points with `Translation()` (it printed its title only). Checked in simavr.
- 20261022 (v6.1.3): lesson 6, topic 1, prints the array size as `10.00` (it printed `1010`, the int in base 2). Checked in simavr.
- 20261022 (v6.3.0): teaching blocks. Above every topic function, a block names the hint (the last word or phrase of the topic name, `LessonName_Tnn_Hint`), the purpose, what is learnt (terms defined at first use: declaration, instantiation, constructor, getter, setter, overload, and so on), and the expected output; in lessons 17 to 19 the blocks are at the end of the file, so the lines cited by the lab cards stay. Code was added, never removed: getters and setters in topic 1 of lessons 7, 8, 9, 10, 13, and 14 (lesson 13 also the `Matrix4x4(Matrix2x2)` constructor, lesson 14 the pure quaternion constructors), `GetElement(row, col)` in lesson 12, topic 2, and the copy assignment `v3 = v1;` in lesson 7, topic 17, and lesson 9, topic 16. Built with avr-gcc 7.3.0 with `-std=gnu++11` and `-std=gnu++17` (`-Wall -Wextra`): every lesson with every topic, no warnings; the 16 changed builds print every line of v6.2.3 in the same order, plus the new lines (simavr); all other builds give the same Intel HEX as v6.2.3.
- 20261022 (v6.3.1): lesson 3, topic 3, prints its table in columns of fixed width with `dtostrf()` (tabs up to v6.3.0); lesson 11, topic 13, and lesson 13, topic 2, call `Rotation()` and `Translation()` on a finished identity matrix `I` (they called them on the matrix being declared). Checked in simavr; all other builds give the same Intel HEX as v6.3.0.
- 20261025 (v6.4.1): every input a topic uses is printed, with a correct label (author's review of v6.4.0.a: lesson 7, topic 13, did not print the scalar 3). Code was added, never removed; wrong or unclear labels were corrected. Lesson 1, topic 6, prints a and its reverse with labels and adds the same bits in an `unsigned int` (45568 does not fit in an `int`, which stores -19968); lesson 2 names each byte, in decimal and hex; lessons 3, 5, and 6 print the map and the random intervals, and lesson 6, topic 5, the starting array and the outlier written by `QueueReset()`; lesson 4 names the columns of topics 2 to 5 and prints the input of topic 6; lesson 7 prints the scalar of topic 13 and the cross product of topic 9, and labels topic 8 `mag = v2.Magnitude()`; lesson 8 names the vector `v`; lesson 11 labels the matrix of topic 2 and prints the 30 degree angle of topic 13; lesson 12 prints the index of topic 2, det M in topics 6 and 7, the three 45 degree angles of topic 14, and the ranges and det A of topic 15 (with a line when A is not invertible); lesson 14 names the columns and the angles, separates every label from its values, and prints the axis in topics 8 and 9 (topic 9 reads it back with `GetAxis()`); lesson 15 prints the data of each fit; lesson 16 prints its quaternions; lesson 17 prints the centers of `include/JoystickCenter.h`, the average in ADC counts, and the offset about the file center; lesson 18 echoes each count and prints the five PWM and RPM pairs; lesson 19 prints the mount angle and the ADC counts, and its check labels name the input vectors; lesson 20 takes its centers from `include/JoystickCenter.h` and prints its constants. `main.cpp` holds D5 to D10 LOW, then prints the program title before the lesson starts. Every expected output block was updated. Built with avr-gcc 7.3.0 with `-std=gnu++11` and `-std=gnu++17` (`-Wall -Wextra`): every lesson with every topic, no warnings, the same sizes under both standards; flash and RAM in `main.cpp`. In simavr, every expected output line matches; lessons 3, 15, 16, and 19 print `Failures: 0`; lesson 18 was run with five typed counts.

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
