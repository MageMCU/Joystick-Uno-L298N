# Joystick-Uno-L298N, Experiment-2 Code

Standalone PlatformIO project for Article 1009's **Joystick Setup** procedure.
Open this folder in VS Code. See [`../Instructions/README.md`](../Instructions/README.md)
for wiring and the learner guide.

No motor driver or motors are connected. The sketch tests the joystick button
with the production `Button` class, then reports raw X/Y analog readings. It
uses the production `Button.h` and `Timer.h` copies in `include/`.

Draft project; physical joystick wiring and behavior still need review and
testing.

Build with PlatformIO for an Arduino Uno. The source filter includes this
project's single `main.cpp`.

**Black-box boundary:** joystick stick/button are inputs; ADC readings,
button state, LED, and serial output are observable outputs. Use the
instructions to make and test predictions.

Work in progress; this project has not been physically tested on hardware.
See [experiment safety notice](../../../Experiments.md) and the
[Carpenter Software Disclaimer](https://github.com/MageMCU/MageMCU-Carpenter_Software-Disclaimer/blob/main/README_20260924.md).
