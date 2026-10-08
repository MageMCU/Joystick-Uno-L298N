# Joystick-Uno-L298N, Experiment-4 Code

Standalone PlatformIO draft for decoding the L298N's 16 `BitsL298N`
configurations before the powered setup procedure. Open this folder in VS
Code and follow
[`../Instructions/README.md`](../Instructions/README.md).

This software-only pre-lab connects only the Uno by USB. It does not configure
L298N output pins or drive motors. Enter a hex digit `0`-`f` to display the
four configuration flags.

**Black-box boundary:** the input is one hex digit; the output is the decoded
bit pattern and flags. The software has not been physically tested on
hardware and remains a work in progress. Keep it software-only. See the
[experiment safety notice](../../../Experiments.md) and the
[Carpenter Software Disclaimer](https://github.com/MageMCU/MageMCU-Carpenter_Software-Disclaimer/blob/main/README_20260924.md).
