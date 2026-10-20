# Experiment-1: Timing and Button Input on the Uno

*Lab card for Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. The article gives the objective, prediction, steps, and expected output of every lab, under the heading of the same name; this card gives the files and settings used at the bench. The article and this card refer to release v2.4.0 of the repository, so the line numbers and printed values agree. A later release may differ; compare it with the tag. Updated 20261018 for release v3.2.0: the upload port is required in `platformio.ini`.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

Project folder: open `Experiments/Experiment-1/Code` in Visual Studio Code, never the repository root. Select one lab at a time with `build_src_filter` in `platformio.ini`; the serial monitor runs at 9600 baud.

**Before the first upload (required since v3.2.0):** in `platformio.ini` of the project folder, remove the comment mark from the `upload_port` line and the `monitor_port` line and change both to the port of your computer, for example `/dev/ttyACM0` on Raspberry Pi OS and Linux (`/dev/ttyUSB0` for a CH340 clone), `/dev/cu.usbmodem14101` on macOS, or `COM3` on Windows; `pio device list` prints the ports. The upload does not work with the port left to automatic detection. A lab that uses the Code-JUL folder needs the same two lines in `Code-JUL/platformio.ini`.

| Lab | Folder | build_src_filter | Wiring |
|---|---|---|---|
| Lab 1: The delay() Function | `src/1_Delay` | `build_src_filter = +<*> +<1_Delay/> -<2_Timer/> -<3_Button/> -<4_Switch/>` | Uno and USB cable |
| Lab 2: The Timer Class | `src/2_Timer` | `build_src_filter = +<*> -<1_Delay/> +<2_Timer/> -<3_Button/> -<4_Switch/>` | Uno and USB cable |
| Lab 3: The Button Class with the Timer Class | `src/3_Button` | `build_src_filter = +<*> -<1_Delay/> -<2_Timer/> +<3_Button/> -<4_Switch/>` | [Circuit-1](../../Circuits/Circuit-1.svg) |
| Lab 4: Switch.h and Contact Bounce | `src/4_Switch` | `build_src_filter = +<*> -<1_Delay/> -<2_Timer/> -<3_Button/> +<4_Switch/>` | [Circuit-1](../../Circuits/Circuit-1.svg) |

## Notes for the bench

- Lab 3: `button = Button(buttonPin, buttonLED, false);` (line 48) is written for the pull down resistor of Circuit-1.
- Lab 4, step 4: move the call to `m_pins()` after the two assignments in the `Switch` constructor of `include/Switch.h` (the copy in this folder only).

Record every lab in the notebook: [LAB-NOTEBOOK-TEMPLATE.md](../../LAB-NOTEBOOK-TEMPLATE.md).

## Related Articles


- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
