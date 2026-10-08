# Joystick-Uno-L298N, Experiment-5 Code

Standalone PlatformIO draft for Article 1009 Procedure 2 (**L298N Setup**):
joystick-to-driver control, selectable `Bits()` patterns, checklist
diagnostics, and post-check voltage measurements. Open this folder in VS Code and follow
[`../Instructions/README.md`](../Instructions/README.md).

Build-checked only; the powered checklist, physical movement, and meter
measurements have not been validated on hardware. Follow the exact module
instructions and supervised safety procedure.

The sketch starts at `bits_0000`; send a hexadecimal digit `0`-`f` to select
another pattern only while D2 is released. It reports the E/P/L/R flags and,
while D2 is held, the octant and left/right PWM values every 100 ms. The
Article 1009 [eight-direction checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4) and voltage worksheet are completed
and recorded by the operator; serial diagnostics alone do not validate motor
movement.

**Black-box boundary:** stick, enable, pattern, and supply are inputs; motor
movement and voltage readings are physical outputs, with serial diagnostics
as intermediate observations. This is a work in progress and has not been
physically tested. Do not energize motor hardware before supervised review.
See the [experiment safety notice](../../../Experiments.md) and the
[Carpenter Software Disclaimer](https://github.com/MageMCU/MageMCU-Carpenter_Software-Disclaimer/blob/main/README_20260924.md).
