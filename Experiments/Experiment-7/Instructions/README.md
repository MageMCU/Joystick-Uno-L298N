# Experiment-7: Line Fit and Motor Calibration

*Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. Part B of the article gives a one page summary of the advanced experiments; this file holds the full steps. Labels such as Table 7.1 and Equation 7.1 are local to this file; Table-n, Equation-n, and Circuit-n refer to the article. The article and this file refer to release v2.4.0 of the repository. Updated 20261017 for release v3.0.0: Step1_Joystick was removed and the Code-JUL programs renumbered (Step3_MathLessons became Step2_MathLessons, and Step4_MathLessons since v3.1.0); the notes below give the new names, and Article 1004 DRAFT 4 keeps the v2.4.0 names until it is revised. Updated 20261018 for release v3.2.0: lesson 18 turns the internal pull up of D2 off and builds without the debug flags of `Common.h`. Updated 20261021 for release v4.0.0: the Code-JUL programs are renumbered (Step1_Joystick, the joystick connection check, is new; Step2_JUL, Step3_Generator, Step4_Generated, Step5_MathLessons), and the notes below give the new names. Updated 20261021 for release v5.0.0: each lesson is a header file in `Step5_MathLessons/lessons/`, selected with `#define LESSON` in `Step5_MathLessons/main.cpp`, and the line numbers below are those of the headers.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

**Running a lesson (since v5.0.0; topics since v5.1.0).** Open `Code-JUL/` and select Step5_MathLessons in `platformio.ini`, `build_src_filter` (one folder per line since v6.4.0):

```
build_src_filter =
    +<*>
    -<Step1_Joystick/>
    -<Step2_JUL/>
    -<Step3_Generator/>
    -<Step4_Generated/>
    +<Step5_MathLessons/>
```

Then set `#define LESSON` in `Code-JUL/src/Step5_MathLessons/main.cpp` to the number of the lesson and `#define TOPIC`, the line below it, to the number of one topic of that lesson, or to 0 for every topic in order; build and upload. Only that lesson is compiled, and only the selected topics run. A topic is one function of the lesson, named LessonName_Tnn_Operation, for example `Vector3_T16_Copy()`, and it prints the same name as its title; `LESSON_TOPICS` in each lesson file gives its number of topics; each lesson is one header file in `Code-JUL/src/Step5_MathLessons/lessons/`, for example lesson 17 is `L17_DeadZone.h`. Restore the Step2_JUL line of `platformio.ini` before uploading to the robot.

**Objective.** Measure the speed of a motor at five PWM values, fit a straight line to the data, and find the PWM value below which the motor does not turn.

**Builds on.** Experiment-3, Lab 2 (the lowest duty cycle at which the motor starts); Experiment-5 (the Bits() value of the bench); Article 1009, Advanced Questions with the Variable Supply, question 5.

## Lab 1: The Least Squares Line

A least squares line is the straight line y = mx + b that makes the sum of the squared vertical distances from the data points to the line as small as possible. Its slope m and intercept b follow from the averages of the data (Equation 7.1). The root mean square (RMS) error is the square root of the average squared distance; it has the units of y and states how far a typical point lies from the line. The x intercept, −b / m, is the value of x at which the line crosses y = 0.

**Equation 7.1.** `m = Σ (xi − x̄)(yi − ȳ) / Σ (xi − x̄)²,   b = ȳ − m x̄`<br>
Slope and intercept of the least squares line through n points (xi, yi).

**Code.** Lesson L15_LineFit. Uno and USB cable only. Run it and confirm Failures: 0. Topic T02, `LineFit_T02_MotorCalibration()` (TOPIC 2), fits the data of Table 7.1; compute the slope from Equation 7.1 by hand for the first two columns and compare.

**Table 7.1.** Test data of lesson 15, topic T02. The fit gives a slope of 0.63 RPM per PWM step, an intercept of −25.8 RPM, an x intercept of 40.95, and an RMS error of 0.748 RPM.

| PWM | 60 | 100 | 140 | 180 | 220 |
|---|---|---|---|---|---|
| RPM | 12 | 38 | 61 | 88 | 113 |

## Lab 2: Calibrating the Motor

**Code.** Lesson L18_MotorLineFit (Code-JUL/src/Step5_MathLessons/lessons/L18_MotorLineFit.h). Wiring: Article 1009, Circuit-1, complete, with the drive raised so that both wheels turn freely. Set the `Bits()` value to the one found in Experiment-5, and set `ledPin` to the pin of the indicator LED. The line `button = Button(buttonPin, ledPin);` uses the default `activeLow = true`, and the lines `button.begin();` and `pinMode(buttonPin, INPUT);` (added in v3.2.0) turn the internal pull up of D2 off, as Step2_JUL does; the external 10 kOhm pull up from D2 to 5 V of Circuit-2 is required (Experiment-2, Lab 3). A module that closes SW to 5 V when pressed instead needs the resistor from D2 to GND and `button = Button(buttonPin, ledPin, false);` in that line. The lesson defines no debug switch (since v6.0.0; up to v5.1.0 it defined `DEBUG_ALL_OFF`), so no debug output of `Common.h` applies: the motor tick is 100 ms and the serial monitor shows only the lesson's prompts. Before the motor supply is applied, press the button twice and confirm that the indicator LED turns on and then off. The joystick push button enables the motors. While it is ON, both motors turn forward at one PWM value at a time: 60, 100, 140, 180, and 220.

**Prediction.** From the starting duty cycle recorded in Experiment-3, predict the x intercept of the fit.

1. Upload with the motor supply off, open the serial monitor, then apply the motor supply as in Article 1009, Safety and Supervision.

2. Mark one wheel with tape. Press the joystick button (state ON). Count the revolutions of the marked wheel in 10 s, type the count, and press Enter. The program converts the count to RPM (count × 6) and moves to the next PWM value.

3. After the fifth value the motors stop and the program prints the five PWM and RPM pairs (since v6.4.1; each entry is also echoed as Count, then RPM), then the slope, the intercept, the x intercept (the dead band of the motor), the predicted RPM at PWM 255, and the RMS error. Record them. The program stores one set of five measurements; send n to start a new set. The motors stop and the button state returns to OFF, so the new set starts only after the button is pressed again.

4. Send n and repeat with the other wheel. To repeat with the motor bus raised by 1 V, remove the motor supply first as directed by Article 1009, change the supply, apply it again, send n, and collect a new set. Do not press the reset button of the Uno while the motor supply is applied: D5 to D10 float between a reset and `PinsL298N()`.

**Expected output and verification.** The five points lie close to a straight line, and the RMS error is a few RPM. The x intercept agrees with the starting duty cycle of Experiment-3 within the resolution of the measurement. Two motors of the same model give slightly different slopes; this difference is one reason a robot drifts to one side with equal commands, and it is the measurement that closed loop speed control, described in Article 1003, corrects automatically.

**Watch for.** A count typed while the button state is OFF (the motors were stopped; repeat the value). A point far from the line (a miscount; the RMS error rises).


## Related Articles

- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
