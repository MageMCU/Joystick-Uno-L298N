# Releases & Active Study

**This repository is under active development.** All releases represent milestones in the ongoing joystick algorithm study and software refinement.

**Version numbers.** MAJOR.MINOR.FIXES. MAJOR changes break old names or the way of working; MINOR adds programs or features and keeps the existing names; FIXES counts debug fixes. A download file adds a letter for each attempt (v4.0.1.a, v4.0.1.b); the git tag carries the three numbers only. Adopted 20261021, from v4.0.1.

---

## v6.7.0 (2026-10-27), Coding rules in every program; Article 1009 references

Tag: v6.7.0, to be set by the author on the commit that holds this release and v6.6.0 (v6.6.0 was not committed on its own; download v6.7.0.b). Requested by the author on 20261027 after the review of Article 1009 revision 20261027b (Discrepancies.md, 221 to 226): the coding rules of Step2_JUL apply to the whole repository, without changing the code shown in the Article 1009 images. The layout of every program changes and the line numbers move, so the second number (MINOR) counts it; the author pushes MINOR releases.

- **Coding rules (221).** Every `.cpp` and `.h` file of `Code-JUL` and of the five experiment projects: no line over 80 characters, strings included; every comment on its own line above its statement (125 comments moved); comment lines wrapped at spaces, no word split; a long string continued after a backslash, or cut into adjacent strings, one per line, each piece starting with `\n` when the string does. Long statements are split after a comma or an operator. Two `#error` messages are shorter so that they fit (Step3_Generator and Step5_MathLessons). Two web addresses in `Debug.h` are written as Arduino reference names. The commented out `m_ptrSorted` of `Statistics.h` moves to a comment above its statement. The experiment copies of the headers are identical again in Experiments 1 to 5.
- **Not changed (221).** `Code-JUL/src/Step2_JUL/main.cpp` (Article 1009, Code-2a to Code-4, already within the rules) and every line of `L298N.h` shown in Article 1009, Image-4. `platformio.ini` keeps its layout, so `build_src_filter` stays on lines 31 to 37.
- **Step3_Generator and Step4_Generated (222).** Step4_Generated writes its title as one statement over four lines and its joystick center line after a backslash; the comment beside X_CENTER and Y_CENTER moves above them. Step3_Generator prints that layout: a printed `Serial.println()` line over 80 characters continues after a backslash. The serial output of both programs is unchanged.
- **Article 1009 references (223 to 225).** `L298N.h` cites Table-4 (the flags table; Table-3 before) and no longer names the author's Bits() value; Article 1009, Joystick Setup, becomes Article 1009, Step1, The Joystick Self Test, in the README files, `platformio.ini`, Step1_Joystick, the Experiment-2 card, and `LAB-NOTEBOOK-TEMPLATE.md`; the README tree cites Code-2a to Code-4; the README signal chain calls X_OFFSET and Y_OFFSET dead zones, not center offsets.
- **Line numbers (226).** The lab cards cite the lines moved by this release: Experiment-3 (lines 102, 108, and 109), Experiment-4 (`L298N.h`, lines 237 to 290), Experiment-5 Lab 1 (lines 102 and 103), Experiment-6 (lesson 17, lines 144 and 145), Experiment-7 (lesson 18, lines 185, 191, and 192), Experiment-8 (lesson 19, lines 124 and 125). Their Step2_JUL line numbers stay as they were (219, with Article 1004).
- **Documents.** `README.md` (Coding Rules, Status, tree, signal chain), `Code-JUL/README.md`, `Code-JUL/src/Step5_MathLessons/README.md`, `Motor-Movement-Checklist/ReadMe.md`, `Experiments.md`, lab cards 2 to 8, `LAB-NOTEBOOK-TEMPLATE.md`, `Discrepancies.md`.

Verified 20261027 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra -std=gnu++11`, link time optimization): 155 builds (Step1_Joystick to Step4_Generated, Step2_JUL with its debug switches off, every lesson with every topic, and the 13 lab programs), no warnings. All but Step3_Generator build to the same Intel HEX as v6.6.0, so their behavior is unchanged; Step3_Generator grows from 13676 to 13846 bytes of flash. In simavr, Step3_Generator (answers Enter, y, y, y, 0000, y, p) prints the same monitor text as v6.6.0 up to the program (Article 1009, Code-6, unchanged) and then prints the shipped Step4_Generated line for line. Article 1009 images: Code-1, Code-2a to Code-6, and Image-4 are unchanged. Bench tested by the author on 2026-10-28 (v6.7.0.a): passed.

Download v6.7.0.b (2026-10-28): the same code as v6.7.0.a (the same Intel HEX for all 155 builds); the documents record the bench test, the commit that holds v6.6.0 and v6.7.0, and the release tags (Discrepancies.md, 227).

---

## v6.6.0 (2026-10-27), Step2_JUL fits the article listings; line numbers replaced by names

Tag: none. v6.6.0 was not committed on its own; it is committed and tagged with v6.7.0. Requested by the author with Article 1009 revision 20261027a (Discrepancies.md, 216 to 220). The program behavior is unchanged; the release is MINOR so that it is pushed and Article 1009 can cite it.

- **Step2_JUL layout (216, 217).** Every line fits the 80 character cutoff of the Article 1009 listings: statements are 72 characters at most (78 in v6.5.0) and comments 76, so Code-2 to Code-4 show every line whole. Long strings are written as several strings, each starting with `\n` and closed before a backslash, which joins the next line to the statement; a backslash inside a string would print the indentation. Every comment is on its own line above its statement.
- **Names instead of line numbers (218).** Comments and printed text name the Bits() line, the analogRead() lines, the six pin lines, the debug switches, X_OFFSET and Y_OFFSET, and the line `pinMode(buttonPin, INPUT)`, so a moved line no longer makes a citation wrong. Step3_Generator and the shipped Step4_Generated print the new names; `platformio.ini` names its settings (build_src_filter, build_flags) instead of its line numbers.
- **Documents.** `README.md`, `Code-JUL/README.md`, `Code-JUL/include/claude/README.md`, `Code-JUL/src/Step5_MathLessons/README.md`, `Motor-Movement-Checklist/ReadMe.md`, `Discrepancies.md`. The lab cards keep their line numbers until Article 1004 is revised (219).

Verified 20261027 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization): Step2_JUL builds to the same Intel HEX as v6.5.0; Step1_Joystick, Step3_Generator, Step4_Generated, and lessons 17 and 20 build with no warnings. In simavr, Step3_Generator (answers Enter, y, y, y, 0000, y, p) prints the shipped Step4_Generated line for line. Not bench tested on its own; v6.7.0, which holds it, was bench tested by the author on 2026-10-28: passed.

---

## v6.5.0 (2026-10-25), Step1 center warning; Simple Drive and Fast Drive

Tag: v6.5.0, to be set by the author. Requested by the author after his review of v6.4.1.a with Article 1009 (Discrepancies.md, 210 to 215). A new feature (the Test 3 warning) that keeps the existing program names, so the second number (MINOR) counts it; the author pushes MINOR releases.

- **Step1_Joystick, Test 3 (212).** A center more than 50 counts from 511 fails (100 in v6.4.0 and v6.4.1): the joystick is exchanged. A center more than 25 counts from 511 passes with a warning that a new joystick is recommended, printed under Test 3 and after `Result: PASS` (author decision). 25 counts is about the dead zone of Step2_JUL (X_OFFSET 0.05), and Step2_JUL keeps the center 511, so beyond it its motors may turn slowly with the grip released; Step4_Generated corrects the center. New constant `CENTER_WARNING` and function `centerWarning()`. The report label reads `Center (511, within 50)`.
- **Allowed center (212).** 461 to 561 (411 to 611 in v6.4.0 and v6.4.1): the `#error` of Step3_Generator, the `static_assert` of `ace.h`, and `JoystickCenter.h`.
- **JoystickCenter.h (210).** The comments explain why the file was added, where it is used (Step1_Joystick, Step3_Generator, Step4_Generated through `ace.h`, lessons 17 and 20; not Step2_JUL), and how to update it. Step1_Joystick prints the same comments in the file it prints, so a replaced file keeps them. Added to the repository tree of `README.md`.
- **Comments corrected (211).** Step1_Joystick said that Step2_JUL moves each reading by the center and reads the file through `Common.h`; it does neither. `platformio.ini` said the filter is lines 32 to 37; it is lines 31 to 37.
- **Simple Drive and Fast Drive (213).** Path A and Path B are named Simple Drive (Step2_JUL with its debug switches commented out; recommended, and its code is the teaching guide) and Fast Drive (Step3_Generator and Step4_Generated; optional, advanced), as in Article 1009. "Fast" refers to the 50 ms control tick, not to the speed of the robot. `README.md`, `Code-JUL/README.md`, `Experiments.md`, the Experiment-5 and Experiment-6 cards, `LAB-NOTEBOOK-TEMPLATE.md`, `Motor-Movement-Checklist/ReadMe.md`, and the comments of `ace.h`. Earlier entries of this file and of `Discrepancies.md` keep the old names.
- **Article 1009 (215).** Revised to cite this release. Its bench captures, Code-1 to Code-6, are to be taken from v6.5.0.

Verified 20261025 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization): Step1_Joystick to Step4_Generated build with no warnings under `-std=gnu++11` and `-std=gnu++17`, the same sizes under both; Step1_Joystick 11584 bytes of flash (8966 in v6.4.1; the printed file now carries its comments). Step2_JUL, Step3_Generator, Step4_Generated, and lessons 17 and 20 build to the same Intel HEX as v6.4.1. In simavr, with scripted readings and answers: centers 511 and 511, 536 and 511, and 511 and 486 pass without a warning; 537 and 511, 511 and 485, and 561 and 470 pass with the warning; 562 and 511, and 511 and 460, fail Test 3 and print no file. The printed `JoystickCenter.h` equals the shipped file except the two values, and builds with Step1_Joystick and Step3_Generator; a center of 562 stops Step3_Generator with the `#error` message and Step4_Generated with the `static_assert` message. Bench test by the author pending.

---

## v6.4.1 (2026-10-25), Every lesson input printed; program titles

Tag: v6.4.1, to be set by the author on the commit that holds these changes (and v6.4.0, not yet committed). Requested by the author after his bench test of v6.4.0.a (passed): the lesson outputs did not give all the information (lesson 7, topic 13, did not print the scalar 3), and the serial monitor did not name the program, so a forgotten `platformio.ini` change went unnoticed (Discrepancies.md, 203 to 209). Corrections of output, so the third number (FIXES) counts them.

- **Program titles (204).** Each program prints, first, a blank line, a dotted line, its name, and `Selected in platformio.ini: +<StepN_.../>`. Step1_Joystick (line 667) and Step2_JUL (line 44, inside `DEBUG_SERIAL_ON`) print it in one statement on a line that was blank, so no cited line moves. Step3_Generator prints it in `printIntro()`, and its printed Step4_Generated prints it with `DEBUG_GENERATED` (line 132). `Step5_MathLessons/main.cpp` holds D5 to D10 LOW, then prints the lesson and topic, for example `Step5_MathLessons: lesson 7 (L07_Vector2), topic 13 (0: every topic)`.
- **Lesson inputs and labels (203, 205).** Code added, never removed; wrong or unclear labels corrected. Lesson 1, topic 6: a and the reversed value labelled, and the same bits in an `unsigned int` (45568 does not fit in an `int`, which stores -19968). Lesson 2: each byte named, in decimal and hex. Lessons 3, 5, 6: the map and the random intervals; lesson 6, topic 5, the starting array, the outlier of `QueueReset()`, and the new average; topic 1 prints the size as `10`. Lesson 4: a line that names the columns of topics 2 to 5; the input of topic 6. Lesson 7: `scalar: 3.00` (topic 13); `v5 = v3 ^ v4` (topic 9) and the subtitle `DotPerp`; `mag = v2.Magnitude() =` (topic 8). Lesson 8: subtitle `Vector2<float> v(1, 2);`. Lesson 11: the matrix of topic 2 labelled; `angle: 30 degrees` (topic 13). Lesson 12: `index = M.GetIndex(0, 1): 1` (topic 2), `det M: 5.00` (topics 6 and 7), the three 45 degree angles (topic 14), the ranges and `det A` (topic 15, with a line when A is not invertible). Lesson 14: `columns: w x y z`, the angles in the labels, a space after every label, `q = q.UnitQuaternion():` and `Norm Deviation (norm not 1):` (topic 2), the axis and the step of topics 8 and 9, and `c.GetAxis()` (topic 9, named Angle Axis, printed the angle only). Lesson 15: the data of each fit. Lesson 16: the quaternions of each check. Lesson 17: the centers of `include/JoystickCenter.h`, the average in ADC counts, and the offset about the file center. Lesson 18: each count echoed, and the five PWM and RPM pairs. Lesson 19: `MOUNT_ANGLE_DEG`, the ADC counts, and check labels that name the input vectors. Lesson 20: its centers from `include/JoystickCenter.h` (206), and its constants printed once. Every expected output block updated.
- **Cited lines (207).** Lesson 17, lines 139 and 140 (116 and 117); lesson 18, lines 179, 185, and 186 (168, 174, and 175); lesson 19 unchanged (123 and 124). Experiment-6, -7, -8, and -9 cards and `Experiments.md` updated.
- **Filter lines (208).** Every card and comment names `build_src_filter`, lines 31 to 37 (some said 32 to 37).
- **Memory (209).** The table of `Step5_MathLessons/main.cpp` rebuilt for all 20 lessons; the largest TOPIC 0 build is lesson 12, 19134 bytes of flash (59 percent); the most RAM, lesson 17, 1112 bytes (54 percent), unchanged.
- **Documents.** `README.md` (Status, Joystick Self Test), `Code-JUL/README.md` (Program titles, `JoystickCenter.h`), `Code-JUL/src/Step5_MathLessons/README.md`, `Experiments.md`, lab cards 2 and 5 to 9, `Discrepancies.md`.

Verified 20261025 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization): the four programs and every lesson with every topic, 141 builds, with no warnings, under `-std=gnu++11` and `-std=gnu++17`, the same sizes under both. Step2_JUL with both debug switches off and Step4_Generated without `DEBUG_GENERATED` build to the same Intel HEX as v6.4.0. In simavr: Step3_Generator (answers Enter, y, y, y, 0000, y, p) prints the shipped Step4_Generated line for line; every program prints its title; every lesson with TOPIC 0 runs to its end with no NaN, every line quoted in the expected output blocks of lessons 1 to 16 appears in the output (random values aside), and lessons 3, 15, 16, and 19 print `Failures: 0`; lesson 18 was run with a press and five typed counts. The 13 lab programs of Experiments 1 to 5 are unchanged and were not rebuilt. Bench test by the author pending.

---

## v6.4.0 (2026-10-25), Joystick center; filter written one folder per line

Tag: v6.4.0, to be set by the author on the commit that holds these changes. Approved by the author after his bench test of v6.3.1.a (Discrepancies.md, 200 to 202); a new feature that keeps the existing names, so the second number (MINOR) counts it.

- **The joystick center (200).** New file `Code-JUL/include/JoystickCenter.h`, `JOYSTICK_A0_CENTER` and `JOYSTICK_A1_CENTER`, shipped 511 and 511, which change nothing.
  - **Step1_Joystick.** Test 3 accepts a center within 100 counts of 511 (25 up to v6.3.1). After a pass, the report shows the measured centers and the centers now in the file, then prints a complete `JoystickCenter.h` between two marker lines, to be copied over the whole file. The `map()` calls of the report and the mapped column of the live values are removed; the live values show each reading's offset from the measured center.
  - **Step2_JUL and `Common.h`.** Not changed (author decision). Step2_JUL keeps the center 511; with an off center joystick its motors may turn slowly with the grip released during L298N Setup, which does not affect the `Bits()` value, found at full deflection. The push button OFF stops them.
  - **Step3_Generator.** Five items: Check 1 is the new joystick center check; the pin check, the joystick lines, the `Bits()` value, and the debug question follow as items 2 to 5. The printed program passes `TICK_MS`, `DEBOUNCE_MS`, `X_CENTER`, and `Y_CENTER` to `Ace`. The shipped Step4_Generated was printed again in simavr (answers Enter, y, y, y, 0000, y, p).
  - **ace.h.** Two template parameters at the end of the list, `X_CENTER` and `Y_CENTER`, default 511, checked for 411 to 611 by `static_assert`. `tick()` moves each reading by `CENTER - 511`, held inside 0 to 1023, before `compute()`, which is unchanged, so a resting grip gives the command 0. For a center of 511 no code is added, so a Step4_Generated printed before v6.4.0 builds to the same Intel HEX.
- **build_src_filter (201).** `Code-JUL/platformio.ini`, lines 31 to 37, one entry per line; a program is selected by giving its line `+` and the other four folder lines `-`. The README files, the lab cards of Experiments 2 and 5 to 9, and the comments of Step3_Generator, Step4_Generated, and Step5_MathLessons describe the new form.
- **Documents.** `README.md` (Joystick Self Test, Two Ways to Drive, Steps 3 and 4), `Code-JUL/README.md`, `Code-JUL/include/claude/README.md`, `Discrepancies.md`.

Verified 20261025 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, without link time optimization, because the PlatformIO registry could not be reached from the review environment; the sizes are therefore larger than those of `pio run`): Step1_Joystick to Step4_Generated and lessons 1 to 20 (TOPIC 0) build with no warnings with `-std=gnu++11` and `-std=gnu++17`. Step4_Generated, printed again, builds without `DEBUG_GENERATED` to the same Intel HEX as the v6.3.1 program without it, so its drive is unchanged with the shipped centers. Step2_JUL builds to the same Intel HEX as in v6.3.1. A `JoystickCenter.h` printed by Step1_Joystick in simavr (centers 560 and 470) builds with Step3_Generator and the printed Step4_Generated; a center of 700 stops the build with the error message. Host test: for the centers 511 and 511, 523 and 498, 411 and 611, 611 and 411, 560 and 470, 450 and 580, and all 1024 x 1024 pairs of readings, `ace.h` gives the same left and right commands as the float chain of Step2_JUL applied to the moved readings. Bench tested by the author (v6.4.0.a, 2026-10-25): passed.

---

## v6.3.1 (2026-10-22), Lesson fixes 192 and 193; full review

Tag: v6.3.1, to be set by the author on the commit that holds these changes. Approved by the author after v6.3.0.a (Discrepancies.md, 192, 193, and 196 to 199); debug fixes, so the third number (FIXES) counts them.

- **Lesson 3, topic 3 (192).** The table prints in columns of fixed width with `dtostrf()`, the AVR C library function that writes a float right aligned in a field (tabs up to v6.3.0). The lesson grows by about 1.4 KB of flash for TOPIC 0 (9106 bytes, 28 percent).
- **Lesson 11, topic 13, and lesson 13, topic 2 (193).** `Rotation()` and `Translation()` are called on a finished identity matrix `I` (`Matrix2x2<float> I; Matrix2x2<float> R = I.Rotation(...)`), not on the matrix being declared. Lesson 13 prints `T = I.Translation(v):`. The comments of `Matrix2x2.h` and `Matrix4x4.h` show the same form.
- **Printed text (196).** Lesson 4, topic 1: subtitles `Celsius`, labels `Map<float>(...)` (they read `Celcius` and `dM.map(...)`); lesson 11, topic 11: subtitle `Noncommutative`. Four comment typos corrected in lessons 2, 3, 12, and 14.
- **Documents (197, 198).** The memory table of `Step5_MathLessons/main.cpp` (lessons 3, 4, 11, 13); `Step5_MathLessons/README.md`; `Code-JUL/README.md`; the lab notebook template; `README.md` (Status); `Experiments.md`; the checks of `platformio.ini` (item 6, now with the lab programs); `Discrepancies.md`.

Verified 20261022 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization) with `-std=gnu++11` and with `-std=gnu++17`: 154 builds each (the four programs, every lesson with every topic, the 13 lab programs), no warnings, the same sizes under both standards. Only lessons 3, 4, 11, and 13 differ from v6.3.0; Step1_Joystick to Step4_Generated give the same Intel HEX as v6.3.0, so the Step1_Joystick of the bench test is unchanged. In simavr: lesson 3, topic 3, prints aligned columns and `Failures: 0`; lesson 11 prints the same lines as v6.3.0 except the subtitle `Noncommutative`; lesson 13, topic 2, the same except its label. Bench test by the author pending.

## v6.3.0 (2026-10-22), Step1_Joystick start question and columns; teaching blocks in every lesson

Tag: v6.3.0, to be set by the author on the commit that holds these changes. Requested by the author after the bench test of v6.2.3.a (Discrepancies.md, 188 to 195). New teaching content and new lesson output, so the second number (MINOR) counts it.

- **Step1_Joystick (188).** `waitForStart()` asks for Enter before Test 1 and repeats the question every 3 s; `discardInput()` empties the serial input before each question. Up to v6.2.3 the program printed Test 1 before the serial monitor was listening, or found a stray character waiting, so the first Enter ended Test 1 (FAIL) and Test 2 appeared first; `r` worked because by then the monitor was connected.
- **Step1_Joystick (189).** `printColumn()` prints right aligned numbers with spaces. The report header and rows used tabs; the row label `A0:   ` (6 characters) put every value one column left of its heading. The live values use the same columns. The note at `printColumn()` explains why `String(value, 3)` (Numerics, `TESTS/Common.h`) is not a column width: for a float it sets the decimal places, for an int the base.
- **Step5_MathLessons (190).** Every topic function has a teaching block: the hint (the last word or phrase of the name), the purpose, what is learnt, and the expected output. Code was added, never removed: getters and setters in topic 1 of lessons 7, 8, 9, 10, 13, and 14, the `Matrix4x4(Matrix2x2)` constructor (lesson 13) and the pure quaternion constructors (lesson 14), `GetElement(row, col)` in lesson 12, topic 2, and the copy assignment `v3 = v1;` after the copy constructor in lesson 7, topic 17, and lesson 9, topic 16 (191). Memory table of `main.cpp` updated for lessons 7 to 10, 12, 13, and 14.
- **`platformio.ini` (194).** The compiler notes are collected at the end of the file under COMPILER AND C++ STANDARD: the compiler version (avr-gcc 7.3.0) and the C++ standard (`-std=gnu++11`, `__cplusplus` 201103) are different numbers; `gnu++` and `c++`; selecting C++17; what avr-gcc 7.3.0 supports; the checks. No setting changes.
- Documents: `README.md` (Step1_Joystick, the D2 line citation 568 to 640, Status), `Experiments.md`, `Code-JUL/src/Step5_MathLessons/README.md`, and `Discrepancies.md`.

Verified 20261022 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization), with `-std=gnu++11` and again with `-std=gnu++17`: the four programs and every lesson with every topic, 141 builds each, no warnings, and each build the same size under both standards. Step2_JUL, Step3_Generator, and Step4_Generated give the same Intel HEX as v6.2.3; of the lessons only the 16 builds that contain new code differ. In simavr: Step1_Joystick repeats the start question until Enter, then runs Tests 1 to 5, prints the aligned report, and prints aligned live values; each changed lesson build prints every line of v6.2.3 in the same order, plus its new lines; lessons 1 to 16 match the expected outputs written in the blocks. Upload Step1_Joystick again; bench test by the author pending. The Experiment projects were not rebuilt.

## v6.2.3 (2026-10-22), Step2_JUL stops at once; Step4_Generated prints Ready

Tag: v6.2.3, to be set by the author on the commit that holds these changes. Approved by the author after the review of v6.2.2.b (Discrepancies.md, 184 and 185); two debug fixes, so the third number (FIXES) counts them.

- **Step2_JUL (184).** `loop()` calls `motors.PowerDownL298N()` on every pass while the push button state is OFF. Up to v6.2.2 the motors stopped only at the next control tick, up to 3 s later with the debug switches on, as shipped. Four lines added after line 181; no cited line moves.
- **Step3_Generator and Step4_Generated (185).** With `DEBUG_GENERATED`, the printed `setup()` ends with the line `Ready: press the push button; the LED on D12 shows ON.`, and the header says that the button is read after it (a press during the printout, about 1 s, is not seen). The shipped Step4_Generated was printed again.
- Documents: `README.md`, `Code-JUL/README.md`, the Motor Movement Checklist, the Experiment-5 card, `Experiments.md`, and `Discrepancies.md`.

Verified 20261022 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization): all 154 builds with no warnings; only Step2_JUL, Step3_Generator, and Step4_Generated differ from v6.2.2. Step2_JUL 9976 bytes of flash and 708 of RAM as shipped (with both switches); Step4_Generated 3306 and 200; Step4_Generated without `DEBUG_GENERATED` gives the same Intel HEX as v6.2.2. In simavr: Step2_JUL (switches on) has the enable pins LOW 0.3 s after the press OFF (up to 3 s before); Step2_JUL (switches off) and Step4_Generated set the same D5 to D10 and LED for 75 joystick positions; Step3_Generator prints the shipped Step4_Generated, which prints Ready. Upload Step2_JUL and Step4_Generated again; bench test by the author pending.

## v6.2.2 (2026-10-22), L298N.h enable pin variables renamed

Tag: v6.2.2, to be set by the author on the commit that holds these changes. Approved by the author (Discrepancies.md, 183); one debug fix, so the third number (FIXES) counts it.

- **`L298N.h`, `UpdateL298N()`.** The local variables `ENA` and `ENB` are `enPinA` and `enPinB`, each with a comment: they hold the enable pin of the class channel A or B, the pin that receives `_pwmA` or `_pwmB` after bit 3, not the module terminal of the same letter (in Circuit-1, D5 = `_EN_A` goes to L298N ENB). The same change in the five copies of `Experiments/Experiment-N/Code/include/`. No line moves.
- Documents: the Experiment-4 card (Lab 3), `Experiments.md`, `README.md` (Status), and `Discrepancies.md`.

Verified 20261022 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization): all 154 builds (the four programs, every lesson with every topic, the 13 lab programs) give the same Intel HEX as v6.2.1, with no warnings. No upload is needed.

Download b (v6.2.2.b, 20261022): after a full review and a functional analysis of the repository (Discrepancies.md, 184 to 187), documents only: the lab notebook template has a record for the Step1_Joystick self test and a wiring field for Experiment-5, Lab 3. Every Intel HEX file equals v6.2.2.a. Open for the author's approval: Step2_JUL stops the motors only at its next control tick, up to 3 s with the debug switches on (184); Step4_Generated with `DEBUG_GENERATED` does not read the button during its startup printout, about 0.75 s (185).

## v6.2.1 (2026-10-22), Pin names follow Circuit-1; any press fails the self test

Tag: v6.2.1, to be set by the author on the commit that holds these changes. Decisions of the author on Discrepancies.md, 175 and 176, and three items found while making them (179 to 181); debug fixes, so the third number (FIXES) counts them.

- **Pin names (175).** The Uno to L298N connections are the same in every step: Step2_JUL (lines 66 to 78) and Step3_Generator (lines 118 to 123) name each pin after the L298N input it is wired to in Article 1009, Circuit-1: `ENB = 5`, `IN4 = 6`, `IN3 = 7`, `IN2 = 8`, `IN1 = 9`, `ENA = 10` (up to v6.2.0 `ENA = 5`, `IN1 = 6` to `IN4 = 9`, `ENB = 10`). The pin numbers are unchanged, and so is the line count. Check 1 of Step3_Generator prints ENB D5 to ENA D10; the shipped Step4_Generated was printed again.
- **Reader instruction.** `README.md` (Wiring Checklist), the Motor Movement Checklist, and the Experiment-5 card: wire by the table and Circuit-1; a bench wired by the old names keeps the connection rules and needs no new wiring, the checklist finds its `Bits()` value, which belongs to that wiring; record it, or rewire to Circuit-1 with all power removed and run the checklist again.
- **Step1_Joystick (176).** Any press during Tests 3 to 5 fails the self test, with the line "Presses were counted: check the pull up resistor on D2." The pull up line is now 568.
- **Printed header (179, 180).** "STEPS 2 TO 4" and "DATA CHECKED IN STEP3_GENERATOR" in the program printed by Step3_Generator; its Check 1 comment cites lines 66 to 71 of Step2_JUL.
- **`BitsProof.py` (181).** One comment; same output.

Verified 20261022 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization): Step1_Joystick to Step4_Generated build with no warnings. Step2_JUL gives the same Intel HEX as v6.2.0. Step4_Generated, printed in simavr by Step3_Generator (answers y, y, 0000, y, p), differs from v6.2.0 in 14 lines only (the two header names and the six pin lines, in the comment and in the debug output), and without `DEBUG_GENERATED` builds to the same Intel HEX. Step1_Joystick: 7332 bytes of flash and 270 of RAM in this build; in simavr a passing run reports PASS, and the same run with one press during Test 4 reports FAIL. Bench test by the author pending.

## v6.2.0 (2026-10-22), Step1_Joystick asks for Enter; live values on request; full repository review

Tag: v6.2.0, to be set by the author on the commit that holds these changes. Requested by the author after v6.1.3.a (Discrepancies.md, 164 and 165): the output of Step1_Joystick scrolled after the self test, so its values could not be read. The self test changes the way it is used, and `DEBUG_STEP1_LIVE` is removed from Step1_Joystick only, so the minor number marks the change.

- **Step1_Joystick, controlled questions.** Each test prints one instruction and waits for Enter, with the line rules of Step3_Generator (`readLine()`, Backspace, CR, LF, and CR LF), then prints its reading and PASS or FAIL. The order is the push button first, then the axes: Test 1 press and hold the button (press Enter with the other hand), Test 2 release it, Test 3 the grip at rest (center), Test 4 to every edge (the ends are recorded every 20 ms until Enter), Test 5 released (return). The limits are those of v6.0.0. No test is timed: `SETTLE_MS`, `REST_MS`, `TIMEOUT_MS`, `MOVE_WINDOW`, and the state machine of `loop()` are removed. Presses are counted during Tests 3 to 5.
- **After the report.** The program asks: r runs the self test again; v prints A0 and A1, raw and mapped, and SW every 250 ms for 20 s (`PRINT_MS`, `LIVE_MS`), discards the keys typed meanwhile, and asks the question again. The report stays in view until the student answers.
- **No debug switch.** `DEBUG_STEP1_LIVE` is removed; the serial monitor output of Step1_Joystick is always on (author decision). The pull up line, `pinMode(buttonPin, INPUT)`, is now line 563 (formerly 485).
- **Full repository review** (Discrepancies.md, 166 to 178), documents only: `Code-JUL/README.md` (LESSON 1 to 20; lesson 20 in the `Timer.h` and `LinearMap.h` rows; the build note), `README.md` (the self test section, Steps 3 and 4, the bench runs, the Experiments table, Debugging, Status), `Experiments.md` (v6.2.0; the header copies), the Experiment-6 card, the lab notebook template, `include/Common.h` (one comment, line count unchanged), and `platformio.ini` (an en dash, comments only). Open for the author: the pin names of Step2_JUL and Step3_Generator (175), presses and the overall result (176), and Article 1009 (177).

Verified 20261022 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization): the four programs, every lesson with every topic, and the 13 lab programs of Experiments 1 to 5, 154 builds, with no warnings; only Step1_Joystick differs from v6.1.3 in Intel HEX. Step1_Joystick: 7246 bytes of flash (22 percent) and 270 of RAM in this build, 448 bytes more flash and 10 less RAM than v6.1.3 built the same way (6798 and 280; `pio run` reported 6818 for v6.1.0, so expect about 7266). In simavr with typed Enter keys, a pressed and released D2, and a swept joystick: all five tests pass; r runs again; v prints 79 lines in 20 s and the question returns; an r typed during the live values is discarded; a run with no press fails Tests 1, 2, 4, and 5 and counts the press made during Test 3. Bench test by the author pending.

## v6.1.3 (2026-10-22), Lesson 6 prints the array size in decimal; colons in the Experiment Common.h copies

Tag: v6.1.3, to be set by the author on the commit that holds these changes. Approved by the author after the review of v6.1.2.b (Discrepancies.md, 151 and 160); one debug fix, so the third number (FIXES) counts it.

- **Lesson 6, topic 1.** `printResult("Array Size: ", (float)stats.GetTuplesSize());`: the topic printed `Array Size: 1010`, because `printResult()` (Debug.h) calls `String(result, 2)`, which for an int means base 2. It now prints `Array Size: 10.00`. The comment of the topic explains the cast.
- **Experiments 1 to 5, `Code/include/Common.h`.** The two em dashes of each copy (lines 22 and 29) are colons, as the house style requires (entry 108). Comments only.
- `main.cpp` of Step5: the flash of lesson 6.

Verified 20261022 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization): of the 141 builds only lesson 6 (TOPIC 0 and 1) differs from v6.1.2.b; the 13 lab programs of Experiments 1 to 5 build to the same Intel HEX; no warnings. In simavr lesson 6, topic 1, prints `Array Size: 10.00`.

## v6.1.2 (2026-10-22), Lesson 12 solves with A; lesson 13 translates

Tag: v6.1.2, to be set by the author on the commit that holds these changes. Two debug fixes approved by the author (Discrepancies.md, 158 and 159), so the third number (FIXES) counts them.

- **Lesson 12, topics 8 and 15.** `x = Ainv.Solve(b)` is now `x = A.Solve(b)`: `Solve()` applies the inverse of the matrix it is called on, so the call on `Ainv` returned A b. Topic 8 now prints `A.Solve(b): (1.00, 1.00, 2.00)`, the same as `A.Cramer(b)`; in topic 15 both calls return the random x. The comments of both topics are updated.
- **Lesson 13, topic 2.** `Matrix4x4_T02_Translation()` builds the translation matrix of v = (1, 2, 3), prints it, and moves two points written with w = 1: (0, 0, 0, 1) to (1, 2, 3, 1) and (4, 5, 6, 1) to (5, 7, 9, 1). It printed its title only.
- `main.cpp` of Step5: the flash and RAM of lessons 12 and 13.

Download b (v6.1.2.b, 20261022): after a full review of the repository, comments and documents only (Discrepancies.md, 160 to 163): the comment of lesson 9, topic 8; the debug switch names in the Experiment-8 card, the Motor Movement Checklist, and `README.md`; the Step5 README. Every Intel HEX file equals v6.1.2.a. Lesson 6, topic 1, prints the array size in binary (160), open for the author's approval.

Verified 20261022 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization): of the 141 builds (four programs, every lesson with every topic), only lesson 12 (TOPIC 0, 8, 15) and lesson 13 (TOPIC 0, 2) differ from v6.1.1, all with no warnings. In simavr lesson 12, topic 8, prints (1.00, 1.00, 2.00) for both Solve() and Cramer(); topic 15 returns the random x with both; lesson 13, topic 2, prints the matrix and (1, 2, 3, 1) and (5, 7, 9, 1).

## v6.1.1 (2026-10-22), Teaching comments in the numerics headers and the lessons

Tag: v6.1.1, to be set by the author on the commit that holds these changes. Requested by the author (Discrepancies.md, 157). Comments only: every program, lesson, and topic builds to the same Intel HEX as in v6.1.0, so the third number marks the release, as v3.1.2 did for documentation.

- **Numerics headers.** Each of the 17 headers in `Code-JUL/include/numerics/` opens its class or functions with a block marked `TEACHING NOTES (v6.1.1)`: the terms of the subject, each defined at first use (for example mask, bitwise operator, row major order, determinant, cofactor, unit quaternion, least squares, slerp), and a worked example that can be checked by hand, taken from the robot where possible. Each function then has a short comment with its formula and a small example. Each subject is explained in one header and the others refer to it (Vector2.h for vectors, Matrix2x2.h for matrices, Statistics.h for the mean and the standard deviation).
- **Lessons.** Each of the 20 lessons opens with a `TEACHING NOTES (v6.1.1)` block: what the lesson teaches, the header that defines its terms, the values used and their results worked by hand, and the order of the topics. Each topic function has a comment with the expected output. In lessons 17 to 19 the notes are placed at the end of the file, so the lines cited by the lab cards of Experiments 7 and 8 (lesson 18, lines 168, 174, 175; lesson 19, lines 123 and 124) do not move; the line numbers of lessons 1 to 16 move, and no lab card cites them.
- **Found while writing the comments** (not changed, code changes wait for the author's approval): lesson 12, topics 8 and 15, call `Ainv.Solve(b)`, which prints A b instead of x, because `Solve()` already applies the inverse (Discrepancies.md, 158); lesson 13, topic 2, prints its title only (159). The comments of those topics say so.
- Documentation: `README.md` (Status), `Code-JUL/README.md`, the Step5 README (history), `Experiments.md`, and `Discrepancies.md`.

Verified 20261022 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization): the four programs and every lesson with every topic number, 141 builds, give Intel HEX files identical to v6.1.0, with no warnings.

## v6.1.0 (2026-10-22), Dotted lines; the two segment map in lessons 3 and 20

Tag: v6.1.0, to be set by the author on the commit that holds these changes. Requested by the author (Discrepancies.md, 154 to 157): Option A of v6.0.0 stays (Step2_JUL and Step4_Generated keep the full range map), plus lessons for the two segment map, and a dotted line at the start of each new output. No name changes, so the minor number marks the new features.

- **Dotted lines.** A blank line and a line of 48 dots start each new output: in Step1_Joystick each instruction, the report, and the live readout (`printDots()`); in Step2_JUL each control tick while a debug switch is defined (in `loop()`, so the cited lines of Step2_JUL do not move); in Step3_Generator each check, question, the summary, and the copy instruction (`printDots()`); in Step4_Generated the data block of `DEBUG_GENERATED`, printed so by Step3_Generator; in lesson 20 each sample. Step2_JUL without the switches builds as in v6.0.0.
- **Lesson 3, topic 3.** `LinearMap_T03_TwoSegment()`: the two segment map, low to center onto -1 to 0 and center to high onto 0 to 1, with `constrain()`, against the full range map of Step2_JUL, for the example values 12, 498, and 1010; self checking (`Failures: 0`). `LESSON_TOPICS` is 3.
- **Lesson 20.** `lessons/L20_JoystickMap.h`, one topic, `JoystickMap_T01_LiveCompare()`: the live joystick once per second, the raw reading, the full range map, the full range map after the dead zone of Step2_JUL, and the two segment map from the six values of a Step1_Joystick report; motor supply off, D5 to D10 held LOW. `main.cpp` accepts LESSON 1 to 20.
- **Step1_Joystick.** The line "Press the push button to run the self test again." moves from the end of the report to the start of the live readout; the pull up line is now 485 (formerly 472).
- Documentation: `README.md`, `Code-JUL/README.md`, the Step5 README (Layout, history), `main.cpp` of Step5 (instructions, memory table), `platformio.ini` (lesson list), `Experiments.md`, and `Discrepancies.md`. The size of Step1_Joystick in the v6.0.0 note is corrected.

Verified 20261022 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization, sizes as `pio run` reports them, flash = code and initialized data): Step1_Joystick 6818 bytes of flash (21 percent) and 280 of RAM; Step2_JUL, Step3_Generator, Step4_Generated, every lesson with TOPIC 0, and every topic of lessons 1 to 4 and 17 to 20 build with no warnings; LESSON 21 stops the build with the `#error`. In simavr: the Step1 self test passes and reruns with the dotted lines; Step2_JUL prints a dotted line each 3000 ms tick; Step3_Generator (answers y, y, 0000, y) prints Step4_Generated line for line as shipped; lesson 3, topic 3, prints `Failures: 0`; lesson 20 prints each sample after a dotted line. Bench test by the author pending, with that of Step5_MathLessons.

## v6.0.0 (2026-10-22), Joystick self test; setLatching() explained; debug switches by step

Tag: v6.0.0, to be set by the author on the commit that holds these changes. Requested by the author after the bench test of v5.1.0.a (20261022; Discrepancies.md, 144 to 153). `DEBUG_ALL_OFF` and `DEBUG_MAIN` are removed and the debug switches of Step2_JUL have new names in a new place, so the major number marks that break.

- **Step1_Joystick, a self test.** The serial monitor gives five instructions: leave the grip at rest, move it to every edge, release it, press the push button and hold it, release it. Each test moves on by itself when it is complete, or after 20 s. The report gives PASS or FAIL for each test, the low, center, high, and rest readings of A0 and A1 (formerly printed as x and y), and the presses seen during Tests 1 to 3, which reveal a floating D2. Test 1 passes a center within 25 counts of 511, the dead zone of Step2_JUL and Step4_Generated; Test 2 needs 200 counts each way on both axes; Test 3 a return within 25 counts of the center. The notes above `printReport()` name the wire to check for each failure. A press after the report runs the self test again.
- **Measured values and `map()`.** A PASS report prints two Arduino `map()` calls for each axis, low to center onto minus 100 to 0 and center to high onto 0 to 100, from the measured values. `DEBUG_STEP1_LIVE` (shipped on) then prints A0 and A1, raw and mapped (`constrain()` to minus 100 to 100), four times a second. Step2_JUL and Step4_Generated do not use these values (Discrepancies.md, 147).
- **`setLatching()`.** Step1_Joystick explains the two modes in `setup()` and why the self test uses the momentary mode; Step2_JUL calls `setLatching(true)`, the default of `Button.h`, with a comment, so the choice can be seen. Behavior unchanged.
- **Debug switches by step.** Step2_JUL defines `DEBUG_STEP2_JOYSTICK` and `DEBUG_STEP2_L298N` on lines 21 and 22, above its includes, shipped on. `Common.h` defines no flag of its own; it turns those two switches into `DEBUG_JOYSTICK` and `DEBUG_L298N`, which `Joystick.h` and `L298N.h` test unchanged, and sets `DEBUG_SERIAL_ON` and `BUTTON_TIMER_mS` as before. `DEBUG_ALL_OFF` and `DEBUG_MAIN` are removed; Step3_Generator and lessons 18 and 19 define no switch, and a comment of the same length replaces their `DEBUG_ALL_OFF` lines, so their line numbers do not change. Path A of Two Ways to Drive: comment out lines 21 and 22 of Step2_JUL.
- **Step2_JUL line numbers.** From line 18 on the lines move down by 6, from line 46 on by 11: `ledPin` 50 (formerly 44), the D3 form 48 (42), `Button()` 51 (45), `setLatching(true)` 56 (new), the pull up line 58 (47), the L298N pins 66 to 71 (55 to 60), `Bits()` 103 (92), `analogRead()` 114 and 115 (103 and 104), X_OFFSET and Y_OFFSET 132 and 133 (121 and 122). Step3_Generator, Step4_Generated (printed again), `ace.h`, and the documents cite the new numbers.
- Documentation: `README.md` (new section Joystick Self Test; Debugging; Two Ways to Drive; Status), `Code-JUL/README.md`, `platformio.ini` (comments), `Motor-Movement-Checklist/ReadMe.md`, `Experiments.md` (Changes in Release v6.0.0), the lab cards of Experiments 2, 5, and 7, the notebook template, `include/claude/README.md`, and `Discrepancies.md`.

Verified 20261022 (avr-gcc 7.3.0, ArduinoCore-avr, `-Os -Wall -Wextra`, link time optimization): every program, all 19 lessons with TOPIC 0, and the 13 lab programs of Experiments 1 to 5 build with no warnings. Step1_Joystick uses 6662 bytes of flash (21 percent) and 280 bytes of RAM (corrected in v6.1.0; 7500 bytes was a build without link time optimization); it runs in simavr through all five tests (PASS with a working joystick; FAIL for an open axis, a short travel; presses counted for a floating D2). Step2_JUL differs from v5.1.0 only by the `setLatching(true)` call (18 bytes without link time optimization), with the switches on and off. Lessons 18 and 19 build to the same Intel HEX as in v5.1.0. Step3_Generator, run in simavr with the answers y, y, 0000, y, prints Step4_Generated line for line as shipped. Bench test by the author pending (Discrepancies.md, 152).

## v5.1.0 (2026-10-21), One topic at a time; topic names

Tag: v5.1.0, to be set by the author on the commit that holds these changes. Requested by the author (Discrepancies.md, 138 to 143). A lesson printed all of its tests in one run, up to 17 in lesson 7; this release divides each lesson into topics and runs one topic at a time. TOPIC 0 keeps the way of working of v5.0.0, so the minor number marks a new feature.

- **One topic at a time.** `Code-JUL/src/Step5_MathLessons/main.cpp` has a second selection line, `#define TOPIC`, below `#define LESSON`. TOPIC 0 runs every topic of the lesson, in order, as before; a topic number runs that topic only. Each topic call in the `Setup()` of a lesson sits inside its own `#if TOPIC == 0 || TOPIC == n` and `#endif`. Each lesson defines `LESSON_TOPICS`; `main.cpp` stops the build with `#error` when TOPIC is below 0 or above it. The comments of `main.cpp` describe the five compiler directives used (`#define`, `#include`, `#if`, `#elif`/`#else`/`#endif`, `#error`) and the topic names, and give the flash and RAM of each lesson with TOPIC 0 and of its largest topic.
- **Topic names.** Every topic function is named `LessonName_Tnn_Operation()`: the lesson name, the topic number with two digits in the order of `Setup()`, and the operation in PascalCase. Every number is used once per lesson. Each title prints the same lesson name and topic number, for example `Vector3 T16 Copy using the equal sign`.
- **Titles in flash.** Every topic title is written as `printTitle(F("..."))`. With TOPIC 0 the RAM of lesson 7 drops from 1490 to 1058 bytes and of lesson 9 from 1444 to 1078.
- **Titles corrected.** Lesson 11 printed T3 for the Invertible test and T4 for the Determinate test (exchanged); "prosuct" (lesson 7), "Additin" (lessons 8 and 10), "Matric" (lesson 11), "Invertiable" (lesson 12), "Determinate" (lessons 11 and 12, now Determinant), and "UnitaryOperation" (lessons 11 and 12, the unary minus `operator-()`, now UnaryMinus; the printed label "Unitary Operator -M" is now "Unary Minus -M").
- **Lesson 19.** Part 1 moves from `Setup()` into `JoystickFrame_T01_RotationChecks()`, and Part 2 from `Loop()` into `JoystickFrame_T02_LiveJoystick()`; the pins D5 to D10 are still held LOW first, whatever the topic. The analogRead() lines are now lines 123 and 124 (formerly 133 and 134).
- **Lessons 17 and 18.** One topic each; `LESSON_TOPICS 1` is added at the end of the file, so the line numbers cited by the lab cards do not change. Code unchanged.
- `include/numerics/Statistics.h`: one comment names `Statistics_T05_QueueReset()`.
- Documentation: the Step5 README (One Topic at a Time, Layout, Verification), `Code-JUL/README.md`, `README.md`, `platformio.ini` (comments), `Experiments.md` (Changes in Release v5.1.0), and the lab cards of Experiments 6 to 9 (TOPIC line; topic names; Experiment-8 lines 123 and 124).

Renamed functions:

| Lesson | Renamed (old to new) |
|---|---|
| L01_Bitwise | `Bitwise_T1_Constructor` to `Bitwise_T01_Constructor`, `Bitwise_T2_SetBitNumber` to `Bitwise_T02_SetBitNumber`, `Bitwise_T3_ClearBitNUmber` to `Bitwise_T03_ClearBitNumber`, `Bitwise_T4_SetBitsValue` to `Bitwise_T04_SetBitsValue`, `Bitwise_T5_GetBitsValue` to `Bitwise_T05_GetBitsValue`, `Bitwise_T6_ReverseBits` to `Bitwise_T06_ReverseBits` |
| L02_TypeConv | `TypeConv_T1_WordTo2Bytes` to `TypeConv_T01_WordTo2Bytes`, `TypeConv_T2_DWordTo4Bytes` to `TypeConv_T02_DWordTo4Bytes` |
| L03_LinearMap | `LinearMap_T1_Inclusive_Test` to `LinearMap_T01_Inclusive`, `LinearMap_T2_Reverse` to `LinearMap_T02_Reverse` |
| L04_MiscMath | `MiscMath_T1_Map` to `MiscMath_T01_Map`, `MiscMath_T2_AngleRadian` to `MiscMath_T02_AngleRadian`, `MiscMath_T3_Angle2Radian` to `MiscMath_T03_Angle2Radian`, `MiscMath_T4_DirectionComponents` to `MiscMath_T04_DirectionComponents`, `MiscMath_T5_DirectionVector` to `MiscMath_T05_DirectionVector`, `MiscMath_T6_AbsoluteValue` to `MiscMath_T06_AbsoluteValue` |
| L05_RandomNumber | `RandomNumber_T1_RandomNumber_Test` to `RandomNumber_T01_Random` |
| L06_Statistics | `Statistics_T1_Constructor` to `Statistics_T01_Constructor`, `Statistics_T2_Average` to `Statistics_T02_Average`, `Statistics_T3_Standard_Deviation` to `Statistics_T03_StandardDeviation`, `Statistics_T4_Median` to `Statistics_T04_Median`, `Statistics_T5_Queue` to `Statistics_T05_QueueReset`, `Statistics_T6_Queue` to `Statistics_T06_Queue100` |
| L07_Vector2 | `Vector2_T1_Constructor` to `Vector2_T01_Constructor`, `Vector2_T2_GetVector` to `Vector2_T02_GetVector`, `Vector2_T3_Magnitude_Distance` to `Vector2_T03_MagnitudeDistance`, `Vector2_T4_UnitVector_Normalize` to `Vector2_T04_UnitVectorNormalize`, `Vector2_T5_Dot_Product` to `Vector2_T05_DotProduct`, `Vector2_T6_Angle` to `Vector2_T06_Angle`, `Vector2_T7_Perp` to `Vector2_T07_Perp`, `Vector2_T7_A_UnitPerp` to `Vector2_T08_UnitPerp`, `Vector2_T8_DotPerp` to `Vector2_T09_DotPerp`, `Vector2_T8_A_ZComp` to `Vector2_T10_ZComp`, `Vector2_T9_ProjV` to `Vector2_T11_ProjV`, `Vector2_T10_NegateVector` to `Vector2_T12_NegateVector`, `Vector2_T11_VectorScalarProduct` to `Vector2_T13_VectorScalarProduct`, `Vector2_T12_VectorVectorAddition` to `Vector2_T14_VectorVectorAddition`, `Vector2_T13_VectorVectorSubtraction` to `Vector2_T15_VectorVectorSubtraction`, `Vector2_T14_DotProduct` to `Vector2_T16_DotOperator`, `Vector2_T15_COPY` to `Vector2_T17_Copy` |
| L08_Point2 | `Point2_T1_Constructor` to `Point2_T01_Constructor`, `Point2_T2_GetPoint` to `Point2_T02_GetPoint`, `Point2_T3_VectorFromPointPointSubtraction` to `Point2_T03_VectorFromPointPointSubtraction`, `Point2_T4_PointFromPointVectorAddition` to `Point2_T04_PointFromPointVectorAddition` |
| L09_Vector3 | `Vector3_T1_Constructor` to `Vector3_T01_Constructor`, `Vector3_T2_GetVector` to `Vector3_T02_GetVector`, `Vector3_T3_Magnitude_Distance` to `Vector3_T03_MagnitudeDistance`, `Vector3_T4_UnitVector_Normalize` to `Vector3_T04_UnitVectorNormalize`, `Vector3_T5_Dot_Product` to `Vector3_T05_DotProduct`, `Vector3_T6_Cross_Product` to `Vector3_T06_CrossProduct`, `Vector3_T6_A_UnitCross_Product` to `Vector3_T07_UnitCross`, `Vector3_T7_Angle` to `Vector3_T08_Angle`, `Vector3_T8_ProjV` to `Vector3_T09_ProjV`, `Vector3_T9_NegateVector` to `Vector3_T10_NegateVector`, `Vector3_T10_VectorScalarProduct` to `Vector3_T11_VectorScalarProduct`, `Vector3_T11_VectorVectorAddition` to `Vector3_T12_VectorVectorAddition`, `Vector3_T12_VectorVectorSubtraction` to `Vector3_T13_VectorVectorSubtraction`, `Vector3_T13_DotProduct` to `Vector3_T14_DotOperator`, `Vector3_T14_CrossProduct` to `Vector3_T15_CrossPerpendicular`, `Vector3_T15_COPY` to `Vector3_T16_Copy` |
| L10_Point3 | `Point3_T1_Constructor` to `Point3_T01_Constructor`, `Point3_T2_GetPoint` to `Point3_T02_GetPoint`, `Point3_T3_VectorFromPointPointSubtraction` to `Point3_T03_VectorFromPointPointSubtraction`, `Point3_T4_PointFromPointVectorAddition` to `Point3_T04_PointFromPointVectorAddition` |
| L11_Matrix2x2 | `Matrix2x2_T1_Constructor` to `Matrix2x2_T01_Constructor`, `Matrix2x2_T2_Getters` to `Matrix2x2_T02_Getters`, `Matrix2x2_T3_Determinate` to `Matrix2x2_T03_Determinant`, `Matrix2x2_T4_Invertible` to `Matrix2x2_T04_Invertible`, `Matrix2x2_T5_Transpose` to `Matrix2x2_T05_Transpose`, `Matrix2x2_T6_Inverse` to `Matrix2x2_T06_Inverse`, `Matrix2x2_T7_Solve` to `Matrix2x2_T07_Solve`, `Matrix2x2_T8_UnitaryOperation` to `Matrix2x2_T08_UnaryMinus`, `Matrix2x2_T9_MatrixScalarMultiplication` to `Matrix2x2_T09_MatrixScalarMultiplication` |
| L12_Matrix3x3 | `Matrix3x3_T1_Constructor` to `Matrix3x3_T01_Constructor`, `Matrix3x3_T2_Access` to `Matrix3x3_T02_Access`, `Matrix3x3_T3_Determinate` to `Matrix3x3_T03_Determinant`, `Matrix3x3_T4_Invertible` to `Matrix3x3_T04_Invertible`, `Matrix3x3_T5_Transpose` to `Matrix3x3_T05_Transpose`, `Matrix3x3_T6_Adjoint` to `Matrix3x3_T06_Adjoint`, `Matrix3x3_T7_Inverse` to `Matrix3x3_T07_Inverse`, `Matrix3x3_T8_Solve` to `Matrix3x3_T08_Solve`, `Matrix3x3_T9_UnitaryOperation` to `Matrix3x3_T09_UnaryMinus`, `Matrix3x3_Find_Invertible_Matrix` to `Matrix3x3_T15_FindInvertible` |
| L13_Matrix4x4 | `Matrix4x4_T1_Constructor` to `Matrix4x4_T01_Constructor`, `Matrix4x4_T2_Translation` to `Matrix4x4_T02_Translation` |
| L14_Quaternion | `Quaternion_T1_Constructor` to `Quaternion_T01_Constructor`, `Quaternion_T2_NormSquared` to `Quaternion_T02_NormSquared`, `Quaternion_T3_Norm` to `Quaternion_T03_Norm`, `Quaternion_T4_Scale` to `Quaternion_T04_Scale`, `Quaternion_T5_UnitQuaternion` to `Quaternion_T05_UnitQuaternion`, `Quaternion_T6_Conjugate` to `Quaternion_T06_Conjugate`, `Quaternion_T7_Inverse` to `Quaternion_T07_Inverse`, `Quaternion_T8_QuaternionMultiplication` to `Quaternion_T08_Multiplication`, `Quaternion_T9_Quaternion_to_Angle_Axis` to `Quaternion_T09_ToAngleAxis` |
| L15_LineFit | `LineFit_T1_ExactLine` to `LineFit_T01_ExactLine`, `LineFit_T2_MotorCalibration` to `LineFit_T02_MotorCalibration`, `LineFit_T3_Degenerate` to `LineFit_T03_Degenerate` |
| L16_Rotation | `Rotation_T1_RotateVector` to `Rotation_T01_RotateVector`, `Rotation_T2_QuaternionToMatrix` to `Rotation_T02_QuaternionToMatrix`, `Rotation_T3_MatrixToQuaternion` to `Rotation_T03_MatrixToQuaternion`, `Rotation_T4_Slerp` to `Rotation_T04_Slerp`, `Rotation_T5_Drift` to `Rotation_T05_Drift` |
| L19_JoystickFrame | Part 1 of `Setup()` to `JoystickFrame_T01_RotationChecks()`; Part 2 of `Loop()` to `JoystickFrame_T02_LiveJoystick()` |

Verified 20261021 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, link time optimization): every lesson with TOPIC 0 and with each of its topic numbers, 134 programs, builds with no warnings; TOPIC 18 for lesson 7 and TOPIC -1 stop the build with the `#error`. Lessons 17 and 18 build to the same Intel HEX as in v5.0.0 with TOPIC 0 and 1. In simavr the TOPIC 0 output of every lesson matches v5.0.0 except the titles, the label Unary Minus of lessons 11 and 12, and the random values of lessons 03, 06, and 12, and each topic prints its part of the TOPIC 0 output; lessons 15, 16, and 19 print `Failures: 0`. The programs Step1_Joystick to Step4_Generated and the Experiment projects did not change. Bench test of lessons 17 to 19 pending (Discrepancies.md, 137).

## v5.0.0 (2026-10-21), One program for the math lessons; LED_PIN 12 in ace.h; bench test passed

Tag: v5.0.0, to be set by the author on the commit that holds these changes. Requested by the author with Article 1009, revision 20261021d, which cites this release in its Bibliography [1] (Discrepancies.md, 127 to 137). The lesson names and the way a lesson is selected change, so the major number marks that break.

- **Math lessons as headers.** `Code-JUL/src/Step5_MathLessons/` holds one `main.cpp` and the folder `lessons/` with 19 headers, `L01_Bitwise.h` to `L19_JoystickFrame.h`, each with a namespace of the same name; `setup()` and `loop()` of each lesson are now `Setup()` and `Loop()`, and the test functions are unchanged. The 19 folders `01_Bitwise/` to `19_JoystickFrame/` are removed. The second `#include "Arduino.h"` of lessons 02 and 07 is removed.
- **One lesson at a time.** `main.cpp` compiles ONE lesson, chosen with `#define LESSON` (1 to 19); a number outside that range stops the build with `#error`. Its comments give the instructions, the reason (32256 bytes of flash and 2048 bytes of RAM; all 19 lessons together would need about 145 KB and 9.8 KB), and the flash and RAM of each lesson.
- **`platformio.ini`.** Step5_MathLessons is selected like the other four programs, `+<Step5_MathLessons/>` with the other four excluded; the sixth filter entry for one lesson folder is removed. Line 31 still ships Step1_Joystick.
- **`include/claude/ace.h`.** The default of `LED_PIN` is 12, as in Article 1009, Circuit-1 (formerly 3); Step4_Generated passes 12 itself.
- **Line 47.** `README.md`, the comment of Step4_Generated, and the line that Step3_Generator prints for it name line 47 of Step2_JUL for the active LOW button (formerly line 45).
- **Bench test.** The author bench tested Step1_Joystick, Step2_JUL, Step3_Generator, and Step4_Generated on 2026-10-21 with release v4.0.1: all passed, and the indicator LED on D12 is good and consistent (Discrepancies.md, 130). The bench status is updated in `README.md`, `Code-JUL/README.md`, `include/claude/README.md`, `ace.h`, `L298NPins.h`, `Experiments.md`, and the notebook template.
- Documentation: the Step5 README, `Code-JUL/README.md`, `README.md`, `Experiments.md` (Changes in Release v5.0.0), and the lab cards of Experiments 6 to 9 (Running a lesson; new file names and line numbers); `include/claude/README.md`, two revision notes corrected (Discrepancies.md, 132).

Verified 20261021 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`, with and without link time optimization): Step1_Joystick, Step2_JUL, and Step4_Generated build to the same Intel HEX as in v4.0.1; Step3_Generator differs only in the printed character of line 523; every lesson builds through `main.cpp` with no warnings; with link time optimization, as `pio run` builds, 16 lessons build to the same Intel HEX as in v4.0.1 and lessons 06, 11, and 14 to the same instructions in every function in a different order; without it, `main.cpp` adds 4 to 8 bytes of flash, one jump from `setup()` and from `loop()` into the lesson (Discrepancies.md, 128). The Experiment projects did not change. Bench test of lessons 17 to 19 through the new `main.cpp` pending (Discrepancies.md, 137).

## v4.0.1 (2026-10-21), Button.h: internal or external pull up

Tag: v4.0.1, to be set by the author on the commit that holds these changes (v4.0.0 may be tagged on the same commit if it was not committed separately). FIXES release, comments only, requested by the author (Discrepancies.md, 123 to 126). Article 1009, revision 20261021c, cites this release in its Bibliography [1].

- `Code-JUL/include/Button.h`, the Wiring comment (formerly lines 59 to 64, now 59 to 74): the pin needs a pull up, the internal pull up set by `begin()` or the external 10 kOhm pull up of Article 1009, Circuit-1a, with `pinMode(pin, INPUT)` after `begin()`; the sentence "No external resistor is required" is removed; `activeLow = false` is kept as an option that Article 1009 does not use. The two usage examples give the indicator LED on D12, as in Circuit-1.
- The copies of `Button.h` in `Experiments/Experiment-1/Code/include/` to `Experiment-5/Code/include/` receive the same comments and stay byte for byte identical to `Code-JUL/include/Button.h`.
- `RELEASES.md`: the version note above, and this entry. `Discrepancies.md`, `Experiments.md`, and `README.md`: v4.0.1.

Verified 20261021 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`): the 23 Code-JUL programs build to the same Intel HEX as in v4.0.0, and the 13 Experiment programs to the same Intel HEX as in v3.2.2; no warnings. Bench test pending.

## v4.0.0 (2026-10-21), Steps renumbered; Step1_Joystick checks the joystick; LED on D12; wire once

Tag: v4.0.0, to be set by the author on the commit that holds these changes. Requested by the author with Article 1009, revision 20261021b, which describes this release and cites it in its Bibliography [1] (Discrepancies.md, 111 to 122). The folder names change, so every reference to the old names changes; the major number marks that break.

- **Programs renumbered** in the order of use: `Code-JUL/src/Step1_Joystick` (new), `Step2_JUL` (formerly Step1_JUL), `Step3_Generator` (formerly Step2_Generator), `Step4_Generated` (formerly Step3_Generated), and `Step5_MathLessons` (formerly Step4_MathLessons). `platformio.ini`: five folders in every `build_src_filter` line; line 31 ships Step1_Joystick.
- **Step1_Joystick** (new): the joystick connection check of Article 1009, Joystick Setup. Prints x (A0), y (A1), and the push button state four times a second; Button.h in momentary mode lights the LED on D12 while the button is held; Timer.h sets the 250 ms interval; D5 to D10 are held LOW. It finds an open wire, a dead axis, or a floating D2 before the motors get power, and it never aligns an axis.
- **Indicator LED on D12:** `Step2_JUL/main.cpp`, line 44 (`int ledPin = 12;`), with the D3 form of the advanced wiring as a comment on line 42; `Step3_Generator`, `LED_PIN = 12`; `Step4_Generated` printed again by Step3_Generator (bits_0000, with the debug data). The pin lines printed by the generator read lines 41 and 44.
- **Wire once:** `README.md`, Wiring Checklist, and `Code-JUL/README.md`: all of Article 1009, Circuit-1, before Step 1; Steps 1 to 4 use that wiring unchanged.
- **Push button:** the internal or the external 10 kOhm pull up (Article 1009, The Thumb Joystick; Circuit-1a), the same choice in Step1_Joystick (line 51) and Step2_JUL (line 47); the comment block at the end of Step2_JUL rewritten (comments only). Step4_Generated supports the external pull up only.
- Documentation: the README files, lab cards of Experiments 2, 3, 5, 6, 7, and 8, `Experiments.md` (Changes in Release v4.0.0), the notebook template, the Motor Movement Checklist ReadMe, `Common.h` and `ace.h` comments, and the lesson headers name the new folders; the Joystick and Button Check of Article 1009 is now Joystick Setup.
- `RELEASES.md` and `Discrepancies.md`: this entry and entries 111 to 122.

Verified 20261021 (avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, `-Os -Wall -Wextra`): Step1_Joystick, Step2_JUL, Step3_Generator, Step4_Generated, and all 19 lessons build with no warnings; Step2_JUL differs from v3.2.2 only in the LED pin; lessons 01 to 16, 18, and 19 build to the same Intel HEX as in v3.2.2 (Discrepancies.md, 121). Bench test pending.

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
- Fixed type mismatch in [Code-JUL/src/Step2_JUL/main.cpp](Code-JUL/src/Step2_JUL/main.cpp) (Step1_JUL from v3.0.0 to v3.2.2, Step2_JUL again since v4.0.0): `ActiveAlgorithm<float>()` → `Joystick<float>()`
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
