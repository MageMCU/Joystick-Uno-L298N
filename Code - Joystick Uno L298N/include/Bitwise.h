//
// Carpenter Software
// File: Class Bitwise.h
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

#ifndef Numerics_Bitwise_h
#define Numerics_Bitwise_h

#include <Arduino.h>

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    template <typename integer>
    class Bitwise
    {
    private:
        // Private Properties
        integer b_bits;
        integer b_maxSize;
        integer b_numberOfBits;
        // Private Methods
        integer b_powerOfTwo(integer bitNumber);
        integer b_sumPowerOfTwo(integer bitNumber);

    public:
        // Constructor
        Bitwise();

        // Public Methods - Bit Numbers 0, 1, 2, 3, 4, etc.
        // Bit Numbers
        void SetBitNumber(integer bitNumber);
        bool IsBitNumberSet(integer bitNumber);
        bool IsBitNumberSetToBitsValue(integer bitNumber, integer bitsValue);
        integer GetBitNumber();
        void ClearBitNumber(integer bitNumber);
        // Bits Value
        void SetBitsValue(integer);
        integer GetBitsValue();
        void ClearAllBits();
        String PrintBinaryBits();
    };

    template <typename integer>
    Bitwise<integer>::Bitwise()
    {
        // Used in for loops
        b_numberOfBits = (sizeof(integer) * (integer)8);
        // MINUS-ONE: assuming programmer might use a signed-integer.
        b_maxSize = b_sumPowerOfTwo(b_numberOfBits - (integer)1);
        b_bits = (integer)0;

        // DEBUG
        // Serial.print("number of bits: ");
        // Serial.print(b_numberOfBits);
        // Serial.print(" max size: ");
        // Serial.println(b_maxSize);
    }

    template <typename integer>
    integer Bitwise<integer>::b_powerOfTwo(integer bitNumber)
    {
        integer value = (integer)1;
        if (bitNumber >= (integer)0 && bitNumber < b_numberOfBits)
        {
            if (bitNumber == (integer)0)
                return value;

            for (int i = 0; i < (int)bitNumber; i++)
            {
                value *= (integer)2;
            }
        }
        else
        {
            Serial.println("Error - bitNumber size");
        }
        return value;
    }

    template <typename integer>
    integer Bitwise<integer>::b_sumPowerOfTwo(integer bitNumber)
    {
        integer sum = (integer)0;
        for (int poT = 0; poT < (int)bitNumber; poT++)
        {
            sum += b_powerOfTwo(poT);
        }
        return sum;
    }

    template <typename integer>
    void Bitwise<integer>::SetBitNumber(integer bitNumber)
    {
        b_bits |= b_powerOfTwo(bitNumber);
    }

    template <typename integer>
    bool Bitwise<integer>::IsBitNumberSet(integer bitNumber)
    {
        if ((b_bits & b_powerOfTwo(bitNumber)) != 0)
            return true;

        return false;
    }

    template <typename integer>
    bool Bitwise<integer>::IsBitNumberSetToBitsValue(integer bitNumber, integer bitsValue)
    {
        if ((bitsValue & b_powerOfTwo(bitNumber)) != 0)
            return true;

        return false;
    }

    template <typename integer>
    integer Bitwise<integer>::GetBitNumber()
    {
        // bit-numbers: 0, 1, 2, 3,  ... 13, 14, 15.
        if (b_bits > (integer)0 && b_bits < b_maxSize)
        {
            for (int bitNumber = 0; bitNumber < (int)b_numberOfBits; bitNumber++)
            {
                // GET FIRST BIT-NUMBER OF BITS
                // If there is more than one bit number,
                // use string or array to capture all bit numbers
                if (IsBitNumberSet((integer)bitNumber))
                    return (integer)bitNumber;
            }
        }
        else
        {
            Serial.println("Error - no such bit number");
        }
        return (integer)-1;
    }

    template <typename integer>
    void Bitwise<integer>::ClearBitNumber(integer bitNumber)
    {
        b_bits &= ~b_powerOfTwo(bitNumber);
    }

    template <typename integer>
    void Bitwise<integer>::SetBitsValue(integer bitsValue)
    {
        b_bits = bitsValue;
    }

    template <typename integer>
    integer Bitwise<integer>::GetBitsValue()
    {
        return (integer)b_bits;
    }

    template <typename integer>
    void Bitwise<integer>::ClearAllBits()
    {
        b_bits = (integer)0;
    }

    template <typename integer>
    String Bitwise<integer>::PrintBinaryBits()
    {
        String str = "bits:";
        // Count backwards
        for (int bitNumber = (int)b_numberOfBits - 1; bitNumber >= 0; bitNumber--)
        {
            // Insert Space-Char after every 4th digit
            if (((bitNumber + (integer)1) % (integer)4) == (integer)0)
                str += ' ';

            // Insert binary digit
            if (IsBitNumberSet(bitNumber))
                str += '1';
            else
                str += '0';
        }
        return str;
    }
}
#endif
