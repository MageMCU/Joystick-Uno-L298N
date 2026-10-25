# Experiment-5: Joystick to Motors

*Lab card for Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. The article gives the objective, prediction, steps, and expected output of every lab, under the heading of the same name; this card gives the files and settings used at the bench. The article and this card refer to release v2.4.0 of the repository, so the line numbers and printed values agree. A later release may differ; compare it with the tag. Updated 20261017 for release v3.0.0: Step1_Joystick was removed and the Code-JUL programs renumbered (Step2_JUL is now Step1_JUL); the notes below give the new names, and Article 1004 DRAFT 4 keeps the v2.4.0 names until it is revised. Updated 20261018 for release v3.2.0: the upload port is required in `platformio.ini`; Lab 1 reads x on A0 and y on A1, as Step1_JUL; Step1_JUL ships with every debug flag on, and the notes give the two ways to drive after Lab 3. Updated 20261019 for release v3.2.1: Path B runs Step2_Generator with the motor supply off, and Step3_Generated sets D5 to D10 LOW before its debug output. Updated 20261021 for release v4.0.0: the Code-JUL programs are renumbered (Step1_Joystick, the joystick connection check, is new; Step2_JUL, Step3_Generator, Step4_Generated, Step5_MathLessons), and the notes below give the new names.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

Project folder: open `Experiments/Experiment-5/Code` in Visual Studio Code, never the repository root. Select one lab at a time with `build_src_filter` in `platformio.ini`; the serial monitor runs at 9600 baud.

**Before the first upload (required since v3.2.0):** in `platformio.ini` of the project folder, remove the comment mark from the `upload_port` line and the `monitor_port` line and change both to the port of your computer, for example `/dev/ttyACM0` on Raspberry Pi OS and Linux (`/dev/ttyUSB0` for a CH340 clone), `/dev/cu.usbmodem14101` on macOS, or `COM3` on Windows; `pio device list` prints the ports. The upload does not work with the port left to automatic detection. A lab that uses the Code-JUL folder needs the same two lines in `Code-JUL/platformio.ini`.

| Lab | Folder | build_src_filter | Wiring |
|---|---|---|---|
| Lab 1: Vector3.h and the Joystick Vector | `src/1_Vector3` | `build_src_filter = +<*> +<1_Vector3/> -<2_Joystick/>` | Drive wiring; joystick powered as in Article 1004, Experiment-3, Powering the Joystick after Experiment-3 |
| Lab 2: Joystick.h, Test Vectors | `src/2_Joystick` | `build_src_filter = +<*> -<1_Vector3/> +<2_Joystick/>` | Uno and USB cable |
| Lab 3: Step2_JUL and the Motor Movement Checklist | Code-JUL, Step2_JUL | see the notes below | Article 1009, Circuit-1 |

## Notes for the bench

- Lab 1: leave the two `analogRead()` lines of `loop()` as shipped, lines 101 and 102, x on A0 and y on A1, the lines of Step2_JUL since v3.1.0 (changed here in v3.2.0; up to v3.1.2 this lab read x on A1 and y on A0; see Discrepancies.md, 68). `setup()` first sets D5 to D10 as outputs and LOW; upload and open the serial monitor before the bench supply is applied, and remove the supply before any upload or reset.
- Lab 3 uses the Code-JUL folder with Step2_JUL selected in platformio.ini (since v4.0.0 the shipped setting selects Step1_Joystick, which checks the joystick first; in `build_src_filter`, lines 31 to 37, one folder per line since v6.4.0, give `Step2_JUL` the sign `+` and the other four folders the sign `-`):

  ```
  build_src_filter =
      +<*>
      -<Step1_Joystick/>
      +<Step2_JUL/>
      -<Step3_Generator/>
      -<Step4_Generated/>
      -<Step5_MathLessons/>
  ```

  Since v3.0.1 the shipped line also excludes the generator programs, named Step2_Generator and Step3_Generated since v3.1.0, when the math lessons became Step4_MathLessons.

  Step2_JUL lines, as in Article 1009, L298N Setup: `ledPin` on line 50 (12, since v4.0.0), with the D3 form of the advanced wiring on line 48; `Button(buttonPin, ledPin)` on line 51 and `setLatching(true)` on line 56 (latching mode: press once for ON, again for OFF); pins D5 to D10 on lines 66 to 71, named since v6.2.1 after the L298N input of each pin in Circuit-1 (`ENB = 5`, `IN4 = 6`, `IN3 = 7`, `IN2 = 8`, `IN1 = 9`, `ENA = 10`; up to v6.2.0 the opposite names; a bench wired by the old names needs no new wiring, and its `Bits()` value belongs to that wiring, see the repository `README.md`, Wiring Checklist); `motors.Bits(...)` on line 103; the two `analogRead()` lines on 114 and 115, x on A0 and y on A1 since v3.1.0, which stay as written. Lines 21 and 22 define the debug switches `DEBUG_STEP2_JOYSTICK` and `DEBUG_STEP2_L298N` (since v6.0.0; from v3.2.0 to v5.1.0 the flags of `Code-JUL/include/Common.h`); both are on as shipped, so the checklist reads the joystick values and the L298N pin states in the serial monitor, and the motors respond once every 3 s (`BUTTON_TIMER_mS` 3000 ms); the push button OFF stops them at once (v6.2.3). The push button needs a pull up: the external 10 kOhm pull up of Circuit-2 with line 58 as written, or the internal pull up with line 58 commented out (Path A only).

- After Lab 3, with the `Bits()` value found, there are two ways to drive:

  | Path | What to do | Control tick |
  |---|---|---|
  | A. Stay with Step2_JUL | Comment out lines 21 and 22 of Step2_JUL (`DEBUG_STEP2_JOYSTICK`, `DEBUG_STEP2_L298N`), then upload Step2_JUL again | 100 ms |
  | B. Continue to Step 3 | With the motor supply off, select Step3_Generator, answer its checks with the value found, copy the printed program into `Code-JUL/src/Step4_Generated/main.cpp`, select Step4_Generated, and upload it; apply the motor supply after the upload | 50 ms |

  Both paths set the same motor pins for the same joystick readings, with the center offsets of Step2_JUL as shipped (0.05 and 0.06, lines 132 and 133); `ace.h` keeps these values, so offsets changed in Experiment-6 apply to Path A only. Path B uses `include/claude/ace.h` only, not `Common.h`; its `DEBUG_GENERATED` output prints once at startup and may stay on; press the push button after the line Ready (v6.2.3). The `build_src_filter` lines for Step3_Generator and Step4_Generated are in `Code-JUL/platformio.ini` (notes below the filter) and `Code-JUL/README.md` (Selecting a Program); Article 1009, Two Ways to Drive, gives the Path B procedure step by step.

Record every lab in the notebook: [LAB-NOTEBOOK-TEMPLATE.md](../../LAB-NOTEBOOK-TEMPLATE.md).

## Related Articles


- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)
- [1009 MMC Results for JUL](https://drive.google.com/file/d/17yNw5FNRORWgtDyey11OeKGRMB9qV0SZ)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
