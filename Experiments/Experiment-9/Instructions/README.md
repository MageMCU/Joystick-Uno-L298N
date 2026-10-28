# Experiment-9: Quaternions

*Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. Part B of the article gives a one page summary of the advanced experiments; this file holds the full steps. Labels such as Table 9.1 and Equation 9.1 are local to this file; Table-n, Equation-n, and Circuit-n refer to the article. The article and this file refer to release v2.4.0 of the repository. Updated 20261021 for release v5.0.0: each lesson is a header file in `Step5_MathLessons/lessons/`, selected with `#define LESSON` in `Step5_MathLessons/main.cpp`, and the line numbers below are those of the headers.*

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

**Objective.** Repeat the experiment of the Study of Quaternions (Article 1005) on the Uno: build a rotation from a quaternion, apply it many times, and measure how the rounding of float arithmetic changes the result.

**Builds on.** Article 1005; Experiment-8.

A quaternion is a number with four components, q = (w, x, y, z), written w + xi + yj + zk, where w is the real part and (x, y, z) is the vector part. A unit quaternion has a norm of 1, and the unit quaternion (cos(θ/2), sin(θ/2) u) represents a rotation by the angle θ about the unit axis u (Equation 9.1). Rotating a vector v is the product q v q*, where q* is the conjugate (w, −x, −y, −z). The product of two unit quaternions is the rotation that applies one after the other. Article 1005 builds on the properties given by Dam, Koch, and Lillholm (Quaternions, Interpolation and Animation, Technical Report DIKU-TR-98/5, University of Copenhagen, 1998).

**Equation 9.1.** `q = cos(θ/2) + sin(θ/2) (ux i + uy j + uz k)`<br>
The unit quaternion of a rotation by θ about the unit axis u.

## Lab 1: Quaternion Products

**Code.** Lesson L14_Quaternion. Uno and USB cable only. Topic T08, `Quaternion_T08_Multiplication()`, multiplies the quaternion of a 1 degree rotation about the axis (1, 2, 3) by itself repeatedly and prints the four components, the stream of data plotted in Article 1005. Run the lesson with TOPIC 8, so that only this topic prints, copy the T08 output from the serial monitor into a spreadsheet (since v6.4.1 the first two lines after the title name the axis and the columns; leave them out of the plot), and plot w, x, y, and z against the number of products.

**Expected output and verification.** Each component follows a cosine or sine of half the total angle, so one full turn of the rotation, 360 degrees, is half a period of w; the quaternion returns to its start after 720 degrees. The norm stays at 1 within the rounding of float arithmetic.

## Lab 2: Rotation, Conversion, and Drift

**Code.** Lesson L16_Rotation. Uno and USB cable only. The five topics rotate (1, 0, 0) by 90 degrees about z, convert a quaternion of 120 degrees about (1, 1, 1) into a 3 × 3 rotation matrix and back, interpolate between two rotations with spherical linear interpolation (Slerp), and apply 720 products of a 1 degree rotation. Slerp moves along the shortest arc between two unit quaternions at a constant angular rate.

1. Run the lesson and confirm Failures: 0.

2. In topic T05 the Quaternion class renormalizes the product when its norm has drifted from 1 by more than the rounding error of a float. Record the norm and w after 720 products.

3. In topic T02, the quaternion of 120 degrees about (1, 1, 1) becomes a matrix that exchanges the axes x to y, y to z, and z to x. Write the matrix by hand and compare.

**Expected output and verification.** Every check prints PASS. After 720 products of 1 degree the norm is 1.0000 and |w| is 1.000, the start, as Article 1005 predicts.


## Related Articles

- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- 1005 Study of Quaternions, published on [carpentersoftware.com, Projects, Robotics](https://carpentersoftware.com/pages/projects/robotics/robotics.html)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
