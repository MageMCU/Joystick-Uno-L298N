# Motor Movement Checklist (MMC)

**Updated for the revised algorithm, 2026-07-14; octant list and code corrected 2026-10-12**

- Previously updated for clarity, 20240814
- **Current status:** verified with the revised joystick algorithm (octant based control, with both a center offset dead zone and an in algorithm tolerance)
- [MMC Reference](https://drive.google.com/file/d/1Cs-94KHmOfRT9C4QJFMCgcuQ93iygg6h)
- **Related article:** [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4); the procedure is Article 1009, L298N Setup, and Article 1004, Experiment-5, Lab 3

## MMC Results for JUL

- [Hardware Test Results](https://drive.google.com/file/d/17yNw5FNRORWgtDyey11OeKGRMB9qV0SZ)

## How to Use

The MMC is a checklist for validating motor behavior at the eight joystick positions. Use it with the [Step2_JUL](../Code-JUL/src/Step2_JUL/) program to verify that:

1. Motor response matches joystick input
2. All eight positions produce the expected movement
3. Forward, backward, left turn, and right turn are correct
4. The dead zone holds the motors at rest without delaying the response

Start with `bits_0000` in the `Bits()` call of Step2_JUL. At the first wrong movement, stop, place the next value, upload, and start the next row. The first value that passes all eight positions is the value for that wiring; the author's bench uses `bits_1010`. Change the value, never the wires.

### Review Note

The algorithm and motor mapping in the code are internally consistent with the checklist: the program uses the revised joystick algorithm and the default control tick is 100 ms. Any code change should be checked against the current sketch before relying on the results.

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

From `Code-JUL/src/Step2_JUL/main.cpp`, `setup()`. The names are the constructor names of the L298N class, not the silkscreen labels of the module: D5 is wired to L298N ENB and D10 to ENA (Article 1004, Table-1; Article 1009, Table-2).

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

// The value found with this checklist; the author's bench uses bits_1010
motors.Bits(BitsL298N::bits_1010);
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
