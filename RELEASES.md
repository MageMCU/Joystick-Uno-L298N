# Releases & Active Study

**This repository is under active development.** All releases represent milestones in the ongoing joystick algorithm study and software refinement.

---

## v3.2.2 (2026-10-20), Valid article links; MMC proof table in the README

Tag: v3.2.2, to be set by the author on the commit that holds these changes. Documentation and `.gitignore` only; no program code and no `platformio.ini` changed, and every program builds to the same Intel HEX as in v3.2.1 (Discrepancies.md, 102 to 110).

- **Links:** every Google Drive link now comes from the author's list of valid links of 20261020. Removed: 1020 Note, Button.h and Timer.h; the 1005 Drive link (the title stays in Experiment-9, the Articles table, and `Experiments.md`, linked to the Robotics page of carpentersoftware.com); the MMC Reference of `Motor-Movement-Checklist/ReadMe.md`. Added: 1009 MMC Results for JUL and 1009 MMC Results for nRF24L01+ in the Articles table of `README.md` and in the ReadMe section MMC Results; MMC Results for JUL in the Experiment-5 lab card (entries 102 and 103)
- `README.md`: new subsection MMC Proof Table under Setup: One Program, One Bits() Value, from `python3 BitsProof.py` run 20261020 (entry 104); the legend names the **standard** row, also in the ReadMe (entry 105); Testing Platform, Status: v3.2.2
- `README.md`: new section Contact, hello@carpentersoftware.com (entry 110)
- `.gitignore`: `.DS_Store` (entry 106)
- `RELEASES.md` and `Discrepancies.md`: em dashes and "firmware" replaced in the older notes (entry 108); `Discrepancies.md`: new section with entries 102 to 109. **Open:** the GitHub repository has no release tags (entry 107)
- `Experiments.md`: Changes in Release v3.2.2

Verified 20261020 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`): all 35 programs build with no warnings and to the same Intel HEX as e006f32; every relative Markdown link and anchor resolves; every Google Drive link in the repository is on the list of valid links. Bench test pending, as for v3.2.0.

## v3.2.1 (2026-10-19), Review with Article 1009 revision 20261019; Step3_Generated sets the L298N pins first

Tag: v3.2.1, to be set by the author on the commit that holds these changes. Documentation, comments, and one program change at the author's request: the program printed by Step2_Generator calls `robot.begin()` first in `setup()` (entry 85). No `platformio.ini` file changed. Article 1009, revision 20261019, describes this release and cites it in its Bibliography [1] (Discrepancies.md, 82 to 101).

- `Motor-Movement-Checklist/ReadMe.md`: other Uno pins are for the L298N only (lines 55 to 60 of Step1_JUL and the same six pins of Step2_Generator); the joystick stays on A0 and A1 (entry 83)
- `README.md`, wiring table, D2: the 10 kOhm pull up may use the Uno 5V pin or the 5 V bus of the breadboard; the Uno 5V pin is preferred, because the 5 V bus is off whenever the motor supply is off (entry 86)
- `README.md`, `Code-JUL/README.md`, and the Experiment-5 lab card, Two Ways to Drive: Path B runs Step2_Generator with the motor supply off and applies it after the upload, as Article 1009 does; Article 1009 gives the Path B procedure. `README.md`, Steps 2 and 3: the sentence "Step1_JUL remains the program of Article 1009" replaced (entry 88); `README.md`, Testing Platform, Status: v3.2.1 is documentation only
- `Discrepancies.md`: new section with entries 83 to 101; entries 61 and 69 closed; entry 82 closed for Article 1009 and open for Article 1004. Entry 85 closed by the program change below
- `Code-JUL/include/claude/ace.h`, lines 47 to 49: comment only; the sentence "Step1_JUL remains the program of Article 1009" replaced by the use of each program in Article 1009 (entry 88). `include/claude/README.md`: the control tick of Step1_JUL, 100 ms with the debug flags commented out and 3000 ms as shipped (entry 89)
- `Code-JUL/src/Step2_Generator/main.cpp`: `printProgram()` prints `robot.begin();` as the first line of `setup()`, with a SAFETY comment, ahead of the `#ifdef DEBUG_GENERATED` block, so D5 to D10 are outputs and LOW before the debug data is printed (entry 85); header comment Revised 20261019 (v3.2.1). `Code-JUL/src/Step3_Generated/main.cpp`: printed again by Step2_Generator for bits_0000 with the debug data, unedited
- `Experiments.md`: Changes in Release v3.2.1. `Experiments/LAB-NOTEBOOK-TEMPLATE.md`, Bench status: v3.2.1. `Code-JUL/README.md`, `src/` table: Step2_Generator and Step3_Generated rows
- Full repository review (entries 91 to 101): sizes of v3.2.1 in the performance tables of `README.md`, `Code-JUL/README.md`, and `include/claude/README.md`; Experiment-5 status in `README.md`; Used by columns and the line 31 description in `Code-JUL/README.md`; the shipped center offsets named wherever both drive paths are said to set the same pins (`README.md`, `Code-JUL/README.md`, lab cards of Experiments 5 and 6); `LAB-NOTEBOOK-TEMPLATE.md`, Experiment-2 heading and record, and a drive path line; the v3.0.0 folder name in the lab cards of Experiments 3, 6, 7, and 8; lesson sizes in `Step4_MathLessons/README.md`; the Code Snippet label of `Motor-Movement-Checklist/ReadMe.md`; comments only in `Code-JUL/platformio.ini` (C++ standard note) and the headers of lessons 15 to 19
- `RELEASES.md`: this entry

Verified 20261019 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`): all 35 programs build with no warnings; every program other than Step2_Generator has the flash and RAM sizes recorded for v3.2.0 (Step1_JUL 10546 and 710 bytes). Step2_Generator 13328 bytes of flash and 359 of RAM (13250 in v3.2.0, for the added comment line it prints); Step3_Generated 3654 and 200, the same size as before with `robot.begin()` moved. In simavr, D5 and D10 of Step3_Generated are outputs and LOW 0.0001 s after reset (0.626 s in v3.2.0), and Step3_Generated and Step1_JUL with the debug flags commented out set the same motor pins and duty cycles for the same button press and 13 joystick positions (entry 90). After the full review, Step1_JUL and all 19 lessons build to the same Intel HEX as the last commit (ad0c4e7), and every Markdown link resolves. The Code-1 and Code-2 listings of Article 1009 match `Code-JUL/src/Step1_JUL/main.cpp` line for line. Bench test pending, as for v3.2.0.

## v3.2.0 (2026-10-18), Bench findings: pull up, upload port, debug flags, 50 ms tick

Tag: v3.2.0. Requested by the author after a bench test (Discrepancies.md, 74 to 82). Articles 1004 and 1009 do not yet describe these changes (entry 82).

- **Push button:** the thumb joystick module has no resistor on SW, so the external 10 kOhm pull up from D2 to 5 V (Article 1004, Circuit-2) is required. `Code-JUL/src/Step1_JUL/main.cpp`: the comment block The Push Button records the bench result (comments only; line 45 stays as written). Experiment-3 Lab 2 (`2_DutyCycle`, lines 103 and 104) and lesson 18_MotorLineFit (lines 168 and 169) turn the internal pull up of D2 off after `button.begin()`, as Step1_JUL does (entries 74 and 75). Closes entry 71
- **Upload port:** `Code-JUL/platformio.ini` and the five Experiment `platformio.ini` files state that the `upload_port` line is required and add a commented `monitor_port` line; the READMEs and lab cards add the step before the first upload (entry 76)
- **Debug flags:** `Code-JUL/include/Common.h` defines `DEBUG_MAIN`, `DEBUG_JOYSTICK`, and `DEBUG_L298N` (lines 45 to 47) unless a program defines `DEBUG_ALL_OFF` before its first include. Step1_JUL is the diagnostic program (3000 ms tick); lessons 18 and 19 and Step2_Generator define `DEBUG_ALL_OFF`. New section Two Ways to Drive in `README.md` and `Code-JUL/README.md`, and in the Experiment-5 lab card: Step1_JUL with the three flags commented out (100 ms), or Step3_Generated (50 ms) (entry 77)
- **Control tick of ace.h:** `Code-JUL/include/claude/ace.h`, `TICK_MS` default 50 ms (100 ms before). `src/Step2_Generator/main.cpp` prints the 50 ms tick and the required pull up into the program; `src/Step3_Generated/main.cpp` printed again for bits_0000 with the debug data, unedited (entry 78)
- **Joystick lines:** Experiment-5 Lab 1 (`1_Vector3`, lines 101 and 102) and lessons 17_DeadZone (110 and 111) and 19_JoystickFrame (127 and 128) read x on A0 and y on A1, as Step1_JUL since v3.1.0 (entries 68 and 80)
- **Documents:** `README.md` (Quick Start, wiring table A0, A1, D2, and D12, Two Ways to Drive, Steps 2 and 3, Testing Platform, Next Steps), `Code-JUL/README.md`, `include/claude/README.md`, `Step4_MathLessons/README.md`, `Experiments.md` (Changes in Release v3.2.0), the lab cards of Experiments 1 to 8, `Code/README.md` of Experiments 1 to 5, `LAB-NOTEBOOK-TEMPLATE.md`, `Motor-Movement-Checklist/ReadMe.md` (entries 79 to 81)

Verified 20261018 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, without link time optimization): all 35 programs build with no warnings: Step1_JUL, Step2_Generator, Step3_Generated, the 19 lessons, and the 13 labs of Experiments 1 to 5. Lessons 01 to 16 and the 11 unchanged labs build to the same Intel HEX as in v3.1.2. Step1_JUL with the three flags commented out builds to the same Intel HEX as in v3.1.2; with the flags on, as shipped, 10546 bytes of flash and 710 bytes of RAM, and in simavr it prints its debug output. Lessons 18 and 19 and Step2_Generator build to the same Intel HEX as with the flags commented out. Step2_Generator, run in simavr with the answers y, y, 0000, y, p, prints the shipped Step3_Generated (3654 bytes of flash, 200 bytes of RAM, as in v3.1.2). Bench test pending.

## v3.1.2 (2026-10-18), Documentation: Step1_Joystick and bench status

Tag: v3.1.2. Documentation only; no program code changed, and every program builds to the same Intel HEX as in v3.1.1 (Discrepancies.md, 72 and 73).

- `README.md`, Setup: One Program, One Bits() Value: a paragraph states what Step1_Joystick did (Article 1009, Joystick Setup: choosing each `analogRead()` equation, plain or reversed, before the `Bits()` value was found) and why it was removed
- `README.md`, Testing Platform, Status; `Code-JUL/README.md`, `src/` programs table, Step1_JUL row; `Experiments/LAB-NOTEBOOK-TEMPLATE.md`, Bench status: Step1_JUL was bench tested at commit f2307a1 and has changed since (lines 46, 47, 103, 104), so its bench retest is pending
- `Discrepancies.md`: entries 72 and 73

## v3.1.1 (2026-10-18), Push button without the internal pull up

Tag: v3.1.1. Requested by the author: the push button is the joystick switch, SW, whose module circuit is unknown and may include its own pull up or pull down resistor, so the internal pull up of the ATmega328P is not used (Discrepancies.md, 70).

- `Code-JUL/src/Step1_JUL/main.cpp`: line 46 `buttonDebug.begin();` and line 47 `pinMode(buttonPin, INPUT);`, which turns the internal pull up of D2 off after `begin()` configured it as `INPUT_PULLUP`. They take the place of a blank line and the comment `// Joystick Algorithm`, so lines 41, 42, 45, 48, 55 to 60, 92, 103, and 104 keep their numbers. A comment block after `loop()`, The Push Button, gives the black box test and the three outcomes: module pull up (line 45 as written), module pull down (`Button(buttonPin, ledPin, false)`), or no resistor (add an external 10 kOhm resistor). `Button.h` is unchanged
- `Code-JUL/include/claude/ace.h`: the button pin is configured as an input with the internal pull up off (`AcePin::input()` in place of `inputPullup()`), as in Step1_JUL; the button is still read active LOW
- `README.md` (wiring table, D2; Testing Platform), `include/claude/README.md`: the same
- `Discrepancies.md`: entries 70 and 71

Verified 20261018 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Wall -Wextra`): Step1_JUL, Step2_Generator, and Step3_Generated build with no warnings. In simavr, after `setup()` of Step1_JUL and after the first `update()` of Step3_Generated, D2 is an input with its PORTD bit LOW (no pull up) and D3 is an output. Step2_Generator prints the same Step3_Generated as in v3.1.0. The host test of `ace.h` against Step1_JUL and `L298N.h` is unchanged: 0 differences. Bench test pending.

## v3.1.0 (2026-10-18), Steps reordered; generator checks the pins; joystick on A0 and A1

Tag: v3.1.0. Requested by the author after a bench test: with lines 103 and 104 of Step1_JUL exchanged, Step3_Generator (now Step2_Generator) printed a program with the joystick fixed on x A1 and y A0, so the joystick lines had to be changed in both programs (Discrepancies.md, 63). Article 1009 cites the line 31 filter and the joystick lines, which change in this release (Discrepancies.md, 69).

- Renamed in the order of use: `Step3_Generator` to `Step2_Generator`, `Step4_Generated` to `Step3_Generated`, `Step2_MathLessons` to `Step4_MathLessons` (Discrepancies.md, 67). Line 31 of `Code-JUL/platformio.ini` is `build_src_filter = +<*> +<Step1_JUL/> -<Step2_Generator/> -<Step3_Generated/> -<Step4_MathLessons/>`; the notes list the line for each program and one lesson
- `Code-JUL/src/Step1_JUL/main.cpp`: lines 103 and 104 read `xDigital = analogRead(A0)` and `yDigital = analogRead(A1)`, and stay as written; comments on lines 89 to 91 and 105 and 106 and in the connection rules after `loop()`. No other program code changed; line numbers 41, 42, 55 to 60, 92, 103, and 104 are kept. A bench calibrated with v3.0.1 reads its two axes exchanged and needs the value of the swap column of the checklist table (bits_1100 becomes bits_1101)
- `Code-JUL/src/Step2_Generator/main.cpp` (written with Claude): Check 1 shows ENA, IN1 to IN4, ENB, the push button, and the LED as Uno pins and ATmega328P port pins, for example `D5 (PD5)`; Check 2 shows the joystick lines, x on A0 (PC0) and y on A1 (PC1); Question 3 takes the four binary digits of the `Bits()` value; Question 4 asks whether the printed program carries the debug data. A summary of all four precedes the program (Discrepancies.md, 64 and 65)
- `Code-JUL/src/Step3_Generated/main.cpp`: printed again by Step2_Generator for bits_0000 with the debug data, unedited. `#define DEBUG_GENERATED` makes `setup()` print the data checked in Step2_Generator once at 9600 baud; comment it out to turn the output off. Answered n, Question 4 prints the program without the debug data, as before
- `Code-JUL/include/claude/ace.h`: template parameters `X_REVERSED` and `Y_REVERSED` and the two reversal lines of `tick()` removed (Discrepancies.md, 66)
- `Motor-Movement-Checklist/BitsProof.py` and `ReadMe.md`: the shipped lines are x on A0 and y on A1; the table is unchanged, its columns counted from the shipped lines
- `README.md`, `Code-JUL/README.md`, `include/claude/README.md`, `Step4_MathLessons/README.md`, the Experiment lab cards, `Experiments.md`, and every lesson header: the new folder names
- `Discrepancies.md`: entries 63 to 69

Verified 20261018 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Wall -Wextra`): Step1_JUL, Step2_Generator, Step3_Generated with and without `DEBUG_GENERATED`, and all 19 lessons build with no warnings. Step2_Generator runs in simavr with typed answers, including answers n, wrong entries, and r; answered y, 0000, y, it prints the shipped Step3_Generated, which prints the checked data in simavr. On the host, `Ace::compute()` matches the float chain of Step1_JUL for all 1024 x 1024 pairs of readings, and for all 16 `Bits()` values the pin levels and duty cycles set by `ace.h` with the pins of `L298NPins` match `L298N::UpdateL298N()` over 13818 pairs of readings each. `BitsProof.py`: 128 benches, exactly one value each. Bench test pending.

## v3.0.1 (2026-10-17), Step3_Generator binary only; build flags removed

Tag: v3.0.1. Step1_JUL is unchanged and builds to the same Intel HEX as v3.0.0. Article 1009 cites the line 31 filter, which now also excludes Step3_Generator and Step4_Generated (Discrepancies.md, 61).

- `Code-JUL/src/Step3_Generator/main.cpp` (written with Claude): the question reads the four binary digits of line 92 only; the decimal entry, the table of the 16 values, and the decimal line of the result were removed (Discrepancies.md, 60). `#ifdef STEP3_GENERATOR` and `#endif` removed; the printed program has no `#ifdef` line and names its `build_src_filter` line
- `Code-JUL/src/Step4_Generated/main.cpp`: printed again by Step3_Generator for bits_0000, unedited
- `Code-JUL/platformio.ini`: `env:step3`, `env:step4`, the flags `STEP3_GENERATOR` and `STEP4_GENERATED`, and `default_envs` removed. Line 31 is `build_src_filter = +<*> +<Step1_JUL/> -<Step2_MathLessons/> -<Step3_Generator/> -<Step4_Generated/>`; the notes list the line for Step3_Generator, Step4_Generated, and one lesson. `monitor_filters = default, log2file` in `env:uno`. Commented `upload_port` lines for macOS, Linux, and Windows (Discrepancies.md, 61 and 62)
- `README.md`, `Code-JUL/README.md`, `include/claude/README.md`, `Step2_MathLessons/README.md`, lab cards of Experiments 2 and 5, `.gitignore`: the new filter lines; no environments or flags
- `Code-JUL/platformio.ini`: comments only, Notes on the C++ standard: how to select C++17 (`build_unflags = -std=gnu++11`, `build_flags = -std=gnu++17`), what avr-gcc 7.3.0 supports, and the 20261017 check; the shipped setting stays `-std=gnu++11`
- `Code-JUL/platformio.ini`: comments only, Raspberry Pi 5 and Raspberry Pi OS, the author's development computer: the Uno's port (`/dev/ttyACM0`, or `/dev/ttyUSB0` for a CH340 clone), the commands that find it, and the dialout group; a commented `upload_port` line for the Raspberry Pi. The Ubuntu notes remain
- `Discrepancies.md`: entries 60 to 62

Verified 20261017 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6): Step1_JUL and Step4_Generated build to the same Intel HEX as in v3.0.0; Step3_Generator builds with no warnings (`-Wall -Wextra`) and runs in simavr with typed answers, and its printed program is the shipped Step4_Generated; each `build_src_filter` line in `platformio.ini` selects exactly one program folder; lesson 07_Vector2 builds with its line.

## v3.0.0 (2026-10-17), Step1_Joystick removed; Steps renumbered

Tag: v3.0.0, because folder names, environments, and build flags change. Article 1009 (revision 20261017) cites this release; Article 1004 DRAFT 4 still cites v2.4.0 and keeps the old names until it is revised.

Finding (Discrepancies.md, 53): whatever the analog pins, the two `analogRead()` equations, and the L298N connections, one four digit `Bits()` value corrects the motor movement of a working bench. The author's bench gave bits_1011 with the y equation reversed and bits_1100 with no change; a simulation of all 128 benches (8 joystick orientations times 16 L298N wirings) finds exactly one passing value for each.

- `Code-JUL/src/Step1_Joystick/` removed
- Renamed: `Step2_JUL` to `Step1_JUL`, `Step3_MathLessons` to `Step2_MathLessons`, `Step4_Generator` to `Step3_Generator`, `Step5_Generated` to `Step4_Generated`; `env:step4` to `env:step3`, `env:step5` to `env:step4`; `STEP4_GENERATOR` to `STEP3_GENERATOR`, `STEP5_GENERATED` to `STEP4_GENERATED`
- `Code-JUL/src/Step1_JUL/main.cpp`: comments only. Lines 89 to 91 state that one four digit value corrects any bench; two comment lines after line 104 state that the joystick lines need no change. Lines 42, 44, 45, 55 to 60, 92, 103, and 104 keep their numbers
- `Code-JUL/src/Step1_JUL/main.cpp`: a comment block after `loop()` lists the L298N and joystick connection rules that one `Bits()` value corrects (16 of the 720 ways to connect D5 to D10)
- `Code-JUL/src/Step1_JUL/main.cpp`, line 92, and `Step2_MathLessons/18_MotorLineFit/main.cpp`, line 163: ship with `bits_0000`, the first row of the Motor Movement Checklist, in place of the author's value; the student replaces it with the value found
- `Code-JUL/src/Step3_Generator/main.cpp`: `readLine()` accepts LF, CR, and CR LF line endings (an empty line with LF alone was skipped, so "Press Enter to begin" did not respond with the Arduino IDE ending Newline); `loop()` reads a whole line for r
- `README.md`, Wiring Checklist, D2: the joystick SW circuit is unknown and is tested as a black box
- `Code-JUL/platformio.ini`: line 31 is `build_src_filter = +<*> +<Step1_JUL/> -<Step2_MathLessons/>`; examples and environments renamed
- `Code-JUL/src/Step3_Generator/main.cpp` (written with Claude): one question, the `Bits()` value; the joystick lines are fixed as in Step1_JUL. `Step4_Generated/main.cpp` printed again by it for bits_0000
- `Code-JUL/include/claude/ace.h`, `include/numerics/MiscMath.h`, `LinearMap.h`, lessons 01 and 19: comments only
- `Motor-Movement-Checklist/BitsProof.py` (new, written with Claude) and a ReadMe section with the 128 bench table
- `README.md`, `Code-JUL/README.md`, `include/claude/README.md`, `Step2_MathLessons/README.md`, `Experiments.md`, lab cards of Experiments 2, 5, and 8: new names; Experiment-2, Lab 3, is the Joystick and Button Check with `DEBUG_JOYSTICK`
- `Experiments/Experiment-5/Code/src/1_Vector3/main.cpp`: comment on line 99 only

Verified 20261017 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6): Step1_JUL builds to the same Intel HEX as Step2_JUL of the last commit with line 92 set to `bits_0000`, the only change that is not a comment; it also builds with `DEBUG_JOYSTICK` and `DEBUG_L298N`; all 19 lessons build; Step3_Generator runs in simavr with typed answers (invalid entries, binary entry, answer again) with LF, CR, and CR LF endings; its printed program for bits_0000 is in Step4_Generated, unedited, and builds; every Experiment 1 to 5 lab builds; Markdown links resolve.

## Unreleased (2026-10-17), Code-1 and Code-2 comments match Article 1009; Steps 4 and 5 and include/claude

Code-1 and Code-2 comments:

- `Code-JUL/src/Step1_Joystick/main.cpp`: comments only. Lines 86 to 117 restored to the comment block printed in Article 1009, Code-1; the expected output block after the `Analogs` print removed, so the closing braces are on lines 121 and 122 as in Code-1
- `Code-JUL/src/Step2_JUL/main.cpp`: comments only. Lines 43, 54, 61, and 75 to 91 restored to the comments printed in Article 1009, Code-2, including the binary Bits table; the two group labels corrected to agree with Table-3 and `L298N.h`: line 82 `EN B & A` (bit 3 = 0, enable pins crossed, values 0 to 7), line 85 `EN A & B` (bit 3 = 1, enable pins straight, values 8 to 15)
- Line numbers cited in Article 1009 are unchanged; the program code of both files is unchanged
- The include folders of Experiments 1 to 5 keep the original `L298N.h` of commit f2307a1, whose Bits comment still carries the reversed labels

Steps 4 and 5, written with Claude (Anthropic), an AI assistant:

- `Code-JUL/src/Step4_Generator/main.cpp` (new): with the Uno and USB cable only, asks four questions in the serial monitor (1: x pin, A1 or A0; 2: x equation; 3: y equation; 4: `Bits()` value, decimal or binary, with the table of the 16 values), shows a summary, and prints the Step5 program. Choices a or b; Backspace corrects a typing error; r starts over. It writes nothing to D5 to D10
- `Code-JUL/src/Step5_Generated/main.cpp` (new): the program printed by Step4_Generator for the author's bench (x A1, y A0, bits_1010), unedited. It includes `claude/ace.h` only and creates one `Ace` object with the answers as template parameters
- `Code-JUL/include/claude/` (new folder): files written with Claude, kept apart from the original headers, which are unchanged
  - `L298NPins.h`: class `L298NPins` and struct `MotorPins`; resolves one `Bits()` value into the enable pin and the two direction pins of each command, with the rules of `L298N::Bits()` and `L298N::UpdateL298N()`
  - `ace.h`: class template `Ace`, the complete drive program in one file for speed and size. It incorporates `Joystick.h`, `LinearMap.h`, `absT()` of `MiscMath.h`, `Button.h`, `Timer.h`, `BUTTON_TIMER_mS` of `Common.h`, and `UpdateL298N()` and `PowerDownL298N()` of `L298N.h`, with register access in place of `analogRead()`, `digitalWrite()`, and `analogWrite()`, and integer math in place of float
  - `README.md`: the classes incorporated, performance, tests, and the reason for the folder
- `Code-JUL/platformio.ini`: new environments `env:step4` (flag `STEP4_GENERATOR`, monitor filter `log2file`) and `env:step5` (flag `STEP5_GENERATED`) and `default_envs = uno`, all appended after the notes; line 31 and every documented `build_src_filter` line are unchanged, and in `env:uno` the Step4 and Step5 folders compile to nothing
- `.gitignore`: monitor log files of `log2file`
- `README.md` and `Code-JUL/README.md`: Steps 4 and 5, `include/claude`, and the performance tables

Performance (simavr, 16 MHz, 1024 simulated joystick positions, bits_1010), Step2_JUL against Step5_Generated with `ace.h`: joystick math 322.5 µs against 16.4 µs per tick; motor output 40.3 µs against 3.7 µs; full control tick with the two ADC readings 574.8 µs against 232.0 µs (2.5 times faster; the ADC conversions are 91 percent of the faster tick); flash 6344 against 1420 bytes; RAM 316 against 23 bytes.

Verified 20261017 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, core linked as an archive as PlatformIO does):

- Step1_Joystick and Step2_JUL compile to the same Intel HEX as the last commit, with no flag, with the Step4 and Step5 folders present
- `Ace::compute()` gives the same commands as the float chain of Step2_JUL for all 1024 x 1024 pairs of readings (host test with the original headers); one float rounding case (x = 341, octant 4: 84.99998 truncated to 84) is reproduced on purpose
- In simavr, the port, timer, and compare registers after each motor update match the original code for 12519 pairs, and the float results on the Uno match the host test (same checksum)
- `L298NPins` with the printed motor code sets the same pin levels and duty cycles as `L298N::UpdateL298N()` for all 16 `Bits()` values and seven command pairs
- Step4_Generator run in simavr with typed answers (invalid entries, A and B, Backspace, decimal and binary, answer again); the printed program builds unedited in `env:step5`
- Bench tests of Step4_Generator and Step5_Generated are pending

---

## v2.4.0 (2026-10-12), Article 1004 Update Rev 2 and Article 1009 alignment

Tag `v2.4.0` marks the code that Article 1004 Update 20261012 Rev 2 and Article 1009 (20261007b) describe; compare a later release with this tag before revising either article.

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
- Also in this release (Part B lessons only):
  - `Code-JUL/src/Step3_MathLessons/19_JoystickFrame/main.cpp`: apply the positive mount angle rotation for a joystick mounted counterclockwise, matching the frame derivation and the Experiment-8 instructions.
  - `Code-JUL/src/Step3_MathLessons/18_MotorLineFit/main.cpp`: discard calibration counts entered while the joystick button is OFF; Experiment-7 explains how to reset between measurement sets and change the motor supply voltage safely.
- `Experiments/Experiment-1/Code/src/3_Button/main.cpp`: print label corrected to `Number of Loops/1000mS` (the count covers the 1000 ms LOW half); comment added above `loop()`
- `Experiments/Experiment-5/Code/src/1_Vector3`, `Code-JUL/src/Step3_MathLessons/17_DeadZone`, `19_JoystickFrame`: `setup()` first sets D5 to D10 as outputs and LOW, so the bench supply can be applied while these programs read the joystick (Article 1004, Experiment-3, Powering the Joystick after Experiment-3); the Experiment-5, Experiment-6, and Experiment-8 instructions refer to that section. The article defines one procedure; the earlier Method 1 and Method 2 wording is removed
- `Experiments/Experiment-2/Instructions/README.md`: Lab 3 note to select the D12 form of `ledPin` in Step1_Joystick (lines 48 and 50), as Circuit-2 wires the indicator LED to D12
- `Experiments/Experiment-7/Instructions/README.md`: Lab 2 directs the student to set `activeLow` on line 157 of 18_MotorLineFit to match the push button measured in Experiment-2, and to test both button states before the motor supply is applied
- `Experiments/Experiment-4/Code/src/3_BitsLEDs/main.cpp`: comment cites Article 1003, Changing the PWM Frequency of Timer1, as the article does (it cited Article 1002)
- `Code-JUL/src/Step3_MathLessons/17_DeadZone/main.cpp`: any key typed in the serial monitor repeats the measurement (it required a reset of the Uno); wiring comment matches the drive wiring with the bench supply applied
- `Code-JUL/src/Step3_MathLessons/18_MotorLineFit/main.cpp`: n starts a new set of five measurements, stops the motors, and returns the button state to OFF (it required a reset of the Uno); `button = Button(buttonPin, ledPin);` is now on line 157
- `Experiments/Experiment-6` and `7/Instructions/README.md`: no reset of the Uno while the bench or motor supply is applied; the key and n commands replace it
- `Experiments/Experiment-8/Instructions/README.md`: the diagonal positions may report either neighboring octant; a Watch for note on limiting a rotated input to the range −1 to 1 before it drives the motors
- `Experiments/Experiment-3` and `4/Instructions/README.md`: Experiment-3 lab card gives `activeLow` on line 97; Experiment-4, Lab 4, names the program uploaded before power is applied (Experiment-3, Lab 2)
- `Experiments/Experiment-5/Code/src/1_Vector3/main.cpp`: wiring comment matches the drive wiring with the bench supply applied
- `Code-JUL/src/Step3_MathLessons/04_MiscMath/main.cpp`: test titles T2 to T5 corrected
- `Code-JUL/include/numerics/RandomNumber.h`: divisor 2^24, so the result stays below max (code); `Quaternion.h`: note that `GetEulerAngle()` returns the rotation angle in degrees (comment only)
- `Motor-Movement-Checklist/ReadMe.md`: octant list corrected to the regions of Joystick.h; code snippet matches Step2_JUL and Table-1
- `Experiments/LAB-NOTEBOOK-TEMPLATE.md`: experiment records rewritten for the current labs (Experiment-1, Lab 4; Experiment-2 voltages; Experiment-3 keys 0 to 4, f, r; Experiment-4 LEDs and second motor; Experiment-5 positions of Table-8)
- `README.md`, `Code-JUL/README.md`, `Code-JUL/src/Step3_MathLessons/README.md`: header status, Vector3.h corrections, Eberly credits for lessons 15, 16, and 18, and the 20261012 build record
- Verified 20261012: Step1_Joystick, Step2_JUL, lessons 01 to 19, and every Experiment 1 to 5 lab compile with avr-gcc 7.3.0 and ArduinoCore-avr 1.8.6; Table-4, Table-8, and the outputs of Experiment-3, Lab 1, Experiment-4, Labs 1 and 2, and lessons 15, 16, and 19 (Part 1) agree with the article in simavr
- Lab cards, `Experiments.md`, and Experiment-6 to 9 instructions cite Article 1004 Update 20261012 Rev 2
- `CLAUDE.md` removed (review note, completed)

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
- ✅ **Single production algorithm:** revised octant-based approach locked in
- ✅ **Simplified to deploy:** no compile-time algorithm selection needed
- ✅ **New getter methods:** check motor direction and current octant
- ✅ **User-focused docs:** quick-start guides and wiring checklists
- ✅ **Ready to use:** software tested and verified on hardware

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

**⚠️ No Breaking Changes:** API remains compatible

If you were using algorithm variants (ALGO_STUDY_*):
- Remove `#define ALGO_STUDY_REVISED` or `ALGO_STUDY_COMPACT` from Common.h
- Replace `ActiveAlgorithm<float>` with `Joystick<float>` in main.cpp
- *(Full algorithm variants available in PRIVATE repo)*

---

## Version History (Details)

### [2.0.0], 2026-07-14

**Major Changes**
- Replaced original `Joystick.h` with revised octant-based algorithm
- Removed `Algorithm_Study_Revised.h` and `Algorithm_Study_Compact.h` from active code
- Simplified compile-time algorithm selection (no more `ALGO_STUDY_*` preprocessor flags)
- Cleaned up `Common.h` and `platformio.ini` build configuration

**New Features**
- Added `IsLeftForward()` getter: checks whether the left motor is moving forward
- Added `IsRightForward()` getter: checks whether the right motor is moving forward
- Added `Octant()` getter: returns the current directional octant (0 to 8)
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
- Fixed type mismatch in [Code-JUL/src/Step2_JUL/main.cpp](Code-JUL/src/Step1_JUL/main.cpp) (now Step1_JUL): `ActiveAlgorithm<float>()` → `Joystick<float>()`
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

### [1.0.0], Original Release

**Status:** Archived (see PRIVATE repo for experimental variants)

**Contents:**
- Initial software for Arduino Uno + L298N differential drive motor control
- Original joystick algorithm (quadrant-based routing)
- Algorithm selection system with study variants
- Motor movement checklist for hardware validation

---

## Technical Notes

- Namespace: **csjc** (Carpenter Software, Jesse Carpenter)
- Hardware: **Arduino Uno (Atmega328P)** + **L298N Motor Driver**
- IDE: **PlatformIO** (VS Code)
- Language: **C++** (GNU++11)
- Status: **Active through end of 2026**

See [Repository Status & History](README.md#repository-status--history) for information about the relationship to the predecessor experimental repository.
