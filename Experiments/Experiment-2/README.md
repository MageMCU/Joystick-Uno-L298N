# Joystick-Uno-L298N Experiment-2

## Article 1009 Procedure 1: Joystick Setup

This standalone experiment implements Article 1009's **Joystick Setup**:
verify the joystick button and both analog axes in software, with no motor
driver or motors connected. Correct swapped or reversed axes in the program,
not by moving wires.

- Open [`Code/`](Code/) as the PlatformIO project.
- Follow the wiring, activity, verification, and troubleshooting guide in
  [`Instructions/README.md`](Instructions/README.md).
- The sketch reads X on A1 and Y on A0 and uses the production `Button` and
  `Timer` headers copied into `Code/include/`.

Draft; build-verified for the Arduino Uno. Physical joystick setup remains to
be completed.

**Black-box question:** How do stick position and button presses change the
measured ADC values and button output? Predict, test one input at a time,
record evidence, and revise the explanation using the notebook linked in the
instructions.

This is a work in progress and has not been physically tested on hardware.
Review the [experiment safety notice](../../Experiments.md) and the
[Carpenter Software Disclaimer](https://github.com/MageMCU/MageMCU-Carpenter_Software-Disclaimer/blob/main/README_20260924.md)
before use.
