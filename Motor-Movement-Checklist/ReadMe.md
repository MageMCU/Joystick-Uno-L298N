# Motor Movement Checklist (MMC)

**Updated for Revised Algorithm — 2026-07-14**

- Previously updated for clarity - 20240814
- **Current Status:** Verified with revised joystick algorithm (octant-based, tolerance dead zone)
- [MMC Reference](https://drive.google.com/file/d/1Cs-94KHmOfRT9C4QJFMCgcuQ93iygg6h)

## MMC Results for JUL

- [Hardware Test Results](https://drive.google.com/file/d/17yNw5FNRORWgtDyey11OeKGRMB9qV0SZ)

## How to Use

The MMC is a step-by-step checklist for validating motor behavior across all 8 joystick octants (directions). Use it alongside the [Step2_JUL](../Code%20-%20Joystick%20Uno%20L298N/src/Step2_JUL/) firmware to verify:

1. Motor response matches joystick input
2. All 8 directional octants work smoothly
3. Forward/backward and left/right movements are correct
4. Dead zone doesn't cause lag or sensitivity issues

**Related Articles:** See article **1009 - L298N Supplemental** for detailed explanation.

## Algorithm Overview

The revised joystick algorithm processes 2-axis input into 8 directional octants:

- **Octant 0:** Stop (dead zone)
- **Octants 1–8:** Forward, forward-right, right, back-right, back, back-left, left, forward-left

With **tolerance-based dead zone (0.001)** and **octant-based motor routing**, movement is smooth and responsive across the entire joystick range.

## Code Snippet

```cpp
// Joystick Algorithm
joystick = Joystick<float>();

// Constructor setup the x-range and the y-range
mapInputFromDigital = LinearMap<float>(0, 1023, -1.0, 1.0);
mapOutFromJoystick = LinearMap<float>(-1.0, 1.0, -255, 255);

// L298N Setup
int8_t ENA = 5;   // Left motor speed
int8_t IN1 = 6;   // Left motor direction 1
int8_t IN2 = 7;   // Left motor direction 2
int8_t IN3 = 8;   // Right motor direction 1
int8_t IN4 = 9;   // Right motor direction 2
int8_t ENB = 10;  // Right motor speed

motors = L298N(ENA, IN1, IN2, IN3, IN4, ENB);
motors.PinsL298N();

// Configure motor bit pattern (16 combinations available)
// bits_1010 = standard forward/reverse mapping
motors.Bits(BitsL298N::bits_1010);
```

## Validation Methods

Use the new API getters to validate motor control:

```cpp
if (joystick.IsLeftForward()) {
    // Left motor is moving forward
}
if (joystick.IsRightForward()) {
    // Right motor is moving forward
}
int currentOctant = joystick.Octant();  // Returns 0-8
```

---
    // Bits:       0000  0001  0010  0011  0100  0101  0110  0111
    // EN B & A ----------------------------------------------
    // Bits-Value:  8     9     10    11    12    13    14    15
    // Bits:       1000  1001  1010  1011  1100  1101  1110  1111
    // -----------------------------------------------------------
    // NOTICE: Changing the BITS is much easier than switching
    // the actual wires around on the L298N module....
    // For my setup, bits 1010 was used...
    motors.Bits(BitsL298N::bits_1010);
    '''
