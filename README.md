# Joystick-Uno-L298N (JUL)

**A differential drive motor control system for the Arduino Uno using joystick input and the L298N dual H bridge motor driver.**

This repository is the companion to the [Carpenter Software STEM Starter Kit article series](https://carpentersoftware.com/pages/projects/robotics/robotics.html). Article 1003, L298N Motor Driver, explains the driver as a component. Article 1004, Experiments for Joystick-Uno-L298N, covers the experiments and the software in this repository, and Article 1009, the Parent, Teacher, and Student Guide, holds the safety rules, the bench, and the two setup procedures. See [Articles](#articles).

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
   - For the drive software open `Code-JUL/`
   - For an experiment open `Experiments/Experiment-N/Code/`
   - **Important:** open the project folder itself, never the repository root
   - Wait for PlatformIO to index the project

5. **Connect the Arduino Uno** by USB. PlatformIO detects the port automatically.

6. **Upload the program** with the Upload button in the PlatformIO toolbar and wait for SUCCESS.

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
├── Code-JUL/                          Drive software (open this folder in VS Code)
│   ├── include/                       Original header files (namespace csjc)
│   │   ├── Button.h, Timer.h, Switch.h
│   │   ├── Joystick.h, L298N.h
│   │   ├── Common.h, Headers.h, Debug.h
│   │   └── numerics/                  Math headers: Bitwise, LinearMap, MiscMath, TypeConv, Vector3,
│   │                                  Vector2, Point2, Point3, Matrix, Matrix2x2/3x3/4x4,
│   │                                  Quaternion, Statistics, RandomNumber, LineFit2, Rotation
│   ├── src/
│   │   ├── Step1_Joystick/            Joystick Setup program (Article 1009, Code-1)
│   │   ├── Step2_JUL/                 Joystick to motors program (Article 1009, Code-2)
│   │   └── Step3_MathLessons/         Math lessons 01 to 19 (Article 1004, Experiments 6 to 9)
│   ├── platformio.ini
│   └── README.md
├── Experiments/
│   ├── Experiment-1/ to Experiment-5/ Core experiments: Code/ (PlatformIO project with copies
│   │                                  of the original headers) and Instructions/README.md
│   ├── Experiment-6/ to Experiment-9/ Advanced experiments: Instructions/README.md (code in Code-JUL)
│   └── LAB-NOTEBOOK-TEMPLATE.md
├── Motor-Movement-Checklist/          Bench validation of the eight octants
├── Experiments.md                     Experiment overview
├── Discrepancies.md                   Review findings and their resolution
├── RELEASES.md                        Version history
├── DISCLAIMER.md
├── LICENSE                            MIT
└── README.md                          This file
```

---

## Hardware Setup

### Wiring Checklist

From Article 1009, Table-2, and Article 1004, Table-1. The joystick axes and the motor directions are matched to the wiring in software (Article 1009, Joystick Setup and L298N Setup), never by moving wires.

| Uno pin | Connection (Article 1009, Circuit-1) | Software name |
|---------|--------------------------------------|---------------|
| A0 | Joystick VRx | yDigital, analogRead(A0) |
| A1 | Joystick VRy | xDigital, analogRead(A1) |
| D2 | Joystick SW, external 10 kΩ resistor | buttonPin |
| D5 | L298N ENB | _EN_A (LeftEN) |
| D6 | L298N IN4 | _LeftIN_A (LeftA) |
| D7 | L298N IN3 | _LeftIN_B (LeftB) |
| D8 | L298N IN2 | _RightIN_A (RightA) |
| D9 | L298N IN1 | _RightIN_B (RightB) |
| D10 | L298N ENA | _EN_B (RightEN) |
| D12 | Indicator LED through 220 Ω to GND (D3 in the advanced wiring of Article 1003, Table-4) | ledPin |

Article 1009, L298N Setup, removes the ENA, ENB, and 5 V regulator jumpers of the L298N. Never connect the motor supply to the Uno 5V pin, never change jumpers while powered, and connect the Uno, the driver logic, and the motor supply negative to a common ground.

**Signal chain**

- Joystick X and Y, ADC (0 to 1023), mapped to the range −1 to 1
- Center offsets applied in `Step2_JUL/main.cpp` (X 0.05, Y 0.06) so a resting stick reads zero
- `Joystick.h` produces left and right motor outputs in the range −1 to 1
- Outputs mapped to −255 to 255; the sign sets the IN pair, the magnitude is the PWM on the enable pin

---

## Active Algorithm

The repository uses the **revised joystick algorithm**:

- **8 direction octant routing**
- **Tolerance based dead zone** inside the algorithm (0.001), in addition to the center offsets above
- **Direction getters** `IsLeftForward()`, `IsRightForward()`, and `Octant()`

The algorithm itself is the subject of Article 1001, Joystick Algorithm.

---

## Experiments

The experiments are written in Article 1004; each `Instructions/README.md` is the text of its experiment in the article. Experiments 1 to 5 use the **original header files**, copied unchanged into each `Experiments/Experiment-N/Code/include/`. Experiments 6 to 9 use `Code-JUL/include/numerics/` and the lessons of `Code-JUL/src/Step3_MathLessons/`. Review the safety conditions in Article 1009 before any motor is powered; build verification is not hardware verification.

| Experiment | Subject | Code | Status |
|-----------|---------|------|--------|
| [Experiment-1](Experiments/Experiment-1/Instructions/README.md) | Timing and Button Input on the Uno: delay(), Timer.h, Button.h, Switch.h | `Experiments/Experiment-1/Code` | Labs 1 to 3 by the author (Lab 3 corrected 20261008); Lab 4 new, simulated |
| [Experiment-2](Experiments/Experiment-2/Instructions/README.md) | Wiring and Reading the Thumb Joystick: preprocessor, LinearMap.h, Joystick Setup | `Experiments/Experiment-2/Code`, `Code-JUL` (Step1_Joystick) | Labs simulated; bench pending |
| [Experiment-3](Experiments/Experiment-3/Instructions/README.md) | L298N Single Motor: MiscMath.h, duty cycle | `Experiments/Experiment-3/Code` | Labs simulated; bench pending |
| [Experiment-4](Experiments/Experiment-4/Instructions/README.md) | L298N Two Motors and the Bits Table: Bitwise.h, TypeConv.h, L298N.h | `Experiments/Experiment-4/Code` | Labs simulated; bench pending |
| [Experiment-5](Experiments/Experiment-5/Instructions/README.md) | Joystick to Motors: Vector3.h, Joystick.h, Motor Movement Checklist | `Experiments/Experiment-5/Code`, `Code-JUL` (Step2_JUL) | Step2_JUL bench tested (bits_1010) |
| [Experiment-6](Experiments/Experiment-6/Instructions/README.md) | Statistics and the Dead Zone | Lessons 01 to 06, 17 | Simulated; bench pending |
| [Experiment-7](Experiments/Experiment-7/Instructions/README.md) | Line Fit and Motor Calibration | Lessons 15, 18 | Simulated; bench pending |
| [Experiment-8](Experiments/Experiment-8/Instructions/README.md) | Vectors, Matrices, and the Joystick Frame | Lessons 07 to 13, 19 | Simulated; bench pending |
| [Experiment-9](Experiments/Experiment-9/Instructions/README.md) | Quaternions (Article 1005) | Lessons 14, 16 | Simulated |

Use the shared [lab notebook template](Experiments/LAB-NOTEBOOK-TEMPLATE.md).

## Articles

Carpenter Software articles, as linked from [carpentersoftware.com, Projects, Robotics](https://carpentersoftware.com/pages/projects/robotics/robotics.html):

| Article | Title |
|---------|-------|
| 1000 | [Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I) |
| 1001 | [Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO) |
| 1002 | [Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE) |
| 1003 | [L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq) |
| 1004 | Experiments for Joystick-Uno-L298N (in progress) |
| 1005 | [Study of Quaternions](https://drive.google.com/file/d/1xQS_DkKx-wXtF7fm8C6GPfF8NV9Qoxnr) |
| 1009 | [Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr) |
| 1009 | [Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4) |
| 1020 | [Note, Button.h and Timer.h](https://drive.google.com/file/d/1mLdqeahOOybPuAjdK8CqOVFJma677UWk) |
| | [Joystick Algorithm Simulation](https://carpentersoftware.com/pages/projects/ytube/joystickAlgoSim.html) |

---

## Testing Platform

| Platform | Version |
|----------|---------|
| **MCU** | ATmega328P (Arduino Uno) |
| **IDE** | PlatformIO |
| **Editor** | Visual Studio Code |
| **Language** | C++ (GNU++11) |
| **Status** | Step1_Joystick and Step2_JUL bench tested (commit f2307a1, unchanged); new labs and lessons built with avr-gcc and run in simulation (simavr), bench tests pending |

---

## Next Steps

1. **First time?** Read [Code-JUL/README.md](Code-JUL/README.md) for the software layout, then follow Experiments 1 to 5 in order (see [Experiments](#experiments)), with Article 1009 on the bench.

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

4. **Motor tuning?** See [Motor-Movement-Checklist/ReadMe.md](Motor-Movement-Checklist/ReadMe.md).

---

## Resources

- **Algorithm simulation:** [YouTube video](https://www.youtube.com/watch?v=maIHbdbDBwo&t=2s)
- **Version history and the relationship to the earlier research repository:** [RELEASES.md](RELEASES.md)
- **Review findings:** [Discrepancies.md](Discrepancies.md)

## Repository Status & History

This is the public software and documentation repository for the Arduino Uno
and L298N joystick project. It continues work from an earlier experimental
repository; the releases document that transition and the project's
milestones. See [RELEASES.md](RELEASES.md) for version history and
[Experiments.md](Experiments.md) for the current experiment and hardware
validation status.

---

## Credits

The files `Code-JUL/include/numerics/LineFit2.h` and `Code-JUL/include/numerics/Rotation.h` are adapted from the Geometric Tools Engine by **David Eberly**, Geometric Tools ([geometrictools.com](https://www.geometrictools.com), [GitHub](https://github.com/davideberly/GeometricTools)), under the Boost Software License, Version 1.0. Each file keeps his copyright notice and states the changes made. See `Code-JUL/src/Step3_MathLessons/README.md`.

## License

MIT License. See [LICENSE](LICENSE) and [DISCLAIMER.md](DISCLAIMER.md). [Carpenter Software](https://carpentersoftware.com), Jesse Carpenter.
