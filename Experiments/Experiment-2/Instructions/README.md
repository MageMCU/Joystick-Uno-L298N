# Experiment-2: Wiring and Reading the Thumb Joystick

*Lab card for Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. The article gives the objective, prediction, steps, and expected output of every lab, under the heading of the same name; this card gives the files and settings used at the bench. The article and this card refer to release v2.4.0 of the repository, so the line numbers and printed values agree. A later release may differ; compare it with the tag. Updated 20261017 for release v3.0.0: Step1_Joystick was removed and the Code-JUL programs renumbered (Step2_JUL is now Step1_JUL); the notes below give the new names, and Article 1004 DRAFT 4 keeps the v2.4.0 names until it is revised. Updated 20261018 for release v3.2.0: the upload port is required in `platformio.ini`; `Code-JUL/include/Common.h` ships with every debug flag on, so Lab 3 needs no change to it; the joystick switch requires the external 10 kOhm pull up of Circuit-2.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

Project folder: open `Experiments/Experiment-2/Code` in Visual Studio Code, never the repository root. Select one lab at a time with `build_src_filter` in `platformio.ini`; the serial monitor runs at 9600 baud.

**Before the first upload (required since v3.2.0):** in `platformio.ini` of the project folder, remove the comment mark from the `upload_port` line and the `monitor_port` line and change both to the port of your computer, for example `/dev/ttyACM0` on Raspberry Pi OS and Linux (`/dev/ttyUSB0` for a CH340 clone), `/dev/cu.usbmodem14101` on macOS, or `COM3` on Windows; `pio device list` prints the ports. The upload does not work with the port left to automatic detection. A lab that uses the Code-JUL folder needs the same two lines in `Code-JUL/platformio.ini`.

| Lab | Folder | build_src_filter | Wiring |
|---|---|---|---|
| Lab 1: Common.h, Headers.h, and the Preprocessor | `src/1_Preprocessor` | `build_src_filter = +<*> +<1_Preprocessor/> -<2_LinearMap/>` | Uno and USB cable |
| Lab 2: LinearMap.h, One Formula, Three Types | `src/2_LinearMap` | `build_src_filter = +<*> -<1_Preprocessor/> +<2_LinearMap/>` | Uno and USB cable |
| Lab 3: Joystick and Button Check | Code-JUL, Step1_JUL | see the notes below | [Circuit-2](../../Circuits/Circuit-2.svg) |

## Notes for the bench

- Lab 1, step 2: `build_flags = -std=gnu++11 -D DEBUG_JOYSTICK`, then restore the line.
- Lab 3 uses the Code-JUL folder, line 31 of its platformio.ini, the shipped setting:

  `build_src_filter = +<*> +<Step1_JUL/> -<Step2_Generator/> -<Step3_Generated/> -<Step4_MathLessons/>`

  Since v3.0.1 the shipped line also excludes the generator programs, named Step2_Generator and Step3_Generated since v3.1.0, when the math lessons became Step4_MathLessons.

  `Code-JUL/include/Common.h` ships with every debug flag on since v3.2.0 (lines 45 to 47: `DEBUG_MAIN`, `DEBUG_JOYSTICK`, `DEBUG_L298N`), so it needs no change for this lab; up to v3.1.2 the student removed the comment marks from `#define DEBUG_JOYSTICK`. The `DEBUG_L298N` lines also print the L298N pin states. No motors are connected; the L298N outputs of D5 to D10 drive nothing. Circuit-2 places the indicator LED on D12: in Step1_JUL, comment out line 42 (`int ledPin = 3;`) and remove the comment marks from line 44 (`int ledPin = 12;`). The two `analogRead()` lines, 103 and 104, need no change: the student confirms that the push button toggles "Button ON" and "Button OFF" once per press, that each axis changes the `Analogs` line over most of 0 to 1023, and that both readings rest near 511 (Article 1009, L298N Setup, Joystick and Button Check). Wire the push button as in Circuit-2, with the external 10 kOhm pull up from D2 to 5 V. It is required: the author's bench test (v3.2.0) showed that the thumb joystick module has no resistor on SW, and Step1_JUL turns the internal pull up of D2 off (lines 46 and 47). Without the pull up, "Button ON" and "Button OFF" change by themselves with the switch untouched. Step1_Joystick, used here up to v2.4.0, was removed on 20261017: the Bits() value found with the Motor Movement Checklist corrects any joystick orientation, so the axes are no longer corrected in the program.

Record every lab in the notebook: [LAB-NOTEBOOK-TEMPLATE.md](../../LAB-NOTEBOOK-TEMPLATE.md).

## Related Articles


- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
