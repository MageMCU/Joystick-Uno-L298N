# Joystick-Uno-L298N (JUL), Code-JUL Folder

Drive software. Namespace **csjc** (Carpenter Software, Jesse Carpenter).

## Quick Use (PlatformIO)

1. Open VS Code.
2. Open this folder, `Code-JUL/`, as the project (File, Open Folder).
3. Let PlatformIO load `platformio.ini`.
4. Connect the Arduino Uno by USB.
5. Click PlatformIO **Upload** to build and upload the program.

### Important

- Open the `Code-JUL/` folder itself in VS Code, not the repository root.
- If build errors mention the project structure or source filters, reopen VS Code with only `Code-JUL/` selected.

## Selecting a Program

`platformio.ini` compiles one `src/` folder at a time through `build_src_filter`. A leading `+` includes a folder and a leading `-` excludes it. The shipped setting selects the drive program, Step2_JUL:

```
build_src_filter = +<*> -<Step1_Joystick/> +<Step2_JUL/> -<Step3_MathLessons/>
```

To run the joystick wiring test instead, swap the signs on the first two folders. To run a math lesson, see `src/Step3_MathLessons/README.md` and the examples in `platformio.ini`.

Step4_Generator is built in its own PlatformIO environment, `env:step4`, so the filter lines above are unchanged. Select `env:step4` in the PlatformIO status bar, or run `pio run -e step4 -t upload -t monitor`. The PlatformIO monitor of `env:step4` also saves its output in a log file in this folder (`log2file`), so the printed program can be copied from the file. Step5_Generated holds the program that Step4_Generator prints and is built the same way, in `env:step5` (`pio run -e step5 -t upload`). In `env:uno` the Step4 and Step5 folders compile to nothing.

## `include/`, Header Files

| File | Purpose | Used by |
|---|---|---|
| `Common.h` | Debug flags and the control tick `BUTTON_TIMER_mS` | all |
| `Headers.h` | Aggregated include | Step1, Step2 |
| `Timer.h` | Nonblocking millisecond timer, drifting and fixed rate policies | Step1, Step2 |
| `Button.h` | Debounced button, latching or momentary mode, optional indicator LED | Step1, Step2 |
| `Joystick.h` | Revised joystick algorithm (class `Joystick`) | Step2 |
| `L298N.h` | L298N motor driver interface, `Bits()` configuration | Step2 |
| `Switch.h` | Simple switch handler | not used by the current sketches |
| `Debug.h` | Print helpers for vectors, points, matrices, quaternions (added from Numerics, 20261008) | Step3 |

## `include/claude/`, Files Written with Claude

Added 2026-10-17. These files were written with Claude (Anthropic), an AI assistant, and are kept apart from the original headers, which they do not change. See [include/claude/README.md](include/claude/README.md) for the original classes incorporated, the performance, and the tests.

| File | Purpose | Used by |
|---|---|---|
| `claude/L298NPins.h` | Resolves one `Bits()` value into constant enable and direction pins, with the same rules as `L298N.h` | Step4 |
| `claude/ace.h` | The complete drive program in one file, for speed and size: joystick algorithm, mapping, dead zone, button, timer, L298N pins; includes `Arduino.h` only | Step5 |

Performance on the simulated Uno (16 MHz, bits_1010), Step2_JUL against Step5_Generated with `ace.h`:

| | Step2_JUL | Step5_Generated |
|---|---|---|
| Joystick math per tick | 322.5 µs | 16.4 µs |
| Motor output per tick | 40.3 µs | 3.7 µs |
| Full control tick with the two ADC readings | 574.8 µs | 232.0 µs |
| Flash / RAM | 6344 / 316 bytes | 1420 / 23 bytes |

## `include/numerics/`, Math Headers

The math headers are in the `numerics` subfolder and are included with an explicit path, for example `#include "numerics/MiscMath.h"`. Headers inside `numerics` include each other by file name alone, because a quoted `#include` searches the folder of the including file first.

These five headers moved from `include/` on 20261008. Their code is unchanged except for two corrections in `Vector3.h` (`Angle()` and `ProjV()`, marked FIXED 20261008), which Step1 and Step2 do not call; all five gained REVIEW 20261008 notes. `L298N.h`, `Joystick.h`, and `Headers.h` now include them with the `numerics/` path:

| File | Purpose | Used by |
|---|---|---|
| `Bitwise.h` | Bit manipulation used by `L298N.h` | Step1 (through the L298N object), Step2 |
| `LinearMap.h` | Linear range mapping | Step2 |
| `MiscMath.h` | `absT()` and the `Debug()` serial helpers | Step1, Step2 |
| `TypeConv.h` | Type conversion helpers | not used by the current sketches |
| `Vector3.h` | 3 component vector | not used by the current sketches |

These were added on 20261008, ten from the MageMCU Numerics repository (Algebra/include, 20241202) and two adapted from David Eberly's Geometric Tools Engine; they are used only by the Step3 math lessons. Bugs fixed on 20261008 are listed in `src/Step3_MathLessons/README.md`.

| File | Purpose |
|---|---|
| `Vector2.h`, `Point2.h`, `Point3.h` | 2 component vector; 2 and 3 component points |
| `Matrix.h`, `Matrix2x2.h`, `Matrix3x3.h`, `Matrix4x4.h` | Matrices, determinant, inverse, solve, rotation |
| `Quaternion.h` | Quaternion arithmetic and angle axis conversion |
| `Statistics.h` | Mean, standard deviation, median, queue |
| `RandomNumber.h` | Random numbers in a range |
| `LineFit2.h` | Least squares line fit; adapted from David Eberly, GTE ApprHeightLine2.h (Boost Software License 1.0) |
| `Rotation.h` | Quaternion to matrix, matrix to quaternion, slerp; adapted from David Eberly, GTE Rotation.h and Slerp.h (Boost Software License 1.0) |

Class templates generate no code until a program uses them, and Step1 and Step2 do not include the added files.

## `src/`, Programs

| Folder | File | Purpose | Status |
|---|---|---|---|
| `Step1_Joystick/` | `main.cpp` | Joystick wiring validation; prints raw X and Y with `DEBUG_MAIN` enabled | Tested |
| `Step2_JUL/` | `main.cpp` | Full joystick to L298N motor control | Tested |
| `Step4_Generator/` | `main.cpp` | Asks four questions in the serial monitor (x pin, x equation, y equation, `Bits()` value) and prints the Step5 program; Uno and USB cable only | Build and simulation checked (20261017); bench pending |
| `Step5_Generated/` | `main.cpp` | The program printed by Step4_Generator for the author's bench (x A1, y A0, bits_1010), using `include/claude/ace.h` only; replace it with the program printed for another bench | Build checked; motor pin states match Step2_JUL in simulation (20261017); bench pending |
| `Step3_MathLessons/` | 19 `main.cpp` lessons | Numerics math lessons 01 to 16; hardware lessons 17 to 19 | First 16 build and simulation checked; hardware lessons build-checked, bench pending |

## Debugging

In `include/Common.h` uncomment one flag: `DEBUG_MAIN` (Step1 output), `DEBUG_JOYSTICK` (values through the signal chain), or `DEBUG_L298N` (motor driver pin states). Any debug flag sets `DEBUG_SERIAL_ON`, which changes `BUTTON_TIMER_mS` from 100 ms to 3000 ms so the Serial Monitor (9600 baud) stays readable. Comment the flag out again for normal motor response.

## Notes

- Timer.h and Button.h were revised in September 2026 (two timer policies; latching and momentary button modes). The copies in `Experiments/Experiment-1/Code/include/` to `Experiment-5/Code/include/` are byte for byte identical to these files.
- The I2C helper (`BusI2C.h` and `src/DEP/BusI2C.cpp`) was removed in September 2026. Nothing in this folder uses I2C. The class lives on in the MageMCU Serial-Communication repository.
- Build verification: all sketches compiled for `board = uno` with avr-gcc on 2026-09-05 (see `RELEASES.md`). On 2026-10-08, after the Numerics merge, Step1_Joystick and Step2_JUL were rebuilt with avr-gcc 7.3.0 and produced Intel HEX files byte for byte identical to the 2026-10-01 commit (f2307a1). On 2026-10-17, with Step4_Generator and Step5_Generated added, Step1_Joystick and Step2_JUL again produced Intel HEX files identical to the last commit. Run `pio run` locally before flashing hardware connected to motors.
