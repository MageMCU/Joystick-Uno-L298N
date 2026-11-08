# Experiment-10: The Bus Monitor

*Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), revised November 7, 2026 (revision 20261107g). Part C of the article gives a one page summary of the Circuit-4 experiments; this file holds the full steps. Labels such as Table 10.1 and Equation 10.1 are local to this file; Table-n, Equation-n, and Circuit-n refer to the article. The article and this file refer to release v7.4.0 of the repository. A later release may differ; compare it with the tag. The notes of earlier releases are in `RELEASES.md`.*

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

**Builds on.** Experiment-5 (the Bits() value); Article 1009, Appendix C, Circuit-4, with Building Circuit-4 complete and both tests of Step6_Circuit passed (Software for Circuit-4).

**Objective.** Verify the voltage divider and the ADC equation of the bus monitor, and find the bus voltages at which Step6_Circuit refuses to connect VS.

**Wiring.** Circuit-4A with the variac supply of Article 1009, Appendix A, Circuit-2, operated by the supervising adult, and Circuit-4B. Measurement points: [Circuit-5](../../Circuits/Circuit-5.svg), the bus monitor with TP1 (the bus), TP2 (A2), and TP3 (the 5 V bus, the reference of the ADC). The motors are disconnected from OUT1 to OUT4.

A voltage divider is two resistors in series whose junction gives a fixed fraction of the voltage across both. The ADC reads A2 against AVCC, the 5 V bus (Article 1009, The ADC reference), so the reference is measured, not assumed. The source impedance seen by A2 is R15 and R16 in parallel, 8.7 kΩ, below the 10 kΩ for which the ADC of the ATmega328P is designed; C12 and that impedance form a low pass filter with a time constant of 8.7 kΩ × 100 nF = 0.87 ms.

**Equation 10.1.** `V(A2) = V(bus) × R16 / (R15 + R16)`<br>
**Equation 10.2.** `count = V(A2) / V(ref) × 1023`<br>
With the nominal values and V(ref) = 5.00 V: count = V(bus) × 26.23.

## Lab 1: The Divider and the Counts

**Code.** Step6_Circuit with `STEP6_CIRCUIT` and `STEP6_LAB`.

**Prediction.** Before Circuit-4B is powered, measure R15 and R16 with the ohmmeter and record them (raw values first). Compute the divider ratio from the measured values, and predict V(A2) and the count for each bus voltage of Table 10.1.

1. The supervising adult sets the variac to zero, turns on S1, and raises the bus to 10 V at TP1. The 7805 needs about 7 V, so U3 starts above it.
2. Record V(ref) at TP3.
3. For each bus voltage of Table 10.1, the supervising adult sets the variac; wait two seconds, then record, in this order: the A2 count printed, V(bus) at TP1, V(A2) at TP2, and the bus printed with in range or OUT OF RANGE.
4. Return the variac to zero and turn off S1.

**Table 10.1.** Bus voltages and the counts expected with the nominal resistors and V(ref) = 5.00 V. Do not raise the bus above 18.5 V.

| V(bus) | 10 V | 12 V | 13.2 V | 14 V | 15 V | 16 V | 17 V | 18 V | 18.5 V |
|---|---|---|---|---|---|---|---|---|---|
| Count | 262 | 315 | 346 | 367 | 393 | 420 | 446 | 472 | 485 |
| STEP6_LAB | out | in | in | in | in | in | in | in | out |

**Expected output and verification.** Each printed count agrees with Equation 10.2, computed from the measured resistors and V(ref), within 2 counts; the counts rise in a straight line with the bus. With the nominal values the counts may differ by several percent, because resistors of 5 percent tolerance can change the ratio by up to about 9 percent; this is why the resistors are measured first. The printed bus agrees with the multimeter within about 0.2 V.

## Lab 2: The Accepted Range

**Code.** As in Lab 1, with SW used.

1. With the bus at 15 V, press SW (ON): DS2 lights and VS reads the bus.
2. The supervising adult lowers the variac slowly. Record the bus at TP1 and the count at which the serial monitor prints "Bus out of range" and DS2 goes dark. Raise the bus to 15 V and press SW again.
3. Repeat while the bus is raised slowly toward 18.5 V, and record where VS goes off.
4. Return the variac to zero and turn off S1.

**Expected output and verification.** VS goes off near 12 V (count 315) and near 18 V (count 472). Because the program averages ten readings taken 100 ms apart, VS goes off up to about one second after the bus leaves the range. Optional: fit a least squares line to the pairs of Lab 1, count against V(bus), with lesson 15 (Experiment-7); its slope is the counts per volt, about 26.2.

**Watch for.** A count that does not change with the bus (H, the wire from the divider to pin 25, open). A count that jumps by tens (C12 missing, or a loose ground at R16).

## Related Articles

- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)

Record every lab in the notebook: [LAB-NOTEBOOK-TEMPLATE.md](../../LAB-NOTEBOOK-TEMPLATE.md).

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
