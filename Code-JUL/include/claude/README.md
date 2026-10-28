# include/claude

The files in this folder were written with Claude (Anthropic), an AI assistant, at the request of Jesse Carpenter on 2026-10-17. They are kept apart from the original header files in `include/` and `include/numerics/`, which they do not change, so a reader can tell at once which code is original and which was generated. Each file was tested against the original code as described below, and on the bench by the author on 2026-10-21 (release v4.0.1).

| File | Used by | Purpose |
|---|---|---|
| `L298NPins.h` | Step3_Generator | Class `L298NPins` resolves one `Bits()` value of `L298N.h` into constant enable and direction pins, with the same four rules as `L298N::Bits()` and `L298N::UpdateL298N()` |
| `ace.h` | Step4_Generated | Class template `Ace`: the complete drive program in one file, for speed and size; includes `Arduino.h` only |

Other files written with Claude on the same date: `src/Step3_Generator/main.cpp` and `src/Step4_Generated/main.cpp` (printed by Step3_Generator).

Revised later on 2026-10-17: the programs were renumbered (Step4_Generator to Step3_Generator, Step5_Generated to Step4_Generated, Step2_JUL to Step1_JUL; since v4.0.0 the names are Step3_Generator, Step4_Generated, and Step2_JUL), and Step3_Generator now asks one question, the `Bits()` value. The joystick lines are fixed as in Step2_JUL, x on A1 and y on A0 with no reversal, because one `Bits()` value corrects any joystick orientation (see `../../README.md`, Setup with One Bits() Value). `ace.h` keeps `X_REVERSED` and `Y_REVERSED` as template parameters; the printed program sets them false. Printed for bits_1010, the program builds to the same Intel HEX as before the revision; the shipped Step4_Generated is printed for bits_0000, the first row of the checklist. `readLine()` of Step3_Generator now accepts LF, CR, and CR LF line endings.

Revised for v3.0.1 (2026-10-17): Step3_Generator takes the four binary digits of the `Bits()` value only (no decimal entry and no table), and Step3_Generator and Step4_Generated no longer use the build flags `STEP3_GENERATOR` and `STEP4_GENERATED`; each is selected with `build_src_filter` in `platformio.ini`. The printed program has no `#ifdef` line, so it can be copied into a project of its own with `ace.h` unchanged. Step4_Generated, printed again for bits_0000, builds to the same Intel HEX as in v3.0.0.

Revised for v3.1.0 (2026-10-18): the programs were renumbered in the order of use (Step3_Generator to Step2_Generator, Step4_Generated to Step3_Generated, Step2_MathLessons to Step4_MathLessons; since v4.0.0 the names are Step3_Generator, Step4_Generated, and Step5_MathLessons). Step2_JUL now reads x on A0 and y on A1, and those lines stay as written. Step3_Generator shows the L298N, push button, and LED pins as Uno and ATmega328P pins (for example `D5 (PD5)`) and the joystick lines for the student to confirm against Step2_JUL, then asks for the `Bits()` value and whether the printed program carries the debug data. With the debug data, Step4_Generated defines `DEBUG_GENERATED` and prints the checked data once in `setup()`. `ace.h` no longer has the template parameters `X_REVERSED` and `Y_REVERSED`: one `Bits()` value corrects any joystick orientation, so the reversal was never used. The shipped Step4_Generated is printed for bits_0000 with the debug data.

Revised for v3.1.1 (2026-10-18): the push button pin is configured as an input with the internal pull up off, as Step2_JUL does with the line `pinMode(buttonPin, INPUT)`. The joystick switch module may have its own pull up or pull down resistor; with none, an external 10 kOhm resistor is added. `ace.h` reads the button active LOW, the form of Step2_JUL as shipped.

Revised for v3.2.0 (2026-10-18), requested by the author after a bench test: the default control tick of `ace.h`, `TICK_MS`, is 50 ms in place of 100 ms, for a faster response to the joystick; Step2_JUL keeps `BUTTON_TIMER_mS` of `Common.h` (100 ms without debug flags). The bench test also showed that the thumb joystick module has no resistor on SW, so the external 10 kOhm pull up from D2 to 5 V (Article 1004, Circuit-2) is required; it matches the active LOW reading of `ace.h`, so Step3_Generator needs no question about the button polarity. Step3_Generator prints both facts into the header of the program, and the shipped Step4_Generated was printed again (bits_0000, with the debug data, unedited). Step4_Generated is the drive program of the repository; Step2_JUL ships with every debug flag of `Common.h` on and serves the checks.

Revised for v3.2.1 (2026-10-19), requested by the author: the program printed by Step3_Generator calls `robot.begin()` as the first line of `setup()`, ahead of the debug output, so D5 to D10 are outputs and LOW at once after a reset (Discrepancies.md, 85). The shipped Step4_Generated was printed again (bits_0000, with the debug data). `ace.h` changed in one comment only.

Revised for v6.4.0 (2026-10-25), requested by the author after his bench test of v6.3.1.a: `ace.h` takes the joystick center as two more template parameters, `X_CENTER` and `Y_CENTER`, at the end of the list (default 511, range 461 to 561 since v6.5.0; 411 to 611 in v6.4.0 and v6.4.1). `tick()` moves each reading by `CENTER - 511` and holds it inside 0 to 1023, so a resting grip gives the command 0; `compute()` is unchanged. Step2_JUL keeps the center 511 (author decision). Step3_Generator reads the centers from `include/JoystickCenter.h`, shows them as Check 1, and prints them into Step4_Generated with `TICK_MS` and `DEBOUNCE_MS`, which come before them in the list. Host test: for six pairs of centers and all 1024 x 1024 pairs of readings, the same commands as the float chain of Step2_JUL applied to the moved readings. Cost: about 24 cycles (1.5 µs) per tick and 46 bytes of flash when a center differs from 511; nothing for 511.

Revised for v5.0.0 (2026-10-21), requested by the author: the default of `LED_PIN` in `ace.h` is 12, the indicator LED of Article 1009, Circuit-1, in place of 3. Step4_Generated passes `LED_PIN = 12` itself, so it builds to the same Intel HEX. The bench test of 2026-10-21 (release v4.0.1) passed.

## Original code incorporated into ace.h

| Original | What ace.h keeps |
|---|---|
| `Joystick.h`, class `Joystick<float>` | The octant algorithm, `UpdateInputs()`, `Left()`, `Right()`, the 0.001 tolerance |
| `numerics/LinearMap.h`, class `LinearMap<float>` | 0 to 1023 onto -1 to 1, and -1 to 1 onto -255 to 255 |
| `numerics/MiscMath.h` | Function template `absT()` |
| `Button.h`, class `Button` | Active LOW, latching, 50 ms debounce, indicator LED; internal pull up off, as in Step2_JUL since v3.1.1 |
| `Timer.h`, class `Timer` | `isTimer()`, armed on the first call |
| `Common.h` | `BUTTON_TIMER_mS`, the control tick: 100 ms in Step2_JUL with the debug switches commented out (3000 ms as shipped, since v3.2.0), 50 ms in `ace.h` (`TICK_MS`, since v3.2.0) |
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

The two ADC conversions are 91 percent of the ace.h tick; they are set by the ADC clock, kept at 125 kHz for full accuracy. At one tick every 100 ms, Step2_JUL uses about 0.57 percent of the processor time. ace.h ticks every 50 ms since v3.2.0 and uses about 0.46 percent (0.23 percent at 100 ms).

## Verification (2026-10-17)

- `Ace::compute()` gives the same left and right commands as the float chain of Step2_JUL for all 1024 x 1024 pairs of joystick readings. One case is reproduced on purpose: at x = 341 in octant 4 the float chain computes 84.99998 and truncates it to 84.
- On the simulated Uno, the port, timer, and compare registers after each motor update match the original code for 12519 pairs of readings, and the float results on the Uno match the host test.
- `L298NPins` with the printed motor code sets the same pin levels and duty cycles as `L298N::UpdateL298N()` for all 16 `Bits()` values and seven command pairs.
- 2026-10-21: bench tested by the author (release v4.0.1): Step3_Generator, and Step4_Generated with motors, the push button, the timer of ace.h, and the LED on D12; all passed.
- 2026-10-19 (v3.2.1): in simavr, D5 and D10 of Step4_Generated are outputs and LOW 0.0001 s after reset (0.626 s in v3.2.0); with the same button press and 13 joystick positions, Step4_Generated and Step2_JUL with its debug flags commented out set the same IN pins, enable duty cycles, and LED (Discrepancies.md, 90).
- 2026-10-18 (v3.2.0): with `TICK_MS` 50, Step4_Generated builds with no warnings (`-Wall -Wextra`), 3654 bytes of flash and 200 bytes of RAM with `DEBUG_GENERATED`, as before; the tick changes only the time between ticks, not the pin states set for a pair of readings. Step3_Generator, run in simavr with the answers y, y, 0000, y, p, prints the shipped Step4_Generated.

## Keep in step

`L298NPins.h` and `ace.h` repeat rules of `L298N.h`, `Joystick.h`, `LinearMap.h`, `Button.h`, and `Timer.h`. If one of those files changes, change these files to match and repeat the tests.
