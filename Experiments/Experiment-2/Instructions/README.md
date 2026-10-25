# Experiment-2: Wiring and Reading the Thumb Joystick

*Lab card for Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. The article gives the objective, prediction, steps, and expected output of every lab, under the heading of the same name; this card gives the files and settings used at the bench. The article and this card refer to release v2.4.0 of the repository, so the line numbers and printed values agree. A later release may differ; compare it with the tag. Updated 20261017 for release v3.0.0: Step1_Joystick was removed and the Code-JUL programs renumbered (Step2_JUL is now Step1_JUL); the notes below give the new names, and Article 1004 DRAFT 4 keeps the v2.4.0 names until it is revised. Updated 20261018 for release v3.2.0: the upload port is required in `platformio.ini`; `Code-JUL/include/Common.h` ships with every debug flag on, so Lab 3 needs no change to it; the joystick switch requires the external 10 kOhm pull up of Circuit-2. Updated 20261021 for release v4.0.0: the Code-JUL programs are renumbered (Step1_Joystick, the joystick connection check, is new; Step2_JUL, Step3_Generator, Step4_Generated, Step5_MathLessons), and the notes below give the new names.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

Project folder: open `Experiments/Experiment-2/Code` in Visual Studio Code, never the repository root. Select one lab at a time with `build_src_filter` in `platformio.ini`; the serial monitor runs at 9600 baud.

**Before the first upload (required since v3.2.0):** in `platformio.ini` of the project folder, remove the comment mark from the `upload_port` line and the `monitor_port` line and change both to the port of your computer, for example `/dev/ttyACM0` on Raspberry Pi OS and Linux (`/dev/ttyUSB0` for a CH340 clone), `/dev/cu.usbmodem14101` on macOS, or `COM3` on Windows; `pio device list` prints the ports. The upload does not work with the port left to automatic detection. A lab that uses the Code-JUL folder needs the same two lines in `Code-JUL/platformio.ini`.

| Lab | Folder | build_src_filter | Wiring |
|---|---|---|---|
| Lab 1: Common.h, Headers.h, and the Preprocessor | `src/1_Preprocessor` | `build_src_filter = +<*> +<1_Preprocessor/> -<2_LinearMap/>` | Uno and USB cable |
| Lab 2: LinearMap.h, One Formula, Three Types | `src/2_LinearMap` | `build_src_filter = +<*> -<1_Preprocessor/> +<2_LinearMap/>` | Uno and USB cable |
| Lab 3: Reading the Joystick in Step2_JUL | Code-JUL, Step2_JUL | see the notes below | [Circuit-2](../../Circuits/Circuit-2.svg) |

## Notes for the bench

- Lab 1, step 2: `build_flags = -std=gnu++11 -D DEBUG_JOYSTICK`, then restore the line.
- Lab 3 uses the Code-JUL folder with Step2_JUL selected in its platformio.ini (since v4.0.0 the shipped setting selects Step1_Joystick; in `build_src_filter`, lines 31 to 37, one folder per line since v6.4.0, give `Step2_JUL` the sign `+` and the other four folders the sign `-`):

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

  Step2_JUL ships with both debug switches on (since v6.0.0 lines 21 and 22 of `Code-JUL/src/Step2_JUL/main.cpp`: `DEBUG_STEP2_JOYSTICK`, `DEBUG_STEP2_L298N`; from v3.2.0 to v5.1.0 the flags `DEBUG_JOYSTICK` and `DEBUG_L298N` in `Code-JUL/include/Common.h`), so it needs no change for this lab; up to v3.1.2 the student removed the comment marks from `#define DEBUG_JOYSTICK`. The `DEBUG_STEP2_L298N` lines also print the L298N pin states. The motor supply stays off. Since v4.0.0 Step2_JUL ships with the indicator LED on D12 (line 50), as in Circuit-2; the advanced wiring on D3 is line 48. The two `analogRead()` lines, 114 and 115, need no change: the student confirms that the push button toggles "Button ON" and "Button OFF" once per press, that each axis changes the `Analogs` line over most of 0 to 1023, and that both readings rest near 511 (Article 1009 first checks the same connections with the Step1_Joystick self test, Joystick Setup). Wire the push button as in Circuit-2, with the external 10 kOhm pull up from D2 to 5 V, or use the internal pull up with comment marks on line 58 of Step2_JUL (Article 1009, The Thumb Joystick). The author's bench test (v3.2.0) showed that the thumb joystick module has no resistor on SW. Without a pull up, "Button ON" and "Button OFF" change by themselves with the switch untouched. Step1_Joystick, used here up to v2.4.0 to correct the axes, was removed on 20261017, because the Bits() value found with the Motor Movement Checklist corrects any joystick orientation; since v4.0.0 a new Step1_Joystick checks the connections only.

Record every lab in the notebook: [LAB-NOTEBOOK-TEMPLATE.md](../../LAB-NOTEBOOK-TEMPLATE.md).

## Related Articles


- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
