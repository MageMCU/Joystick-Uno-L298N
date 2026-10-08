# Joystick-Uno-L298N Experiment-3

## L298N Setup Preparation: One Motor

Carpenter Software, Jesse Carpenter. STEM Starter Kit Series, Part 5
(Article 1004), Experiment-3. This optional motor familiarization supports
the second formal Article 1009 procedure, **L298N Setup**. It is preparation,
not a substitute for that procedure or its Motor Movement Checklist.

> **Draft:** Review the instructions and confirm them against the exact L298N
> module before classroom or motor-power use. The Uno build succeeded; no
> physical motor test has been performed.

---

## 1. Overview

The Uno controls the L298N logic inputs; a separate, correctly rated motor
supply powers the motor. This sketch exercises one motor on channel A at a
fixed, limited PWM value. While D2 is held, use the Serial Monitor to request
forward (`w`), reverse (`s`), or stop (`x`). Before reversing, the code sets
the command to zero for 300 ms. Releasing D2 removes PWM after the 50 ms
button debounce.

The experiment uses `L298N.h` and its `Bitwise.h` dependency. It does not yet
use the joystick or attempt to drive a robot.

### Black-box investigation

For this optional activity, investigate the motor/driver/control path as the
black box. Inputs are the D2 enable state and serial commands; observable
outputs are the Uno's reported state and the motor's measured/observed
movement. Predict each result before a trial, vary one command at a time, and
record actual movement and operating conditions separately from code output.
Use the [Article 1004 lab notebook template](../../LAB-NOTEBOOK-TEMPLATE.md)
to compare the prediction and evidence. Do not proceed to a powered test
until the instructor has reviewed the exact hardware and safety setup.

---

## 2. Materials

| Item | Qty | Notes |
|------|-----|-------|
| Arduino Uno and USB cable | 1 | Logic, upload and control |
| L298N module | 1 | Check its exact board labels and jumper arrangement |
| DC motor compatible with its supply and driver | 1 | Connect to channel A output terminals |
| Motor power supply | 1 | Correct voltage/current for the motor |
| Momentary push button | 1 | D2 to GND; internal pull-up is used |
| Indicator LED and 220 Ohm resistor | 1 each | D3 indicator |
| Jumper wires | as needed | Disconnect power before changing wiring |

Do not power a motor from an Uno I/O pin or the Uno 5V pin.

---

## 3. Software Setup

Open `Experiments/Experiment-3/Code/` in VS Code. Build and upload with
PlatformIO, then hold the D2 button to run the test. The project has one
sketch. The copied `L298N`, `Bitwise`, `Button`, `Timer`, and support headers
keep it independent of other project folders.

---

## 4. Wiring and Safety

Disconnect USB and motor supply before wiring. Use the pin assignments in the
firmware:

| Uno pin | L298N connection |
|---------|------------------|
| D5 | ENA |
| D6 | IN1 |
| D7 | IN2 |
| D2 | Momentary enable switch to GND |
| D3 | Indicator LED through 220 Ohm resistor |
| GND | L298N logic GND and motor-supply negative/common ground |
| — | Motor connected only to channel A output terminals |

Connect the motor supply to the module's motor-supply input according to that
module's markings. Module jumper/regulator arrangements vary: follow the
board manufacturer's documentation and the Article 1003 wiring plan. Never
feed the motor supply into the Uno 5V pin, never connect motor outputs to Uno
pins, and do not move jumpers while powered. Ensure the Uno and driver share
ground.

Before the first powered test, raise and secure the motor so it cannot move
the robot, keep hands clear, and have a way to disconnect motor power. Start
with the motor disconnected and verify the logic wiring.

---

## 5. Activity

1. Upload the sketch with the motor supply disconnected.
2. Verify the enable switch is released and the indicator is off.
3. Recheck ENA/IN1/IN2, grounds, supply polarity, and the motor terminals.
4. Secure the motor and connect the motor supply only after the checks pass.
5. Hold D2 and send `w`. The motor runs at PWM 80/255.
6. Send `x` to stop, then send `s` to request reverse. The firmware enforces
   a 300 ms zero-output interval before applying reverse PWM, even if you
   have already sent `x`.
7. Release D2. After the button debounce, PWM is disabled.
8. Disconnect motor power before changing any wiring.

PWM 80 is a limited test command, not a promise that every motor will start:
motor friction and the L298N voltage drop affect the result. Do not increase
the value until the wiring, supply and motor ratings are confirmed.

Use the [Article 1004 lab notebook template](../../LAB-NOTEBOOK-TEMPLATE.md) to
record the supply and motor/module used, your prediction, requested command,
observed direction, whether PWM 80 starts the motor, and any heating or
unexpected behavior. Article 1003 explains why driver voltage loss affects
motor voltage and why power dissipated in the L298N becomes heat; stop and
investigate unexpected heating rather than treating it as a normal result.

### What the code does

`PinsL298N()` configures the driver's six Uno pins and powers down the enable
outputs. `Bits(bits_1100)` routes the first signed motor command to channel A
with the direct left-input mapping. `Button` is configured in momentary mode
so motor enable is true only while the operator holds the button. On a
direction change, `Timer` holds the motor command at zero for 300 ms before
applying the new direction; the interlock still applies if `x` was sent
first. The button is sampled on every pass through `loop()`.

The sketch calls `PowerDownL298N()` whenever the enable is released. It uses
channel A for the motor and sends zero PWM to channel B.

---

## 6. Verification and Troubleshooting

| Check | Expected result |
|-------|-----------------|
| Button released | Indicator off; after 50 ms debounce, enable PWM disabled |
| `w` sent while enabled | Channel A receives PWM 80 |
| `s` sent after `w` | Output command is zero for 300 ms before reverse PWM |
| `x` sent | Motor command is zero |
| Button released during motion | PWM disable occurs after button debounce |
| Motor does not start | First verify supply voltage, module wiring and ground; PWM 80 may be below its start threshold |

| Symptom | Check |
|---------|-------|
| No motor movement | Confirm supply and motor ratings, common ground, ENA jumper/PWM arrangement, and OUT1/OUT2 connections |
| Direction differs from expectation | Motor lead polarity and driver input mapping determine physical direction; document what the bench shows |
| Uno resets | Separate motor supply, verify common ground and current capability, check for shorts |
| Motor keeps receiving PWM after release | Check D2-to-GND wiring and ensure this experiment's sketch is uploaded |

---

## 7. What Carries Forward

Record which physical motor direction corresponds to each signed command.
Do not assume that “forward” is universal: motor mounting and wire polarity
matter. Experiment-4 is an optional `Bits()` familiarization. The formal
L298N Setup procedure is completed in Experiment-5 with the joystick and the
Article 1009 Motor Movement Checklist.

## References

Safety and draft status: this experiment has not been physically tested on
hardware and remains a work in progress. Do not connect or power the motor
until the setup has been reviewed and supervised. Read the
[Carpenter Software Disclaimer](https://github.com/MageMCU/Carpenter-Software-Disclaimer/blob/main/README.md)
before use.

1. Article 1002, *Arduino Uno: Pins, Ports, and Peripherals* (GPIO and PWM pins).
2. Article 1003, *L298N Motor Driver* (H-bridge, voltage loss, and heating).
3. Article 1009 supplemental motor-movement checklist and parent/teacher/
   student guide.
4. `Code-JUL/include/L298N.h` and `Code-JUL/include/Bitwise.h`.

MIT License. Carpenter Software, Jesse Carpenter.
