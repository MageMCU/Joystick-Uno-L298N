//
// Carpenter Software
// File: DEBUG DEBUG.h (debug version)
// Folder: joystick_L298N_debug
// Purpose: Github Depository (MageMCU)
//
// Teacher's and Parent's copy...
// Dedicated to Parents and Teachers of the USA.
// Teachers Note: The _BEGIN_DEBUG is defined (see
//                DEBUG.h file), also MAIN _ANALOG_
//                is defined for debugging the
//                analog readings. For safety
//                reasons while debugging, the
//                motors are conditioned not to
//                operate. Be warned. the Student's
//                copy has no safety feature.
//
// Hardware
// MCU: Atmega328P (Microchip)
// * Board: Arduino Uno (Italy)
// Thumb Joystick: (China)
// Motor Driver: L298N (ST)
// * Motor Module: (China)
// 12V Geared Motors (ratio 1:75) (China)
// Note: motors: current peaks on average 1.14 amps
//       for static friction, and it levels down to
//       about 0.29 amps for dynamic friction. When
//       joystick with hands-off (center position),
//       is about 0.10 amps. The robot was sitting
//       on stand with no weight on wheels, otherwise,
//       the electrical currents would have increased.
// Battery 12V - APX1250 (12V 5.0Ah) Sealed Lead-Acid
// Note: battery: with five years design life (using
//       now for 7 years.) Requires special battery
//       charger from APEX.
//
// By Jesse Carpenter (Github as MageMCU)
//
// CHANGELOG
// August 30, 2021 - debug comments
// August 24, 2021 - editing
// June 19, 2021 - programming debug version
//
// Atmega328P Total Usgae
// RAM : [==] 15.3 % (used 314 bytes from 2048 bytes)
// Flash : [==] 21.2 % (used 6846 bytes from 32256 bytes)
//
// MIT LICENSE
//

#ifndef __UNO_DEBUG_H__
#define __UNO_DEBUG_H__

// MAIN AND ALL DEPENDENCIES
// FOR DEBUGGING...
//////////////////////////////////
// BEGIN DEBUG HEADERS AND MAIN //
//          UN-COMMENT          //
//////////////////////////////////
#define _BEGIN_DEBUG
//////////////////////////////////
//         DO NOT TOUCH         //
//////////////////////////////////
#ifdef _BEGIN_DEBUG
// DEBUG MAIN
#define _dM_
#ifdef _dM_

//////////////////////////////////
//             MAIN             //
//////////////////////////////////

// (1) MAIN ANALOG DEBUG
#define _ANALOG_

// (4) MAIN JOYSTICK DEBUG
// #define _JOYSTICK_

// MAIN L298N DEBUG
// #define _L298N_

//////////////////////////////////
//            HEADERS           //
//////////////////////////////////

// (2) DEBUG JOYSTICK
// #define _dJ_

// (3) DEBUG L298N
// #define _dL_

// DEBUG TIMER
// #define _dT_

// DEBUG BUTTON
// #define _dB_

//////////////////////////////////
//           JOYSTICK           //
//////////////////////////////////
#ifdef _dJ_

// _alignRawData()
#define _ALIGN_

// _shiftFromZeroToMidpoint()
#define _SHIFT_

// _adjustToDynamicFriction()
#define _DYNAMIC_

// _integerToDouble()
#define _DOUBLE_

// _joystAlgorithm()
#define _NORMAL_

//IF-DEF-HEADER-dJ/////////////////////////
#endif

//////////////////////////////////
//           L298N              //
//////////////////////////////////
#ifdef _dL_

// Write definitions here
// The code is small...
// #define _SOMETHING_ you want to DEBUG

//IF-DEF-HEADER-dL/////////////////////////
#endif
//IF-DEF-MAIN/////////////////////////
#endif
// IF-DEF-ALL ////////////////////////
#endif
// DEFINE-ALL    /////////////////////
#endif