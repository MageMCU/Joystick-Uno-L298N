## Simplified Joystick Uno L298N (SJUL)

- namespace ***uno***

## ***include folder***

**Following classes are stand-alone**
- **Bitwise.h**   - (The file is located in the *Numerics* Repository)
- **Button.h** 
- **LinearMap.h** - (The file is located in the *Numerics* Repository)
- **Timer.h** 

***Followng classes are dependent on the stand-alones***
+ ***Joystick.h***  - The Joystick Algorithm Class has been simplified for upcoming projects.
+ ***L298N.h***     - The L298N Class has a new method to setup dc-motors.

## ***src folder***

- main.cpp - (has new L298N method example to setup dc-motors instead of matching the system's wiring within the entire code... ALso mapping has been removed from the Joystick Algorithm Class and LinearMap.h is now used in the main.cpp. The Joystick Algorithm Class has been simplified for upcoming projects.)

## ***root folder***

- platformio.ini        - (Please review this document for platform configuration while testing the code.)

## ***Notes***

The older **Joystick-Uno-L298N** code especially the *Debug version* was too difficult to understand the debugging and the *Release version* was too complicated with unnessary code. The **Simplified-Joystick-Uno-L298N** code is better than the two older versions.

