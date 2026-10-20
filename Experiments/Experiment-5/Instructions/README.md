# Experiment-5: Joystick to Motors

*Lab card for Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. The article gives the objective, prediction, steps, and expected output of every lab, under the heading of the same name; this card gives the files and settings used at the bench. The article and this card refer to release v2.4.0 of the repository, so the line numbers and printed values agree. A later release may differ; compare it with the tag. Updated 20261017 for release v3.0.0: Step1_Joystick was removed and the Code-JUL programs renumbered (Step2_JUL is now Step1_JUL); the notes below give the new names, and Article 1004 DRAFT 4 keeps the v2.4.0 names until it is revised. Updated 20261018 for release v3.2.0: the upload port is required in `platformio.ini`; Lab 1 reads x on A0 and y on A1, as Step1_JUL; Step1_JUL ships with every debug flag on, and the notes give the two ways to drive after Lab 3. Updated 20261019 for release v3.2.1: Path B runs Step2_Generator with the motor supply off, and Step3_Generated sets D5 to D10 LOW before its debug output.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

Project folder: open `Experiments/Experiment-5/Code` in Visual Studio Code, never the repository root. Select one lab at a time with `build_src_filter` in `platformio.ini`; the serial monitor runs at 9600 baud.

**Before the first upload (required since v3.2.0):** in `platformio.ini` of the project folder, remove the comment mark from the `upload_port` line and the `monitor_port` line and change both to the port of your computer, for example `/dev/ttyACM0` on Raspberry Pi OS and Linux (`/dev/ttyUSB0` for a CH340 clone), `/dev/cu.usbmodem14101` on macOS, or `COM3` on Windows; `pio device list` prints the ports. The upload does not work with the port left to automatic detection. A lab that uses the Code-JUL folder needs the same two lines in `Code-JUL/platformio.ini`.

| Lab | Folder | build_src_filter | Wiring |
|---|---|---|---|
| Lab 1: Vector3.h and the Joystick Vector | `src/1_Vector3` | `build_src_filter = +<*> +<1_Vector3/> -<2_Joystick/>` | Drive wiring; joystick powered as in Article 1004, Experiment-3, Powering the Joystick after Experiment-3 |
| Lab 2: Joystick.h, Test Vectors | `src/2_Joystick` | `build_src_filter = +<*> -<1_Vector3/> +<2_Joystick/>` | Uno and USB cable |
| Lab 3: Step1_JUL and the Motor Movement Checklist | Code-JUL, Step1_JUL | see the notes below | Article 1009, Circuit-1 |

## Notes for the bench

- Lab 1: leave the two `analogRead()` lines of `loop()` as shipped, lines 101 and 102, x on A0 and y on A1, the lines of Step1_JUL since v3.1.0 (changed here in v3.2.0; up to v3.1.2 this lab read x on A1 and y on A0; see Discrepancies.md, 68). `setup()` first sets D5 to D10 as outputs and LOW; upload and open the serial monitor before the bench supply is applied, and remove the supply before any upload or reset.
- Lab 3 uses the Code-JUL folder, line 31 of platformio.ini, the shipped setting:

  `build_src_filter = +<*> +<Step1_JUL/> -<Step2_Generator/> -<Step3_Generated/> -<Step4_MathLessons/>`

  Since v3.0.1 the shipped line also excludes the generator programs, named Step2_Generator and Step3_Generated since v3.1.0, when the math lessons became Step4_MathLessons.

  Step1_JUL lines, as in Article 1009, L298N Setup: `ledPin` on line 42 (3), with the D12 form on line 44; `Button(buttonPin, ledPin)` on line 45; pins D5 to D10 on lines 55 to 60; `motors.Bits(...)` on line 92; the two `analogRead()` lines on 103 and 104, x on A0 and y on A1 since v3.1.0, which stay as written. In `Code-JUL/include/Common.h`, lines 45 to 47 define `DEBUG_MAIN`, `DEBUG_JOYSTICK`, and `DEBUG_L298N`; since v3.2.0 all three are on as shipped, so the checklist reads the joystick values and the L298N pin states in the serial monitor, and the motors respond once every 3 s (`BUTTON_TIMER_mS` 3000 ms). The push button needs the external 10 kOhm pull up of Circuit-2.

- After Lab 3, with the `Bits()` value found, there are two ways to drive:

  | Path | What to do | Control tick |
  |---|---|---|
  | A. Stay with Step1_JUL | In `Code-JUL/include/Common.h`, comment out lines 45 to 47 (`DEBUG_MAIN`, `DEBUG_JOYSTICK`, `DEBUG_L298N`), then upload Step1_JUL again | 100 ms |
  | B. Continue to Step 3 | With the motor supply off, select Step2_Generator, answer its checks with the value found, copy the printed program into `Code-JUL/src/Step3_Generated/main.cpp`, select Step3_Generated, and upload it; apply the motor supply after the upload | 50 ms |

  Both paths set the same motor pins for the same joystick readings, with the center offsets of Step1_JUL as shipped (0.05 and 0.06, lines 121 and 122); `ace.h` keeps these values, so offsets changed in Experiment-6 apply to Path A only. Path B uses `include/claude/ace.h` only, not `Common.h`; its `DEBUG_GENERATED` output prints once at startup and may stay on. The `build_src_filter` lines for Step2_Generator and Step3_Generated are in `Code-JUL/platformio.ini` (notes below line 31) and `Code-JUL/README.md` (Selecting a Program); Article 1009, Two Ways to Drive, gives the Path B procedure step by step.

Record every lab in the notebook: [LAB-NOTEBOOK-TEMPLATE.md](../../LAB-NOTEBOOK-TEMPLATE.md).

## Related Articles


- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1005 Study of Quaternions](https://drive.google.com/file/d/1xQS_DkKx-wXtF7fm8C6GPfF8NV9Qoxnr)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)
- [1020 Note, Button.h and Timer.h](https://drive.google.com/file/d/1mLdqeahOOybPuAjdK8CqOVFJma677UWk)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
