# Experiment-8: Vectors, Matrices, and the Joystick Frame

*Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. Part B of the article gives a one page summary of the advanced experiments; this file holds the full steps. Labels such as Table 8.1 and Equation 8.1 are local to this file; Table-n, Equation-n, and Circuit-n refer to the article. The article and this file refer to release v2.4.0 of the repository. Updated 20261017 for release v3.0.0: Step1_Joystick was removed and the Code-JUL programs renumbered (Step3_MathLessons became Step2_MathLessons, and Step4_MathLessons since v3.1.0); the notes below give the new names, and Article 1004 DRAFT 4 keeps the v2.4.0 names until it is revised. Updated 20261018 for release v3.2.0: lesson 19 reads x on A0 and y on A1 and builds without the debug flags of `Common.h`. Updated 20261021 for release v4.0.0: the Code-JUL programs are renumbered (Step1_Joystick, the joystick connection check, is new; Step2_JUL, Step3_Generator, Step4_Generated, Step5_MathLessons), and the notes below give the new names. Updated 20261021 for release v5.0.0: each lesson is a header file in `Step5_MathLessons/lessons/`, selected with `#define LESSON` in `Step5_MathLessons/main.cpp`, and the line numbers below are those of the headers.*

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
    -<Step6_Circuit/>
```

Then set `#define LESSON` in `Code-JUL/src/Step5_MathLessons/main.cpp` to the number of the lesson and `#define TOPIC`, the line below it, to the number of one topic of that lesson, or to 0 for every topic in order; build and upload. Only that lesson is compiled, and only the selected topics run. A topic is one function of the lesson, named LessonName_Tnn_Operation, for example `Vector3_T16_Copy()`, and it prints the same name as its title; `LESSON_TOPICS` in each lesson file gives its number of topics; each lesson is one header file in `Code-JUL/src/Step5_MathLessons/lessons/`, for example lesson 17 is `L17_DeadZone.h`. Restore the Step2_JUL line of `platformio.ini` before uploading to the robot.

**Objective.** Use a rotation matrix to correct a joystick mounted at any angle, and relate it to the eight joystick orientations that the Bits() value of Article 1009, L298N Setup, corrects for the drive.

**Builds on.** Experiment-2, Lab 3; Experiment-5, Labs 1 and 2.

## Lab 1: Vectors, Points, and Matrices

Run lessons L07_Vector2, L08_Point2, L09_Vector3, L10_Point3, L11_Matrix2x2, L12_Matrix3x3, and L13_Matrix4x4. A point is a position; a vector is a displacement with a magnitude and a direction, so the difference of two points is a vector. A matrix is a rectangular array of numbers; multiplying a vector by a matrix produces a new vector, and a rotation matrix turns a vector about the origin without changing its length (Equation 8.1). For each lesson, choose one printed result and confirm it by hand. Set TOPIC to study one topic at a time; lesson 7 has 17 topics and lesson 9 has 16, too many to read in one run.

**Equation 8.1.** `R(θ) = [ cos θ   −sin θ ;  sin θ   cos θ ]`<br>
The 2 × 2 matrix that rotates a vector counterclockwise by the angle θ.

## Lab 2: The Joystick Frame

A frame is a set of axes in which coordinates are measured. The joystick reads its position in its own frame; the drive needs it in the frame of the robot, x to the right and y forward. A joystick mounted counterclockwise by an angle θ has raw readings rotated by −θ from the robot frame, so multiplying the reading by R(θ) returns it to the robot frame. The eight orientations that are multiples of 90 degrees, with or without a reflection, can be corrected by exchanging and reversing the analogRead() lines. For the drive, Article 1009, L298N Setup, makes the same correction at the motors with the Bits() value, and Step2_JUL keeps its default lines; lesson 19 corrects the frame itself, so its octants can be compared with Table-8. The rotation matrix also corrects any angle between them.

**Code.** Lesson L19_JoystickFrame (Code-JUL/src/Step5_MathLessons/lessons/L19_JoystickFrame.h). The lesson has two topics. Topic T01, `JoystickFrame_T01_RotationChecks()` (Part 1), checks rotations of 90, −90, and −45 degrees with test vectors and prints Failures: 0. Topic T02, `JoystickFrame_T02_LiveJoystick()` (Part 2), reads the live joystick once per second and prints the raw vector, the corrected vector, and the octant from Joystick.h; since v6.4.1 each line starts with the ADC counts of A0 and A1, and the topic first prints MOUNT_ANGLE_DEG. TOPIC 1 needs only the USB cable; for TOPIC 2 or TOPIC 0, power the joystick as in Article 1004, Experiment-3, Powering the Joystick after Experiment-3. Set `MOUNT_ANGLE_DEG` to the angle at which the joystick is mounted, counterclockwise as seen from above. The two `analogRead()` lines read x on A0 and y on A1 as shipped, the lines of Step2_JUL since v3.1.0 (changed in v3.2.0). The lesson defines no debug switch (since v6.0.0; up to v5.1.0 it defined `DEBUG_ALL_OFF`), so no `Joystick.h` debug output mixes with its own output.

1. Exchange or reverse the two analogRead() lines of lesson 19 until the four axis positions report the octants of Article 1004, Table-8, upload with MOUNT_ANGLE_DEG = 0, and confirm that the raw and corrected vectors agree and that the octants of the eight checklist positions agree with Article 1004, Table-8. Each diagonal position lies on the boundary between two octants (Article 1004, Experiment-5, Lab 2, step 2), so a real grip reports either neighboring octant there; record which one.

2. Turn the joystick module 45 degrees counterclockwise on the bench and repeat. Record the octants with MOUNT_ANGLE_DEG = 0, then set it to 45, upload, and record them again.

3. Turn the module to 90 degrees and find the correction twice: once by exchanging and reversing the analogRead() lines of lesson 19, and once with MOUNT_ANGLE_DEG = 90 and the original lines. Show on paper that the two corrections are the same matrix.

**Expected output and verification.** Topic T01 prints Failures: 0. With the correct mount angle, the four axis positions report the octants of Article 1004, Table-8 for any mounting angle, and each diagonal reports one of its two neighboring octants. A rotation keeps the magnitude of the vector, so the corner positions still have a magnitude of 1.414.

**Watch for.** A rotated reading can have a component larger than 1: a corner reading of (1, 1) rotated by 45 degrees becomes (0, 1.414). Lesson 19 drives no motor, so it only prints the value. A drive program that applies the rotation must limit each component to the range −1 to 1 before the Joystick class; otherwise the command exceeds 255, and analogWrite() of a value above 255 on a timer pin does not give full speed.


## Related Articles

- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
