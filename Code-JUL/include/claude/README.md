# include/claude

The files in this folder were written with Claude (Anthropic), an AI assistant, at the request of Jesse Carpenter on 2026-10-17. They are kept apart from the original header files in `include/` and `include/numerics/`, which they do not change, so a reader can tell at once which code is original and which was generated. Each file was tested against the original code as described below and bench tested by the author.

| File | Used by | Purpose |
|---|---|---|
| `L298NPins.h` | Step3_Generator | Class `L298NPins` resolves one `Bits()` value of `L298N.h` into constant enable and direction pins, with the same four rules as `L298N::Bits()` and `L298N::UpdateL298N()` |
| `ace.h` | Step4_Generated | Class template `Ace`: the complete drive program in one file, for speed and size; includes `Arduino.h` only |

Other files written with Claude on the same date: `src/Step3_Generator/main.cpp` and `src/Step4_Generated/main.cpp` (printed by Step3_Generator).

## Original code incorporated into ace.h

| Original | What ace.h keeps |
|---|---|
| `Joystick.h`, class `Joystick<float>` | The octant algorithm, `UpdateInputs()`, `Left()`, `Right()`, the 0.001 tolerance |
| `numerics/LinearMap.h`, class `LinearMap<float>` | 0 to 1023 onto -1 to 1, and -1 to 1 onto -255 to 255 |
| `numerics/MiscMath.h` | Function template `absT()` |
| `Button.h`, class `Button` | Active LOW, latching, 50 ms debounce, indicator LED; internal pull up off, as in Step2_JUL since v3.1.1 |
| `Timer.h`, class `Timer` | `isTimer()`, armed on the first call |
| `Common.h` | `BUTTON_TIMER_mS`, the control tick: 100 ms in Step2_JUL with the debug switches commented out (3000 ms as shipped, since v3.2.0), 45 ms in `ace.h` (`TICK_MS`, since v7.2.0; 50 ms from v3.2.0) |
| `L298N.h`, class `L298N` | `UpdateL298N()` and `PowerDownL298N()`, with the `Bits()` decision made by Step3_Generator |
| Arduino core | `analogRead()`, `digitalWrite()`, `analogWrite()`, `pinMode()`, replaced by register access |

Not incorporated: the `Debug()` serial output of `MiscMath.h` and the debug flags of `Common.h`. The numerics headers remain separate and unchanged.

## How ace.h is faster

1. **ADC**: the joystick is read through the ADC registers with the prescaler of the Arduino core (125 kHz ADC clock), so the readings and their accuracy are those of `analogRead()`.
2. **Integer math**: the float chain of Step2_JUL is computed in integers scaled by 1023. A reading a (0 to 1023) gives N = 2a - 1023; the dead zones 0.05 and 0.06 become |N| <= 51 and |N| <= 61; the output 255 N / 1023 is one multiplication by 16336 and a 16 bit shift.
3. **Pins**: every pin is a template parameter, so each write is one instruction on a port register or a timer compare register, with the same pin states as `digitalWrite()` and `analogWrite()`.

## Performance

avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, simavr at 16 MHz, 1024 simulated joystick positions, bits_1010, measured 20261017:

| Stage, microseconds per tick | Step2_JUL | ace.h | Times faster |
|---|---|---|---|
| Joystick math (map, dead zone, octants, map) | 322.5 | 16.4 | 19.6 |
| Motor output | 40.3 | 3.7 | 10.9 |
| Math and output | 362.9 | 20.1 | 18.0 |
| Two ADC readings | 212.3 | 211.9 | 1.0 |
| Full control tick | 574.8 | 232.0 | 2.5 |

| Size, v3.2.1 (20261019) | Step2_JUL, flags commented out | Step4_Generated with ace.h |
|---|---|---|
| Flash | 6498 bytes | 1548 bytes |
| RAM | 318 bytes | 23 bytes |

Step4_Generated as measured without `DEBUG_GENERATED` (20261017, before v3.1.1: 6344 and 316 bytes for Step2_JUL, 1420 and 23 bytes for Step4_Generated). With it, the Serial code of the startup printout adds about 2.1 KB of flash and 177 bytes of RAM (avr-gcc 7.3.0 without link time optimization, 20261018: 1548 to 3654 bytes of flash, 23 to 200 bytes of RAM); the control tick is unchanged.

The two ADC conversions are 91 percent of the ace.h tick; they are set by the ADC clock, kept at 125 kHz for full accuracy. At one tick every 100 ms, Step2_JUL uses about 0.57 percent of the processor time. ace.h ticked every 50 ms from v3.2.0 and used about 0.46 percent (0.23 percent at 100 ms). Since v7.0.0 a tick takes about 249 µs (THE JOYSTICK EQUATIONS add about 17 µs); since v7.2.0 it repeats every 45 ms, about 0.55 percent of the processor time.

## Verification (2026-11-18, release v7.5.1)

- Every program of Code-JUL, all 20 lessons, and the 14 programs of the experiments build for the Uno (avr-gcc 7.3.0, `-Wall -Wextra`) with no warnings; Step4_Generated also with `DEBUG_GENERATED` off.
- Host simulation, all 1024 x 1024 pairs of joystick readings with the shipped measurements (A0: 0, 510, 1008; A1: 0, 497, 1009): `Ace::compute()` and the float chain of Step2_JUL give the same commands for 1.6 percent of the pairs. The mean difference is 6 and the largest 16 of 255, over the whole range: Step4 measures its dead zone in counts (25) and spreads the rest of each side over the full command, while Step2_JUL applies X_OFFSET 0.05 and Y_OFFSET 0.06 after its input map. Both are correct; they are two designs.
- The joystick correction of `ace.h` and `JoystickCorrection.h` follow the same equations (Article 1009, Equation-1); `JoystickCorrection` matches them for all 1024 readings.
- Bench tested by the author.

## Keep in step

`L298NPins.h` and `ace.h` repeat rules of `L298N.h`, `Joystick.h`, `LinearMap.h`, `Button.h`, and `Timer.h`. If one of those files changes, change these files to match and repeat the tests.
