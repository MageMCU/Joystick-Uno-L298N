# Experiment-12: The Robot Supply

*Article 1004, Experiments for Joystick-Uno-L298N (STEM Starter Kit Series, Part 5), revised November 7, 2026 (revision 20261107g). Part C of the article gives a one page summary of the Circuit-4 experiments; this file holds the full steps. Labels such as Table 12.1 and Equation 12.1 are local to this file; Table-n, Equation-n, and Circuit-n refer to the article. The article and this file refer to release v7.4.0 of the repository. A later release may differ; compare it with the tag. The notes of earlier releases are in `RELEASES.md`.*

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

**Builds on.** Experiments 10 and 11, repeated here on the battery; Experiment-5 (the Bits() value); Article 1009, Appendix C, Circuit-4, with Building Circuit-4 complete and both tests of Step6_Circuit passed (Software for Circuit-4).

**Objective.** Measure the battery supply of the robot: the drop of the reverse polarity protection, the gate voltages of Q3 and Q1, and the fall of the battery bus when the motors start, against the cutoff of the bus monitor.

**Wiring.** Circuit-4A, the robot supply, and Circuit-4B; the Electronics Lab supply is disconnected from B. BT1 is charged (about 16 V or more) with a balance charger under supervision, on a fireproof surface. Measurement points: [Circuit-7](../../Circuits/Circuit-7.svg), the robot supply with TP8, TP9, TP10, and TP1 (test point (2)); Circuit-6 for Q1.

The cutoff of a lithium polymer battery is the lowest voltage to which it may be discharged without damage: 3.3 V per cell, 13.2 V for BT1. Step6_Circuit with `STEP6_ROBOT` disconnects VS when the one second average of A2 falls to 346 or less (Article 1009, The bus monitor). This experiment does not discharge BT1 to its cutoff.

## Lab 1: The Protection and the Gates

**Code.** Step6_Circuit with `STEP6_CIRCUIT` and `STEP6_ROBOT`; the motors disconnected.

**Prediction.** For the voltage of BT1, predict V(bus), V(GS) of Q3 (D3 holds it at 12 V or less), V(DS) of Q3, and V(GS) of Q1 with SW ON.

1. S3 at OFF. Record V(BT1) at TP8 and V(bus) at TP1.
2. S3 to RUN. Record the A2 count and the bus printed, then V(BT1) at TP8, V(bus) at TP1, V(DS) of Q3 (red lead at TP9, black lead at TP1), and V(GS) of Q3 (red lead at TP10, black lead at TP1).
3. Press SW (ON). Record V(GS) of Q1 (Circuit-6, TP4 to TP1) and V(VS) (Circuit-6, TP5).
4. Press SW (OFF), and turn S3 to OFF.

**Expected output and verification.** At RUN the bus equals V(BT1) within a few hundredths of a volt: Q3 is fully on, and its channel carries the current instead of its body diode, which would drop about 0.6 V. V(GS) of Q3 reads about −12 V, the Zener voltage of D3. V(GS) of Q1 is half the bus, for example −8.2 V at 16.4 V. The printed count is V(bus) × 26.23 for V(ref) = 5.00 V, above 346, so the bus is in range.

## Lab 2: The Battery Under Load

**Code.** Step6_Circuit with `STEP6_MOTORS` and `STEP6_ROBOT`; the drive raised so that both wheels turn freely, the motors connected.

1. S3 at OFF. Connect the motors, then S3 to RUN; upload with S2. Center the grip and press SW (ON).
2. With the grip released, record V(bus) at TP1 and the A2 count.
3. Push the grip fully forward (commands limited to 128). Record V(bus), the A2 count, V(DS) of Q3 (TP9 to TP1), and V(SD) of Q1 (Circuit-6, TP1 to TP5). If the multimeter has a MIN function, record the lowest V(bus) while the grip is pushed from rest to full forward several times.
4. Release the grip, press SW (OFF), and turn S3 to OFF. Charge BT1 when the bus at rest reads 14.4 V (3.6 V per cell) or less.

**Expected output and verification.** The bus falls by a few tenths of a volt while the motors run; the internal resistance of the battery causes the fall. A motor start pulls the bus down briefly, but the one second average of A2 stays above 346, so VS stays connected. V(DS) of Q3 and V(SD) of Q1 are each below 0.1 V. The margin of the average above the cutoff, the count minus 346, tells how far the battery is from 13.2 V, at about 26 counts per volt.

**Watch for.** VS that goes off while driving (the battery near its cutoff: stop and charge it). A battery that is warm or swollen (stop, turn S3 to OFF, and give it to the supervising adult). V(DS) of Q3 near 0.6 V (the body diode carries the current: check R14 and the gate wiring of Q3).

## Related Articles

- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)

Record every lab in the notebook: [LAB-NOTEBOOK-TEMPLATE.md](../../LAB-NOTEBOOK-TEMPLATE.md).

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
