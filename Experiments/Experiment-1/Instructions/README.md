# Joystick-Uno-L298N Experiment-1

## Timing and Button Input on the Arduino Uno

Carpenter Software, Jesse Carpenter. STEM Starter Kit Series, Part 5 (Article 1004), Experiment-1.

---

## 1. Overview

Experiment-1 is the first experiment in the Joystick-Uno-L298N (JUL) series. It uses the Arduino Uno alone: no motor driver, no motors, and no joystick. It teaches the timing pattern that every later part of the JUL firmware depends on.

The JUL firmware reads a joystick, runs a drive algorithm, and commands the L298N motor driver, all inside one function called `loop()` that must never stop. Before the motor hardware is introduced, you need to understand why `loop()` must keep running and how the firmware waits for an interval without stopping it.

The experiment has three software labs. Each lab is a folder under `Code/src/`, and each is a complete program with its own `main.cpp`.

| Lab | Folder | What it shows |
|-----|--------|---------------|
| Lab 1 | `1_Delay` | Blinks the onboard LED with `delay()` and shows what that function costs |
| Lab 2 | `2_Timer` | Replaces `delay()` with the `Timer` class, which waits while `loop()` keeps running |
| Lab 3 | `3_Button` | Adds the `Button` class so a push button turns the timed work on and off |

The `Timer` and `Button` classes are the same classes the full JUL firmware uses in `Code-JUL`, so you are working with production code from the first lab.

### Two terms used throughout

**Blocking call.** A function call that does not return until its work is finished. While it runs, nothing else in `loop()` can execute.

**Nonblocking design.** The work is divided into short steps and each step returns at once, so `loop()` repeats many times per second and attends to several tasks in turn.

Lab 1 is blocking. Labs 2 and 3 are nonblocking.

### Two styles of code

Each `main.cpp` is written in the **procedural** style of the C language: a sequence of statements and function calls. `Timer.h` and `Button.h` are written in the **object oriented** style of C++: a class bundles data and the functions that operate on that data into one unit, the program creates an object of that class, and it calls the object's methods. A **method** is a function that belongs to a class. The sketches call `timer.isTimer()` and `button.updateButton()` without needing to know how they are implemented.

---

## 2. Materials

Labs 1 and 2 need only the Uno and a USB cable. The onboard LED on digital pin 13 is the only output. Lab 3 adds a push button and an indicator LED on the breadboard.

| Item | Qty | Used in | Notes |
|------|-----|---------|-------|
| Arduino Uno, Rev3 | 1 | Labs 1, 2, 3 | Onboard LED on pin 13 |
| USB cable, Uno to computer | 1 | Labs 1, 2, 3 | Power, upload, and Serial Monitor |
| Breadboard and jumper wires | 1 set | Lab 3 | |
| Tactile push button, momentary, normally open | 1 | Lab 3 | Wired between D2 and GND |
| LED, 5 mm | 1 | Lab 3 | Indicator LED on D3 |
| Resistor, 220 ohm, 1/4 W | 1 | Lab 3 | Current limiting resistor for the LED |

No pull up or pull down resistor is needed for the button. The `Button` class enables the Uno's internal pull up resistor on the button pin (see Lab 3).

---

## 3. Software Setup

### 3.1 Open the project

The labs are built with **PlatformIO**, an embedded development extension for Visual Studio Code. The PlatformIO project for this experiment is the folder `Experiments/Experiment-1/Code`.

1. Open Visual Studio Code.
2. File, Open Folder, and select `Experiments/Experiment-1/Code`.
3. Wait for PlatformIO to finish indexing (the status bar at the bottom stops changing).

Open that folder, not the repository root. Opening the root makes PlatformIO search the wrong directories and report path errors.

```
Joystick-Uno-L298N/
  Experiments/
    Experiment-1/
      Instructions/
        README.md            this file
      Code/                  open this folder in Visual Studio Code
        platformio.ini
        README.md
        include/
          Timer.h
          Button.h
        src/
          1_Delay/main.cpp   Lab 1
          2_Timer/main.cpp   Lab 2
          3_Button/main.cpp  Lab 3
```

### 3.2 Select a lab in platformio.ini

All three labs share one PlatformIO project, and only one may be compiled at a time because each defines its own `setup()` and `loop()`. The active lab is chosen with the `build_src_filter` line in `platformio.ini`. A **source filter** is a list of folder patterns under `src/`; a pattern with a plus sign is included in the build and a pattern with a minus sign is excluded.

```
build_src_filter = +<*> +<1_Delay/> -<2_Timer/> -<3_Button/>
```

The wildcard `+<*>` includes the `src/` folder and everything under it as the starting set. The exclusions then remove the two folders that are not wanted. Without the wildcard the starting set would be empty and the exclusions would have nothing to act on.

| To run | Set build_src_filter to |
|--------|-------------------------|
| Lab 1 | `+<*> +<1_Delay/> -<2_Timer/> -<3_Button/>` |
| Lab 2 | `+<*> -<1_Delay/> +<2_Timer/> -<3_Button/>` |
| Lab 3 | `+<*> -<1_Delay/> -<2_Timer/> +<3_Button/>` |

Save the file after each change. PlatformIO reads it at the next build.

### 3.3 Serial port

`platformio.ini` leaves `upload_port` unset so that PlatformIO detects the Uno automatically. If the upload fails with a port error, uncomment the `upload_port` line and set it to the device name for your computer. On Linux the Uno appears as `/dev/ttyACM0`, on macOS as `/dev/cu.usbmodemXXXX` where XXXX varies by board, and on Windows as a COM port such as `COM3`.

### 3.4 Build, upload, and monitor

1. Click the **Build** button (check mark) in the PlatformIO toolbar at the bottom of the window. The terminal ends with SUCCESS.
2. Click **Upload** (right arrow). The terminal ends with SUCCESS and the Uno resets.
3. Click **Serial Monitor** (plug icon). The monitor opens at 9600 baud, set by `monitor_speed` in `platformio.ini`.

**Baud** is the signaling rate of the serial link. The rate set in the sketch by `Serial.begin(9600)` must match the rate of the monitor. The first line printed by every lab is `Serial 9600 baudrate`, which confirms that the rates match. If you see nothing or unreadable characters, the rates differ.

---

## 4. Lab 1: The delay() Function

**Objective.** Blink the onboard LED once per two seconds with `delay()`, count how many times `loop()` runs, and observe that the count advances by exactly one per blink.

**Source folder.** `Code/src/1_Delay/main.cpp`. No additional wiring.

**Set the filter.** `build_src_filter = +<*> +<1_Delay/> -<2_Timer/> -<3_Button/>`

### 4.1 The code

```cpp
#include <Arduino.h>

#define LED_PIN 13

// Global
int counter = 0;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");
    pinMode(LED_PIN, OUTPUT);
}

// Delay? 
void loop()
{
    Serial.print("Number of Loops: ");
    Serial.println(counter++);

    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED HIGH");
    delay(1000);

    digitalWrite(LED_PIN, LOW); 
    Serial.println("LED LOW");
    delay(1000); 

    Serial.println("-----------");
}
```

### 4.2 How it works

The Arduino framework calls `setup()` once after power up or reset and then calls `loop()` repeatedly for as long as the board is powered. In `setup()`, `Serial.begin()` opens the serial port, the `while (!Serial)` loop waits until the port is ready, and `pinMode()` configures pin 13 as an output.

In `loop()`, the global variable `counter` is printed and then incremented, so the first line reads `Number of Loops: 0`. The LED is turned on with `digitalWrite(LED_PIN, HIGH)`, and `delay(1000)` then holds the processor for 1000 milliseconds. `delay()` is a blocking call: the processor executes nothing else in the sketch until the interval has elapsed. The LED is turned off and a second `delay(1000)` follows. One pass through `loop()` therefore takes about two seconds, and the counter advances by one per pass.

### 4.3 Steps

1. Set the filter for Lab 1 and save `platformio.ini`.
2. Build and upload.
3. Open the Serial Monitor.
4. Watch the onboard LED (marked L, next to pin 13) and the monitor for at least five blinks.

### 4.4 Expected output

```
Serial 9600 baudrate
Number of Loops: 0
LED HIGH
LED LOW
-----------
Number of Loops: 1
LED HIGH
LED LOW
-----------
```

### 4.5 What to observe

The count is exactly one per blink because `loop()` runs only once per two seconds. During each `delay(1000)` the sketch cannot read a sensor, sample a button, or update a motor command. In a robot, a blocking wait of one second means that a joystick released at the start of the wait is not noticed until the wait ends. Lab 2 removes this limitation.

---

## 5. Lab 2: The Timer Class

**Objective.** Blink the onboard LED on the same schedule as Lab 1 without stopping `loop()`, and count how many times `loop()` runs during each one second interval.

**Source folder.** `Code/src/2_Timer/main.cpp`, which includes `Code/include/Timer.h`. No additional wiring.

**Set the filter.** `build_src_filter = +<*> -<1_Delay/> +<2_Timer/> -<3_Button/>`

### 5.1 The code

```cpp
#include <Arduino.h>
#include "Timer.h"

#define LED_PIN 13
// Carpenter Software Jesse Carpenter
using namespace csjc;
// Object
Timer timer;
// Global Variables
unsigned long lastCount = 0;
unsigned long currentCount = 0;
unsigned long counter = 0;
// Assumes LOW to start counter...
bool toggle = false;

// the setup function runs once when you press reset or power the board
void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_PIN, OUTPUT);
    timer.resetTimer();
}

// the loop function runs over and over again forever
void loop()
{
    counter++;

    if (toggle && timer.isTimer(1000))
    {
        currentCount = counter - lastCount;
        Serial.print("Number of Loops: ");
        Serial.println(currentCount);

        digitalWrite(LED_PIN, HIGH); // turn the LED on (HIGH is the voltage level)
        Serial.println("LED HIGH");

        toggle = false;
    }

    if (!toggle && timer.isTimer(1000))
    {
        digitalWrite(LED_PIN, LOW); // turn the LED off by making the voltage LOW
        Serial.println("LED LOW");

        toggle = true;

        lastCount = counter;
        Serial.println("-----------");
    }
}
```

### 5.2 The Timer class

`Timer.h` declares the class `Timer` inside the **namespace** `csjc`. A namespace is a named scope that keeps the class name from colliding with any other `Timer` in the program; the line `using namespace csjc;` lets the sketch write `Timer` instead of `csjc::Timer`.

The class is built on `millis()`, an Arduino function that returns the number of milliseconds since the board was powered up as an `unsigned long`, a 32 bit unsigned integer.

`isTimer(ms)` returns `true` once each time `ms` milliseconds have elapsed since the previous time it returned `true`, and `false` on every other call. It never waits. The first call after construction or after `resetTimer()` **arms** the timer, meaning that it records the current `millis()` value as the starting point, and returns `false`. Elapsed time is computed as now minus the recorded start using unsigned subtraction, so the comparison stays correct when `millis()` rolls over to zero after about 49.7 days.

`Timer.h` also provides `isTimerFixedRate(ms)`, which schedules each interval from the previous deadline rather than from the moment the timer fired, and `deltaTimeSeconds()`, which reports the measured length of the last interval. These serve control loops in later experiments and are not needed here. Use one policy or the other on a given `Timer` object, not both.

### 5.3 How it works

`counter` is incremented on every pass through `loop()`, so it measures how many passes occur. The boolean `toggle` records which half of the blink is due next. It starts `false`, so the second `if` block is the first to act: when `isTimer(1000)` fires, the LED is set LOW, `toggle` becomes `true`, and `lastCount` is set to the current `counter`. One second later the first `if` block fires: it prints `counter - lastCount`, the number of passes completed during the interval, sets the LED HIGH, and clears `toggle`. The two blocks alternate at one second intervals, giving the same two second blink as Lab 1.

Each `if` condition tests `toggle` before calling `isTimer()`. Because `&&` evaluates its right operand only when the left operand is true, `isTimer()` is called from exactly one of the two blocks on any pass, so both blocks share a single timer without either one consuming the other's fire.

### 5.4 Steps

1. Set the filter for Lab 2 and save `platformio.ini`.
2. Build and upload.
3. Open the Serial Monitor and watch for at least five blinks.
4. Compare the `Number of Loops` value with Lab 1.

### 5.5 Expected output

```
Serial 9600 baudrate
LED LOW
-----------
Number of Loops: 118563
LED HIGH
LED LOW
-----------
Number of Loops: 118571
LED HIGH
```

The loop count shown is representative. The exact value depends on the board and on how many characters are printed during the interval; expect a number on the order of one hundred thousand per second.

### 5.6 What to observe

The LED blinks on the same schedule as Lab 1, but `loop()` now runs roughly one hundred thousand times per second instead of once per two seconds. Every one of those passes is an opportunity to read an input or update an output. This is the pattern the JUL firmware uses to sample the joystick and drive the motors while a timer paces the control update.

---

## 6. Lab 3: The Button Class with the Timer Class

**Objective.** Use a push button to turn the timed blink of Lab 2 on and off, with an indicator LED that shows the button state, and confirm that both the button and the timer are serviced on every pass through `loop()`.

**Source folder.** `Code/src/3_Button/main.cpp`, which includes `Code/include/Timer.h` and `Code/include/Button.h`.

**Set the filter.** `build_src_filter = +<*> -<1_Delay/> -<2_Timer/> +<3_Button/>`

### 6.1 Wiring, Circuit-1

The button is wired to close to ground. The `Button` class configures pin D2 as `INPUT_PULLUP`, which connects the Uno's internal pull up resistor (about 20 to 50 kilohm) between the pin and 5 V. With the button released the pin is pulled HIGH; pressing the button connects the pin to ground and it reads LOW. No external resistor is required. This is the same wiring the joystick SW pin uses in later experiments.

1. Place the tactile push button on the breadboard so that its two contact pairs straddle the center gap.
2. Wire one side of the button to Uno digital pin **D2**.
3. Wire the other side of the button to the breadboard ground rail.
4. Wire the anode (longer leg) of the LED to Uno digital pin **D3** through the 220 ohm resistor, and the cathode (shorter leg, flat side of the case) to the ground rail.
5. Wire the Uno **GND** pin to the breadboard ground rail.

**Check before uploading.** With the Uno powered by USB and the Lab 3 sketch not yet uploaded, the pin is not yet configured, so measure after the upload instead: with a multimeter from D2 to GND, expect about 5 V with the button released and 0 V while it is held. If you read the reverse, the button is wired to 5 V rather than to ground.

**Alternative wiring.** If you prefer a button wired to 5 V with an external 10 kilohm pull down resistor from D2 to ground, change the constructor in `setup()` to `Button(buttonPin, buttonLED, false)`. The third argument, `activeLow`, tells the class that a pressed button reads HIGH. Do not mix the two: the default constructor with a pull down resistor reads the idle pin as pressed.

### 6.2 The code

```cpp
#include <Arduino.h>
#include "Timer.h"
#include "Button.h"

#define LED_PIN 13

// Carpenter Software Jesse Carpenter
using namespace csjc;

// Object
Timer timer;
Button button;

// Global Variables
unsigned long lastCount = 0;
unsigned long currentCount = 0;
unsigned long counter = 0;
unsigned long timerMS = 1000;

// Assumes LOW to start counter...
bool toggle = true;
bool once = true;

// the setup function runs once when you press reset or power the board
void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");

    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_PIN, OUTPUT);

    // Temporary (local) variables
    int buttonPin = 2; // UNO D2, push button to GND
    int buttonLED = 3; // UNO D3, indicator LED through 220 ohm to GND

    // Instantiate Button Object
    // Default wiring (activeLow = true): the button closes to GND and
    // the class configures the pin as INPUT_PULLUP, so no external
    // resistor is needed. This is the same wiring the joystick SW pin
    // uses in Code-JUL. For a button wired to 5V with an external
    // pull down resistor, use Button(buttonPin, buttonLED, false).
    button = Button(buttonPin, buttonLED);
    button.begin();

    timer.resetTimer();
}

// the loop function runs over and over again forever
void loop()
{
    counter++;
    // Essential Button Call
    button.updateButton();
    // Methods called once to reduce processing time
    bool buttonON = button.isButtonOn();
    bool tickON = timer.isTimer(timerMS);

    // Complete the cycle with LOW
    // by using (OR !toggle) 
    if (buttonON || !toggle)
    {
        if (tickON)
        {
            if (toggle)
            {
                Serial.println("Button ON...");

                currentCount = counter - lastCount;
                Serial.print("Number of Loops per 2000 mS: ");
                Serial.println(currentCount);

                digitalWrite(LED_PIN, HIGH);
                Serial.println("LED HIGH");

                toggle = false;

                //
            }
            else
            {
                digitalWrite(LED_PIN, LOW);
                Serial.println("LED LOW");

                toggle = true;
                once = true;

                lastCount = counter;
                Serial.println("-----------");
            }
        }
    } 
    else // Button OFF (always the first state after power up)
    if (once && tickON)
    {
        // Simulate Motor Shutdown
        // Safety Comes First
        digitalWrite(LED_PIN, LOW);

        Serial.println("Button OFF...");
        Serial.println("-----------");
        once = false;
    }
}
```

### 6.3 The Button class

`Button.h` declares the class `Button` in the `csjc` namespace. It converts the raw contact of a momentary switch into a clean on and off state. Two ideas are involved.

**Debouncing.** For a few milliseconds after a press or release, a mechanical contact chatters between open and closed, and a sketch that read the pin directly would see several presses. The class ignores a new pin level until it has held steady for the **debounce window**, 50 milliseconds by default, and only then accepts it as the real state.

**Latching.** In the default latching mode, each accepted press toggles an on and off flag: press once for on, press again for off, in the manner of a push on, push off power switch. `isButtonOn()` reports this flag, and the indicator LED on the pin given to the constructor follows it. The class also offers a **momentary** mode, selected with `setLatching(false)`, in which the flag is on only while the button is held; that mode is intended as a dead man control for motors in later experiments and is not used here.

The constructor `Button(buttonPin, ledPin, activeLow, debounceMs)` records the pins and the wiring convention. `begin()` configures the pins and is called once in `setup()`. `updateButton()` samples the pin and must be called on every pass through `loop()`; if it were called only once per timer interval, a press shorter than the interval would be missed and the debounce window would be meaningless.

### 6.4 How it works

Each pass through `loop()` increments `counter`, calls `button.updateButton()`, and then reads the two conditions that drive everything else: `buttonON`, the latched state of the button, and `tickON`, whether the one second timer has fired on this pass. Each method is called once per pass and its result is stored, so the same value is used everywhere in the pass.

The outer `if` selects the on branch when the button is latched on **or** when a blink cycle is in its second half (`!toggle`). The second condition guarantees that a blink started while the button was on completes its LOW half even if the button is turned off in the middle of the cycle; the LED never remains stuck HIGH. Inside the on branch, nothing happens until `tickON` is true. When it is, `toggle` selects the HIGH half or the LOW half of the blink, alternating as in Lab 2, and the HIGH half prints the number of passes completed since the previous LOW half. That span covers two timer intervals, hence the label per 2000 mS.

The `else` branch runs while the button is off and no half cycle is pending. It waits for one timer tick, forces the LED LOW, prints `Button OFF`, and clears the `once` flag so the message is printed a single time rather than on every tick. `once` is set again inside the LOW half of the blink, so the next transition from on to off prints the message again. The comment in the source names the intent: in the full firmware, this branch is where the motors are commanded to stop when the operator turns the enable button off.

### 6.5 Steps

1. Build Circuit-1.
2. Set the filter for Lab 3 and save `platformio.ini`.
3. Build and upload. Open the Serial Monitor.
4. Confirm both LEDs are off and `Button OFF...` is printed once.
5. Measure D2 to GND with the multimeter: about 5 V released, 0 V held.
6. Press the button once. The indicator LED on D3 lights at once; the onboard LED starts blinking on the next tick and `Button ON...` with a loop count is printed each cycle.
7. Press the button again. The indicator LED goes off; the onboard LED finishes its current cycle LOW and `Button OFF...` is printed once.
8. Tap the button rapidly several times. Each accepted press changes the indicator LED exactly once.

### 6.6 Expected output

```
Serial 9600 baudrate
Button OFF...
-----------
                          (press the button once)
Button ON...
Number of Loops per 2000 mS: 73412
LED HIGH
LED LOW
-----------
Button ON...
Number of Loops per 2000 mS: 236918
LED HIGH
LED LOW
-----------
                          (press the button again)
Button OFF...
-----------
```

The loop counts are representative. The first count after a press is smaller than the following counts because it spans only the time from the press to the next two ticks rather than a full two second cycle.

### 6.7 What to observe

After the upload, the indicator LED is off, the onboard LED is off, and the monitor shows `Button OFF` once. Pressing the button lights the indicator LED immediately, because the class drives it directly from the latched flag, and the onboard LED begins blinking on the next timer tick. Pressing again turns the indicator LED off; the onboard LED finishes its cycle in the LOW state and `Button OFF` is printed once. Throughout, `loop()` continues to run at full speed, and both the button and the timer are serviced on every pass.

---

## 7. Verification

| Lab | Check | Expected result |
|-----|-------|-----------------|
| 1 | Serial Monitor at 9600 baud | `Number of Loops` advances by exactly one per blink; two seconds per line group |
| 1 | Onboard LED | One second on, one second off |
| 2 | Serial Monitor at 9600 baud | `Number of Loops` is on the order of one hundred thousand per interval |
| 2 | Onboard LED | Same one second on, one second off schedule as Lab 1 |
| 3 | Multimeter on D2 after upload | About 5 V released, 0 V pressed |
| 3 | Power up | Both LEDs off; `Button OFF` printed once |
| 3 | First press | Indicator LED on; onboard LED blinks; `Button ON` and a loop count printed each cycle |
| 3 | Second press | Indicator LED off; onboard LED ends LOW; `Button OFF` printed once |
| 3 | Rapid tapping | Each accepted press changes the indicator LED exactly once; no double toggles from contact bounce |

---

## 8. Troubleshooting

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| Build error mentioning multiple definitions of `setup` or `loop` | Two lab folders included in `build_src_filter` | Exactly one `+<N_Name/>` entry |
| Build error, no source files | `+<*>` missing from the filter | Restore the wildcard |
| Upload fails with a port error | Port not detected | Set `upload_port` in `platformio.ini` (see 3.3) |
| Serial Monitor shows nothing or garbage | Baud mismatch | Monitor at 9600; `monitor_speed = 9600` |
| Lab 3: indicator LED is on at power up, goes off when pressed | Button wired to 5 V with the default constructor | Wire the button to GND, or pass `false` as the third constructor argument |
| Lab 3: onboard LED never blinks | Button not latched on, or D2 wiring open | Check step 5 of 6.5 |
| Lab 3: LED toggles twice on one press | Debounce window too short for this button | `button.setDebounce(80)` in `setup()` |

---

## 9. What Carries Forward

`Timer.h` and `Button.h` are the same headers used by the full JUL firmware in `Code-JUL`. In that firmware the button is the enable switch for the motors, the timer paces the joystick read and the motor update, and `updateButton()` is called on every pass through `loop()` exactly as in Lab 3. A reader who can explain why Lab 2 counts one hundred thousand passes where Lab 1 counts one, and why Lab 3 completes its LOW half before honoring an off press, has the two ideas the rest of the series builds on: `loop()` must never block, and safety related outputs must be brought to a known state on every path through the code.

Experiment-2 wires the thumb joystick to the Uno and reads it with `Code-JUL/src/Step1_Joystick`.

---

## References

1. Arduino. delay(). Arduino Language Reference. https://docs.arduino.cc/language-reference/en/functions/time/delay/
2. Arduino. millis(). Arduino Language Reference. https://docs.arduino.cc/language-reference/en/functions/time/millis/
3. Arduino. pinMode() and INPUT_PULLUP. Arduino Language Reference. https://docs.arduino.cc/language-reference/en/functions/digital-io/pinMode/
4. MageMCU. Joystick-Uno-L298N repository, `Code-JUL/include/Timer.h` and `Button.h`. https://github.com/MageMCU/Joystick-Uno-L298N

MIT License. Carpenter Software, Jesse Carpenter.
