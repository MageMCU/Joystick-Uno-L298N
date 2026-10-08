# Joystick-Uno-L298N Experiment-2

## Article 1009 Procedure 1: Joystick Setup

Carpenter Software, Jesse Carpenter. STEM Starter Kit Series, Part 5
(Article 1004), Experiment-2.

> **Draft:** This guide follows Article 1009's first formal setup procedure.
> Build verification is complete, but physical joystick testing remains.

---

## 1. Purpose

Article 1009's **Joystick Setup** verifies the joystick as a black box before
connecting motors. Use `Code-1` to check the joystick push button and read the
two analog axes on the serial monitor. If the axes are exchanged or reversed,
correct them with a one-line software change; do not move wires to make the
program agree.

This experiment uses the same production `Button` class as the project. It
does not use an L298N or motor. Complete and record this procedure before
starting the L298N Setup procedure.

### Black-box investigation

The joystick module is the black box. Its controlled inputs are stick
position and button press; its observable outputs are the two analog ADC
readings and the debounced button state/indicator. Predict which reading
should change before moving the stick along one axis, then test center,
extremes, and button independently. Compare repeated trials, infer the
module's axis directions and button behavior, and test any proposed software
swap or inversion with a new trial. Record the prediction and evidence in the
[Article 1004 lab notebook template](../../LAB-NOTEBOOK-TEMPLATE.md); do not
infer motor behavior from joystick measurements alone.

---

## 2. Materials

| Item | Qty | Notes |
|------|-----|-------|
| Arduino Uno and USB cable | 1 | |
| Two-axis thumb joystick with SW button | 1 | Treat the module as a black box |
| Breadboard and jumper wires | 1 set | |
| Indicator LED and 220 Ohm resistor | 1 each | D3 button-state indicator |

No driver, motor, or motor supply is connected.

---

## 3. Software Setup

Open `Experiments/Experiment-2/Code/` in VS Code. Build and upload the
standalone PlatformIO project, then open Serial Monitor at 9600 baud. The
project contains one sketch and copied `Button.h`/`Timer.h` headers.

---

## 4. Wiring

With USB disconnected, connect the joystick to the Uno:

| Joystick signal | Uno pin |
|-----------------|---------|
| VCC | 5V |
| GND | GND |
| VRx | A1 |
| VRy | A0 |
| SW | D2 |

Connect the indicator LED anode through a 220 Ohm resistor to D3 and its
cathode to GND. The production `Button` class uses the internal pull-up and
expects the joystick's SW contact to close to GND; do not add an external
pull-down for this default wiring. No L298N, motors, or motor supply should be
connected during this procedure.

---

## 5. Joystick Setup Procedure

1. Check the wiring and connect the Uno by USB.
2. Upload the sketch and open the Serial Monitor at 9600 baud.
3. Press the joystick's SW button once. The indicator LED should turn on and
   the serial monitor should report `Joystick button ON`.
4. Move the stick fully left, right, forward, and backward. Record the X/Y
   readings at center and at each extreme. The sketch labels X=A1 and Y=A0.
5. Press SW again. The LED should turn off and serial should report
   `Joystick button OFF`; readings should stop.
6. Repeat the button and axis checks as needed, then record the verified
   joystick wiring/orientation in the project notebook. Use the
   [Article 1004 lab notebook template](../../LAB-NOTEBOOK-TEMPLATE.md) and take
   more than one reading at each stick position.

The button state is debounced, so its LED and message change after the button
has passed the class's debounce interval, not at the instant of contact.

### 5.1 Correct the input in software

If horizontal movement changes the value labeled Y and vertical movement
changes X, exchange the `analogRead(A1)` and `analogRead(A0)` assignments in
`Code/src/main.cpp`.

If an axis counts downward when the joystick is moved in the intended
positive direction, reverse that axis in software. For example:

```cpp
const int xValue = 1023 - analogRead(A1);
```

Use the same transformation for Y only if your measurements show it is
reversed. Change one axis assignment at a time, rebuild, and repeat the
measurement. Keep the wiring fixed.

### 5.2 Relate the readings to Article 1001

Article 1001 treats the two potentiometer outputs as a joystick X/Y vector;
the pushbutton is a separate input. For a rough normalized coordinate from
the Uno's 10-bit ADC, calculate `2 * reading / 1023 - 1` for each measured
axis. Compare the center and directional readings with the article's
bounding-area/vector diagrams. This worksheet analysis does not change the
formal Joystick Setup sketch and does not predict physical motor movement;
the motor-routing algorithm is exercised later in Experiment-5.

### 5.3 Optional Article 1002: analog voltage and ADC counts

Article 1002 explains that the Uno's analog inputs use a 10-bit ADC, producing
readings from 0 to 1023 relative to the selected analog reference. As an
optional extension, use a DC voltmeter to measure one joystick output (VRx
or VRy) relative to GND at center and one extreme, then compare the voltage
with the corresponding serial ADC reading. Record the meter range, measured
voltage, ADC value, and joystick position. Do not let probe tips bridge
adjacent pins. Treat the conversion as approximate: the ADC reference and
joystick supply, meter accuracy, and module tolerances affect the result.
This is a measurement extension, not a change to Article 1009's required
axis/button setup.

---

## 6. Verification Record

| Test | Record |
|------|--------|
| SW press/release and indicator behavior | |
| Center ADC X/Y | |
| Full-left / full-right readings | |
| Full-backward / full-forward readings | |
| Axis swap or inversion applied in code | |
| Final verified X/Y pin and sign convention | |

Do not begin L298N Setup until the joystick button and axis interpretation are
known and recorded.

---

## 7. What Carries Forward

This completes the first of Article 1009's two major procedures. The second,
**L298N Setup**, pairs the joystick with `Code-2`, motor wiring, the `Bits()`
configuration, and the Motor Movement Checklist. Proceed only after the
Joystick Setup record is complete.

## References

Safety and draft status: this experiment has not been physically tested on
hardware and remains a work in progress. Review the
[Carpenter Software Disclaimer](https://github.com/MageMCU/Carpenter-Software-Disclaimer/blob/main/README.md)
before use.

1. Article 1000, *Introduction Robotics* (observation and lab notebook).
2. Article 1001, *Joystick Algorithm* (potentiometer voltages and X/Y vector).
3. Article 1002, *Arduino Uno: Pins, Ports, and Peripherals* (ADC and pin map).
4. Article 1009, “The Two Setup Procedures” and “Joystick Setup.”
5. `Code-JUL/src/Step1_Joystick/main.cpp` and `Code-JUL/include/Button.h`.

MIT License. Carpenter Software, Jesse Carpenter.
