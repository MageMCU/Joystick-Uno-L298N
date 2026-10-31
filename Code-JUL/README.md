# Joystick-Uno-L298N (JUL), Code-JUL Folder

Drive software. Namespace **csjc** (Carpenter Software, Jesse Carpenter).

## Quick Use (PlatformIO)

1. Open VS Code.
2. Open this folder, `Code-JUL/`, as the project (File, Open Folder).
3. Let PlatformIO load `platformio.ini`.
4. Connect the Arduino Uno by USB.
5. **Set the serial port (required).** In `platformio.ini`, remove the comment mark from one `upload_port` line and the `monitor_port` line and change both to the port of your computer (`pio device list` prints the ports). The upload does not work with the port left to automatic detection.
6. Click PlatformIO **Upload** to build and upload the program.

### Important

- Open the `Code-JUL/` folder itself in VS Code, not the repository root.
- If build errors mention the project structure or source filters, reopen VS Code with only `Code-JUL/` selected.

## Selecting a Program

`platformio.ini` compiles one `src/` folder at a time through `build_src_filter`. A leading `+` includes a folder and a leading `-` excludes it. **Wire once.** Complete every connection of Article 1009, Circuit-1, before Step 1; Step1_Joystick to Step4_Generated use this one wiring unchanged, and every correction is made in software.

Every file follows the coding rules of the repository `README.md` (Coding Rules): lines of 80 characters at most and each comment above its statement.

The shipped setting selects Step1_Joystick, the joystick self test (Article 1009, Step1, The Joystick Self Test):

```
build_src_filter =
    +<*>
    +<Step1_Joystick/>
    -<Step2_JUL/>
    -<Step3_Generator/>
    -<Step4_Generated/>
    -<Step5_MathLessons/>
    -<Step6_Circuit/>
```

Since v6.4.0 the filter is written one folder per line. To select another program, give its line the sign `+` and the other five folder lines the sign `-`; `+<*>` stays as written. Up to v6.3.1 the filter was one line, copied from the notes below it.

Step2_JUL, the diagnostic program that also drives (L298N Setup and Simple Drive):

```
build_src_filter =
    +<*>
    -<Step1_Joystick/>
    +<Step2_JUL/>
    -<Step3_Generator/>
    -<Step4_Generated/>
    -<Step5_MathLessons/>
    -<Step6_Circuit/>
```

Renumbered 2026-10-17: Step1_Joystick was removed, and Step2_JUL became Step1_JUL. Renumbered again 2026-10-18 (v3.1.0), in the order of use: Step2_Generator (formerly Step3_Generator, before that Step4_Generator), Step3_Generated (formerly Step4_Generated, before that Step5_Generated), and Step4_MathLessons (formerly Step2_MathLessons, before that Step3_MathLessons). Renumbered again 2026-10-21 (v4.0.0): Step1_Joystick is new, and the others move up one number, to Step2_JUL, Step3_Generator, Step4_Generated, and Step5_MathLessons. Since v5.0.0 the math lessons are selected the same way, with one more step: select Step5_MathLessons, then set `#define LESSON` (1 to 20, since v6.1.0) in `src/Step5_MathLessons/main.cpp`, which compiles one lesson only, and, since v5.1.0, `#define TOPIC` on the line below it, which runs one topic of that lesson, or every topic with 0 (see `src/Step5_MathLessons/README.md`):

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

Step3_Generator and Step4_Generated are selected the same way (since v3.0.1; up to v3.0.0 they had their own environments, `env:step3` and `env:step4`, and build flags). Step3_Generator:

```
build_src_filter =
    +<*>
    -<Step1_Joystick/>
    -<Step2_JUL/>
    +<Step3_Generator/>
    -<Step4_Generated/>
    -<Step5_MathLessons/>
    -<Step6_Circuit/>
```

Step4_Generated:

```
build_src_filter =
    +<*>
    -<Step1_Joystick/>
    -<Step2_JUL/>
    -<Step3_Generator/>
    +<Step4_Generated/>
    -<Step5_MathLessons/>
    -<Step6_Circuit/>
```

Step6_Circuit, the test of Circuit-4 (Article 1009, Appendix C), since v7.3.0 (20261030). Circuit-4 and Step6_Circuit are used with each other ONLY: the other programs do not set D4, so on Circuit-4 they leave the motor supply off. Select ONE test with `#define STEP6_CIRCUIT` (shipped, the motors stopped) or `#define STEP6_MOTORS` (the motor test, after the circuit test passes) in `src/Step6_Circuit/main.cpp`:

```
build_src_filter =
    +<*>
    -<Step1_Joystick/>
    -<Step2_JUL/>
    -<Step3_Generator/>
    -<Step4_Generated/>
    -<Step5_MathLessons/>
    +<Step6_Circuit/>
```

The PlatformIO monitor also saves its output in a log file in this folder (`monitor_filters = default, log2file`), so the program printed by Step3_Generator can be copied from the file. The `upload_port` and `monitor_port` lines are required since v3.2.0 (Quick Use, step 5); `platformio.ini` lists an example for macOS, Linux, the Raspberry Pi, and Windows.

## Setup with One Bits() Value

Whatever the joystick orientation and the L298N connections, one four digit `Bits()` value (the Bits() line of Step2_JUL, found with the Motor Movement Checklist) corrects the motor movement of a working bench. The two joystick lines, `xDigital = analogRead(A0)` and `yDigital = analogRead(A1)` since v3.1.0, stay as written; Step3_Generator uses the same two pins. Exchanging or reversing a joystick axis only swaps or negates the two motor commands, which bits 2, 1, and 0 undo; bit 3 corrects crossed enable pins. All 128 combinations of 8 joystick orientations and 16 L298N wirings were checked in simulation; each has exactly one passing value (see `../Motor-Movement-Checklist/ReadMe.md`). The connection rules are listed at the end of `src/Step2_JUL/main.cpp`: D5 and D10 to ENA and ENB, either way; D6 and D7 together on one IN pair and D8 and D9 on the other, either order; each motor on one output pair. Faults the value cannot correct, such as an open wire, a dead axis, or a floating D2, are found first with Step1_Joystick (Article 1009, Step1, The Joystick Self Test), with the motor supply off.

## Simple Drive and Fast Drive (v3.2.0; named in v6.5.0)

Step2_JUL ships with both debug switches on (`DEBUG_STEP2_JOYSTICK` and `DEBUG_STEP2_L298N`, at the top of `src/Step2_JUL/main.cpp`), so L298N Setup and the Motor Movement Checklist (Article 1009) can read the whole signal chain in the Serial Monitor; its motors respond once every 3 s. Pressing the push button OFF stops the motors at once, in every mode (v6.2.3). Once the `Bits()` value is found, the robot is driven with Simple Drive or Fast Drive (named in v6.5.0; Path A and Path B up to v6.4.1). Simple Drive is the recommended one: Step2_JUL is a complete drive program, and its code, written with the classes of the series, also serves as a teaching guide. Fast Drive is optional and advanced: its program is compact and harder to read. "Fast" refers to the control tick, not to the speed of the robot.

| Drive | What to do | Control tick |
|---|---|---|
| Simple Drive, Step2_JUL | Comment out the two debug switches of Step2_JUL (`DEBUG_STEP2_JOYSTICK` and `DEBUG_STEP2_L298N`), then upload Step2_JUL again | 100 ms |
| Fast Drive, Step3_Generator and Step4_Generated (optional, advanced) | With the motor supply off, run Step3_Generator with the `Bits()` value, copy the printed program into `Step4_Generated/main.cpp`, and upload it (`include/claude/ace.h`, no `Common.h`); apply the motor supply after the upload | 45 ms |

Both drives use the octant algorithm of Joystick.h. Simple Drive (Step2_JUL) keeps the center 511 and the dead zones X_OFFSET 0.05 and Y_OFFSET 0.06, so dead zones changed in Experiment-6 apply to Simple Drive only. Since v7.0.0 Fast Drive corrects each axis at the center and at both ends with THE JOYSTICK EQUATIONS of `ace.h`, from the six values of `include/JoystickMeasurements.h` that Step3_Generator writes into Step4_Generated, with a dead zone of 25 counts (`DEAD_ZONE`), so for the same readings the two drives may give different commands (up to v6.3.1 they gave the same; from v6.4.0 they differed for a joystick center other than 511). After new measurements are copied into the file, run Step3_Generator again. Article 1009 gives both procedures step by step (Step2, Simple Drive and Fast Drive; Step3; Step4). Fast Drive also leaves the serial monitor free: `DEBUG_GENERATED` prints once at startup and may stay on.

## `include/`, Header Files

| File | Purpose | Used by |
|---|---|---|
| `Common.h` | Turns the debug switches of Step2_JUL (`DEBUG_STEP2_JOYSTICK`, `DEBUG_STEP2_L298N`) into the flags of `Joystick.h` and `L298N.h`, and sets the control tick `BUTTON_TIMER_mS` (v6.0.0) | Step2; through `Joystick.h` and `L298N.h`, Step3_Generator and lessons 18 and 19, which define no switch |
| `Headers.h` | Aggregated include | Step2 |
| `JoystickMeasurements.h` | The low end, center, and high end of A0 and A1 in raw ADC counts (`JOYSTICK_A0_LOW`, `JOYSTICK_A0_CENTER`, `JOYSTICK_A0_HIGH`, and the same for A1; the printed file also holds the Self Test Report), printed by Step1_Joystick after a passing self test; shipped 0, 511, and 1023 (v7.0.0; `JoystickCenter.h`, the centers only, from v6.4.0 to v6.8.0). Step3_Generator checks the centers (461 to 561) and the ends (200 counts from the center) and writes the values into Step4_Generated | Step1_Joystick (to compare, and the calculated N of the live values), Step3_Generator, lessons 17 and 20 |
| `Timer.h` | Nonblocking millisecond timer, drifting and fixed rate policies | Step1_Joystick, Step2, lessons 01, 18, 19, and 20 |
| `Button.h` | Debounced button, latching or momentary mode, optional indicator LED | Step1_Joystick, Step2, lesson 18 |
| `Joystick.h` | Revised joystick algorithm (class `Joystick`) | Step2, lesson 19 |
| `L298N.h` | L298N motor driver interface, `Bits()` configuration | Step2, Step3_Generator, lesson 18 |
| `Switch.h` | Simple switch handler | included by `Headers.h`; not called by the current programs (Experiment-1, Lab 4, uses its copy) |
| `Debug.h` | Print helpers for vectors, points, matrices, quaternions (added from Numerics, 20261008) | lessons 01 to 16 |

## `include/claude/`, Files Written with Claude

Added 2026-10-17. These files were written with Claude (Anthropic), an AI assistant, and are kept apart from the original headers, which they do not change. See [include/claude/README.md](include/claude/README.md) for the original classes incorporated, the performance, and the tests.

| File | Purpose | Used by |
|---|---|---|
| `claude/L298NPins.h` | Resolves one `Bits()` value into constant enable and direction pins, with the same rules as `L298N.h` | Step3 |
| `claude/ace.h` | The complete drive program in one file, for speed and size: joystick algorithm, mapping, dead zone, button (active LOW, external 10 kOhm pull up), LED (default D12 since v5.0.0), timer (45 ms tick since v7.2.0; 50 ms from v3.2.0), L298N pins; includes `Arduino.h` only | Step4 |

Performance on the simulated Uno (16 MHz, bits_1010, measured 20261017), Step2_JUL against Step4_Generated with `ace.h`; sizes measured 20261019 (v3.2.1) without debug output:

| | Step2_JUL | Step4_Generated |
|---|---|---|
| Joystick math per tick | 322.5 µs | 16.4 µs |
| Motor output per tick | 40.3 µs | 3.7 µs |
| Full control tick with the two ADC readings | 574.8 µs | 232.0 µs |
| Flash / RAM | 6498 / 318 bytes | 1548 / 23 bytes |

## `include/numerics/`, Math Headers

The math headers are in the `numerics` subfolder and are included with an explicit path, for example `#include "numerics/MiscMath.h"`. Headers inside `numerics` include each other by file name alone, because a quoted `#include` searches the folder of the including file first.

These five headers moved from `include/` on 20261008. Their code is unchanged except for two corrections in `Vector3.h` (`Angle()` and `ProjV()`, marked FIXED 20261008), which Step2_JUL does not call; all five gained REVIEW 20261008 notes. `L298N.h`, `Joystick.h`, and `Headers.h` now include them with the `numerics/` path:

| File | Purpose | Used by |
|---|---|---|
| `Bitwise.h` | Bit manipulation used by `L298N.h` | Step2, Step3_Generator, lessons 01 and 18 |
| `LinearMap.h` | Linear range mapping | Step2, lessons 03, 17, 19, and 20 |
| `MiscMath.h` | `absT()` and the `Debug()` serial helpers | Step2, Step3_Generator, the lessons |
| `TypeConv.h` | Type conversion helpers | lesson 02; included by `Headers.h`, not called by Step2 |
| `Vector3.h` | 3 component vector | lesson 09; included by `Headers.h`, not called by Step2 |

These were added on 20261008, ten from the MageMCU Numerics repository (Algebra/include, 20241202) and two adapted from David Eberly's Geometric Tools Engine; they are used only by the Step5 math lessons. Bugs fixed on 20261008 are listed in `src/Step5_MathLessons/README.md`.

| File | Purpose |
|---|---|
| `Vector2.h`, `Point2.h`, `Point3.h` | 2 component vector; 2 and 3 component points |
| `Matrix.h`, `Matrix2x2.h`, `Matrix3x3.h`, `Matrix4x4.h` | Matrices, determinant, inverse, solve, rotation |
| `Quaternion.h` | Quaternion arithmetic and angle axis conversion |
| `Statistics.h` | Mean, standard deviation, median, queue |
| `RandomNumber.h` | Random numbers in a range |
| `LineFit2.h` | Least squares line fit; adapted from David Eberly, GTE ApprHeightLine2.h (Boost Software License 1.0) |
| `Rotation.h` | Quaternion to matrix, matrix to quaternion, slerp; adapted from David Eberly, GTE Rotation.h and Slerp.h (Boost Software License 1.0) |

Class templates generate no code until a program uses them, and Step2_JUL does not include the added files.

## `src/`, Programs

| Folder | File | Purpose | Status |
|---|---|---|---|
| `Step1_Joystick/` | `main.cpp` | Joystick self test (v6.0.0; a connection check since v4.0.0; questions since v6.2.0; a start question, repeated every 3 s until Enter, and aligned report columns since v6.3.0): six tests in the serial monitor (five up to v7.0.0), each ended with Enter, the push button pressed and released (momentary mode, LED on D12 while held), the grip at rest (CENTER), held UP, DOWN, LEFT, and RIGHT (the first entry, v7.1.0), moved in a circle twice (the second entry, which verifies the held ends), released (Return); reports PASS or FAIL and each value raw first, then calculated, in the order of the bench test check list (v7.1.0), in its format since v7.2.0: each block prints its equations once, then its values in a table, a star marking each line of values for the check list; after a pass prints `include/JoystickMeasurements.h` with the measured low end, center, and high end of each axis (v7.0.0; `include/JoystickCenter.h` with the centers from v6.4.0 to v6.8.0; the `map()` calls up to v6.3.1) and, since v6.8.0, the Self Test Report as comments (SELF TEST REPORT); after a failure the report prints in the monitor; then asks r (run again) or v (the live values of A0 and A1 with their offset from the center and the calculated N, v7.0.0, and SW, four times a second for 20 seconds). Test 3 fails a center more than 50 counts from 511 and warns above 25 counts that a new joystick is recommended (v6.5.0; 100 counts in v6.4.0 and v6.4.1). Any press during Tests 3 to 6 fails the self test (v7.1.0; Tests 3 to 5 from v6.2.1). Holds D5 to D10 LOW; motor supply off. Finds an open wire, a dead axis, an off center module, or a floating D2 before the motors get power; introduces Button.h and Timer.h | Build checked and simulated in simavr (20261022, v6.0.0, v6.1.0, v6.2.0, and v6.3.0; 20261025, v6.4.0); v6.3.1 bench tested by the author 20261023; v6.4.0.a bench tested 20261025, passed; v6.7.0.a bench tested 20261028, passed; v6.8.0.a bench tested 20261028, passed |
| `Step2_JUL/` | `main.cpp` | Full joystick to L298N motor control and, since v3.2.0, the diagnostic program (both debug switches on, 3000 ms tick); one `Bits()` value (the Bits() line) corrects any joystick orientation and L298N wiring; since v6.2.1 the six pin variables carry the name of the L298N input each is wired to in Circuit-1 (`ENB = 5` to `ENA = 10`) | Bench tested as Step2_JUL at commit f2307a1; changed since (v3.1.0 and v3.1.1; LED on D12, v4.0.0); bench tested again by the author 20261021 (release v4.0.1); v6.0.0 adds the debug switches and `setLatching(true)` (behavior unchanged; line numbers from 18 on move down by 6, from 46 on by 11); v6.7.0.a bench tested by the author 20261028, passed |
| `Step3_Generator/` | `main.cpp` | Shows the joystick measurements of `include/JoystickMeasurements.h` (Check 1, v7.0.0; the center of `include/JoystickCenter.h` since v6.4.0), the L298N, button, and LED pins as Uno and ATmega328P pins, for example `D5 (PD5)`, and the joystick lines for the student to check against Step2_JUL; asks for the four binary digits of the `Bits()` value and whether to include the debug data; prints the Step4 program, whose `setup()` calls `robot.begin()` first (v3.2.1) and whose comment header repeats the summary (SUMMARY, v6.8.0); Uno and USB cable only, motor supply off | Build and simulation checked (20261019); bench tested by the author 20261021 (release v4.0.1) and 20261028 (v6.7.0.a), passed |
| `Step4_Generated/` | `main.cpp` | The drive program, printed by Step3_Generator for bits_0000, the first value of the checklist, with the debug data (`DEBUG_GENERATED`), using `include/claude/ace.h` only (45 ms tick since v7.2.0); replace it with the program printed for the value found on the bench | Build checked; motor pin states match Step2_JUL on the host (20261018) and in simavr (20261019, Discrepancies.md, 90); bench tested by the author 20261021 (release v4.0.1) and 20261028 (v6.7.0.a), passed |
| `Step5_MathLessons/` | `main.cpp`; `lessons/L01_Bitwise.h` to `L20_JoystickMap.h` | Numerics math lessons 1 to 16; hardware lessons 17 to 20 (lesson 20, the two segment map on the live joystick, v6.1.0). `main.cpp` compiles ONE lesson, chosen with `#define LESSON`, because the Uno cannot hold them all (v5.0.0), and runs ONE topic of it, chosen with `#define TOPIC`, or all topics with 0 (v5.1.0); its comments give the flash and RAM of each lesson and of its largest topic. Each topic function carries a teaching block: hint, purpose, what is learnt, expected output (v6.3.0) | Lessons 1 to 16 build and simulation checked; hardware lessons 17 to 20 build checked; bench test of Step5 pending |
| `Step6_Circuit/` | `main.cpp` | The test of Circuit-4, the Complete Wiring (Article 1009, Appendix C), used with Circuit-4 ONLY (v7.3.0, 20261030; designed by Jesse Carpenter and Claude (Anthropic)). Two precompiler switches: `STEP6_CIRCUIT` (shipped) holds ENA and ENB LOW and turns VS on and off through D4, Q2, and Q1 with each press of SW; `STEP6_MOTORS` drives the motors with the joystick of Step1 (`include/JoystickMeasurements.h`) and the `Bits()` value of Step2_JUL, accepted only with the joystick centered, after a 500 ms settle, at no more than half power (`STEP6_PWM_LIMIT` 128). D4 and D5 to D10 are LOW before anything else; OFF stops the motors, then disconnects VS. Prints the raw A0 and A1 counts first, then x and y | Build checked with no warnings in both tests; simulated in simavr (20261030): no enable before the settle time, none above 128, none while D4 is LOW; bench test by the author pending |

**Program titles (v6.4.1).** Each program prints its name first, after a blank line and a dotted line, with the `build_src_filter` entry that selects it:

```
................................................
Step1_Joystick: the joystick self test
Selected in platformio.ini: +<Step1_Joystick/>
```

Step2_JUL prints `Step2_JUL: the diagnostic program (L298N Setup)` while a debug switch is on (as shipped; with both switches off it opens no serial port and builds to the same Intel HEX as v6.4.0). Step3_Generator prints `Step3_Generator: prints the program Step4_Generated`, and the program it prints, Step4_Generated, prints `Step4_Generated: the drive program printed by Step3_Generator` with `DEBUG_GENERATED` (without it, the same Intel HEX as v6.4.0). Step5_MathLessons prints the lesson and the topic, for example `Step5_MathLessons: lesson 7 (L07_Vector2), topic 13 (0: every topic)`. A title that names another program means `platformio.ini` still selects that program. The title lines of Step1_Joystick and Step2_JUL replace a blank line, so no cited line moves.

## Debugging

Since v6.0.0 each debug switch is defined in the program that uses it, above its first `#include`, and carries the name of its step. Step2_JUL ships with both of its switches on (top of the file): `DEBUG_STEP2_JOYSTICK` (values through the signal chain) and `DEBUG_STEP2_L298N` (motor driver pin states). `include/Common.h` turns them into `DEBUG_JOYSTICK` and `DEBUG_L298N`, the flags that `Joystick.h` and `L298N.h` test, and either one sets `DEBUG_SERIAL_ON`, which changes `BUTTON_TIMER_mS` from 100 ms to 3000 ms so the Serial Monitor (9600 baud) stays readable. Do not define those three flags by hand. Up to v5.1.0 `Common.h` defined `DEBUG_MAIN` (used by no program), `DEBUG_JOYSTICK`, and `DEBUG_L298N` itself.

While a switch is defined, each control tick starts with a blank line and a dotted line (v6.1.0), so each new output is found at a glance. Step2_JUL is therefore the diagnostic program: L298N Setup and the Motor Movement Checklist (Article 1009) read its output, and its motors respond once every 3 s; the push button OFF stops them at once, outside the tick (v6.2.3). **Step4_Generated is the drive program**: it uses `ace.h` only, not `Common.h`, and its control tick is 45 ms (v7.2.0; 50 ms from v3.2.0). To drive with Step2_JUL at the 100 ms tick instead, comment out both switches (top of the file).

A program that defines no switch gets no debug output. Step3_Generator and lessons L18_MotorLineFit and L19_JoystickFrame include `Common.h` through `L298N.h` or `Joystick.h` and define none. Lessons 18 and 19 build to the same Intel HEX as in v5.1.0, when they defined `DEBUG_ALL_OFF` (removed in v6.0.0); Step3_Generator changes only in the Step2_JUL line numbers it prints. The comment that replaces the `DEBUG_ALL_OFF` lines keeps their line numbers.

Step1_Joystick has no debug switch: its serial monitor output is always on, because the self test is read there. After the report, the answer v prints A0 and A1, raw, with their offset from the measured center (mapped up to v6.3.1) and the calculated N of THE JOYSTICK EQUATIONS (v7.0.0), and the button state four times a second for 20 seconds. Up to v6.1.3 the switch `DEBUG_STEP1_LIVE` (shipped on) printed them after the report without end. Step1_Joystick does not include `Common.h`; it includes `JoystickMeasurements.h` only, to compare the measured values with the file and to compute N (v7.0.0; `JoystickCenter.h` from v6.4.0).

Step4_Generated has its own flag, `DEBUG_GENERATED`, defined at the top of its `main.cpp` when Step3_Generator is answered y to Question 5 (Question 4 up to v6.3.1). It prints the data checked in Step3_Generator (the SUMMARY of its comment header, v6.8.0) once in `setup()`, then the line `Ready: press the push button; the LED on D12 shows ON.`: the button is read from then on, so a press made during the printout, about 1 s, is not seen (v6.2.3). It does not read the serial monitor and does not change the control tick, so it may stay defined while the robot drives; it is not part of `Common.h`, so the printed program needs `ace.h` only.

## Notes

- Teaching notes (v6.1.1): every header in `include/numerics/` and every lesson of `src/Step5_MathLessons/lessons/` has a block marked `TEACHING NOTES (v6.1.1)` that defines the terms and works an example by hand. Comments only.

- Timer.h and Button.h were revised in September 2026 (two timer policies; latching and momentary button modes). The copies in `Experiments/Experiment-1/Code/include/` to `Experiment-5/Code/include/` are byte for byte identical to these files.
- The I2C helper (`BusI2C.h` and `src/DEP/BusI2C.cpp`) was removed in September 2026. Nothing in this folder uses I2C. The class lives on in the MageMCU Serial-Communication repository.
- Build verification: all sketches compiled for `board = uno` with avr-gcc on 2026-09-05 (see `RELEASES.md`). On 2026-10-08, after the Numerics merge, Step1_Joystick and Step2_JUL were rebuilt with avr-gcc 7.3.0 and produced Intel HEX files byte for byte identical to the 2026-10-01 commit (f2307a1). On 2026-10-17, with Step4_Generator and Step5_Generated added, Step1_Joystick and Step2_JUL again produced Intel HEX files identical to the last commit. Later on 2026-10-17, after the renumbering, Step1_JUL produced the same Intel HEX as Step2_JUL (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6). For v3.0.1 (2026-10-17), with the build flags removed, Step1_JUL and Step3_Generated produced the same Intel HEX as in v3.0.0. For v3.1.0 (2026-10-18), with avr-gcc 7.3.0 and ArduinoCore-avr 1.8.6 (`-Wall -Wextra`): Step1_JUL, Step2_Generator, Step3_Generated (with and without `DEBUG_GENERATED`), and all 19 lessons build with no warnings; Step2_Generator runs in simavr with typed answers and prints the shipped Step3_Generated; on the host, `Ace::compute()` matches the float chain of Step1_JUL for all 1024 x 1024 pairs of readings, and for all 16 `Bits()` values the pins set by `ace.h` match `L298N::UpdateL298N()`. For v3.2.0 (2026-10-18) and v3.2.1 (2026-10-19), with avr-gcc 7.3.0 and ArduinoCore-avr 1.8.6 (`-Wall -Wextra`): see `RELEASES.md`. For v4.0.0 to v6.2.1 (2026-10-21 and 2026-10-22): see `RELEASES.md`. Run `pio run` locally before flashing hardware connected to motors.
