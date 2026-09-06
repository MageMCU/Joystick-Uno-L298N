# Joystick-Uno-L298N, Experiment-1 Code

PlatformIO project for Experiment-1: Timing and Button Input on the Arduino Uno. Open this folder (`Experiments/Experiment-1/Code/`) in VS Code, not the repository root.

Reader instructions, wiring, and expected output are in [`../Instructions/README.md`](../Instructions/README.md).

## Three labs, one project

| Lab | Folder | Subject |
|-----|--------|---------|
| Lab 1 | `src/1_Delay/` | The `delay()` function and why it blocks `loop()` |
| Lab 2 | `src/2_Timer/` | The `Timer` class: waiting without blocking |
| Lab 3 | `src/3_Button/` | The `Button` class together with the `Timer` class |

Each lab folder is a complete program with its own `setup()` and `loop()`, so only one may be compiled at a time.

## Selecting a lab

Edit `build_src_filter` in `platformio.ini`. A leading `+` includes a folder and a leading `-` excludes it.

```
build_src_filter = +<*> +<1_Delay/> -<2_Timer/> -<3_Button/>
```

The wildcard `+<*>` includes the `src/` folder and everything under it as the starting set; the exclusions then remove the labs that are not wanted. Without the wildcard the starting set would be empty and the exclusions would have nothing to act on. The three settings are listed in the comments of `platformio.ini`.

## Headers

`include/Timer.h` and `include/Button.h` are copies of the files in `Code-JUL/include/`. They are copied so that this project has no dependency on any other folder.

## Serial port

`platformio.ini` leaves `upload_port` unset so PlatformIO detects the board. Set it only if detection fails; examples for Linux, macOS, and Windows are in the file. The Serial Monitor speed is 9600 baud (`monitor_speed = 9600`).

## C and C++ in this project

Each `main.cpp` is written in the procedural style of C: a sequence of statements and function calls. `Timer.h` and `Button.h` are written in the object oriented style of C++: a class bundles data and the functions (methods) that operate on it, and the sketch creates an object and calls its methods without needing to know how they are implemented.
