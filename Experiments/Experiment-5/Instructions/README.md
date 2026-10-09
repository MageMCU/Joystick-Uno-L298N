# Experiment-5: Joystick to Motors

*Lab card for Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), DRAFT 4. The article gives the objective, prediction, steps, and expected output of every lab, under the heading of the same name; this card gives the files and settings used at the bench. The article and this card refer to release v2.4.0 of the repository, so the line numbers and printed values agree. A later release may differ; compare it with the tag.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

Project folder: open `Experiments/Experiment-5/Code` in Visual Studio Code, never the repository root. Select one lab at a time with `build_src_filter` in `platformio.ini`; the serial monitor runs at 9600 baud.

| Lab | Folder | build_src_filter | Wiring |
|---|---|---|---|
| Lab 1: Vector3.h and the Joystick Vector | `src/1_Vector3` | `build_src_filter = +<*> +<1_Vector3/> -<2_Joystick/>` | Joystick as in [Circuit-2](../../Circuits/Circuit-2.svg) |
| Lab 2: Joystick.h, Test Vectors | `src/2_Joystick` | `build_src_filter = +<*> -<1_Vector3/> +<2_Joystick/>` | Uno and USB cable |
| Lab 3: Step2_JUL and the Motor Movement Checklist | Code-JUL, Step2_JUL | see the notes below | Article 1009, Circuit-1 |

## Notes for the bench

- Lab 1: make the two `analogRead()` lines of `loop()` match the lines recorded in Experiment-2.
- Lab 3 uses the Code-JUL folder, line 31 of platformio.ini, the shipped setting:

  `build_src_filter = +<*> -<Step1_Joystick/> +<Step2_JUL/> -<Step3_MathLessons/>`

  Step2_JUL lines, as in Article 1009, L298N Setup: `ledPin` on line 42 (3), with the D12 form on line 44; `Button(buttonPin, ledPin)` on line 45; pins D5 to D10 on lines 55 to 60; `motors.Bits(...)` on line 92; the two `analogRead()` lines on 103 and 104. In `Code-JUL/include/Common.h`, line 33 is `DEBUG_MAIN` and line 43 is `DEBUG_L298N`.

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
