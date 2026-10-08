# Discrepancies

Review of the Joystick-Uno-L298N repository, updated October 7, 2026. Each item lists what was found, where, and its current status. Items marked **Open** need author input or verification that cannot be completed from repository contents alone.

## Code

| # | Finding | Location | Resolution |
|---|---------|----------|------------|
| 1 | Button wiring conflicted with the class default. The sketch set `pinMode(buttonPin, INPUT)` with the comment "Uses pull-down resistor" but constructed `Button(buttonPin, buttonLED)` with the default `activeLow = true`. On the first `updateButton()` the class calls `begin()`, which reconfigures the pin as `INPUT_PULLUP` and treats LOW as pressed, so a pull down wired button read as pressed at idle. `Code-JUL` (Step1 and Step2) uses the same default and therefore assumes the switch closes to ground. | `Experiments/Experiment-1/Code/src/3_Button/main.cpp` | **Fixed 20261008 (replaces the 20261007 fix).** The author's external 10 kΩ pull down wiring is kept, as Article 1009 describes, and the constructor is `Button(buttonPin, buttonLED, false)`; the `pinMode` line is removed. The series does not rely on the internal pull up resistors. |
| 2 | `upload_port = /dev/ttyACM0` hard coded (Linux device name). Uploads fail on macOS and Windows until edited. `Code-JUL/platformio.ini` leaves the port to auto detection. | `Experiments/Experiment-1/Code/platformio.ini` | **Fixed.** Line commented out with examples for Linux, macOS, and Windows. `monitor_speed = 9600` added to both projects. |
| 3 | `Code-JUL` compiles with `build_flags = -std=gnu++11`; the Experiment-1 project did not set a standard. | `Experiments/Experiment-1/Code/platformio.ini` | **Fixed.** Same flag added. |
| 4 | I2C code linked into every `Code-JUL` build. `Headers.h` included `BusI2C.h` and `build_src_filter` always included `+<DEP/>`, so `Wire` and the TWI driver were compiled into Step1 and Step2 although neither uses I2C. The build produced two warnings from `BusI2C.cpp` (unused parameter, comparison always true). | `Code-JUL/include/Headers.h`, `Code-JUL/platformio.ini`, `Code-JUL/src/DEP/`, `Code-JUL/include/BusI2C.h` | **Fixed.** Include, filter entry, folder, and header removed. Step2_JUL program size fell from 8196 to 6960 bytes and static data from 544 to 329 bytes; Step1_Joystick from 4708 to 3472 bytes and 512 to 297 bytes. The class remains available in the MageMCU Serial-Communication repository. |
| 5 | `Switch.h`, `Vector3.h`, and `TypeConv.h` are included through `Headers.h` but not used by either sketch. Templates cost nothing until instantiated, so this is a clarity issue. | `Code-JUL/include/Headers.h` | **Left as is.** Documented in `Code-JUL/README.md` as not used by the current sketches. Remove if no future sketch needs them. |
| 6 | Two dead zones exist in the signal chain. `Step2_JUL/main.cpp` zeroes inputs below 0.05 (X) and 0.06 (Y) before the algorithm; `Joystick.h` applies its own tolerance of 0.001. Only the 0.001 value was documented. | `Code-JUL/src/Step2_JUL/main.cpp`, `Motor-Movement-Checklist/ReadMe.md`, root `README.md` | **Documented.** Root README now describes both. Article 1004 should explain both. |

## Header Review (2026-10-07)

> **2026-10-08:** the header changes described in this section were reversed. `Code-JUL/include/` and `Code-JUL/src/` were restored to the bench verified commit f2307a1; the Numerics merge moved `Bitwise.h`, `LinearMap.h`, `MiscMath.h`, `TypeConv.h`, and `Vector3.h` unchanged into `include/numerics/` and added `include/Debug.h`, the Numerics classes, and `src/Step3_MathLessons/` (see `RELEASES.md`, v2.2.0). The findings below remain valid as review notes.

The production headers were reviewed against `Step1_Joystick`, `Step2_JUL`, the Markdown documentation, and the available build/simulation environment. Changes in this review were limited to `Code-JUL/include/`; `Button.h` and `Timer.h` were intentionally left unchanged.

| Header | Review finding and change | Follow-up verification |
|--------|---------------------------|------------------------|
| `Bitwise.h` | Invalid indexes could be treated as bit 0, and the maximum bit was excluded from `GetBitNumber()`. Index checks now reject out-of-range operations, and lookup includes the highest valid bit. | Test bit 0, the highest valid bit, zero bits, and negative/out-of-range indexes with the target integer types. |
| `L298N.h` | Configuration and PWM fields were uninitialized until configured. Constructors now initialize state; PWM values are clamped to `-255…255` before magnitude conversion; header definitions are inline and the safety argument is declared at the public API. | Exercise every `BitsL298N` value against the documented truth table, verify motor/enable pin mapping, and test `-255`, `255`, and extreme signed inputs. Confirm the L298N’s real direction/PWM behavior on the bench. |
| `Switch.h` | Constructors called `pinMode()` before applying caller-provided pin numbers, and the on/off state was not initialized. Setup is deferred to `begin()` or the first update, and state is initialized. | Test default and custom pins, initial LED state, and active-high switch wiring with an external pull-down on hardware. |
| `TypeConv.h` | Stored bytes/words were indeterminate until a conversion ran, and out-of-line header definitions risked duplicate symbols in multi-translation-unit builds. State is initialized, definitions are inline, and getters are const. | Test byte/word round trips and compile a multi-source sketch that includes the header in more than one translation unit. |
| `MiscMath.h` | `AngleRadian()` divided by `a`, making axis cases fragile; it now uses `atan2()` and normalizes negative angles to `[0, 2π)`. The non-template `Debug(String)` definition is inline. | Verify the four quadrants and both axes, plus a multi-translation-unit include test. |
| `Joystick.h` | Output getters only read state but were not const-qualified. They are now `const`. | Build succeeded; verify octant outputs and direction getters with representative inputs and the bench checklist. |

**Validation performed:** on 2026-10-07, `pio run` succeeded for the production `Code-JUL` project and all five `Experiments/Experiment-N/Code` projects. The generated Uno firmware sizes are recorded below. A temporary debug build ran in simavr and exercised the button-enabled path through joystick processing and an L298N output command. simavr reported missing AVCC and returned zero for both analog reads, so the observed octant/output is not evidence of realistic joystick behavior. The attempted second-press simulation did not yield a usable trace. No systematic header unit tests or physical hardware validation have been performed; those checks remain open.

## Article 1004 DRAFT 3 (2026-10-08)

- Experiments 1 to 5 were rewritten from Article 1004 DRAFT 3; the Copilot drafts of Experiments 2 to 5, their modified header copies, and 160 committed `.pio` build files were removed. Every experiment `include/` folder now holds the original headers of commit f2307a1.
- Each `Instructions/README.md` is generated from the article text. Experiments 6 to 9 (numerics) have instructions only; their code is `Code-JUL/src/Step3_MathLessons/`, including the new lessons 17, 18, and 19.
- `Code-JUL/platformio.ini`: the active `build_src_filter` is back on line 31, where Article 1009 points. Every filter must now also exclude `Step3_MathLessons`; the filter lines printed in Article 1009 (Joystick Setup, step 3; L298N Setup, step 5) need that addition.
- Article cross review (1000, 1001, 1002, 1003, 1005, 1009): see the Author Review section of Article 1004 DRAFT 3.

## Documentation

| # | Finding | Location | Resolution |
|---|---------|----------|------------|
| 7 | `Step2_JUL/main.cpp.txt` listed as a reference snapshot; the file does not exist. | `Code-JUL/README.md` | **Fixed.** Entry removed. |
| 8 | "Status: Hardware tested & verified" and "A full hardware build was not executed in this environment" both appeared in the same README. | root `README.md` | **Fixed.** Review note removed; the verified status stands as the author's statement. Build verification details moved to `RELEASES.md`. |
| 9 | Project structure tree omitted `Experiments/`, `RELEASES.md`, `DISCLAIMER.md`, and `LICENSE`. | root `README.md` | **Fixed.** Tree regenerated. |
| 10 | The debug flags were documented without the side effect that any flag changes `BUTTON_TIMER_mS` from 100 ms to 3000 ms. | root `README.md` | **Fixed.** Note added in Next Steps. |
| 11 | Joystick axis assignment differs between documents. The repository code and README use X on A1 and Y on A0; Article 1000 reportedly shows X on A0 and Y on A1. | root `README.md`; Article 1000 | **Open.** The Experiment-2 procedure tells users to measure the actual joystick and correct the software mapping if needed. The repository cannot establish which mapping the external article or a user's hardware should use; verify the physical setup and resolve the article/code discrepancy with the author. |
| 12 | Header comments in the Experiment-1 copies of `Timer.h` and `Button.h` said "Folder: Code-JUL". | `Experiments/Experiment-1/Code/include/` | **Fixed.** Folder line now reads `Experiments/Experiment-1/Code/include (copy of Code-JUL/include)`. Files otherwise identical to the Code-JUL originals. |
| 13 | `Experiments/Experiment-1/Code/README` had no `.md` extension, so GitHub showed raw Markdown. It described the shipped `build_src_filter` as selecting `1_Delay` while `platformio.ini` selected `3_Button`. Typos "hte" and "togehter". A fenced code block was indented under a bullet. | `Experiments/Experiment-1/Code/README` | **Fixed.** Renamed `README.md` and rewritten. `platformio.ini` now ships with Lab 1 selected, matching the reading order. |
| 14 | `Instructions/README.md` contained only two placeholder lines. | `Experiments/Experiment-1/Instructions/README.md` | **Fixed.** Full reader instructions written (overview, materials, software setup, three labs with code, wiring, expected output, verification, troubleshooting). |
| 15 | Markdown broken at the end of the root README: `Note:` followed a bullet with no blank line and `---` followed the note with no blank line, so the note and the rule were absorbed into the last bullet. | root `README.md` | **Fixed** by the rewrite. |
| 16 | `Experiments/Experiment-2/README.md` was empty. | `Experiments/Experiment-2/README.md` | **Fixed.** Stub added naming the subject and the code folder. |
| 17 | Header comments used a repository-name spelling that differed from GitHub's `Joystick-Uno-L298N`. | all `include/*.h`, `src/*/main.cpp` | **Fixed.** Comments now use the exact repository spelling `Joystick-Uno-L298N`. |
| 18 | `RELEASES.md` cited a fix at "line 48" that no longer matched the file, and claimed "All code compiles without warnings or errors", which the BusI2C warnings contradicted. | `RELEASES.md` | **Fixed.** Line reference removed; claim replaced with the compile date. Unreleased v2.1.0 entry added listing this revision. |
| 19 | The root README, `Code-JUL/README.md`, and `RELEASES.md` repeated the history of the private research repository in several places. | root `README.md`, `Code-JUL/README.md`, `RELEASES.md` | **Fixed.** The root README now has only a brief status summary linking to `RELEASES.md`; detailed history remains in `RELEASES.md`, and the `Code-JUL` README omits the repeated history. |
| 20 | The checklist did not describe both dead-zone layers, and the root README linked to `Motor-Movement-Checklist/README.md`, which did not match the existing file's `ReadMe.md` casing. | `Motor-Movement-Checklist/ReadMe.md`, root `README.md` | **Fixed.** The checklist now states both dead-zone layers, and the root README link matches the existing filename. |

## Structure

| # | Finding | Location | Resolution |
|---|---------|----------|------------|
| 21 | `Labs - DELETEME/` remained in the tree with the I2C Lab-1 README. | repository root | **Fixed.** Folder removed. The I2C material is preserved in the author's Lab-1 repo seed for a later article. |
| 22 | Experiment-2 originally depended on `Step1_Joystick` in `Code-JUL`, so it was not self-contained. | `Experiments/Experiment-2/` | **Fixed.** Experiment-2 now has its own `Code/` PlatformIO project, source, and copied headers; its instructions describe the standalone project. |
| 23 | Experiments 3, 4, and 5 originally had no code folders. | `Experiments/` | **Fixed.** Each now has its own `Code/` PlatformIO project and instructions. The projects are build-verified, but physical checks remain outstanding as noted above. |

## Build verification

The following five sketches were compiled on 2026-09-05 for `board = uno` (ATmega328P, 16 MHz) with avr-gcc 7.3.0 and the Arduino AVR core, using the same flags PlatformIO applies (`-std=gnu++11`, `-Os`). These are historical results from that review, not a claim that every current project was rebuilt on that date:

| Sketch | Program (bytes) | Data (bytes) | Warnings |
|--------|-----------------|--------------|----------|
| Experiment-1 `1_Delay` | 3306 | 269 | none |
| Experiment-1 `2_Timer` | 3430 | 289 | none |
| Experiment-1 `3_Button` | 4082 | 359 | none |
| Code-JUL `Step1_Joystick` | 3472 | 297 | two `unused variable` warnings for `xDigital` and `yDigital` when `DEBUG_MAIN` is off (they are used only inside the debug block); harmless, pre existing |
| Code-JUL `Step2_JUL` | 6960 | 329 | none |

The PlatformIO registry was not reachable in that review environment, so those compiles used avr-gcc directly rather than `pio run`. The four Experiment-2 through Experiment-5 projects and the production Step2_JUL project were subsequently reported as build-verified on 2026-10-07; see `RELEASES.md`. Run `pio run` in each project folder on the development machine before flashing hardware connected to motors. Build verification is not physical hardware validation.

**Current local build verification (2026-10-07):** `pio run` completed successfully for all six projects in this repository on the Arduino Uno target. `avr-size` reported:

| Project | Program (bytes) | Static data (bytes) |
|---------|-----------------|---------------------|
| `Code-JUL` | 6262 | 288 |
| Experiment-1 | 2346 | 258 |
| Experiment-2 | 3268 | 222 |
| Experiment-3 | 3962 | 249 |
| Experiment-4 | 2046 | 190 |
| Experiment-5 | 7158 | 293 |

These results establish compilation only. There is no automated host-side or PlatformIO unit-test suite in the repository; ADC interpretation, octant outputs, driver pin behavior, button timing, and motor behavior still need the separately listed software-vector and physical checks.

## Not changed, by design

- `Code-JUL/src/Step1_Joystick/main.cpp` and `Step2_JUL/main.cpp`: application logic was not changed in the 2026-10-07 header review; repository-name comments were standardized.
- `Button.h` and `Timer.h`: intentionally left unchanged in the 2026-10-07 header review.
- The other production headers listed in the Header Review section were changed as described there; do not interpret this section as saying those headers were untouched.
