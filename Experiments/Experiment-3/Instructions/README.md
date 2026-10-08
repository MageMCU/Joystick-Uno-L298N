# Experiment-3: L298N Single Motor

*Article 1004, Experiments for Joystick-Uno-L298N, STEM Starter Kit Series, Part 5. This guide is the text of the experiment in the article (DRAFT 3, 20261008). Labels such as Table-n, Code-n, Equation-n, and Circuit-n refer to the article; every Code-n listing is the main.cpp file named beside it in this repository.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

**Objective.** Measure the average voltage across one motor at several PWM duty cycles and compare it with the duty cycle equation of Article 1003.

**Builds on.** Experiment-2; Article 1003, Pulse Width Modulation and Board Connections; Article 1009, Measuring the Motor Bus and the L298N Drop.

**Materials.** L298N module; one DC motor rated for the motor bus; the bench power supply; multimeter.

## Lab 1: MiscMath.h, Sign and Magnitude

**Objective.** Study the helper functions that the L298N class uses to turn a signed command into a direction and a PWM value, and the limits of the int type.

A function template is a function written once with a type parameter; the compiler deduces the type from the arguments of each call. absT() returns the magnitude of a value of any numeric type. The L298N class writes the sign of a command to the IN pins and passes absT() of the command to analogWrite(). Overloading is the definition of several functions with the same name and different parameter lists; the compiler selects the one whose parameters match the arguments.

**Code.** Experiments/Experiment-3/Code/src/1_MiscMath/main.cpp, Code-7. Uno and USB cable only. The program prints absT<int>() of 255, −255, 0, −32767, and −32768; prints Map() of MiscMath.h for the ADC value 512 once with int arguments and once with float arguments; and calls the overloaded Debug() functions.

**Prediction.** Predict each absT() result, and predict the two Map() results from Table-4.

1. Run the program and record every line beside the prediction.

2. Explain absT<int>(−32768). An int on the Uno holds −32768 to 32767 in two's complement form, the binary representation in which the negative range is one value larger than the positive range. The value 32768 does not exist as an int, so the negation overflows, and the Uno returns −32768.

3. Map(512, 0, 1023, −255, 255) with int arguments returns −256, as LinearMap<int> did in Experiment-2. Change the second argument to 0.0f, build, and record the compiler error: no matching function for call to Map(int, float, int, int, int), with the note deduced conflicting types for parameter real (int and float). Restore the line.

4. Read the four Debug lines and name the version of Debug() that the compiler selected for each.

**Expected output and verification.** absT() gives the magnitude for every value except −32768. Map with int arguments prints −256 and with float arguments prints 0.25. Debug("Int and float", 3, 4.5f) uses the version with two type parameters, S and T, because the version with one type parameter T cannot be both int and float.

## Lab 2: One Motor and the Duty Cycle

**Objective.** Measure the average voltage across one motor at five duty cycles and compare it with Equation-4.

**Wiring.** Circuit-3. Follow Article 1009, L298N Setup, steps 1 to 4: power down and measure 0 V across the filter capacitor, remove the ENA, ENB, and 5 V regulator jumpers, wire D5 to D10 as listed in Table-1, and move the 5V and GND leads of the joystick to the 5 V bus and the common ground. Connect the one motor to either Motor A or Motor B. Secure the motor so that it cannot move, and keep fingers clear of the shaft.

**Circuit-3.** Experiment-3, Lab 2. The L298N wired as in Article 1009, Circuit-1, with one motor. [Circuit placeholder: Article 1009, Circuit-1, with one motor on Motor A or Motor B; the joystick, SW resistor, and indicator LED as in Experiment-2.]

**Code.** Experiments/Experiment-3/Code/src/2_DutyCycle/main.cpp, Code-8. The program sends the same command to the left and the right inputs of the L298N class, so the one motor turns on either output for any Bits() value; the pairing of the two channels is the subject of Experiment-4. The joystick push button, in latching mode, enables the output: while the state is OFF, PowerDownL298N() holds both enable inputs LOW. With the state ON, a key typed in the serial monitor selects the command: 0, 1, 2, 3, or 4 for a duty cycle of 0, 25, 50, 75, or 100 percent, f for forward, and r for reverse. A change of direction passes through zero for 300 ms before the new direction is applied, so the motor is never reversed at speed.

The duty cycle D of a PWM signal is the fraction of each period during which the signal is HIGH (Equation-3). The analogWrite() value v, from 0 to 255, sets D. The average voltage across the motor is approximately the duty cycle multiplied by the voltage that the bridge delivers when fully on, which is the motor bus voltage minus the drop of the two conducting transistors of the bridge (Equation-4).[5]

**Equation-3.** `D = ton / T = v / 255`  
Duty cycle from the on time ton and the period T, and from the analogWrite() value v.

**Equation-4.** `Vavg ≈ D × (VS − Vdrop)`  
Average motor voltage from the duty cycle D, the motor bus voltage VS, and the drop of the bridge Vdrop.

**Table-5.** Duty cycle record, copied into the notebook once for f and once for r.

| Key | analogWrite() | D | Vavg predicted | Vavg measured | Shaft turns |
|---|---|---|---|---|---|
| 0 | 0 | 0.00 |   |   |   |
| 1 | 64 | 0.25 |   |   |   |
| 2 | 128 | 0.50 |   |   |   |
| 3 | 191 | 0.75 |   |   |   |
| 4 | 255 | 1.00 |   |   |   |

**Prediction.** Using VS and the drop measured in Article 1009, Measuring the Motor Bus and the L298N Drop, steps 1 and 2, fill the predicted column of Table-5 before the motor is powered.

1. Upload the program with the bench supply unplugged. Confirm that the indicator LED is off and the serial monitor shows the start message.

2. Apply the motor bus last, as in Article 1009, Safety and Supervision.

3. Set the multimeter to DC volts across the two terminals of the motor.

4. Press the joystick button once (state ON). Send f, then 1. Record the meter reading and whether the shaft turns.

5. Repeat for 2, 3, and 4. Send 0, then repeat the four readings with r.

6. Press the joystick button once (state OFF) and confirm that the motor stops. Unplug the bench supply before any change of wiring.

**Expected output and verification.** The measured voltage rises in proportion to the duty cycle and agrees with Equation-4 within the meter tolerance, and its sign reverses with r. At a low duty cycle the motor may not turn although a voltage is present, because the motor needs a minimum voltage to overcome the friction of its gear train; record the lowest duty cycle at which it starts. A DC multimeter reads the average of a PWM waveform only approximately; record the meter model in the notebook. Experiment-7 returns to this measurement and finds the starting duty cycle with a line fit.

**Watch for.** A motor at full speed regardless of the key (an ENA or ENB jumper still fitted). No voltage at all (missing common ground, the motor bus not applied, or the button state OFF). The Uno resets when the motor starts (motor current returning through a logic ground path; check the ground wiring against Article 1009, Circuit-1). An L298N heat sink that becomes hot at a low duty cycle (stop and check the wiring).


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
