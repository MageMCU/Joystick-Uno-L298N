# Experiment-6: Statistics and the Dead Zone

*Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. Part B of the article gives a one page summary of the advanced experiments; this file holds the full steps. Labels such as Table 6.1 and Equation 6.1 are local to this file; Table-n, Equation-n, and Circuit-n refer to the article. The article and this file refer to release v2.4.0 of the repository. Updated 20261017 for release v3.0.0: Step1_Joystick was removed and the Code-JUL programs renumbered (Step3_MathLessons became Step2_MathLessons, and Step4_MathLessons since v3.1.0); the notes below give the new names, and Article 1004 DRAFT 4 keeps the v2.4.0 names until it is revised. Updated 20261018 for release v3.2.0: lesson 17 reads x on A0 and y on A1, as Step1_JUL. Updated 20261021 for release v4.0.0: the Code-JUL programs are renumbered (Step1_Joystick, the joystick connection check, is new; Step2_JUL, Step3_Generator, Step4_Generated, Step5_MathLessons), and the notes below give the new names. Updated 20261021 for release v5.0.0: each lesson is a header file in `Step5_MathLessons/lessons/`, selected with `#define LESSON` in `Step5_MathLessons/main.cpp`, and the line numbers below are those of the headers.*

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

**Objective.** Measure the noise of the joystick at rest and choose the dead zone of Step2_JUL from data rather than by trial.

**Builds on.** Experiment-5, Lab 3, step 4 (the dead zone tuned by trial).

## Lab 1: The Numerics Folder

Run lessons L01_Bitwise, L02_TypeConv, L03_LinearMap, and L04_MiscMath. They test the numerics copies of the header files studied in Experiments 2 to 4. Open each header in Code-JUL/include/numerics and read its REVIEW 20261008 notes; each note marks an edge case that a core lab found, such as the out of range bit of Experiment-4, Lab 1, and the integer overflow of Experiment-2, Lab 2. Record, for each note, the lab that found it.

## Lab 2: Random Numbers and Statistics

The average (mean) of n readings is their sum divided by n. The standard deviation measures how far the readings spread from the average; the Statistics class computes the sample standard deviation of Equation 6.2. The median is the middle value after the readings are sorted; it is not moved by a single reading far from the rest. A pseudo random number generator produces a sequence of numbers that appears random but is computed by a formula from a starting value, the seed; RandomNumber.h seeds once from analogRead() of A0 and A1 and from micros().

**Equation 6.1.** `x̄ = (x1 + x2 + … + xn) / n`<br>
The average of n readings.

**Equation 6.2.** `s = √( Σ (xi − x̄)² / (n − 1) )`<br>
The sample standard deviation of n readings about their average.

Run lessons L05_RandomNumber and L06_Statistics. Record the average, standard deviation, and median that lesson 06 prints, and confirm one of them by hand from the printed data. Note that the constructor of Statistics sorts the array it is given.

## Lab 3: The Joystick at Rest

**Code.** Lesson L17_DeadZone (Code-JUL/src/Step5_MathLessons/lessons/L17_DeadZone.h). Wiring: the drive as wired since Experiment-3; power the joystick as in Article 1004, Experiment-3, Powering the Joystick after Experiment-3. The two analogRead() lines read x on A0 and y on A1, the lines of Step2_JUL since v3.1.0 (changed in v3.2.0; up to v3.1.2 the student made them match the lines recorded in Experiment-2). The program takes 100 readings of each axis with the grip at rest, maps them into the range −1 to 1 as Step2_JUL does, and prints the average, standard deviation, median, minimum, and maximum of each axis, and a suggested offset of |average| + 3 standard deviations. Since v6.4.1 it also prints, first, the centers of `include/JoystickCenter.h` (Step1_Joystick), and for each axis the average in ADC counts beside the center of that file and the suggested offset about that center, the center Step4_Generated uses. For readings that follow the normal distribution, about 99.7 percent lie within 3 standard deviations of the average.

**Prediction.** From the readings at rest recorded in Experiment-2, estimate the average of each axis in the range −1 to 1.

1. Upload and open the serial monitor with the bench supply unplugged, then apply the supply as in Article 1004, Experiment-3, Powering the Joystick after Experiment-3. Leave the grip at rest and record both lines. Send any key in the serial monitor to repeat the measurement, four more times. Do not press the reset button of the Uno while the bench supply is applied.

2. Release the grip from a full deflection, let it return to center, and send a key. Repeat from four directions and record the averages. The spread of the averages shows how well the spring of the joystick returns it to center.

3. Choose X_OFFSET and Y_OFFSET as the largest suggested offset of each axis over all trials, set them in Step2_JUL, and confirm with Experiment-5, Lab 3, step 4, that a resting grip produces commands of zero. Step2_JUL prints the commands with its debug switches on, as shipped (since v6.0.0 the two debug switch lines at the top of Step2_JUL; from v3.2.0 to v5.1.0 the flags of `Common.h`). Step4_Generated (`include/claude/ace.h`) keeps the original offsets, 0.05 and 0.06, as the integer limits 51 and 61, and `ace.h` is never edited; with new offsets, drive with Step2_JUL (Article 1009, Simple Drive).

**Expected output and verification.** The standard deviation at rest is small, often one or two ADC counts (about 0.002 to 0.004 in the range −1 to 1), while the average after a release changes with the direction of the release. The return to center, not the electrical noise, usually sets the dead zone. The chosen offsets are recorded beside the values of Experiment-5 and the original values, 0.05 and 0.06.


## Related Articles

- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
