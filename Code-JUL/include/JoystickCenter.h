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
// The joystick center (added 20261025, v6.4.0)
// The rest reading of each joystick axis, measured by Step1_Joystick
// (Test 3). Shipped with 511, the middle of 0 to 1023, which leaves
// every reading unchanged. After a passing self test, Step1_Joystick
// prints a new copy of this file: replace the whole file with the
// printed lines. Step3_Generator checks these two values and writes
// them into Step4_Generated; Step2_JUL does not use them.
// Allowed range: 411 to 611 (Step1_Joystick, Test 3).
//

#ifndef JoystickCenter_h
#define JoystickCenter_h

#define JOYSTICK_A0_CENTER 511
#define JOYSTICK_A1_CENTER 511

#endif
