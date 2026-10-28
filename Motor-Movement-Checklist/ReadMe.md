# Motor Movement Checklist (MMC)

**Updated for the revised algorithm, 2026-07-14; octant list and code corrected 2026-10-12**

- Previously updated for clarity, 20240814
- **Current status:** verified with the revised joystick algorithm (octant based control, with both a center offset dead zone and an in algorithm tolerance)
- **Related article:** [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4), which holds both the Expected Motor Movements and the Motor Movement Checklist (MMC); the procedure is Article 1009, L298N Setup, and Article 1004, Experiment-5, Lab 3

## MMC Results

- [1009 MMC Results for JUL](https://drive.google.com/file/d/17yNw5FNRORWgtDyey11OeKGRMB9qV0SZ): hardware test results for this repository
- [1009 MMC Results for nRF24L01+](https://drive.google.com/file/d/11rTdUBuKK-MIu4N-AC_g-3Bj84E3aSp4)

## How to Use

The MMC is a checklist for validating motor behavior at the eight joystick positions. Use it with the [Step2_JUL](../Code-JUL/src/Step2_JUL/) program to verify that:

1. Motor response matches joystick input
2. All eight positions produce the expected movement
3. Forward, backward, left turn, and right turn are correct
4. The dead zone holds the motors at rest without delaying the response

Start with `bits_0000` in the `Bits()` call of Step2_JUL. At the first wrong movement, stop, place the next value, upload, and start the next row. The first value that passes all eight positions is the value for that bench. Change the value, never the wires.

### One Value Corrects Any Bench

Whatever the joystick orientation and the L298N connections, one four digit `Bits()` value corrects the motor movement of a working bench. Leave the two analogRead() lines of Step2_JUL as shipped, `xDigital = analogRead(A0)` and `yDigital = analogRead(A1)`, and let the checklist find the value. Step3_Generator uses the same two pins. (Since v3.1.0; up to v3.0.1 the lines read x on A1 and y on A0.)

The reason is a symmetry of the joystick algorithm: F(−x, y) = (R, L), F(x, −y) = (−R, −L), and F(y, x) = (L, −R). Exchanging or reversing a joystick axis only swaps or negates the two motor commands. Bit 2 swaps the commands, and bits 1 and 0 negate the left and right IN pairs, so the checklist finds a value that undoes the change. Bit 3 corrects crossed enable pins and does not depend on the joystick.

The author's bench test confirms it: with the y equation reversed the checklist found `bits_1011`; with no equation changed it found `bits_1100`; 1100 XOR 0111 = 1011, bits 2, 1, and 0. Both values were found with the lines of v3.0.1 (x on A1, y on A0). With the lines of v3.1.0 the same bench reads its two axes exchanged, the **swap** column of the table below, and the checklist finds `bits_1101` for the unchanged equations.

`BitsProof.py` (written with Claude, 20261017) models Step2_JUL with the shipped lines and searches from `bits_0000` for each of 2^7 = 128 benches: 8 joystick orientations times 16 L298N wirings. Each of the 128 has exactly one passing value, and each of the 16 values serves 8 benches. Run `python3 BitsProof.py` for the table and `python3 BitsProof.py example` for one random bench, step by step.

Columns are counted from the shipped lines: **normal** = VRx on A0 and VRy on A1, **swap** = VRx and VRy exchanged, **xR** = x reversed, **yR** = y reversed. Rows: **standard** = none of the four changes, the pin order of Step2_JUL (the six pin lines); **E** = enable pins crossed, **M** = motors exchanged between the channels, **L** and **R** = left and right motor leads reversed.

| Wiring | normal | yR | xR | xR yR | swap | swap yR | swap xR | swap xR yR |
|---|---|---|---|---|---|---|---|---|
| standard | 1100 | 1011 | 1000 | 1111 | 1101 | 1010 | 1001 | 1110 |
| R | 1101 | 1010 | 1001 | 1110 | 1100 | 1011 | 1000 | 1111 |
| L | 1110 | 1001 | 1010 | 1101 | 1111 | 1000 | 1011 | 1100 |
| L,R | 1111 | 1000 | 1011 | 1100 | 1110 | 1001 | 1010 | 1101 |
| M | 1000 | 1111 | 1100 | 1011 | 1010 | 1101 | 1110 | 1001 |
| M,R | 1010 | 1101 | 1110 | 1001 | 1000 | 1111 | 1100 | 1011 |
| M,L | 1001 | 1110 | 1101 | 1010 | 1011 | 1100 | 1111 | 1000 |
| M,L,R | 1011 | 1100 | 1111 | 1000 | 1001 | 1110 | 1101 | 1010 |
| E | 0100 | 0011 | 0000 | 0111 | 0101 | 0010 | 0001 | 0110 |
| E,R | 0101 | 0010 | 0001 | 0110 | 0100 | 0011 | 0000 | 0111 |
| E,L | 0110 | 0001 | 0010 | 0101 | 0111 | 0000 | 0011 | 0100 |
| E,L,R | 0111 | 0000 | 0011 | 0100 | 0110 | 0001 | 0010 | 0101 |
| E,M | 0000 | 0111 | 0100 | 0011 | 0010 | 0101 | 0110 | 0001 |
| E,M,R | 0010 | 0101 | 0110 | 0001 | 0000 | 0111 | 0100 | 0011 |
| E,M,L | 0001 | 0110 | 0101 | 0010 | 0011 | 0100 | 0111 | 0000 |
| E,M,L,R | 0011 | 0100 | 0111 | 0000 | 0001 | 0110 | 0101 | 0010 |

**Connection rules.** The value corrects every bench that keeps these rules, also listed at the end of `Code-JUL/src/Step2_JUL/main.cpp`:

1. D5 and D10, the two PWM pins, go to ENA and ENB, either way.
2. D6 and D7 go together to one IN pair (IN1 and IN2, or IN3 and IN4), in either order; D8 and D9 go to the other IN pair, in either order.
3. The two leads of each motor go to one output pair (OUT1 and OUT2, or OUT3 and OUT4); either motor may use either output, with either polarity.
4. The ENA and ENB jumpers are removed; power, the 5 V logic supply, and the common ground are wired as in Article 1009, Circuit-1. No value corrects a power or ground fault.
5. The joystick: VRx and VRy on A0 and A1, either way; SW on D2.

`python3 BitsProof.py connections` tries all 720 ways of connecting D5 to D10 to the six L298N inputs: the 16 that keep rules 1 and 2 are corrected for all 8 joystick orientations, and none of the other 704 is corrected for any orientation. To use other Uno pins for the L298N, change the six pin lines of Step2_JUL and the same six pins at the top of Step3_Generator, not the wires (the joystick stays on A0 and A1, the analogRead() lines as written, because Step3_Generator holds the same two pins); the enable pins must be PWM pins (D3, D5, D6, D9, D10, D11), clear of D0 and D1 (serial), D2 (button), and the LED pin.

The value cannot correct a fault outside this table: a dead joystick axis, a dead L298N channel, an open motor lead, or a wire on a wrong Uno pin. If no row of the checklist passes, find the fault with the Step1_Joystick self test (Article 1009, Step1, The Joystick Self Test) and Circuit-1. The octant numbers printed with `DEBUG_STEP2_JOYSTICK` (Step2_JUL) follow the joystick's own frame, so on a rotated joystick they differ from the octant list below while the motors move correctly.

### Review Note

The algorithm and motor mapping in the code are internally consistent with the checklist: the program uses the revised joystick algorithm. Since v3.2.0 Step2_JUL ships with its debug output on (since v6.0.0 the switches `DEBUG_STEP2_JOYSTICK` and `DEBUG_STEP2_L298N`), so it prints the joystick values and the L298N pin states for each checklist position and its control tick is 3000 ms: hold each position for at least 3 s before the motors are judged. Pressing the push button OFF stops the motors at once (v6.2.3). The push button needs a pull up on D2, the external 10 kOhm pull up to 5 V (Article 1004, Circuit-2; Article 1009, Circuit-1a) or the internal pull up (Article 1009, The Thumb Joystick). After the value is found, drive with Step2_JUL with both switches commented out (100 ms tick) or with Step4_Generated (50 ms tick); see Simple Drive and Fast Drive in the repository `README.md`. Any code change should be checked against the current sketch before relying on the results.

## Algorithm Overview

The revised joystick algorithm (Article 1001) divides the input square into eight octants, numbered counterclockwise from the right turn axis:

| Octant | Region (x to the right, y forward) |
|---|---|
| 0 | Stop: both inputs inside the tolerance of 0.001 |
| 1 | Right turn to North-East (x dominant, x and y not negative) |
| 2 | North-East to Forward (y dominant) |
| 3 | Forward to North-West (y dominant) |
| 4 | North-West to Left turn (x dominant) |
| 5 | Left turn to South-West (x dominant) |
| 6 | South-West to Backward (y dominant) |
| 7 | Backward to South-East (y dominant) |
| 8 | South-East to Right turn (x dominant) |

A position on a boundary reports one octant: a tie |x| = |y| goes to the x dominant octant, so North-East reports 1, North-West 4, South-West 5, and South-East 8 (Article 1004, Table-8).

With **center offsets applied before the algorithm** (`X_OFFSET = 0.05`, `Y_OFFSET = 0.06` in Step2_JUL) and an **in algorithm tolerance of 0.001**, the controller treats a resting stick as neutral while still routing movement through the eight octants.

## Code Snippet

Condensed from `Code-JUL/src/Step2_JUL/main.cpp`, `setup()` (the program assigns the pins through six variables, named since v6.2.1 after the L298N input of each pin: `ENB = 5`, `IN4 = 6`, `IN3 = 7`, `IN2 = 8`, `IN1 = 9`, `ENA = 10`). The names are the constructor names of the L298N class, not the silkscreen labels of the module: D5 is wired to L298N ENB and D10 to ENA (Article 1004, Table-1; Article 1009, Table-2). A bench wired by the names of v6.2.0 and earlier (D5 to ENA, D6 to IN1, and so on) keeps the connection rules and needs no new wiring; the checklist finds the value of that wiring. See the repository `README.md`, Wiring Checklist.

```cpp
// Constructor setup the x-range and the y-range
mapInputFromDigital = LinearMap<float>(0, 1023, -1.0, 1.0);
mapOutFromJoystick = LinearMap<float>(-1.0, 1.0, -255, 255);

// L298N Setup: Uno pins D5 to D10 in the class default order
int8_t LeftEN = 5;   // L298N ENB
int8_t LeftA = 6;    // L298N IN4
int8_t LeftB = 7;    // L298N IN3
int8_t RightA = 8;   // L298N IN2
int8_t RightB = 9;   // L298N IN1
int8_t RightEN = 10; // L298N ENA

motors = L298N(LeftEN, LeftA, LeftB, RightA, RightB, RightEN);
motors.PinsL298N();

// Shipped as bits_0000, the first row of the checklist; the value
// found with this checklist replaces it
motors.Bits(BitsL298N::bits_0000);
```

## Validation Methods

The Joystick class reports the direction of each output and the octant:

```cpp
if (joystick.IsLeftForward()) {
    // Left output is positive
}
if (joystick.IsRightForward()) {
    // Right output is positive
}
int currentOctant = joystick.Octant();  // Returns 0 to 8
```

---
