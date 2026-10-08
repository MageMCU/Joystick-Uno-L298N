# Experiment-5: Joystick to Motors

*Article 1004, Experiments for Joystick-Uno-L298N, STEM Starter Kit Series, Part 5. This guide is the text of the experiment in the article (DRAFT 3, 20261008). Labels such as Table-n, Code-n, Equation-n, and Circuit-n refer to the article; every Code-n listing is the main.cpp file named beside it in this repository.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

**Objective.** Find the one Bits() value that makes every joystick position produce the expected motor movement, then measure the loaded motor bus and the L298N drop.

**Builds on.** Experiments 2 and 4; Article 1009, L298N Setup and the Motor Movement Checklist.

## Lab 1: Vector3.h and the Joystick Vector

**Objective.** Treat the two joystick inputs as a vector, measure its magnitude and angle, and compare the two angle functions of MiscMath.h.

A vector has a magnitude and a direction; here it is the pair (x, y) of normalized joystick inputs, stored in a Vector3<float> with z equal to 0. Magnitude() returns the square root of x² + y². Operator overloading gives an operator, such as *, a meaning for a class; for Vector3, u * v is the dot product, which for two unit vectors equals the cosine of the angle between them.

**Code.** Experiments/Experiment-5/Code/src/1_Vector3/main.cpp, Code-12. Before uploading, make the two analogRead() lines of loop() match the lines recorded in Experiment-2. For the test points (1, 0), (1, 1), (0, 1), (−1, 0), (0, −1), and (0, 0), and then for the live joystick once per second, the program prints Magnitude(), AngleRadian() and Angle2Radian() converted to degrees, and the octant computed from the angle as the whole part of the angle divided by 45, plus 1.

**Prediction.** Predict the magnitude and the two angles for each test point.

1. Run the program and record the table.

2. Record the magnitude at (1, 1). It is 1.414, not 1. The joystick inputs fill a square from −1 to 1 on each axis, not a circle of radius 1; this square input space is the reason for the octant algorithm of Article 1001.

3. Compare the two angle functions. Both return 0, 45, 90, 180, and 270 degrees for the first five points. AngleRadian() divides y by x; at (0, 1) the division by zero gives infinity under the floating point standard (IEEE 754), and atan() of infinity is 90 degrees, so the axis is still correct. At (0, 0) the division 0 by 0 gives NaN (not a number), and AngleRadian() prints nan. Angle2Radian() uses atan2(), which takes y and x separately and returns 0 at the origin.

4. Note that (1, 1) at 45 degrees gives octant 2 by the angle, while the Joystick class reports octant 1 for the same point (Lab 2). The point lies on the boundary between the two octants, and each method assigns the boundary to a different side.

5. Move the live joystick slowly around its full travel and record where the octant computed from the angle changes.

**Expected output and verification.** The recorded table agrees with steps 2 to 4, and the angle octant changes every 45 degrees.

## Lab 2: Joystick.h, Test Vectors

**Objective.** Verify the octant algorithm in software, with known inputs, before the motors are connected. A test vector is a chosen input together with the output it must produce.

**Code.** Experiments/Experiment-5/Code/src/2_Joystick/main.cpp, Code-13. Uno and USB cable only. The program passes each input of Table-8 to UpdateInputs(), prints Left(), Right(), and Octant() beside the expected values, marks each row PASS or FAIL, and prints the number of failures.

**Table-8.** Test vectors for the eight positions of the Motor Movement Checklist, with the expected outputs of Article 1009, Image-5, the octant that Joystick.h reports, and two tests of the tolerance of 0.001.

| Position | Input (x, y) | Expected [left, right] | Octant | Observed |
|---|---|---|---|---|
| Right Turn | (1, 0) | [1, −1] | 1 |   |
| North-East | (1, 1) | [1, 0] | 1 |   |
| Forward | (0, 1) | [1, 1] | 2 |   |
| North-West | (−1, 1) | [0, 1] | 4 |   |
| Left Turn | (−1, 0) | [−1, 1] | 4 |   |
| South-West | (−1, −1) | [−1, 0] | 5 |   |
| Backward | (0, −1) | [−1, −1] | 6 |   |
| South-East | (1, −1) | [0, −1] | 8 |   |
| Tolerance, stop | (0.0005, 0.0005) | [0, 0] | 0 |   |
| Tolerance, octant 1 | (0.002, 0) | [0.002, −0.002] | 1 |   |

1. Run the program and fill in the Observed column. The program prints Failures: 0 when every row passes.

2. Each position lies on a boundary between two octants, yet each reports one octant. Read the conditions of _joystick() in include/Joystick.h and explain why North-West reports 4 and Forward reports 2: the test |x| >= |y| comes first, and >= sends every tie to the x branch.

3. Read the last two lines, which move North-West by 0.01 to either side of its boundary: (−1.00, 0.99) reports octant 4 and (−0.99, 1.00) reports octant 3.

**Expected output and verification.** Every row agrees with Table-8. Together with Lab 1, the algorithm is verified before any motor turns, so a wrong movement in Lab 3 can only come from the Bits() value or the wiring.

## Lab 3: Step2_JUL and the Motor Movement Checklist

**Code.** The Code-JUL folder, program Step2_JUL, Article 1009, Code-2. Select it with line 31 of platformio.ini, the shipped setting:

```
build_src_filter = +<*> -<Step1_Joystick/> +<Step2_JUL/> -<Step3_MathLessons/>
```

The loop() function samples the push button on every pass and calls updateJoystick() once each control interval, BUTTON_TIMER_mS in Common.h: 100 ms in normal operation, 3000 ms when any debug flag is defined. While the button state is ON, updateJoystick() runs the signal chain and passes the two commands to UpdateL298N(). While the state is OFF, it calls PowerDownL298N(), which writes 0 to both enable inputs. Two dead zones act in series: Step2_JUL forces an input to zero when its magnitude is below X_OFFSET (0.05) or Y_OFFSET (0.06), and the Joystick class applies its own tolerance of 0.001.

**Prediction.** Before step 2, use Table-6 and the wiring of Table-1 to predict which group of values can pass. Values with bit 3 equal to 0 cross the enable pins. In a position where one motor reverses while the other is stopped, such as South-West [−1, 0], the stopped command then sets the speed of the running motor, so those values are expected to fail at that position.

1. Copy the joystick result. Make the same changes to the two analogRead() lines of updateJoystick(), Step2_JUL, lines 106 and 107), that were recorded in Experiment-2. Set ledPin, line 44, to 12 by moving the comment marks to line 46. If the push button was measured as a pull down in Experiment-2, also give the Button activeLow = false, line 47). Article 1009 gives these lines as 103 and 104, 42, 44, and 45; the program now has two more comment lines above them.

2. Find the value. Carry out Article 1009, L298N Setup, steps 5, 7, and 9, with the Motor Movement Checklist. Start at bits_0000 in line 95. At the first wrong movement, stop, place the next value in the Bits() call, upload, and start the next row of the checklist. The first value that passes all eight positions is the value for this wiring.

3. Measure under load. With the passing value uploaded, carry out Article 1009, Measuring the Motor Bus and the L298N Drop, steps 3 to 8.

4. Tune the dead zone. With DEBUG_JOYSTICK defined, record the inputs printed at rest. Reduce X_OFFSET and Y_OFFSET only while a resting grip still produces commands of zero. Record the final values. Experiment-6 chooses the same values from statistics.

5. Comment out the debug flag, upload, and test the eight positions once more at the normal 100 ms interval. The supervisor signs the notebook entry.

**Expected output and verification.** One value passes all eight positions; on the author's bench it is bits_1010. The checklist rows for every value tried are kept, including the failed rows. The notebook records the passing value, the loaded measurements, and the final dead zone.

**Watch for.** A robot that turns the wrong way (continue the checklist; do not move a motor lead). A motor that moves with the grip at rest (the dead zone too small, or the joystick supply moved without repeating the reading at rest; Article 1009, L298N Setup, step 7). A slow response (a debug flag left defined, which sets the control interval to 3000 ms).


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
