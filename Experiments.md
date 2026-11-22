# Experiments

The experiments of Article 1004, *Experiments for Joystick-Uno-L298N* (STEM Starter Kit Series, Part 5), revised November 21, 2026. The article gives the objective, prediction, steps, and expected output of Experiments 1 to 5; each of their `Instructions/README.md` files is a lab card with the folders, filter lines, and wiring used at the bench. Experiments 6 to 9 are summarized in Part B of the article and Experiments 10 to 12 in Part C, and their `Instructions/README.md` files hold the full steps. The article refers to release v7.5.2 of this repository; schematics Circuit-1, Circuit-1b, and Circuit-2 to Circuit-7 are in [Experiments/Circuits](Experiments/Circuits).

## Safety

Follow [Article 1009](https://drive.google.com/file/d/1aoN7Wy96OosGRiRH86_kl4rql6KzG3AJ), Safety and Supervision, in every experiment. A supervising adult operates the bench power supply; the motor supply is applied last and removed first, and the line cord is unplugged before any change of wiring. Build success and simulation confirm the code only; they do not confirm that the wiring is safe or that the motors behave correctly. See the [Carpenter Software Disclaimer](https://github.com/MageMCU/MageMCU-Carpenter_Software-Disclaimer/blob/main/README_20260924.md).

## Part A: Core Experiments (original header files)

| Experiment | Labs | Code |
|------------|------|------|
| [Experiment-1: Timing and Button Input on the Uno](Experiments/Experiment-1/Instructions/README.md) | delay(), Timer.h, Button.h, Switch.h | `Experiments/Experiment-1/Code` |
| [Experiment-2: Wiring and Reading the Thumb Joystick](Experiments/Experiment-2/Instructions/README.md) | Preprocessor, LinearMap.h, reading the joystick in Step2_JUL | `Experiments/Experiment-2/Code`; `Code-JUL` Step2_JUL with `DEBUG_STEP2_JOYSTICK` (the Step1_Joystick self test checks the connections first) |
| [Experiment-3: L298N Single Motor](Experiments/Experiment-3/Instructions/README.md) | MiscMath.h, duty cycle | `Experiments/Experiment-3/Code` |
| [Experiment-4: L298N Two Motors and the Bits Table](Experiments/Experiment-4/Instructions/README.md) | Bitwise.h, TypeConv.h, L298N.h on six LEDs, second motor | `Experiments/Experiment-4/Code` |
| [Experiment-5: Joystick to Motors](Experiments/Experiment-5/Instructions/README.md) | Vector3.h, Joystick.h, Step2_JUL and the Motor Movement Checklist | `Experiments/Experiment-5/Code`; `Code-JUL` Step2_JUL |

The `include/` folder of each core experiment holds copies of the original header files of `Code-JUL/include` (commit f2307a1). Their compiled code is unchanged; since then comments changed in `Timer.h` (folder line), `Button.h` (v4.0.1), and `Common.h` (v6.1.3), and two local variables of `L298N.h` were renamed (v6.2.2). `Button.h`, `Timer.h`, and `Switch.h` are identical to the files in `Code-JUL/include`; the others keep the code of that commit.

## Part B: Advanced Experiments (numerics)

| Experiment | Lessons in `Code-JUL/src/Step5_MathLessons/lessons` (select with `#define LESSON` and `#define TOPIC` in `main.cpp`) |
|------------|------|
| [Experiment-6: Statistics and the Dead Zone](Experiments/Experiment-6/Instructions/README.md) | L01 to L06, L17_DeadZone |
| [Experiment-7: Line Fit and Motor Calibration](Experiments/Experiment-7/Instructions/README.md) | L15_LineFit, L18_MotorLineFit |
| [Experiment-8: Vectors, Matrices, and the Joystick Frame](Experiments/Experiment-8/Instructions/README.md) | L07 to L13, L19_JoystickFrame |
| [Experiment-9: Quaternions](Experiments/Experiment-9/Instructions/README.md) | L14_Quaternion, L16_Rotation (Article 1005, on [carpentersoftware.com, Projects, Robotics](https://carpentersoftware.com/pages/projects/robotics/robotics.html)) |

## Part C: Circuit-4 Experiments (Step6_Circuit)

Built after Article 1009, Appendix C, Circuit-4, and both tests of Step6_Circuit, in order from the easiest to the most difficult: measurements only, then the switch under load, then the battery. A supervising adult operates every supply.

| Experiment | Program and switches | Figure |
|------------|----------------------|--------|
| [Experiment-10: The Bus Monitor](Experiments/Experiment-10/Instructions/README.md) | Step6_Circuit, `STEP6_CIRCUIT`, `STEP6_LAB`, variac supply | [Circuit-5](Experiments/Circuits/Circuit-5.svg) |
| [Experiment-11: The Motor Power Switch](Experiments/Experiment-11/Instructions/README.md) | Step6_Circuit, `STEP6_CIRCUIT` then `STEP6_MOTORS`, `STEP6_LAB` | [Circuit-6](Experiments/Circuits/Circuit-6.svg) |
| [Experiment-12: The Robot Supply](Experiments/Experiment-12/Instructions/README.md) | Step6_Circuit, `STEP6_CIRCUIT` then `STEP6_MOTORS`, `STEP6_ROBOT` | [Circuit-7](Experiments/Circuits/Circuit-7.svg) (TP11 since v7.4.1) |

## Lab Notebook

Every experiment records the date, the objective, the prediction written before the program is run, the observed output beside the expected output, and the signature of the supervisor where a step asks for it. Template: [Experiments/LAB-NOTEBOOK-TEMPLATE.md](Experiments/LAB-NOTEBOOK-TEMPLATE.md).
