//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: Class Matrix.h
// Folder: include/numerics
// Github: MageMCU
// Repository: Joystick-Uno-L298N
//
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//

// Matrix<real>: empty base class of Matrix2x2, Matrix3x3, and Matrix4x4.
// Merged from MageMCU/Numerics (Algebra/include, 20241202).

#ifndef Numerics_Matrix_h
#define Numerics_Matrix_h

#include <Arduino.h>
#include "Quaternion.h"

namespace csjc
{

    template <typename real>
    // FIXED 20261008: Matrix no longer inherits from Quaternion (it used
    // none of its members). Matrix2x2<float> is now 16 bytes on the Uno
    // instead of 92. Quaternion.h is still included because the matrix
    // classes use Vector2, Vector3, and RandomNumber through it.
    class Matrix
    {
    private:
    public:
        // Constructors
        Matrix() = default;
        ~Matrix() = default;
    };

    /* Experimental
    template <typename real>
    Vector2<real> Matrix2x2<real>::m_Ax(real A[], real x[], int NumRows, int NumCommon, int NumCols)
    {
        // Test the following conditions
        // (1) A(2x2)(rows)=2 * B(2x2)(cols)=2 where A(cols) & B(rows) = 2... DO NOT USE HERE
        // (2) A(2x2)(rows)=2 * v(2x1)(col)=1 where A(cols) & B(rows) = 2
        // Minimum Size (2, 2, 1)

        int arraySize = NumRows * NumCols;
        real vector[arraySize];
        int rIndex;
        int aIndex;
        int bIndex;

        for (int r = 0; r < NumRows; ++r)
        {
            for (int c = 0; c < NumCols; ++c)
            {
                rIndex = r * NumCommon + c;
                // Convert from col-vector to row-vector
                // We want the indices in numerical order...
                if (NumCols == 1)
                    rIndex = c * NumCommon + r;
                vector[rIndex] = (real)0;
                for (int i = 0; i < NumCommon; ++i)
                {
                    aIndex = r * NumCommon + i;
                    bIndex = i * NumCommon + c;
                    // Convert from col-vector to row-vector
                    // We want the indices in numerical order...
                    if (NumCols == 1)
                        bIndex = c * NumCommon + i;
                    vector[rIndex] += A[aIndex] * x[bIndex];
                }
            }
        }
        Vector2<real> b(vector);
        return b;
    }
    */

    /* Experimental
     template <typename real>
     Matrix2x2<real> Matrix2x2<real>::m_AB(real A[],
                                           real B[],
                                           int NumRows,
                                           int NumCommon,
                                           int NumCols)
     {
         // Test the following conditions
         // (1) A(2x2)(rows)=2 * B(2x2)(cols)=2 where A(cols) & B(rows) = 2
         // (2) A(2x2)(rows)=2 * v(2x1)(col)=1 where A(cols) & B(rows) = 2 ... DO NOT USE HERE
         // Minimum Size (2, 2, 2)

         int arraySize = NumRows * NumCols;
         real matrix[arraySize];
         int rIndex;
         int aIndex;
         int bIndex;

         for (int r = 0; r < NumRows; ++r)
         {
             for (int c = 0; c < NumCols; ++c)
             {
                 rIndex = r * NumCommon + c;
                 // Convert from col-vector to row-vector
                 // We want the indices in numerical order...
                 if (NumCols == 1)
                     rIndex = c * NumCommon + r;
                 matrix[rIndex] = (real)0;
                 for (int i = 0; i < NumCommon; ++i)
                 {
                     aIndex = r * NumCommon + i;
                     bIndex = i * NumCommon + c;
                     // Convert from col-vector to row-vector
                     // We want the indices in numerical order...
                     if (NumCols == 1)
                         bIndex = c * NumCommon + i;
                     matrix[rIndex] += A[aIndex] * B[bIndex];
                 }
             }
         }
         Matrix2x2<real> R(matrix);
         return R;

         // idea taken from GTE
         // Test the following conditions
         // (1) A(2x2)(rows)=2 * B(2x2)(cols)=2 where A(cols) & B(rows) = 2
         // (2) A(2x2)(rows)=2 * v(2x1)(col)=1 where A(cols) & B(rows) = 2
         // int NumRows = 2;
         // int NumCols = 2; // or 1 as indicated above...
         // int NumCommon = 2;
         // int rIndex;
         // int aIndex;
         // int bIndex;

         // for (int r = 0; r < NumRows; ++r)
         // {
         //     for (int c = 0; c < NumCols; ++c)
         //     {
         //         rIndex = r * NumCommon + c;
         //         // Convert from col-vector to row-vector
         //         // We want the indices in numerical order...
         //         if (NumCols == 1)
         //             rIndex = c * NumCommon + r;
         //         for (int i = 0; i < NumCommon; ++i)
         //         {
         //             aIndex = r * NumCommon + i;
         //             bIndex = i * NumCommon + c;
         //         // Convert from col-vector to row-vector
         //         // We want the indices in numerical order...
         //             if (NumCols == 1)
         //                 bIndex = c * NumCommon + i;
         //             // result(r, c) += A(r, i) * B(i, c); DO NOT USE

         //             // Debug
         //             cout << " R:(" << r << ", " << c << ")="
         //             << rIndex << " A:(" << r << ", " << i
         //             << ")=" << aIndex << " B:(" << i << ", "
         //             << c << ")=" << bIndex << endl;
         //         }
         //     }
         // }
     }
     */

    /* Experimental
    template <typename real>
    void Matrix2x2<real>::m_AB(real A[],
                               real B[],
                               real C[],
                               int NumRows,
                               int NumCommon,
                               int NumCols)
    {
        // Test the following conditions
        // (1) A(2x2)(rows)=2 * B(2x2)(cols)=2 where A(cols) & B(rows) = 2
        // (2) A(2x2)(rows)=2 * v(2x1)(col)=1 where A(cols) & B(rows) = 2 ... DO NOT USE HERE
        // Minimum Size (2, 2, 2)

        int rIndex;
        int aIndex;
        int bIndex;

        for (int r = 0; r < NumRows; ++r)
        {
            for (int c = 0; c < NumCols; ++c)
            {
                rIndex = r * NumCommon + c;
                // Convert from col-vector to row-vector
                // We want the indices in numerical order...
                if (NumCols == 1)
                    rIndex = c * NumCommon + r;
                C[rIndex] = (real)0;
                for (int i = 0; i < NumCommon; ++i)
                {
                    aIndex = r * NumCommon + i;
                    bIndex = i * NumCommon + c;
                    // Convert from col-vector to row-vector
                    // We want the indices in numerical order...
                    if (NumCols == 1)
                        bIndex = c * NumCommon + i;
                    C[rIndex] += A[aIndex] * B[bIndex];
                }
            }
        }
    }
    */
}

#endif /* Numerics_Matrix_h */
