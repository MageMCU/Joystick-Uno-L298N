# Experiment-3: L298N Single Motor

*Lab card for Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. The article gives the objective, prediction, steps, and expected output of every lab, under the heading of the same name; this card gives the files and settings used at the bench. The article and this card refer to release v2.4.0 of the repository, so the line numbers and printed values agree. A later release may differ; compare it with the tag. Updated 20261017 for release v3.0.0: Step1_Joystick was removed and the Code-JUL programs renumbered (Step3_MathLessons became Step2_MathLessons, and Step4_MathLessons since v3.1.0); the notes below give the new names, and Article 1004 DRAFT 4 keeps the v2.4.0 names until it is revised. Updated 20261018 for release v3.2.0: the upload port is required in `platformio.ini`; Lab 2 turns the internal pull up of D2 off, and the joystick switch requires the external 10 kOhm pull up of Circuit-2.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

Project folder: open `Experiments/Experiment-3/Code` in Visual Studio Code, never the repository root. Select one lab at a time with `build_src_filter` in `platformio.ini`; the serial monitor runs at 9600 baud.

**Before the first upload (required since v3.2.0):** in `platformio.ini` of the project folder, remove the comment mark from the `upload_port` line and the `monitor_port` line and change both to the port of your computer, for example `/dev/ttyACM0` on Raspberry Pi OS and Linux (`/dev/ttyUSB0` for a CH340 clone), `/dev/cu.usbmodem14101` on macOS, or `COM3` on Windows; `pio device list` prints the ports. The upload does not work with the port left to automatic detection. A lab that uses the Code-JUL folder needs the same two lines in `Code-JUL/platformio.ini`.

| Lab | Folder | build_src_filter | Wiring |
|---|---|---|---|
| Lab 1: MiscMath.h, Sign and Magnitude | `src/1_MiscMath` | `build_src_filter = +<*> +<1_MiscMath/> -<2_DutyCycle/>` | Uno and USB cable |
| Lab 2: One Motor and the Duty Cycle | `src/2_DutyCycle` | `build_src_filter = +<*> -<1_MiscMath/> +<2_DutyCycle/>` | [Circuit-3](../../Circuits/Circuit-3.svg) |

## Notes for the bench

- Lab 2: keys 0 to 4 set the duty cycle (0, 25, 50, 75, 100 percent), f forward, r reverse; the joystick button enables the output. `button = Button(buttonPin, ledPin);` is on line 97 with the default `activeLow = true`, and lines 103 and 104 (`button.begin();` and `pinMode(buttonPin, INPUT);`, added in v3.2.0) turn the internal pull up of D2 off, as Step1_JUL does. The external 10 kOhm pull up from D2 to 5 V of Circuit-2 is required (Experiment-2, Lab 3). A module that closes SW to 5 V when pressed instead needs the resistor from D2 to GND and `Button(buttonPin, ledPin, false)` on line 97.

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
