# Article 1004 Experiment Lab Notebook

Use a bound notebook or a dated, sequential record for the Article 1004
experiments. This template is a guide for the entries; preserve original
observations and do not replace them with corrected values after the fact.
If an entry needs correction, add a dated note explaining the change.

**Bench status:** The author bench tested Step1_Joystick, Step2_JUL, Step3_Generator, and Step4_Generated on 20261021 (release v4.0.1), with the indicator LED on D12; all passed. Since v6.0.0 Step1_Joystick is a self test that reports PASS or FAIL, since v6.2.0 each test waits for Enter, and since v6.3.0 the program asks for Enter before Test 1 (bench test pending); Step2_JUL ships with both debug switches on (`DEBUG_STEP2_JOYSTICK` and `DEBUG_STEP2_L298N`, lines 21 and 22, 3000 ms control tick), Step4_Generated ticks every 50 ms, and the upload port must be set in `platformio.ini`. The other labs and the math lessons are build checked and simulated, and their bench tests are pending. Since v5.0.0 a math lesson is selected with `#define LESSON` in `Code-JUL/src/Step5_MathLessons/main.cpp`. Record the release tag of the code used in each entry. This template does not authorize a powered test. Review the [experiment safety notice](../Experiments.md), Article 1009, Safety and Supervision, and the
[Carpenter Software Disclaimer](https://github.com/MageMCU/MageMCU-Carpenter_Software-Disclaimer/blob/main/README_20260924.md).

## Black-box inquiry record

| Inquiry step | Record |
|--------------|--------|
| System boundary: what component/system is the black box? | |
| Inputs changed and inputs held constant | |
| Observable outputs and measurement tools | |
| Prediction and reason, recorded before trial | |
| Evidence observed (values, units, movement, serial output) | |
| Inference: what internal model could explain this evidence? | |
| Next test that could distinguish explanations | |
| What remains unknown? | |

## Entry identification

| Field | Record |
|-------|--------|
| Date and time | |
| Learner(s) / witness | |
| Article and experiment / lab | |
| Uno board / revision | |
| Code version or change made | |
| Hardware identification (joystick, driver, motors, supply) | |
| Ambient / setup conditions, where relevant | |

## Question and prediction

**Question or objective:**

**Prediction:** What do you expect the sketch, indicator, readings, or motor
to do? State the reason for the prediction.

## Setup and safety

**Wiring diagram or pin table:** Include labels, grounds, polarity, and any
module jumpers in their observed positions. Do not rely on memory.

**Tools and measurement ranges:**

**Safety checks completed:** Record the power state during wiring and
measurements, supervision where required, and how motion/power can be stopped.

## Procedure and observations

Record steps and observations in chronological order. Include actual values,
units, commands, code changes, and unexpected results. Keep expected behavior
separate from observed behavior.

| Time / step | Action or command | Expected | Observed (with units) | Notes |
|-------------|------------------|----------|------------------------|-------|
| | | | | |
| | | | | |
| | | | | |

## Results and interpretation

**Results:** Summarize measured or observed evidence; distinguish build
success, serial diagnostics, and physical hardware behavior.

**Calculations:** Show the equation, substituted values, units, and result.

**Conclusion:** Answer the original question using the recorded evidence.
Identify what remains uncertain or untested.

## Follow-up

**Changes for the next trial:**

**Next test / question:**

**Learner initials / witness initials, if required by the class:**

---

## Experiment-specific records

Use the relevant table with the common entry fields above. Add pages for
repeated trials rather than squeezing distinct tests into a single result.
The tables follow Article 1004, Update 20261012 Rev 2, and release v2.4.0.

### Joystick Setup: the Step1_Joystick self test (Article 1009)

Motor supply off. Press Enter at the start question, then copy the report from the serial monitor (v6.2.1: each test waits for Enter; any press during Tests 3 to 5 fails the self test; v6.3.0: the start question repeats every 3 s until Enter, and the report prints in aligned columns).

| Test | Reading at Enter | Pass or fail | Notes |
|------|------------------|--------------|-------|
| 1 Button pressed and held | SW: | | LED on? |
| 2 Button released | SW: | | LED off? |
| 3 Grip at rest (center) | A0: ____ A1: ____ | | |
| 4 To every edge (low, high) | A0: ____ ____ A1: ____ ____ | | |
| 5 Released (rest) | A0: ____ A1: ____ | | |
| Presses during Tests 3 to 5 | ____ (0 expected) | | |

The four `map()` lines of a PASS report, or the wire checked after a FAIL: ________

### Experiment-1: Timing and button input

| Lab | Test | Observation, count, or timing | Explanation |
|-----|------|-------------------------------|-------------|
| 1: `delay()` | First three values of Number of Loops and the time between them | | |
| 2: `Timer` | Number of Loops per one second interval | | |
| 3: `Button` | Indicator LED, onboard LED, and serial output after the first and second press | | |
| 4: `Switch` | Switch closures counted for ten presses, three trials; Lab 3 toggles for ten presses; LED after the constructor correction | | |

### Experiment-2: Wiring and reading the thumb joystick

| Lab | Test | Observation | Explanation |
|-----|------|-------------|-------------|
| 1: Preprocessor | Five printed lines with no flag and with `DEBUG_JOYSTICK`; Flash and RAM figures; first three linker errors of `second.cpp` | | |
| 2: LinearMap | Table-4, three columns beside the prediction; the three Reverse lines | | |

Lab 3, step 1: push button measurement (SW to GND and SW to 5V, released and pressed), resistor fitted (the external 10 kOhm pull up from D2 to 5 V of Circuit-2, required since v3.2.0 for a module with no resistor on SW, as on the author's bench; or a pull down), and the `activeLow` value used.

| Grip position | VRx to GND (V) | VRy to GND (V) | x reading | y reading | Expected N (Equation-2) | Notes |
|---------------|----------------|----------------|-----------|-----------|-------------------------|-------|
| At rest | | | | | | |
| Left | | | | | | |
| Right | | | | | | |
| Forward | | | | | | |
| Backward | | | | | | |

Record which reading follows which axis and whether it approaches 0 or 1023 in each position (the `analogRead()` lines stay as shipped, x on A0 and y on A1; the `Bits()` value corrects the orientation), and the two readings at rest, three times. Supervisor signature.

### Experiment-3: One motor and the duty cycle

Lab 1: every printed `absT()`, `Map()`, and `Debug()` line beside the prediction, and the compiler error of step 3.

Lab 2 (Table-5), one copy for f and one for r. Motor bus VS: ____ V; datasheet drop 1.8 V; meter model: ________

| Key | analogWrite() | D | Vavg predicted | Vavg measured | Shaft turns |
|-----|---------------|---|----------------|---------------|-------------|
| 0 | 0 | 0.00 | | | |
| 1 | 64 | 0.25 | | | |
| 2 | 128 | 0.50 | | | |
| 3 | 191 | 0.75 | | | |
| 4 | 255 | 1.00 | | | |

At key 4: VS to GND under load ____ V; L298N drop (loaded bus minus motor voltage) ____ V. Lowest duty cycle at which the motor starts: ____

### Experiment-4: The Bits table

Lab 1: binary pattern and value after each call, and the value after the `b_powerOfTwo()` correction. Lab 2: high and low bytes of 1023, the mismatch count, and the values printed by the local object.

Lab 3 (Table-7), test command left 255, right −64:

| Digit (bits) | D5 | D6 | D7 | D8 | D9 | D10 | LEDs as observed |
|--------------|----|----|----|----|----|-----|------------------|
| 0 (0000) | | | | | | | |
| 2 (0010) | | | | | | | |
| a (1010) | | | | | | | |
| f (1111) | | | | | | | |

Lab 4: unloaded motor bus voltage ____ V; no motor turns while the button state is OFF (yes or no).

### Experiment-5: Joystick to motors

Lab 1: magnitude, AngleRadian(), Angle2Radian(), and the octant from the angle for the six test points; where the angle octant changes on the live joystick. Lab 2: the Observed column of Table-8 and the Failures line.

Lab 3: one copy of this table for **each** `Bits()` value tried. A value passes only when all eight positions pass; keep the failed rows.

**Configuration:** `bits_____`  **Wiring:** Circuit-1 (D5 to ENB, D6 to IN4, D7 to IN3, D8 to IN2, D9 to IN1, D10 to ENA) or other: ________

| Position (Table-8) | Expected [left, right] | Observed motion | Pass or fail | Notes |
|--------------------|------------------------|-----------------|--------------|-------|
| Right Turn | [1, −1] | | | |
| North-East | [1, 0] | | | |
| Forward | [1, 1] | | | |
| North-West | [0, 1] | | | |
| Left Turn | [−1, 1] | | | |
| South-West | [−1, 0] | | | |
| Backward | [−1, −1] | | | |
| South-East | [0, −1] | | | |

**First value passing all eight positions:** `bits_____`

**Drive path after the checklist (Article 1009, Two Ways to Drive):** A, Step2_JUL with both debug switches commented out, or B, Step4_Generated printed by Step3_Generator (answers to Checks 1 and 2 and Questions 3 and 4: ______). Supervisor signature.

| Voltage check | Meter points and load state | Reading | Units | Supply, motor, conditions |
|---------------|-----------------------------|---------|-------|---------------------------|
| Unloaded motor bus | | | | |
| Loaded motor bus | | | | |
| Motor terminals | | | | |
| L298N drop (loaded bus minus motor terminals) | | | | |

Final dead zone: X_OFFSET ____ , Y_OFFSET ____ ; inputs printed at rest. Supervisor signature after step 5.

### Experiments 6 to 9

Use the common entry fields and the record named in each step of `Experiments/Experiment-n/Instructions/README.md`: the suggested offsets of lesson 17 (Experiment-6), the five counts and the fit of lesson 18 (Experiment-7), the octants at each mounting angle of lesson 19 (Experiment-8), and the T8 plot and T5 values (Experiment-9).

Record who supervised powered testing and any supply or motor changes
requiring repeated measurements.
