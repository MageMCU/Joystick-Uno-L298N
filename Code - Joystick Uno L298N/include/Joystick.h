//
// Carpenter Software
// File: Class Joystick.h
// Github: MageMCU
// Repository: Joystick-UNO-L298N
// Folder: Code
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

#ifndef Joystick_Algorithm_h
#define Joystick_Algorithm_h

#include <Arduino.h>
#include "MiscMath.h"
#include "Common.h"

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    template <typename real>
    class Joystick
    {
    private:
        // PROPERTIES
        // INPUT
        real _inputX;
        real _inputY;
        // OUTPUT
        real _outputLeft;
        real _outputRight;
        // METHODS
        void _joystick();

    public:
        // Constructor
        Joystick();
        ~Joystick() = default;
        // Getters
        bool IsLeftForward();
        bool IsRightForward();
        // METHODS
        void UpdateInputs(real inputX, real inputY);
        real OutLeft();
        real OutRight();
    };

    // Constructor
    template <typename real>
    Joystick<real>::Joystick()
    {
    }

    // Getters
    template <typename real>
    bool Joystick<real>::IsLeftForward()
    {
        return _outputLeft > (real)0;
    }

    template <typename real>
    bool Joystick<real>::IsRightForward()
    {
        return _outputRight > (real)0;
    }

    // Method update
    template <typename real>
    void Joystick<real>::UpdateInputs(real inputX, real inputY)
    {
        _inputX = inputX;
        _inputY = inputY;
        _joystick();
    }

    // Method output
    template <typename real>
    real Joystick<real>::OutLeft()
    {
        return _outputLeft;
    }

    // Method output
    template <typename real>
    real Joystick<real>::OutRight()
    {
        return _outputRight;
    }

    // Private Method
    template <typename real>
    void Joystick<real>::_joystick()
    {
        real outLeft = (real)0;
        real outRight = (real)0;

#ifdef DEBUG_JOYSTICK
        Debug("Joystick INPUT", _inputX, _inputY);
#endif

        real delta = absT<float>(absT<float>(_inputY) - absT<float>(_inputX));

        // Quadrant 1
        if ((_inputX > (real)0) && (_inputY > (real)0))
        {
            if (absT<float>(_inputX) >= absT<float>(_inputY))
            {
                // Within Octant 1 (++)
                // x-dominate
                // POS      POS
                outLeft = _inputX;
                // NEG      -POS
                outRight = -delta;
#ifdef DEBUG_JOYSTICK
                Debug("Octant-1", outLeft, outRight);
#endif
            }
            else if (absT<float>(_inputX) < absT<float>(_inputY))
            {
                // Within Octant 2 (++)
                // y-dominate
                // POS      POS
                outLeft = _inputY;
                // POS      POS
                outRight = delta;
#ifdef DEBUG_JOYSTICK
                Debug("Octant-2", outLeft, outRight);
#endif
            }
        } // Quadrant 2
        else if ((_inputX < (real)0) && (_inputY > (real)0))
        {
            if (absT<float>(_inputX) < absT<float>(_inputY))
            {
                // Within Octant 3 (-+)
                // y-dominate
                // POS      POS
                outLeft = delta;
                // POS      POS
                outRight = _inputY;
#ifdef DEBUG_JOYSTICK
                Debug("Octant-3", outLeft, outRight);
#endif
            }
            else if (absT<float>(_inputX) >= absT<float>(_inputY))
            {
                // Octant 4 (-+)
                // x-dominate
                // NEG      -POS
                outLeft = -delta;
                // POS      -NEG
                outRight = -_inputX;
#ifdef DEBUG_JOYSTICK
                Debug("Octant-4", outLeft, outRight);
#endif
            }
        } // Quadrant 3
        else if ((_inputX < (real)0) && (_inputY < (real)0))
        {
            if (absT<float>(_inputX) >= absT<float>(_inputY))
            {
                // Octant 5 (--)
                // x-dominate
                // NEG      NEG
                outLeft = _inputX;
                // POS      POS
                outRight = delta;
#ifdef DEBUG_JOYSTICK
                Debug("Octant-5", outLeft, outRight);
#endif
            }
            else if (absT<float>(_inputX) < absT<float>(_inputY))
            {
                // Octant 6 (--)
                // y-dominate
                // NEG      NEG
                outLeft = _inputY;
                // NEG      -POS
                outRight = -delta;
#ifdef DEBUG_JOYSTICK
                Debug("Octant-6", outLeft, outRight);
#endif
            }
        } // Quadrant 4
        else if ((_inputX > (real)0) && (_inputY < (real)0))
        {
            if (absT<float>(_inputX) < absT<float>(_inputY))
            {
                // Octant 7 (+-)
                // y-dominate
                // NEG      -POS
                outLeft = -delta;
                // NEG      NEG
                outRight = _inputY;
#ifdef DEBUG_JOYSTICK
                Debug("Octant-7", outLeft, outRight);
#endif
            }
            else if (absT<float>(_inputX) >= absT<float>(_inputY))
            {
                // Octant 8 (+-)
                // x-dominate
                // POS      POS
                outLeft = delta;
                // NEG      -POS
                outRight = -_inputX;
#ifdef DEBUG_JOYSTICK
                Debug("Octant-8", outLeft, outRight);
#endif
            }
        } // Forward & Backward
        else if ((_inputX == (real)0) && (_inputY != (real)0))
        {
            outLeft = _inputY;
            outRight = _inputY;
#ifdef DEBUG_JOYSTICK
            Debug("Forward-Backward", outLeft, outRight);
#endif
        } // Left & Right Turns
        else if ((_inputX != (real)0) && (_inputY == (real)0))
        {
            outLeft = _inputX;
            outRight = -_inputX;
#ifdef DEBUG_JOYSTICK
            Debug("Left-Right", outLeft, outRight);
#endif
        } // STOP - Requires OFFSET
        else if ((_inputX == (real)0) && (_inputY == (real)0))
        {
            outLeft = 0;
            outRight = 0;
#ifdef DEBUG_JOYSTICK
            Debug("STOP", outLeft, outRight);
#endif
        }

        _outputLeft = outLeft;
        _outputRight = outRight;
    }
}
#endif
