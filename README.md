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
│   │   └── claude/                    Files written with Claude (AI assistant): L298NPins.h (Step3),
│   │                                  ace.h (Step4), README.md
│   ├── src/
│   │   ├── Step1_Joystick/            Joystick self test (Article 1009, Joystick Setup, Code-1)
│   │   ├── Step2_JUL/                 Joystick to motors program (Article 1009, Code-2 and Code-3)
│   │   ├── Step3_Generator/           Checks the pins, asks for the Bits() value; prints Step4
│   │   ├── Step4_Generated/           The printed drive program, one header: claude/ace.h
│   │   └── Step5_MathLessons/         main.cpp selects ONE math lesson, L01 to L20, and ONE topic
│   │                                  (Article 1004, Experiments 6 to 9)
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

**Wire once.** Complete every connection of Article 1009, Circuit-1, check each one, and fasten the wiring before Step 1. Step1_Joystick to Step4_Generated all use this one wiring; no step adds, moves, or removes a wire, and every correction after that is made in software. Keep the motor supply off until Article 1009, L298N Setup, applies it.

| Uno pin | Connection (Article 1009, Circuit-1) | Software name |
|---------|--------------------------------------|---------------|
| A0 | Joystick VRx | xDigital, analogRead(A0) (since v3.1.0) |
| A1 | Joystick VRy | yDigital, analogRead(A1) (since v3.1.0) |
| D2 | Joystick SW. Pressed, the push button connects SW to GND. D2 needs a pull up resistor, chosen by the reader (Article 1009, The Thumb Joystick, The Push Button): the **external 10 kOhm pull up from D2 to the Uno 5V pin** (Article 1009, Circuit-1a; line 58 of Step2_JUL as written, which turns the internal pull up off), or the internal pull up (comment marks on line 58 of Step2_JUL and line 688 of Step1_Joystick (line 640 up to v6.3.1)). Step4_Generated supports the external resistor only. The joystick and its pull up take 5 V from the Uno 5V pin, not the 5 V bus. Step1_Joystick checks the push button before the motors get power | buttonPin |
| D5 | L298N ENB | _EN_A (LeftEN) |
| D6 | L298N IN4 | _LeftIN_A (LeftA) |
| D7 | L298N IN3 | _LeftIN_B (LeftB) |
| D8 | L298N IN2 | _RightIN_A (RightA) |
| D9 | L298N IN1 | _RightIN_B (RightB) |
| D10 | L298N ENA | _EN_B (RightEN) |
| D12 | Indicator LED through 220 Ω to GND, as in Article 1009, Circuit-1. Since v4.0.0 Step1_Joystick, Step2_JUL (line 50), and Step3_Generator ship with D12; the advanced wiring of Article 1003, Table-4, uses D3 (line 48 of Step2_JUL) | ledPin |

**Pin names in the code (v6.2.1).** Step2_JUL (lines 66 to 71), Step3_Generator (Check 1), and Step4_Generated name each Uno pin after the L298N input it is wired to in Article 1009, Circuit-1, as in the table above: `ENB = 5`, `IN4 = 6`, `IN3 = 7`, `IN2 = 8`, `IN1 = 9`, `ENA = 10`. Wire by the table and the circuit. Up to v6.2.0 the code gave the same pin numbers the opposite names (`ENA = 5`, `IN1 = 6` to `IN4 = 9`, `ENB = 10`). A bench wired by those old names (D5 to ENA, D6 to IN1, D7 to IN2, D8 to IN3, D9 to IN4, D10 to ENB) still keeps the connection rules, so it works without new wiring: the Motor Movement Checklist finds its `Bits()` value, and that value belongs to that wiring, not to Circuit-1. Record the wiring in the lab notebook. To match the articles, remove all power as Article 1009 directs, rewire to Circuit-1, and run the checklist again.

Article 1009, L298N Setup, removes the ENA, ENB, and 5 V regulator jumpers of the L298N. Never connect the motor supply to the Uno 5V pin, never change jumpers while powered, and connect the Uno, the driver logic, and the motor supply negative to a common ground.

**Signal chain**

- Joystick X and Y, ADC (0 to 1023), mapped to the range −1 to 1
- Center offsets applied in `Step2_JUL/main.cpp` (X 0.05, Y 0.06) so a resting stick reads zero
- `Joystick.h` produces left and right motor outputs in the range −1 to 1
- Outputs mapped to −255 to 255; the sign sets the IN pair, the magnitude is the PWM on the enable pin

---

## Joystick Self Test (v6.2.0)

Step1_Joystick (`Code-JUL/src/Step1_Joystick/main.cpp`) runs with the motor supply off and D5 to D10 held LOW. Open the Serial Monitor at 9600 baud. The first lines name the program (since v6.4.1), `Step1_Joystick: the joystick self test` and `Selected in platformio.ini: +<Step1_Joystick/>`; another name there means `platformio.ini` selects another program. The program first asks for Enter and repeats the question every 3 s, so the first instruction is seen whenever the monitor connects; characters typed ahead are discarded before each question (v6.3.0; up to v6.2.3 the first Enter could end Test 1 before it was read). Each test prints one instruction and waits: follow it, then press Enter. Nothing is timed, so each result can be read before the next test starts (v6.2.0; from v6.0.0 to v6.1.3 each test moved on by itself, or after 20 s, and the button was tested last).

| Test | Instruction | PASS when Enter is pressed |
|---|---|---|
| 1 | Press the push button and hold it; press Enter with the other hand | the button is ON; the LED on D12 is on |
| 2 | Release the push button | the button is OFF; the LED is off (Test 1 passed) |
| 3 | Leave the grip at rest | the rest reading (the center) of A0 and of A1 lies within 100 counts of 511 (25 up to v6.3.1) |
| 4 | Move the grip slowly to every edge, around the full circle, two times | each axis has reached 200 counts below and above its center |
| 5 | Release the grip | each axis is back within 25 counts of its center (Test 4 passed) |

Each test prints its reading and PASS or FAIL below its instruction. A blank line and a dotted line start each new output, each instruction, the report, the live values, and the question, so the newest output is found at a glance (v6.1.0; Step2_JUL, Step3_Generator, Step4_Generated, and lesson 20 do the same). The report lists the low, center, high, and rest readings of A0 and A1 in columns of spaces (v6.3.0; tabs up to v6.2.3 left each value one column left of its heading), PASS or FAIL for each test, and the number of presses seen during Tests 3 to 5; a floating D2 gives presses that no one made, so any press fails the self test (v6.2.1). The notes above `printReport()` in the program name the wire to check for each failure.

After the report the program asks: type r and Enter to run the self test again, or v and Enter to view the live values of A0, A1, and SW four times a second for 20 seconds; then the question is asked again. The output stops at the question, so the report stays in view until the student answers. Keys typed during the live values are discarded.

**The joystick center (v6.4.0).** A thumb joystick seldom rests at exactly 511, the middle of 0 to 1023. Since v6.4.0 the self test measures the rest reading of each axis (Test 3) and, after a pass, prints a complete `Code-JUL/include/JoystickCenter.h` between two marker lines, with the measured center of A0 and A1:

```cpp
#define JOYSTICK_A0_CENTER 523
#define JOYSTICK_A1_CENTER 498
```

Copy every line between the markers and replace the whole file with them; the PlatformIO monitor also saves the output in its log file. The report also shows the centers now in the file, so a rerun shows at once whether the file needs a change. The file ships with 511 and 511, which change nothing. Step3_Generator shows the two centers in its Check 1 and writes them into Step4_Generated as `X_CENTER` and `Y_CENTER`; `ace.h` moves each reading by the offset of its center from 511, held inside 0 to 1023, so a resting grip reads 511 and gives the command 0. Step2_JUL is not changed: it keeps the center 511, so with an off center joystick its motors may turn slowly with the grip released during L298N Setup. That does not change the `Bits()` value, which the checklist finds at full deflection, and the push button OFF stops the motors. In Step4_Generated the dead zones (X_OFFSET 0.05 and Y_OFFSET 0.06, about 25 and 31 counts) then cover only the noise and the return of the spring. Test 3 therefore accepts a center within 100 counts of 511 (25 up to v6.3.1): farther off, one side of the axis keeps less than 412 counts of travel, 80 percent of full speed, and a center near 0 or 1023 is a wiring fault. A center outside 411 to 611 stops the build with an error message. Run the self test again after exchanging the joystick, and copy the new file.

The live values (answer v) print A0 and A1 raw and, in parentheses, their offset from the measured center; at rest both stay near 0. From v6.0.0 to v6.3.1 the report printed the Arduino `map()` calls of the measured low, center, and high readings, and the live values the mapped value; neither was used by Steps 2 to 4, and they are removed. Step5_MathLessons still teaches the two segment map in lesson 3, topic 3, and in lesson 20, `L20_JoystickMap.h`, from the low, center, and high values of the report table (v6.1.0).

**Button modes.** Step1_Joystick calls `setLatching(false)`, the momentary mode: ON only while the button is held, so Test 1 sees the press and Test 2 the release. Step2_JUL calls `setLatching(true)`, the latching mode and the default of `Button.h`: press once for ON, press again for OFF, so the thumb that steers the grip need not hold the button down. Each `setup()` explains its choice.

---

## Setup: One Program, One Bits() Value

Updated 2026-10-17. Step1_Joystick, the joystick setup program, was removed, and the programs were renumbered: Step2_JUL became Step1_JUL, Step3_MathLessons became Step2_MathLessons, Step4_Generator became Step3_Generator, and Step5_Generated became Step4_Generated. Renumbered again 2026-10-18 (v3.1.0), in the order of use: Step3_Generator is now Step2_Generator, Step4_Generated is Step3_Generated, and Step2_MathLessons is Step4_MathLessons.

Up to v2.4.0, Step1_Joystick served Article 1009, Joystick Setup: with the push button ON, it read the two joystick axes so that the student could choose each `analogRead()` equation, plain or reversed (`1023 - analogRead()`), until the stick matched the robot, before the `Bits()` value was found in Step2_JUL. The author's bench test showed that the `Bits()` value alone corrects any joystick orientation, so the joystick setup step and its program were removed.

Renumbered 2026-10-21 (v4.0.0). **Step1_Joystick** returns as a new program with a different purpose: it checks the joystick connections only (x on A0, y on A1, and the push button on D2 with the LED on D12), with the motor supply off and D5 to D10 held LOW. It finds the faults that no `Bits()` value corrects, an open wire, a dead axis, or a floating D2, before the motors get power, and it introduces the Button and Timer classes. It never asks for an axis to be aligned. Since v6.0.0 it is a self test, and since v6.2.0 each test waits for Enter: the serial monitor asks the student to press the push button, release it, leave the grip at rest, move it to every edge, and release it, then reports PASS or FAIL for each test, the measured low, center, and high readings of A0 and A1, and, since v6.4.0, the joystick center file `include/JoystickCenter.h` (the `map()` calls up to v6.3.1; see [Joystick Self Test](#joystick-self-test-v620)). The other programs move up one number: Step1_JUL is now **Step2_JUL**, Step2_Generator is **Step3_Generator**, Step3_Generated is **Step4_Generated**, and Step4_MathLessons is **Step5_MathLessons**. `platformio.ini` ships with Step1_Joystick selected (lines 31 to 37; one folder per line since v6.4.0).

The author's bench test showed that changing the joystick equations is not necessary. With the lines of Step2_JUL left as written, the Motor Movement Checklist finds one `Bits()` value that corrects both the joystick orientation and the L298N wiring. Since v3.1.0 the lines read `xDigital = analogRead(A0)` and `yDigital = analogRead(A1)` (up to v3.0.1, x on A1 and y on A0), and they are not changed: Step3_Generator uses the same two pins. Step2_JUL ships with `bits_0000` on line 103, the first row of the checklist; the student replaces it with the value found:

- Bench run 1, y equation reversed: bits_1011. Bench run 2, no equation changed: bits_1100. 1100 XOR 0111 = 1011. (Both with the lines of v3.0.1; with the lines of v3.1.0 the same bench reads its axes exchanged, and bench run 2 gives bits_1101.)
- Reason: the joystick algorithm satisfies F(-x, y) = (R, L), F(x, -y) = (-R, -L), and F(y, x) = (L, -R). Exchanging or reversing a joystick axis swaps or negates the two motor commands. Bit 2 swaps the commands, and bits 1 and 0 negate the left and right IN pairs, so `Bits()` can undo each change. Bit 3 corrects crossed enable pins only.
- Proof: 8 joystick orientations (A0 and A1 exchanged, x reversed, y reversed) times 16 L298N wirings (enable pins crossed, motors exchanged between channels, left leads reversed, right leads reversed) give 2^7 = 128 benches. A simulation of Step2_JUL with the default lines finds exactly one passing `Bits()` value for each of the 128; each of the 16 values serves 8 benches. The table is below (MMC Proof Table); the script is `Motor-Movement-Checklist/BitsProof.py`, explained in [Motor-Movement-Checklist/ReadMe.md](Motor-Movement-Checklist/ReadMe.md).
- Connection rules: D5 and D10 go to ENA and ENB, either way; D6 and D7 go together to one IN pair and D8 and D9 to the other, each pair in either order; each motor's two leads go to one output pair, either motor on either output, either polarity; ENA and ENB jumpers removed; joystick VRx and VRy on A0 and A1, either way. Of the 720 ways to connect D5 to D10 to the six L298N inputs, only the 16 that keep these rules can be corrected. Details at the end of `Code-JUL/src/Step2_JUL/main.cpp`.
- Limits: a dead axis, a dead L298N channel, or a wire on a wrong Uno pin leaves no passing value. Article 1009, Joystick Setup, runs Step1_Joystick with the motor supply off, which finds the joystick and push button faults before the motors are powered. The octant numbers printed by `DEBUG_STEP2_JOYSTICK` follow the joystick's own frame, so on a rotated joystick they differ from Article 1004, Table-8, while the motors still move correctly.

### MMC Proof Table

The passing `Bits()` value of each of the 128 benches, as printed by `python3 BitsProof.py` (run 20261020, release v3.2.2; the same table as `Motor-Movement-Checklist/ReadMe.md`). Find the bench by its wiring (row) and its joystick orientation (column); the cell is the four binary digits of `bits_nnnn`. The student does not need the table: the checklist finds the value by searching from `bits_0000`. The table shows that the search always ends at exactly one value.

Columns are counted from the shipped lines of Step2_JUL: **normal** = VRx on A0 and VRy on A1, **swap** = VRx and VRy exchanged, **xR** = x reversed, **yR** = y reversed. Rows: **standard** = none of the four changes, the pin order of Step2_JUL (lines 66 to 71); **E** = enable pins crossed, **M** = motors exchanged between the channels, **L** and **R** = left and right motor leads reversed.

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

Step2_JUL ships with both debug switches on (`DEBUG_STEP2_JOYSTICK` and `DEBUG_STEP2_L298N`, lines 21 and 22 of `Code-JUL/src/Step2_JUL/main.cpp`), so L298N Setup and the Motor Movement Checklist (Article 1009) can read the whole signal chain in the Serial Monitor; its motors respond once every 3 s. Pressing the push button OFF stops the motors at once, in every mode (v6.2.3). Once the `Bits()` value is found, there are two ways to drive:

| Path | What to do | Control tick |
|---|---|---|
| A. Stay with Step2_JUL | Comment out lines 21 and 22 of Step2_JUL (`DEBUG_STEP2_JOYSTICK` and `DEBUG_STEP2_L298N`), then upload Step2_JUL again | 100 ms |
| B. Continue to Step 3 | With the motor supply off, run Step3_Generator with the `Bits()` value, copy the printed program into `Step4_Generated/main.cpp`, and upload it (`include/claude/ace.h`, no `Common.h`); apply the motor supply after the upload | 50 ms |

Both paths set the same motor pins for the same joystick readings with the dead zones as shipped (X_OFFSET 0.05 and Y_OFFSET 0.06, lines 132 and 133 of Step2_JUL; `ace.h` keeps these two values, so dead zones changed in Experiment-6 apply to Path A only) and with the shipped joystick center, 511. Since v6.4.0 Path B also corrects an off center joystick: Step4_Generated carries the centers Step3_Generator found in `include/JoystickCenter.h` when it printed the program, while Step2_JUL keeps 511. After a new center is copied into the file, run Step3_Generator again. Article 1009 (revision 20261021d), Two Ways to Drive, gives the Path B procedure step by step. Path B also leaves the serial monitor free: `DEBUG_GENERATED` prints once at startup and may stay on.

---

## Steps 3 and 4: Generated Drive Program

Added 2026-10-17, written with Claude (an AI assistant); build and simulation checked, and bench tested by the author on 2026-10-21 (release v4.0.1). Revised 2026-10-18 (v3.1.0 and v3.2.0) and 2026-10-21 (v4.0.0, renumbered). Article 1009 (revision 20261021d) uses Step1_Joystick for Joystick Setup and Step2_JUL for L298N Setup, and gives Steps 3 and 4 in Two Ways to Drive, Path B.

Since v3.2.0 the two programs divide the work: **Step2_JUL is the diagnostic program**, shipped with both of its debug switches on (lines 21 and 22; up to v5.1.0 the debug flags of `Common.h`), which prints the signal chain and the L298N pin states for L298N Setup and the Motor Movement Checklist (control tick 3000 ms); **Step4_Generated is the drive program** (control tick 50 ms).

1. **Step3_Generator**: with the Uno and USB cable only and the motor supply off, the student works through five items in the serial monitor. Check 1 (v6.4.0) shows the joystick center of `include/JoystickCenter.h`; the student types y when it matches the Step1_Joystick report. Check 2 shows the L298N pins, the push button, and the LED, each as an Uno pin and an ATmega328P port pin, for example `D5 (PD5)`; Check 3 shows the joystick lines, x on A0 (PC0) and y on A1 (PC1). The student types y when they match Step2_JUL. Question 4 takes the four binary digits of the `Bits()` value found with Step2_JUL (line 103). Question 5 decides whether the printed program shows the checked data in the serial monitor when it starts. A summary of all five follows, and the program prints a complete `main.cpp`. Up to v6.3.1 the generator had four items, without the center.
2. **Step4_Generated**: the printed program. It includes one header, `Code-JUL/include/claude/ace.h`, which holds the joystick algorithm, the mapping and dead zone, the push button, the timer, and the L298N pins in one file. With the debug data (Question 5, y), the line `#define DEBUG_GENERATED` makes `setup()` print the data checked in Step3_Generator once at 9600 baud; commenting the line out turns the output off. Without it (n), the program is printed without the debug data. A new run of Step 3 changes only `main.cpp`; `ace.h` is never edited. `DEBUG_GENERATED` does not read the serial monitor and does not change the control tick, so it may stay on while the robot drives. The push button is read active LOW and requires the external 10 kOhm pull up of D2 (the form of line 58 of Step2_JUL as written). Since v3.2.0 the control tick of `ace.h` is 50 ms (`TICK_MS`; Step2_JUL keeps 100 ms without debug flags).

Each program is selected with `build_src_filter` in `Code-JUL/platformio.ini`, which lists the line for each (since v3.0.1; the environments `env:step3` and `env:step4` and their build flags were removed).

For every pair of joystick readings, Step4_Generated sets the same motor pins as Step2_JUL with the shipped centers, 511 and 511 (all 1024 x 1024 pairs on the host; 12519 pairs at the register level in simavr; 13 positions with the button in simavr, 20261019). With other centers (v6.4.0), Step4_Generated gives the commands of Step2_JUL for the readings moved by the centers (all 1024 x 1024 pairs on the host for six pairs of centers, 20261025). The center correction adds about 24 processor cycles, 1.5 µs, per control tick when a center differs from 511, and 46 bytes of flash; with the shipped centers, 511 and 511, the compiled program is unchanged. Performance on the simulated Uno at 16 MHz, bits_1010, measured 20261017; sizes measured 20261019 (v3.2.1) without debug output, Step2_JUL with the three flags commented out and Step4_Generated printed without `DEBUG_GENERATED`:

| | Step2_JUL | Step4_Generated (ace.h) |
|---|---|---|
| Joystick math per tick | 322.5 µs | 16.4 µs (19.6 times faster) |
| Motor output per tick | 40.3 µs | 3.7 µs (10.9 times faster) |
| Full control tick, with the two ADC readings | 574.8 µs | 232.0 µs (2.5 times faster) |
| Flash | 6498 bytes | 1548 bytes |
| RAM | 318 bytes | 23 bytes |

The two ADC conversions (about 106 µs each, ADC clock 125 kHz for full accuracy) are 91 percent of the faster tick. The control tick repeats every 50 ms in Step4_Generated (v3.2.0) and every 100 ms in Step2_JUL without debug flags. Details, the original classes incorporated into `ace.h`, and the tests: [Code-JUL/include/claude/README.md](Code-JUL/include/claude/README.md).

---

## Active Algorithm

The repository uses the **revised joystick algorithm**:

- **8 direction octant routing**
- **Tolerance based dead zone** inside the algorithm (0.001), in addition to the center offsets above
- **Direction getters** `IsLeftForward()`, `IsRightForward()`, and `Octant()`

The algorithm itself is the subject of Article 1001, Joystick Algorithm.

---

## Experiments

The experiments follow Article 1004. The Instructions files for Experiments 1 to 5 are lab cards with project folders, build filters, and bench wiring; Experiments 6 to 9 contain the full advanced steps summarized in the article. Experiments 1 to 5 use copies of the original header files in each `Experiments/Experiment-N/Code/include/`. Experiments 6 to 9 use `Code-JUL/include/numerics/` and the lessons `L01_Bitwise.h` to `L19_JoystickFrame.h` in `Code-JUL/src/Step5_MathLessons/lessons/`; `#define LESSON` in `Code-JUL/src/Step5_MathLessons/main.cpp` selects one lesson, because the Uno cannot hold them all (since v5.0.0), and `#define TOPIC` selects one topic of that lesson, or all topics with 0 (since v5.1.0). Review the safety conditions in Article 1009 before any motor is powered; build verification is not hardware verification.

| Experiment | Subject | Code | Status |
|-----------|---------|------|--------|
| [Experiment-1](Experiments/Experiment-1/Instructions/README.md) | Timing and Button Input on the Uno: delay(), Timer.h, Button.h, Switch.h | `Experiments/Experiment-1/Code` | Labs 1 to 3 by the author (Lab 3 corrected 20261008); Lab 4 new, simulated |
| [Experiment-2](Experiments/Experiment-2/Instructions/README.md) | Wiring and Reading the Thumb Joystick: preprocessor, LinearMap.h; Article 1009, Joystick Setup | `Experiments/Experiment-2/Code`, `Code-JUL` (Step1_Joystick; Step2_JUL, `DEBUG_STEP2_JOYSTICK`) | Labs simulated; bench pending. Step1_Joystick bench tested 20261021 (release v4.0.1); the self test of v6.0.0 and its questions of v6.2.0 are simulated, bench pending |
| [Experiment-3](Experiments/Experiment-3/Instructions/README.md) | L298N Single Motor: MiscMath.h, duty cycle | `Experiments/Experiment-3/Code` | Labs simulated; bench pending |
| [Experiment-4](Experiments/Experiment-4/Instructions/README.md) | L298N Two Motors and the Bits Table: Bitwise.h, TypeConv.h, L298N.h | `Experiments/Experiment-4/Code` | Labs simulated; bench pending |
| [Experiment-5](Experiments/Experiment-5/Instructions/README.md) | Joystick to Motors: Vector3.h, Joystick.h, Motor Movement Checklist | `Experiments/Experiment-5/Code`, `Code-JUL` (Step2_JUL) | Step2_JUL bench tested 20261021 (release v4.0.1, LED on D12); ships with bits_0000, the first row of the checklist |
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
| **Status** | v6.4.1 (2026-10-25). Every step prints its program name and the `build_src_filter` entry that selects it at the top of the serial monitor output; every math lesson topic prints all of its inputs with correct labels (for example lesson 7, topic 13, the scalar 3), and lessons 17 and 20 use `include/JoystickCenter.h`. Requested after the author's bench test of v6.4.0.a (passed); bench test of v6.4.1 pending. v6.4.0 (2026-10-25). Step1_Joystick prints `include/JoystickCenter.h`, the measured rest reading of each joystick axis, and Test 3 accepts a center within 100 counts of 511; Step3_Generator checks it first and writes it into Step4_Generated, whose `ace.h` moves each reading by that center (Step2_JUL unchanged); `build_src_filter` is written one folder per line. Requested after the author's bench test of v6.3.1.a (20261024, passed); v6.4.0.a bench tested by the author on 2026-10-25, passed. v6.3.1 (2026-10-22): Lesson 3, topic 3, prints its table in aligned columns, and lessons 11 and 13 build their rotation and translation matrices from a finished identity matrix; the whole repository was reviewed (v6.3.1). v6.3.0: Step1_Joystick asks for Enter before Test 1 and prints its report and live values in aligned columns; every topic function of Step5_MathLessons has a teaching block (hint, purpose, what is learnt, expected output), and lessons 7 to 10, 13, and 14 demonstrate the getters and setters (v6.3.0). Step2_JUL stops the motors at once when the push button is pressed OFF, and Step4_Generated prints Ready when it starts reading the button (v6.2.3). Step1_Joystick asks for Enter after each test and prints the live values on request (v6.2.0); a press during Tests 3 to 5 fails it, and the pin names of Step2_JUL to Step4_Generated follow Circuit-1 (v6.2.1); `L298N.h` names its two enable pin variables `enPinA` and `enPinB` (v6.2.2). The numerics headers and the lessons carry teaching notes (v6.1.1). Bench tested by the author on 2026-10-21 (release v4.0.1): Step1_Joystick, Step2_JUL, Step3_Generator, and Step4_Generated, with the indicator LED on D12; all passed. The Step1_Joystick self test (v6.0.0, questions since v6.2.0) and the dotted lines and lessons of v6.1.0 are built with avr-gcc and checked in simavr; their bench tests are pending, as is the bench test of Step5_MathLessons. Step2_JUL ships with `bits_0000`, the first row of the Motor Movement Checklist, and its debug switches on (3000 ms control tick). The lessons and the labs of Experiments 1 to 9 are built with avr-gcc and run in simulation (simavr); their bench tests are pending, except where the Experiments table says otherwise. Since v5.0.0 each math lesson is a header in `Step5_MathLessons/lessons/`, selected with `#define LESSON` in `Step5_MathLessons/main.cpp`; since v5.1.0 `#define TOPIC` runs one topic of the lesson. The history of each release is in [RELEASES.md](RELEASES.md) |

---

## Next Steps

1. **First time?** Wire the whole bench once (Article 1009, Circuit-1), run Step1_Joystick, then read [Code-JUL/README.md](Code-JUL/README.md) for the software layout and follow Experiments 1 to 5 in order (see [Experiments](#experiments)), with Article 1009 on the bench.

2. **Joystick API reference**

   | Method | Returns | Purpose |
   |--------|---------|---------|
   | `UpdateInputs(inputX, inputY)` | void | Process joystick X and Y values (minus 1 to plus 1) |
   | `Left()` | float | Left motor output (minus 1 to plus 1) |
   | `Right()` | float | Right motor output (minus 1 to plus 1) |
   | `IsLeftForward()` | bool | True if the left motor output is forward |
   | `IsRightForward()` | bool | True if the right motor output is forward |
   | `Octant()` | int | Current octant (0 = stop, 1 to 8 = directions) |

3. **Debugging.** Since v6.0.0 each debug switch is defined in the program that uses it, above its first `#include`, and is named after its step. Step2_JUL is the diagnostic program and ships with both of its switches on (lines 21 and 22): open the Serial Monitor at 9600 baud to read the joystick values through the signal chain and the L298N pin states.
   ```cpp
   #define DEBUG_STEP2_JOYSTICK // the joystick signal chain
   #define DEBUG_STEP2_L298N    // the L298N inputs and pin states
   ```
   `Code-JUL/include/Common.h` turns them into the flags that `Joystick.h` and `L298N.h` test (`DEBUG_JOYSTICK`, `DEBUG_L298N`). Either switch changes the control tick `BUTTON_TIMER_mS` from 100 ms to 3000 ms so the output is readable, and each tick starts with a blank line and a dotted line (v6.1.0), so the motors of Step2_JUL respond once every 3 s. Drive with Step4_Generated, which does not use `Common.h` (50 ms tick). To drive with Step2_JUL at 100 ms instead, comment out both switches. Step4_Generated has `DEBUG_GENERATED`. Step1_Joystick has no switch: its serial monitor output is always on, and its live values are printed on request after the report (v6.2.0; `DEBUG_STEP1_LIVE` of v6.0.0 to v6.1.3 is removed). A program that defines no switch, such as Step3_Generator and lessons 18 and 19, gets no debug output. Up to v5.1.0 `Common.h` defined `DEBUG_MAIN`, `DEBUG_JOYSTICK`, and `DEBUG_L298N` itself, and those three programs defined `DEBUG_ALL_OFF` to turn them off.

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

The files `Code-JUL/include/numerics/LineFit2.h` (lessons 15 and 18) and `Code-JUL/include/numerics/Rotation.h` (lesson 16) are adapted from the Geometric Tools Engine by **David Eberly**, Geometric Tools ([geometrictools.com](https://www.geometrictools.com), [GitHub](https://github.com/davideberly/GeometricTools)), under the Boost Software License, Version 1.0. Each file keeps his copyright notice and states the changes made. See `Code-JUL/src/Step5_MathLessons/README.md`.

## License

MIT License. See [LICENSE](LICENSE) and [DISCLAIMER.md](DISCLAIMER.md). [Carpenter Software](https://carpentersoftware.com), Jesse Carpenter.

## Contact

Jesse Carpenter, [Carpenter Software](https://carpentersoftware.com): [hello@carpentersoftware.com](mailto:hello@carpentersoftware.com), or the [Contact page](https://carpentersoftware.com/pages/legals/contact/contact.html) of the website.
