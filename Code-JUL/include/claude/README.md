# include/claude

The files in this folder were written with Claude (Anthropic), an AI assistant, at the request of Jesse Carpenter on 2026-10-17. They are kept apart from the original header files in `include/` and `include/numerics/`, which they do not change, so a reader can tell at once which code is original and which was generated. Each file was tested against the original code as described below; the bench test on hardware is pending.

| File | Used by | Purpose |
|---|---|---|
| `L298NPins.h` | Step4_Generator | Class `L298NPins` resolves one `Bits()` value of `L298N.h` into constant enable and direction pins, with the same four rules as `L298N::Bits()` and `L298N::UpdateL298N()` |
| `ace.h` | Step5_Generated | Class template `Ace`: the complete drive program in one file, for speed and size; includes `Arduino.h` only |

Other files written with Claude on the same date: `src/Step4_Generator/main.cpp` and `src/Step5_Generated/main.cpp` (printed by Step4_Generator).

## Original code incorporated into ace.h

| Original | What ace.h keeps |
|---|---|
| `Joystick.h`, class `Joystick<float>` | The octant algorithm, `UpdateInputs()`, `Left()`, `Right()`, the 0.001 tolerance |
| `numerics/LinearMap.h`, class `LinearMap<float>` | 0 to 1023 onto -1 to 1, and -1 to 1 onto -255 to 255 |
| `numerics/MiscMath.h` | Function template `absT()` |
| `Button.h`, class `Button` | Active LOW with the internal pull up, latching, 50 ms debounce, indicator LED |
| `Timer.h`, class `Timer` | `isTimer()`, armed on the first call |
| `Common.h` | `BUTTON_TIMER_mS`, the 100 ms control tick |
| `L298N.h`, class `L298N` | `UpdateL298N()` and `PowerDownL298N()`, with the `Bits()` decision made by Step4_Generator |
| Arduino core | `analogRead()`, `digitalWrite()`, `analogWrite()`, `pinMode()`, replaced by register access |

Not incorporated: the `Debug()` serial output of `MiscMath.h` and the debug flags of `Common.h`. The numerics headers remain separate and unchanged.

## How ace.h is faster

1. **ADC**: the joystick is read through the ADC registers with the prescaler of the Arduino core (125 kHz ADC clock), so the readings and their accuracy are those of `analogRead()`.
2. **Integer math**: the float chain of Step2_JUL is computed in integers scaled by 1023. A reading a (0 to 1023) gives N = 2a - 1023; the dead zones 0.05 and 0.06 become |N| <= 51 and |N| <= 61; the output 255 N / 1023 is one multiplication by 16336 and a 16 bit shift.
3. **Pins**: every pin is a template parameter, so each write is one instruction on a port register or a timer compare register, with the same pin states as `digitalWrite()` and `analogWrite()`.

## Performance

avr-gcc 7.3.0, ArduinoCore-avr 1.8.6, simavr at 16 MHz, 1024 simulated joystick positions, bits_1010:

| Stage, microseconds per tick | Step2_JUL | ace.h | Times faster |
|---|---|---|---|
| Joystick math (map, dead zone, octants, map) | 322.5 | 16.4 | 19.6 |
| Motor output | 40.3 | 3.7 | 10.9 |
| Math and output | 362.9 | 20.1 | 18.0 |
| Two ADC readings | 212.3 | 211.9 | 1.0 |
| Full control tick | 574.8 | 232.0 | 2.5 |

| Size | Step2_JUL | Step5_Generated with ace.h |
|---|---|---|
| Flash | 6344 bytes | 1420 bytes |
| RAM | 316 bytes | 23 bytes |

The two ADC conversions are 91 percent of the ace.h tick; they are set by the ADC clock, kept at 125 kHz for full accuracy. At one tick every 100 ms, Step2_JUL uses about 0.57 percent of the processor time and ace.h about 0.23 percent.

## Verification (2026-10-17)

- `Ace::compute()` gives the same left and right commands as the float chain of Step2_JUL for all 1024 x 1024 pairs of joystick readings. One case is reproduced on purpose: at x = 341 in octant 4 the float chain computes 84.99998 and truncates it to 84.
- On the simulated Uno, the port, timer, and compare registers after each motor update match the original code for 12519 pairs of readings, and the float results on the Uno match the host test.
- `L298NPins` with the printed motor code sets the same pin levels and duty cycles as `L298N::UpdateL298N()` for all 16 `Bits()` values and seven command pairs.
- Not yet tested: the push button and the timer of ace.h on the bench, and Step5_Generated with motors.

## Keep in step

`L298NPins.h` and `ace.h` repeat rules of `L298N.h`, `Joystick.h`, `LinearMap.h`, `Button.h`, and `Timer.h`. If one of those files changes, change these files to match and repeat the tests.
