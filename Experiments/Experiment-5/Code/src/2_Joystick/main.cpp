//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: main.cpp
// Folder: Experiments/Experiment-5/Code/src/2_Joystick
// Github: MageMCU
// Repository: Joystick-Uno-L298N
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//
// Experiment-5, Lab 2: Joystick.h, test vectors.
// Uno and USB cable only.
//
// A test vector is a chosen input together with the output it must
// produce. Each input below is passed to UpdateInputs(), and Left(),
// Right(), and Octant() are printed beside the expected values of
// Article 1009, Image-5. The octant algorithm is verified before any
// motor turns.

#include <Arduino.h>
#include "Joystick.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

Joystick<float> joystick;
int failures = 0;

struct TestVector
{
    const char *name;
    float x, y;
    float left, right;
    int octant;
};

const TestVector tests[] = {
    {"Right Turn", 1, 0, 1, -1, 1},
    {"North-East", 1, 1, 1, 0, 1},
    {"Forward", 0, 1, 1, 1, 2},
    {"North-West", -1, 1, 0, 1, 4},
    {"Left Turn", -1, 0, -1, 1, 4},
    {"South-West", -1, -1, -1, 0, 5},
    {"Backward", 0, -1, -1, -1, 6},
    {"South-East", 1, -1, 0, -1, 8},
    {"Tolerance, stop", 0.0005, 0.0005, 0, 0, 0},
    {"Tolerance, octant 1", 0.002, 0, 0.002, -0.002, 1},
};

void runTest(const TestVector &t)
{
    joystick.UpdateInputs(t.x, t.y);
    float left = joystick.Left();
    float right = joystick.Right();
    int octant = joystick.Octant();
    bool pass = fabs(left - t.left) < 0.0001 && fabs(right - t.right) < 0.0001 && octant == t.octant;
    if (!pass)
        failures++;
    Serial.print(t.name);
    Serial.print("  expected [");
    Serial.print(t.left, 3);
    Serial.print(", ");
    Serial.print(t.right, 3);
    Serial.print("] octant ");
    Serial.print(t.octant);
    Serial.print("  observed [");
    Serial.print(left, 3);
    Serial.print(", ");
    Serial.print(right, 3);
    Serial.print("] octant ");
    Serial.print(octant);
    Serial.println(pass ? "  PASS" : "  FAIL");
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        /* code */
    }
    Serial.println("Serial 9600 baudrate");

    for (unsigned int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
    {
        runTest(tests[i]);
    }
    Serial.print("Failures: ");
    Serial.println(failures);

    // Step 3: each position lies on a boundary between two octants.
    // Move North-West by 0.01 to either side and print the octant.
    joystick.UpdateInputs(-1.0, 0.99);
    Serial.print("(-1.00, 0.99) octant ");
    Serial.println(joystick.Octant());
    joystick.UpdateInputs(-0.99, 1.0);
    Serial.print("(-0.99, 1.00) octant ");
    Serial.println(joystick.Octant());
}

void loop()
{
}
