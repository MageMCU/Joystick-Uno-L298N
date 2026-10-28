//
// Carpenter Software
// File: JoystickCenter.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL
//
// By Jesse Carpenter (carpentersoftware.com)
//
// MIT LICENSE
//
// RELEASE
//   2026-10-28  v6.8.0
//   JoystickCenter.h last changed: 2026-10-28  v6.8.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//
// The joystick center (added 20261025, v6.4.0)
//
// WHY THIS FILE WAS ADDED
// A thumb joystick seldom rests at exactly 511, the middle of the
// ADC range 0 to 1023. The rest reading of an axis is called its
// center. When the center differs from 511, a released grip reads
// as a small push in one direction, and the dead zone must be made
// wider to hide it. The bench test of v6.3.1.a showed this: an old
// joystick failed Step1_Joystick Test 3 with its x center more than
// 25 counts from 511. This file keeps the measured center of each
// axis in one place, so each program reads the same two values and
// a resting grip maps to 0.
//
// WHERE IT IS USED
//   Step1_Joystick     Includes it to show the center now in the
//                      project. Test 3 measures the center; after a
//                      passing self test the report prints a new copy
//                      of this file.
//   Step3_Generator    Check 1 shows these two values for the student
//                      to confirm, rejects a value outside 461 to 561
//                      at compile time (#error), and writes them into
//                      Step4_Generated as X_CENTER and Y_CENTER.
//   Step4_Generated    Does not include this file. It holds the copied
//                      values, which claude/ace.h uses to move each
//                      reading by its offset from 511.
//   Lesson 17          DeadZone: prints the centers and suggests the
//                      dead zone offset about each center (v6.4.1).
//   Lesson 20          JoystickMap: the center of each two segment map
//                      (v6.4.1).
//   Step2_JUL          Does not use it; it keeps the center 511
//                      (author decision, v6.4.0).
//
// HOW TO UPDATE IT
// Shipped with 511 and 511, which leave every reading unchanged.
// After a passing self test, replace the whole file with the lines
// Step1_Joystick prints between its two marker lines. Then run
// Step3_Generator again so Step4_Generated receives the new values.
// Allowed range: 461 to 561 (Step1_Joystick, Test 3 fails a center
// more than 50 counts from 511 and warns above 25 counts: a new
// joystick is recommended; v6.5.0).
//
// SELF TEST REPORT
// None: the shipped values 511 and 511 were not measured. The file
// printed by Step1_Joystick holds the report of its self test here
// (v6.8.0).
//

#ifndef JoystickCenter_h
#define JoystickCenter_h

#define JOYSTICK_A0_CENTER 511
#define JOYSTICK_A1_CENTER 511

#endif
