//
// Carpenter Software
// File: L11_Matrix2x2.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L11_Matrix2x2, selected with LESSON 11 in
// Step5_MathLessons/main.cpp
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
// RELEASE
//   2026-10-28  v6.8.0
//   L11_Matrix2x2.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

// TEACHING NOTES (v6.1.1)
// Lesson 11: 2 x 2 matrices. Every term used here (element, row major
// order, identity, determinant, invertible, inverse, transpose, adjoint,
// the products, the rotation matrix) is defined at the top of
// include/numerics/Matrix2x2.h, with a worked example; read it first.
// Most topics use M = | 3 2 |, so the results can be checked by hand:
//                     | 2 4 |
//   det M = 3 (4) - 2 (2) = 8
//   M^-1 = (1/8) |  4 -2 | = |  0.50 -0.25 |
//                | -2  3 |   | -0.25  0.38 |
//   M x = (5, -2) has the solution x = (3, -2):
//   3 (3) + 2 (-2) = 5 and 2 (3) + 4 (-2) = -2.
// Why it matters: lesson 19 turns the joystick frame with a 2 x 2
// rotation matrix.
// The topics run T01 to T13 (see Setup()).
#ifndef Lesson_L11_Matrix2x2_h
#define Lesson_L11_Matrix2x2_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 13

#include <Arduino.h>
#include "Debug.h"

namespace L11_Matrix2x2
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// T13: the five corners of a house shape turned 30 degrees
// counterclockwise by R(30) = | 0.87 -0.50 |. Example: the roof top
//                             | 0.50  0.87 |
// (0, 2) goes to (-1.00, 1.73). Every corner keeps its distance from
// the origin.
// ---------------------------------------------------------------
// Matrix2x2_T13_Rotation (teaching notes, v6.3.0)
// Hint: Rotation, turn vectors about the origin.
// Purpose: R(a) = | cos a  -sin a |, applied to the five corners of a
//                 | sin a   cos a |
// house shape.
// What is learnt:
//   Rotation matrix  turns every vector by the angle a, counterclockwise
//                  for a > 0, and keeps its length (det R = 1).
//   Array of objects  Vector2<float> aV[] { {-1, -1}, ... }; C++11 list
//                  initialization: each inner pair calls the constructor
//                  Vector2(x, y).
//   In place update  aV[i] = R * aV[i]; replaces each corner.
//   Construction note  Rotation() is a member function, so it needs an
//                  object to be called on. It is called on I, a finished
//                  identity matrix:
//                    Matrix2x2<float> I;
//                    Matrix2x2<float> R = I.Rotation(30 * DEG_TO_RAD);
//                  Writing Matrix2x2<float> R = R.Rotation(...) would call
//                  it on R while R itself is still being built (v6.3.0 and
//                  earlier did; it worked only because Rotation() reads
//                  nothing but its argument). Once R exists, R =
//                  R.Rotation(a); is an ordinary assignment (lesson 19).
// Expected output:
//   angle: 30 degrees (counterclockwise)
//   R
//   0.87 -0.50
//   0.50 0.87
//   Was-aV[2]:  (0.00, 2.00)   Rot-aV[2]:  (-1.00, 1.73)
//   (five corners in all)
// ---------------------------------------------------------------
void Matrix2x2_T13_Rotation()
{
    printTitle(F("Matrix2x2 T13 Rotation"));

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
    // Rotation() is called on a finished object, the identity I (v6.3.1;
    // up to v6.3.0 Matrix2x2<float> R = R.Rotation(...) called it on R
    // while R was still being built; Discrepancies.md, 193).
    Matrix2x2<float> I;
    Matrix2x2<float> R = I.Rotation(30 * DEG_TO_RAD);
    // v6.4.1: print the angle of the rotation, the input of R.
    Serial.println(F("angle: 30 degrees (counterclockwise)"));
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

// T12: the default constructor makes the identity I, and M I = M.
// ---------------------------------------------------------------
// Matrix2x2_T12_Identity (teaching notes, v6.3.0)
// Hint: Identity, the matrix that changes nothing.
// Purpose: I = | 1 0 |, and M I = M.
//              | 0 1 |
// What is learnt:
//   The default constructor of this class makes the identity, not the
//   zero matrix; the private m_identity() fills it.
//   The identity plays the role of the number 1 in multiplication.
// Expected output:
//   I              M2 = M1 * I
//   1.00 0.00      3.00 2.00
//   0.00 1.00      2.00 4.00
// ---------------------------------------------------------------
void Matrix2x2_T12_Identity()
{
    printTitle(F("Matrix2x2 T12 Identity"));

    Matrix2x2<float> M1((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("M1 ", M1);

    // By using the default constructor as shown below,
    // the matrix is not zeros but an identity matrix 2x2...
    Matrix2x2<float> I;
    printMatrix2x2("I ", I);

    Matrix2x2<float> M2 = M1 * I;
    printMatrix2x2("M2 = M1 * I ", M2);

}

// T11: the product is worked out in the comment below; compare the
// printed M3 with it.
// ---------------------------------------------------------------
// Matrix2x2_T11_MatrixMatrixMultiplication (teaching notes, v6.3.0)
// Hint: MatrixMatrixMultiplication, the product of two matrices.
// Purpose: M1 M2, and why the order matters.
// What is learnt:
//   Product        element (i, j) is row i of M1 dotted with column j of M2.
//   Not commutative  M1 M2 differs from M2 M1. Applying M2 first and M1
//                  second is M1 M2; the order of transformations matters.
//   The subtitle printed between the products is Noncommutative (v6.3.1;
//   Non-communitive up to v6.3.0).
// Expected output:
//   M1 * M2 = M3:     ** Noncommutative **   M2 * M1 = M4:
//   4.00 13.00        -10.00 -4.00
//   24.00 22.00       34.00 36.00
// ---------------------------------------------------------------
void Matrix2x2_T11_MatrixMatrixMultiplication()
{
    printTitle(F("Matrix2x2 T11 operator*(Matrix2x2 M)"));

    Matrix2x2<float> M1((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("M1 ", M1);

    Matrix2x2<float> M2((float)-4, (float)1, (float)8, (float)5);
    printMatrix2x2("M2 ", M2);

    // 3 2   -4 1     3(-4) + 2(8) =  4; 3(1) + 2(5) = 13        4  13
    // 2 4    8 5     2(-4) + 4(8) = 24; 2(1) + 4(5) = 22       24  22

    Matrix2x2<float> M3 = M1 * M2;
    printMatrix2x2("M1 * M2 = M3: ", M3);

    printSubTitle("Noncommutative");
    Matrix2x2<float> M4 = M2 * M1;
    printMatrix2x2("M2 * M1 = M4: ", M4);
}

// T10: M (1, 1) = (3 + 2, 2 + 4) = (5.00, 6.00).
// ---------------------------------------------------------------
// Matrix2x2_T10_MatrixVectorMultiplication (teaching notes, v6.3.0)
// Hint: MatrixVectorMultiplication, apply the matrix to a vector.
// Purpose: M v, the operation that transforms a vector.
// What is learnt:
//   Each result component is a row of M dotted with v:
//   (3 (1) + 2 (1), 2 (1) + 4 (1)) = (5, 6).
//   Overloads of operator*: M * s gives a matrix (T09), M * v a vector,
//   M * N a matrix (T11); the right operand decides.
// Expected output:
//   M*v:  (5.00, 6.00)
// ---------------------------------------------------------------
void Matrix2x2_T10_MatrixVectorMultiplication()
{
    printTitle(F("Matrix2x2 T10 Matrix Vector Multiplication"));

    Matrix2x2<float> M((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("Original M: ", M);
    Vector2<float> v(1, 1);
    printVector2("v(1, 1): ", v);
    printVector2("M*v: ", M*v);
}

// T09: M (-0.5) = | -1.50 -1.00 |
//                 | -1.00 -2.00 |
// ---------------------------------------------------------------
// Matrix2x2_T09_MatrixScalarMultiplication (teaching notes, v6.3.0)
// Hint: MatrixScalarMultiplication, multiply every element by a number.
// Purpose: M * s, with s = -0.5.
// What is learnt:
//   Scaling a matrix scales its effect on every vector by s; the
//   determinant changes by s^2 (s times each of the two rows).
//   float s = (float)-0.5; the cast states the type of the constant.
// Expected output:
//   Scalar: -0.50
//   -1.50 -1.00
//   -1.00 -2.00
// ---------------------------------------------------------------
void Matrix2x2_T09_MatrixScalarMultiplication()
{
    printTitle(F("Matrix2x2 T09 operator*(real s)"));

    Matrix2x2<float> M((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("Original M: ", M);
    float s = (float)-0.5;
    printResult("Scalar: ", s);
    printMatrix2x2("M*s: ", M*s);
}

// T08: -M negates every element.
// ---------------------------------------------------------------
// Matrix2x2_T08_UnaryMinus (teaching notes, v6.3.0)
// Hint: UnaryMinus, negate every element.
// Purpose: -M, the operator with one operand.
// What is learnt:
//   operator-() without a parameter; -M is a new matrix and M is
//   unchanged. (-M) v = -(M v): the result of M, turned 180 degrees.
// Expected output:
//   -3.00 -2.00
//   -2.00 -4.00
// ---------------------------------------------------------------
void Matrix2x2_T08_UnaryMinus()
{
    printTitle(F("Matrix2x2 T08 Unary Minus operator-()"));

    Matrix2x2<float> M((float)3, (float)2, (float)2, (float)4);
    printMatrix2x2("Original M: ", M);
    printMatrix2x2("Unary Minus -M: ", -M);
}

// T07: Solve((5, -2)) gives x = (3.00, -2.00); the check M x returns b.
// ---------------------------------------------------------------
// Matrix2x2_T07_Solve (teaching notes, v6.3.0)
// Hint: Solve, find x in A x = b directly.
// Purpose: Solve(b) returns the vector x of the linear system A x = b.
// What is learnt:
//   Linear system  3 x + 2 y = 5 and 2 x + 4 y = -2, written as A x = b.
//   Verification   multiply back: A x must give b again. Always check a
//                  solution this way.
//   Solve() and Inverse() in T06 give the same x; Solve() names the goal.
// Expected output:
//   Ax = b; solve: x:  (3.00, -2.00)
//   A*x = c: (5.00, -2.00)
// ---------------------------------------------------------------
void Matrix2x2_T07_Solve()
{
    printTitle(F("Matrix2x2 T07 Solve"));
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

// T06: M^-1 as in the notes above, and M^-1 (5, -2) = (3.00, -2.00),
// the same x as Solve() in T07.
// ---------------------------------------------------------------
// Matrix2x2_T06_Inverse (teaching notes, v6.3.0)
// Hint: Inverse, the matrix that undoes M.
// Purpose: M^-1 = (1 / det) adj(M), and its use to solve M x = b.
// What is learnt:
//   Inverse        M^-1 M = I, the identity.
//   Adjoint        | d -b |, the swapped and negated elements (Adjoint()).
//                  | -c a |
//   Default argument  Inverse(bool *invertible = nullptr): the parameter
//                  may be left out, as here; passing the address of a bool
//                  reports whether the inverse exists.
//   nullptr        the C++11 null pointer, a pointer to nothing.
//   x = M^-1 b solves the system of two equations.
// Expected output:
//   Inverse
//   0.50 -0.25
//   -0.25 0.38
//   inverse * b = x:  (3.00, -2.00)
// ---------------------------------------------------------------
void Matrix2x2_T06_Inverse()
{
    printTitle(F("Matrix2x2 T06 Inverse"));
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

// T05: the transpose of | 1 2 | is | 1 3 |.
//                       | 3 4 |    | 2 4 |
// ---------------------------------------------------------------
// Matrix2x2_T05_Transpose (teaching notes, v6.3.0)
// Hint: Transpose, swap rows and columns.
// Purpose: M^T, the matrix mirrored across its main diagonal.
// What is learnt:
//   Main diagonal  the elements e00 and e11; they stay in place, and e01
//                  and e10 swap.
//   For a rotation matrix the transpose equals the inverse, a fast way
//   to undo a rotation (lesson 16).
//   A returned object printed directly: printMatrix2x2("...",
//   m1.Transpose()) needs no variable.
// Expected output:
//   1.00 3.00
//   2.00 4.00
// ---------------------------------------------------------------
void Matrix2x2_T05_Transpose()
{
    printTitle(F("Matrix2x2 T05 Transpose"));

    Matrix2x2<float> m1((float)1, (float)2, (float)3, (float)4);
    printMatrix2x2("Original", m1);
    printMatrix2x2("Transpose", m1.Transpose());
}

// T04: M (det 8) is invertible; | 1 2 | (det 4 - 4 = 0) is not: its
//                               | 2 4 |
// second row is twice the first.
// ---------------------------------------------------------------
// Matrix2x2_T04_Invertible (teaching notes, v6.3.0)
// Hint: Invertible, test before inverting.
// Purpose: Invertible() returns a bool, true when the determinant is not
// zero.
// What is learnt:
//   bool           a type with two values, true and false; it can be used
//                  directly as the condition of an if.
//   Singular matrix  a matrix with determinant 0, such as one whose rows
//                  are multiples of each other (row 2 = 2 x row 1).
//   Floating point  the class compares |det| with a small tolerance
//                  rather than with exactly 0, because float arithmetic
//                  rounds.
// Expected output:
//   m1 Invertible
//   m2 NOT Invertible
// ---------------------------------------------------------------
void Matrix2x2_T04_Invertible()
{
    printTitle(F("Matrix2x2 T04 Invertible"));

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

// T03: det | 1 3 | = 5 + 6 = 11, det | 2 1 | = 0, det | -3 3 | = 6.
//          |-2 5 |                   | 10 5 |         | -7 5 |
// ---------------------------------------------------------------
// Matrix2x2_T03_Determinant (teaching notes, v6.3.0)
// Hint: Determinant, one number that tells whether a matrix can be
// inverted.
// Purpose: det | a b | = a d - b c, computed for three matrices.
//               | c d |
// What is learnt:
//   Determinant    the factor by which the matrix scales areas; 0 means
//                  the matrix flattens the plane onto a line, so no
//                  inverse exists.
//   Check: 1 (5) - 3 (-2) = 11; 2 (5) - 1 (10) = 0; -3 (5) - 3 (-7) = 6.
// Expected output:
//   det: 11.00   det: 0.00   det: 6.00
// ---------------------------------------------------------------
void Matrix2x2_T03_Determinant()
{
    printTitle(F("Matrix2x2 T03 Determinant"));

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

// T02: element (row 1, column 0) is at index 1 * 2 + 0 = 2 and holds 3;
// SetElement() changes it to 3.67.
// ---------------------------------------------------------------
// Matrix2x2_T02_Getters (teaching notes, v6.3.0)
// Hint: Getters, read (and write) single elements.
// Purpose: the getters and the setter of Matrix2x2, and the index of an
// element in the row major array.
// What is learnt:
//   Named getters  E00(), E01(), E10(), E11() read one element each.
//   GetIndex(row, col)  returns row * 2 + col, the place in the array;
//                  (1, 0) gives 2.
//   Overloaded getters  GetElement(index) and GetElement(row, col) read
//                  the same element two ways.
//   Setter         SetElement(index, value) writes one element. The
//                  class has no SetElement(row, col, value); use
//                  GetIndex() first.
//   Type note      GetIndex() returns int; this topic stores it in a float
//                  and passes it back to GetElement(int), so the compiler
//                  converts float to int. It works for small whole numbers,
//                  but int index = m1.GetIndex(1, 0); is the proper type.
//   String(v, 2)   prints a float with 2 decimals; String(index, 0) prints
//                  the float index without decimals.
// Expected output:
//   m1 by its getters: E00() E01() / E10() E11()
//   1.00 2.00
//   3.00 4.00
//   index = m1.GetIndex(1, 0):  2
//    element = m1.GetElement(index): 3.00
//   element = m1.GetElement(1, 0): 3.67
// ---------------------------------------------------------------
void Matrix2x2_T02_Getters()
{
    printTitle(F("Matrix2x2 T02 Getters"));

    Matrix2x2<float> m1((float)1, (float)2, (float)3, (float)4);

    // v6.4.1: label the matrix the getters read.
    Serial.println(F("m1 by its getters: E00() E01() / E10() E11()"));
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

// T01: three ways to fill a matrix: four elements, an array of four, or
// nothing (the identity).
// ---------------------------------------------------------------
// Matrix2x2_T01_Constructor (teaching notes, v6.3.0)
// Hint: Constructor, build a 2 x 2 matrix.
// Purpose: how to declare and instantiate Matrix2x2 variables with the
// three constructors.
// What is learnt:
//   Matrix         a table of numbers in rows and columns; element e10 is
//                  in row 1, column 0 (both counted from 0).
//   Row major order  the four elements are stored in one array, row by
//                  row: e00, e01, e10, e11. Every constructor that takes
//                  values expects this order.
//   Three constructors (overloads):
//     Matrix2x2<float> m1;                 default: the identity matrix,
//                                          not zeros (see T12)
//     Matrix2x2<float> m2(1, 2, 3, 4);     from four values
//     Matrix2x2<float> m3(array);          from an array of four values
//   Casts (float)1: the constructor takes real parameters; with
//                  <float> plain integers would also convert, but the
//                  casts make the type visible.
// Expected output:
//   m1           m2 and m3
//   1.00 0.00    1.00 2.00
//   0.00 1.00    3.00 4.00
// ---------------------------------------------------------------
void Matrix2x2_T01_Constructor()
{
    printTitle(F("Matrix2x2 T01 Constructor"));

    Matrix2x2<float> m1;
    printMatrix2x2("m1", m1);

    Matrix2x2<float> m2((float)1, (float)2, (float)3, (float)4);
    printMatrix2x2("m2((float)1, (float)2, (float)3, (float)4): ", m2);

    float array[] = {1, 2, 3, 4};
    Matrix2x2<float> m3(array);
    printMatrix2x2("m3(array[] = {1, 2, 3, 4}): ", m3);
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    Matrix2x2_T01_Constructor();
#endif
#if TOPIC == 0 || TOPIC == 2
    Matrix2x2_T02_Getters();
#endif
#if TOPIC == 0 || TOPIC == 3
    Matrix2x2_T03_Determinant();
#endif
#if TOPIC == 0 || TOPIC == 4
    Matrix2x2_T04_Invertible();
#endif
#if TOPIC == 0 || TOPIC == 5
    Matrix2x2_T05_Transpose();
#endif
#if TOPIC == 0 || TOPIC == 6
    Matrix2x2_T06_Inverse();
#endif
#if TOPIC == 0 || TOPIC == 7
    Matrix2x2_T07_Solve();
#endif
#if TOPIC == 0 || TOPIC == 8
    Matrix2x2_T08_UnaryMinus();
#endif
#if TOPIC == 0 || TOPIC == 9
    Matrix2x2_T09_MatrixScalarMultiplication();
#endif
#if TOPIC == 0 || TOPIC == 10
    Matrix2x2_T10_MatrixVectorMultiplication();
#endif
#if TOPIC == 0 || TOPIC == 11
    Matrix2x2_T11_MatrixMatrixMultiplication();
#endif
#if TOPIC == 0 || TOPIC == 12
    Matrix2x2_T12_Identity();
#endif
#if TOPIC == 0 || TOPIC == 13
    Matrix2x2_T13_Rotation();
#endif
}

void Loop()
{
}
// namespace L11_Matrix2x2
}

// Lesson_L11_Matrix2x2_h
#endif
