# Discrepancies

Review of the Joystick-Uno-L298N repository, updated October 12, 2026, against Article 1004 Update 20261012 Rev 2. Sections are dated, newest first. Each item lists what was found, where, and its current status. Items marked **Open** need author input or verification that cannot be completed from repository contents alone.

Open as of 2026-10-12: 11 (Article 1000 axis mapping), 29 (bench check of the joystick power procedure only), 36 (Experiment-5, Lab 3, step 4, against Article 1009), 37 (tag v2.4.0 and Bibliography [1] date), 38 (Eberly credits for the matrix and quaternion fixes, author decision).

## Full Repository Review against Article 1004 Rev 2 (2026-10-12)

Every file of the repository was reviewed for correctness, then compared with Article 1004 Rev 1; the article was revised to `1004_Experiments_Guide_20261012_Update_Rev2.docx` (Update 20261012 Rev 2). All programs were compiled with avr-gcc 7.3.0 and ArduinoCore-avr 1.8.6, and the labs with fixed output were run in simavr.

| # | Finding | Location | Resolution |
|---|---------|----------|------------|
| 39 | Experiment-6, Lab 3, steps 1 and 2, and Experiment-7, Lab 2, steps 3 and 4, told the student to reset the Uno with the bench or motor supply applied. D5 to D10 float between a reset and `setup()`, which conflicts with Article 1004, Experiment-3, Powering the Joystick after Experiment-3. | `17_DeadZone`, `18_MotorLineFit`; Experiment-6 and Experiment-7 instructions | **Fixed 2026-10-12.** Lesson 17 repeats on any key; lesson 18 starts a new set on n, stops the motors, and returns the button state to OFF. The instructions no longer reset the Uno with a supply applied. Article Rev 2 states this in the subsection. Bench check open with finding 29. |
| 40 | Article, Before the Experiments, Safety, said "Experiments 1, 2, and the code labs need only the USB cable"; Experiment-5, Lab 1, needs the bench supply since Rev 1. | Article 1004, Safety, first paragraph | **Fixed 2026-10-12** in Rev 2. |
| 41 | The Motor Movement Checklist listed octants 1 to 8 as Forward, forward right, right, and so on, which does not match Joystick.h; its code snippet called D5 "ENA, left motor speed", while Table-1 wires D5 to L298N ENB. | `Motor-Movement-Checklist/ReadMe.md` | **Fixed 2026-10-12.** Octant table follows Joystick.h and Table-8; snippet follows Step2_JUL. |
| 42 | The lab notebook template recorded the earlier programs (Experiment-3 keys w, x, s; Experiment-4 E/P/L/R and "no motor hardware"), had no Experiment-1, Lab 4, and treated the Experiment-2 voltages as optional. The article called it a one page template. | `Experiments/LAB-NOTEBOOK-TEMPLATE.md`; Article 1004, The Lab Notebook | **Fixed 2026-10-12.** Records rewritten for the current labs; Rev 2 says "a template". |
| 43 | Wiring comments of `1_Vector3` and `17_DeadZone` said "no motor power". | `Experiments/Experiment-5/Code/src/1_Vector3/main.cpp`; `17_DeadZone/main.cpp` | **Fixed 2026-10-12.** |
| 44 | Experiment-8 expected every live diagonal to report the octant of Table-8, but a diagonal is a boundary; a rotated input can exceed 1 and, if used to drive the motors, gives a command above 255. | `Experiments/Experiment-8/Instructions/README.md`; Article 1004, Part B, second paragraph | **Fixed 2026-10-12.** Either neighboring octant is accepted at a diagonal; Watch for note and a Rev 2 sentence on limiting the input to −1 to 1. |
| 45 | The Experiment-3 lab card gave no `activeLow` note; the Experiment-4 lab card said Lab 4 has no program. | Experiment-3 and Experiment-4 lab cards | **Fixed 2026-10-12.** |
| 46 | The Step3_MathLessons README credited Eberly code to lessons 15 and 16 (the article says 15, 16, and 18), said the headers used by Step1 and Step2 were unchanged without naming the Vector3.h corrections, and had no build record for lessons 17 to 19. | `Code-JUL/src/Step3_MathLessons/README.md` | **Fixed 2026-10-12.** |
| 47 | Code-JUL README said the five moved headers were unchanged, and that the Experiment-1 copies of Timer.h and Button.h differ in the folder line (they are identical). | `Code-JUL/README.md` | **Fixed 2026-10-12.** |
| 48 | The root README called Step1 and Step2 "commit f2307a1, unchanged"; their comments and include paths changed (the Intel HEX did not). | `README.md`, Testing Platform | **Fixed 2026-10-12.** |
| 49 | Lesson 04 printed "T2 Direction Components" for T4 and T5 and no title for T2 and T3. | `04_MiscMath/main.cpp` | **Fixed 2026-10-12.** |
| 50 | `RandomNumber::Random()` could return max: the float division of `random(2^31 − 1)` can round up to 1. | `Code-JUL/include/numerics/RandomNumber.h` | **Fixed 2026-10-12.** Divisor 2^24. |
| 51 | `Quaternion::GetEulerAngle()` returns the rotation angle in degrees, not Euler angles. | `Code-JUL/include/numerics/Quaternion.h` | **Documented 2026-10-12.** Comment added; the name is kept for existing programs. |
| 52 | The Vector3.h projection function was named `Project()` in Rev 1 and in the README and finding 33; its name is `ProjV()`. Article Rev 1, Part B, also cited line 128 for the Button of 18_MotorLineFit, which is now line 157. | Article 1004, Part B; READMEs; this file | **Fixed 2026-10-12** in Rev 2 and the repository. |

## Article 1004 Update Rev 1 Cross Review (2026-10-12)

Compared the repository with `1004_Experiments_Guide_20261012_Update.docx`, and the Copilot changes of commit cc69140 with `Copilot_Instructions_v2.4.0_20261012.txt` and `Copilot_Instructions_JoystickPower_20261012.txt`. Both instruction files were carried out as written. The article was then revised to `1004_Experiments_Guide_20261012_Update_Rev1.docx` (Update 20261012 Rev 1). Locations in the article are given by section, subsection, and paragraph or step.

| # | Finding | Location | Resolution |
|---|---------|----------|------------|
| 11 | Joystick axis assignment differs between documents. The repository code, the root README, and Article 1004, Table-1, use X on A1 and Y on A0; Article 1000 reportedly shows X on A0 and Y on A1. Article 1004, Experiment-2, Lab 3, directs the student to measure the axes and correct the software. | root `README.md`; `Code-JUL/src/Step1_Joystick/main.cpp`; Article 1000; Article 1004, The Signal Chain and Pin Assignments, Table-1 | **Open.** Article 1004 and the repository agree. Confirm the mapping in Article 1000; keep the measurement step. |
| 28 | `18_MotorLineFit` creates `Button(buttonPin, ledPin)` with the default `activeLow = true`. Article 1004, Part B, second paragraph, already tells the student to use `activeLow = false` for a pull down, but the Experiment-7 instructions did not. | `Code-JUL/src/Step3_MathLessons/18_MotorLineFit/main.cpp`, line 128 (line 157 since finding 39); `Experiments/Experiment-7/Instructions/README.md`, Lab 2 | **Fixed 2026-10-12.** Experiment-7, Lab 2, now names line 128, gives the `activeLow = false` form, and has the student test both button states before the motor supply is applied. Article Rev 1, Part B, second paragraph, names line 128. The code is unchanged, as the article directs the edit. |
| 29 | The source comments and the Experiment-6 and Experiment-8 instructions cited a section of Article 1004, Experiment-3, Powering the Joystick after Experiment-3, that did not exist in the Update 20261012 article. Table-9 listed Circuit-2 for Experiments 6 and 8, and Experiment-5, Lab 1, gave no power procedure although the joystick is on the drive 5 V bus from Experiment-3 onward. | Article 1004, Experiment-3; Part B, Table-9; Experiment-5, Lab 1, Code paragraph; `Experiments/Experiment-5`, `6`, `8/Instructions/README.md`; `1_Vector3`, `17_DeadZone`, `19_JoystickFrame` | **Fixed 2026-10-12, bench check open.** Article Rev 1 adds the subsection Powering the Joystick after Experiment-3 (after Experiment-3, Watch for) with a five step procedure, refers to it from Experiment-5, Lab 1, and from Table-9. The procedure addresses the reset interval: D5 to D10 float between a reset and the first statement of `setup()`, and opening the serial monitor resets the Uno, so the monitor is opened before the bench supply is applied. Author bench check still required: upload `1_Vector3` with the supply unplugged, measure D5 and D10 at 0 V, apply the supply, and confirm that no motor turns. |
| 30 | The experiment overview identified Article 1004 as DRAFT 4. | `Experiments.md`; `Experiments/Experiment-1` to `9/Instructions/README.md` | **Fixed 2026-10-12.** Every current label now reads Update 20261012 Rev 1. Historical entries keep their draft references. |
| 31 | `Copilot_Instructions_JoystickPower_20261012.txt` named a Method 1 and a Method 2; Method 2 was not defined in the article or the repository. | source comments of `1_Vector3`, `17_DeadZone`, `19_JoystickFrame`; Experiment-6 and Experiment-8 instructions; `RELEASES.md` | **Fixed 2026-10-12.** The article defines one procedure; the Method 1 and Method 2 wording is removed everywhere. |
| 32 | Experiment-2, Lab 3, wires the indicator LED to D12 (Circuit-2), but Step1_Joystick ships with `ledPin = 3` on line 48, and neither the article nor the lab card told the student to select the D12 form on line 50. | Article 1004, Experiment-2, Lab 3, step 2; `Experiments/Experiment-2/Instructions/README.md`; Troubleshooting, Table-10 | **Fixed 2026-10-12.** Article Rev 1, step 2, and the lab card give the edit; Table-10 refers to it. Step1_Joystick is unchanged. |
| 33 | Part B, first paragraph, said the five headers moved into `include/numerics` with their code unchanged. `numerics/Vector3.h` has two code corrections marked FIXED 20261008, in `Angle()` and `ProjV()`. | Article 1004, Part B, first paragraph; `Code-JUL/include/numerics/Vector3.h` | **Fixed 2026-10-12.** Article Rev 1 names the two corrections and states that the drive program calls neither function. |
| 34 | The Introduction said the two Article 1009 setup procedures are carried out in Experiments 2, 4, and 5; Experiment-3, Lab 2, also carries out L298N Setup, steps 1 to 4. | Article 1004, Introduction, first paragraph | **Fixed 2026-10-12.** Rev 1 reads Experiments 2 to 5. |
| 35 | The article cites Article 1003, Changing the PWM Frequency of Timer1, for reading the timer registers; the code comment cited Article 1002. | Article 1004, Experiment-4, Lab 3, Code paragraph; `Experiments/Experiment-4/Code/src/3_BitsLEDs/main.cpp` | **Fixed 2026-10-12.** The comment cites Article 1003. No line that the article cites moved. |
| 36 | Experiment-5, Lab 3, step 4, says to place comment marks on line 43 (`DEBUG_L298N`) of Common.h, which ships commented out. The step is correct only if Article 1009, L298N Setup, defines that flag earlier. | Article 1004, Experiment-5, Lab 3, step 4; `Code-JUL/include/Common.h`, line 43 | **Open.** Check against Article 1009, L298N Setup. |
| 37 | The article refers to tag v2.4.0 for every folder, line number, and printed value, and Bibliography [1] gives an access date of October 9, 2026; the tag does not exist yet. | Article 1004, Repository Release and Code; Bibliography [1] | **Open, author step.** Tag v2.4.0 on the commit that holds these changes, then set the access date of [1] to the tag date. |
| 38 | Part B, Eberly paragraph, names `numerics/LineFit2.h` and `numerics/Rotation.h` as the adapted files. `Matrix2x2.h`, `Matrix3x3.h`, and `Quaternion.h` also carry short GTE credits for their inverse corrections. | Article 1004, Part B, last paragraph; `Code-JUL/include/numerics/` | **Open, author decision.** These are credits for an approach, not adapted files; mention them in the article only if wanted. |

`CLAUDE.md`, the review note for this cross review, was removed once the findings above were recorded.

## Current Repository Consistency Review (2026-10-09)

| # | Finding | Location | Resolution |
|---|---------|----------|------------|
| 24 | The root README said every experiment's Instructions file was the article text, although Experiments 1 to 5 use lab cards and Experiments 6 to 9 contain the full advanced steps. | `README.md`, `Experiments.md`, `Experiments/Experiment-1` to `9/Instructions/README.md` | **Fixed.** Root README now distinguishes the two formats and agrees with `Experiments.md`. |
| 25 | `Code-JUL/README.md` reported 16 math lessons, but the project contains 19 lesson folders. | `Code-JUL/README.md`, `Code-JUL/src/Step3_MathLessons/` | **Fixed.** README now lists all 19 and distinguishes the first 16 simulated math lessons from hardware lessons 17 to 19. |
| 26 | Finding 12 below incorrectly said the Experiment-1 `Button.h` and `Timer.h` copies had corrected folder comments and differed only in that comment. The current snapshots intentionally retain the original `Folder: Code-JUL` comments. | `Discrepancies.md`, `Experiments/Experiment-1/Code/include/Button.h`, `Experiments/Experiment-1/Code/include/Timer.h` | **Corrected.** The copied headers are unchanged source snapshots; their original folder comments are retained intentionally, consistent with the Experiment-1 Code README and release notes. |
| 27 | Experiment-7 and Experiment-8 instructions used source line numbers that became stale after the follow up code and comment updates, which are now part of v2.4.0. | `Experiments/Experiment-7/Instructions/README.md`, `Experiments/Experiment-8/Instructions/README.md` | **Fixed.** Instructions identify the settings by symbol name rather than line number. |

## Code

| # | Finding | Location | Resolution |
|---|---------|----------|------------|
| 1 | Button wiring conflicted with the class default. The sketch set `pinMode(buttonPin, INPUT)` with the comment "Uses pull-down resistor" but constructed `Button(buttonPin, buttonLED)` with the default `activeLow = true`. On the first `updateButton()` the class calls `begin()`, which reconfigures the pin as `INPUT_PULLUP` and treats LOW as pressed, so a pull down wired button read as pressed at idle. `Code-JUL` (Step1 and Step2) uses the same default and therefore assumes the switch closes to ground. | `Experiments/Experiment-1/Code/src/3_Button/main.cpp` | **Fixed 20261008 (replaces the 20261007 fix).** The author's external 10 kΩ pull down wiring is kept, as Article 1009 describes, and the constructor is `Button(buttonPin, buttonLED, false)`; the `pinMode` line is removed. The series does not rely on the internal pull up resistors. |
| 2 | `upload_port = /dev/ttyACM0` hard coded (Linux device name). Uploads fail on macOS and Windows until edited. `Code-JUL/platformio.ini` leaves the port to auto detection. | `Experiments/Experiment-1/Code/platformio.ini` | **Fixed.** Line commented out with examples for Linux, macOS, and Windows. `monitor_speed = 9600` added to both projects. |
| 3 | `Code-JUL` compiles with `build_flags = -std=gnu++11`; the Experiment-1 project did not set a standard. | `Experiments/Experiment-1/Code/platformio.ini` | **Fixed.** Same flag added. |
| 4 | I2C code linked into every `Code-JUL` build. `Headers.h` included `BusI2C.h` and `build_src_filter` always included `+<DEP/>`, so `Wire` and the TWI driver were compiled into Step1 and Step2 although neither uses I2C. The build produced two warnings from `BusI2C.cpp` (unused parameter, comparison always true). | `Code-JUL/include/Headers.h`, `Code-JUL/platformio.ini`, `Code-JUL/src/DEP/`, `Code-JUL/include/BusI2C.h` | **Fixed.** Include, filter entry, folder, and header removed. Step2_JUL program size fell from 8196 to 6960 bytes and static data from 544 to 329 bytes; Step1_Joystick from 4708 to 3472 bytes and 512 to 297 bytes. The class remains available in the MageMCU Serial-Communication repository. |
| 5 | `Switch.h`, `Vector3.h`, and `TypeConv.h` are included through `Headers.h` but not used by either sketch. Templates cost nothing until instantiated, so this is a clarity issue. | `Code-JUL/include/Headers.h` | **Left as is.** Documented in `Code-JUL/README.md` as not used by the current sketches. Remove if no future sketch needs them. |
| 6 | Two dead zones exist in the signal chain. `Step2_JUL/main.cpp` zeroes inputs below 0.05 (X) and 0.06 (Y) before the algorithm; `Joystick.h` applies its own tolerance of 0.001. Only the 0.001 value was documented. | `Code-JUL/src/Step2_JUL/main.cpp`, `Motor-Movement-Checklist/ReadMe.md`, root `README.md`, Article 1004 Update, Experiment-5, Lab 3 | **Fixed 2026-10-12.** The root README, checklist, and current Article 1004 explain both the center offsets and the algorithm tolerance. |

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
| 12 | Header comments in the Experiment-1 copies of `Timer.h` and `Button.h` say "Folder: Code-JUL", reflecting their source location rather than the copy location. | `Experiments/Experiment-1/Code/include/` | **Intentional.** The files are preserved as original source snapshots; their comments are not rewritten in the copies. |
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

**Local build verification recorded 2026-10-07:** `pio run` completed successfully for all six projects in this repository on the Arduino Uno target. `avr-size` reported:

| Project | Program (bytes) | Static data (bytes) |
|---------|-----------------|---------------------|
| `Code-JUL` | 6262 | 288 |
| Experiment-1 | 2346 | 258 |
| Experiment-2 | 3268 | 222 |
| Experiment-3 | 3962 | 249 |
| Experiment-4 | 2046 | 190 |
| Experiment-5 | 7158 | 293 |

Since that record, the `setup()` of Experiment-5 `1_Vector3` and of lessons 17 and 19 gained the loop that holds D5 to D10 LOW (v2.4.0), so their sizes differ from the figures above; rebuild before flashing. **Build verification recorded 2026-10-12:** every program of the repository (Step1_Joystick, Step2_JUL, lessons 01 to 19, and the thirteen labs of Experiments 1 to 5) compiled with avr-gcc 7.3.0 and ArduinoCore-avr 1.8.6 (`-Os -Wall -Wextra`), with no warnings except the two unused variables of Step1_Joystick. Sizes are not recorded here because the core version differs from PlatformIO. These results establish compilation only. There is no automated host-side or PlatformIO unit-test suite in the repository; ADC interpretation, octant outputs, driver pin behavior, button timing, and motor behavior still need the separately listed software-vector and physical checks.

## Not changed, by design

- `Code-JUL/src/Step1_Joystick/main.cpp` and `Step2_JUL/main.cpp`: application logic was not changed in the 2026-10-07 header review; repository-name comments were standardized.
- `Button.h` and `Timer.h`: intentionally left unchanged in the 2026-10-07 header review.
- The other production headers listed in the Header Review section were changed as described there; do not interpret this section as saying those headers were untouched.
