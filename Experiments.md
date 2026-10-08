# Experiments

## Draft and safety status

The five Article 1004 experiment projects and their instructions are
**works in progress**. They have **not been physically tested on hardware**.
This is an intentional safety boundary: the motor-control activities must
first receive review against the exact Uno, joystick, L298N breakout,
motors, power supply, wiring, and supervised lab procedure. Build success
only confirms compilation; it does not establish that wiring is safe or that
the physical behavior is correct.

Do not use an unreviewed draft to connect or power a motor driver or motor.
Before any powered activity, have a qualified instructor verify component
ratings, module-specific connections and jumpers, common ground, polarity,
power sequencing, secured wheels, and a safe way to disconnect power. Stop
if a component heats unexpectedly, wiring is uncertain, or behavior differs
from expectations. Follow the exact hardware documentation and applicable
lab safety rules.

All experiments remain drafts until the guides, code, and physical procedure
have been reviewed and the required supervised hardware checks have been
completed and documented. See the [Carpenter Software Disclaimer](https://github.com/MageMCU/MageMCU-Carpenter_Software-Disclaimer/blob/main/README_20260924.md).

## Article 1004 experiment sequence

| Experiment | Focus | Status |
|------------|-------|--------|
| [Experiment 1](Experiments/Experiment-1/Instructions/README.md) | Uno timing, `Timer`, and button behavior | Draft; no physical test claimed |
| [Experiment 2](Experiments/Experiment-2/Instructions/README.md) | Article 1009 Joystick Setup; measure axes and button | Draft; no physical test claimed |
| [Experiment 3](Experiments/Experiment-3/Instructions/README.md) | Optional one-motor L298N familiarization | Draft; not to be powered before review |
| [Experiment 4](Experiments/Experiment-4/Instructions/README.md) | Optional software-only `Bits()` flag familiarization | Draft; no physical test claimed |
| [Experiment 5](Experiments/Experiment-5/Instructions/README.md) | Article 1009 L298N Setup, movement checklist, and measurements | Draft; not to be powered before review |

The formal Article 1009 progression is Experiment 2 (Joystick Setup),
followed by Experiment 5 (L298N Setup). Experiments 3 and 4 are optional
preparation, not replacements for those procedures.

## Black-box inquiry method

Each experiment should investigate a system by relating controlled inputs to
observable outputs before claiming to know its internal behavior:

1. **Define the box:** state which component or subsystem is under study,
   its boundary, and what counts as its input and output.
2. **Predict:** write down the expected response and why before running a
   trial.
3. **Control the test:** change one input at a time and keep other conditions
   fixed where practical.
4. **Observe and record:** capture actual values, units, commands, setup, and
   unexpected results in chronological order.
5. **Infer a model:** explain what internal behavior could account for the
   observations, while separating evidence from assumptions.
6. **Test the explanation:** make a new prediction, run a discriminating
   trial, and record what remains unknown.

Use the [Article 1004 lab notebook template](Experiments/LAB-NOTEBOOK-TEMPLATE.md).
An explanation is a working model supported by recorded evidence, not proof
that every internal detail has been exposed.

## Individual experiment documents

Each experiment's guide and code README identify the black box and observable
inputs/outputs, provide a place to make predictions and record findings, and
link to the same disclaimer:

- [Experiment 1 instructions](Experiments/Experiment-1/Instructions/README.md) /
  [code README](Experiments/Experiment-1/Code/README.md)
- [Experiment 2 instructions](Experiments/Experiment-2/Instructions/README.md) /
  [project README](Experiments/Experiment-2/README.md) /
  [code README](Experiments/Experiment-2/Code/README.md)
- [Experiment 3 instructions](Experiments/Experiment-3/Instructions/README.md) /
  [code README](Experiments/Experiment-3/Code/README.md)
- [Experiment 4 instructions](Experiments/Experiment-4/Instructions/README.md) /
  [code README](Experiments/Experiment-4/Code/README.md)
- [Experiment 5 instructions](Experiments/Experiment-5/Instructions/README.md) /
  [code README](Experiments/Experiment-5/Code/README.md)
