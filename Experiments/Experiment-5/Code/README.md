# Experiment-5 Code

PlatformIO project for Article 1004, Experiment-5. Open this `Code` folder in VS Code, not the repository root.

- `include/`: copies of the original header files of `Code-JUL/include` (commit f2307a1), unchanged. Labs that ask for a correction change the copy here, never the file in Code-JUL.
- `src/`: one folder per lab: 1_Vector3 2_Joystick 
- `platformio.ini`: select one lab with `build_src_filter`; the comments list the line for every lab. **Required before the first upload (since v3.2.0):** remove the comment mark from the `upload_port` and `monitor_port` lines and set both to the port of your computer (`pio device list` prints the ports); the upload does not work with automatic detection.

Serial monitor: 9600 baud. Steps, predictions, and expected output: Article 1004, under the heading of each lab. Files and filter lines at the bench: [Instructions/README.md](../Instructions/README.md).
