//
// Carpenter Software
// File: main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step3_MathLessons/13_Matrix4x4
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestMatrix4x4.h (merged 20261008)
//
// By Jesse Carpenter (carpentersoftware.com)
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//

#include <Arduino.h>
#include "Debug.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

void Matrix4x4_T2_Translation()
{
    printTitle("Matrix4x4 T2 Translation");

}
// Working --------------------others constructors FIXME
void Matrix4x4_T1_Constructor()
{
    printTitle("Matrix4x4 T1 Constructor");

    Matrix4x4<float> M1;
    printMatrix4x4("M(): ", M1);

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    Matrix4x4<float> M2(array);
    printMatrix4x4("M(array): ", M2);

    float min = 0.001;
    float max = 0.999;
    Matrix4x4<float> M3(min, max);
    printMatrix4x4("M(0.001, 0.999): ", M3);
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Matrix4x4 tests, in order
    Matrix4x4_T1_Constructor();
    Matrix4x4_T2_Translation();
}

void loop()
{
}
