//
// Carpenter Software
// File: Class Joystick.h
// Github: MageMCU
// Repository: Joystick-UNO-L298N
// Folder: Code-JUL
//
// By Jesse Carpenter (carpentersoftware.com)
//
// Testing Platform:
//  * MCU: Atmega328P
//  * IDE: PlatformIO
//  * Editor: VSCode
//
// MIT LICENSE
//
// NOTE: This implementation is the revised joystick algorithm.
// It includes improved octant routing, tolerance-based dead zone,
// and forward/backward direction getters for better motor control.
//

#ifndef Code_JUL_Joystick_h
#define Code_JUL_Joystick_h

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
        // Active octant number (0 = stop, 1-8 = directional regions)
        int _octant;
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
        real Left();
        real Right();
        int Octant();
    };

    // Constructor
    template <typename real>
    Joystick<real>::Joystick()
    {
        _inputX = (real)0;
        _inputY = (real)0;
        _outputLeft = (real)0;
        _outputRight = (real)0;
        _octant = 0;
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
    real Joystick<real>::Left()
    {
        return _outputLeft;
    }

    // Method output
    template <typename real>
    real Joystick<real>::Right()
    {
        return _outputRight;
    }

    // Method output
    template <typename real>
    int Joystick<real>::Octant()
    {
        return _octant;
    }

    // Private Method
    template <typename real>
    void Joystick<real>::_joystick()
    {
        // Tolerance defines the dead zone radius around the stick center.
        const real _tolerance = (real)0.001;

        // Local motor values, initialized to zero (safe default).
        real outLeft = (real)0;
        real outRight = (real)0;

#ifdef DEBUG_JOYSTICK
        Debug("Joystick INPUT", _inputX, _inputY);
#endif

        // Delta matches the revised Unity form:
        // abs(abs(x) - abs(y))
        real delta = absT<real>(absT<real>(_inputX) - absT<real>(_inputY));

        // --- OCTANT ZERO: CENTER STOP ---
        if (absT<real>(_inputX) < _tolerance && absT<real>(_inputY) < _tolerance)
        {
            outLeft = (real)0;
            outRight = (real)0;
            _octant = 0;
#ifdef DEBUG_JOYSTICK
            Debug("STOP", outLeft, outRight);
#endif
        }
        else
        {
            // --- X-DOMINANT OCTANTS (1, 4, 5, 8) ---
            if (absT<real>(_inputX) >= absT<real>(_inputY))
            {
                if (_inputX >= (real)0 && _inputY >= (real)0)
                {
                    outLeft = _inputX;
                    outRight = -delta;
                    _octant = 1;
#ifdef DEBUG_JOYSTICK
                    Debug("Octant-1", outLeft, outRight);
#endif
                }
                else if (_inputX <= (real)0 && _inputY >= (real)0)
                {
                    outLeft = -delta;
                    outRight = -_inputX;
                    _octant = 4;
#ifdef DEBUG_JOYSTICK
                    Debug("Octant-4", outLeft, outRight);
#endif
                }
                else if (_inputX <= (real)0 && _inputY <= (real)0)
                {
                    outLeft = _inputX;
                    outRight = delta;
                    _octant = 5;
#ifdef DEBUG_JOYSTICK
                    Debug("Octant-5", outLeft, outRight);
#endif
                }
                else if (_inputX >= (real)0 && _inputY <= (real)0)
                {
                    outLeft = delta;
                    outRight = -_inputX;
                    _octant = 8;
#ifdef DEBUG_JOYSTICK
                    Debug("Octant-8", outLeft, outRight);
#endif
                }
            }
            // --- Y-DOMINANT OCTANTS (2, 3, 6, 7) ---
            else if (absT<real>(_inputX) < absT<real>(_inputY))
            {
                if (_inputX >= (real)0 && _inputY >= (real)0)
                {
                    outLeft = _inputY;
                    outRight = delta;
                    _octant = 2;
#ifdef DEBUG_JOYSTICK
                    Debug("Octant-2", outLeft, outRight);
#endif
                }
                else if (_inputX <= (real)0 && _inputY >= (real)0)
                {
                    outLeft = delta;
                    outRight = _inputY;
                    _octant = 3;
#ifdef DEBUG_JOYSTICK
                    Debug("Octant-3", outLeft, outRight);
#endif
                }
                else if (_inputX <= (real)0 && _inputY <= (real)0)
                {
                    outLeft = _inputY;
                    outRight = -delta;
                    _octant = 6;
#ifdef DEBUG_JOYSTICK
                    Debug("Octant-6", outLeft, outRight);
#endif
                }
                else if (_inputX >= (real)0 && _inputY <= (real)0)
                {
                    outLeft = -delta;
                    outRight = _inputY;
                    _octant = 7;
#ifdef DEBUG_JOYSTICK
                    Debug("Octant-7", outLeft, outRight);
#endif
                }
            }
        }

        _outputLeft = outLeft;
        _outputRight = outRight;
    }
}
#endif
