# Joystick-Uno-L298N (JUL)

**A differential drive motor control system for the Arduino Uno, with a thumb joystick for input and the L298N dual H bridge motor driver.**

This repository is the companion to the [Carpenter Software STEM Starter Kit article series](https://carpentersoftware.com/pages/projects/robotics/robotics.html). Article 1003 explains the L298N as a component, Article 1004 covers the experiments and the software of this repository, and Article 1009, the Parent, Teacher, and Student Guide, holds the safety rules, the bench, and the setup procedure. See [Articles](#articles).

This is the maintained code. It continues the first version of the code and the study of the joystick algorithm, kept in the repository [JUL-Study](https://github.com/MageMCU/JUL-Study).

Follow Article 1009, Safety and Supervision, before any motor is powered. A successful build confirms the code only; it does not confirm that the wiring is safe.

---

## Quick Start

| Item | Requirement |
|------|-------------|
| MCU | Arduino Uno (ATmega328P) |
| Editor and build tool | Visual Studio Code with the PlatformIO IDE extension |
| Joystick | 2 axis analog thumb joystick with push button (SW) |
| Motor driver | L298N dual H bridge module |
| Motors | 2 DC motors rated for the motor supply |

1. Install VS Code and the PlatformIO IDE extension.
2. Clone the repository: `git clone https://github.com/MageMCU/Joystick-Uno-L298N.git`
3. Open a **project folder**, never the repository root: `Code-JUL/` for the drive software, or `Experiments/Experiment-N/Code/` for an experiment. A project folder is the folder that holds a `platformio.ini`; opening the root gives path and source filter errors.
4. Connect the Uno by USB.
5. **Set the serial port (required).** In the `platformio.ini` of the project folder, remove the comment marks from `upload_port` and `monitor_port` and set both to the port of your computer, for example `/dev/ttyACM0` (Linux and Raspberry Pi OS), `/dev/cu.usbmodem14101` (macOS), or `COM3` (Windows). `pio device list` prints the ports.
6. Upload with the Upload button of the PlatformIO toolbar and wait for SUCCESS.

---

## Project Structure

```
Joystick-Uno-L298N/
├── Code-JUL/                   Drive software (open this folder in VS Code)
│   ├── include/                Header files (namespace csjc)
│   │   ├── numerics/           Math headers used by the lessons
│   │   └── claude/             Files written with Claude (Step3 and Step4)
│   ├── src/                    Step1_Joystick to Step6_Circuit (see Programs)
│   └── README.md               Selecting a program, headers, debugging
├── Experiments/                Experiment-1 to Experiment-12, Circuits,
│                               LAB-NOTEBOOK-TEMPLATE.md
├── Motor-Movement-Checklist/   Finding the Bits() value; BitsProof.py
├── Experiments.md              Experiment overview
├── Discrepancies.md            Open review items
├── RELEASES.md                 Release notes
├── DISCLAIMER.md, LICENSE
└── README.md
```

---

## Hardware

Wire the whole bench once, as Article 1009, Circuit-1, shows, and check every connection before Step1. No step adds, moves, or removes a wire; the joystick orientation and the motor directions are matched in software with one `Bits()` value.

| Uno pin | Connection (Article 1009, Circuit-1) | Name in the code |
|---------|--------------------------------------|------------------|
| A0 | Joystick VRx | xDigital |
| A1 | Joystick VRy | yDigital |
| D2 | Joystick SW, with a 10 kOhm pull up resistor from D2 to the 5 V bus (Article 1009, Circuit-1a); pressed, SW connects D2 to GND | buttonPin |
| D5 | L298N ENB | `ENB` |
| D6 | L298N IN4 | `IN4` |
| D7 | L298N IN3 | `IN3` |
| D8 | L298N IN2 | `IN2` |
| D9 | L298N IN1 | `IN1` |
| D10 | L298N ENA | `ENA` |
| D12 | Indicator LED through 1 kOhm to GND | ledPin |

Remove the ENA, ENB, and 5 V regulator jumpers of the L298N (Article 1009, L298N Setup). Never connect the motor supply to the Uno 5V pin, never change a jumper while powered, and connect the Uno, the driver logic, and the motor supply negative to one common ground. Circuit-4 (Article 1009, Appendix C) is the complete robot wiring and is used with Step6_Circuit only.

---

## Programs

Each program is selected with `build_src_filter` in `Code-JUL/platformio.ini`; details are in [Code-JUL/README.md](Code-JUL/README.md).

| Program | Purpose | Article 1009 |
|---------|---------|--------------|
| Step1_Joystick | Joystick self test, motor supply off: the push button, the center, both ends of each axis; prints `include/JoystickMeasurements.h` | Step1 |
| Step2_JUL | Joystick to motors; ships with its two debug switches on for L298N Setup and the Motor Movement Checklist. With both switches off it is Simple Drive (100 ms tick) | Step2, L298N Setup |
| Step3_Generator | Checks the measurements and pins, asks for the `Bits()` value, prints Step4_Generated | Step3 |
| Step4_Generated | Fast Drive (optional, advanced): the printed drive program, one header `claude/ace.h` (45 ms tick) | Step4 |
| Step5_MathLessons | One math lesson, L01 to L20, and one topic at a time | Article 1004, Experiments 6 to 9 |
| Step6_Circuit | The test of Circuit-4A and Circuit-4B | Appendix C |

**Signal chain.** The joystick readings (0 to 1023) are corrected with the six values of `JoystickMeasurements.h`, mapped to the range minus 1 to 1, and passed through a dead zone; `Joystick.h` turns them into left and right commands of minus 1 to 1, which are mapped to minus 255 to 255. The sign sets the IN pair and the size sets the PWM on the enable pin.

**One `Bits()` value.** Step2_JUL ships with `bits_1101` and `platformio.ini` selects Step5_MathLessons. These are the settings of the author's bench test, kept with its serial monitor logs in `Code-JUL/logs/`. A new bench starts at `bits_0000`, the first row of the Motor Movement Checklist, and selects Step1_Joystick first. The [Motor Movement Checklist](Motor-Movement-Checklist/ReadMe.md) finds the one value of the 16 that corrects both the joystick orientation and the L298N wiring of a bench; `BitsProof.py` shows that every bench that keeps the connection rules has exactly one.

---

## Joystick Algorithm

`Code-JUL/include/Joystick.h` divides the joystick input into nine regions, a center stop zone and eight octants, chosen by the dominant axis and the quadrant. It has a tolerance based dead zone (0.001) and the getters `Left()`, `Right()`, `IsLeftForward()`, `IsRightForward()`, and `Octant()` (0 is stop, 1 to 8 are directions). The algorithm is the subject of Article 1001; the study that led to it is the repository [JUL-Study](https://github.com/MageMCU/JUL-Study).

---

## Experiments

The experiments follow Article 1004, from easy to difficult; [Experiments.md](Experiments.md) lists them with their code. Experiments 1 to 5 are PlatformIO projects with copies of the original headers; Experiments 6 to 9 use the lessons of Step5_MathLessons; Experiments 10 to 12 use Step6_Circuit and Circuit-4. Record each lab in the [lab notebook template](Experiments/LAB-NOTEBOOK-TEMPLATE.md).

---

## Articles

The articles are linked from [carpentersoftware.com, Projects, Robotics](https://carpentersoftware.com/pages/projects/robotics/robotics.html). An asterisk marks the articles written for this repository.

| Article | Title |
|---------|-------|
| *1000 | [Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I) |
| *1001 | [Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO) |
| *1002 | [Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE) |
| *1003 | [L298N Motor Driver](https://drive.google.com/file/d/1sPCllUSFPy56IU6-IgOWoAyB3GcKCKon) |
| *1004 | [Experiments for Joystick-Uno-L298N](https://drive.google.com/file/d/1AG-T4KW5Sv5UCVoDrdHhYXrfJJ76LF6E) |
| 1005 | [Study of Quaternions](https://drive.google.com/file/d/1xQS_DkKx-wXtF7fm8C6GPfF8NV9Qoxnr) |
| *1009 | [Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/1Vyc0tTbyL052Sz_xCbNz2F0aL16zDutC) |
| *1009 | [Supplemental: Circuits, Diagrams, and Check Lists](https://drive.google.com/file/d/1xfzl9v4AlJra85AO-Mb8qxhmqGoAyuV9) (printable) |
| *1009 | [MMC Results for JUL](https://drive.google.com/file/d/17yNw5FNRORWgtDyey11OeKGRMB9qV0SZ) |
| *1009 | [MMC Results for nRF24L01+](https://drive.google.com/file/d/11rTdUBuKK-MIu4N-AC_g-3Bj84E3aSp4) |
| 1018 | [Wireless Communication: Study nRF24L01+ Radio](https://drive.google.com/file/d/1FZ1uQ5eXjISBS4j_eSFcjuqiw4irZYlK) |
| Video | [Joystick Algorithm Simulation](https://carpentersoftware.com/pages/projects/ytube/joystickAlgoSim.html) |

Articles 1006 (Sensors), 1007 (PID), 1008 (Finite State Machines), 1010 (Robot Orientation), and 1011 (Communication) are in progress.

---

## Coding Rules

The code is written for the student who reads it as well as for the compiler.

- Every line stops at 80 characters, strings included.
- Every comment is on its own line above the statement it explains.
- A word in a comment is never split with a hyphen.
- A long string is split with backslashes; when it starts with `\n`, every continued string also starts with `\n`.
- Walkthroughs name a line (the Bits() line) instead of citing its number.
- Every code file ends its comment header with a RELEASE block: the release, the release in which that file last changed, and the repository address.

---

## Releases

The current release is v7.5.0. Versions are MAJOR.MINOR.FIXES; see [RELEASES.md](RELEASES.md) for the notes and for the articles each release affects.

## Credits

`Code-JUL/include/numerics/LineFit2.h` and `Rotation.h` are adapted from the Geometric Tools Engine by **David Eberly** ([geometrictools.com](https://www.geometrictools.com)), under the Boost Software License, Version 1.0; each file keeps his copyright notice and states the changes. The files in `Code-JUL/include/claude/` were written with Claude (Anthropic) at the request of the author.

## License and Contact

MIT License. See [LICENSE](LICENSE) and [DISCLAIMER.md](DISCLAIMER.md).
Jesse Carpenter, [Carpenter Software](https://carpentersoftware.com), [hello@carpentersoftware.com](mailto:hello@carpentersoftware.com).
