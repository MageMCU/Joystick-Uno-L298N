# Releases & Active Study

**This repository is under active development.** All releases represent milestones in the ongoing joystick algorithm study and firmware refinement.

---

## Unreleased: v2.1.0 (2026-09-05)

**Repository cleanup and Experiment-1**
- Added `Experiments/Experiment-1` (delay, Timer, Button labs) with reader instructions in `Experiments/Experiment-1/Instructions/README.md`
- Removed the `Labs - DELETEME` folder (the I2C Lab-1 draft is deferred to a later article)
- Removed `BusI2C.h` and `src/DEP/BusI2C.cpp` from `Code-JUL`; nothing in this repository uses I2C
- `Timer.h` revised: drifting policy `isTimer()` and fixed rate policy `isTimerFixedRate()`, `deltaTimeSeconds()`
- `Button.h` revised: debounce, latching and momentary modes, `begin()`, `wasPressed()`, `heldForMs()`
- Experiment-1 `platformio.ini`: `upload_port` no longer hard coded; `build_flags = -std=gnu++11` and `monitor_speed = 9600` added
- Experiment-1 Lab 3: button wiring aligned with `Code-JUL` (switch to GND, `INPUT_PULLUP`); the pull down alternative is documented in the code comment
- Root README rewritten: project tree includes `Experiments/`, debug tick note added, review notes moved here
- `Code-JUL/README.md` corrected: removed the nonexistent `main.cpp.txt` entry and the DEP row
- Header comments: repository name standardized to `Joystick-Uno-L298N`
- Added `Discrepancies.md` with the review findings and their resolution

**Build verification**
- All five sketches (`1_Delay`, `2_Timer`, `3_Button`, `Step1_Joystick`, `Step2_JUL`) compiled for ATmega328P with avr-gcc 7.3.0 and the Arduino AVR core on 2026-09-05, no errors. Hardware test on the bench is still to be run by the author before release.

---

## Current Status: v2.0.0

**Released:** 2026-07-14  
**Status:** Production-ready baseline with simplified, user-focused design  
**Next:** Continuing active research and optimization

---

## What's New in v2.0.0?

### 🎯 Big Picture
- ✅ **Single production algorithm** — Revised octant-based approach locked in
- ✅ **Simplified to deploy** — No compile-time algorithm selection needed
- ✅ **New getter methods** — Check motor direction and current octant
- ✅ **User-focused docs** — Quick-start guides and wiring checklists
- ✅ **Ready to use** — Firmware tested and verified on hardware

### 🆕 API Enhancements
```cpp
bool IsLeftForward()   // Check if left motor moving forward
bool IsRightForward()  // Check if right motor moving forward
int Octant()           // Get current direction octant (0-8)
```

### 📚 Better Documentation
- 6-step quick-start installation guide
- Pin-by-pin wiring checklist (Arduino → L298N)
- Joystick API reference table
- Updated Motor Movement Checklist

---

## Ongoing Study & Future Work

The joystick algorithm continues to be researched and refined. Expected improvements:

- Hardware performance optimization
- Additional motor control methods
- Expanded test coverage
- Algorithm refinement for edge cases

**For experimental features:**
- See the PRIVATE repo (intentionally not publicly accessible)
- Includes 3-variant algorithm system and detailed QA reports

---

## Upgrading from v1.0 to v2.0

**⚠️ No Breaking Changes** — API remains compatible

If you were using algorithm variants (ALGO_STUDY_*):
- Remove `#define ALGO_STUDY_REVISED` or `ALGO_STUDY_COMPACT` from Common.h
- Replace `ActiveAlgorithm<float>` with `Joystick<float>` in main.cpp
- *(Full algorithm variants available in PRIVATE repo)*

---

## Version History (Details)

### [2.0.0] — 2026-07-14

**Major Changes**
- Replaced original `Joystick.h` with revised octant-based algorithm
- Removed `Algorithm_Study_Revised.h` and `Algorithm_Study_Compact.h` from active code
- Simplified compile-time algorithm selection (no more `ALGO_STUDY_*` preprocessor flags)
- Cleaned up `Common.h` and `platformio.ini` build configuration

**New Features**
- Added `IsLeftForward()` getter — check if left motor is moving forward
- Added `IsRightForward()` getter — check if right motor is moving forward
- Added `Octant()` getter — retrieve current directional octant (0–8)
- Improved dead zone handling with tolerance-based approach (0.001 offset)

**Documentation**
- Simplified root README with quick-start guide
- Added prerequisites table (VS Code, PlatformIO, Arduino Uno)
- Added 6-step installation guide for new users
- Added hardware wiring checklist (pin-by-pin table)
- Added Joystick API reference table
- Updated "Next Steps" with actionable guidance
- Added Repository Status & History section explaining relationship to PRIVATE repo
- Updated Motor Movement Checklist for revised algorithm compatibility
- Created `RELEASES.md` for version tracking

**Code Quality Fixes**
- Fixed type mismatch in [Code-JUL/src/Step2_JUL/main.cpp](Code-JUL/src/Step2_JUL/main.cpp): `ActiveAlgorithm<float>()` → `Joystick<float>()`
- Removed outdated algorithm selection logic from main.cpp
- Removed conditional compilation blocks for algorithm selection
- Verified all includes and dependencies resolve correctly
- Code compiled at the time of release

**Verification**
- Code syntax validated (no compilation errors)
- All method signatures match declarations
- Include dependencies verified (no circular includes)
- Template implementations complete
- Namespace usage correct

---

### [1.0.0] — Original Release

**Status:** Archived (see PRIVATE repo for experimental variants)

**Contents:**
- Initial firmware for Arduino Uno + L298N differential drive motor control
- Original joystick algorithm (quadrant-based routing)
- Algorithm selection system with study variants
- Motor movement checklist for hardware validation

---

## Technical Notes

- Namespace: **csjc** — Carpenter Software - Jesse Carpenter
- Hardware: **Arduino Uno (Atmega328P)** + **L298N Motor Driver**
- IDE: **PlatformIO** (VS Code)
- Language: **C++** (GNU++11)
- Status: **Active through end of 2026**

See [Repository Status & History](README.md#repository-status--history) for information about the relationship to the predecessor experimental repository.

