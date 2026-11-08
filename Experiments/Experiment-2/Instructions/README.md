# Experiment-2: Wiring and Reading the Thumb Joystick

*Lab card for Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), revised November 7, 2026 (revision 20261107g). The article gives the objective, prediction, steps, and expected output of every lab, under the heading of the same name; this card gives the files and settings used at the bench. The article and this card refer to release v7.4.0 of the repository. A later release may differ; compare it with the tag. The notes of earlier releases are in `RELEASES.md`.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

Project folder: open `Experiments/Experiment-2/Code` in Visual Studio Code, never the repository root. Select one lab at a time with `build_src_filter` in `platformio.ini`; the serial monitor runs at 9600 baud.

**Before the first upload (required since v3.2.0):** in `platformio.ini` of the project folder, remove the comment mark from the `upload_port` line and the `monitor_port` line and change both to the port of your computer, for example `/dev/ttyACM0` on Raspberry Pi OS and Linux (`/dev/ttyUSB0` for a CH340 clone), `/dev/cu.usbmodem14101` on macOS, or `COM3` on Windows; `pio device list` prints the ports. The upload does not work with the port left to automatic detection. A lab that uses the Code-JUL folder needs the same two lines in `Code-JUL/platformio.ini`.

| Lab | Folder | build_src_filter | Wiring |
|---|---|---|---|
| Lab 1: Common.h, Headers.h, and the Preprocessor | `src/1_Preprocessor` | `build_src_filter = +<*> +<1_Preprocessor/> -<2_LinearMap/>` | Uno and USB cable |
| Lab 2: LinearMap.h, One Formula, Three Types | `src/2_LinearMap` | `build_src_filter = +<*> -<1_Preprocessor/> +<2_LinearMap/>` | Uno and USB cable |
| Lab 3: The Joystick Self Test and the Readings | Code-JUL, Step1_Joystick, then Step2_JUL | see the notes below | [Circuit-2](../../Circuits/Circuit-2.svg) |

## Notes for the bench

- Lab 1, step 2: `build_flags = -std=gnu++11 -D DEBUG_JOYSTICK`, then restore the line.
- Lab 3 uses the Code-JUL folder. The shipped setting of `build_src_filter` selects Step1_Joystick; for Step2_JUL give `Step2_JUL` the sign `+` and the other five folders the sign `-`:

  ```
  build_src_filter =
      +<*>
      -<Step1_Joystick/>
      +<Step2_JUL/>
      -<Step3_Generator/>
      -<Step4_Generated/>
      -<Step5_MathLessons/>
      -<Step6_Circuit/>
  ```

  1. Step1_Joystick, the self test (Article 1009, Step1 Procedure). With the result PASS, copy the file the report prints between its two marker lines over `Code-JUL/include/JoystickMeasurements.h`, from the log file of the monitor (log2file); upload Step1 again and confirm They match.
  2. Step2_JUL with both debug switches on, as shipped (`DEBUG_STEP2_JOYSTICK` and `DEBUG_STEP2_L298N`, the two `#define` lines at the top of `Code-JUL/src/Step2_JUL/main.cpp`): every 3000 ms it prints the `Analogs` line, the raw readings, then the `Corrected` line, the readings after the joystick correction of `include/JoystickCorrection.h` (v7.4.0). With the grip at rest the Corrected line reads 511 for both axes, within a count or two; at the ends of each axis it reads 0 and 1023. The motor supply stays off and the L298N is not connected. The push button toggles "Button ON" and "Button OFF" once per press.
  3. The two `analogRead()` lines, x on A0 and y on A1, are never edited; the Bits() value of Experiment-5 corrects the joystick orientation. Step2_JUL ships with the indicator LED on D12 (`int ledPin = 12;`). The push button needs the external 10 kOhm pull up from D2 to 5 V of Circuit-2, with the line `pinMode(buttonPin, INPUT);` as written; the thumb joystick module has no resistor on SW. A module that connects SW to 5 V when pressed takes the resistor from SW to GND (pull down) and `activeLow = false` in the Button line of Step1_Joystick and Step2_JUL (Circuit-2, note); Fast Drive supports the pull up only.

Record every lab in the notebook: [LAB-NOTEBOOK-TEMPLATE.md](../../LAB-NOTEBOOK-TEMPLATE.md).

## Related Articles


- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
