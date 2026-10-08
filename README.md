# Joystick-Uno-L298N (JUL)

**A differential drive motor control system for the Arduino Uno using joystick input and the L298N dual H bridge motor driver.**

This repository is the companion to the [Carpenter Software STEM Starter Kit article series](https://carpentersoftware.com). Article 1003, L298N Motor Driver, explains the driver as a component. Article 1004, Joystick Uno L298N, covers the wiring, the firmware in this repository, and the experiments.

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
│   │   ├── Step1_Joystick/            Production-project joystick diagnostic
│   │   └── Step2_JUL/                 Production joystick-to-motor firmware
│   ├── platformio.ini
│   └── README.md
├── Experiments/
│   ├── Experiment-1/                  Timing and button input on the Uno (complete)
│   │   ├── Code/                      PlatformIO project: 1_Delay, 2_Timer, 3_Button
│   │   └── Instructions/README.md     Reader instructions for the three labs
│   ├── Experiment-2/                  Article 1009 Procedure 1: Joystick Setup
│   ├── Experiment-3/                  Optional one-motor L298N familiarization
│   ├── Experiment-4/                  Optional software-only Bits table familiarization
│   └── Experiment-5/                  Article 1009 Procedure 2: L298N Setup
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

L298N modules differ in their enable and regulator jumper arrangements. Follow the instructions for the exact module and Article 1003, Board Connections; do not assume that all jumpers should be removed or that an external 5 V logic supply is required. Never connect motor-supply voltage to the Uno 5V pin, never change jumpers while powered, and connect the Uno, driver logic, and motor-supply negative to a common ground as required by the module instructions.

**Axis assignment.** The firmware reads X on A1 and Y on A0. Confirm the
actual module's axis/pin orientation with Experiment-2 and record the measured
result; do not rely on a diagram alone.

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

**Safety and draft status:** These experiments are works in progress and
have not been physically tested on hardware. Build verification is not
hardware verification. Review the safety conditions and draft status in
[Experiments.md](Experiments.md) before use; do not power motor hardware from
unreviewed instructions.

See [Experiments.md](Experiments.md) for the complete experiment overview,
the black-box inquiry method, and the shared lab notebook template.

| Experiment | Subject | Code | Status |
|-----------|---------|------|--------|
| Experiment-1 | Timing and button input on the Uno: delay(), Timer.h, Button.h | `Experiments/Experiment-1/Code` | Build-verified; hardware checks remain |
| Experiment-2 | Article 1009 Procedure 1: joystick button and axis verification, no motor driver connected | `Experiments/Experiment-2/Code` | Draft; build-verified, physical joystick checks pending |
| Experiment-3 | Optional one-motor L298N preparation with a zero-before-reverse interlock | `Experiments/Experiment-3/Code` | Draft; build-verified, physical motor test pending |
| Experiment-4 | Optional software-only decoding of the 16 L298N `Bits()` patterns and E/P/L/R flags | `Experiments/Experiment-4/Code` | Draft; build-verified; no motor hardware used |
| Experiment-5 | Article 1009 Procedure 2: full eight-direction `Bits()` checklist and follow-up voltage worksheet | `Experiments/Experiment-5/Code` | Draft; build-verified, physical checks and measurements pending |

The formal sequence is Experiment-2 (**Joystick Setup**) followed by
Experiment-5 (**L298N Setup**). Experiments 3 and 4 are optional preparation,
not substitutes for either procedure. Experiment-5 includes the checklist
and measurement workflow; all physical movement and voltage readings remain
to be completed and documented on the actual bench. These drafts do not claim
to cover every teaching activity in the Article 1009 guide.

### How Articles 1000-1003 support the Article 1004 experiments

| Source article | Concepts carried into this experiment sequence |
|----------------|--------------------------------------------------|
| [Article 1000, *Introduction Robotics*](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I/view) | Treat the system as a measurable black box; make dated, factual notebook entries and preserve setup conditions, readings, and conclusions. This record-keeping practice applies throughout Experiments 1-5. |
| [Article 1001, *Joystick Algorithm*](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO/view) | Interpret the two potentiometer readings as an X/Y vector and follow how normalized inputs are routed into joystick directions. Experiment-2 verifies the actual axes; Experiment-5 uses the algorithm with motors. |
| [Article 1002, *Arduino Uno: Pins, Ports, and Peripherals*](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE/view) | Relate the Uno pin map and I/O functions to the project's digital button/LED, analog joystick, timing, serial diagnostics, and PWM signals. This grounds the pin choices in Experiments 1-5. |
| [Article 1003, *L298N Motor Driver*](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq/view) | Understand the dual H-bridge, direction/enable inputs, PWM, `Bits()` software mapping, voltage loss, and heat. Experiments 3-4 prepare; Experiment-5 carries out the supervised movement and voltage checks. |
| Article 1009 setup guide and [supplemental Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4) | Defines the two formal procedures: joystick-only setup in Experiment-2, then L298N setup/checklist and measurements in Experiment-5. |

These are the relevant prerequisites for Article 1004's joystick-to-L298N
experiments, not a mandate to reproduce every peripheral topic in Articles
1000-1003. However, Article 1002's pin map, GPIO circuits, ADC, and PWM
concepts merit additional practical work; see the extension roadmap below.
Use the shared [Article 1004 lab notebook template](Experiments/LAB-NOTEBOOK-TEMPLATE.md);
builds and serial traces do not substitute for physical measurements.

### Review suggestions for the Article 1004 experiment drafts

The five experiments are a sound **starting point**, not yet classroom-ready
final materials: the sequence moves from Uno timing and inputs to joystick
measurement and motor integration, and clearly separates Article 1009's two
formal setup procedures from optional preparation. Before treating them as
finished labs, apply these improvements:

1. Start each lab with a question and a prediction, then have learners compare
   that prediction with what they actually observed.
2. Use the shared notebook template in every experiment. Record dated setup,
   wiring, code changes, actual readings with units, conclusions, and
   remaining uncertainty; preserve measurements from before and after code
   changes as separate trials.
3. In Experiment-2, take repeated joystick readings at center and each
   direction; distinguish analog axis readings from the separate pushbutton.
   Confirm axis pin and sign from the measured module, not a generic diagram.
4. Keep Experiment-3 and Experiment-4 explicitly optional. Experiment-3's
   powered motor activity needs instructor review and physical safety
   verification; Experiment-4 is a low-risk software-only way to decode the
   `Bits()` flags, not a substitute for observing a motor.
5. In Experiment-5, maintain a separate complete eight-direction record for
   every candidate `Bits()` pattern. Stop at the first all-pass pattern and
   record actual movement, not just octant/PWM serial output. Log voltmeter
   connection points, load state, units, motor/supply, and supervision.
6. Add a short debrief to each experiment: what the observations establish,
   what they do not establish, and what test should follow. Rebuild after
   code edits and record hardware validation separately from compilation.
7. Explain L298N loss and heating using the exact driver's documentation and
   measured conditions. Avoid promising that a module will safely deliver
   the IC's headline limits; breakout layout, heat sinking, motor startup
   current, and supply conditions matter.
8. Consider a later, separate simulation activity to visualize differential
   drive and compare its predictions with the physical robot. Treat that as
   an extension, not evidence that the hardware has been tested.

These suggestions are informed by the [MageMCU GitHub landing page](https://github.com/MageMCU/MageMCU),
which foregrounds hands-on AVR/Uno exploration, differential-drive robotics,
lab notebooks, and simulation as a companion path. They reinforce the
existing article sequence rather than requiring unrelated MCU peripherals or
a new numbered experiment now. The public [Joystick-Uno-L298N repository](https://github.com/MageMCU/Joystick-Uno-L298N)
also presents this project as a companion to the STEM Starter Kit articles.
The [notebook template](Experiments/LAB-NOTEBOOK-TEMPLATE.md) and experiment
guides turn the notebook emphasis into a practical record format.

**Draft assessment:** Yes, these are a good educational starting point. The
core progression and Article 1009 alignment are in place, and there is a
shared notebook template. Remaining gates before calling the labs complete
are instructor/safety review, hardware trials for joystick and motor behavior,
verification of the exact L298N module wiring and measurement procedure, and
updating each guide from those observed results. No physical validation is
claimed yet.

### Article 1002 extension experiment ideas

Article 1002 has enough practical Uno content to support a small follow-on
sequence rather than being used only as a pin-reference citation. Its
pinout/peripheral overview identifies the Uno's general digital pins, PWM
pins, D0/D1 serial functions, analog inputs/ADC, and power/ground connections;
its basic-circuit discussion covers LEDs, buttons, floating inputs, and
pull-up/pull-down wiring. These topics are directly relevant to reading and
building the Article 1004 hardware.

| Candidate | Possible investigation | Relationship to the current five |
|-----------|------------------------|-----------------------------------|
| Uno pins and safe GPIO | Identify the board pins; drive an LED through a current-limiting resistor; compare an input with an internal pull-up to a floating input; record the logic state. | Extend Experiment-1's button/LED lab before connecting the joystick. |
| Analog voltage to ADC | Measure a joystick potentiometer output with a meter at center and extremes; compare the measured voltage with `analogRead()` counts and discuss reference/tolerance. | Optional measured extension to Experiment-2; its first core setup remains aligned to Article 1009. |
| PWM as a digital signal | Use a PWM-capable pin and a protected LED circuit to compare low, medium, and high duty-cycle settings; explain why PWM is not a steady analog output. | Bridge the Uno pin study to the L298N enable/PWM control in Experiments 3 and 5. |
| Pin multiplexing and serial | Map D0/RX and D1/TX; observe how USB Serial uses these pins and why they are not general-purpose I/O while serial is active. | Optional troubleshooting/preparation for the Serial Monitor used throughout. |

Recommended sequence: first add the analog voltage-to-ADC activity to
Experiment-2 as an optional extension (already noted in that guide), then
prototype the GPIO and PWM exercises on the Uno with no motor driver or motor
power connected. Decide whether these deserve new numbered experiments or
expanded Experiment-1 only after checking for duplicate learning objectives
and validating the circuits. Do not turn pin-name coverage into activities
with no measurable question. SPI/I2C and other multiplexed interfaces should
be reserved for a specific Article 1004 use or an explicitly optional
microcontroller-peripherals track; the robot's core joystick/L298N sequence
does not require them.

The [MageMCU profile README](https://github.com/MageMCU/MageMCU) also points
to deeper Uno/ATmega328P internals and a separate robot-simulation path. Those
are worthwhile advanced extensions, but should remain distinct from the
beginner Article 1004 build-up unless the article's audience and prerequisites
are expanded.

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

1. **First time?** Read [Code-JUL/README.md](Code-JUL/README.md) for the firmware layout, then follow [Experiment-1](Experiments/Experiment-1/Instructions/README.md) and [Experiment-2](Experiments/Experiment-2/Instructions/README.md). Complete the optional preparation in Experiments 3-4 only as needed, then follow [Experiment-5](Experiments/Experiment-5/Instructions/README.md) for Article 1009's L298N Setup. Each experiment has its own PlatformIO project and instructions.

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

This is the public firmware and documentation repository for the Arduino Uno
and L298N joystick project. It continues work from an earlier experimental
repository; the releases document that transition and the project's
milestones. See [RELEASES.md](RELEASES.md) for version history and
[Experiments.md](Experiments.md) for the current experiment and hardware
validation status.

---

## License

MIT License. See [LICENSE](LICENSE) and [DISCLAIMER.md](DISCLAIMER.md). [Carpenter Software](https://carpentersoftware.com), Jesse Carpenter.
