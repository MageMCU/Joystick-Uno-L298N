# Article 1004 Experiment Lab Notebook

Use a bound notebook or a dated, sequential record for the Article 1004
experiments. This template is a guide for the entries; preserve original
observations and do not replace them with corrected values after the fact.
If an entry needs correction, add a dated note explaining the change.

**Work in progress:** the experiment instructions and hardware have not been
physically tested. This template does not authorize a powered test. Review
the [experiment safety notice](../Experiments.md) and the
[Carpenter Software Disclaimer](https://github.com/MageMCU/Carpenter-Software-Disclaimer/blob/main/README.md).

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

### Experiment 1: Timing and button input

| Lab | Test | Observation / count / timing | Explanation |
|-----|------|------------------------------|-------------|
| 1: `delay()` | Loop count and LED state across several cycles | | |
| 2: `Timer` | Loop count during each timed interval | | |
| 3: `Button` | Press/release, LED, debounce, and motor-safe state behavior | | |

### Experiment 2: Joystick setup

| Stick position | Trial 1 X (ADC) | Trial 1 Y (ADC) | Trial 2 X (ADC) | Trial 2 Y (ADC) | Notes |
|----------------|-----------------|-----------------|-----------------|-----------------|-------|
| Center | | | | | |
| Left | | | | | |
| Right | | | | | |
| Forward | | | | | |
| Backward | | | | | |

Record whether axes were exchanged or inverted in software, the final
convention, and button press/release behavior. Keep readings before and after
any code change as separate dated trials. For the optional Article 1002 ADC
extension, add a row recording joystick output voltage (VRx/VRy to GND),
meter range, ADC count, and stick position.

### Experiment 3: One-motor familiarization

| Command | Enable held? | Requested direction / PWM | Observed motion | Start / stop result | Notes, supply, temperature |
|---------|--------------|---------------------------|-----------------|---------------------|----------------------------|
| `w` | | | | | |
| `x` | | | | | |
| `s` | | | | | |
| Release D2 | | | | | |

Record the driver/motor identifiers and supply settings; do not infer safety
or suitability from a successful short test.

### Experiment 4: Bits table familiarization

| Input | `bits_XXXX` reported | E/P/L/R reported | Explanation of changed flags |
|-------|----------------------|------------------|------------------------------|
| `0` through `f` | | | |

This is a software decoding exercise only. Do not connect or energize motor
hardware for this record.

### Experiment 5: L298N setup

Create one copy of this table for **each** configuration tested. A candidate
pattern passes only when the complete eight-position checklist passes.

**Configuration:** `bits_____`  **E/P/L/R:** ____ / ____ / ____ / ____

| Stick position | Expected motion | Observed motion | Pass / fail | Notes |
|----------------|-----------------|-----------------|-------------|-------|
| Forward | | | | |
| Forward-right | | | | |
| Right | | | | |
| Reverse-right | | | | |
| Reverse | | | | |
| Reverse-left | | | | |
| Left | | | | |
| Forward-left | | | | |

**First configuration passing all eight positions:** `bits_____`

| Voltage check | Meter points / load state | Reading | Units | Supply / motor / conditions |
|---------------|---------------------------|---------|-------|-----------------------------|
| Unloaded supply bus | | | | |
| Loaded supply bus | | | | |
| Motor terminals | | | | |
| Calculated driver drop (loaded bus - motor terminals) | | | | |

Record who supervised powered testing and any supply or motor changes
requiring repeated measurements.
