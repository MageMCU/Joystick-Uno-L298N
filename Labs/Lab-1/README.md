## 1003 L298N, Lab 1: I2C Link, Uno to ATmega328P
- STEM Starter Kit Series, Part 4, Electronics Lab, Experiment 1 (standalone test draft)

### Overview
- Lab-1 is a complete, self-contained lab: by the end of it, the Arduino Uno and a bare ATmega328P are
exchanging real I2C messages, with no motor and no joystick hardware involved. It has four parts. Part 1 builds
the ATmega328P's minimum system on the breadboard, the handful of passive parts every bare AVR chip
needs before it can run at all. Part 2 turns the Uno into a temporary ISP programmer and uses it to load
firmware directly onto the bare chip, since that chip has no USB port of its own. Part 3 wires the I2C bus
between the two boards. Part 4 verifies the link, including a deliberate fault test, so the lab proves the link works
rather than just assuming it.
- The firmware is adapted from your own MageMCU repository, Serial-Communication, under Serial
Communication/I2C/Uno-Uno. That project's BusI2C class, message-framing pattern, and I2C addresses (0x14
for master, 0x16 for slave) carry over unchanged. What's different here is the message itself: the original
Uno-Uno demo sends live joystick position data, but this lab's joystick is not wired in until a later experiment.
Lab-1 instead sends a small counter that the slave must correctly receive and answer, which proves the same
underlying mechanics (transmit, receive, request, respond) without needing hardware this lab doesn't have yet.
The full joystick message returns, unchanged in spirit from the original, in the experiment where the joystick is
actually wired.
- This document, and the code and repo layout described in it, is a first draft meant for your own bench testing.
Values, wiring, and code are marked where they are standard defaults rather than something confirmed against
your other sources, so discrepancies you find on the bench can be corrected here before Article 1003 is
drafted.
