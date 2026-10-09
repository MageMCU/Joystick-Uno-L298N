# Experiment-2: Wiring and Reading the Thumb Joystick

*Lab card for Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), DRAFT 4. The article gives the objective, prediction, steps, and expected output of every lab, under the heading of the same name; this card gives the files and settings used at the bench. The article and this card refer to release v2.4.0 of the repository, so the line numbers and printed values agree. A later release may differ; compare it with the tag.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

Project folder: open `Experiments/Experiment-2/Code` in Visual Studio Code, never the repository root. Select one lab at a time with `build_src_filter` in `platformio.ini`; the serial monitor runs at 9600 baud.

| Lab | Folder | build_src_filter | Wiring |
|---|---|---|---|
| Lab 1: Common.h, Headers.h, and the Preprocessor | `src/1_Preprocessor` | `build_src_filter = +<*> +<1_Preprocessor/> -<2_LinearMap/>` | Uno and USB cable |
| Lab 2: LinearMap.h, One Formula, Three Types | `src/2_LinearMap` | `build_src_filter = +<*> -<1_Preprocessor/> +<2_LinearMap/>` | Uno and USB cable |
| Lab 3: Joystick Setup | Code-JUL, Step1_Joystick | see the notes below | [Circuit-2](../../Circuits/Circuit-2.svg) |

## Notes for the bench

- Lab 1, step 2: `build_flags = -std=gnu++11 -D DEBUG_JOYSTICK`, then restore the line.
- Lab 3 uses the Code-JUL folder: open `Code-JUL` in VS Code and set line 31 of its platformio.ini to

  `build_src_filter = +<*> +<Step1_Joystick/> -<Step2_JUL/> -<Step3_MathLessons/>`

  In `Code-JUL/include/Common.h`, remove the comment marks from line 33 (`#define DEBUG_MAIN`). Step1_Joystick: axes on lines 82 and 84, reversed forms on lines 83 and 85, `Button(buttonPin, ledPin)` on line 51 (Article 1009, Joystick Setup).

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
