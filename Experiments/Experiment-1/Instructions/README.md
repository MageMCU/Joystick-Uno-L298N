# Experiment-1: Timing and Button Input on the Uno

*Article 1004, Experiments for Joystick-Uno-L298N, STEM Starter Kit Series, Part 5. This guide is the text of the experiment in the article (DRAFT 3, 20261008). Labels such as Table-n, Code-n, Equation-n, and Circuit-n refer to the article; every Code-n listing is the main.cpp file named beside it in this repository.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

**Objective.** Learn the timing pattern that every later program of the series depends on: loop() must never stop, and the program waits for an interval without stopping it.

**Builds on.** Article 1000, the platformio.ini file and the Blink sketch; Article 1002, push buttons, pull down resistors, and the serial monitor.

The drive program of this repository reads a joystick, runs a drive algorithm, and commands the L298N motor driver, all inside a single function called loop() that must never stop. Experiment-1 uses the Arduino Uno alone, with no motor driver, no motors, and no joystick. It has four labs. Lab 1 uses the Arduino delay() function to blink the onboard LED and shows what that function costs. Lab 2 replaces delay() with the Timer class from Timer.h, which waits for an interval while loop() continues to run. Lab 3 adds the Button class from Button.h and combines it with the Timer class, so that a push button turns the timed work on and off. Lab 4 reads the same push button with the Switch class from Switch.h, which does not debounce, and shows why the Button class does. The Timer and Button classes are the same classes used by the drive program in Code-JUL, so the student works with the tested code from the first lab.[1]

Two terms are used throughout. A blocking call is a function call that does not return until its work is finished; while it runs, nothing else in loop() can execute. A nonblocking design divides the work into short steps and returns from each step at once, so loop() can repeat many times per second and attend to several tasks in turn. Lab 1 is blocking. Labs 2, 3, and 4 are nonblocking.

The labs also introduce the two styles of code found in this repository. Each main.cpp is written in the procedural style of the C language: a sequence of statements and function calls. Timer.h and Button.h are written in the object oriented style of C++: a class bundles data and the functions that operate on that data into one unit, and the program creates an object of that class and calls its methods. A method is a function that belongs to a class. The main.cpp files call methods such as timer.isTimer() and button.updateButton() without needing to know how they are implemented.

## Materials

Labs 1 and 2 need only the Arduino Uno and a USB cable; the onboard LED on digital pin 13 is the only output. Labs 3 and 4 add a push button and an indicator LED on the breadboard (Table-3).

**Table-3.** Experiment-1 materials. The indicator LED is on D3 in this experiment because no L298N is connected; from Experiment-2 onward it is on D12, as in Article 1009, Circuit-1.

| Item | Qty | Used in | Note |
|---|---|---|---|
| Arduino Uno R3 | 1 | Labs 1 to 4 | Onboard LED on pin 13 |
| USB cable, Uno to computer | 1 | Labs 1 to 4 | Power, upload, and serial monitor |
| Breadboard and jumper wires | 1 set | Labs 3, 4 | Electronics Lab bench supplies |
| Tactile push button, momentary | 1 | Labs 3, 4 | Normally open; wired to digital pin 2 |
| Resistor, 10 kΩ, 1/4 W | 1 | Labs 3, 4 | Pull down resistor on the button pin |
| LED, 5 mm | 1 | Labs 3, 4 | Indicator LED on digital pin 3 |
| Resistor, 220 Ω, 1/4 W | 1 | Labs 3, 4 | Current limiting resistor for the indicator LED |

## Software Setup

The PlatformIO project for this experiment is the folder Experiments/Experiment-1/Code. Open that folder in Visual Studio Code. The four labs are the folders src/1_Delay, src/2_Timer, src/3_Button, and src/4_Switch, each with its own main.cpp, and the include folder holds Timer.h, Button.h, Switch.h, and the other original header files. The repository ships with Lab 1 selected:

```
build_src_filter = +<*> +<1_Delay/> -<2_Timer/> -<3_Button/> -<4_Switch/>
```

To run another lab, copy its line from the comments of platformio.ini, so that its folder has the plus sign and the other three have the minus sign. Without the wildcard +<*> the starting set would be empty and the exclusions would have nothing to act on. PlatformIO finds the serial port of the Uno automatically; the upload_port line is left as a comment and is set only if detection fails, for example /dev/ttyACM0 on Linux, /dev/cu.usbmodem followed by a board number on macOS, or COM3 on Windows.

Every lab prints to the serial port at 9600 baud. Baud is the signaling rate of the serial link, and the rate set in the program by Serial.begin(9600) must match the rate selected in the monitor. Open the PlatformIO serial monitor after each upload; the first line printed is Serial 9600 baudrate, which confirms that the rates match.

## Lab 1: The delay() Function

**Objective.** Blink the onboard LED once per two seconds with delay(), count how many times loop() runs, and observe that the count advances by exactly one per blink.

**Code.** Experiments/Experiment-1/Code/src/1_Delay/main.cpp, Code-1. No additional wiring.

The Arduino framework calls setup() once after power up or reset and then calls loop() repeatedly for as long as the board is powered. In setup(), Serial.begin() opens the serial port, the while (!Serial) loop waits until the port is ready, and pinMode() configures pin 13 as an output. In loop(), the global variable counter is printed and then incremented, so the first line reads Number of Loops: 0. The LED is turned on with digitalWrite(LED_PIN, HIGH), and delay(1000) then holds the processor for 1000 milliseconds. The delay() function is a blocking call: the processor executes nothing else in the program until the interval has elapsed.[3] The LED is turned off and a second delay(1000) follows. One pass through loop() therefore takes about two seconds.

**Prediction.** Write the first three values of Number of Loops and the time between them.

**Expected output and verification.** Number of Loops advances by exactly one per blink, and the LED is on for one second and off for one second. During each delay(1000) the program cannot read a sensor, sample a button, or update a motor command. In a robot, a blocking wait of one second means that a joystick released at the start of the wait is not noticed until the wait ends. Lab 2 removes this limitation.

## Lab 2: The Timer Class

**Objective.** Blink the onboard LED on the same schedule as Lab 1 without stopping loop(), and count how many times loop() runs during each one second interval.

**Code.** Experiments/Experiment-1/Code/src/2_Timer/main.cpp, Code-2, which includes Timer.h. No additional wiring.

Timer.h declares the class Timer inside the namespace csjc. A namespace is a named scope that keeps the class name from colliding with any other Timer in the program; the line using namespace csjc; lets the program write Timer instead of csjc::Timer. The class is built on millis(), an Arduino function that returns the number of milliseconds since the board was powered up as an unsigned long, a 32 bit unsigned integer.[4] The method isTimer(ms) returns true once each time ms milliseconds have elapsed since the previous time it returned true, and false on every other call. It never waits. The first call after construction or after resetTimer() arms the timer: it records the current millis() value as the starting point and returns false. Elapsed time is computed as now minus the recorded start with unsigned subtraction, so the comparison remains correct when millis() rolls over to zero after about 49.7 days. Timer.h also provides isTimerFixedRate(ms), which schedules each interval from the previous deadline rather than from the moment the timer fired, and deltaTimeSeconds(), which reports the measured length of the last interval; a given Timer object uses one policy or the other, not both.

The variable counter is incremented on every pass through loop(). The Boolean toggle records which half of the blink is due next. It starts false, so the second if block acts first: when isTimer(1000) fires, the LED is set LOW, toggle becomes true, and lastCount is set to the current counter value. One second later the first if block fires: it prints counter minus lastCount, the number of passes completed during the interval, sets the LED HIGH, and clears toggle. Each if condition tests toggle before calling isTimer(). Because the && operator evaluates its right operand only when the left operand is true, isTimer() is called from exactly one of the two blocks on any pass, so both blocks share one timer.

**Prediction.** Estimate the order of magnitude of Number of Loops per second.

**Expected output and verification.** The LED blinks on the same schedule as Lab 1, but loop() now runs on the order of one hundred thousand times per second instead of once per two seconds. The exact count depends on the board and on how many characters are printed during the interval. Every one of those passes is an opportunity to read an input or update an output; this is the pattern the drive program uses to sample the joystick and drive the motors while a timer paces the control update.

## Lab 3: The Button Class with the Timer Class

**Objective.** Use a push button to turn the timed blink of Lab 2 on and off, with an indicator LED that shows the button state, and confirm that both the button and the timer are serviced on every pass through loop().

**Code.** Experiments/Experiment-1/Code/src/3_Button/main.cpp, Code-3, which includes Timer.h and Button.h.

**Wiring.** Circuit-1 adds a push button and an indicator LED to the Uno. The button is wired with a pull down resistor: a resistor from the input pin to ground that holds the pin LOW while the button is open, so that the pin reads HIGH only while the button is pressed and connects it to 5 V.

**Circuit-1.** Experiment-1, Labs 3 and 4. The push button with its external pull down resistor on D2 and the indicator LED on D3. [Circuit placeholder: Uno 5V to one side of the push button; other side to D2; 10 kΩ from D2 to GND; D3 through 220 Ω to the LED anode, cathode to GND; Uno GND to the ground rail.]

1. Place the push button on the breadboard so that its two contact pairs straddle the center gap.

2. Wire one side of the button to the 5V pin of the Uno, and the other side to digital pin 2.

3. Wire the 10 kΩ resistor from digital pin 2 to the ground rail. This is the pull down resistor.

4. Wire the anode (longer leg) of the LED to digital pin 3 through the 220 Ω resistor, and the cathode (shorter leg, flat side of the case) to the ground rail.

5. Wire the GND pin of the Uno to the ground rail.

6. Before uploading, measure digital pin 2 with the multimeter: 0 V with the button released and about 5 V with the button held, following the measurement first approach of Article 1000.

Button.h declares the class Button in the csjc namespace. It converts the raw contact of a momentary switch into a clean on and off state. Debouncing addresses contact bounce: for a few milliseconds after a press or release, a mechanical contact chatters between open and closed, and a program that read the pin directly would see several presses. The class ignores a new pin level until it has held steady for the debounce window, 50 ms by default, and only then accepts it. Latching describes how accepted presses become an on and off flag. In the default latching mode, each accepted press toggles the flag, in the manner of a push on, push off power switch. The method isButtonOn() reports this flag, and the indicator LED on the pin given to the constructor follows it. The class also offers a momentary mode, selected with setLatching(false), in which the flag is on only while the button is held.

The constructor Button(buttonPin, ledPin, activeLow, debounceMs) records the pins and the wiring convention. With activeLow true, the default, a pressed button reads LOW and the class selects INPUT_PULLUP; with activeLow false, a pressed button reads HIGH and the class selects INPUT, for an external pull down resistor. The pull down wiring of Circuit-1 therefore needs Button(buttonPin, buttonLED, false), Code-3, line 48). The class configures its pins the first time updateButton() runs, so no begin() call is written in this program, and any pinMode() call written for the button pin in setup() would be replaced by that first call. The method updateButton() samples the pin and must be called on every pass through loop(); called only once per timer interval, it would miss a press shorter than the interval.

Each pass through loop() increments counter, calls button.updateButton(), and then reads the two conditions that drive everything else: buttonON, the latched state of the button, and tickON, whether the one second timer has fired on this pass. The outer if selects the on branch when the button is latched on or when a blink cycle is in its second half (!toggle). The second condition guarantees that a blink started while the button was on completes its LOW half even if the button is turned off in the middle of the cycle, so the LED never remains HIGH. The else branch runs while the button is off and no half cycle is pending: it waits for one timer tick, forces the LED LOW, prints Button OFF once, and clears the once flag. In the drive program, the same branch is where the motors are commanded to stop when the operator turns the enable button off.

**Prediction.** Describe the indicator LED, the onboard LED, and the serial output after the first press and after the second press.

**Expected output and verification.** After the upload, both LEDs are off and the monitor shows Button OFF once. Pressing the button lights the indicator LED at once and the onboard LED begins blinking on the next timer tick; each HIGH half prints a loop count for the two second cycle. Pressing again turns the indicator LED off; the onboard LED finishes its current cycle in the LOW state and Button OFF is printed once. Rapid tapping changes the indicator LED exactly once per accepted press.

## Lab 4: Switch.h and Contact Bounce

**Objective.** Show why the Button class debounces, and find a fault in the order of statements in the Switch constructor.

**Wiring.** Circuit-1, unchanged. The Switch class reads an input that is HIGH when pressed, which is the pull down wiring of Lab 3.

**Code.** Experiments/Experiment-1/Code/src/4_Switch/main.cpp, Code-4. The program creates the global object Switch pushSwitch(2, 3), calls updateSwitch() on every pass through loop(), counts every change of isSwitchOn() from false to true, and prints the count once per second when it changes.

**Prediction.** Press and release the button ten times. Predict the count.

1. Select Lab 4 in platformio.ini, upload, and press the button ten times. Record the count. Repeat three times.

2. Select Lab 3, upload, and press the button ten times with the same hand motion. Record the number of times the indicator LED toggles.

3. Return to Lab 4 and observe the indicator LED while the button is held. It lights faintly or not at all.

4. Read the constructor Switch(int switchPin, int ledPin) in include/Switch.h. It calls m_pins(), which runs pinMode(), before it assigns the two pin numbers. Move the call to m_pins() after the two assignments, upload, and confirm that the LED lights fully.

**Expected output and verification.** The Switch count is often greater than ten, because the contact opens and closes several times within a few milliseconds of each press, and loop() runs fast enough to see each closure. Lab 3 toggles exactly ten times, because the Button class accepts a new level only after it has held for 50 ms. In step 3, the LED pin was never set to OUTPUT: a global object is constructed before setup() runs, its members are zero before the constructor assigns them, so m_pins() configured pin 0 instead of pins 2 and 3. A digitalWrite(3, HIGH) on a pin that is still an input only connects the internal pull up resistor, which passes too little current to light the LED. The statements of a constructor run in the order written.

## What Carries Forward

In the drive program the button is the enable switch for the motors, the timer paces the joystick reading and the motor update, and updateButton() is called on every pass through loop() exactly as in Lab 3. A student who can explain why Lab 2 counts one hundred thousand passes where Lab 1 counts one, and why Lab 3 completes its LOW half before honoring an off press, has the two ideas that the rest of the series builds on: loop() must never block, and outputs that affect safety are brought to a known state on every path through the code.


## Related Articles

- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1005 Study of Quaternions](https://drive.google.com/file/d/1xQS_DkKx-wXtF7fm8C6GPfF8NV9Qoxnr)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)
- [1020 Note, Button.h and Timer.h](https://drive.google.com/file/d/1mLdqeahOOybPuAjdK8CqOVFJma677UWk)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
