# Joystick-Uno-L298N (JUL)

**A differential drive motor control system for the Arduino Uno using joystick input and the L298N dual H bridge motor driver.**

This repository is the companion to the [Carpenter Software STEM Starter Kit article series](https://carpentersoftware.com/pages/projects/robotics/robotics.html). Article 1003, L298N Motor Driver, explains the driver as a component. Article 1004, Experiments for Joystick-Uno-L298N, covers the experiments and the software in this repository, and Article 1009, the Parent, Teacher, and Student Guide, holds the safety rules, the bench, and the setup procedure. See [Articles](#articles).

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

5. **Connect the Arduino Uno** by USB.

6. **Set the serial port in `platformio.ini` (required).** The upload does not work with the port left to automatic detection. In the `platformio.ini` of the project folder, remove the comment mark from the `upload_port` line and the `monitor_port` line and change both to the port of your computer, for example `/dev/ttyACM0` (Raspberry Pi OS and Linux; `/dev/ttyUSB0` for a CH340 clone), `/dev/cu.usbmodem14101` (macOS), or `COM3` (Windows). `pio device list` prints the ports. Every project folder needs this once: `Code-JUL/` and each `Experiments/Experiment-N/Code/`.

7. **Upload the program** with the Upload button in the PlatformIO toolbar and wait for SUCCESS.

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
│   │   ├── numerics/                  Math headers: Bitwise, LinearMap, MiscMath, TypeConv, Vector3,
│   │   │                              Vector2, Point2, Point3, Matrix, Matrix2x2/3x3/4x4,
│   │   │                              Quaternion, Statistics, RandomNumber, LineFit2, Rotation
│   │   └── claude/                    Files written with Claude (AI assistant): L298NPins.h (Step2),
│   │                                  ace.h (Step3), README.md
│   ├── src/
│   │   ├── Step1_JUL/                 Joystick to motors program (Article 1009, Code-1 and Code-2)
│   │   ├── Step2_Generator/           Checks the pins, asks for the Bits() value; prints Step3
│   │   ├── Step3_Generated/           The printed drive program, one header: claude/ace.h
│   │   └── Step4_MathLessons/         Math lessons 01 to 19 (Article 1004, Experiments 6 to 9)
│   ├── platformio.ini
│   └── README.md
├── Experiments/
│   ├── Experiment-1/ to Experiment-5/ Core experiments: Code/ (PlatformIO project with copies
│   │                                  of the original headers) and Instructions/README.md (lab card)
│   ├── Experiment-6/ to Experiment-9/ Advanced experiments: Instructions/README.md (code in Code-JUL)
│   ├── Circuits/                      Schematics Circuit-1 to Circuit-4 of Article 1004 (SVG, PNG)
│   └── LAB-NOTEBOOK-TEMPLATE.md
├── Motor-Movement-Checklist/          Bench validation of the eight octants; BitsProof.py (128 benches)
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

From Article 1009, Table-2, and Article 1004, Table-1. The joystick orientation and the motor directions are matched to the wiring in software with one `Bits()` value (Article 1009, L298N Setup), never by moving wires.

| Uno pin | Connection (Article 1009, Circuit-1) | Software name |
|---------|--------------------------------------|---------------|
| A0 | Joystick VRx | xDigital, analogRead(A0) (since v3.1.0) |
| A1 | Joystick VRy | yDigital, analogRead(A1) (since v3.1.0) |
| D2 | Joystick SW, with an **external 10 kOhm pull up resistor from D2 to 5 V (required)**, as in Article 1004, Circuit-2. Either 5 V may be used, the Uno 5V pin or the 5 V bus of the breadboard; the Uno 5V pin is preferred, because the 5 V bus (7805) is off whenever the motor supply is off, and D2 then reads LOW, the pressed level (Article 1009, Wiring). Step1_JUL turns the internal pull up of D2 off (lines 46 and 47, since v3.1.1). The author's bench test (v3.2.0) showed that the thumb joystick module has no resistor on SW: without the external pull up the input floats when the switch is released, and a floating input can turn the motors on. Test the switch as a black box before the motors are connected (Article 1009, Joystick and Button Check, step 4; see the end of `Step1_JUL/main.cpp`) | buttonPin |
| D5 | L298N ENB | _EN_A (LeftEN) |
| D6 | L298N IN4 | _LeftIN_A (LeftA) |
| D7 | L298N IN3 | _LeftIN_B (LeftB) |
| D8 | L298N IN2 | _RightIN_A (RightA) |
| D9 | L298N IN1 | _RightIN_B (RightB) |
| D10 | L298N ENA | _EN_B (RightEN) |
| D12 | Indicator LED through 220 Ω to GND, as in Article 1009, Circuit-1 (Step1_JUL ships with D3 on line 42, the advanced wiring of Article 1003, Table-4; the D12 form is on line 44) | ledPin |

Article 1009, L298N Setup, removes the ENA, ENB, and 5 V regulator jumpers of the L298N. Never connect the motor supply to the Uno 5V pin, never change jumpers while powered, and connect the Uno, the driver logic, and the motor supply negative to a common ground.

**Signal chain**

- Joystick X and Y, ADC (0 to 1023), mapped to the range −1 to 1
- Center offsets applied in `Step1_JUL/main.cpp` (X 0.05, Y 0.06) so a resting stick reads zero
- `Joystick.h` produces left and right motor outputs in the range −1 to 1
- Outputs mapped to −255 to 255; the sign sets the IN pair, the magnitude is the PWM on the enable pin

---

## Setup: One Program, One Bits() Value

Updated 2026-10-17. Step1_Joystick, the joystick setup program, was removed, and the programs were renumbered: Step2_JUL became Step1_JUL, Step3_MathLessons became Step2_MathLessons, Step4_Generator became Step3_Generator, and Step5_Generated became Step4_Generated. Renumbered again 2026-10-18 (v3.1.0), in the order of use: Step3_Generator is now Step2_Generator, Step4_Generated is Step3_Generated, and Step2_MathLessons is Step4_MathLessons.

Step1_Joystick served Article 1009, Joystick Setup: with the push button ON, it read the two joystick axes so that the student could choose each `analogRead()` equation, plain or reversed (`1023 - analogRead()`), until the stick matched the robot, before the `Bits()` value was found in Step2_JUL. The author's bench test showed that the `Bits()` value alone corrects any joystick orientation, so the joystick setup step and its program were removed.

The author's bench test showed that changing the joystick equations is not necessary. With the lines of Step1_JUL left as written, the Motor Movement Checklist finds one `Bits()` value that corrects both the joystick orientation and the L298N wiring. Since v3.1.0 the lines read `xDigital = analogRead(A0)` and `yDigital = analogRead(A1)` (up to v3.0.1, x on A1 and y on A0), and they are not changed: Step2_Generator uses the same two pins. Step1_JUL ships with `bits_0000` on line 92, the first row of the checklist; the student replaces it with the value found:

- Test 1, y equation reversed: bits_1011. Test 2, no equation changed: bits_1100. 1100 XOR 0111 = 1011. (Both with the lines of v3.0.1; with the lines of v3.1.0 the same bench reads its axes exchanged, and Test 2 gives bits_1101.)
- Reason: the joystick algorithm satisfies F(-x, y) = (R, L), F(x, -y) = (-R, -L), and F(y, x) = (L, -R). Exchanging or reversing a joystick axis swaps or negates the two motor commands. Bit 2 swaps the commands, and bits 1 and 0 negate the left and right IN pairs, so `Bits()` can undo each change. Bit 3 corrects crossed enable pins only.
- Proof: 8 joystick orientations (A0 and A1 exchanged, x reversed, y reversed) times 16 L298N wirings (enable pins crossed, motors exchanged between channels, left leads reversed, right leads reversed) give 2^7 = 128 benches. A simulation of Step1_JUL with the default lines finds exactly one passing `Bits()` value for each of the 128; each of the 16 values serves 8 benches. The table is below (MMC Proof Table); the script is `Motor-Movement-Checklist/BitsProof.py`, explained in [Motor-Movement-Checklist/ReadMe.md](Motor-Movement-Checklist/ReadMe.md).
- Connection rules: D5 and D10 go to ENA and ENB, either way; D6 and D7 go together to one IN pair and D8 and D9 to the other, each pair in either order; each motor's two leads go to one output pair, either motor on either output, either polarity; ENA and ENB jumpers removed; joystick VRx and VRy on A0 and A1, either way. Of the 720 ways to connect D5 to D10 to the six L298N inputs, only the 16 that keep these rules can be corrected. Details at the end of `Code-JUL/src/Step1_JUL/main.cpp`.
- Limits: a dead axis, a dead L298N channel, or a wire on a wrong Uno pin leaves no passing value. Article 1009, L298N Setup, opens with a Joystick and Button Check in Step1_JUL (`DEBUG_JOYSTICK`, no motors) that finds the joystick and push button faults before the motors are connected. The octant numbers printed by `DEBUG_JOYSTICK` follow the joystick's own frame, so on a rotated joystick they differ from Article 1004, Table-8, while the motors still move correctly.

### MMC Proof Table

The passing `Bits()` value of each of the 128 benches, as printed by `python3 BitsProof.py` (run 20261020, release v3.2.2; the same table as `Motor-Movement-Checklist/ReadMe.md`). Find the bench by its wiring (row) and its joystick orientation (column); the cell is the four binary digits of `bits_nnnn`. The student does not need the table: the checklist finds the value by searching from `bits_0000`. The table shows that the search always ends at exactly one value.

Columns are counted from the shipped lines of Step1_JUL: **normal** = VRx on A0 and VRy on A1, **swap** = VRx and VRy exchanged, **xR** = x reversed, **yR** = y reversed. Rows: **standard** = none of the four changes, the pin order of Step1_JUL (lines 55 to 60); **E** = enable pins crossed, **M** = motors exchanged between the channels, **L** and **R** = left and right motor leads reversed.

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

Script summary: benches 128, exactly one passing value 128, none 0, more than one 0. Each of the 16 values appears 8 times. The author's bench results are in Article 1009, [MMC Results for JUL](https://drive.google.com/file/d/17yNw5FNRORWgtDyey11OeKGRMB9qV0SZ).

---

## Two Ways to Drive (v3.2.0)

Step1_JUL ships with every debug flag of `Code-JUL/include/Common.h` on, so the Joystick and Button Check and the Motor Movement Checklist (Article 1009, L298N Setup) can read the whole signal chain in the Serial Monitor; its motors respond once every 3 s. Once the `Bits()` value is found, there are two ways to drive:

| Path | What to do | Control tick |
|---|---|---|
| A. Stay with Step1_JUL | In `Common.h`, comment out `DEBUG_MAIN`, `DEBUG_JOYSTICK`, and `DEBUG_L298N`, then upload Step1_JUL again | 100 ms |
| B. Continue to Step 3 | With the motor supply off, run Step2_Generator with the `Bits()` value, copy the printed program into `Step3_Generated/main.cpp`, and upload it (`include/claude/ace.h`, no `Common.h`); apply the motor supply after the upload | 50 ms |

Both paths set the same motor pins for the same joystick readings with the center offsets as shipped (X_OFFSET 0.05 and Y_OFFSET 0.06, lines 121 and 122 of Step1_JUL; `ace.h` keeps these two values and is never edited, so offsets changed in Experiment-6 apply to Path A only). Article 1009 (revision 20261019), Two Ways to Drive, gives the Path B procedure step by step. Path B also leaves the serial monitor free: `DEBUG_GENERATED` prints once at startup and may stay on.

---

## Steps 2 and 3: Generated Drive Program

Added 2026-10-17, written with Claude (an AI assistant); build and simulation checked, bench test pending. Revised 2026-10-18 (v3.1.0 and v3.2.0). Article 1009 (revision 20261019) uses Step1_JUL for the setup procedure and gives Steps 2 and 3 in Two Ways to Drive, Path B.

Since v3.2.0 the two programs divide the work: **Step1_JUL is the diagnostic program**, shipped with every debug flag of `Common.h` on, which prints the signal chain and the L298N pin states for the Joystick and Button Check and the Motor Movement Checklist (control tick 3000 ms); **Step3_Generated is the drive program** (control tick 50 ms).

1. **Step2_Generator**: with the Uno and USB cable only and the motor supply off, the student works through four items in the serial monitor. Check 1 shows the L298N pins, the push button, and the LED, each as an Uno pin and an ATmega328P port pin, for example `D5 (PD5)`; Check 2 shows the joystick lines, x on A0 (PC0) and y on A1 (PC1). The student types y when they match Step1_JUL. Question 3 takes the four binary digits of the `Bits()` value found with Step1_JUL (line 92). Question 4 decides whether the printed program shows the checked data in the serial monitor when it starts. A summary of all four follows, and the program prints a complete `main.cpp`.
2. **Step3_Generated**: the printed program. It includes one header, `Code-JUL/include/claude/ace.h`, which holds the joystick algorithm, the mapping and dead zone, the push button, the timer, and the L298N pins in one file. With the debug data (Question 4, y), the line `#define DEBUG_GENERATED` makes `setup()` print the data checked in Step2_Generator once at 9600 baud; commenting the line out turns the output off. Without it (n), the program is printed without the debug data. A new run of Step 2 changes only `main.cpp`; `ace.h` is never edited. `DEBUG_GENERATED` does not read the serial monitor and does not change the control tick, so it may stay on while the robot drives. The push button is read active LOW and requires the external 10 kOhm pull up of D2 (the form of line 45 of Step1_JUL as written). Since v3.2.0 the control tick of `ace.h` is 50 ms (`TICK_MS`; Step1_JUL keeps 100 ms without debug flags).

Each program is selected with `build_src_filter` in `Code-JUL/platformio.ini`, which lists the line for each (since v3.0.1; the environments `env:step3` and `env:step4` and their build flags were removed).

For every pair of joystick readings, Step3_Generated sets the same motor pins as Step1_JUL (all 1024 x 1024 pairs on the host; 12519 pairs at the register level in simavr; 13 positions with the button in simavr, 20261019). Performance on the simulated Uno at 16 MHz, bits_1010, measured 20261017; sizes measured 20261019 (v3.2.1) without debug output, Step1_JUL with the three flags commented out and Step3_Generated printed without `DEBUG_GENERATED`:

| | Step1_JUL | Step3_Generated (ace.h) |
|---|---|---|
| Joystick math per tick | 322.5 µs | 16.4 µs (19.6 times faster) |
| Motor output per tick | 40.3 µs | 3.7 µs (10.9 times faster) |
| Full control tick, with the two ADC readings | 574.8 µs | 232.0 µs (2.5 times faster) |
| Flash | 6498 bytes | 1548 bytes |
| RAM | 318 bytes | 23 bytes |

The two ADC conversions (about 106 µs each, ADC clock 125 kHz for full accuracy) are 91 percent of the faster tick. The control tick repeats every 50 ms in Step3_Generated (v3.2.0) and every 100 ms in Step1_JUL without debug flags. Details, the original classes incorporated into `ace.h`, and the tests: [Code-JUL/include/claude/README.md](Code-JUL/include/claude/README.md).

---

## Active Algorithm

The repository uses the **revised joystick algorithm**:

- **8 direction octant routing**
- **Tolerance based dead zone** inside the algorithm (0.001), in addition to the center offsets above
- **Direction getters** `IsLeftForward()`, `IsRightForward()`, and `Octant()`

The algorithm itself is the subject of Article 1001, Joystick Algorithm.

---

## Experiments

The experiments follow Article 1004. The Instructions files for Experiments 1 to 5 are lab cards with project folders, build filters, and bench wiring; Experiments 6 to 9 contain the full advanced steps summarized in the article. Experiments 1 to 5 use copies of the original header files in each `Experiments/Experiment-N/Code/include/`. Experiments 6 to 9 use `Code-JUL/include/numerics/` and lessons 01 to 19 in `Code-JUL/src/Step4_MathLessons/`. Review the safety conditions in Article 1009 before any motor is powered; build verification is not hardware verification.

| Experiment | Subject | Code | Status |
|-----------|---------|------|--------|
| [Experiment-1](Experiments/Experiment-1/Instructions/README.md) | Timing and Button Input on the Uno: delay(), Timer.h, Button.h, Switch.h | `Experiments/Experiment-1/Code` | Labs 1 to 3 by the author (Lab 3 corrected 20261008); Lab 4 new, simulated |
| [Experiment-2](Experiments/Experiment-2/Instructions/README.md) | Wiring and Reading the Thumb Joystick: preprocessor, LinearMap.h, Joystick and Button Check | `Experiments/Experiment-2/Code`, `Code-JUL` (Step1_JUL, `DEBUG_JOYSTICK`) | Labs simulated; bench pending |
| [Experiment-3](Experiments/Experiment-3/Instructions/README.md) | L298N Single Motor: MiscMath.h, duty cycle | `Experiments/Experiment-3/Code` | Labs simulated; bench pending |
| [Experiment-4](Experiments/Experiment-4/Instructions/README.md) | L298N Two Motors and the Bits Table: Bitwise.h, TypeConv.h, L298N.h | `Experiments/Experiment-4/Code` | Labs simulated; bench pending |
| [Experiment-5](Experiments/Experiment-5/Instructions/README.md) | Joystick to Motors: Vector3.h, Joystick.h, Motor Movement Checklist | `Experiments/Experiment-5/Code`, `Code-JUL` (Step1_JUL) | Step1_JUL bench tested at commit f2307a1, retest pending (simulation retest passed, v3.2.1); ships with bits_0000, the first row of the checklist |
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
| 1005 | Study of Quaternions, published on [carpentersoftware.com, Projects, Robotics](https://carpentersoftware.com/pages/projects/robotics/robotics.html) |
| 1009 | [Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr) |
| 1009 | [Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4) (Expected Motor Movements and the Motor Movement Checklist, MMC) |
| 1009 | [MMC Results for JUL](https://drive.google.com/file/d/17yNw5FNRORWgtDyey11OeKGRMB9qV0SZ) |
| 1009 | [MMC Results for nRF24L01+](https://drive.google.com/file/d/11rTdUBuKK-MIu4N-AC_g-3Bj84E3aSp4) |
| | [Joystick Algorithm Simulation](https://carpentersoftware.com/pages/projects/ytube/joystickAlgoSim.html) |

---

## Testing Platform

| Platform | Version |
|----------|---------|
| **MCU** | ATmega328P (Arduino Uno) |
| **IDE** | PlatformIO |
| **Editor** | Visual Studio Code |
| **Language** | C++ (GNU++11) |
| **Status** | Step1_JUL (formerly Step2_JUL) bench tested at commit f2307a1. Since v3.0.0 it ships with `bits_0000`, the first row of the Motor Movement Checklist; its other changes are comments, include paths, and the folder name, and it compiles to the same Intel HEX as Step2_JUL of v2.4.0 with line 92 set to `bits_0000`. Since v3.1.0, lines 103 and 104 read x on A0 and y on A1; since v3.1.1, lines 46 and 47 turn the internal pull up of the push button pin off. These are the only changes to its program code; the bench test is to be repeated with them. Since v3.2.0, `Common.h` ships with every debug flag on, so Step1_JUL builds with its debug output and the 3000 ms control tick. New labs and lessons built with avr-gcc and run in simulation (simavr); bench tests pending. Step2_Generator and Step3_Generated (2026-10-17): build and simulation checked; bench pending. v3.2.1 (2026-10-19): documentation, and Step3_Generated sets D5 to D10 LOW before its debug output (printed again by Step2_Generator); all 35 programs build with no warnings, and simulation retest passed (Discrepancies.md, 90); bench retest pending. v3.2.2 (2026-10-20): documentation only (article links, MMC Proof Table, Contact) |

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

3. **Debugging.** Since v3.2.0, `Code-JUL/include/Common.h` ships with **every debug flag on**. Step1_JUL is the diagnostic program: open the Serial Monitor at 9600 baud to read the joystick values through the signal chain and the L298N pin states.
   ```cpp
   #define DEBUG_MAIN        // not used by Step1_JUL (it served Step1_Joystick, removed)
   #define DEBUG_JOYSTICK    // joystick values through the signal chain
   #define DEBUG_L298N       // motor driver pin states
   ```
   Any debug flag changes the control tick `BUTTON_TIMER_mS` from 100 ms to 3000 ms so the output is readable, so the motors of Step1_JUL respond once every 3 s. Drive with Step3_Generated, which does not use `Common.h` (50 ms tick). To drive with Step1_JUL at 100 ms instead, comment out all three flags. Lessons 18 and 19 and Step2_Generator define `DEBUG_ALL_OFF` before their includes and build without the flags.

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

The files `Code-JUL/include/numerics/LineFit2.h` (lessons 15 and 18) and `Code-JUL/include/numerics/Rotation.h` (lesson 16) are adapted from the Geometric Tools Engine by **David Eberly**, Geometric Tools ([geometrictools.com](https://www.geometrictools.com), [GitHub](https://github.com/davideberly/GeometricTools)), under the Boost Software License, Version 1.0. Each file keeps his copyright notice and states the changes made. See `Code-JUL/src/Step4_MathLessons/README.md`.

## License

MIT License. See [LICENSE](LICENSE) and [DISCLAIMER.md](DISCLAIMER.md). [Carpenter Software](https://carpentersoftware.com), Jesse Carpenter.

## Contact

Jesse Carpenter, [Carpenter Software](https://carpentersoftware.com): [hello@carpentersoftware.com](mailto:hello@carpentersoftware.com), or the [Contact page](https://carpentersoftware.com/pages/legals/contact/contact.html) of the website.
