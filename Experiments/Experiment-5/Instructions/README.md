# Joystick-Uno-L298N, Experiment-5

## Article 1009 Procedure 2: L298N Setup

This draft integrates the joystick, the L298N driver, the `Bits()` settings,
the Article 1009 Motor Movement Checklist, and the follow-up voltage
measurements. Complete and record Experiment-2 (Article 1009 **Joystick
Setup**) before connecting the motor driver.

> **Draft and safety notice:** This guide and sketch require instructor review
> against the exact module and bench setup. The Uno build has been checked;
> no physical motor, direction, or voltage-measurement test has been
> performed. Follow the exact L298N board documentation and Article 1003.

---

## 1. Goal and Sketch Behavior

The sketch reads joystick X on A1 and Y on A0 every 100 ms while the D2
joystick button is held. It reports the joystick octant and signed left/right
PWM values over Serial. Releasing D2 powers down the L298N outputs after the
button's 50 ms debounce; this does not wait for the next control interval.

The sketch starts with `bits_0000`. While D2 is released, enter one
hexadecimal digit (`0` through `f`) in the Serial Monitor to select that
`Bits()` configuration. The sketch prints the four flags in bit order
E/P/L/R (bits 3/2/1/0). It ignores Bits input while D2 is held. The sketch
does not decide which configuration matches the physical motor layout; that
must be determined by the checklist.

### Black-box investigation

The combined joystick, firmware, L298N, supply, and motors form the system
under investigation. Inputs include stick position, enable state, selected
`Bits()` pattern, and supply/motor conditions; observable outputs include
ADC/serial diagnostics, wheel movement, and measured voltages. Predict the
outcome for one direction before each supervised trial, vary one factor at a
time, and compare serial commands with actual movement and meter readings.
A software diagnostic is not proof of physical behavior. Use the
[Article 1004 lab notebook template](../../LAB-NOTEBOOK-TEMPLATE.md) and
preserve a separate record for each tested pattern.

## 2. Materials

| Item | Qty | Notes |
|------|-----|-------|
| Arduino Uno and USB cable | 1 | |
| Two-axis joystick with SW contact | 1 | X=A1, Y=A0, SW to D2/GND |
| L298N module and compatible DC motors | 1 each | Check ratings and exact module instructions |
| Correctly rated motor supply | 1 | Never power motors from Uno 5V |
| Indicator LED and 220 Ohm resistor | 1 each | D3 |
| DC voltmeter | 1 | Use a suitable DC voltage range |
| Breadboard and jumper wires | as needed | Common ground as required by module |

## 3. Software and Wiring

Open `Experiments/Experiment-5/Code/` as the PlatformIO project. Build and
upload with motor power disconnected. The project includes copied production
headers for `Joystick`, `LinearMap`, `L298N`, `Bitwise`, `Button`, `Timer`,
and their dependencies.

| Signal | Uno pin |
|--------|---------|
| Joystick VRx / VRy | A1 / A0 |
| Joystick SW | D2 to GND; internal pull-up |
| Enable indicator LED | D3 through 220 Ohm resistor to GND |
| L298N ENA, IN1, IN2 | D5, D6, D7 |
| L298N IN3, IN4, ENB | D8, D9, D10 |
| Uno GND | L298N logic GND and common supply ground as required |

With all power disconnected, inspect signal wiring, motor connections, supply
polarity and common ground. Connect motors only to the L298N output
terminals. Module regulator/enable jumpers vary: follow the exact module
markings and Article 1003. Never connect motor supply voltage to Uno 5V, move
jumpers while powered, or connect motor outputs to Uno pins. Raise and secure
the wheels so the robot cannot drive off the bench. Keep hands, hair and loose
objects clear. Stop if the driver or motor becomes unexpectedly hot.

## 4. Article 1009 Motor Movement Checklist

Use the [Article 1009 supplemental Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4).
Have an instructor supervise the powered procedure. Keep motor power
disconnected until the wiring and voltage/polarity checks are complete.

1. Start with the joystick centered and D2 released. Open Serial Monitor at
   9600 baud and confirm the startup setting is `bits_0000`.
2. With motor power connected only after safety checks, hold D2 and test the
   cardinal directions first, then the diagonals. Test one direction at a
   time and record the expected arrow, observed movement, and pass/fail.
   Release D2 between tests if needed to stop the motors.
3. Complete all eight checklist positions for the selected configuration.
   Record its E/P/L/R flags and the observed movement for every position.
4. If any direction fails, release D2, enter the next pattern (`1` through
   `f`, in order), and repeat the full eight-direction checklist. Change
   patterns only while D2 is released. Stop at the first pattern that passes
   all eight positions and record it. Do not change wiring or module jumpers
   while powered.
5. Preserve the completed checklist and note the selected pattern, motor
   polarity, mounting orientation, supply, and test conditions. Use a
   separate full checklist page for each pattern in the
   [Article 1004 lab notebook template](../../LAB-NOTEBOOK-TEMPLATE.md).

The target behavior is the direction specified by the supplemental checklist,
not merely a nonzero octant or PWM report. Serial output is diagnostic
evidence only; it cannot prove that the physical wheels moved correctly.

| Checklist position | Expected direction | Observed direction | Pass/fail |
|--------------------|--------------------|--------------------|-----------|
| Forward | | | |
| Forward-right | | | |
| Right | | | |
| Reverse-right | | | |
| Reverse | | | |
| Reverse-left | | | |
| Left | | | |
| Forward-left | | | |

## 5. Follow-up Voltage Measurements

After identifying a passing `Bits()` configuration, perform Article 1009's
voltage checks with a DC voltmeter and the instructor's supervision. Use the
guide's specified supply/motor conditions and meter connection points; avoid
shorting adjacent terminals with the probes.

1. Measure and record the unloaded motor-supply bus voltage (`VS` to GND).
2. With the checklist configuration selected, measure the loaded bus voltage
   while commanding full-duty forward.
3. Measure the voltage across the motor output terminals under the specified
   operating condition.
4. Calculate the L298N drop as loaded bus voltage minus motor-terminal
   voltage. Record units and conditions with every value.
5. Repeat the measurements after changing the supply or motors, as directed
   by Article 1009. Variac use is instructor/supervisor-led only.

Record your prediction and every actual movement and meter reading in the
notebook. Include meter probe points, load state, units, supply and motor,
and supervision. Preserve failed-pattern records; do not overwrite them with
the final passing configuration.

| Measurement | Reading | Conditions / notes |
|-------------|---------|--------------------|
| Unloaded bus, VS to GND | | |
| Loaded bus, full-duty forward | | |
| Motor output terminals | | |
| Calculated driver drop | | |

## 6. Verification and Troubleshooting

| Check | Expected result |
|-------|-----------------|
| Uno build | PlatformIO succeeds for Uno/ATmega328P |
| D2 released | L298N PWM outputs powered down after button debounce |
| Hex input while released | Selected `Bits()` pattern and E/P/L/R flags reported |
| D2 held | Octant and left/right PWM diagnostic output every 100 ms |
| Eight checklist positions | Actual movement recorded; first all-pass Bits pattern retained |
| Voltage worksheet | Measurements and operating conditions recorded after checklist |

If an axis is wrong, revisit Experiment-2's joystick record. If the center
drifts, verify joystick power/ground and documented center offsets. For
incorrect motor direction, review the E/P/L/R pattern, motor leads, channel
mapping, and mounting; stop and disconnect motor power before any wiring
change. If the Uno resets or the driver overheats, stop and inspect ratings,
supply capacity, grounds, shorts, and cooling before proceeding.

## 7. Scope and References

Experiment-5 is the draft for the second formal Article 1009 procedure. It
does not claim physical validation, and it does not replace instructor
supervision or the complete source checklists. The optional Experiments 3
and 4 are preparation only.

Safety and draft status: this experiment has not been physically tested on
hardware and remains a work in progress. Do not power the L298N or motors
until the exact setup has been reviewed and the activity is supervised.
Review the [Carpenter Software Disclaimer](https://github.com/MageMCU/MageMCU-Carpenter_Software-Disclaimer/blob/main/README_20260924.md)
before use.

1. Article 1002, *Arduino Uno: Pins, Ports, and Peripherals*.
2. Article 1001, *Joystick Algorithm* (X/Y normalization and octant routing).
3. Article 1003, *L298N Motor Driver* (H-bridge, PWM, voltage loss, and heat).
4. Article 1009, *Parent, Teacher, and Student Guide*.
5. Article 1009 supplemental [*Motor Movement Checklist*](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4).
6. `Code-JUL/src/Step2_JUL/main.cpp` and `Code-JUL/include/L298N.h`.

MIT License. [Carpenter Software](https://carpentersoftware.com), Jesse Carpenter.
