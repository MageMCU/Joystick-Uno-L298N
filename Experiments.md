# Experiments

The experiments of Article 1004, *Experiments for Joystick-Uno-L298N* (STEM Starter Kit Series, Part 5), Update 20261012 Rev 2. The article gives the objective, prediction, steps, and expected output of Experiments 1 to 5; each of their `Instructions/README.md` files is a lab card with the folders, filter lines, and wiring used at the bench. Experiments 6 to 9 are summarized in Part B of the article, and their `Instructions/README.md` files hold the full steps. The article refers to release v2.4.0 of this repository; schematics Circuit-1 to Circuit-4 are in [Experiments/Circuits](Experiments/Circuits).

## Changes in Release v3.2.0 (20261018)

Article 1004 still cites v2.4.0; the lab cards give the current names, lines, and settings.

- **Upload port, required.** Each project folder (`Experiments/Experiment-N/Code` and `Code-JUL`) needs its `upload_port` and `monitor_port` lines set to the port of the computer before the first upload; the upload does not work with automatic detection.
- **Push button, external 10 kOhm pull up required.** The author's bench test showed that the thumb joystick module has no resistor on SW. Every program that reads the joystick switch turns the internal pull up of D2 off (Step1_JUL, `ace.h`, Experiment-3 Lab 2, lesson 18), so the pull up of Circuit-2, from D2 to 5 V, must be fitted.
- **Debug flags on.** `Code-JUL/include/Common.h` ships with every debug flag on: Step1_JUL is the diagnostic program of Experiment-2 Lab 3 and Experiment-5 Lab 3 (3000 ms tick). Lessons 18 and 19 define `DEBUG_ALL_OFF` and are not affected.
- **Two ways to drive** after Experiment-5 Lab 3: Step1_JUL with the three debug flags commented out (100 ms tick), or Step2_Generator and Step3_Generated (50 ms tick). See the Experiment-5 lab card and `Code-JUL/README.md`.
- **Joystick lines.** Experiment-5 Lab 1 and lessons 17 and 19 read x on A0 and y on A1, as Step1_JUL since v3.1.0.

## Safety

Follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision, in every experiment. A supervising adult operates the bench power supply; the motor supply is applied last and removed first, and the line cord is unplugged before any change of wiring. Build success and simulation confirm the code only; they do not confirm that the wiring is safe or that the motors behave correctly. See the [Carpenter Software Disclaimer](https://github.com/MageMCU/MageMCU-Carpenter_Software-Disclaimer/blob/main/README_20260924.md).

## Part A: Core Experiments (original header files)

| Experiment | Labs | Code |
|------------|------|------|
| [Experiment-1: Timing and Button Input on the Uno](Experiments/Experiment-1/Instructions/README.md) | delay(), Timer.h, Button.h, Switch.h | `Experiments/Experiment-1/Code` |
| [Experiment-2: Wiring and Reading the Thumb Joystick](Experiments/Experiment-2/Instructions/README.md) | Preprocessor, LinearMap.h, Joystick and Button Check | `Experiments/Experiment-2/Code`; `Code-JUL` Step1_JUL with `DEBUG_JOYSTICK` |
| [Experiment-3: L298N Single Motor](Experiments/Experiment-3/Instructions/README.md) | MiscMath.h, duty cycle | `Experiments/Experiment-3/Code` |
| [Experiment-4: L298N Two Motors and the Bits Table](Experiments/Experiment-4/Instructions/README.md) | Bitwise.h, TypeConv.h, L298N.h on six LEDs, second motor | `Experiments/Experiment-4/Code` |
| [Experiment-5: Joystick to Motors](Experiments/Experiment-5/Instructions/README.md) | Vector3.h, Joystick.h, Step1_JUL and the Motor Movement Checklist | `Experiments/Experiment-5/Code`; `Code-JUL` Step1_JUL |

The `include/` folder of each core experiment holds copies of the original header files of `Code-JUL/include` (commit f2307a1), unchanged.

## Part B: Advanced Experiments (numerics)

| Experiment | Lessons in `Code-JUL/src/Step4_MathLessons` |
|------------|------|
| [Experiment-6: Statistics and the Dead Zone](Experiments/Experiment-6/Instructions/README.md) | 01 to 06, 17_DeadZone |
| [Experiment-7: Line Fit and Motor Calibration](Experiments/Experiment-7/Instructions/README.md) | 15_LineFit, 18_MotorLineFit |
| [Experiment-8: Vectors, Matrices, and the Joystick Frame](Experiments/Experiment-8/Instructions/README.md) | 07 to 13, 19_JoystickFrame |
| [Experiment-9: Quaternions](Experiments/Experiment-9/Instructions/README.md) | 14_Quaternion, 16_Rotation ([Article 1005](https://drive.google.com/file/d/1xQS_DkKx-wXtF7fm8C6GPfF8NV9Qoxnr)) |

## Lab Notebook

Every experiment records the date, the objective, the prediction written before the program is run, the observed output beside the expected output, and the signature of the supervisor where a step asks for it. Template: [Experiments/LAB-NOTEBOOK-TEMPLATE.md](Experiments/LAB-NOTEBOOK-TEMPLATE.md).
