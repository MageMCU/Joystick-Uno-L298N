# Releases & Active Study

**This repository is under active development.** All releases represent milestones in the ongoing joystick algorithm study and software refinement.

---

## Unreleased: follow-up corrections after v2.4.0

- `Code-JUL/src/Step3_MathLessons/19_JoystickFrame/main.cpp`: apply the positive mount-angle rotation for a counterclockwise-mounted joystick, matching the frame derivation and Experiment-8 instructions.
- `Code-JUL/src/Step3_MathLessons/18_MotorLineFit/main.cpp`: discard calibration counts entered while the joystick button is OFF; Experiment-7 now explains how to reset between measurement sets and change motor-supply voltage safely.

These corrections are not part of the v2.4.0 tag.

---

## v2.4.0 (2026-10-09), Article 1004 DRAFT 4 and Article 1009 alignment

Tag `v2.4.0` marks the code that Article 1004 DRAFT 4 and Article 1009 (20261007b) describe; compare a later release with this tag before revising either article.

- `Code-JUL/src/Step2_JUL/main.cpp`: comments only. The lines named in Article 1009 are back at the numbers the article gives: `ledPin` 42, D12 form 44, `Button` 45, pins 55 to 60, L298N object 55 to 71, `PinsL298N()` 73, `Bits()` 92, `analogRead()` 103 and 104. The Bits comment block now states Table-3 of Article 1009: bit 3 = 1 means the enable pins are straight (values 8 to 15); the old block labeled 0 to 7 as straight
- `Code-JUL/src/Step1_Joystick/main.cpp`: comments only. D12 form of `ledPin` added on line 50 (line 51, 68, 82 to 85 unchanged); the Analogs print is on line 119 as in Article 1009; example output corrected to `Analogs:  a: 512 b: 509`; references to the Supplemental replaced by Article 1009, Joystick Setup; typos corrected
- `Code-JUL/include/L298N.h`: comments only. Enumeration, member, and `Bits()` comments rewritten to match Article 1009, Table-3; "Supplimental Article" replaced by Article 1009, L298N Setup
- `Code-JUL/include/Common.h`: comments only. Em dashes removed; the timer note now says that any debug flag selects 3000 ms. Lines 33 and 43 unchanged
- `Experiments/Experiment-1/Code/src/1_Delay`, `2_Timer`, `3_Button`: comment blocks above `loop()` that explain the code (moved from the article, which no longer prints the listings); `Button(...)` remains on line 48
- `Experiments/Experiment-1` to `5/Instructions/README.md`: replaced by lab cards (folders, filter lines, wiring, lines edited at the bench); the steps are in the article
- `Experiments/Experiment-6` to `9/Instructions/README.md`: now the full source of the advanced steps; local labels (Table 7.1, Equation 6.1, and so on); lesson paths in place of Code-14 to Code-16
- `Experiments/Circuits/`: schematics Circuit-1 to Circuit-4 (SVG and PNG)
- The include folders of Experiments 1 to 5 are unchanged: they stay the original headers of commit f2307a1, old comments included
- Verified: Step1_Joystick and Step2_JUL compile to the same Intel HEX as v2.3.0 (c08735a) with no flag, DEBUG_MAIN, DEBUG_JOYSTICK, and DEBUG_L298N (avr-gcc 7.3.0, Arduino AVR core)

## v2.3.0 (2026-10-08), Article 1004 experiments (commit c08735a)

- Experiments 1 to 5 rebuilt from Article 1004 DRAFT 3: every `include/` folder holds the original header files of commit f2307a1, unchanged; new labs Experiment-1 `4_Switch`; Experiment-2 `1_Preprocessor`, `2_LinearMap`; Experiment-3 `1_MiscMath`, `2_DutyCycle`; Experiment-4 `1_Bitwise`, `2_TypeConv`, `3_BitsLEDs`; Experiment-5 `1_Vector3`, `2_Joystick`. Experiment-2 and Experiment-5 use Step1_Joystick and Step2_JUL for the Article 1009 setup procedures
- Experiment-1, Lab 3: `Button(buttonPin, buttonLED, false)` for the external pull down resistor (the class replaced the `pinMode(buttonPin, INPUT)` line with `INPUT_PULLUP`)
- Experiments 6 to 9 (advanced, numerics): instructions; new lessons `17_DeadZone`, `18_MotorLineFit` (uses LineFit2.h, credit David Eberly), `19_JoystickFrame`
- Instructions/README.md of every experiment generated from the article text; article links added to README.md
- `Code-JUL/platformio.ini`: active `build_src_filter` returned to line 31 (Article 1009); notes moved below it
- Removed the Copilot drafts of Experiments 2 to 5 and 160 committed `.pio` build files; added a root `.gitignore`
- Verified: Step1_Joystick and Step2_JUL hex identical to f2307a1; all labs and lessons compile with avr-gcc 7.3.0 (`-Wall -Wextra`, no warnings); lab output confirmed in simavr

## Unreleased: v2.2.0 (2026-10-08), Numerics merge

**Code-JUL restored to the bench verified headers**
- `Code-JUL/include/` and `Code-JUL/src/` restored to commit f2307a1 (2026-10-01). This reverses the v2.1.0 header review changes listed below, so that the repository again holds the code that was tested on the bench. The v2.1.0 changes are kept in the history and will be reconsidered as reviewed changes (see Article 1004 planning).

**MageMCU Numerics merged into Code-JUL (additions only)**
- Moved `Bitwise.h`, `LinearMap.h`, `MiscMath.h`, `TypeConv.h`, and `Vector3.h` from `Code-JUL/include/` into `Code-JUL/include/numerics/` with their contents unchanged. The only edits to files used by Step1_Joystick and Step2_JUL are the `#include` lines of `L298N.h`, `Joystick.h`, and `Headers.h`, which now name `numerics/`; the two `main.cpp` files are unchanged
- Added `Code-JUL/include/numerics/` with the Numerics classes not already in Code-JUL (Algebra/include, 20241202): `Vector2.h`, `Point2.h`, `Point3.h`, `Matrix.h`, `Matrix2x2.h`, `Matrix3x3.h`, `Matrix4x4.h`, `Quaternion.h`, `Statistics.h`, `RandomNumber.h`
- Added `Code-JUL/include/Debug.h`, the Numerics print helpers, without the `Debug()` overloads already defined in `MiscMath.h`
- Added `Code-JUL/src/Step3_MathLessons/`: the Numerics test programs as 14 lessons, one folder per class (`01_Bitwise` to `14_Quaternion`), selected with `build_src_filter` (examples in `Code-JUL/platformio.ini`). Each lesson holds its class's test functions, moved from the Numerics `TESTS` files and calls them in order from `setup()`. Where a Numerics test called a function that the Code-JUL header does not have, the lesson was changed instead of the header: `01_Bitwise` defines its own `ReverseBits()`, and `02_TypeConv` uses the return value of `BytesToWord()` and `BytesToDWord()` in place of `GetWord()` and `GetDWord()`
- `Code-JUL/platformio.ini`: the shipped filter also excludes `Step3_MathLessons/`, so Step2_JUL is still the program built by default
- Not merged: the Numerics versions of the headers that already exist in Code-JUL (`Bitwise.h`, `TypeConv.h`, `LinearMap.h`, `MiscMath.h`, `Vector3.h`, `Button.h`, `Timer.h`); the Numerics Button and Timer tests (those classes are studied in Experiment-1); the archived `Joystick` and `L298N` text files. The `BusI2C` files are set aside for a later article
- Removed `TempObjects/` (working copies of article PDFs; the published articles are linked from the README)
- Experiments 1 to 5 are unchanged in this release; their `include/` folders still hold flat copies and will be rebuilt with the Article 1004 labs

**Numerics bug fixes and Geometric Tools adaptations (2026-10-08)**
- Fixed bugs in the ten Numerics headers that Step1 and Step2 do not use (Matrix3x3 `Solve()`, singular `Inverse()`, Matrix4x4 constructors and members, Quaternion `GetAxis()`, `NormDeviation()`, product renormalization, unused inheritance that enlarged every quaternion and matrix, Vector2/Vector3 `Angle()` and `ProjV()`, RandomNumber seeding and range, Statistics sorting stack and empty sets). Details in `Code-JUL/src/Step3_MathLessons/README.md`; each fix is marked `FIXED 20261008`
- New banner (Author, Website, File, Folder, Github, Repository) on every numerics header
- Added `numerics/LineFit2.h` and `numerics/Rotation.h`, adapted with credit from the Geometric Tools Engine by David Eberly (ApprHeightLine2.h, Rotation.h, Slerp.h; Boost Software License 1.0); each carries his notice and an adaptation clause
- Added lessons `15_LineFit` and `16_Rotation` (self checking: expected, observed, PASS or FAIL)
- AVR simulation (simavr) of all 16 lessons: each ran to its last test; lessons 15 and 16 report 0 failures

**Build verification (avr-gcc 7.3.0, ATmega328P, `-Os -std=gnu++11`, 2026-10-08)**
- `Step2_JUL` 6324 bytes program, 316 bytes data; `Step1_Joystick` 3048 bytes program, 284 bytes data. The Intel HEX output of both is byte for byte identical to commit f2307a1, so the merge changes no behavior of the bench verified program
- `Step2_JUL` also builds with each of `DEBUG_MAIN`, `DEBUG_JOYSTICK`, and `DEBUG_L298N`
- All 16 math lessons compile and link for the Uno with no warnings under `-Wall -Wextra` (program and data sizes in `Code-JUL/src/Step3_MathLessons/README.md`); the `build_src_filter` settings were checked with PlatformIO's own source matcher, and each selects exactly one program
- Experiments 1 to 5 still build
- Compilation is not hardware validation; run the math lessons on an Uno before relying on their printed results

---

## Unreleased: v2.1.0 (2026-10-07)

> Note (2026-10-08): the header changes in this entry were reversed in v2.2.0.

**Header review follow-up (2026-10-07)**
- Reviewed the remaining `Code-JUL/include/` headers against the production sketches and repository Markdown; `Button.h` and `Timer.h` were not changed
- `Bitwise.h`: guarded invalid bit indexes and fixed lookup of the highest valid bit
- `L298N.h`: initialized internal state, clamped PWM input to `-255…255`, and made header-defined functions inline
- `Switch.h`: deferred hardware initialization until `begin()` or first update and initialized its state
- `TypeConv.h`: initialized stored conversion values, made header definitions inline, and const-qualified getters
- `MiscMath.h`: changed `AngleRadian()` to use `atan2()` and made the non-template `Debug()` helper inline
- `Joystick.h`: const-qualified read-only getters
- `Step2_JUL` built successfully for the Uno. A temporary simavr run reached the button-enabled motor-update path, but ADC reads were zero because AVCC was not modeled; joystick directions and motor behavior remain unverified in simulation and require targeted tests and bench validation. See `Discrepancies.md`.

**Experiments 2-5 (2026-10-07)**
- Initially added draft, self-contained Uno projects and learner instructions for joystick diagnostics (Experiment-2), one-motor L298N control (Experiment-3), two-motor/`Bits()` validation (Experiment-4), and joystick-to-motor integration with the Article 1009 checklist (Experiment-5)
- Copied the production headers required by each experiment into its local `Code/include/` folder
- Built all four draft projects successfully for the Uno; these materials need further review, and wiring, motor behavior, and the Article 1009 bench checks still require physical hardware validation
- Related Article 1003/1009 material was used as context; `TempObjects/` was not modified

**Article 1009 alignment follow-up**
- Reorganized the draft sequence around Article 1009's two formal procedures: Experiment-2 is **Joystick Setup** (no motor driver connected), and Experiment-5 is **L298N Setup** (the full eight-direction `Bits()` checklist and post-check voltage worksheet)
- Reframed Experiment-3 as optional one-motor familiarization and added a 300 ms zero-output interlock whenever the requested direction reverses; Experiment-4 is now a software-only `Bits()`/E/P/L/R decoding exercise
- Mapped Articles 1000-1003 into the Article 1004 experiment sequence: notebook/scientific method; joystick voltages and X/Y algorithm; Uno pin/peripheral functions; and L298N H-bridge, PWM, voltage loss, and heating
- Updated learner guides and the root experiment table to distinguish formal procedures from optional preparation; all four revised Uno projects build successfully, but physical movement and voltage measurements remain unverified
- Kept unrelated peripheral topics outside the Article 1004 scope, and all `TempObjects/` source PDFs remain read-only.

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
