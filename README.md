# Joystick-Uno-L298N (JUL)

**A differential drive motor control system for the Arduino Uno using joystick input and the L298N dual H bridge motor driver.**

This repository is the companion to the Carpenter Software STEM Starter Kit article series. Article 1003, L298N Motor Driver, explains the driver as a component. Article 1004, Joystick Uno L298N, covers the wiring, the firmware in this repository, and the experiments.

---

## Quick Start

### Prerequisites

| Item | Requirement |
|------|-------------|
| **MCU** | Arduino Uno (ATmega328P), genuine board recommended |
| **Editor** | Visual Studio Code |
| **Build Tool** | PlatformIO (VS Code extension) |
| **Joystick** | 2 axis analog thumbstick with push button (SW pin) |
| **Motor Driver** | L298N dual H bridge module |
| **Motors** | 2 DC motors (voltage matching your motor power supply) |

### Installation Steps

1. **Install VS Code** from [code.visualstudio.com](https://code.visualstudio.com)

2. **Install the PlatformIO extension**
   - Open VS Code, then Extensions (Ctrl+Shift+X)
   - Search for "PlatformIO IDE" and click Install

3. **Clone this repository**
   ```bash
   git clone https://github.com/MageMCU/Joystick-Uno-L298N.git
   ```

4. **Open a PlatformIO project folder in VS Code**
   - File, Open Folder
   - For the production firmware open `Code-JUL/`
   - For an experiment open `Experiments/Experiment-N/Code/`
   - **Important:** open the project folder itself, never the repository root
   - Wait for PlatformIO to index the project

5. **Connect the Arduino Uno** by USB. PlatformIO detects the port automatically.

6. **Upload the firmware** with the Upload button in the PlatformIO toolbar and wait for SUCCESS.

### Important Folder Selection Rule

- Each PlatformIO project root is the folder that contains a `platformio.ini` file: `Code-JUL/` and each `Experiments/Experiment-N/Code/`.
- If you open the repository root in VS Code instead, PlatformIO reports path or source filter errors.
- If you see such errors, close VS Code and reopen only the project folder.

---

## What This Repository Does

- **Reads** joystick X and Y analog input (2 axis) and the push button
- **Processes** the input through the octant based differential drive algorithm (Article 1001)
- **Controls** two independent DC motors through the L298N
- **Provides** a button controlled motor enable and a tolerance based dead zone

---

## Project Structure

```
Joystick-Uno-L298N/
├── Code-JUL/                          Production firmware (open this folder in VS Code)
│   ├── include/                       Header files (namespace csjc)
│   │   ├── Joystick.h                 Motor control algorithm (revised)
│   │   ├── L298N.h                    Motor driver interface
│   │   ├── Button.h                   Debounced button with latching or momentary mode
│   │   ├── Timer.h                    Nonblocking interval timer
│   │   ├── LinearMap.h                Range mapping (ADC to unit range to PWM)
│   │   ├── Common.h                   Debug flags and control tick
│   │   └── ...other utilities
│   ├── src/
│   │   ├── Step1_Joystick/            Joystick wiring test (Experiment-2)
│   │   └── Step2_JUL/                 Full firmware (Experiment-5)
│   ├── platformio.ini
│   └── README.md
├── Experiments/
│   ├── Experiment-1/                  Timing and button input on the Uno (complete)
│   │   ├── Code/                      PlatformIO project: 1_Delay, 2_Timer, 3_Button
│   │   └── Instructions/README.md     Reader instructions for the three labs
│   └── Experiment-2/                  Wiring and reading the thumb joystick (under development)
├── Motor-Movement-Checklist/          Bench validation of the eight octants
├── Discrepancies.md                   Review findings and their resolution
├── RELEASES.md                        Version history
├── DISCLAIMER.md
├── LICENSE                            MIT
└── README.md                          This file
```

---

## Hardware Setup

### Wiring Checklist

| Component | Arduino Pin | L298N Pin | Notes |
|-----------|-------------|-----------|-------|
| Joystick X (VRx) | A1 | | Analog input |
| Joystick Y (VRy) | A0 | | Analog input |
| Joystick button (SW) | D2 | | Digital input, INPUT_PULLUP, SW closes to GND |
| Button LED | D3 | | Digital output, LED through 220 ohm to GND |
| L298N ENA | D5 (PWM) | ENA | Motor A speed |
| L298N IN1 | D6 | IN1 | Motor A direction |
| L298N IN2 | D7 | IN2 | Motor A direction |
| L298N IN3 | D8 | IN3 | Motor B direction |
| L298N IN4 | D9 | IN4 | Motor B direction |
| L298N ENB | D10 (PWM) | ENB | Motor B speed |

Remove all three jumpers from the L298N module (ENA, ENB, and the onboard 5 V regulator jumper) and supply 5 V logic power to the module from the bench supply. See Article 1003, Board Connections.

**Axis assignment.** The firmware reads X on A1 and Y on A0. Article 1000 shows the two axes the other way around. This repository is authoritative for the code; confirm your wiring with the serial test in `Step1_Joystick` (see Experiment-2) before trusting either document.

**Signal chain**

- Joystick X and Y, ADC (0 to 1023), mapped to the range minus 1.0 to plus 1.0
- Center offsets applied in `Step2_JUL/main.cpp` (X 0.05, Y 0.06) so a resting stick reads zero
- `Joystick.h` produces left and right motor outputs in the range minus 1.0 to plus 1.0
- Outputs mapped to minus 255 to plus 255; the sign sets IN1/IN2 or IN3/IN4, the magnitude is the PWM on ENA or ENB

---

## Active Algorithm

The repository uses the **revised joystick algorithm**:

- **8 direction octant routing**
- **Tolerance based dead zone** inside the algorithm (0.001), in addition to the center offsets above
- **Direction getters** `IsLeftForward()`, `IsRightForward()`, and `Octant()`

The algorithm itself is the subject of Article 1001, Joystick Algorithm.

---

## Experiments

Each experiment is a self contained PlatformIO project under `Experiments/Experiment-N/Code/` with reader instructions under `Experiments/Experiment-N/Instructions/`. Header files used by an experiment are copied into its own `include/` folder so that no experiment depends on another folder.

| Experiment | Subject | Code | Status |
|-----------|---------|------|--------|
| Experiment-1 | Timing and button input on the Uno: delay(), Timer.h, Button.h | `Experiments/Experiment-1/Code` | Complete |
| Experiment-2 | Wiring and reading the thumb joystick | `Code-JUL/src/Step1_Joystick` | Under development |
| Experiment-3 | L298N, one motor | planned | Planned |
| Experiment-4 | L298N, two motors and the Bits() table | planned | Planned |
| Experiment-5 | Joystick to motors, Motor Movement Checklist | `Code-JUL/src/Step2_JUL` | Planned |

Related articles by Carpenter Software: 1000 Introduction Robotics, 1001 Joystick Algorithm, 1002 Arduino Uno: Pins, Ports, and Peripherals, 1003 L298N Motor Driver, 1004 Joystick Uno L298N (in progress), 1009 L298N Supplemental for teachers and parents.

---

## Testing Platform

| Platform | Version |
|----------|---------|
| **MCU** | ATmega328P (Arduino Uno) |
| **IDE** | PlatformIO |
| **Editor** | Visual Studio Code |
| **Language** | C++ (GNU++11) |
| **Status** | Firmware build and logic reviewed; local hardware bench validation still requires a physical Uno test |

---

## Next Steps

1. **First time?** Read [Code-JUL/README.md](Code-JUL/README.md) for the firmware layout, then start with [Experiments/Experiment-1/Instructions/README.md](Experiments/Experiment-1/Instructions/README.md).

2. **Joystick API reference**

   | Method | Returns | Purpose |
   |--------|---------|---------|
   | `UpdateInputs(inputX, inputY)` | void | Process joystick X and Y values (minus 1 to plus 1) |
   | `Left()` | float | Left motor output (minus 1 to plus 1) |
   | `Right()` | float | Right motor output (minus 1 to plus 1) |
   | `IsLeftForward()` | bool | True if the left motor output is forward |
   | `IsRightForward()` | bool | True if the right motor output is forward |
   | `Octant()` | int | Current octant (0 = stop, 1 to 8 = directions) |

3. **Debugging?** In `Code-JUL/include/Common.h` uncomment one of the debug flags and open the Serial Monitor at 9600 baud:
   ```cpp
   // #define DEBUG_MAIN        // Step1_Joystick output
   // #define DEBUG_JOYSTICK    // joystick values through the signal chain
   // #define DEBUG_L298N       // motor driver pin states
   ```
   Enabling any debug flag also changes the control tick `BUTTON_TIMER_mS` from 100 ms to 3000 ms so the output is readable. Comment the flag out again for normal motor response.

4. **Motor tuning?** See [Motor-Movement-Checklist/README.md](Motor-Movement-Checklist/README.md).

---

## Resources

- **Algorithm simulation:** [YouTube video](https://www.youtube.com/watch?v=maIHbdbDBwo&t=2s)
- **Version history and the relationship to the earlier research repository:** [RELEASES.md](RELEASES.md)
- **Review findings:** [Discrepancies.md](Discrepancies.md)

---

## License

MIT License. See [LICENSE](LICENSE) and [DISCLAIMER.md](DISCLAIMER.md). Carpenter Software, Jesse Carpenter.
