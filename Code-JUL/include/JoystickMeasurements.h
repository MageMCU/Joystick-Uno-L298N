// ----- BEGIN JoystickMeasurements.h -----
//
// Carpenter Software
// File: JoystickMeasurements.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL
//
// By Jesse Carpenter (carpentersoftware.com)
//
// MIT LICENSE
//
// RELEASE
//   2026-10-30  v7.3.0
//   JoystickMeasurements.h printed by Step1_Joystick
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//
// The joystick measurements (v7.0.0; include/JoystickCenter.h, added
// in v6.4.0, held the two centers only)
//
// WHY THIS FILE EXISTS
// A thumb joystick seldom rests at exactly 511, the middle of the
// ADC range 0 to 1023, and seldom reaches 0 and 1023 at its ends.
// Step1_Joystick measures three points of each axis in raw ADC
// counts: the center, the rest reading (Test 3), and the low end and
// the high end, the smallest and largest reading with the grip held
// UP, DOWN, LEFT, and RIGHT (Test 4), verified by a circle (Test 5).
// This file keeps those six measured values in one place.
// Step4_Generated corrects each axis at the center and at both ends
// with two linear equations, one on each side of the center
// (include/claude/ace.h, THE JOYSTICK EQUATIONS), so a resting grip
// gives 0 and a full push gives the full command on both sides.
//
// WHERE IT IS USED
//   Step1_Joystick     Includes it to compare the values now in the
//                      project with a new self test, and to print
//                      the calculated N in the live values. After a
//                      passing self test the report prints a new copy
//                      of this file.
//   Step3_Generator    Check 1 shows the six values for the student
//                      to confirm, rejects values outside the Step1
//                      limits when it is built (#error), and writes
//                      them into Step4_Generated.
//   Step4_Generated    Does not include this file. It holds the copied
//                      values, which claude/ace.h uses in THE JOYSTICK
//                      EQUATIONS.
//   Lesson 17          DeadZone: prints the centers and suggests the
//                      dead zone offset about each center.
//   Lesson 20          JoystickMap: the low end, center, and high end
//                      of each two segment map.
//   Step2_JUL          Does not use it; it keeps the center 511
//                      (author decision, v6.4.0).
//
// HOW TO UPDATE IT
// Shipped with 0, 511, and 1023 for each axis; these were not
// measured. After a passing self test, replace the whole file with
// the lines Step1_Joystick prints between its two marker lines. Then
// run Step3_Generator again so Step4_Generated receives the new
// values. Limits (Step1_Joystick): each center 461 to 561 (Test 3
// fails a center more than 50 counts from 511 and warns above 25
// counts: a new joystick is recommended); each end at least 200
// counts from its center (Tests 4 and 5).
//
// SELF TEST REPORT
// A * holds values for the check list.
//
// CENTER (Test 3, grip at rest)
//   A0CO = A0C - 511
//   A1CO = A1C - 511
//             A0C    A1C    A0CO   A1CO
//   *         517    503    6      -8
//
// FIRST ENTRY (Test 4, grip held at each edge)
//   A0O = A0 - A0C
//   A1O = A1 - A1C
//     dir     A0     A1     A0O    A1O
//   * UP      0      503    -517   0
//   * DOWN    1020   506    503    3
//   * LEFT    517    0      0      -503
//   * RIGHT   517    1020   0      517
// ENDS: the smallest and largest held reading
//     end     A0L    A0H    A1L    A1H
//   * value   0      1020   0      1020
//   * dir     UP     DOWN   LEFT   RIGHT
//
// SECOND ENTRY (Test 5, circle twice)
//     end     A0SL   A0SH   A1SL   A1SH
//   * value   0      1020   0      1020
// VERIFICATION: circle end and held end
//   A0HD = A0SH - A0H
//   A0LD = A0L - A0SL
//   A1HD = A1SH - A1H
//   A1LD = A1L - A1SL
//             A0HD   A0LD   A1HD   A1LD
//   *         0      0      0      0
//
// RETURN (Test 6, grip released)
//   A0O = A0 - A0C
//   A1O = A1 - A1C
//             A0     A1     A0O    A1O
//   *         515    501    -2     -2
//
// RESULTS
//     test    T1     T2     T3     T4     T5     T6
//   * result  PASS   PASS   PASS   PASS   PASS   PASS
//   * warning -      -      NO     NO     NO     -
//   * Presses during Tests 3 to 6: 0 (0 expected)
//   * Result: PASS
//

#ifndef JoystickMeasurements_h
#define JoystickMeasurements_h

// Raw ADC counts (0 to 1023): low end, center, high end of each axis
#define JOYSTICK_A0_LOW 0
#define JOYSTICK_A0_CENTER 517
#define JOYSTICK_A0_HIGH 1020
#define JOYSTICK_A1_LOW 0
#define JOYSTICK_A1_CENTER 503
#define JOYSTICK_A1_HIGH 1020

#endif
// ----- END JoystickMeasurements.h -----