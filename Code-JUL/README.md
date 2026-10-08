# Joystick-Uno-L298N (JUL), Code-JUL Folder

Production firmware. Namespace **csjc** (Carpenter Software, Jesse Carpenter).

## Quick Use (PlatformIO)

1. Open VS Code.
2. Open this folder, `Code-JUL/`, as the project (File, Open Folder).
3. Let PlatformIO load `platformio.ini`.
4. Connect the Arduino Uno by USB.
5. Click PlatformIO **Upload** to build and flash the firmware.

### Important

- Open the `Code-JUL/` folder itself in VS Code, not the repository root.
- If build errors mention the project structure or source filters, reopen VS Code with only `Code-JUL/` selected.

## Selecting a Program

`platformio.ini` compiles one `src/` folder at a time through `build_src_filter`. A leading `+` includes a folder and a leading `-` excludes it. The shipped setting selects the full firmware:

```
build_src_filter = +<*> -<Step1_Joystick/> +<Step2_JUL/>
```

To run the joystick wiring test instead, swap the signs on the two folders.

## `include/`, Header Files

| File | Purpose | Used by |
|---|---|---|
| `Common.h` | Debug flags and the control tick `BUTTON_TIMER_mS` | all |
| `Headers.h` | Aggregated include | Step1, Step2 |
| `Timer.h` | Nonblocking millisecond timer, drifting and fixed rate policies | Step1, Step2 |
| `Button.h` | Debounced button, latching or momentary mode, optional indicator LED | Step1, Step2 |
| `LinearMap.h` | Linear range mapping | Step2 |
| `Joystick.h` | Revised joystick algorithm (class `Joystick`) | Step2 |
| `L298N.h` | L298N motor driver interface, `Bits()` configuration | Step2 |
| `Bitwise.h` | Bit manipulation used by `L298N.h` | Step2 |
| `MiscMath.h` | `absT()` and the `Debug()` serial helpers | Step1, Step2 |
| `Switch.h` | Simple switch handler | not used by the current sketches |
| `TypeConv.h` | Type conversion helpers | not used by the current sketches |
| `Vector3.h` | 3 component vector | not used by the current sketches |

## `src/`, Firmware Programs

| Folder | File | Purpose | Status |
|---|---|---|---|
| `Step1_Joystick/` | `main.cpp` | Joystick wiring validation; prints raw X and Y with `DEBUG_MAIN` enabled | Tested |
| `Step2_JUL/` | `main.cpp` | Full joystick to L298N motor control | Build-verified; hardware validation pending |

## Debugging

In `include/Common.h` uncomment one flag: `DEBUG_MAIN` (Step1 output), `DEBUG_JOYSTICK` (values through the signal chain), or `DEBUG_L298N` (motor driver pin states). Any debug flag sets `DEBUG_SERIAL_ON`, which changes `BUTTON_TIMER_mS` from 100 ms to 3000 ms so the Serial Monitor (9600 baud) stays readable. Comment the flag out again for normal motor response.

## Header Review and Validation

The remaining production headers were reviewed on 2026-10-07 against both sketches and the repository documentation. `L298N.h` now initializes its state and clamps PWM input to the Arduino range; `Bitwise.h` guards bit indexes and correctly searches the highest bit; `Switch.h` defers hardware setup until `begin()` or its first update; `TypeConv.h` initializes stored values and uses inline definitions; `MiscMath.h` uses `atan2()` for `AngleRadian()` and makes its non-template `Debug()` definition inline; and the `Joystick` read-only getters are `const`. `Button.h` and `Timer.h` were not changed in this review.

The production `Step2_JUL` project builds for the Uno. A temporary debug build also ran in simavr and exercised the button-enabled path through joystick processing and the L298N command. The simulator reported missing AVCC, so the joystick ADC readings were zero; this run does not validate realistic analog input, all eight directions, motor electrical behavior, or reliable button-disable timing.

Before relying on the changes on hardware, verify the `Bitwise` boundary cases (invalid indexes and the highest valid bit), the L298N bit-pattern table and PWM limits (including extreme signed inputs), and the `Switch` default/custom pins and active-high pull-down wiring. Then bench-test all eight joystick positions, neutral/dead-zone behavior, and prompt motor disable with the actual Uno, joystick, and L298N. See [`Discrepancies.md`](../Discrepancies.md) for the review record.

## Notes

- Timer.h and Button.h were revised in September 2026 (two timer policies; latching and momentary button modes). The copies in `Experiments/Experiment-1/Code/include/` are identical apart from the folder line in the header comment.
- The I2C helper (`BusI2C.h` and `src/DEP/BusI2C.cpp`) was removed in September 2026. Nothing in this folder uses I2C. The class lives on in the MageMCU Serial-Communication repository.
- Historical build verification: all sketches compiled for `board = uno` with avr-gcc on 2026-09-05 (see `RELEASES.md`). The 2026-10-07 `Step2_JUL` build is recorded above and in `RELEASES.md`; run `pio run` locally before flashing hardware connected to motors.
