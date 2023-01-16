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

- main.cpp - NEW METHOD - Has experimental code for motor encoders using Arduino's Interrupt-Pins 2 and 3. There are 8 combinations for Reverse-Inputs and Direction-Motors, *motors.Bits(uno::MotorBits::motorsFFF);*... Simply plugin one 3-boolean value at a time from the eight possible values until the motors behave as expected. This is beeter than rearranging the actual wires among the two motors and the L298N module.

## ***root folder***

- platformio.ini        - (Please review this document for platform configuration while testing the code.)

## ***Notes***

- Updated 20230116...There is a new article ***1009 L298N Supplemental*** I'll be changing the names of the article's folders for clarity...
