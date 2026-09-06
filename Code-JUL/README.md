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
| `Step2_JUL/` | `main.cpp` | Full joystick to L298N motor control | Tested |

## Debugging

In `include/Common.h` uncomment one flag: `DEBUG_MAIN` (Step1 output), `DEBUG_JOYSTICK` (values through the signal chain), or `DEBUG_L298N` (motor driver pin states). Any debug flag sets `DEBUG_SERIAL_ON`, which changes `BUTTON_TIMER_mS` from 100 ms to 3000 ms so the Serial Monitor (9600 baud) stays readable. Comment the flag out again for normal motor response.

## Notes

- Timer.h and Button.h were revised in September 2026 (two timer policies; latching and momentary button modes). The copies in `Experiments/Experiment-1/Code/include/` are identical apart from the folder line in the header comment.
- The I2C helper (`BusI2C.h` and `src/DEP/BusI2C.cpp`) was removed in September 2026. Nothing in this folder uses I2C. The class lives on in the MageMCU Serial-Communication repository.
- Build verification: all sketches compiled for `board = uno` with avr-gcc on 2026-09-05 (see `RELEASES.md`). Run `pio run` locally before flashing hardware connected to motors.
