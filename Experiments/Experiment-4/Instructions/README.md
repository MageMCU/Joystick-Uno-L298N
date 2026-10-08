# Joystick-Uno-L298N, Experiment-4

## L298N Bits Table Familiarization

This optional, software-only activity prepares learners to read the
`BitsL298N` patterns used in Article 1009's formal **L298N Setup**. It uses
the flag definitions in Article 1003 and the Uno's digital representation
and serial I/O described in Article 1002. It is not a powered motor test and
does not replace the [Article 1009 Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4).

> **Draft:** The Uno build has been verified. This exercise uses only the Uno
> connected by USB; no L298N module or motors are connected.

---

## 1. Goal

Enter hexadecimal values `0` through `f` in the Serial Monitor and relate
each value to the four configuration flags in bit order 3, 2, 1, 0:

| Flag | Bit | Meaning in `L298N::Bits()` |
|------|-----|----------------------------|
| E | 3 | Swap the two motor channels |
| P | 2 | Reverse the L298N input mapping |
| L | 1 | Change the left motor direction |
| R | 0 | Change the right motor direction |

The sketch prints the corresponding `bits_XXXX` pattern and `E/P/L/R`
values. It only decodes the value; it does not call `PinsL298N()`, configure
output pins, or energize a motor.

### Black-box investigation

The software decoder is the black box in this low-risk exercise. The
hexadecimal character is the input; the displayed `bits_XXXX` pattern and
E/P/L/R flags are observable outputs. Predict the output before each entry,
change one input bit at a time, and compare the report with the bit
definitions. Record any mismatch and test it again. This validates the
decoder's representation only; it does not reveal how a physical L298N/motor
assembly behaves. Use the
[Article 1004 lab notebook template](../../LAB-NOTEBOOK-TEMPLATE.md).

## 2. Materials and Setup

- Arduino Uno and USB cable
- VS Code with PlatformIO
- Serial Monitor set to 9600 baud

Open `Experiments/Experiment-4/Code/` as the PlatformIO project, build, and
upload. Connect only the Uno over USB. Keep the L298N and motors disconnected.

## 3. Activity

1. Open the Serial Monitor at 9600 baud.
2. Enter `0`, then `1`, and compare the reported binary patterns.
3. Continue through `f`, recording how one changed bit affects E, P, L, or R.
4. Check the patterns against the `BitsL298N` table in `L298N.h`.
5. Explain why the formal setup tests one configuration at a time and records
   actual movement instead of assuming a bit pattern matches a motor layout.

Record your prediction and the reported pattern/flags for every input from
`0` through `f` in the [Article 1004 lab notebook template](../../LAB-NOTEBOOK-TEMPLATE.md).
For each step, describe which single flag or flags changed from the prior
value. Keep this activity software-only; it is not a powered driver test.

| Input | Expected pattern | E/P/L/R | Notes |
|-------|------------------|---------|-------|
| `0` | `bits_0000` | `0/0/0/0` | |
| `1` | `bits_0001` | | |
| `2` | `bits_0010` | | |
| `3` | `bits_0011` | | |
| `4` | `bits_0100` | | |
| `5` | `bits_0101` | | |
| `6` | `bits_0110` | | |
| `7` | `bits_0111` | | |
| `8` | `bits_1000` | | |
| `9` | `bits_1001` | | |
| `a` | `bits_1010` | `1/0/1/0` | |
| `b` | `bits_1011` | | |
| `c` | `bits_1100` | | |
| `d` | `bits_1101` | | |
| `e` | `bits_1110` | | |
| `f` | `bits_1111` | `1/1/1/1` | |

## 4. Carry Forward

Use this activity to understand the checklist's E/P/L/R columns only. In
Experiment-5, with supervised hardware and the motor supply handled safely,
the operator selects patterns while the enable button is released, tests the
eight joystick directions, and records observed motion. This table exercise
cannot establish the correct pattern for a particular module, wiring layout,
or motor mounting.

## References

Safety and draft status: this experiment has not been physically tested on
hardware and remains a work in progress. Keep the activity software-only;
do not connect or energize motor hardware. Review the
[Carpenter Software Disclaimer](https://github.com/MageMCU/MageMCU-Carpenter_Software-Disclaimer/blob/main/README_20260924.md)
before use.

1. Article 1002, *Arduino Uno: Pins, Ports, and Peripherals*.
2. Article 1003, *L298N Motor Driver*.
3. Article 1009 and its [supplemental Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4).
4. `Code-JUL/include/L298N.h` and `Code-JUL/include/Bitwise.h`.

MIT License. [Carpenter Software](https://carpentersoftware.com), Jesse Carpenter.
