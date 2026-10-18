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

`platformio.ini` compiles one `src/` folder at a time through `build_src_filter`. A leading `+` includes a folder and a leading `-` excludes it. The shipped setting, line 31, selects the drive program, Step1_JUL:

```
build_src_filter = +<*> +<Step1_JUL/> -<Step2_Generator/> -<Step3_Generated/> -<Step4_MathLessons/>
```

Renumbered 2026-10-17: Step1_Joystick was removed, and Step2_JUL became Step1_JUL. Renumbered again 2026-10-18 (v3.1.0), in the order of use: Step2_Generator (formerly Step3_Generator, before that Step4_Generator), Step3_Generated (formerly Step4_Generated, before that Step5_Generated), and Step4_MathLessons (formerly Step2_MathLessons, before that Step3_MathLessons). To run a math lesson, see `src/Step4_MathLessons/README.md` and the examples in `platformio.ini`.

Step2_Generator and Step3_Generated are selected the same way (since v3.0.1; up to v3.0.0 they had their own environments, `env:step3` and `env:step4`, and build flags). Copy one of these lines over line 31:

```
build_src_filter = +<*> -<Step1_JUL/> +<Step2_Generator/> -<Step3_Generated/> -<Step4_MathLessons/>
build_src_filter = +<*> -<Step1_JUL/> -<Step2_Generator/> +<Step3_Generated/> -<Step4_MathLessons/>
```

The PlatformIO monitor also saves its output in a log file in this folder (`monitor_filters = default, log2file`), so the program printed by Step2_Generator can be copied from the file. The `upload_port` and `monitor_port` lines are required since v3.2.0 (Quick Use, step 5); `platformio.ini` lists an example for macOS, Linux, the Raspberry Pi, and Windows.

## Setup with One Bits() Value

Whatever the joystick orientation and the L298N connections, one four digit `Bits()` value (line 92 of Step1_JUL, found with the Motor Movement Checklist) corrects the motor movement of a working bench. The joystick lines 103 and 104, `xDigital = analogRead(A0)` and `yDigital = analogRead(A1)` since v3.1.0, stay as written; Step2_Generator uses the same two pins. Exchanging or reversing a joystick axis only swaps or negates the two motor commands, which bits 2, 1, and 0 undo; bit 3 corrects crossed enable pins. All 128 combinations of 8 joystick orientations and 16 L298N wirings were checked in simulation; each has exactly one passing value (see `../Motor-Movement-Checklist/ReadMe.md`). The connection rules are listed at the end of `src/Step1_JUL/main.cpp`: D5 and D10 to ENA and ENB, either way; D6 and D7 together on one IN pair and D8 and D9 on the other, either order; each motor on one output pair. Faults the value cannot correct, such as a dead axis or a wire on a wrong Uno pin, are found first with the Joystick and Button Check of Article 1009, L298N Setup (`DEBUG_JOYSTICK`, no motors).

## Two Ways to Drive (v3.2.0)

Step1_JUL ships with every debug flag of `include/Common.h` on, so the Joystick and Button Check and the Motor Movement Checklist (Article 1009, L298N Setup) can read the whole signal chain in the Serial Monitor; its motors respond once every 3 s. Once the `Bits()` value is found, there are two ways to drive:

| Path | What to do | Control tick |
|---|---|---|
| A. Stay with Step1_JUL | In `Common.h`, comment out `DEBUG_MAIN`, `DEBUG_JOYSTICK`, and `DEBUG_L298N`, then upload Step1_JUL again | 100 ms |
| B. Continue to Step 3 | Run Step2_Generator with the `Bits()` value, copy the printed program into `Step3_Generated/main.cpp`, and upload it (`include/claude/ace.h`, no `Common.h`) | 50 ms |

Both paths set the same motor pins for the same joystick readings. Path B also leaves the serial monitor free: `DEBUG_GENERATED` prints once at startup and may stay on.

## `include/`, Header Files

| File | Purpose | Used by |
|---|---|---|
| `Common.h` | Debug flags, all on since v3.2.0 (`DEBUG_ALL_OFF` turns them off), and the control tick `BUTTON_TIMER_mS` | Step1, lessons 18 and 19 (with `DEBUG_ALL_OFF`) |
| `Headers.h` | Aggregated include | Step1 |
| `Timer.h` | Nonblocking millisecond timer, drifting and fixed rate policies | Step1 |
| `Button.h` | Debounced button, latching or momentary mode, optional indicator LED | Step1 |
| `Joystick.h` | Revised joystick algorithm (class `Joystick`) | Step1 |
| `L298N.h` | L298N motor driver interface, `Bits()` configuration | Step1 |
| `Switch.h` | Simple switch handler | not used by the current sketches |
| `Debug.h` | Print helpers for vectors, points, matrices, quaternions (added from Numerics, 20261008) | Step4 |

## `include/claude/`, Files Written with Claude

Added 2026-10-17. These files were written with Claude (Anthropic), an AI assistant, and are kept apart from the original headers, which they do not change. See [include/claude/README.md](include/claude/README.md) for the original classes incorporated, the performance, and the tests.

| File | Purpose | Used by |
|---|---|---|
| `claude/L298NPins.h` | Resolves one `Bits()` value into constant enable and direction pins, with the same rules as `L298N.h` | Step2 |
| `claude/ace.h` | The complete drive program in one file, for speed and size: joystick algorithm, mapping, dead zone, button (active LOW, external 10 kOhm pull up), timer (50 ms tick since v3.2.0), L298N pins; includes `Arduino.h` only | Step3 |

Performance on the simulated Uno (16 MHz, bits_1010), Step1_JUL against Step3_Generated with `ace.h`:

| | Step1_JUL | Step3_Generated |
|---|---|---|
| Joystick math per tick | 322.5 µs | 16.4 µs |
| Motor output per tick | 40.3 µs | 3.7 µs |
| Full control tick with the two ADC readings | 574.8 µs | 232.0 µs |
| Flash / RAM | 6344 / 316 bytes | 1420 / 23 bytes |

## `include/numerics/`, Math Headers

The math headers are in the `numerics` subfolder and are included with an explicit path, for example `#include "numerics/MiscMath.h"`. Headers inside `numerics` include each other by file name alone, because a quoted `#include` searches the folder of the including file first.

These five headers moved from `include/` on 20261008. Their code is unchanged except for two corrections in `Vector3.h` (`Angle()` and `ProjV()`, marked FIXED 20261008), which Step1_JUL does not call; all five gained REVIEW 20261008 notes. `L298N.h`, `Joystick.h`, and `Headers.h` now include them with the `numerics/` path:

| File | Purpose | Used by |
|---|---|---|
| `Bitwise.h` | Bit manipulation used by `L298N.h` | Step1 |
| `LinearMap.h` | Linear range mapping | Step1 |
| `MiscMath.h` | `absT()` and the `Debug()` serial helpers | Step1 |
| `TypeConv.h` | Type conversion helpers | not used by the current sketches |
| `Vector3.h` | 3 component vector | not used by the current sketches |

These were added on 20261008, ten from the MageMCU Numerics repository (Algebra/include, 20241202) and two adapted from David Eberly's Geometric Tools Engine; they are used only by the Step4 math lessons. Bugs fixed on 20261008 are listed in `src/Step4_MathLessons/README.md`.

| File | Purpose |
|---|---|
| `Vector2.h`, `Point2.h`, `Point3.h` | 2 component vector; 2 and 3 component points |
| `Matrix.h`, `Matrix2x2.h`, `Matrix3x3.h`, `Matrix4x4.h` | Matrices, determinant, inverse, solve, rotation |
| `Quaternion.h` | Quaternion arithmetic and angle axis conversion |
| `Statistics.h` | Mean, standard deviation, median, queue |
| `RandomNumber.h` | Random numbers in a range |
| `LineFit2.h` | Least squares line fit; adapted from David Eberly, GTE ApprHeightLine2.h (Boost Software License 1.0) |
| `Rotation.h` | Quaternion to matrix, matrix to quaternion, slerp; adapted from David Eberly, GTE Rotation.h and Slerp.h (Boost Software License 1.0) |

Class templates generate no code until a program uses them, and Step1_JUL does not include the added files.

## `src/`, Programs

| Folder | File | Purpose | Status |
|---|---|---|---|
| `Step1_JUL/` | `main.cpp` | Full joystick to L298N motor control and, since v3.2.0, the diagnostic program (every debug flag of `Common.h` on, 3000 ms tick); one `Bits()` value (line 92) corrects any joystick orientation and L298N wiring | Bench tested as Step2_JUL at commit f2307a1; changed since (lines 46, 47, 103, 104; v3.1.0 and v3.1.1), bench retest pending |
| `Step2_Generator/` | `main.cpp` | Shows the L298N, button, and LED pins as Uno and ATmega328P pins, for example `D5 (PD5)`, and the joystick lines for the student to check against Step1_JUL; asks for the four binary digits of the `Bits()` value and whether to include the debug data; prints the Step3 program; Uno and USB cable only | Build and simulation checked (20261018); bench pending |
| `Step3_Generated/` | `main.cpp` | The drive program, printed by Step2_Generator for bits_0000, the first value of the checklist, with the debug data (`DEBUG_GENERATED`), using `include/claude/ace.h` only (50 ms tick); replace it with the program printed for the value found on the bench | Build checked; motor pin states match Step1_JUL on the host (20261018); bench pending |
| `Step4_MathLessons/` | 19 `main.cpp` lessons | Numerics math lessons 01 to 16; hardware lessons 17 to 19 | First 16 build and simulation checked; hardware lessons build-checked, bench pending |

## Debugging

Since v3.2.0, `include/Common.h` ships with **every debug flag on**: `DEBUG_JOYSTICK` (values through the signal chain), `DEBUG_L298N` (motor driver pin states), and `DEBUG_MAIN`, which no program in this folder uses since Step1_Joystick was removed. Any debug flag sets `DEBUG_SERIAL_ON`, which changes `BUTTON_TIMER_mS` from 100 ms to 3000 ms so the Serial Monitor (9600 baud) stays readable.

Step1_JUL is therefore the diagnostic program: the Joystick and Button Check and the Motor Movement Checklist (Article 1009, L298N Setup) read its output, and its motors respond once every 3 s. **Step3_Generated is the drive program**: it uses `ace.h` only, not `Common.h`, and its control tick is 50 ms. To drive with Step1_JUL at the 100 ms tick instead, comment out all three flags in `Common.h`.

A program that defines `DEBUG_ALL_OFF` before its first include gets no debug flag. Lessons 18_MotorLineFit and 19_JoystickFrame and Step2_Generator do so; each builds to the same Intel HEX as with the flags commented out.

Step3_Generated has its own flag, `DEBUG_GENERATED`, defined at the top of its `main.cpp` when Step2_Generator is answered y to Question 4. It prints the data checked in Step2_Generator once in `setup()`. It does not read the serial monitor and does not change the control tick, so it may stay defined while the robot drives; it is not part of `Common.h`, so the printed program needs `ace.h` only.

## Notes

- Timer.h and Button.h were revised in September 2026 (two timer policies; latching and momentary button modes). The copies in `Experiments/Experiment-1/Code/include/` to `Experiment-5/Code/include/` are byte for byte identical to these files.
- The I2C helper (`BusI2C.h` and `src/DEP/BusI2C.cpp`) was removed in September 2026. Nothing in this folder uses I2C. The class lives on in the MageMCU Serial-Communication repository.
- Build verification: all sketches compiled for `board = uno` with avr-gcc on 2026-09-05 (see `RELEASES.md`). On 2026-10-08, after the Numerics merge, Step1_Joystick and Step2_JUL were rebuilt with avr-gcc 7.3.0 and produced Intel HEX files byte for byte identical to the 2026-10-01 commit (f2307a1). On 2026-10-17, with Step4_Generator and Step5_Generated added, Step1_Joystick and Step2_JUL again produced Intel HEX files identical to the last commit. Later on 2026-10-17, after the renumbering, Step1_JUL produced the same Intel HEX as Step2_JUL (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6). For v3.0.1 (2026-10-17), with the build flags removed, Step1_JUL and Step3_Generated produced the same Intel HEX as in v3.0.0. For v3.1.0 (2026-10-18), with avr-gcc 7.3.0 and ArduinoCore-avr 1.8.6 (`-Wall -Wextra`): Step1_JUL, Step2_Generator, Step3_Generated (with and without `DEBUG_GENERATED`), and all 19 lessons build with no warnings; Step2_Generator runs in simavr with typed answers and prints the shipped Step3_Generated; on the host, `Ace::compute()` matches the float chain of Step1_JUL for all 1024 x 1024 pairs of readings, and for all 16 `Bits()` values the pins set by `ace.h` match `L298N::UpdateL298N()`. For v3.2.0 (2026-10-18), with avr-gcc 7.3.0 and ArduinoCore-avr 1.8.6 (`-Wall -Wextra`): see `RELEASES.md`. Run `pio run` locally before flashing hardware connected to motors.
