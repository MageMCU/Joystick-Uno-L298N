# Experiment-2: Wiring and Reading the Thumb Joystick

*Article 1004, Experiments for Joystick-Uno-L298N, STEM Starter Kit Series, Part 5. This guide is the text of the experiment in the article (DRAFT 3, 20261008). Labels such as Table-n, Code-n, Equation-n, and Circuit-n refer to the article; every Code-n listing is the main.cpp file named beside it in this repository.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

**Objective.** Determine, by measurement, which Uno input reads each joystick axis, in which direction each reading increases, and how the push button behaves, before any motor is connected.

**Builds on.** Experiment-1; Article 1001, the voltage divider and the ADC; Article 1009, Joystick Setup.

**Materials.** Thumb joystick module (GND, 5V, VRx, VRy, SW); one 10 kΩ resistor for SW; indicator LED and 220 Ω resistor; multimeter.

## Lab 1: Common.h, Headers.h, and the Preprocessor

**Objective.** Show what the preprocessor does with the debug flags of Common.h and with the #include lines of Headers.h. The preprocessor is the first stage of compilation; it carries out every line that begins with #, such as #include, #define, and #ifdef, and passes the resulting text to the compiler.

**Code.** Experiments/Experiment-2/Code/src/1_Preprocessor/main.cpp, Code-5. Uno and USB cable only. The program prints, for each of DEBUG_MAIN, DEBUG_JOYSTICK, DEBUG_L298N, and DEBUG_SERIAL_ON, whether the flag is defined, and the value of BUTTON_TIMER_mS.

**Prediction.** Read Common.h and predict the five printed lines with no flag defined, then with DEBUG_JOYSTICK defined.

1. Build and upload with the shipped settings. Record the printed lines and the Flash and RAM figures that PlatformIO reports at the end of the build.

2. Define DEBUG_JOYSTICK without editing Common.h: change the build_flags line of platformio.ini to build_flags = -std=gnu++11 -D DEBUG_JOYSTICK. Build, upload, and compare with the prediction. Record the new Flash and RAM figures, then restore the line.

3. Add a second source file, src/1_Preprocessor/second.cpp, that contains only the line #include "Headers.h". Build and record the first three errors that the linker reports, and the header file in which each reported function is defined. Delete second.cpp.

**Expected output and verification.** With no flag defined, every flag prints not defined and BUTTON_TIMER_mS is 100. With DEBUG_JOYSTICK defined, DEBUG_JOYSTICK and DEBUG_SERIAL_ON print defined and BUTTON_TIMER_mS becomes 3000, the slow interval that the drive program uses while it prints. In step 3 the linker reports a multiple definition of functions such as csjc::TypeConv::WordTo2Bytes(unsigned int), from TypeConv.h. An include guard (#ifndef, #define, #endif) prevents a header from being copied twice into one source file, but it does not prevent an ordinary function from being defined once in each source file, and C++ allows only one definition in the whole program: the one definition rule. A function template, a member function written inside its class, or a function marked inline may be defined in every source file that includes it. The drive program has one source file, so the rule is never broken there.

## Lab 2: LinearMap.h, One Formula, Three Types

**Objective.** Show how the type parameter of a class template changes the result of the same formula. A class template is a class written once with a type parameter, here T, from which the compiler generates a separate class for each type used, such as LinearMap<float> or LinearMap<int>.

**Code.** Experiments/Experiment-2/Code/src/2_LinearMap/main.cpp, Code-6. Uno and USB cable only. The program creates LinearMap<float>, LinearMap<long>, and LinearMap<int>, each with the ADC range 0 to 1023 and the PWM range −255 to 255, prints Map(x) from each for the inputs of Table-4, and then calls Reverse() on the joystick map of the drive program.

**Equation-1.** `y = (y2 − y1)(x − x1) / (x2 − x1) + y1`  
The formula of Map(): the input x in the range x1 to x2 is mapped onto the range y1 to y2.

**Table-4.** Map(x) for the three types, as printed by the Uno (confirmed in simulation of the ATmega328P). Signed integer overflow is undefined behavior in C++, so the int column is the result that avr-gcc produces, not a guaranteed value.

| x | float | long | int |
|---|---|---|---|
| 0 | −255.00 | −255 | −255 |
| 64 | −223.09 | −224 | −224 |
| 65 | −222.60 | −223 | −286 |
| 511 | −0.25 | −1 | −256 |
| 512 | 0.25 | 0 | −256 |
| 1023 | 255.00 | 255 | −257 |

**Prediction.** Cover the long and int columns of Table-4 and predict them from Equation-1.

1. Run the program and record all three columns beside the prediction.

2. Explain the long column. Integer division discards the fraction (truncation toward zero), so 511 and 512, which lie on either side of center, map to −1 and 0.

3. Explain the int column. On the Uno an int is 16 bits and holds −32768 to 32767. The product 510 × 65 = 33150 does not fit; this is integer overflow, and every result from x = 65 upward is wrong. On a desktop computer, where an int is 32 bits, the same code gives the long column.

4. Read the Reverse lines. Reverse() returns the ADC value that Map() started from: −1 gives 0, 0 gives 511.50, and 1 gives 1023.

**Expected output and verification.** The observed table agrees with Table-4. The drive program uses LinearMap<float> for both maps and converts the final command to int once, after the arithmetic is complete.

## Lab 3: Joystick Setup

**Objective.** Carry out Article 1009, Joystick Setup, with the Step1_Joystick program of Code-JUL, and add a multimeter check of the ADC.

**Wiring.** Circuit-2. VRx to A0, VRy to A1, SW to D2, and 5V and GND from the Uno. SW receives the external 10 kΩ resistor; step 1 measures the module to decide whether it is a pull up resistor (SW to 5 V) or a pull down resistor (SW to GND). Indicator LED anode to D12 through the 220 Ω resistor, cathode to GND. The line cord of the bench supply stays unplugged; the Uno is powered by USB only.

**Circuit-2.** Experiment-2, Lab 3. The joystick and the indicator LED on the Uno, powered by USB. [Circuit placeholder: Article 1009, Circuit-1, with the L298N and the motors omitted. VRx to A0, VRy to A1, SW to D2 with 10 kΩ to 5 V (or to GND per step 1), LED on D12 through 220 Ω, joystick 5V and GND from the Uno.]

**Code.** The Code-JUL folder, program Step1_Joystick, Article 1009, Code-1. Open the Code-JUL folder in Visual Studio Code and select Step1_Joystick with line 31 of platformio.ini:

```
build_src_filter = +<*> +<Step1_Joystick/> -<Step2_JUL/> -<Step3_MathLessons/>
```

Since the math lessons were added to Code-JUL, every setting of build_src_filter also excludes the folder Step3_MathLessons. The comments of platformio.ini list the line for each program.

**Prediction.** Before the grip is moved, write which printed value is expected to change when the grip moves left and right, and whether that value rises or falls when the grip moves right.

1. Measure the push button as a black box before it is wired to D2. With the joystick unpowered, set the multimeter to resistance and measure from SW to GND and from SW to 5V, released and pressed. If SW connects to GND when pressed, fit the 10 kΩ resistor from SW to 5 V (a pull up) and keep the Button as supplied, activeLow = true. If SW connects to 5V when pressed, fit the resistor from SW to GND (a pull down) and create the Button with activeLow = false, Button(buttonPin, ledPin, false), in Step1_Joystick and later in Step2_JUL (Article 1009, Joystick Setup, step 4). Record the result.

2. Carry out Article 1009, Joystick Setup, steps 1 to 5: prepare the bench, wire the joystick, select the program, define DEBUG_MAIN in Common.h, line 33, upload, test the push button, and turn the readings on.

3. Measure before reading. Turn the readings OFF with one press. Set the multimeter to DC volts and measure VRx to GND and VRy to GND with the grip at rest, then at each end of each axis. Record the voltages. Turn the readings ON.

4. Carry out Article 1009, Joystick Setup, steps 6 to 8: check the x axis, the x direction, and the y direction, and correct each one by changing the analogRead() lines, never a wire.

5. Compare each voltage of step 3 with its reading. For a reference voltage of about 5 V, the expected reading is given by Equation-2.

6. Carry out Article 1009, Joystick Setup, steps 9 and 10: record the pin of each axis, whether each axis is reversed, and the two readings at rest, three times. The supervisor signs the entry.

**Equation-2.** `N = (Vin / Vref) × 1023`  
Expected ADC reading N for an input voltage Vin and a reference voltage Vref of about 5 V.

**Expected output and verification.** At rest, both readings lie near 511 and change by a few counts between trials; the variation is quantization and noise, and the dead zone removes it later. Each axis spans close to 0 to 1023. Each measured voltage agrees with Equation-2 within a few percent; the difference comes from the actual reference voltage and the meter tolerance.

**Watch for.** A reading that never leaves 0 or 1023 (VRx or VRy on the wrong pin, or the joystick not powered). Readings that drift with no movement (a loose GND). A state that toggles by itself (the 10 kΩ resistor missing, so that D2 is a floating input, or activeLow that does not match the resistor; see step 1). No serial output (the baud rate is not 9600, or DEBUG_MAIN is not defined).


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
