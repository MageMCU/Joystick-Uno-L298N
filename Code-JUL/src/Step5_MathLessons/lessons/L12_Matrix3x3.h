//
// Carpenter Software
// File: L12_Matrix3x3.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L12_Matrix3x3, selected with LESSON 12 in
// Step5_MathLessons/main.cpp
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
// RELEASE
//   2026-10-28  v6.8.0
//   L12_Matrix3x3.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

// TEACHING NOTES (v6.1.1)
// Lesson 12: 3 x 3 matrices. The terms are defined in
// include/numerics/Matrix2x2.h; minors, cofactors, the 3 x 3 determinant
// and adjoint, and Cramer's rule are explained in
// include/numerics/Matrix3x3.h.
// The topics use three matrices that can be checked by hand:
//   N = | 1 2 3 |  det N = 0: the rows are in arithmetic sequence (row 1
//       | 4 5 6 |  is the mean of rows 0 and 2), so N has no inverse
//       | 7 8 9 |
//   A = | 1 2 1 |  det A = -4; A x = (5, 6, 9) has x = (1, 1, 2)
//       | 2 2 1 |
//       | 1 2 3 |
//   M = | 2 1 2 |  det M = 5
//       | 3 2 2 |
//       | 1 2 3 |
// The topics run T01 to T15 (see Setup()).
#ifndef Lesson_L12_Matrix3x3_h
#define Lesson_L12_Matrix3x3_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 15

#include <Arduino.h>
#include "Debug.h"

namespace L12_Matrix3x3
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// T15: a random matrix with whole number elements from -9 to 8 (zero
// skipped) and a random x; b = A x is computed, then x is found again
// from b. A.Solve(b) and A.Cramer(b) both return the original x.
// Solve() applies the inverse of the matrix it is called on, so it is
// called on A, not on Ainv (FIXED 20261022, v6.1.2; Discrepancies.md,
// 158).
// ---------------------------------------------------------------
// Matrix3x3_T15_FindInvertible (teaching notes, v6.3.0)
// Hint: FindInvertible, make a practice problem with a known answer.
// Purpose: build a random system A x = b whose solution is known, then
// solve it two ways.
// What is learnt:
//   Work backward  choose x first, compute b = A x, then solve for x: the
//                  answer is known in advance, so any error shows. This is
//                  how a teacher writes exercises.
//   randomSeed(seed)  the Arduino seed; mixing two analog readings and
//                  micros() gives a different sequence on each run.
//   random(18) - 9  an integer from -9 to 8; the do while loop draws again
//                  until the value is not 0.
//   do { } while (condition); runs its body at least once.
// Expected output (random values):
//   A: random(18) - 9, whole numbers -9 to 8, never 0
//   A(aM): nine whole numbers   det A: (not 0 when A is invertible)
//   Ainv: its inverse
//   x: random(10) - 5, whole numbers -5 to 4, never 0
//   x(aV): (2.00, -5.00, -1.00) for example
//   Invertible
//   x = A.Solve(b): and x = A.Cramer(b): the same x again
// ---------------------------------------------------------------
void Matrix3x3_T15_FindInvertible()
{
    printTitle(F("Matrix3x3 T15 Find Invertible Matrix"));
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
    // v6.4.1: the ranges of the random whole numbers, and det A.
    Serial.println(F("A: random(18) - 9, whole numbers -9 to 8, never 0"));
    printMatrix3x3("A(aM): ", A);
    printResult(F("det A: "), A.Determinant());

    // Inverse of Matrix A
    Matrix3x3<float> Ainv = A.Inverse();
    printMatrix3x3("Ainv: ", Ainv);

    // Random integers for Vector x
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
    // v6.4.1
    Serial.println(F("x: random(10) - 5, whole numbers -5 to 4, never 0"));
    Vector3<float> x(aV);
    printVector3("x(aV): ", x);

    // Calculate Vector b
    Vector3<float> b = A * x;
    printVector3("b = A * x: ", b);

    // Compare, Solve and Check
    if (A.Invertible())
    {
        Serial.println("Invertible");

        x = A.Solve(b);
        printVector3("x = A.Solve(b): ", x);

        x = A.Cramer(b);
        printVector3("x = A.Cramer(b): ", x);
    }
    else
    {
        // v6.4.1: say so when the random A has no inverse.
        Serial.println(F( \
            "NOT invertible (det A = 0): reset the board for a new A"));
    }
}

// T14: one rotation of 45 degrees about x, then y, then z (Matrix3x3.h,
// Rotation()). Each row and each column of the result is a unit vector
// (the matrix is orthonormal, Rotation.h).
// ---------------------------------------------------------------
// Matrix3x3_T14_Rotation (teaching notes, v6.3.0)
// Hint: Rotation, turn about the three axes in one matrix.
// Purpose: Rotation(x, y, z) builds one matrix from rotations of 45
// degrees about the x, y, and z axes.
// What is learnt:
//   Each axis has its own rotation matrix; the combined matrix is their
//   product, and the order of the product matters (lesson 11, T11).
//   Orthonormal matrix  each row and each column is a unit vector, and
//                  they are mutually perpendicular. Check row 0:
//                  0.50^2 + 0.15^2 + 0.85^2 = 1 (to rounding).
//   RAM            the commented lines would build three more matrices;
//                  each holds nine floats (36 bytes), and on 2 KB of RAM
//                  the original author kept them out (stack and heap
//                  collision).
// Expected output:
//   angles: 45 degrees about x, 45 about y, 45 about z (XYZ order)
//   A (the identity), then
//   ALL
//   0.50 -0.15 0.85
//   0.50 0.85 -0.15
//   -0.71 0.50 0.50
// ---------------------------------------------------------------
void Matrix3x3_T14_Rotation()
{
    printTitle(F("Matrix3x3 T14 Rotation"));

    // In Development --------------------- FIXME
    // working one-direction only (CCW)
    float radian = (float)45 * DEG_TO_RAD;
    // v6.4.1: print the three angles, the inputs of Rotation().
    Serial.println(F( \
        "angles: 45 degrees about x, 45 about y, 45 about z (XYZ order)"));

    // identity
    Matrix3x3<float> A;
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

// T13: the default constructor makes the identity I, and N I = N.
// ---------------------------------------------------------------
// Matrix3x3_T13_Identity (teaching notes, v6.3.0)
// Hint: Identity, the matrix that changes nothing.
// Purpose: the default constructor gives I, and M I = M.
// What is learnt:
//   I has 1 on the main diagonal and 0 elsewhere; it is the neutral
//   element of the matrix product, as 1 is for numbers.
// Expected output:
//   I: the identity
//   M1 = M * I: the rows 1 2 3, 4 5 6, 7 8 9
// ---------------------------------------------------------------
void Matrix3x3_T13_Identity()
{
    printTitle(F("Matrix3x3 T13 Identity"));

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

// T12: N I = N, and A A^-1 = I (the identity, up to rounding).
// ---------------------------------------------------------------
// Matrix3x3_T12_MatrixMatrixMultiplication (teaching notes, v6.3.0)
// Hint: MatrixMatrixMultiplication, the product of two matrices.
// Purpose: two checks of the product: M I = M, and A A^-1 = I.
// What is learnt:
//   Each element (i, j) of the product is row i of the left matrix dotted
//   with column j of the right one: 27 multiplications for 3 x 3.
//   A matrix times its inverse is the identity; with float the result can
//   show -0.00 or 0.99 from rounding.
//   A temporary result printed directly: M * I needs no variable.
// Expected output:
//   M*I: the rows 1 2 3, 4 5 6, 7 8 9 again
//   A*Ainv: the identity
// ---------------------------------------------------------------
void Matrix3x3_T12_MatrixMatrixMultiplication()
{
    printTitle(F("Matrix3x3 T12 Matrix Matrix Multiplication"));

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

// T11: N (1, 1, 1) = the sum of each row, (6.00, 15.00, 24.00).
// ---------------------------------------------------------------
// Matrix3x3_T11_MatrixVectorMultiplication (teaching notes, v6.3.0)
// Hint: MatrixVectorMultiplication, transform a vector.
// Purpose: M v, each component a row of M dotted with v.
// What is learnt:
//   With v = (1, 1, 1) each dot product is the sum of a row: a quick
//   check by hand, 1 + 2 + 3 = 6.
// Expected output:
//   M*v:  (6.00, 15.00, 24.00)
// ---------------------------------------------------------------
void Matrix3x3_T11_MatrixVectorMultiplication()
{
    printTitle(F("Matrix3x3 T11 Matrix Vector Multiplication"));

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M(array);
    printMatrix3x3("Original M: ", M);
    Vector3<float> v(1, 1, 1);
    printVector3("v(1, 1, 1): ", v);
    printVector3("M*v: ", M * v);
}

// T10: N (-0.5) halves every element and reverses its sign.
// ---------------------------------------------------------------
// Matrix3x3_T10_MatrixScalarMultiplication (teaching notes, v6.3.0)
// Hint: MatrixScalarMultiplication, multiply every element by s.
// Purpose: M * s with s = -0.5.
// What is learnt:
//   Each element is halved and changes sign; for 3 x 3 the determinant
//   changes by s^3.
// Expected output:
//   Scalar: -0.50
//   -0.50 -1.00 -1.50
//   -2.00 -2.50 -3.00
//   -3.50 -4.00 -4.50
// ---------------------------------------------------------------
void Matrix3x3_T10_MatrixScalarMultiplication()
{
    printTitle(F("Matrix3x3 T10 Matrix Scalar Multiplication"));

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M(array);
    printMatrix3x3("Original M: ", M);
    float s = (float)-0.5;
    printResult("Scalar: ", s);
    printMatrix3x3("M*s: ", M * s);
}

// T09: -N negates every element.
// ---------------------------------------------------------------
// Matrix3x3_T09_UnaryMinus (teaching notes, v6.3.0)
// Hint: UnaryMinus, negate every element.
// Purpose: -M, operator-() without a parameter.
// What is learnt:
//   The result is a new matrix; M itself is unchanged.
// Expected output:
//   -1.00 -2.00 -3.00
//   -4.00 -5.00 -6.00
//   -7.00 -8.00 -9.00
// ---------------------------------------------------------------
void Matrix3x3_T09_UnaryMinus()
{
    printTitle(F("Matrix3x3 T09 Unary Minus operator-()"));

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M(array);
    printMatrix3x3("Original M: ", M);
    printMatrix3x3("Unary Minus -M: ", -M);
}

// T08: A x = (5, 6, 9). A.Solve(b) and A.Cramer(b) both print the
// solution (1.00, 1.00, 2.00); check: 1 + 2 + 2 = 5, 2 + 2 + 2 = 6,
// 1 + 2 + 6 = 9. Solve() applies the inverse of the matrix it is called
// on, so it is called on A (FIXED 20261022, v6.1.2; it was called on
// Ainv and printed A b = (26, 31, 44); Discrepancies.md, 158). A^-1 prints
//   | -1.00  1.00  0.00 |
//   |  1.25 -0.50 -0.25 |
//   | -0.50  0.00  0.50 |
// ---------------------------------------------------------------
// Matrix3x3_T08_Solve (teaching notes, v6.3.0)
// Hint: Solve, three equations in three unknowns.
// Purpose: A x = b solved two ways, with the inverse and with Cramer's
// rule.
// What is learnt:
//   Solve(b)       x = A^-1 b; called on A, the matrix of the system.
//   Cramer(b)      x_i = det(A_i) / det(A), where A_i is A with column i
//                  replaced by b; four determinants, no inverse.
//   Two methods, one answer: agreement is a check on both.
// Expected output:
//   *Ainv:
//   -1.00 1.00 0.00
//   1.25 -0.50 -0.25
//   -0.50 0.00 0.50
//   A.Solve(b):  (1.00, 1.00, 2.00)
//   A.Cramer(b):  (1.00, 1.00, 2.00)
// ---------------------------------------------------------------
void Matrix3x3_T08_Solve()
{
    printTitle(F("Matrix3x3 T08 Solve (+Cramer)"));

    float array[] = {1, 2, 1, 2, 2, 1, 1, 2, 3};
    Matrix3x3<float> A(array);
    printMatrix3x3("A(array): ", A);

    Vector3<float> b(5, 6, 9);
    printVector3("b(5, 6, 9): ", b);

    Matrix3x3<float> Ainv = A.Inverse();
    printMatrix3x3("*Ainv: ", Ainv);

    // Solve Ax = b; x = Ainv(b)
    Vector3<float> x = A.Solve(b);
    printVector3("A.Solve(b): ", x);

    // ALternate Solution
    x = A.Cramer(b);
    printVector3("A.Cramer(b): ", x);
}

// T07: M^-1 = adjoint / 5 = |  0.40  0.20 -0.40 |
//                           | -1.40  0.80  0.40 |
//                           |  0.80 -0.60  0.20 |
// ---------------------------------------------------------------
// Matrix3x3_T07_Inverse (teaching notes, v6.3.0)
// Hint: Inverse, the matrix that undoes M.
// Purpose: M^-1 = adj(M) / det(M), here adj(M) / 5.
// What is learnt:
//   Each element of T06 divided by 5: 2 / 5 = 0.40, -7 / 5 = -1.40.
//   If det M were 0, Inverse() would return the zero matrix; pass the
//   address of a bool, M.Inverse(&ok), to be told.
// Expected output:
//   det M: 5.00   (v6.4.1, printed after M(array))
//   M.Inverse():
//   0.40 0.20 -0.40
//   -1.40 0.80 0.40
//   0.80 -0.60 0.20
// ---------------------------------------------------------------
void Matrix3x3_T07_Inverse()
{
    printTitle(F("Matrix3x3 T07 Inverse"));

    float array[] = {2, 1, 2, 3, 2, 2, 1, 2, 3};
    Matrix3x3<float> M(array);
    printMatrix3x3("M(array): ", M);
    // v6.4.1: the divisor of adj(M)
    printResult(F("det M: "), M.Determinant());
    M = M.Inverse();
    printMatrix3x3("M.Inverse(): ", M);
    // Verified Output
}

// T06: the adjoint of M is |  2  1 -2 |, which is 5 M^-1 (T07).
//                          | -7  4  2 |
//                          |  4 -3  1 |
// ---------------------------------------------------------------
// Matrix3x3_T06_Adjoint (teaching notes, v6.3.0)
// Hint: Adjoint, the transposed matrix of cofactors.
// Purpose: adj(M), the main step of the inverse: M^-1 = adj(M) / det M.
// What is learnt:
//   Cofactor       a minor with the sign (-1)^(row + col).
//   Adjoint        the cofactors, transposed. M adj(M) = det(M) I.
//   Check: with det M = 5, adj(M) / 5 is the inverse printed in T07.
// Expected output:
//   det M: 5.00   (v6.4.1, printed after M(array))
//   M.Adjoint():
//   2.00 1.00 -2.00
//   -7.00 4.00 2.00
//   4.00 -3.00 1.00
// ---------------------------------------------------------------
void Matrix3x3_T06_Adjoint()
{
    printTitle(F("Matrix3x3 T06 Adjoint"));

    float array[] = {2, 1, 2, 3, 2, 2, 1, 2, 3};
    Matrix3x3<float> M(array);
    printMatrix3x3("M(array): ", M);
    // v6.4.1: links T06 to T07
    printResult(F("det M: "), M.Determinant());
    M = M.Adjoint();
    printMatrix3x3("M.Adjoint(): ", M);
    // Verified Output
    // 2.00 1.00 -2.00
    // -7.00 4.00 2.00
    // 4.00 -3.00 1.00
}

// T05: the transpose of N has the rows (1, 4, 7), (2, 5, 8), (3, 6, 9).
// ---------------------------------------------------------------
// Matrix3x3_T05_Transpose (teaching notes, v6.3.0)
// Hint: Transpose, swap rows and columns.
// Purpose: M^T for a 3 x 3 matrix.
// What is learnt:
//   Row i of M becomes column i of M^T; the main diagonal 1, 5, 9 stays.
//   M = M.Transpose(); replaces M with the result: the right side is
//   computed first, then assigned with operator=.
// Expected output:
//   M.Transpose():
//   1.00 4.00 7.00
//   2.00 5.00 8.00
//   3.00 6.00 9.00
// ---------------------------------------------------------------
void Matrix3x3_T05_Transpose()
{
    printTitle(F("Matrix3x3 T05 Transpose"));

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M(array);
    printMatrix3x3("M(array): ", M);
    M = M.Transpose();
    printMatrix3x3("M.Transpose(): ", M);
}

// T04: a random matrix with elements from -1 to 1; it is invertible
// unless its determinant is within FLT_EPSILON of 0, which random values
// almost never give.
// ---------------------------------------------------------------
// Matrix3x3_T04_Invertible (teaching notes, v6.3.0)
// Hint: Invertible, test before inverting.
// Purpose: Invertible() on a random matrix, with its determinant shown.
// What is learnt:
//   A matrix is invertible when |det| exceeds FLT_EPSILON, the smallest
//   float step near 1 (about 1.2e-7). Random real values almost never
//   give exactly 0, so the message is nearly always the first one.
// Expected output (random values):
//   det: (a number)
//   M is invertible...
// ---------------------------------------------------------------
void Matrix3x3_T04_Invertible()
{
    printTitle(F("Matrix3x3 T04 Invertible"));

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

// T03: the determinant of a random matrix with elements from -9 to 9.
// ---------------------------------------------------------------
// Matrix3x3_T03_Determinant (teaching notes, v6.3.0)
// Hint: Determinant, the volume factor of a 3 x 3 matrix.
// Purpose: det of a random matrix, by expansion along the first row.
// What is learnt:
//   Minor          the 2 x 2 determinant left after deleting one row and
//                  one column.
//   Cofactor expansion  det = e00 m00 - e01 m01 + e02 m02, with the signs
//                  alternating + - +.
//   Random test data: a different matrix and determinant on each run;
//   the student can check one run by hand.
// Expected output (random values):
//   M(-9.0, 9.0): nine values, then det: (a number)
// ---------------------------------------------------------------
void Matrix3x3_T03_Determinant()
{
    printTitle(F("Matrix3x3 T03 Determinant"));

    float min = -9.0;
    float max = 9.0;
    Matrix3x3<float> M(min, max);
    printMatrix3x3("M(-9.0, 9.0): ", M);
    float det = M.Determinant();
    printResult("det: ", det);
}

// T02: element (row 0, column 1) is at index 0 * 3 + 1 = 1 and holds 2;
// SetElement(1, 2.05) changes it.
// ---------------------------------------------------------------
// Matrix3x3_T02_Access (teaching notes, v6.3.0)
// Hint: Access, read and write single elements (getters and setter).
// Purpose: the index of an element in the row major array, and the
// getters and the setter of Matrix3x3.
// What is learnt:
//   GetIndex(row, col)  returns row * 3 + col; (0, 1) gives 1.
//   Getters        GetElement(index) and GetElement(row, col): overloads
//                  that read the same element two ways.
//   Setter         SetElement(index, value) writes one element.
//   Here int index is the proper type for the result of GetIndex()
//   (compare lesson 11, T02).
// Expected output:
//   index = M.GetIndex(0, 1): 1
//   M.GetElement(1): 2.00
//   M.SetElement(1, 2.05): row 0 becomes 1.00 2.05 3.00
//   M.GetElement(0, 1): 2.05
// ---------------------------------------------------------------
void Matrix3x3_T02_Access()
{
    printTitle(F("Matrix3x3 T02 Access"));

    float array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Matrix3x3<float> M(array);
    printMatrix3x3("M(array): ", M);
    int index = M.GetIndex(0, 1);
    // v6.4.1: print the index that GetIndex() returns.
    Serial.print(F("index = M.GetIndex(0, 1): "));
    Serial.println(index);
    float element = M.GetElement(index);

    Serial.print("M.GetElement(");
    Serial.print(index);
    printResult("): ", element);

    M.SetElement(1, 2.05);
    printMatrix3x3("M.SetElement(1, 2.05): ", M);

    // v6.3.0: the second getter reads the same element by row and
    // column, so GetIndex() is not needed to read it back.
    Serial.print(F("M.GetElement(0, 1): "));
    Serial.println(M.GetElement(0, 1));
}

// T01: the identity, a matrix from an array, and a random matrix.
// ---------------------------------------------------------------
// Matrix3x3_T01_Constructor (teaching notes, v6.3.0)
// Hint: Constructor, build a 3 x 3 matrix.
// Purpose: how to declare and instantiate Matrix3x3 variables with the
// three constructors.
// What is learnt:
//     Matrix3x3<float> M1;               default: the identity
//     Matrix3x3<float> M2(array);        from nine values in row major
//                                        order: e00 e01 e02 e10 ... e22
//     Matrix3x3<float> M3(min, max);     nine random values from min to max
//   Two constructors with float parameters: (array) takes a pointer to
//   nine values, (min, max) takes two numbers; the argument types decide
//   which one runs. Unlike Matrix2x2 there is no nine value constructor.
// Expected output:
//   M(): the identity   M(array): rows 1 2 3, 4 5 6, 7 8 9
//   M(0.001, 0.999): nine random values (different on each run)
// ---------------------------------------------------------------
void Matrix3x3_T01_Constructor()
{
    printTitle(F("Matrix3x3 T01 Constructor"));

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

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    Matrix3x3_T01_Constructor();
#endif
#if TOPIC == 0 || TOPIC == 2
    Matrix3x3_T02_Access();
#endif
#if TOPIC == 0 || TOPIC == 3
    Matrix3x3_T03_Determinant();
#endif
#if TOPIC == 0 || TOPIC == 4
    Matrix3x3_T04_Invertible();
#endif
#if TOPIC == 0 || TOPIC == 5
    Matrix3x3_T05_Transpose();
#endif
#if TOPIC == 0 || TOPIC == 6
    Matrix3x3_T06_Adjoint();
#endif
#if TOPIC == 0 || TOPIC == 7
    Matrix3x3_T07_Inverse();
#endif
#if TOPIC == 0 || TOPIC == 8
    Matrix3x3_T08_Solve();
#endif
#if TOPIC == 0 || TOPIC == 9
    Matrix3x3_T09_UnaryMinus();
#endif
#if TOPIC == 0 || TOPIC == 10
    Matrix3x3_T10_MatrixScalarMultiplication();
#endif
#if TOPIC == 0 || TOPIC == 11
    Matrix3x3_T11_MatrixVectorMultiplication();
#endif
#if TOPIC == 0 || TOPIC == 12
    Matrix3x3_T12_MatrixMatrixMultiplication();
#endif
#if TOPIC == 0 || TOPIC == 13
    Matrix3x3_T13_Identity();
#endif
#if TOPIC == 0 || TOPIC == 14
    Matrix3x3_T14_Rotation();
#endif
#if TOPIC == 0 || TOPIC == 15
    Matrix3x3_T15_FindInvertible();
#endif
}

void Loop()
{
}
// namespace L12_Matrix3x3
}

// Lesson_L12_Matrix3x3_h
#endif
