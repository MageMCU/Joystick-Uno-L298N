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
// DEBUG SELECTION
// Revised 20261018 (v3.2.0): Step1_JUL ships with every debug flag
// on. It is the diagnostic program of the series: with the push
// button and the joystick it prints the values of the whole signal
// chain and the L298N pin states for the Joystick and Button Check
// and the Motor Movement Checklist (Article 1009, L298N Setup).
// Step3_Generated (include/claude/ace.h) is the drive program; it
// does not include this file.
// DEBUG_SERIAL_ON activates automatically; do not set it manually.
// NOTE: Any debug flag sets BUTTON_TIMER_mS to 3000 ms, so the
//       motors of Step1_JUL respond once every 3 s. To drive with
//       Step1_JUL at the 100 ms tick, comment out all three flags.
// DEBUG_ALL_OFF: a program that defines it before its first
//       include of this file gets no debug flag (lessons 18 and 19
//       of Step4_MathLessons, which keep the 100 ms tick and print
//       only their own output).
// ======================================================
#ifndef DEBUG_ALL_OFF
#define DEBUG_MAIN
#define DEBUG_JOYSTICK
#define DEBUG_L298N
#endif
// ------------------------------------------------------
#ifdef DEBUG_MAIN
#define DEBUG_SERIAL_ON
#endif
// ------------------------------------------------------
#ifdef DEBUG_JOYSTICK
#define DEBUG_SERIAL_ON
#endif
// ------------------------------------------------------
#ifdef DEBUG_L298N
#define DEBUG_SERIAL_ON
#endif

// ======================================================
// TIMER
// Automatically set based on debug state.
// ======================================================
#ifdef DEBUG_SERIAL_ON
#define BUTTON_TIMER_mS 3000
#else
#define BUTTON_TIMER_mS 100
#endif

#endif // Common_h
