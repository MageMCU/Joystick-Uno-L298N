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

## `include/numerics/`, Math Headers

The math headers are in the `numerics` subfolder and are included with an explicit path, for example `#include "numerics/MiscMath.h"`. Headers inside `numerics` include each other by file name alone, because a quoted `#include` searches the folder of the including file first.

These five headers moved from `include/` on 20261008 with their contents unchanged; `L298N.h`, `Joystick.h`, and `Headers.h` now include them with the `numerics/` path:

| File | Purpose | Used by |
|---|---|---|
| `Bitwise.h` | Bit manipulation used by `L298N.h` | Step2 |
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
| `Step3_MathLessons/` | 16 `main.cpp` lessons | Numerics math lessons, one folder per class | Build checked |

## Debugging

In `include/Common.h` uncomment one flag: `DEBUG_MAIN` (Step1 output), `DEBUG_JOYSTICK` (values through the signal chain), or `DEBUG_L298N` (motor driver pin states). Any debug flag sets `DEBUG_SERIAL_ON`, which changes `BUTTON_TIMER_mS` from 100 ms to 3000 ms so the Serial Monitor (9600 baud) stays readable. Comment the flag out again for normal motor response.

## Notes

- Timer.h and Button.h were revised in September 2026 (two timer policies; latching and momentary button modes). The copies in `Experiments/Experiment-1/Code/include/` are identical apart from the folder line in the header comment.
- The I2C helper (`BusI2C.h` and `src/DEP/BusI2C.cpp`) was removed in September 2026. Nothing in this folder uses I2C. The class lives on in the MageMCU Serial-Communication repository.
- Build verification: all sketches compiled for `board = uno` with avr-gcc on 2026-09-05 (see `RELEASES.md`). On 2026-10-08, after the Numerics merge, Step1_Joystick and Step2_JUL were rebuilt with avr-gcc 7.3.0 and produced Intel HEX files byte for byte identical to the 2026-10-01 commit (f2307a1). Run `pio run` locally before flashing hardware connected to motors.
