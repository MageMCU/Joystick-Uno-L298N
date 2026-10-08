//
// Carpenter Software
// File: main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step3_MathLessons/11_Matrix2x2
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestMatrix2x2.h (merged 20261008)
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

void Matrix2x2_T13_Rotation()
{
    printTitle("Matrix2x2 T13 Rotation");
    
    // House centered at the origin (0, 0)
    //               *
    //            *  |  *
    // ---------------------------------
    //            *  |  *

    Vector2<float> aV[] {  {-1, -1},
                                {-1, 1},
                                {0, 2},
                                {1, 1},
                                {1, -1}  };
    Matrix2x2<float> R = R.Rotation(30 * DEG_TO_RAD);
    printMatrix2x2("R ", R);

    for (int i = 0; i < 5; i++)
    {
        Serial.print("Was-aV[");
        Serial.print(i);
        printVector2("]: ", aV[i]);

        aV[i] = R * aV[i];

        Serial.print("Rot-aV[");
        Serial.print(i);
        printVector2("]: ", aV[i]);
    }
    // Draw the points on  eng. note-pad...
    // Rotates CCW around the origin (0, 0).
}

void Matrix2x2_T12_Identity()
{
    printTitle("Matrix2x2 T12 Identity");
    
    Matrix2x2<float> M1((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("M1 ", M1);
    
    // By using the default constructor as shown below,
    // the matrix is not zeros but an identity matrix 2x2...
    Matrix2x2<float> I;
    printMatrix2x2("I ", I);

    Matrix2x2<float> M2 = M1 * I;
    printMatrix2x2("M2 = M1 * I ", M2);
    
}

void Matrix2x2_T11_MatrixMatrixMultiplication()
{
    printTitle("Matrix2x2 T11 operator*(Matrix2x2 M)");
    
    Matrix2x2<float> M1((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("M1 ", M1);
    
    Matrix2x2<float> M2((float)-4, (float)1, (float)8, (float)5);
    printMatrix2x2("M2 ", M2);

    // 3 2   -4 1     3(-4) + 2(8) =  4; 3(1) + 2(5) = 13        4  13
    // 2 4    8 5     2(-4) + 4(8) = 24; 2(1) + 4(5) = 22       24  22

    Matrix2x2<float> M3 = M1 * M2;
    printMatrix2x2("M1 * M2 = M3: ", M3);

    printSubTitle("Non-communitive");
    Matrix2x2<float> M4 = M2 * M1;
    printMatrix2x2("M2 * M1 = M4: ", M4);
}

void Matrix2x2_T10_MatrixVectorMultiplication()
{
    printTitle("Matrix2x2 T10 Matric Vector Multiplication");
    
    Matrix2x2<float> M((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("Original M: ", M);
    Vector2<float> v(1, 1);
    printVector2("v(1, 1): ", v);
    printVector2("M*v: ", M*v);
}

void Matrix2x2_T9_MatrixScalarMultiplication()
{
    printTitle("Matrix2x2 T9 operator*(real s)");
    
    Matrix2x2<float> M((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("Original M: ", M);
    float s = (float)-0.5;
    printResult("Scalar: ", s);
    printMatrix2x2("M*s: ", M*s);
}

void Matrix2x2_T8_UnitaryOperation()
{
    printTitle("Matrix2x2 T8 operator-()");
    
    Matrix2x2<float> M((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("Original M: ", M);
    printMatrix2x2("Unitary Operator -M: ", -M);
}

void Matrix2x2_T7_Solve()
{
    printTitle("Matrix2x2 T7 Solve");
    // Note: Compare with T6 Inverse...
    Matrix2x2<float> A((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("A: ", A);
    Vector2<float> b(5, -2);
    printVector2("b: ", b);

    Vector2<float> x = A.Solve(b);
    printVector2("Ax = b; solve: x: ", x);

    Serial.println("Check if c = b");
    Vector2<float> c = A*x;
    printVector2("A*x = c:", c);
}

void Matrix2x2_T6_Inverse()
{
    printTitle("Matrix2x2 T6 Inverse");
    // Note: Compare with T7 Solve...
    Matrix2x2<float> m1((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("Original", m1);
    Matrix2x2<float> inverse = m1.Inverse();
    printMatrix2x2("Inverse", inverse);

    Vector2<float> b(5, -2);
    printVector2("b: ", b);

    Vector2<float> x = inverse * b;
    printVector2("inverse * b = x: ", x);
}

void Matrix2x2_T5_Transpose()
{
    printTitle("Matrix2x2 T5 Transpose");

    Matrix2x2<float> m1((float)1, (float)2, (float)3, (float)4);
    printMatrix2x2("Original", m1);
    printMatrix2x2("Transpose", m1.Transpose());
}

void Matrix2x2_T4_Invertible()
{
    printTitle("Matrix2x2 T3 Invertible");

    Matrix2x2<float> m1((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("m1: ", m1);
    if (m1.Invertible())
        Serial.println("m1 Invertible");
    else
        Serial.println("m1 NOT Invertible");

    Matrix2x2<float> m2((float)1, (float)2, (float)2, (float)4);
    printMatrix2x2("m2: ", m2);
    if (m2.Invertible())
        Serial.println("m2 Invertible");
    else
        Serial.println("m2 NOT Invertible");
}

void Matrix2x2_T3_Determinate()
{
    printTitle("Matrix2x2 T4 Determinate");

    Matrix2x2<float> m1((float)1, (float)3, (float)-2, (float)5);
    printMatrix2x2("m1: ", m1);
    float det = m1.Determinant();
    printResult("det: ", det);
    
    Matrix2x2<float> m2((float)2, (float)1, (float)10, (float)5);
    printMatrix2x2("m2: ", m2);
    det = m2.Determinant();
    printResult("det: ", det);
    
    Matrix2x2<float> m3((float)-3, (float)3, (float)-7, (float)5);
    printMatrix2x2("m3: ", m3);
    det = m3.Determinant();
    printResult("det: ", det);
}

void Matrix2x2_T2_Getters()
{
    printTitle("Matrix2x2 T2 Getters");

    Matrix2x2<float> m1((float)1, (float)2, (float)3, (float)4);

    Serial.print(String(m1.E00(), 2));
    Serial.print(" ");
    Serial.println(String(m1.E01(), 2));

    Serial.print(String(m1.E10(), 2));
    Serial.print(" ");
    Serial.println(String(m1.E11(), 2));

    float index = m1.GetIndex(1, 0);
    Serial.print("index = m1.GetIndex(1, 0): ");
    Serial.println(String(index, 0));

    float element = m1.GetElement(index);
    Serial.print(" element = m1.GetElement(index): ");
    Serial.println(String(element, 2));

    m1.SetElement(index, (float)3.67);
    Serial.println("m1.SetElement(index, (float)3.67)");

    element = m1.GetElement(1, 0);
    Serial.print("element = m1.GetElement(1, 0): ");
    Serial.println(String(element, 2));
}

void Matrix2x2_T1_Constructor()
{
    printTitle("Matrix2x2 T1 Constructor");

    Matrix2x2<float> m1;
    printMatrix2x2("m1", m1);

    Matrix2x2<float> m2((float)1, (float)2, (float)3, (float)4);
    printMatrix2x2("m2((float)1, (float)2, (float)3, (float)4): ", m2);


    float array[] = {1, 2, 3, 4};
    Matrix2x2<float> m3(array);
    printMatrix2x2("m3(array[] = {1, 2, 3, 4}): ", m3);
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Matrix2x2 tests, in order
    Matrix2x2_T1_Constructor();
    Matrix2x2_T2_Getters();
    Matrix2x2_T3_Determinate();
    Matrix2x2_T4_Invertible();
    Matrix2x2_T5_Transpose();
    Matrix2x2_T6_Inverse();
    Matrix2x2_T7_Solve();
    Matrix2x2_T8_UnitaryOperation();
    Matrix2x2_T9_MatrixScalarMultiplication();
    Matrix2x2_T10_MatrixVectorMultiplication();
    Matrix2x2_T11_MatrixMatrixMultiplication();
    Matrix2x2_T12_Identity();
    Matrix2x2_T13_Rotation();
}

void loop()
{
}
