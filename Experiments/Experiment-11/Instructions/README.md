# Experiment-11: The Motor Power Switch

*Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), revised November 7, 2026 (revision 20261107g). Part C of the article gives a one page summary of the Circuit-4 experiments; this file holds the full steps. Labels such as Table 11.1 and Equation 11.1 are local to this file; Table-n, Equation-n, and Circuit-n refer to the article. The article and this file refer to release v7.4.0 of the repository. A later release may differ; compare it with the tag. The notes of earlier releases are in `RELEASES.md`.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision, and Appendix C. A supervising adult builds Circuit-4, operates its power switch, and checks every measurement point before the meter leads are placed. Keep fingers clear of the wheels; the meter leads are placed and removed with the power switch off whenever a step allows it.

**Running Step6_Circuit.** Open `Code-JUL/` and select Step6_Circuit in `platformio.ini`:

```
build_src_filter =
    +<*>
    -<Step1_Joystick/>
    -<Step2_JUL/>
    -<Step3_Generator/>
    -<Step4_Generated/>
    -<Step5_MathLessons/>
    +<Step6_Circuit/>
```

In `Code-JUL/src/Step6_Circuit/main.cpp` define one test switch, `STEP6_CIRCUIT` or `STEP6_MOTORS`, and one supply switch, `STEP6_LAB` or `STEP6_ROBOT`, as each lab directs, and copy the value of the Bits() line of Step2_JUL into the Bits() line of Step6. Upload through P2, the Uno programmer, and press S2 as the upload starts. Once each second the serial monitor prints the A2 count of the bus monitor (an average of ten readings), A0 and A1, then the bus in volts, x and y, and the state of SW.

**Builds on.** Experiment-10 (the bus monitor, which decides with SW when VS is connected); Experiment-5 (the Bits() value); Article 1009, Appendix C, Circuit-4, with Building Circuit-4 complete and both tests of Step6_Circuit passed (Software for Circuit-4).

**Objective.** Measure how D4, through Q2, turns Q1 on and connects the motor bus to VS, and confirm that Q1 is fully on.

**Wiring.** Circuit-4A, the Electronics Lab supply (fixed or variac), and Circuit-4B. Measurement points: [Circuit-6](../../Circuits/Circuit-6.svg), the motor power switch with test points TP1 to TP7.

A saturated transistor is one that conducts fully: its collector sits a few tenths of a volt or less above its emitter. Q2 is driven far into saturation: its base current is several times larger than its collector current divided by its current gain. Q1, a P channel MOSFET, conducts when its gate is several volts below its source; R1 and R2 set that voltage to half the bus.

**Equation 11.1.** `IB = (V(D4) − V(BE)) / R3 − V(BE) / R4`<br>
Base current of Q2, from the measured V(D4) and V(BE) (TP7 to the emitter, or the base to GND).

**Equation 11.2.** `IC = (V(bus) − V(CE)) / (R1 + R2)`,  `V(GS) = −(V(bus) − V(CE)) / 2`<br>
Collector current of Q2 and the gate to source voltage of Q1.

## Lab 1: The Switch at Rest and Switched On

**Code.** Step6_Circuit with `STEP6_CIRCUIT` and `STEP6_LAB`. The motors are disconnected from OUT1 to OUT4.

**Prediction.** For the bus of your supply (15.6 V unloaded on the fixed supply), predict V(D4), V(CE), V(GS), and V(VS) with SW OFF and with SW ON, and IB and IC with SW ON.

1. With the power switch off, place the black lead on GND. Turn on S1. Wait for the first A2 count (about one second). Record the A2 count and the bus printed, then V(bus) at TP1.
2. SW OFF. Record V(D4) at TP7, V(CE) at TP6, V(VS) at TP5, and V(GS), red lead at TP4 and black lead at TP1.
3. Press SW once (ON). DS3 and DS2 light. Repeat the four readings of step 2, and measure V(BE), red lead at the base of Q2, black lead at GND.
4. Calculate IB and IC with Equations 10.1 and 10.2, and their ratio.
5. Press SW again (OFF) and time how long DS2 takes to go dark. C11, 470 µF, discharges through R6, 4.7 kΩ, and the module: the time constant of R6 and C11 alone is 4.7 kΩ × 470 µF = 2.2 s.

**Table 11.1.** Expected readings on the fixed supply, 15.6 V bus, Vref 5 V.

| Reading | SW OFF | SW ON |
|---|---|---|
| V(D4), TP7 | 0 V | about 4.9 V |
| V(CE), TP6 | 15.6 V (no current through R1 and R2) | below 0.2 V |
| V(GS), TP4 to TP1 | 0 V | about −7.8 V |
| V(VS), TP5 | 0 V | 15.6 V |
| IB, IC | 0 | about 4.1 mA, about 0.78 mA |

**Expected output and verification.** With SW OFF, R4 holds Q2 off and R1 holds the gate at the source, so V(GS) is 0 V and VS is 0 V. With SW ON, IB is about five times IC, so Q2 is saturated and V(GS) is half the bus, beyond the 2 V to 4 V threshold of the IRF4905 and within its 20 V limit (Article 1009, The gate of Q1).

## Lab 2: Q1 Under Load

**Code.** Step6_Circuit with `STEP6_MOTORS` and `STEP6_LAB`; the drive raised so that both wheels turn freely, the motors connected.

1. Turn off S1, connect the motors, turn on S1, and upload. Center the grip and press SW (ON).
2. Push the grip fully forward. The commands are limited to 128 (`STEP6_PWM_LIMIT`). Record V(bus) at TP1, V(VS) at TP5, and V(SD), red lead at TP1 and black lead at TP5.
3. Release the grip, press SW (OFF), and turn off S1.

**Expected output and verification.** V(SD) is below 0.1 V: Q1 is fully on, and its on resistance, about 0.02 Ω, drops 0.02 V at 1 A. A higher V(SD) means the gate is not driven far enough; check R2 and Q2 (Article 1009, The gate of Q1).

**Watch for.** DS2 that never lights (the bus monitor out of range: read the A2 count; or D4 to R3 open). A meter lead that slips between TP1 and TP5 while the motors run; place the leads with S1 off.

## Related Articles

- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)

Record every lab in the notebook: [LAB-NOTEBOOK-TEMPLATE.md](../../LAB-NOTEBOOK-TEMPLATE.md).

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
