# Experiment-8: Vectors, Matrices, and the Joystick Frame

*Article 1004, Experiments for Joystick-Uno-L298N, STEM Starter Kit Series, Part 5. This guide is the text of the experiment in the article (DRAFT 3, 20261008). Labels such as Table-n, Code-n, Equation-n, and Circuit-n refer to the article; every Code-n listing is the main.cpp file named beside it in this repository.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

**Objective.** Use a rotation matrix to correct a joystick mounted at any angle, and relate it to the eight orientations of Article 1009, Joystick Setup.

**Builds on.** Experiment-2, Lab 3; Experiment-5, Labs 1 and 2.

## Lab 1: Vectors, Points, and Matrices

Run lessons 07_Vector2, 08_Point2, 09_Vector3, 10_Point3, 11_Matrix2x2, 12_Matrix3x3, and 13_Matrix4x4. A point is a position; a vector is a displacement with a magnitude and a direction, so the difference of two points is a vector. A matrix is a rectangular array of numbers; multiplying a vector by a matrix produces a new vector, and a rotation matrix turns a vector about the origin without changing its length (Equation-8). For each lesson, choose one printed result and confirm it by hand.

**Equation-8.** `R(θ) = [ cos θ   −sin θ ;  sin θ   cos θ ]`  
The 2 × 2 matrix that rotates a vector counterclockwise by the angle θ.

## Lab 2: The Joystick Frame

A frame is a set of axes in which coordinates are measured. The joystick reads its position in its own frame; the drive needs it in the frame of the robot, x to the right and y forward. A joystick mounted at an angle θ reads a vector that is rotated by −θ from the robot frame, so multiplying the reading by R(θ) returns it to the robot frame. Article 1009, Joystick Setup, corrects the eight orientations that are multiples of 90 degrees, with or without a reflection, by exchanging and reversing the analogRead() lines; the rotation matrix also corrects any angle between them.

**Code.** Lesson 19_JoystickFrame, Code-16. Part 1 checks rotations of 90, −90, and −45 degrees with test vectors and prints Failures: 0. Part 2 reads the live joystick once per second and prints the raw vector, the corrected vector, and the octant from Joystick.h. MOUNT_ANGLE_DEG in line 42 sets the angle at which the joystick is mounted, counterclockwise as seen from above.

1. Make the two analogRead() lines match Experiment-2, upload with MOUNT_ANGLE_DEG = 0, and confirm that the raw and corrected vectors agree and that the octants of the eight checklist positions agree with Table-8.

2. Turn the joystick module 45 degrees counterclockwise on the bench and repeat. Record the octants with MOUNT_ANGLE_DEG = 0, then set it to 45, upload, and record them again.

3. Turn the module to 90 degrees and find the correction twice: once by exchanging and reversing the analogRead() lines as in Article 1009, Joystick Setup, and once with MOUNT_ANGLE_DEG = 90 and the original lines. Show on paper that the two corrections are the same matrix.

**Expected output and verification.** Part 1 prints Failures: 0. With the correct mount angle, the eight positions report the octants of Table-8 for any mounting angle. A rotation keeps the magnitude of the vector, so the corner positions still have a magnitude of 1.414.


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
