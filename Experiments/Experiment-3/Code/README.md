# Joystick-Uno-L298N, Experiment-3 Code

Standalone PlatformIO draft for cautious, single-motor L298N familiarization. Open
this folder in VS Code and follow [`../Instructions/README.md`](../Instructions/README.md).

Draft project; confirm the mapping and safety instructions against the module.

The sketch uses the production `L298N`, `Bitwise`, `Button`, and `Timer`
headers copied into this project's `include/` folder. It uses the direct
channel-A mapping `bits_1100` and requires the operator to hold the enable
button; after the button's 50 ms debounce, releasing it removes PWM. A change
between forward and reverse enforces 300 ms at zero first, including when a
stop command was sent before requesting the opposite direction.

**Black-box boundary:** serial command and enable-button state are inputs;
driver commands and actual motor movement are outputs to compare. This is a
work in progress and has not been physically tested on hardware. Do not
power the motor without instructor review. See the
[experiment safety notice](../../../Experiments.md) and the
[Carpenter Software Disclaimer](https://github.com/MageMCU/Carpenter-Software-Disclaimer/blob/main/README.md).
