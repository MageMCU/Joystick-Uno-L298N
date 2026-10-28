//
// Carpenter Software
// File: L13_Matrix4x4.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L13_Matrix4x4, selected with LESSON 13 in
// Step5_MathLessons/main.cpp
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
// RELEASE
//   2026-10-28  v6.8.0
//   L13_Matrix4x4.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

// TEACHING NOTES (v6.1.1)
// Lesson 13: 4 x 4 matrices and homogeneous coordinates, explained in
// include/numerics/Matrix4x4.h: a fourth coordinate w = 1 lets one
// matrix both rotate and move (translate) a point.
// The topics run T01 then T02 (see Setup()).
#ifndef Lesson_L13_Matrix4x4_h
#define Lesson_L13_Matrix4x4_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 2

#include <Arduino.h>
#include "Debug.h"

namespace L13_Matrix4x4
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// T02 (written 20261022, v6.1.2; Discrepancies.md, 159): the
// translation matrix of v = (1, 2, 3) is the identity with v in the
// last column. It moves the point (0, 0, 0) to (1, 2, 3) and the point
// (4, 5, 6) to (5, 7, 9). A point is written with the fourth
// coordinate w = 1 (homogeneous coordinates, Matrix4x4.h), and each
// component of T p is the dot product of one row of T with p.
// ---------------------------------------------------------------
// Matrix4x4_T02_Translation (teaching notes, v6.3.0)
// Hint: Translation, move points with a matrix.
// Purpose: why 3D graphics and robotics use 4 x 4 matrices: one matrix
// can rotate and also move (translate) a point.
// What is learnt:
//   Translation    adding the same vector to every point; a 3 x 3 matrix
//                  cannot do it, because it always maps (0, 0, 0) to itself.
//   Homogeneous coordinates  a point (x, y, z) is written (x, y, z, 1).
//                  The 1 multiplies the last column of T, which holds the
//                  move (1, 2, 3).
//   Two dimensional array  float points[2][4]: two rows of four values;
//                  points[k][col] reads row k, column col.
//   Nested loops   the outer loop picks a row of T, the inner loop forms
//                  the dot product of that row with the point.
//   Conditional operator  i < 3 ? F(", ") : F(") = (") chooses one of two
//                  texts.
//   Construction note  Translation() is a member function called on I, a
//                  finished identity matrix (see lesson 11, topic 13).
// Expected output:
//   T = I.Translation(v): the identity with 1, 2, 3 in the last column
//   T * (0, 0, 0, 1) = (1, 2, 3, 1)
//   T * (4, 5, 6, 1) = (5, 7, 9, 1)
// ---------------------------------------------------------------
void Matrix4x4_T02_Translation()
{
    printTitle(F("Matrix4x4 T02 Translation"));

    Vector3<float> v(1, 2, 3);
    printVector3("v", v);
    // Translation() is called on a finished object, the identity I (v6.3.1;
    // up to v6.3.0 Matrix4x4<float> T = T.Translation(v) called it on T
    // while T was still being built; Discrepancies.md, 193).
    Matrix4x4<float> I;
    Matrix4x4<float> T = I.Translation(v);
    printMatrix4x4(F("T = I.Translation(v): "), T);

    // Two points, each (x, y, z, 1)
    float points[2][4] = {{0, 0, 0, 1}, {4, 5, 6, 1}};
    for (int k = 0; k < 2; k++)
    {
        float moved[4];
        for (int row = 0; row < 4; row++)
        {
            moved[row] = 0;
            for (int col = 0; col < 4; col++)
                moved[row] += T.GetElement(row, col) * points[k][col];
        }
        Serial.print(F("T * ("));
        for (int i = 0; i < 4; i++)
        {
            Serial.print(points[k][i], 0);
            Serial.print(i < 3 ? F(", ") : F(") = ("));
        }
        for (int i = 0; i < 4; i++)
        {
            Serial.print(moved[i], 0);
            Serial.print(i < 3 ? F(", ") : F(")"));
        }
        Serial.println();
    }
}
// Working --------------------others constructors FIXME
// T01: the identity (1 on the diagonal), a matrix filled row by row
// from 1 to 16, and a random matrix with elements from 0.001 to 0.999.
// ---------------------------------------------------------------
// Matrix4x4_T01_Constructor (teaching notes, v6.3.0)
// Hint: Constructor, build a 4 x 4 matrix.
// Purpose: how to declare and instantiate Matrix4x4 variables, and the
// getters and the setter of its 16 elements.
// What is learnt:
//   Constructors (overloads):
//     Matrix4x4<float> M1;               default: the identity
//     Matrix4x4<float> M2(array);        16 values in row major order
//     Matrix4x4<float> M3(min, max);     16 random values
//     Matrix4x4<float> M4(m2);           a Matrix2x2 (or a Matrix3x3) in
//                                        the upper left corner of the
//                                        identity
//   Converting constructor  a constructor with one parameter of another
//                  type builds a Matrix4x4 from a Matrix2x2.
//   Getters        GetIndex(row, col) = row * 4 + col; GetElement(index)
//                  and GetElement(row, col).
//   Setter         SetElement(index, value).
// Expected output:
//   M(): the identity   M(array): rows 1 to 4, 5 to 8, 9 to 12, 13 to 16
//   M(0.001, 0.999): random values
//   M(m2): 1.00 2.00 0.00 0.00 / 3.00 4.00 0.00 0.00 / then the identity rows
//   M2.GetIndex(2, 3): 11   M2.GetElement(index): 12.00
//   After M2.SetElement(index, -1), M2.GetElement(2, 3): -1.00
// ---------------------------------------------------------------
void Matrix4x4_T01_Constructor()
{
    printTitle(F("Matrix4x4 T01 Constructor"));

    Matrix4x4<float> M1;
    printMatrix4x4("M(): ", M1);

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    Matrix4x4<float> M2(array);
    printMatrix4x4("M(array): ", M2);

    float min = 0.001;
    float max = 0.999;
    Matrix4x4<float> M3(min, max);
    printMatrix4x4("M(0.001, 0.999): ", M3);

    // v6.3.0: the fourth constructor places a 2 x 2 matrix in the upper
    // left corner of the identity (a 3 x 3 matrix works the same way).
    Matrix2x2<float> m2((float)1, (float)2, (float)3, (float)4);
    Matrix4x4<float> M4(m2);
    printMatrix4x4(F("M(m2), m2 = | 1 2 | | 3 4 |: "), M4);

    // v6.3.0: getters and setter. GetIndex(row, col) is row * 4 + col;
    // GetElement() reads by index or by row and column; SetElement()
    // writes by index.
    int index = M2.GetIndex(2, 3);
    Serial.print(F("M2.GetIndex(2, 3): "));
    Serial.println(index);
    Serial.print(F("M2.GetElement(index): "));
    Serial.println(M2.GetElement(index));
    M2.SetElement(index, (float)-1);
    Serial.print(F("After M2.SetElement(index, -1), M2.GetElement(2, 3): "));
    Serial.println(M2.GetElement(2, 3));
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    Matrix4x4_T01_Constructor();
#endif
#if TOPIC == 0 || TOPIC == 2
    Matrix4x4_T02_Translation();
#endif
}

void Loop()
{
}
// namespace L13_Matrix4x4
}

// Lesson_L13_Matrix4x4_h
#endif
