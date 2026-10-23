//
// Carpenter Software
// File: L06_Statistics.h
// Github: MageMCU
// Repository: Joystick-Uno-L298N
// Folder: Code-JUL/src/Step5_MathLessons/lessons
// Namespace: L06_Statistics, selected with LESSON 6 in Step5_MathLessons/main.cpp
// Origin: MageMCU/Numerics, Algebra/src/TESTS/TestStatistics.h (merged 20261008)
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

// TEACHING NOTES (v6.1.1)
// Lesson 6: descriptive statistics. The mean, the sample variance, the
// standard deviation, the median, and the two sorting methods are
// explained in include/numerics/Statistics.h, with a worked example.
// The data are random values (lesson 5), so the numbers differ on each
// run; check that they are reasonable:
//   * values spread evenly over [a, b): the mean is near (a + b) / 2 and
//     the standard deviation near (b - a) / sqrt(12) = 0.29 (b - a)
//   * the median of such values is near the mean as well
// Remember that the constructor sorts the caller's array: after it, the
// array, GetElement(), and GetSorted() all read in increasing order.
// The topics run T01 to T06 (see Setup()).
#ifndef Lesson_L06_Statistics_h
#define Lesson_L06_Statistics_h

// Number of topics of this lesson; main.cpp checks TOPIC against it.
#define LESSON_TOPICS 6

#include <Arduino.h>
#include "Debug.h"
#include "numerics/RandomNumber.h"
#include "numerics/Statistics.h"

namespace L06_Statistics
{
// Carpenter Software - Jesse Carpenter
using namespace csjc;

// T06: 100 random values in [0, 10) placed one by one with Queue(); the
// mean should be near 5 and the standard deviation near 2.9.
// ---------------------------------------------------------------
// Statistics_T06_Queue100 (teaching notes, v6.3.0)
// Hint: Queue100, fill a set of 100 values with Queue().
// Purpose: a larger sample, to show the mean and the standard deviation
// settle near their expected values.
// What is learnt:
//   const int size = 100; an array size must be a constant expression in
//                  C++; a variable length array is not standard C++.
//   Instantiation before the data: the object is built over an
//                  uninitialized array, and Queue() fills it afterwards.
//   Expected values for [0, 10): mean 5, standard deviation
//                  10 / sqrt(12) = 2.89.
// Expected output (random values; 100 values first):
//   Average: 5.16
//   Standard Deviation: 2.74
// ---------------------------------------------------------------
void Statistics_T06_Queue100()
{
    printTitle(F("Statistics T06 Queue of 100 values"));

    const int size = 100; // const: fixed size array, not a variable length array (20261008)
    float tuples[size];
    Statistics<float> stats = Statistics<float>(tuples, size);
    RandomNumber<float> randomNumber = RandomNumber<float>((float)0, (float)10);

    int cnt = 0;
    while (cnt < size)
    {
        float value = randomNumber.Random();
        stats.Queue(value, cnt);

        value = stats.GetElement(cnt);
        Serial.println(String(value, 2));

        cnt++;
    }

    Serial.print("Average: ");
    Serial.println(String(stats.Average(), 2));
    Serial.print("Standard Deviation: ");
    Serial.println(String(stats.StandardDeviation(), 2));
}

// T05: ten values replaced by random ones, then QueueReset() writes the
// mean plus 10000 into the last place. One value far from the others
// makes the standard deviation jump into the thousands (about 3162 =
// 10000 / sqrt(10)): the standard deviation is sensitive to a single
// outlier, a value far from the rest.
// ---------------------------------------------------------------
// Statistics_T05_QueueReset (teaching notes, v6.3.0)
// Hint: QueueReset, add one outlier to show its effect.
// Purpose: to replace values one at a time with Queue(), then show how a
// single outlier changes the standard deviation.
// What is learnt:
//   Brace initializer  float tuples[]{3.2, 5.3, ...}; a C++11 list
//                  initialization of an array without the = sign.
//   Setter         Queue(value, index) writes one element of the set; the
//                  getter GetElement(index) reads it back.
//   Outlier        a value far from the rest. QueueReset() writes the mean
//                  plus 10000 into the last place, and the standard
//                  deviation jumps from about 3 to about 3162.
// Expected output (random values):
//   0 5.31 ... 9 8.60
//   Average: 5.02   Standard Deviation: 3.33
//   Standard Deviation: 3162.41
// ---------------------------------------------------------------
void Statistics_T05_QueueReset()
{
    printTitle(F("Statistics T05 Queue and QueueReset"));

    float tuples[]{3.2, 5.3, 7.0, 2.2, 9.8, 4.6, 0.5, 4.5, 7.4, 6.5};
    int size = 10;

    Statistics<float> stats = Statistics<float>(tuples, size);
    RandomNumber<float> randomNumber = RandomNumber<float>((float)0, (float)10);
    float randomNum;

    // randomNumber.Random()
    for (int i = 0; i < size; i++)
    {
        randomNum = randomNumber.Random();
        stats.Queue(randomNum, i);
        Serial.print(i);
        Serial.print(" ");
        Serial.println(String(stats.GetElement(i), 2));
    }

    Serial.print("Average: ");
    Serial.println(String(stats.Average(), 2));
    Serial.print("Standard Deviation: ");
    Serial.println(String(stats.StandardDeviation(), 2));

    //
    stats.QueueReset();
    Serial.println("Purpose of Queue Reset is to increase the SD");
    Serial.println("by arbitrarily increasing one of the elements...");
    Serial.print("Standard Deviation: ");
    Serial.println(String(stats.StandardDeviation(), 2));
}

// T04: 200 random values in [-1.9, 2.3). After sorting, element 0 is the
// smallest and element 199 the largest; the median and the mean should
// both be near 0.2, the middle of the interval.
// ---------------------------------------------------------------
// Statistics_T04_Median (teaching notes, v6.3.0)
// Hint: Median, the middle value of the sorted set.
// Purpose: the median, the mean, and the extremes of 200 values.
// What is learnt:
//   Median         sort the values; with an odd count take the middle
//                  one, with an even count the mean of the two middle
//                  ones. Unlike the mean, one extreme value hardly moves
//                  it.
//   Min and max    after the sort, element 0 is the smallest value and
//                  element size - 1 the largest.
//   printResult()  prints a label and a float with 2 decimals.
// Expected output (random values; 200 values first):
//   Average: 0.21   Standard Deviation: 1.22   Median: 0.21
//   Min Value: -1.90   Max Value: 2.30
// ---------------------------------------------------------------
void Statistics_T04_Median()
{
    printTitle(F("Statistics T04 Median"));

    float tuples[200];
    int size = 200;
    RandomNumber<float> rnd = RandomNumber<float>(-1.9, 2.3);

    for (int i = 0; i < size; i++)
    {
        // CAUTION: assigning random numbers...
        tuples[i] = rnd.Random();
        // DEBUG - Original ORDER
        Serial.print(String(i));
        Serial.print(" ");
        Serial.println(String(tuples[i], 2));
    }

    // ok
    Statistics<float> stats = Statistics<float>(tuples, size);

    printResult("Average: ", stats.Average());
    printResult("Standard Deviation: ", stats.StandardDeviation());
    printResult("Median: ", stats.Median());
    printResult("Min Value: ", stats.GetElement(0));
    printResult("Max Value: ", stats.GetElement(size - 1));

    // Debug- Sorted data taken from the class
    // Serial.println("--------------------");
    // Serial.println("--------------------");
    // for (int i = 0; i < size; i++)
    // {
    //     Serial.print(String(i));
    //     Serial.print(" ");
    //     Serial.println(String(stats.GetSorted(i), 2));
    // }
    // Serial.println("--------------------");
    // Serial.println("--------------------");

    // DEBUG - Sorted data taken from tuples[]-(as shown above)
    // for (int i = 0; i < size; i++)
    // {
    //     Serial.print(String(i));
    //     Serial.print(" ");
    //     Serial.println(String(tuples[i], 2));
    // }
}

// T03: ten random values in [-99999.9, 99999.9); the standard deviation
// should be near 0.29 (200000) = 58000, though ten values scatter a lot.
// ---------------------------------------------------------------
// Statistics_T03_StandardDeviation (teaching notes, v6.3.0)
// Hint: StandardDeviation, how far the values spread from the mean.
// Purpose: to compute the spread of ten random values.
// What is learnt:
//   Variance       the mean of the squared distances from the mean; the
//                  class divides by n - 1 (the sample variance).
//   Standard deviation  the square root of the variance, in the units of
//                  the data. For values spread evenly over [a, b) it is
//                  near (b - a) / sqrt(12), here about 58000.
// Expected output (random values):
//   ten values, then for example  Standard Deviation: 46498.41
// ---------------------------------------------------------------
void Statistics_T03_StandardDeviation()
{
    printTitle(F("Statistics T03 Standard Deviation"));

    float tuples[10];
    int size = 10;
    RandomNumber<float> rnd = RandomNumber<float>(-99999.9, 99999.9);

    for (int i = 0; i < size; i++)
    {
        // CAUTION: assigning random numbers...
        tuples[i] = rnd.Random();
        // DEBUG - Original ORDER
        Serial.print(String(i));
        Serial.print(" ");
        Serial.println(String(tuples[i], 2));
    }

    Statistics<float> stats = Statistics<float>(tuples, size);
    printResult("Standard Deviation: ", stats.StandardDeviation());
}

// T02: the mean of ten random values from -99999.9 to 99999.9; it can
// lie far from 0, because ten values are few.
// ---------------------------------------------------------------
// Statistics_T02_Average (teaching notes, v6.3.0)
// Hint: Average, the mean of the set.
// Purpose: to compute the mean of ten random values with Average().
// What is learnt:
//   Mean           the sum of the values divided by their number.
//   Sample size    with ten values from -99999.9 to 99999.9 the mean can
//                  lie tens of thousands from 0, the middle of the
//                  interval; T06 with 100 values lands much closer. Few
//                  samples give a rough estimate.
//   The values are printed before the constructor runs, so this list is
//   in the original, unsorted order.
// Expected output (random values):
//   0 59461.12 ... 9 30808.82
//   Average: 4354.06
// ---------------------------------------------------------------
void Statistics_T02_Average()
{
    printTitle(F("Statistics T02 Average"));

    float tuples[10];
    int size = 10;
    RandomNumber<float> rnd = RandomNumber<float>(-99999.9, 99999.9);

    for (int i = 0; i < size; i++)
    {
        // CAUTION: assigning random numbers...
        tuples[i] = rnd.Random();
        // DEBUG - Original ORDER
        Serial.print(String(i));
        Serial.print(" ");
        Serial.println(String(tuples[i], 2));
    }

    Statistics<float> stats = Statistics<float>(tuples, size);
    printResult("Average: ", stats.Average());
}

// T01: the size of the set, Array Size: 10.00 (cast to float: printResult()
// prints a float with 2 decimals, but String(int, 2) would print the int
// in base 2, 1010; FIXED 20261022, v6.1.3), then ten random values,
// printed after the constructor: they appear in increasing order,
// because the constructor sorted them.
// ---------------------------------------------------------------
// Statistics_T01_Constructor (teaching notes, v6.3.0)
// Hint: Constructor, build a Statistics object over an existing array.
// Purpose: how to declare and instantiate Statistics, and the side
// effect of its constructor on the caller's data.
// What is learnt:
//   Instantiation  Statistics<float>(tuples, size) receives a pointer to
//                  the first element of the array and the number of
//                  elements. A pointer holds an address: the object reads
//                  and writes the caller's array; it keeps no copy (2 KB
//                  of RAM leaves no room for one).
//   Side effect    a change a function makes beyond its return value. The
//                  constructor sorts tuples[] in place to find the median,
//                  so the values print in increasing order.
//   Getters        GetTuplesSize() and GetElement(i).
//   Tuple          the class name for one data value of the set.
// Expected output (random values):
//   Array Size: 10.00
//   ten values in increasing order, for example -56549.89, -34731.28, ...
// ---------------------------------------------------------------
void Statistics_T01_Constructor()
{
    printTitle(F("Statistics T01 Constructor"));

    float tuples[10];
    int size = 10;
    RandomNumber<float> rnd = RandomNumber<float>(-99999.9, 99999.9);

    for (int i = 0; i < size; i++)
    {
        // CAUTION: assigning random numbers...
        tuples[i] = rnd.Random();
        // DEBUG - Original ORDER
        // Serial.print(String(i));
        // Serial.print(" ");
        // Serial.println(String(tuples[i], 2));
    }

    Statistics<float> stats = Statistics<float>(tuples, size);

    float v;
    printResult("Array Size: ", (float)stats.GetTuplesSize());
    for (int i = 0; i < size; i++)
    {
        v = stats.GetElement(i);
        Serial.println(String(v, 2));
    }
}

void Setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    // Topics, in order. TOPIC in main.cpp selects one; 0 selects all.
#if TOPIC == 0 || TOPIC == 1
    Statistics_T01_Constructor();
#endif
#if TOPIC == 0 || TOPIC == 2
    Statistics_T02_Average();
#endif
#if TOPIC == 0 || TOPIC == 3
    Statistics_T03_StandardDeviation();
#endif
#if TOPIC == 0 || TOPIC == 4
    Statistics_T04_Median();
#endif
#if TOPIC == 0 || TOPIC == 5
    Statistics_T05_QueueReset();
#endif
#if TOPIC == 0 || TOPIC == 6
    Statistics_T06_Queue100();
#endif
}

void Loop()
{
}
} // namespace L06_Statistics

#endif // Lesson_L06_Statistics_h
