# Experiment-7: Line Fit and Motor Calibration

*Article 1004, Experiments for Joystick-Uno-L298N, STEM Starter Kit Series, Part 5. This guide is the text of the experiment in the article (DRAFT 3, 20261008). Labels such as Table-n, Code-n, Equation-n, and Circuit-n refer to the article; every Code-n listing is the main.cpp file named beside it in this repository.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

**Objective.** Measure the speed of a motor at five PWM values, fit a straight line to the data, and find the PWM value below which the motor does not turn.

**Builds on.** Experiment-3, Lab 2 (the lowest duty cycle at which the motor starts); Experiment-5 (the Bits() value of the bench); Article 1009, Advanced Questions with the Variable Supply, question 5.

## Lab 1: The Least Squares Line

A least squares line is the straight line y = mx + b that makes the sum of the squared vertical distances from the data points to the line as small as possible. Its slope m and intercept b follow from the averages of the data (Equation-7). The root mean square (RMS) error is the square root of the average squared distance; it has the units of y and states how far a typical point lies from the line. The x intercept, −b / m, is the value of x at which the line crosses y = 0.

**Equation-7.** `m = Σ (xi − x̄)(yi − ȳ) / Σ (xi − x̄)²,   b = ȳ − m x̄`  
Slope and intercept of the least squares line through n points (xi, yi).

**Code.** Lesson 15_LineFit. Uno and USB cable only. Run it and confirm Failures: 0. Test T2 fits the data of Table-10; compute the slope from Equation-7 by hand for the first two columns and compare.

**Table-10.** Test data of lesson 15, T2. The fit gives a slope of 0.63 RPM per PWM step, an intercept of −25.8 RPM, an x intercept of 40.95, and an RMS error of 0.748 RPM.

| PWM | 60 | 100 | 140 | 180 | 220 |
|---|---|---|---|---|---|
| RPM | 12 | 38 | 61 | 88 | 113 |

## Lab 2: Calibrating the Motor

**Code.** Lesson 18_MotorLineFit, Code-15. Wiring: Article 1009, Circuit-1, complete, with the drive raised so that both wheels turn freely. Set the Bits() value in line 127 to the value found in Experiment-5, and ledPin in line 120 to the pin of the indicator LED. The joystick push button enables the motors. While it is ON, both motors turn forward at one PWM value at a time: 60, 100, 140, 180, and 220.

**Prediction.** From the starting duty cycle recorded in Experiment-3, predict the x intercept of the fit.

1. Upload with the motor supply off, open the serial monitor, then apply the motor supply as in Article 1009, Safety and Supervision.

2. Mark one wheel with tape. Press the joystick button (state ON). Count the revolutions of the marked wheel in 10 s, type the count, and press Enter. The program converts the count to RPM (count × 6) and moves to the next PWM value.

3. After the fifth value the motors stop and the program prints the slope, the intercept, the x intercept (the dead band of the motor), the predicted RPM at PWM 255, and the RMS error. Record them and press the joystick button (state OFF).

4. Repeat with the other wheel, then with the motor bus raised by 1 V, and compare the slopes.

**Expected output and verification.** The five points lie close to a straight line, and the RMS error is a few RPM. The x intercept agrees with the starting duty cycle of Experiment-3 within the resolution of the measurement. Two motors of the same model give slightly different slopes; this difference is one reason a robot drifts to one side with equal commands, and it is the measurement that closed loop speed control, described in Article 1003, corrects automatically.

**Watch for.** A count typed while the button state is OFF (the motors were stopped; repeat the value). A point far from the line (a miscount; the RMS error rises).


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
