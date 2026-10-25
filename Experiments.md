# Experiments

The experiments of Article 1004, *Experiments for Joystick-Uno-L298N* (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. The article gives the objective, prediction, steps, and expected output of Experiments 1 to 5; each of their `Instructions/README.md` files is a lab card with the folders, filter lines, and wiring used at the bench. Experiments 6 to 9 are summarized in Part B of the article, and their `Instructions/README.md` files hold the full steps. The article refers to release v2.4.0 of this repository; schematics Circuit-1 to Circuit-4 are in [Experiments/Circuits](Experiments/Circuits).

## Changes in Release v6.4.1 (20261025)

- **Program titles.** Every step prints its name first, after a blank line and a dotted line, with the `build_src_filter` entry that selects it, for example `Step2_JUL: the diagnostic program (L298N Setup)` and `Selected in platformio.ini: +<Step2_JUL/>`. Step5_MathLessons also names the lesson and the topic. A wrong name in the serial monitor means `platformio.ini` still selects another program. Step2_JUL prints its title only with a debug switch on, as shipped for Experiment-2 Lab 3 and Experiment-5 Lab 3, and Step4_Generated only with `DEBUG_GENERATED`; no cited line of Step1_Joystick or Step2_JUL moves.
- **Lessons print every input.** Each topic prints the values it uses (the scalar of lesson 7, topic 13, the angles of lessons 11, 12, and 14, the random intervals of lessons 3, 5, and 6, the data of lesson 15, and so on), and wrong labels are corrected. Lessons 17 and 20 use the centers of `include/JoystickCenter.h`. The new lines move the cited lines of lessons 17 and 18: lesson 17, lines 139 and 140 (Experiment-6); lesson 18, lines 179, 185, and 186 (Experiment-7). Lesson 19 keeps lines 123 and 124 (Experiment-8). Experiment-9: lesson 14, topic 8, prints two input lines before its data.
- **Filter lines.** Every lab card names `build_src_filter`, lines 31 to 37 (up to v6.4.0 some cards said 32 to 37, the entries without the line `build_src_filter =`).

## Changes in Release v6.3.1 (20261022)

- **Lessons 3, 11, and 13.** Lesson 3, topic 3, prints its table in aligned columns; lesson 11, topic 13, and lesson 13, topic 2, call `Rotation()` and `Translation()` on a finished identity matrix. Experiment-6 runs lesson 3 and Experiment-8 runs lessons 11 and 13 (Part A); their output is the same except the column layout of lesson 3, topic 3, and the label `T = I.Translation(v):` of lesson 13, topic 2. No line cited by a lab card moves.
- **Review.** The 13 lab programs of Experiments 1 to 5 build with no warnings with `-std=gnu++11` and with `-std=gnu++17`.

## Changes in Release v6.3.0 (20261022)

- **Step1_Joystick.** The self test asks for Enter before Test 1 and repeats the question every 3 s, so Test 1 is no longer skipped when the serial monitor connects; the report and the live values print in aligned columns.
- **Lessons.** Every topic function carries a teaching block (hint, purpose, what is learnt, expected output). In lessons 17 to 19 the blocks are at the end of the file: no line cited by a lab card moves (lesson 17, lines 116 and 117; lesson 18, lines 168, 174, and 175; lesson 19, lines 123 and 124). Lessons 17 to 20 build to the same Intel HEX as in v6.2.3.

## Changes in Release v6.2.3 (20261022)

- **Step2_JUL stops at once.** Pressing the push button OFF stops the motors at once, not at the next control tick (3000 ms with the debug switches on, as shipped for Experiment-2 Lab 3 and Experiment-5 Lab 3). No line cited by a lab card moves.
- **Step4_Generated prints Ready.** With `DEBUG_GENERATED`, the last startup line, Ready, tells when the push button is read.

## Changes in Release v6.2.2 (20261022)

- **L298N.h.** In `UpdateL298N()` the two local enable pin variables `ENA` and `ENB` are `enPinA` and `enPinB` (Code-JUL and the copies of Experiments 1 to 5): they hold the enable pin of the class channels A and B (`_pwmA`, `_pwmB`), not the module terminals ENA and ENB. Every lab builds to the same Intel HEX; no line moves. Experiment-4, Lab 3, reads the function.

## Changes in Release v6.2.1 (20261022)

- **Pin names.** Step2_JUL, Step3_Generator, and Step4_Generated name the Uno pins after the L298N inputs of Circuit-1 (`ENB = 5`, `IN4 = 6`, `IN3 = 7`, `IN2 = 8`, `IN1 = 9`, `ENA = 10`); the pin numbers and the programs are unchanged. The Experiment-5 card tells the reader what to do with a bench wired by the old names.
- **Step1_Joystick.** A press during Tests 3 to 5 fails the self test.

## Changes in Release v6.2.0 (20261022)

- **Joystick self test with questions.** Step1_Joystick tests the push button first, then the axes, and waits for Enter after each instruction, so every result can be read before the next test; after the report it asks r (run again) or v (the live values for 20 seconds). `DEBUG_STEP1_LIVE` is removed. No lab card changes; Experiment-2 Lab 3 and Experiment-5 Lab 3 still select Step2_JUL.

## Changes in Release v6.1.3 (20261022)

- **Common.h copies.** The em dashes in `Code/include/Common.h` of Experiments 1 to 5 are colons (comments only; the lab programs build as before).

## Changes in Release v6.1.1 (20261022)

- **Teaching notes.** The numerics headers and the lessons used by Experiments 6 to 9 define their terms and work examples by hand (`TEACHING NOTES (v6.1.1)`). Comments only; the line numbers cited by the lab cards of Experiments 7 and 8 do not change.

## Changes in Release v6.1.0 (20261022)

- **Dotted lines.** Step1_Joystick to Step4_Generated start each new output in the serial monitor with a blank line and a dotted line; in Experiment-2 Lab 3 and Experiment-5 Lab 3 each 3000 ms tick of Step2_JUL starts with them.
- **Two segment map.** Lesson 3 has a third topic, the two segment map around a measured center, and lesson 20 compares it with the full range map on the live joystick. No lab card changes; the lessons follow the Step1_Joystick self test (Article 1009, Joystick Setup).

## Changes in Release v6.0.0 (20261022)

- **Joystick self test.** Step1_Joystick asks the student, in the serial monitor, to leave the grip at rest, move it to every edge, release it, and press and release the push button, then reports PASS or FAIL for each test with the measured readings of A0 and A1 and the `map()` calls that fit the joystick (Article 1009, Joystick Setup).
- **Debug switches.** Step2_JUL defines its debug switches itself, `DEBUG_STEP2_JOYSTICK` and `DEBUG_STEP2_L298N` on lines 21 and 22; `Common.h` no longer defines flags, and `DEBUG_ALL_OFF` is removed. Experiment-2 Lab 3 and Experiment-5 Lab 3 need no change (both switches on as shipped); Path A comments out lines 21 and 22.
- **Lab cards 2, 5, and 7.** New Step2_JUL line numbers (the lines move down by 6 from line 18 and by 11 from line 46) and `setLatching(true)` on line 56; lessons 18 and 19 keep their line numbers.

## Changes in Release v5.1.0 (20261021)

- **One topic at a time.** Each math lesson is divided into topics, one function per topic. `#define TOPIC` in `Code-JUL/src/Step5_MathLessons/main.cpp`, the line below `#define LESSON`, runs one topic; TOPIC 0 runs every topic, as before. Lesson 7 printed 17 tests in one run; a reader now studies one topic per run.
- **Topic names.** Every topic function is named LessonName_Tnn_Operation, for example `Vector3_T16_Copy()`, with a two digit topic number used once per lesson, and it prints the same name as its title. The duplicate numbers of lessons 7 and 9, the unnumbered topic of lesson 12, and the spelling of the titles are corrected (RELEASES.md, v5.1.0).
- **Lab cards 6 to 9.** Running a lesson gives the TOPIC line; Experiment-7 and Experiment-9 name the topics they use; Experiment-8 names the two topics of lesson 19 and its joystick lines, now 123 and 124.

## Changes in Release v5.0.0 (20261021)

- **Math lessons as headers.** Each of the 19 lessons is one header file in `Code-JUL/src/Step5_MathLessons/lessons/`, from `L01_Bitwise.h` to `L19_JoystickFrame.h`, with its own namespace of the same name. One `main.cpp` in `Step5_MathLessons` compiles ONE lesson, chosen with `#define LESSON` (1 to 19); its comments give the instructions and the flash and RAM of each lesson. Step5_MathLessons is selected in `platformio.ini` like the other four programs. Each lesson builds to the same code as in v4.0.1. The lab cards of Experiments 6 to 9 give the new file names and line numbers.
- **Bench test.** The author bench tested Step1_Joystick, Step2_JUL, Step3_Generator, and Step4_Generated on 20261021 (release v4.0.1) with the indicator LED on D12: all passed.
- **ace.h.** The default of `LED_PIN` is 12, as in Article 1009, Circuit-1; Step4_Generated passes 12 itself, so no program changed.

## Changes in Release v4.0.1 (20261021)

- **Button.h comments.** The wiring comment of `Button.h` gives the internal or the external 10 kOhm pull up (Article 1009, Circuit-1a), and the usage examples give the LED on D12. The copies in Experiments 1 to 5 are updated and stay identical; no program changed.

## Changes in Release v4.0.0 (20261021)

- **Programs renumbered.** `Code-JUL/src` holds five programs in the order of use: Step1_Joystick (new), Step2_JUL (formerly Step1_JUL), Step3_Generator, Step4_Generated, and Step5_MathLessons. `platformio.ini` ships with Step1_Joystick on line 31; Experiment-2 Lab 3 and Experiment-5 Lab 3 copy the Step2_JUL line over it.
- **Step1_Joystick.** Checks the joystick connections, x on A0, y on A1, and the push button on D2 with the LED on D12, with the motor supply off and D5 to D10 held LOW (Article 1009, Joystick Setup). It finds the faults that no `Bits()` value corrects before the motors get power.
- **Wire once.** The whole bench of Article 1009, Circuit-1, is wired before Step 1, and Steps 1 to 4 use that wiring unchanged.
- **Indicator LED on D12.** Step2_JUL (line 50) and Step3_Generator ship with the LED on D12, as wired in Circuit-1; Step4_Generated is printed again.
- **Pull up choice.** The push button uses the external 10 kOhm pull up (Circuit-1a of Article 1009) or the internal pull up; Step4_Generated supports the external pull up only.

## Changes in Release v3.2.2 (20261020)

- **Article links.** The Related Articles of every lab card follow the author's list of valid links: 1020 is removed, and 1005 is named in Experiment-9 only, linked to the Robotics page of carpentersoftware.com, where it is published. The Experiment-5 lab card links the 1009 MMC Results for JUL. No lab, program, or setting changed.

## Changes in Release v3.2.1 (20261019)

- **Pull up supply.** The 10 kOhm pull up of D2 may use the Uno 5V pin or the 5 V bus of the breadboard; the Uno 5V pin is preferred, because the 5 V bus is off whenever the motor supply is off and D2 then reads LOW, the pressed level (Article 1009, Wiring).
- **Path B order of power.** Step2_Generator runs with the motor supply off, and the motor supply is applied after Step3_Generated is uploaded (Experiment-5 lab card; Article 1009, Two Ways to Drive).
- **Step3_Generated sets the L298N pins first.** Its `setup()` calls `robot.begin()` before the debug output, so D5 to D10 are outputs and LOW at once after a reset (Discrepancies.md, 85).
- **Simulation retest.** Step1_JUL and Step3_Generated set the same motor pins for the same joystick positions in simavr (Discrepancies.md, 90); the bench retest is pending.

## Changes in Release v3.2.0 (20261018)

Article 1004 still cites v2.4.0; the lab cards give the current names, lines, and settings.

- **Upload port, required.** Each project folder (`Experiments/Experiment-N/Code` and `Code-JUL`) needs its `upload_port` and `monitor_port` lines set to the port of the computer before the first upload; the upload does not work with automatic detection.
- **Push button, external 10 kOhm pull up required.** The author's bench test showed that the thumb joystick module has no resistor on SW. Every program that reads the joystick switch turns the internal pull up of D2 off (Step1_JUL, `ace.h`, Experiment-3 Lab 2, lesson 18), so the pull up of Circuit-2, from D2 to 5 V, must be fitted.
- **Debug flags on.** `Code-JUL/include/Common.h` ships with every debug flag on: Step1_JUL is the diagnostic program of Experiment-2 Lab 3 and Experiment-5 Lab 3 (3000 ms tick). Lessons 18 and 19 define `DEBUG_ALL_OFF` and are not affected.
- **Two ways to drive** after Experiment-5 Lab 3: Step1_JUL with the three debug flags commented out (100 ms tick), or Step2_Generator and Step3_Generated (50 ms tick). See the Experiment-5 lab card and `Code-JUL/README.md`.
- **Joystick lines.** Experiment-5 Lab 1 and lessons 17 and 19 read x on A0 and y on A1, as Step1_JUL since v3.1.0.

## Safety

Follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision, in every experiment. A supervising adult operates the bench power supply; the motor supply is applied last and removed first, and the line cord is unplugged before any change of wiring. Build success and simulation confirm the code only; they do not confirm that the wiring is safe or that the motors behave correctly. See the [Carpenter Software Disclaimer](https://github.com/MageMCU/MageMCU-Carpenter_Software-Disclaimer/blob/main/README_20260924.md).

## Part A: Core Experiments (original header files)

| Experiment | Labs | Code |
|------------|------|------|
| [Experiment-1: Timing and Button Input on the Uno](Experiments/Experiment-1/Instructions/README.md) | delay(), Timer.h, Button.h, Switch.h | `Experiments/Experiment-1/Code` |
| [Experiment-2: Wiring and Reading the Thumb Joystick](Experiments/Experiment-2/Instructions/README.md) | Preprocessor, LinearMap.h, reading the joystick in Step2_JUL | `Experiments/Experiment-2/Code`; `Code-JUL` Step2_JUL with `DEBUG_STEP2_JOYSTICK` (the Step1_Joystick self test checks the connections first) |
| [Experiment-3: L298N Single Motor](Experiments/Experiment-3/Instructions/README.md) | MiscMath.h, duty cycle | `Experiments/Experiment-3/Code` |
| [Experiment-4: L298N Two Motors and the Bits Table](Experiments/Experiment-4/Instructions/README.md) | Bitwise.h, TypeConv.h, L298N.h on six LEDs, second motor | `Experiments/Experiment-4/Code` |
| [Experiment-5: Joystick to Motors](Experiments/Experiment-5/Instructions/README.md) | Vector3.h, Joystick.h, Step2_JUL and the Motor Movement Checklist | `Experiments/Experiment-5/Code`; `Code-JUL` Step2_JUL |

The `include/` folder of each core experiment holds copies of the original header files of `Code-JUL/include` (commit f2307a1). Their compiled code is unchanged; since then comments changed in `Timer.h` (folder line), `Button.h` (v4.0.1), and `Common.h` (v6.1.3), and two local variables of `L298N.h` were renamed (v6.2.2). `Button.h`, `Timer.h`, and `Switch.h` are identical to the files in `Code-JUL/include`; the others keep the code of that commit.

## Part B: Advanced Experiments (numerics)

| Experiment | Lessons in `Code-JUL/src/Step5_MathLessons/lessons` (select with `#define LESSON` and `#define TOPIC` in `main.cpp`) |
|------------|------|
| [Experiment-6: Statistics and the Dead Zone](Experiments/Experiment-6/Instructions/README.md) | L01 to L06, L17_DeadZone |
| [Experiment-7: Line Fit and Motor Calibration](Experiments/Experiment-7/Instructions/README.md) | L15_LineFit, L18_MotorLineFit |
| [Experiment-8: Vectors, Matrices, and the Joystick Frame](Experiments/Experiment-8/Instructions/README.md) | L07 to L13, L19_JoystickFrame |
| [Experiment-9: Quaternions](Experiments/Experiment-9/Instructions/README.md) | L14_Quaternion, L16_Rotation (Article 1005, on [carpentersoftware.com, Projects, Robotics](https://carpentersoftware.com/pages/projects/robotics/robotics.html)) |

## Lab Notebook

Every experiment records the date, the objective, the prediction written before the program is run, the observed output beside the expected output, and the signature of the supervisor where a step asks for it. Template: [Experiments/LAB-NOTEBOOK-TEMPLATE.md](Experiments/LAB-NOTEBOOK-TEMPLATE.md).
