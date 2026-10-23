//
// Carpenter Software
// File: Class Common.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL
//
// By Jesse Carpenter (carpentersoftware.com)
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//

#ifndef Common_h
#define Common_h

// ======================================================
// ALGORITHM: Joystick.h (Revised Implementation)
// Single unified algorithm for motor control.
// ======================================================

// ======================================================
// DEBUG SELECTION (revised 20261022, v6.0.0)
// The debug switches are defined in the program that uses them,
// above its first #include, not in this file. Only Step2_JUL has
// them (src/Step2_JUL/main.cpp):
//   DEBUG_STEP2_JOYSTICK  prints the joystick signal chain
//   DEBUG_STEP2_L298N     prints the L298N pin states
// A program that defines no switch gets no debug output, so the
// other programs that include this file (Step3_Generator and
// lessons 18 and 19 of Step5_MathLessons) need no line for it.
// This file turns each switch into the flag that Joystick.h and
// L298N.h test, and sets DEBUG_SERIAL_ON; do not set those three
// flags manually.
// Step1_Joystick (no switch) and Step4_Generated (DEBUG_GENERATED)
// do not include this file; the switch of Step4_Generated is in
// its own main.cpp.
// Up to v5.1.0 this file defined DEBUG_MAIN, DEBUG_JOYSTICK, and
// DEBUG_L298N itself, and DEBUG_ALL_OFF turned them off.
// ======================================================
#ifdef DEBUG_STEP2_JOYSTICK
#define DEBUG_JOYSTICK
#define DEBUG_SERIAL_ON
#endif
// ------------------------------------------------------
#ifdef DEBUG_STEP2_L298N
#define DEBUG_L298N
#define DEBUG_SERIAL_ON
#endif

// ======================================================
// TIMER
// Automatically set based on debug state: 3000 ms while a debug
// switch is defined, so the serial output can be read; 100 ms
// without one.
// ======================================================
#ifdef DEBUG_SERIAL_ON
#define BUTTON_TIMER_mS 3000
#else
#define BUTTON_TIMER_mS 100
#endif

#endif // Common_h
