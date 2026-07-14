# Joystick Uno L298N (JUL) Repository

**A differential drive motor control system for Arduino Uno using joystick input and the L298N H-bridge motor driver.**

---

## Quick Start

### Prerequisites

| Item | Requirement |
|------|-------------|
| **MCU** | Arduino Uno (Atmega328P) — genuine board recommended |
| **Editor** | Visual Studio Code |
| **Build Tool** | PlatformIO (VS Code extension) |
| **Joystick** | 2-axis analog thumbstick + push button |
| **Motor Driver** | L298N dual H-bridge module |
| **Motors** | 2× DC motors (any voltage matching your power supply) |

### Installation Steps

1. **Install VS Code** — Download from [code.visualstudio.com](https://code.visualstudio.com)

2. **Install PlatformIO Extension**
   - Open VS Code → Extensions (Ctrl+Shift+X)
   - Search for "PlatformIO IDE"
   - Click Install

3. **Clone this Repository**
   ```bash
   git clone https://github.com/MageMCU/Joystick-Uno-L298N.git
   ```

4. **Open in VS Code**
   - File → Open Folder
   - Navigate to `Code-JUL/`
   - **Important:** Open `Code-JUL/` only (do **not** open the repository root folder)
   - Wait for PlatformIO to index the project

5. **Connect Arduino Uno**
   - Plug in via USB
   - PlatformIO will auto-detect the port

6. **Upload Firmware**
   - Bottom bar → "Upload" button (or use keyboard shortcut)
   - Wait for compilation and upload to complete
   - Status will show "SUCCESS"

### Important Folder Selection Rule

- PlatformIO project root for this firmware is `Code-JUL/`.
- If you open the full repository root in VS Code instead, PlatformIO/compile tasks can fail or report confusing path/source-filter errors.
- If you see compiler complaints, close VS Code and reopen only `Code-JUL/`.

---

## What This Repo Does

- **Reads** joystick X/Y analog input (2-axis) + push button
- **Processes** input through octant-based differential drive algorithm
- **Controls** two independent DC motors via L298N H-bridge
- **Provides** smooth, noise-free motor response with tolerance-based dead zone

---

## Project Structure

```
Joystick-Uno-L298N/
├── Code-JUL/                     ← Main firmware (open this in VS Code)
│   ├── include/                  ← Header files
│   │   ├── Joystick.h            ← Motor control algorithm (revised)
│   │   ├── L298N.h               ← Motor driver interface
│   │   ├── Button.h              ← Button debounce handler
│   │   ├── LinearMap.h           ← ADC value mapping
│   │   └── ...other utilities
│   ├── src/
│   │   ├── Step1_Joystick/       ← Wiring test only (validate connections)
│   │   └── Step2_JUL/            ← Full firmware (use this one)
│   ├── platformio.ini            ← Build configuration
│   └── README.md                 ← Firmware documentation
├── Motor-Movement-Checklist/     ← Mechanical test guide
└── README.md                     ← This file
```

---

## Hardware Setup

### Wiring Checklist

| Component | Arduino Pin | L298N Pin | Notes |
|-----------|-------------|-----------|-------|
| Joystick X | A1 | — | Analog input |
| Joystick Y | A0 | — | Analog input |
| Joystick Button | D2 (SW) | — | Digital input |
| Button LED | D3 | — | Digital output |
| L298N EN-A | D5 (PWM) | ENA | Motor A speed control |
| L298N IN1 | D6 | IN1 | Motor A direction 1 |
| L298N IN2 | D7 | IN2 | Motor A direction 2 |
| L298N IN3 | D8 | IN3 | Motor B direction 1 |
| L298N IN4 | D9 | IN4 | Motor B direction 2 |
| L298N EN-B | D10 (PWM) | ENB | Motor B speed control |

**Motor Control Logic:**
- Joystick X/Y → ADC (0–1023) → Mapped to −1.0 to +1.0
- Algorithm outputs left/right motor speeds
- L298N IN1/IN2 (or IN3/IN4) set direction
- EN-A/EN-B PWM controls speed (0–255)

---

## Active Algorithm

The repository uses the **revised joystick algorithm** with:

- **8-direction octant routing** — smooth transitions in all directions
- **Tolerance-based dead zone** — eliminates ADC noise automatically
- **Forward/backward detection** — methods for advanced motor control

For algorithm comparison and full study materials, see the PRIVATE repo: [Joystick-Uno-L298N-PRIVATE](https://github.com/MageMCU/Joystick-Uno-L298N-PRIVATE).

---

## Testing Platform

| Platform | Version |
|----------|---------|
| **MCU** | Atmega328P (Arduino Uno) |
| **IDE** | PlatformIO |
| **Editor** | Visual Studio Code |
| **Language** | C++ (GNU++11) |
| **Status** | Hardware tested & verified |

---

## Next Steps

1. **First Time?** → Review [Code-JUL/README.md](Code-JUL/README.md) for detailed firmware docs

2. **Joystick API Reference**
   
   | Method | Returns | Purpose |
   |--------|---------|---------|
   | `UpdateInputs(inputX, inputY)` | void | Process joystick X/Y values (−1 to +1) |
   | `Left()` | float | Get left motor output (−1 to +1) |
   | `Right()` | float | Get right motor output (−1 to +1) |
   | `IsLeftForward()` | bool | Check if left motor is moving forward |
   | `IsRightForward()` | bool | Check if right motor is moving forward |
   | `Octant()` | int | Get current octant (0 = stop, 1–8 = directions) |

3. **Debugging?** → Enable serial debug in `Common.h`:
   ```cpp
   // #define DEBUG_JOYSTICK    // Uncomment for joystick debug output
   // #define DEBUG_L298N       // Uncomment for motor driver debug output
   ```
   Then use Serial Monitor (9600 baud) to view real-time values

4. **Algorithm Research?** → See [Joystick-Uno-L298N-PRIVATE](https://github.com/MageMCU/Joystick-Uno-L298N-PRIVATE) for test data and study materials

5. **Motor Tuning?** → Check [Motor-Movement-Checklist/ReadMe.md](Motor-Movement-Checklist/ReadMe.md)

---

## Resources

- **Algorithm Simulation:** [YouTube Video](https://www.youtube.com/watch?v=maIHbdbDBwo&t=2s)
- **Study & Research:** [Joystick-Uno-L298N-PRIVATE](https://github.com/MageMCU/Joystick-Uno-L298N-PRIVATE)
- **QA & Testing:** Available in the PRIVATE repository study materials

---

## Repository Status & History

### Design Philosophy: Simplified for Clarity

This repository is an **intentionally simplified, user-focused version** derived from the more complex predecessor experimental repository. The reduction prioritizes:

- ✅ **Clear, focused firmware** — Single algorithm, no compile-time switching
- ✅ **Quick onboarding** — New users can deploy without algorithm selection complexity
- ✅ **Production readiness** — Proven algorithm chosen and locked
- ✅ **Better documentation** — Simplified README, clear wiring guides, API reference
- ✅ **Reduced cognitive load** — No algorithm selection decisions; works out of the box

### Public vs. Predecessor (PRIVATE)

| Feature | Public (Current) | PRIVATE (Predecessor) |
|---------|------------------|----------------------|
| **Target** | Users deploying JUL | Researchers studying algorithms |
| **Algorithm** | 1 (Revised) — fixed | 3 variants — selectable |
| **Compile-time switches** | ❌ None | ✅ `ALGO_ORIGINAL`, `ALGO_STUDY_*` |
| **Study folders** | Reference docs only | Full experimental infrastructure |
| **Build complexity** | Simple (no flags) | Complex (algorithm selection) |
| **User onboarding** | Quick start (6 steps) | Experimental workflow |
| **Firmware maturity** | Production-ready | Research platform |
| **Documentation** | Condensed quick-ref | Detailed research logs |

### What Was Simplified Away

The **PRIVATE repo** retains experimental features now removed from public:

- **Algorithm selection system** — Removed `ALGO_ORIGINAL`, `ALGO_STUDY_REVISED`, `ALGO_STUDY_COMPACT` flags
- **Manual algorithm switching** — Removed compile-time variant selection logic
- **JUL-Study/ infrastructure** — Removed experimental test configurations
- **Build flag alternatives** — Removed `platformio.ini` algorithm override mechanism
- **Development logs** — Kept in PRIVATE repo for research reference

### Why Simplify?

**Focus on Production:**
- Users deploying JUL don't need algorithm variants—they need a **working system now**
- Removed decision fatigue: no "which algorithm should I use?" question
- Locked tested algorithm reduces testing burden for end-users

**Clearer Documentation:**
- Single algorithm path = simpler Quick Start guide
- No conditional compilation to explain
- Wiring guide and API reference are self-contained

**Maintainability:**
- Easier code review (no preprocessor conditionals)
- Fewer build configurations to validate
- Cleaner commit history for production branch

### Access to Full Research

Need the experimental features or research data?

| Resource | Location | Content |
|----------|----------|---------|
| **PRIVATE Repo** | [Joystick-Uno-L298N-PRIVATE](https://github.com/MageMCU/Joystick-Uno-L298N-PRIVATE) | Algorithm variants, selection system, study materials, dev logs |
| **Study Materials** | [Joystick-Uno-L298N-PRIVATE](https://github.com/MageMCU/Joystick-Uno-L298N-PRIVATE) | Full QA reports, migration guides, benchmarks |
| **Articles** | Carpenter Software blog | Deep dives into algorithm design and performance |

---
   
