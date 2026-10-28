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
// RELEASE
//   2026-10-28  v6.8.0
//   Common.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

#ifndef Common_h
#define Common_h

// ======================================================
// ALGORITHM: Joystick.h (Revised Implementation)
// Single unified algorithm for motor control.
// ======================================================

// ======================================================
// DEBUG SELECTION
// Uncomment a module to enable its serial debug output.
// DEBUG_SERIAL_ON activates automatically: do not set it manually.
// NOTE: Enabling DEBUG_JOYSTICK also sets BUTTON_TIMER_mS to 3000ms.
//       Comment it out for normal (100ms) motor control loop speed.
// ======================================================
// #define DEBUG_MAIN
#ifdef DEBUG_MAIN
#define DEBUG_SERIAL_ON
#endif
// ------------------------------------------------------
// #define DEBUG_JOYSTICK
#ifdef DEBUG_JOYSTICK
#define DEBUG_SERIAL_ON
#endif
// ------------------------------------------------------
// #define DEBUG_L298N
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

// Common_h
#endif
