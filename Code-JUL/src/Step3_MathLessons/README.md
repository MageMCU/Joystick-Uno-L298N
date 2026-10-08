# Step3_MathLessons

Math lessons, namespace **csjc** ([Carpenter Software](https://carpentersoftware.com), Jesse Carpenter).

This folder holds the test programs of the MageMCU **Numerics** repository (Algebra, last updated 20241202), merged into Joystick-Uno-L298N on 20261008 as lessons 01 to 14, plus lessons 15 and 16, which use code adapted from David Eberly's Geometric Tools Engine (see Credits). The lessons use the math headers in `Code-JUL/include/numerics/` and the print helpers in `Code-JUL/include/Debug.h`.

## Quick Use (PlatformIO)

1. Open the folder `Code-JUL/` in VS Code (not the repository root).
2. In `platformio.ini`, select one lesson with `build_src_filter`, for example:
   ```
   build_src_filter = +<*> -<Step1_Joystick/> -<Step2_JUL/> -<Step3_MathLessons/> +<Step3_MathLessons/07_Vector2/>
   ```
3. Build, upload, and open the Serial Monitor at 9600 baud. The lesson runs all of its tests once, in order, from `setup()`.
4. Restore the Step2_JUL setting before uploading to the robot.

## Layout

```
Code-JUL/src/Step3_MathLessons/
├── README.md                 This file
├── CodeChangeLog.md          Change log of the original Numerics repository
├── 01_Bitwise/main.cpp        6 tests
├── 02_TypeConv/main.cpp       2 tests
├── 03_LinearMap/main.cpp      2 tests
├── 04_MiscMath/main.cpp       6 tests
├── 05_RandomNumber/main.cpp   1 test
├── 06_Statistics/main.cpp     6 tests
├── 07_Vector2/main.cpp       17 tests
├── 08_Point2/main.cpp         4 tests
├── 09_Vector3/main.cpp       16 tests
├── 10_Point3/main.cpp         4 tests
├── 11_Matrix2x2/main.cpp     13 tests
├── 12_Matrix3x3/main.cpp     15 tests
├── 13_Matrix4x4/main.cpp      2 tests
├── 14_Quaternion/main.cpp     9 tests
├── 15_LineFit/main.cpp        3 tests, self checking (new)
├── 16_Rotation/main.cpp       5 tests, self checking (new)
├── 17_DeadZone/main.cpp       joystick at rest, Article 1004 Experiment-6 (new, hardware)
├── 18_MotorLineFit/main.cpp   motor calibration, Article 1004 Experiment-7 (new, hardware)
└── 19_JoystickFrame/main.cpp  rotated joystick frame, Article 1004 Experiment-8 (new, 4 checks plus hardware)
```

Each lesson's `main.cpp` holds the test functions of one class, moved unchanged from the original `TestClass.h` file, and a `setup()` that calls them in order of their test number. The Button and Timer tests of the original repository were not carried over; those classes are studied in Experiment-1.

## Merge Notes (20261008)

- The contents of the Code-JUL headers used by Step1 and Step2 were not changed. Where a Numerics header already existed in Code-JUL (`Bitwise.h`, `TypeConv.h`, `LinearMap.h`, `MiscMath.h`, `Vector3.h`, `Button.h`, `Timer.h`), the lessons use the Code-JUL version.
- Two lessons were adjusted to the Code-JUL headers: `01_Bitwise` defines its own `ReverseBits()` (a member of the Numerics Bitwise class only), and `02_TypeConv` uses the return value of `BytesToWord()` and `BytesToDWord()` in place of `GetWord()` and `GetDWord()`.
- `Debug.h`: the `Debug()` overloads with one to three values are defined in `numerics/MiscMath.h`; `Debug.h` adds the four and five value overloads and the print helpers.
- Not merged: `TypeConv::FloatTo5Bytes()` of Numerics, which calls `_floatToBytes()`, a function declared but never defined; the archived `Joystick` and `L298N` text files. The `BusI2C` files are set aside for a later article.

## Bug Fixes (20261008)

Fixed in the ten Numerics headers that Step1 and Step2 do not use. Each fix is marked `FIXED 20261008` in the header. The files that Step1 and Step2 use (`Bitwise.h`, `LinearMap.h`, `MiscMath.h`, `TypeConv.h`) are unchanged; their remaining edge cases are marked `REVIEW 20261008` and are left as lesson exercises.

| Header | Fix |
|---|---|
| Matrix3x3.h | `Solve(b)` returns the solution of A x = b (it returned A × b) |
| Matrix2x2.h, Matrix3x3.h | `Inverse()` of a singular matrix returns the zero matrix (it returned the identity); optional `Inverse(&ok)` reports invertibility; row and col are `int` |
| Matrix3x3.h | `Cramer()` checks for a zero determinant; `m_swapRows()` comma operator corrected; `m_col()` initialized |
| Matrix4x4.h | Constructors from Matrix2x2 and Matrix3x3 fill the new matrix (they left it uninitialized); `Translation()` and `Rotation()` are defined as members (the free functions remain) |
| Matrix.h, Matrix3x3.h, Matrix4x4.h, Quaternion.h, Point2.h, Point3.h | Unused inheritance removed. Sizes on the Uno: Quaternion 76 to 16 bytes, Matrix2x2 92 to 16, Matrix3x3 128 to 36, Matrix4x4 192 to 64, Point2 18 to 10, Point3 28 to 14 |
| Quaternion.h | `GetAxis()` compiles; `NormDeviation()` is two sided again; `Multiply()` and `operator*` renormalize only products that drifted from unit length (within 0.01), so (2)(2) = 4; `GetRadianAngle()` clamps w; `Inverse()` and `UnitQuaternion()` handle zero; `Element()` bounds check; new `Rotate(v)` |
| Vector2.h, Vector3.h | `Angle()` clamps before `acos()`; `ProjV()` handles a zero vector; `DotPerp()` uses `real` |
| RandomNumber.h | Seeds once, at the first call; returns real values in [min, max) (bounds were truncated to integers) |
| Statistics.h | Quicksort uses a fixed 64 entry stack (no variable length array); empty and one value sets handled. The constructor still sorts the caller's array in place (documented) |
| 06_Statistics lesson | `const int size` (the array was a variable length array) |

## Verification (20261008)

- Desktop tests against reference values: every function listed above, 2000 random rotations (quaternion to matrix and back, and R × v = q.Rotate(v)), slerp, and the line fit. All pass.
- AVR build (avr-gcc 7.3.0, `-Wall -Wextra -Wvla`): all 16 lessons compile with no warnings.
- AVR simulation (simavr, ATmega328P at 16 MHz): every lesson ran to its last test with no reset; lessons 15 and 16 report `Failures: 0`.
- Step1_Joystick and Step2_JUL: Intel HEX byte for byte identical to commit f2307a1.

| Lesson | Program (bytes) | Data (bytes) |
|---|---|---|
| 01_Bitwise | 5288 | 592 |
| 02_TypeConv | 3894 | 442 |
| 03_LinearMap | 6178 | 366 |
| 04_MiscMath | 8828 | 612 |
| 05_RandomNumber | 5946 | 254 |
| 06_Statistics | 10638 | 578 |
| 07_Vector2 | 11576 | 1490 |
| 08_Point2 | 6178 | 570 |
| 09_Vector3 | 14612 | 1444 |
| 10_Point3 | 6314 | 582 |
| 11_Matrix2x2 | 14184 | 1114 |
| 12_Matrix3x3 | 17864 | 1234 |
| 13_Matrix4x4 | 5880 | 386 |
| 14_Quaternion | 13862 | 822 |
| 15_LineFit | 7412 | 440 |
| 16_Rotation | 14824 | 492 |

The Uno has 2048 bytes of RAM. Data is the RAM used before the program runs; in lessons 07, 09, 11, and 12 most of it is text printed by the tests (held in RAM because it is passed as `String`). Lessons 15 and 16 keep their text in program memory with `F()`.

## Known Items for Review

- Lessons 01 to 14 print values but do not compare them with expected values; lessons 15 and 16 show the self checking form (expected, observed, PASS or FAIL).
- `04_MiscMath`: T4 and T5 both print the title "T2 Direction Components"; T2 and T3 print no title.
- Lesson 16 relates to Article 1005, Study of Quaternions (20221207); conventions should be checked against the article.

## Credits

Lessons 15 and 16 use code adapted from the Geometric Tools Engine by **David Eberly**, Geometric Tools (https://www.geometrictools.com, https://github.com/davideberly/GeometricTools), distributed under the Boost Software License, Version 1.0:

- `include/numerics/LineFit2.h`, adapted from GTE/Mathematics/ApprHeightLine2.h
- `include/numerics/Rotation.h`, adapted from GTE/Mathematics/Rotation.h and Slerp.h

Each file carries David Eberly's copyright notice, the Boost license reference, and an adaptation clause listing the changes. The matrix inverse and quaternion inverse fixes follow the approach of GTE Matrix2x2.h, Matrix3x3.h, and Quaternion.h, credited in those headers. These adaptations are not endorsed by David Eberly or Geometric Tools.

## Disclaimer and License

MIT License. See the repository [`LICENSE`](../../../LICENSE) and [`DISCLAIMER.md`](../../../DISCLAIMER.md). The original Numerics repository carried an MIT License, Copyright (c) 2022, Carpenter Software. The portions adapted from the Geometric Tools Engine remain under the Boost Software License, Version 1.0 (https://www.boost.org/LICENSE_1_0.txt).
