//
// Carpenter Software
// File: main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step3_MathLessons/12_Matrix3x3
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestMatrix3x3.h (merged 20261008)
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

void Matrix3x3_Find_Invertible_Matrix()
{
    printTitle("Matrix3x3 Find Invertiable Matrix");
    printSubTitle("Learning tool for parents & teachers...");

    // Updated seed for repeating different
    // values...
    unsigned long seed = analogRead(A0);
    seed += analogRead(A1);
    seed += micros();
    randomSeed(seed);

    // Random integers for Matrix A
    float aM[9];
    for (int i = 0; i < 9; i++)
    {
        // Skip any zeros
        do
        {
            aM[i] = random(18) - 9;
        } while (aM[i] == (float)0);
    }

    // Matrix A
    Matrix3x3<float> A(aM);
    printMatrix3x3("A(aM): ", A);

    // Inverse of Matrix A
    Matrix3x3<float> Ainv = A.Inverse();
    printMatrix3x3("Ainv: ", Ainv);

    // Ramdom integers for Vector x
    float aV[3];
    for (int i = 0; i < 3; i++)
    {
        // Skip any zeros
        do
        {
            aV[i] = random(10) - 5;
        } while (aV[i] == (float)0);
    }

    // Vector x
    Vector3<float> x(aV);
    printVector3("x(aV): ", x);

    // Calculate Vector b
    Vector3<float> b = A * x;
    printVector3("b = A * x: ", b);


    // Compare, Solve and Check
    if (A.Invertible())
    {
        Serial.println("Invertible");

        x = Ainv.Solve(b);
        printVector3("x = Ainv.Solve(b): ", x);

        x = A.Cramer(b);
        printVector3("x = A.Cramer(b): ", x);
    }
}

void Matrix3x3_T14_Rotation()
{
    printTitle("Matrix3x3 T14 Rotation");

    // In Development --------------------- FIXME
    // working one-direction only (CCW)
    float radian = (float)45 * DEG_TO_RAD;

    Matrix3x3<float> A; // identity
    printMatrix3x3("A ", A);

    // CAUTION: DO NOT USE ALL AT ONCE... STACK-HEAP COLLISION
    // Could multiply same matrix instead of all five...

    // Rotate about x-axis (radian measure)
    // Matrix3x3<float> Rx = A.Rotation(radian, 0, 0);
    // printMatrix3x3("Rx ", Rx);

    // Rotate about y-axis (radian measure)
    // Matrix3x3<float> Ry = A.Rotation(0, radian, 0);
    // printMatrix3x3("Ry ", Ry);

    // Rotate about z-axis (radian measure)
    // Matrix3x3<float> Rz = A.Rotation(0, 0, radian);
    // printMatrix3x3("Rz ", Rz);

    // Rotate about all-axes (XYZ) order (radian measure)
    // The matrix multiplication order relative to the (XYZ) order
    // not yet tested....
    Matrix3x3<float> ALL = A.Rotation(radian, radian, radian);
    printMatrix3x3("ALL ", ALL);
}

void Matrix3x3_T13_Identity()
{
    printTitle("Matrix3x3 T13 Identity");

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M(array);
    printMatrix3x3("M ", M);

    // By using the default constructor as shown below,
    // the matrix is not zeros but an identity matrix 3x3...
    Matrix3x3<float> I;
    printMatrix3x3("I ", I);

    Matrix3x3<float> M1 = M * I;
    printMatrix3x3("M1 = M * I ", M1);
}

void Matrix3x3_T12_MatrixMatrixMultiplication()
{
    printTitle("Matrix3x3 T12 Matrix Matrix Multiplication");

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M(array);
    printMatrix3x3("M: ", M);
    Matrix3x3<float> I;
    printMatrix3x3("I: ", I);
    printMatrix3x3("M*I: ", M * I);

    // A * Ainv = I (should get the identity)
    float array1[] = {1, 2, 1, 2, 2, 1, 1, 2, 3};
    Matrix3x3<float> A(array1);
    printMatrix3x3("A(array1): ", A);
    Matrix3x3<float> Ainv = A.Inverse();
    printMatrix3x3("Ainv: ", Ainv);
    printMatrix3x3("A*Ainv: ", A * Ainv);
}

void Matrix3x3_T11_MatrixVectorMultiplication()
{
    printTitle("Matrix3x3 T11 Matrix Vector Multiplication");

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M(array);
    printMatrix3x3("Original M: ", M);
    Vector3<float> v(1, 1, 1);
    printVector3("v(1, 1, 1): ", v);
    printVector3("M*v: ", M * v);
}

void Matrix3x3_T10_MatrixScalarMultiplication()
{
    printTitle("Matrix3x3 T10 Matrix Scalar Multiplication");

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M(array);
    printMatrix3x3("Original M: ", M);
    float s = (float)-0.5;
    printResult("Scalar: ", s);
    printMatrix3x3("M*s: ", M * s);
}

void Matrix3x3_T9_UnitaryOperation()
{
    printTitle("Matrix3x3 T9 Minus operator-()");

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M(array);
    printMatrix3x3("Original M: ", M);
    printMatrix3x3("Unitary Operator -M: ", -M);
}

void Matrix3x3_T8_Solve()
{
    printTitle("Matrix3x3 T8 Solve (+Cramer)");

    float array[] = {1, 2, 1, 2, 2, 1, 1, 2, 3};
    Matrix3x3<float> A(array);
    printMatrix3x3("A(array): ", A);

    Vector3<float> b(5, 6, 9);
    printVector3("b(5, 6, 9): ", b);

    Matrix3x3<float> Ainv = A.Inverse();
    printMatrix3x3("*Ainv: ", Ainv);

    // Solve Ax = b; x = Ainv(b)
    Vector3<float> x = Ainv.Solve(b);
    printVector3("Ainv.Solve(b): ", x);

    // ALternate Solution
    x = A.Cramer(b);
    printVector3("A.Cramer(b): ", x);
}

void Matrix3x3_T7_Inverse()
{
    printTitle("Matrix3x3 T7 Inverse");

    float array[] = {2, 1, 2, 3, 2, 2, 1, 2, 3};
    Matrix3x3<float> M(array);
    printMatrix3x3("M(array): ", M);
    M = M.Inverse();
    printMatrix3x3("M.Inverse(): ", M);
    // Verified Output
}

void Matrix3x3_T6_Adjoint()
{
    printTitle("Matrix3x3 T6 Adjoint");

    float array[] = {2, 1, 2, 3, 2, 2, 1, 2, 3};
    Matrix3x3<float> M(array);
    printMatrix3x3("M(array): ", M);
    M = M.Adjoint();
    printMatrix3x3("M.Adjoint(): ", M);
    // Verified Output
    // 2.00 1.00 -2.00
    // -7.00 4.00 2.00
    // 4.00 -3.00 1.00
}

void Matrix3x3_T5_Transpose()
{
    printTitle("Matrix3x3 T5 Transpose");

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M(array);
    printMatrix3x3("M(array): ", M);
    M = M.Transpose();
    printMatrix3x3("M.Transpose(): ", M);
}

void Matrix3x3_T4_Invertible()
{
    printTitle("Matrix3x3 T4 Invertible");

    float min = -1.0;
    float max = 1.0;
    Matrix3x3<float> M(min, max);
    printMatrix3x3("M(-1.0, 1.0): ", M);
    float det = M.Determinant();
    printResult("det: ", det);
    if (M.Invertible())
        Serial.println("M is invertible...");
    else
        Serial.println("M is NOT invertible...");
}

void Matrix3x3_T3_Determinate()
{
    printTitle("Matrix3x3 T3 Determinate");

    float min = -9.0;
    float max = 9.0;
    Matrix3x3<float> M(min, max);
    printMatrix3x3("M(-9.0, 9.0): ", M);
    float det = M.Determinant();
    printResult("det: ", det);
}

void Matrix3x3_T2_Access()
{
    printTitle("Matrix3x3 T2 Access");

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M(array);
    printMatrix3x3("M(array): ", M);
    int index = M.GetIndex(0, 1);
    float element = M.GetElement(index);

    Serial.print("M.GetElement(");
    Serial.print(index);
    printResult("): ", element);

    M.SetElement(1, 2.05);
    printMatrix3x3("M.SetElement(1, 2.05): ", M);
}

void Matrix3x3_T1_Constructor()
{
    printTitle("Matrix3x3 T1 Constructor");

    Matrix3x3<float> M1;
    printMatrix3x3("M(): ", M1);

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M2(array);
    printMatrix3x3("M(array): ", M2);

    float min = 0.001;
    float max = 0.999;
    Matrix3x3<float> M3(min, max);
    printMatrix3x3("M(0.001, 0.999): ", M3);
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Matrix3x3 tests, in order
    Matrix3x3_T1_Constructor();
    Matrix3x3_T2_Access();
    Matrix3x3_T3_Determinate();
    Matrix3x3_T4_Invertible();
    Matrix3x3_T5_Transpose();
    Matrix3x3_T6_Adjoint();
    Matrix3x3_T7_Inverse();
    Matrix3x3_T8_Solve();
    Matrix3x3_T9_UnitaryOperation();
    Matrix3x3_T10_MatrixScalarMultiplication();
    Matrix3x3_T11_MatrixVectorMultiplication();
    Matrix3x3_T12_MatrixMatrixMultiplication();
    Matrix3x3_T13_Identity();
    Matrix3x3_T14_Rotation();
    Matrix3x3_Find_Invertible_Matrix();
}

void loop()
{
}
