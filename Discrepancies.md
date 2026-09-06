# Discrepancies

Review of the Joystick-Uno-L298N repository, September 5, 2026. Each item lists what was found, where, and what was done about it in this revision. Items marked **Open** need a decision by the author.

## Code

| # | Finding | Location | Resolution |
|---|---------|----------|------------|
| 1 | Button wiring conflicted with the class default. The sketch set `pinMode(buttonPin, INPUT)` with the comment "Uses pull-down resistor" but constructed `Button(buttonPin, buttonLED)` with the default `activeLow = true`. On the first `updateButton()` the class calls `begin()`, which reconfigures the pin as `INPUT_PULLUP` and treats LOW as pressed, so a pull down wired button read as pressed at idle. `Code-JUL` (Step1 and Step2) uses the same default and therefore assumes the switch closes to ground. | `Experiments/Experiment-1/Code/src/3_Button/main.cpp` | **Fixed.** Wiring aligned with `Code-JUL`: button between D2 and GND, no external resistor, `button.begin()` called in `setup()`, `pinMode` line removed. The pull down alternative (`Button(pin, led, false)`) is documented in the code comment and in the Instructions. |
| 2 | `upload_port = /dev/ttyACM0` hard coded (Linux device name). Uploads fail on macOS and Windows until edited. `Code-JUL/platformio.ini` leaves the port to auto detection. | `Experiments/Experiment-1/Code/platformio.ini` | **Fixed.** Line commented out with examples for Linux, macOS, and Windows. `monitor_speed = 9600` added to both projects. |
| 3 | `Code-JUL` compiles with `build_flags = -std=gnu++11`; the Experiment-1 project did not set a standard. | `Experiments/Experiment-1/Code/platformio.ini` | **Fixed.** Same flag added. |
| 4 | I2C code linked into every `Code-JUL` build. `Headers.h` included `BusI2C.h` and `build_src_filter` always included `+<DEP/>`, so `Wire` and the TWI driver were compiled into Step1 and Step2 although neither uses I2C. The build produced two warnings from `BusI2C.cpp` (unused parameter, comparison always true). | `Code-JUL/include/Headers.h`, `Code-JUL/platformio.ini`, `Code-JUL/src/DEP/`, `Code-JUL/include/BusI2C.h` | **Fixed.** Include, filter entry, folder, and header removed. Step2_JUL program size fell from 8196 to 6960 bytes and static data from 544 to 329 bytes; Step1_Joystick from 4708 to 3472 bytes and 512 to 297 bytes. The class remains available in the MageMCU Serial-Communication repository. |
| 5 | `Switch.h`, `Vector3.h`, and `TypeConv.h` are included through `Headers.h` but not used by either sketch. Templates cost nothing until instantiated, so this is a clarity issue. | `Code-JUL/include/Headers.h` | **Left as is.** Documented in `Code-JUL/README.md` as not used by the current sketches. Remove if no future sketch needs them. |
| 6 | Two dead zones exist in the signal chain. `Step2_JUL/main.cpp` zeroes inputs below 0.05 (X) and 0.06 (Y) before the algorithm; `Joystick.h` applies its own tolerance of 0.001. Only the 0.001 value was documented. | `Code-JUL/src/Step2_JUL/main.cpp`, `Motor-Movement-Checklist/ReadMe.md`, root `README.md` | **Documented.** Root README now describes both. Article 1004 should explain both. |

## Documentation

| # | Finding | Location | Resolution |
|---|---------|----------|------------|
| 7 | `Step2_JUL/main.cpp.txt` listed as a reference snapshot; the file does not exist. | `Code-JUL/README.md` | **Fixed.** Entry removed. |
| 8 | "Status: Hardware tested & verified" and "A full hardware build was not executed in this environment" both appeared in the same README. | root `README.md` | **Fixed.** Review note removed; the verified status stands as the author's statement. Build verification details moved to `RELEASES.md`. |
| 9 | Project structure tree omitted `Experiments/`, `RELEASES.md`, `DISCLAIMER.md`, and `LICENSE`. | root `README.md` | **Fixed.** Tree regenerated. |
| 10 | The debug flags were documented without the side effect that any flag changes `BUTTON_TIMER_mS` from 100 ms to 3000 ms. | root `README.md` | **Fixed.** Note added in Next Steps. |
| 11 | Joystick axis assignment differs between documents. The repository (Step1, Step2, README table) reads X on A1 and Y on A0. Article 1000 shows X on A0 and Y on A1. | root `README.md`; Article 1000 | **Open.** README declares the repository authoritative for the code and points to the Step1 serial test. Decide whether Article 1000 is corrected or the code is changed. |
| 12 | Header comments in the Experiment-1 copies of `Timer.h` and `Button.h` said "Folder: Code-JUL". | `Experiments/Experiment-1/Code/include/` | **Fixed.** Folder line now reads `Experiments/Experiment-1/Code/include (copy of Code-JUL/include)`. Files otherwise identical to the Code-JUL originals. |
| 13 | `Experiments/Experiment-1/Code/README` had no `.md` extension, so GitHub showed raw Markdown. It described the shipped `build_src_filter` as selecting `1_Delay` while `platformio.ini` selected `3_Button`. Typos "hte" and "togehter". A fenced code block was indented under a bullet. | `Experiments/Experiment-1/Code/README` | **Fixed.** Renamed `README.md` and rewritten. `platformio.ini` now ships with Lab 1 selected, matching the reading order. |
| 14 | `Instructions/README.md` contained only two placeholder lines. | `Experiments/Experiment-1/Instructions/README.md` | **Fixed.** Full reader instructions written (overview, materials, software setup, three labs with code, wiring, expected output, verification, troubleshooting). |
| 15 | Markdown broken at the end of the root README: `Note:` followed a bullet with no blank line and `---` followed the note with no blank line, so the note and the rule were absorbed into the last bullet. | root `README.md` | **Fixed** by the rewrite. |
| 16 | `Experiments/Experiment-2/README.md` was empty. | `Experiments/Experiment-2/README.md` | **Fixed.** Stub added naming the subject and the code folder. |
| 17 | Header comments named the repository `Joystick-UNO-L298N`; the GitHub repository is `Joystick-Uno-L298N`. | all `include/*.h`, `src/*/main.cpp` | **Fixed.** Standardized to `Joystick-Uno-L298N` (comment lines only). |
| 18 | `RELEASES.md` cited a fix at "line 48" that no longer matched the file, and claimed "All code compiles without warnings or errors", which the BusI2C warnings contradicted. | `RELEASES.md` | **Fixed.** Line reference removed; claim replaced with the compile date. Unreleased v2.1.0 entry added listing this revision. |
| 19 | The root README, `Code-JUL/README.md`, and `RELEASES.md` repeated the history of the private research repository in several places. | root `README.md`, `Code-JUL/README.md` | **Fixed.** Removed from both READMEs; `RELEASES.md` remains the single place for that history. |
| 20 | `Motor-Movement-Checklist/ReadMe.md` reported only the inner tolerance and used the file name `ReadMe.md`, which was inconsistent with the repo naming. | `Motor-Movement-Checklist/ReadMe.md`, root `README.md` | **Fixed.** The checklist now states both dead-zone layers and the repo links to the uppercase `README.md` form for consistency. |

## Structure

| # | Finding | Location | Resolution |
|---|---------|----------|------------|
| 21 | `Labs - DELETEME/` remained in the tree with the I2C Lab-1 README. | repository root | **Fixed.** Folder removed. The I2C material is preserved in the author's Lab-1 repo seed for a later article. |
| 22 | `Step1_Joystick` is the code for Experiment-2 but lives in `Code-JUL`, so Experiment-2 is not self contained in the way Experiment-1 is. | `Code-JUL/src/Step1_Joystick/` | **Open.** Options: move it to `Experiments/Experiment-2/Code` with copied headers, or keep it in `Code-JUL` and have the Experiment-2 instructions point there. |
| 23 | Experiments 3, 4, and 5 named in the Article 1004 outline have no code folders yet. | `Experiments/` | **Open.** Experiments 3 and 4 need small new sketches built on `L298N.h`; Experiment-5 can point at `Step2_JUL`. |

## Build verification

All five sketches were compiled on 2026-09-05 for `board = uno` (ATmega328P, 16 MHz) with avr-gcc 7.3.0 and the Arduino AVR core, using the same flags PlatformIO applies (`-std=gnu++11`, `-Os`). Results after this revision:

| Sketch | Program (bytes) | Data (bytes) | Warnings |
|--------|-----------------|--------------|----------|
| Experiment-1 `1_Delay` | 3306 | 269 | none |
| Experiment-1 `2_Timer` | 3430 | 289 | none |
| Experiment-1 `3_Button` | 4082 | 359 | none |
| Code-JUL `Step1_Joystick` | 3472 | 297 | two `unused variable` warnings for `xDigital` and `yDigital` when `DEBUG_MAIN` is off (they are used only inside the debug block); harmless, pre existing |
| Code-JUL `Step2_JUL` | 6960 | 329 | none |

The PlatformIO registry was not reachable from the review environment, so the compile used avr-gcc directly rather than `pio run`. Run `pio run` in each project folder on the development machine before flashing hardware that is connected to motors.

## Not changed, by design

- `Code-JUL/src/Step1_Joystick/main.cpp` and `Step2_JUL/main.cpp`: logic untouched. Only the repository name in the header comment changed.
- `Joystick.h`, `L298N.h`, `LinearMap.h`, `Bitwise.h`, `MiscMath.h`, `Switch.h`, `TypeConv.h`, `Vector3.h`: untouched apart from the header comment.
- `DISCLAIMER.md`, `LICENSE`: untouched.
