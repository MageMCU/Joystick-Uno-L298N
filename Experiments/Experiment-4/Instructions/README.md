# Experiment-4: L298N Two Motors and the Bits Table

*Lab card for Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), DRAFT 4. The article gives the objective, prediction, steps, and expected output of every lab, under the heading of the same name; this card gives the files and settings used at the bench. The article and this card refer to release v2.4.0 of the repository, so the line numbers and printed values agree. A later release may differ; compare it with the tag.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

Project folder: open `Experiments/Experiment-4/Code` in Visual Studio Code, never the repository root. Select one lab at a time with `build_src_filter` in `platformio.ini`; the serial monitor runs at 9600 baud.

| Lab | Folder | build_src_filter | Wiring |
|---|---|---|---|
| Lab 1: Bitwise.h, Bits and Masks | `src/1_Bitwise` | `build_src_filter = +<*> +<1_Bitwise/> -<2_TypeConv/> -<3_BitsLEDs/>` | Uno and USB cable |
| Lab 2: TypeConv.h, Bytes and Words | `src/2_TypeConv` | `build_src_filter = +<*> -<1_Bitwise/> +<2_TypeConv/> -<3_BitsLEDs/>` | Uno and USB cable |
| Lab 3: L298N.h, Reading the Flags on the Pins | `src/3_BitsLEDs` | `build_src_filter = +<*> -<1_Bitwise/> -<2_TypeConv/> +<3_BitsLEDs/>` | [Circuit-4](../../Circuits/Circuit-4.svg) |
| Lab 4: Wiring the Second Motor | no program | none | Article 1009, Circuit-1 |

## Notes for the bench

- Lab 1, step 3: change the error case of `b_powerOfTwo()` in `include/Bitwise.h` (the copy in this folder only) to return 0.
- Lab 2, step 2: remove the comment marks from the three example lines in `loop()`.
- Lab 3: type one hexadecimal digit, 0 to f, in the serial monitor.

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
