# Experiment-6: Statistics and the Dead Zone

*Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), DRAFT 4. Part B of the article gives a one page summary of the advanced experiments; this file holds the full steps. Labels such as Table 6.1 and Equation 6.1 are local to this file; Table-n, Equation-n, and Circuit-n refer to the article. The article and this file refer to release v2.4.0 of the repository.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

**Objective.** Measure the noise of the joystick at rest and choose the dead zone of Step2_JUL from data rather than by trial.

**Builds on.** Experiment-5, Lab 3, step 4 (the dead zone tuned by trial).

## Lab 1: The Numerics Folder

Run lessons 01_Bitwise, 02_TypeConv, 03_LinearMap, and 04_MiscMath. They test the numerics copies of the header files studied in Experiments 2 to 4. Open each header in Code-JUL/include/numerics and read its REVIEW 20261008 notes; each note marks an edge case that a core lab found, such as the out of range bit of Experiment-4, Lab 1, and the integer overflow of Experiment-2, Lab 2. Record, for each note, the lab that found it.

## Lab 2: Random Numbers and Statistics

The average (mean) of n readings is their sum divided by n. The standard deviation measures how far the readings spread from the average; the Statistics class computes the sample standard deviation of Equation 6.2. The median is the middle value after the readings are sorted; it is not moved by a single reading far from the rest. A pseudo random number generator produces a sequence of numbers that appears random but is computed by a formula from a starting value, the seed; RandomNumber.h seeds once from analogRead() of A0 and A1 and from micros().

**Equation 6.1.** `x̄ = (x1 + x2 + … + xn) / n`<br>
The average of n readings.

**Equation 6.2.** `s = √( Σ (xi − x̄)² / (n − 1) )`<br>
The sample standard deviation of n readings about their average.

Run lessons 05_RandomNumber and 06_Statistics. Record the average, standard deviation, and median that lesson 06 prints, and confirm one of them by hand from the printed data. Note that the constructor of Statistics sorts the array it is given.

## Lab 3: The Joystick at Rest

**Code.** Lesson 17_DeadZone (Code-JUL/src/Step3_MathLessons/17_DeadZone/main.cpp). Wiring: the joystick of Experiment-2, Lab 3; no motor power. Make the two analogRead() lines match the lines recorded in Experiment-2. The program takes 100 readings of each axis with the grip at rest, maps them into the range −1 to 1 as Step2_JUL does, and prints the average, standard deviation, median, minimum, and maximum of each axis, and a suggested offset of |average| + 3 standard deviations. For readings that follow the normal distribution, about 99.7 percent lie within 3 standard deviations of the average.

**Prediction.** From the readings at rest recorded in Experiment-2, estimate the average of each axis in the range −1 to 1.

1. Leave the grip at rest, upload, and record both lines. Press the reset button of the Uno and repeat four times.

2. Release the grip from a full deflection, let it return to center, and press reset. Repeat from four directions and record the averages. The spread of the averages shows how well the spring of the joystick returns it to center.

3. Choose X_OFFSET and Y_OFFSET as the largest suggested offset of each axis over all trials, set them in Step2_JUL, and confirm with Experiment-5, Lab 3, step 4, that a resting grip produces commands of zero.

**Expected output and verification.** The standard deviation at rest is small, often one or two ADC counts (about 0.002 to 0.004 in the range −1 to 1), while the average after a release changes with the direction of the release. The return to center, not the electrical noise, usually sets the dead zone. The chosen offsets are recorded beside the values of Experiment-5 and the original values, 0.05 and 0.06.


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
