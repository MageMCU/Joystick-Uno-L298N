# Experiment-8: Vectors, Matrices, and the Joystick Frame

*Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. Part B of the article gives a one page summary of the advanced experiments; this file holds the full steps. Labels such as Table 8.1 and Equation 8.1 are local to this file; Table-n, Equation-n, and Circuit-n refer to the article. The article and this file refer to release v2.4.0 of the repository. Updated 20261017 for release v3.0.0: Step1_Joystick was removed and the Code-JUL programs renumbered (Step3_MathLessons became Step2_MathLessons, and Step4_MathLessons since v3.1.0); the notes below give the new names, and Article 1004 DRAFT 4 keeps the v2.4.0 names until it is revised. Updated 20261018 for release v3.2.0: lesson 19 reads x on A0 and y on A1 and builds without the debug flags of `Common.h`.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

**Objective.** Use a rotation matrix to correct a joystick mounted at any angle, and relate it to the eight joystick orientations that the Bits() value of Article 1009, L298N Setup, corrects for the drive.

**Builds on.** Experiment-2, Lab 3; Experiment-5, Labs 1 and 2.

## Lab 1: Vectors, Points, and Matrices

Run lessons 07_Vector2, 08_Point2, 09_Vector3, 10_Point3, 11_Matrix2x2, 12_Matrix3x3, and 13_Matrix4x4. A point is a position; a vector is a displacement with a magnitude and a direction, so the difference of two points is a vector. A matrix is a rectangular array of numbers; multiplying a vector by a matrix produces a new vector, and a rotation matrix turns a vector about the origin without changing its length (Equation 8.1). For each lesson, choose one printed result and confirm it by hand.

**Equation 8.1.** `R(θ) = [ cos θ   −sin θ ;  sin θ   cos θ ]`<br>
The 2 × 2 matrix that rotates a vector counterclockwise by the angle θ.

## Lab 2: The Joystick Frame

A frame is a set of axes in which coordinates are measured. The joystick reads its position in its own frame; the drive needs it in the frame of the robot, x to the right and y forward. A joystick mounted counterclockwise by an angle θ has raw readings rotated by −θ from the robot frame, so multiplying the reading by R(θ) returns it to the robot frame. The eight orientations that are multiples of 90 degrees, with or without a reflection, can be corrected by exchanging and reversing the analogRead() lines. For the drive, Article 1009, L298N Setup, makes the same correction at the motors with the Bits() value, and Step1_JUL keeps its default lines; lesson 19 corrects the frame itself, so its octants can be compared with Table-8. The rotation matrix also corrects any angle between them.

**Code.** Lesson 19_JoystickFrame (Code-JUL/src/Step4_MathLessons/19_JoystickFrame/main.cpp). Part 1 checks rotations of 90, −90, and −45 degrees with test vectors and prints Failures: 0. Part 2 reads the live joystick once per second and prints the raw vector, the corrected vector, and the octant from Joystick.h. Part 1 needs only the USB cable; for Part 2, power the joystick as in Article 1004, Experiment-3, Powering the Joystick after Experiment-3. Set `MOUNT_ANGLE_DEG` to the angle at which the joystick is mounted, counterclockwise as seen from above. Lines 127 and 128 read x on A0 and y on A1 as shipped, the lines of Step1_JUL since v3.1.0 (changed in v3.2.0). The lesson defines `DEBUG_ALL_OFF`, so the `Joystick.h` debug output of `Common.h`, on as shipped since v3.2.0, does not mix with its own output.

1. Exchange or reverse the two analogRead() lines of lesson 19 until the four axis positions report the octants of Article 1004, Table-8, upload with MOUNT_ANGLE_DEG = 0, and confirm that the raw and corrected vectors agree and that the octants of the eight checklist positions agree with Article 1004, Table-8. Each diagonal position lies on the boundary between two octants (Article 1004, Experiment-5, Lab 2, step 2), so a real grip reports either neighboring octant there; record which one.

2. Turn the joystick module 45 degrees counterclockwise on the bench and repeat. Record the octants with MOUNT_ANGLE_DEG = 0, then set it to 45, upload, and record them again.

3. Turn the module to 90 degrees and find the correction twice: once by exchanging and reversing the analogRead() lines of lesson 19, and once with MOUNT_ANGLE_DEG = 90 and the original lines. Show on paper that the two corrections are the same matrix.

**Expected output and verification.** Part 1 prints Failures: 0. With the correct mount angle, the four axis positions report the octants of Article 1004, Table-8 for any mounting angle, and each diagonal reports one of its two neighboring octants. A rotation keeps the magnitude of the vector, so the corner positions still have a magnitude of 1.414.

**Watch for.** A rotated reading can have a component larger than 1: a corner reading of (1, 1) rotated by 45 degrees becomes (0, 1.414). Lesson 19 drives no motor, so it only prints the value. A drive program that applies the rotation must limit each component to the range −1 to 1 before the Joystick class; otherwise the command exceeds 255, and analogWrite() of a value above 255 on a timer pin does not give full speed.


## Related Articles

- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
