//
// Carpenter Software
// File: main.cpp
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step3_MathLessons/07_Vector2
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestVector2.h (merged 20261008)
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

#include "Arduino.h"

void Vector2_T15_COPY()
{
    printTitle("Vector2 COPY using the equal sign");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    printSubTitle("This does not always work unless using an operator=");
    Vector2<float> v2 = v1;
    printVector2("v2", v2);
}

void Vector2_T14_DotProduct()
{
    printTitle("Vector2 Dot Product");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    float dot = v1 * v2;
    Serial.print("dot = v1 * v2 ");
    Serial.println(dot);
}

void Vector2_T13_VectorVectorSubtraction()
{
    printTitle("Vector2 Vector Vector Subtraction");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    Vector2<float> v3 = v1 - v2;
    printVector2("v3 = v1 - v2", v3);
}

void Vector2_T12_VectorVectorAddition()
{
    printTitle("Vector2 Vector Vector Addition");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    Vector2<float> v3 = v1 + v2;
    printVector2("v3 = v1 + v2", v3);
}

void Vector2_T11_VectorScalarProduct()
{
    printTitle("Vector2 Vector Scalar Product");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    float scalar = 3;

    Vector2<float> v2 = v1 * scalar;
    printVector2("v2 = v1 * scalar", v2);
}

void Vector2_T10_NegateVector()
{
    printTitle("Vector2 Negate Vector");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2 = -v1;
    printVector2("v2 = -v1", v2);
}

void Vector2_T9_ProjV()
{
    printTitle("Vector2 Project v1 onto v2");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    Vector2<float> v3 = v1.ProjV(v2);
    printVector2("v3 = v1.ProjV(v2)", v3);

    float angle = v1.Angle(v2) * RAD_TO_DEG;
    Serial.print("angle = v1.Angle(v2) * RAD_TO_DEG ");
    Serial.println(angle);

    angle = v1.Angle(v3) * RAD_TO_DEG;
    Serial.print("angle = v1.Angle(v3) * RAD_TO_DEG ");
    Serial.println(angle);

    printSubTitle("Zero Degrees");
    angle = v2.Angle(v3) * RAD_TO_DEG;
    Serial.print("angle = v2.Angle(v3) * RAD_TO_DEG ");
    Serial.println(angle);

    printSubTitle("Normalized v2 & v3 have identical directions if dot is ONE");
    float dot = v2.Normalize() * v3.Normalize();
    Serial.print(" dot = v2.Normalize() * v3.Normalize() ");
    Serial.println(dot);
}

void Vector2_T8_A_ZComp()
{
    printTitle("Vector2 z-component of a cross prosuct");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    float ZComp = v1.ZComp(v2);
    Serial.print("ZComp = v1.ZComp(v2) ");
    Serial.println(ZComp);
}

void Vector2_T8_DotPerp()
{
    printTitle("Vector2 Dot-Perpendicular Product");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    float DotPerp = v1.DotPerp(v2);
    Serial.print("DotPerp = v1.DotPerp(v2) ");
    Serial.println(DotPerp);

    Vector3<float> v3(1, 2, 0);
    printVector3("v3", v3);

    Vector3<float> v4(3, 4, 0);
    printVector3("v4", v4);

    Vector3<float> v5 = v3 ^ v4;
    float zComponent = v5.z();
    Serial.print("zComponent = v5.z() ");
    Serial.println(zComponent);

    printSubTitle("Notice PerpDot and zComponent must be equal...");
}

void Vector2_T7_A_UnitPerp()
{
    printTitle("Vector2 Unit-Perpendicular");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2 = v1.Perp();
    printVector2("v2 = v1.Perp()", v2);

    float mag = v2.Magnitude();
    Serial.print("mag = v1 * v2 = ");
    Serial.println(mag);

    // Comparison with Perp()
    Vector2<float> v3 = v1.UnitPerp();
    printVector2("v3 = v1.UnitPerp()", v3);

    printSubTitle("The dot product of perpendicular vectors ought to be zero...");
    float dot = v1 * v2;
    Serial.print("dot = v1 * v2 = ");
    Serial.println(dot);
    // zero result
    dot = v1 * v3;
    Serial.print("dot = v1 * v3 = ");
    Serial.println(dot);
}

void Vector2_T7_Perp() // ----------------------- BUGFIX ok
{
    printTitle("Vector2 Perpendicular");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2 = v1.Perp();
    printVector2("v2 = v1.Perp()", v2);

    printSubTitle("The dot product of perpendicular vectors ought to be zero...");
    float dot = v1 * v2;
    Serial.print("dot = v1 * v2 ");
    Serial.println(dot);
}

void Vector2_T6_Angle()
{
    printTitle("Vector2 Angle");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    float angle = v1.Angle(v2) * RAD_TO_DEG;
    Serial.print("angle = v1.Angle(v2) * RAD_TO_DEG ");
    Serial.println(angle);
}

void Vector2_T5_Dot_Product()
{
    printTitle("Vector2 Dot Product");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2(3, 4);
    printVector2("v2", v2);

    float dot = v1.Dot(v2);
    Serial.print("dot = v1.Dot(v2) ");
    Serial.println(dot);

    dot = v1 * v2;
    Serial.print("dot = v1 * v2 ");
    Serial.println(dot);
}

void Vector2_T4_UnitVector_Normalize()
{
    printTitle("Vector2 UnitVector & Normalize");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    Vector2<float> v2 = v1.UnitVector();
    printVector2("v2 = v1.UnitVector", v2);

    float magnitude = v2.Magnitude();
    Serial.print("magnitude = v2.Magnitude ");
    Serial.println(magnitude);

    Vector2<float> v3 = v1.Normalize();
    printVector2("v3 = v1.Normalize", v3);

    float distance = v3.Distance();
    Serial.print("distance = v3.Distance ");
    Serial.println(distance);
}

void Vector2_T3_Magnitude_Distance()
{
    printTitle("Vector2 Magnitude & Distance");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);

    float magnitude = v1.Magnitude();
    Serial.print("magnitude ");
    Serial.println(magnitude);

    float distance = v1.Distance();
    Serial.print("distance ");
    Serial.println(distance);
}

void Vector2_T2_GetVector()
{
    printTitle("Vector2 GetVector");

    Vector2<float> v1(1, 2);
    printVector2("v1", v1);
    Vector2<float> v2 = v1.GetVector();
    printVector2("v2 = v1.GetVector", v2);
}

void Vector2_T1_Constructor()
{
    printTitle("Vector2 Constructor");

    Vector2<float> v1;
    printVector2("v1", v1);

    // float size = v1.Size();  NOT USED
    // Serial.print("v1 size ");
    // Serial.println(size);

    Vector2<float> v2(1, 2);
    printVector2("v2", v2);

    float x = v2.x();
    Serial.print("v2.x ");
    Serial.println(x);

    printSubTitle("array[] = {3, 4};");
    float array[] = {3, 4};
    Vector2<float> v3(array);
    printVector2("v3", v3);

    float y = v3.y();
    Serial.print("v3.y ");
    Serial.println(y);

    float element = v3.Element(0);
    Serial.print("v3 element(0) ");
    Serial.println(element);
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Vector2 tests, in order
    Vector2_T1_Constructor();
    Vector2_T2_GetVector();
    Vector2_T3_Magnitude_Distance();
    Vector2_T4_UnitVector_Normalize();
    Vector2_T5_Dot_Product();
    Vector2_T6_Angle();
    Vector2_T7_Perp();
    Vector2_T7_A_UnitPerp();
    Vector2_T8_DotPerp();
    Vector2_T8_A_ZComp();
    Vector2_T9_ProjV();
    Vector2_T10_NegateVector();
    Vector2_T11_VectorScalarProduct();
    Vector2_T12_VectorVectorAddition();
    Vector2_T13_VectorVectorSubtraction();
    Vector2_T14_DotProduct();
    Vector2_T15_COPY();
}

void loop()
{
}
