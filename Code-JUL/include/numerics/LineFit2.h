//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: Class LineFit2.h
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
// CREDIT: the algorithm is by David Eberly, Geometric Tools
// (https://www.geometrictools.com), from the Geometric Tools Engine file
// GTE/Mathematics/ApprHeightLine2.h. His notice follows, as the Boost
// Software License requires:
//
//   David Eberly, Geometric Tools, Redmond WA 98052
//   Copyright (c) 1998-2026
//   Distributed under the Boost Software License, Version 1.0.
//   https://www.boost.org/LICENSE_1_0.txt
//   https://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// ADAPTATION: adapted by Jesse Carpenter, Carpenter Software, 20261008.
// Changes from the original: rewritten without the C++ standard library
// (std::array, std::pair, and virtual ApprQuery are not available on the
// Uno); input is two arrays x[] and y[] instead of Vector2 points; added
// Intercept(), XIntercept(), Evaluate(), and RmsError(). The adapted
// portions remain under the Boost Software License, Version 1.0; Carpenter
// Software's additions are released under the MIT License. This file is
// not endorsed by David Eberly or Geometric Tools, and any error in the
// adaptation is Carpenter Software's.
//

// LineFit2<real>: least squares fit of a straight line to height data
// (x[i], y[i]). The line is
//     y - yAvr = a * (x - xAvr)
// where (xAvr, yAvr) is the mean of the points and a is the slope. It
// minimizes the sum of the squared vertical errors
//     sum of [a * (x[i] - xAvr) - (y[i] - yAvr)]^2.
//
// Robot use: fit measured wheel speed (y) against PWM command (x) to find
// each motor's slope and the PWM at which it starts to turn (the x
// intercept), from measurements instead of by trial.
//
// Usage:
//     float pwm[]   = {60, 100, 140, 180, 220};
//     float speed[] = {12, 38, 61, 88, 113};
//     LineFit2<float> fit;
//     if (fit.Fit(pwm, speed, 5))
//     {
//         float a = fit.Slope();        // speed per PWM step
//         float b = fit.Intercept();    // y at x = 0
//         float x0 = fit.XIntercept();  // PWM where speed reaches zero
//     }

#ifndef Numerics_LineFit2_h
#define Numerics_LineFit2_h

#include <Arduino.h>

namespace csjc
{
    template <typename real>
    class LineFit2
    {
    private:
        real m_xAvr;
        real m_yAvr;
        real m_slope;
        bool m_valid;

    public:
        // Construction: no fit yet; all parameters are zero.
        LineFit2()
            : m_xAvr((real)0), m_yAvr((real)0), m_slope((real)0), m_valid(false)
        {
        }

        // Fit a line to n points. Returns false (and sets every parameter to
        // zero) when n < 2 or when all x values are equal, because a
        // vertical line is not a function of x.
        bool Fit(const real x[], const real y[], int n)
        {
            m_xAvr = (real)0;
            m_yAvr = (real)0;
            m_slope = (real)0;
            m_valid = false;
            if (n < 2)
                return false;

            // Mean of the points.
            real xSum = (real)0;
            real ySum = (real)0;
            for (int i = 0; i < n; i++)
            {
                xSum += x[i];
                ySum += y[i];
            }
            real xAvr = xSum / (real)n;
            real yAvr = ySum / (real)n;

            // Covariance terms about the mean. Subtracting the mean first
            // keeps the sums small, which matters with 32 bit floats.
            real covar00 = (real)0;
            real covar01 = (real)0;
            for (int i = 0; i < n; i++)
            {
                real dx = x[i] - xAvr;
                real dy = y[i] - yAvr;
                covar00 += dx * dx;
                covar01 += dx * dy;
            }

            if (covar00 > (real)0)
            {
                m_xAvr = xAvr;
                m_yAvr = yAvr;
                m_slope = covar01 / covar00;
                m_valid = true;
            }
            return m_valid;
        }

        bool IsValid() const { return m_valid; }
        real XAverage() const { return m_xAvr; }
        real YAverage() const { return m_yAvr; }
        real Slope() const { return m_slope; }

        // y at x = 0: b in y = a * x + b.
        real Intercept() const { return m_yAvr - m_slope * m_xAvr; }

        // x at y = 0. Returns NaN for a horizontal line (slope 0).
        real XIntercept() const
        {
            if (m_slope == (real)0)
                return NAN;
            return m_xAvr - m_yAvr / m_slope;
        }

        // y predicted by the line at x.
        real Evaluate(real x) const { return m_yAvr + m_slope * (x - m_xAvr); }

        // Squared vertical error of one point (as in GTE ApprHeightLine2).
        real Error(real x, real y) const
        {
            real d = m_slope * (x - m_xAvr) - (y - m_yAvr);
            return d * d;
        }

        // Root mean square vertical error of n points: the typical distance,
        // in y units, between the data and the line.
        real RmsError(const real x[], const real y[], int n) const
        {
            if (n < 1)
                return NAN;
            real sum = (real)0;
            for (int i = 0; i < n; i++)
                sum += Error(x[i], y[i]);
            return (real)sqrt(sum / (real)n);
        }
    };
}

#endif /* Numerics_LineFit2_h */
