//
// Carpenter Software
// File: Class Common.h
// Github: MageMCU
// Repository: Joystick-UNO-L298N
// Folder: Code
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

// Comment-out "// #define RUN_WITH_DEBUG_CODE"s
// to remove Serial Debugging
// ------------------------------------------------------
#define RUN_WITH_DEBUG_CODE
// ------------------------------------------------------
#ifdef RUN_WITH_DEBUG_CODE
// ------------------------------------------------------
#define DEBUG_MAIN
#define DEBUG_JOYSTICK
#define DEBUG_L298N
#define BUTTON_TIMER_mS 1000
#else
#define BUTTON_TIMER_mS 100
#endif
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------

#endif // hearder