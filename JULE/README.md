## Joystick Uno L298N with Encoders (JULE)

- namespace ***uno***

## ***include folder***

**Following classes are stand-alone**
- **Bitwise.h**   - (The file is located in the *Numerics* Repository)
- **Button.h** 
- **LinearMap.h** - (The file is located in the *Numerics* Repository)
- **Timer.h**     - (The file is located in the *Numerics* Repository)

***Followng classes are dependent on the stand-alones***
+ ***Joystick.h***  - The Joystick Algorithm Class has been simplified for upcoming projects. Class updated...
+ ***L298N.h***     - The L298N Class has a new method to setup the dc-motors. Class updated...

## ***src folder***

- main.cpp - NEW METHOD - Has experimental code for motor encoders using Arduino's Interrupt-Pins 2 and 3. There are 8 combinations for Reverse-Inputs and Direction-Motors, *motors.Bits(uno::MotorBits::motorsFFF);*...

## ***root folder***

- platformio.ini        - (Please review this document for platform configuration while testing the code.)

## ***Notes***

- Updated 20230114...