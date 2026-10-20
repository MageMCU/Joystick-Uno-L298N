# Experiment-4: L298N Two Motors and the Bits Table

*Lab card for Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. The article gives the objective, prediction, steps, and expected output of every lab, under the heading of the same name; this card gives the files and settings used at the bench. The article and this card refer to release v2.4.0 of the repository, so the line numbers and printed values agree. A later release may differ; compare it with the tag. Updated 20261018 for release v3.2.0: the upload port is required in `platformio.ini`.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

Project folder: open `Experiments/Experiment-4/Code` in Visual Studio Code, never the repository root. Select one lab at a time with `build_src_filter` in `platformio.ini`; the serial monitor runs at 9600 baud.

**Before the first upload (required since v3.2.0):** in `platformio.ini` of the project folder, remove the comment mark from the `upload_port` line and the `monitor_port` line and change both to the port of your computer, for example `/dev/ttyACM0` on Raspberry Pi OS and Linux (`/dev/ttyUSB0` for a CH340 clone), `/dev/cu.usbmodem14101` on macOS, or `COM3` on Windows; `pio device list` prints the ports. The upload does not work with the port left to automatic detection. A lab that uses the Code-JUL folder needs the same two lines in `Code-JUL/platformio.ini`.

| Lab | Folder | build_src_filter | Wiring |
|---|---|---|---|
| Lab 1: Bitwise.h, Bits and Masks | `src/1_Bitwise` | `build_src_filter = +<*> +<1_Bitwise/> -<2_TypeConv/> -<3_BitsLEDs/>` | Uno and USB cable |
| Lab 2: TypeConv.h, Bytes and Words | `src/2_TypeConv` | `build_src_filter = +<*> -<1_Bitwise/> +<2_TypeConv/> -<3_BitsLEDs/>` | Uno and USB cable |
| Lab 3: L298N.h, Reading the Flags on the Pins | `src/3_BitsLEDs` | `build_src_filter = +<*> -<1_Bitwise/> -<2_TypeConv/> +<3_BitsLEDs/>` | [Circuit-4](../../Circuits/Circuit-4.svg) |
| Lab 4: Wiring the Second Motor | Experiment-3 `src/2_DutyCycle` | Experiment-3: `build_src_filter = +<*> -<1_MiscMath/> +<2_DutyCycle/>` | Article 1009, Circuit-1 |

## Notes for the bench

- Lab 1, step 3: change the error case of `b_powerOfTwo()` in `include/Bitwise.h` (the copy in this folder only) to return 0.
- Lab 2, step 2: remove the comment marks from the three example lines in `loop()`.
- Lab 3: type one hexadecimal digit, 0 to f, in the serial monitor.
- Lab 4: before power is applied, upload Experiment-3, Lab 2 (open `Experiments/Experiment-3/Code`) with the bench supply unplugged and leave the push button state OFF. The Uno must not hold the Lab 3 program, which writes 255 to D5 when a digit is typed.

Record every lab in the notebook: [LAB-NOTEBOOK-TEMPLATE.md](../../LAB-NOTEBOOK-TEMPLATE.md).

## Related Articles


- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
