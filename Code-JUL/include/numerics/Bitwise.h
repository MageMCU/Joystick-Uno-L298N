//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: Class Bitwise.h
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
// RELEASE
//   2026-10-30  v7.3.0
//   Bitwise.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

// Bitwise<integer>: set, clear, and test single bits of an integer.
// Bit numbers run from 0 (least significant) to 8 * sizeof(integer) - 1.
// Used by L298N.h (IsBitNumberSetToBitsValue) to decode the four Bits() flags.

#ifndef Numerics_Bitwise_h
#define Numerics_Bitwise_h

#include <Arduino.h>

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    // TEACHING NOTES (v6.1.1)
    // A bit (binary digit) holds 0 or 1. An integer is stored as a row of
    // bits; an 8 bit integer (uint8_t) has bit numbers 7 down to 0. Bit 0 is
    // the least significant bit (LSB), worth 2^0 = 1; bit n is worth 2^n.
    // The value 11 is binary 1011: 8 + 0 + 2 + 1.
    // A mask is an integer with one bit set, 2^n for bit n, used to select
    // that bit. The bitwise operators work on every bit at once:
    //   a | b   OR:  a bit is 1 when it is 1 in a or in b (sets bits)
    //   a & b   AND: a bit is 1 when it is 1 in both (tests or keeps bits)
    //   ~a      NOT: every bit is inverted (with & it clears bits)
    // Example (L298N.h): Bits(BitsL298N::bits_1011) holds the value 11, and
    // IsBitNumberSetToBitsValue(3, 11) is true because 11 & 2^3 = 8 is not 0.
    // A template class (template <typename integer>) is written once for a
    // type parameter; Bitwise<uint8_t> and Bitwise<int> are two classes the
    // compiler generates from it.
    template <typename integer>
    class Bitwise
    {
    private:
        // Private Properties
        integer b_bits;
        integer b_maxSize;
        integer b_numberOfBits;
        // Private Methods
        // b_powerOfTwo(n) returns the mask 2^n; b_sumPowerOfTwo(n) returns
        // 2^0 + 2^1 + ... + 2^(n-1) = 2^n - 1, n bits all set.
        integer b_powerOfTwo(integer bitNumber);
        integer b_sumPowerOfTwo(integer bitNumber);

    public:
        // Constructor
        // The constructor counts the bits of the type: sizeof() gives bytes,
        // and one byte is 8 bits.
        Bitwise();

        // Public Methods - Bit Numbers 0, 1, 2, 3, 4, etc.
        // Bit Numbers
        // Bit numbers: set, test, and clear ONE bit of the stored value.
        void SetBitNumber(integer bitNumber);
        bool IsBitNumberSet(integer bitNumber);
        bool IsBitNumberSetToBitsValue(integer bitNumber, integer bitsValue);
        integer GetBitNumber();
        void ClearBitNumber(integer bitNumber);
        // Bits Value
        // Bits value: the whole stored integer at once.
        void SetBitsValue(integer);
        integer GetBitsValue();
        void ClearAllBits();
        String PrintBinaryBits();
    };

    // (integer)8 is a cast: it converts the constant 8 to the type of the
    // template parameter, so the arithmetic stays in one type.
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

    // REVIEW 20261008: for a bit number outside 0 to (number of bits - 1) this
    // function prints an error and then returns 1, which is the mask of bit 0.
    // SetBitNumber(), ClearBitNumber(), and the IsBitNumber...() tests
    // therefore
    // act on bit 0 for an invalid bit number. Example: SetBitNumber(8) on a
    // Bitwise<uint8_t> sets bit 0. L298N.h only uses bits 0 to 3.
    // 2^n by repeated multiplication: 1, 2, 4, 8, ... (n times 2).
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

    // OR with the mask sets bit n and leaves the others unchanged.
    // Example: 0101 | 0010 = 0111.
    template <typename integer>
    void Bitwise<integer>::SetBitNumber(integer bitNumber)
    {
        b_bits |= b_powerOfTwo(bitNumber);
    }

    // AND with the mask keeps bit n only; the result is not 0 when bit n
    // is 1. Example: 0101 & 0100 = 0100, so bit 2 is set.
    template <typename integer>
    bool Bitwise<integer>::IsBitNumberSet(integer bitNumber)
    {
        if ((b_bits & b_powerOfTwo(bitNumber)) != 0)
            return true;

        return false;
    }

    // The same test on a value passed in, without storing it.
    template <typename integer>
    bool Bitwise<integer>::IsBitNumberSetToBitsValue(integer bitNumber,
                                                     integer bitsValue)
    {
        if ((bitsValue & b_powerOfTwo(bitNumber)) != 0)
            return true;

        return false;
    }

    // REVIEW 20261008: returns the LOWEST bit number that is set (for the value
    // 5,
    // binary 0101, it returns 0, not 2). b_maxSize equals 2^(n-1) - 1, so a
    // value with the highest bit set, or equal to b_maxSize, reports an error.
    template <typename integer>
    integer Bitwise<integer>::GetBitNumber()
    {
        // bit-numbers: 0, 1, 2, 3,  ... 13, 14, 15.
        if (b_bits > (integer)0 && b_bits < b_maxSize)
        {
            for (int bitNumber = 0; bitNumber < (int)b_numberOfBits;
                 bitNumber++)
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

    // AND with the inverted mask clears bit n. Example for bit 2:
    // ~0100 = 1011, and 0111 & 1011 = 0011.
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

    // REVIEW 20261008: builds an Arduino String on the heap; the Uno has 2 KB
    // of RAM,
    // so call it for diagnostics only, not inside a fast control loop.
    // Prints the bits from the most significant (left) to bit 0 (right),
    // with a space every 4 bits, as the Bits table of L298N.h is written.
    template <typename integer>
    String Bitwise<integer>::PrintBinaryBits()
    {
        String str = "bits:";
        // Count backwards
        for (int bitNumber = (int)b_numberOfBits - 1; bitNumber >= 0;
             bitNumber--)
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
