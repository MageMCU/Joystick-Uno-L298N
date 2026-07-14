# Joystick Uno L298N (JUL) — Code Folder

namespace **csjc**

## Quick Use (PlatformIO)

1. Open VS Code.
2. Open this folder: `Code-JUL/`.
3. Let PlatformIO load the project (`platformio.ini`).
4. Connect Arduino Uno by USB.
5. Click PlatformIO **Upload** to build and flash firmware.

### Important

- This firmware must be opened as the `Code-JUL/` folder itself in VS Code.
- Do not open the full repository root as the active PlatformIO project.
- If compiler/build errors appear due to project structure or source filters, reopen VS Code with only `Code-JUL/` selected.

## `include/` — Header Files

| File | Purpose |
|---|---|
| `Bitwise.h` | Bit-manipulation utilities |
| `BusI2C.h` | I²C bus helpers |
| `Button.h` | Momentary push-button handler |
| `Common.h` | Shared constants and type definitions |
| `Headers.h` | Aggregated include for convenience |
| `Joystick.h` | **Revised** joystick algorithm (class `Joystick`, namespace `csjc`) |
| `L298N.h` | L298N motor-driver interface |
| `LinearMap.h` | Linear range-mapping utility |
| `MiscMath.h` | General math helpers |
| `Switch.h` | Toggle/switch handler |
| `Timer.h` | Non-blocking millisecond timer |
| `TypeConv.h` | Type-conversion helpers |
| `Vector3.h` | 3-component vector math |

## `src/` — Firmware Programs

| Folder | File | Status |
|---|---|---|
| `DEP/` | `BusI2C.cpp` | I²C dependency (compiled with all targets) |
| `Step1_Joystick/` | `main.cpp` | Joystick wiring validation — **tested** |
| `Step2_JUL/` | `main.cpp` | Full Joystick + L298N motor control — **tested** |
| `Step2_JUL/` | `main.cpp.txt` | Reference snapshot (plain-text backup, not compiled) |

## Root

| File | Purpose |
|---|---|
| `platformio.ini` | Build configuration (environment, flags, upload settings) |

## Notes

- Code updated 20240820 (Article 1009).
- `main.cpp.txt` in `Step2_JUL/` is a plain-text reference copy and is not compiled.

---

## Additional Notes

- **Algorithm:** This folder uses the **revised Joystick algorithm** exclusively.
- **Study materials:** See the PRIVATE research repo for algorithm comparison references and study implementations (not publicly accessible).
