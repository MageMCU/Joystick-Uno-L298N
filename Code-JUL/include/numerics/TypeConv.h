//
// Author: Jesse Carpenter
// Website: Carpenter Software
//         (carpentersoftware.com)
// File: Class TypeConv.h
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
//   TypeConv.h last changed: 2026-10-27  v6.7.0
//   https://github.com/MageMCU/Joystick-Uno-L298N (RELEASES.md)
//

// TypeConv: split a 16 bit word into two bytes or a 32 bit double word into
// four bytes, and join them again (for example to send a 10 bit ADC reading
// over a link that carries one byte at a time).

#ifndef Type_Conversion_h
#define Type_Conversion_h

#include <Arduino.h>

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    // TEACHING NOTES (v6.1.1)
    // A byte is 8 bits (0 to 255). A word here is 16 bits (uint16_t, 0 to
    // 65535) and a double word 32 bits (uint32_t). The fixed width types
    // uint8_t, uint16_t, and uint32_t come from <stdint.h>; u means unsigned
    // (no sign, never negative) and the number is the width in bits.
    // The high byte of a word holds bits 15 to 8, the low byte bits 7 to 0.
    // Hexadecimal (base 16, written 0x...) shows 4 bits per digit, so
    // 0x03FF = binary 0000 0011 1111 1111 = 1023, the largest ADC reading:
    // high byte 0x03 = 3, low byte 0xFF = 255, and 3 * 256 + 255 = 1023.
    // Two operations split and join the bytes:
    //   x >> n   shift right: moves every bit n places toward bit 0
    //   x << n   shift left:  moves every bit n places up
    //   x & 0xff mask: keeps the low 8 bits only
    class TypeConv
    {
    private:
        // REVIEW 20261008: the shifts and masks below give the same result on
        // any
        // processor; byte order in memory (the AVR is little endian) does not
        // affect them. The comment below refers to bit numbering.
        // AVR-LSB Word Order bit15, bit14, ... , bit1, bit0.
        // Long 4 -------------------
        uint32_t b_dWordIN;
        uint32_t b_dWordOUT;
        // Bytes
        uint8_t b_byte3;
        uint8_t b_byte2;
        uint8_t b_byte1;
        uint8_t b_byte0;
        // Int 2 -------------------
        uint16_t b_wordIN;
        uint16_t b_wordOUT;
        // Bytes
        uint8_t b_byteHi;
        uint8_t b_byteLo;

        // Private Methods
        void b_setHiByte();
        void b_setLoByte();
        void b_glue2Bytes();
        uint16_t b_fGlue2Bytes(uint8_t hi, uint8_t lo);
        //
        void b_setByte3();
        void b_setByte2();
        void b_setByte1();
        void b_setByte0();
        void b_glue4Bytes();
        uint32_t b_fGlue4Bytes(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0);

    public:
        // Constructor
        // REVIEW 20261008: the default constructor leaves every member
        // uninitialized.
        // A global TypeConv starts at zero; a local one holds unpredictable
        // values
        // until a conversion has been made (for example BytesToWord() called
        // before WordTo2Bytes()).
        TypeConv() = default;
        ~TypeConv() = default;

        // Public Methods
        // Split: a word into two bytes, a double word into four. Join: the
        // BytesTo...() methods glue the bytes back into the original value.
        void WordTo2Bytes(uint16_t word);
        void DWordTo4Bytes(uint32_t dWord);
        uint8_t GetHiByte();
        uint8_t GetLoByte();
        uint16_t BytesToWord();
        uint32_t BytesToDWord();
        uint16_t BytesToWord(uint8_t hi, uint8_t lo);
        uint32_t BytesToDWord(uint8_t b3, uint8_t b2,
                              uint8_t b1, uint8_t b0);

        // NEW Methods
        uint8_t GetByte3();
        uint8_t GetByte2();
        uint8_t GetByte1();
        uint8_t GetByte0();
        // REVIEW 20261008: identical to DWordTo4Bytes(); the two differ only in
        // the
        // capital letter.
        void dWordTo4Bytes(uint32_t dWord);
    };

    void TypeConv::WordTo2Bytes(uint16_t uint16)
    {
        b_wordIN = uint16;
        b_setHiByte();
        b_setLoByte();
    }

    void TypeConv::DWordTo4Bytes(uint32_t dWord)
    {
        b_dWordIN = dWord;
        b_setByte3();
        b_setByte2();
        b_setByte1();
        b_setByte0();
    }

    uint8_t TypeConv::GetHiByte()
    {
        return b_byteHi;
    }

    uint8_t TypeConv::GetLoByte()
    {
        return b_byteLo;
    }

    uint16_t TypeConv::BytesToWord()
    {
        b_glue2Bytes();
        return b_wordOUT;
    }

    uint32_t TypeConv::BytesToDWord()
    {
        b_glue4Bytes();
        return b_dWordOUT;
    }

    uint8_t TypeConv::GetByte3()
    {
        return b_byte3;
    }

    uint8_t TypeConv::GetByte2()
    {
        return b_byte2;
    }

    uint8_t TypeConv::GetByte1()
    {
        return b_byte1;
    }

    uint8_t TypeConv::GetByte0()
    {
        return b_byte0;
    }

    uint16_t TypeConv::BytesToWord(uint8_t hi, uint8_t lo)
    {
        return b_fGlue2Bytes(hi, lo);
    }

    uint32_t TypeConv::BytesToDWord(uint8_t b3, uint8_t b2,
                                    uint8_t b1, uint8_t b0)
    {
        return b_fGlue4Bytes(b3, b2, b1, b0);
    }

    void TypeConv::dWordTo4Bytes(uint32_t dWord)
    {
        b_dWordIN = dWord;
        b_setByte3();
        b_setByte2();
        b_setByte1();
        b_setByte0();
    }

    // Shift right by 8 moves bits 15 to 8 down to 7 to 0; the mask keeps them.
    // Example: 1023 >> 8 = 3.
    void TypeConv::b_setHiByte()
    {
        b_byteHi = (uint8_t)((b_wordIN >> 8) & 0xff);
    }

    // The mask keeps bits 7 to 0. Example: 1023 & 0xff = 255.
    void TypeConv::b_setLoByte()
    {
        b_byteLo = (uint8_t)(b_wordIN & 0xff);
    }

    void TypeConv::b_glue2Bytes()
    {
        b_wordOUT = b_fGlue2Bytes(b_byteHi, b_byteLo);
    }

    // Byte 3 holds bits 31 to 24, byte 0 bits 7 to 0; each shift is 8 times
    // the byte number.
    void TypeConv::b_setByte3()
    {
        b_byte3 = (uint8_t)((b_dWordIN >> 24) & 0xff);
    }

    void TypeConv::b_setByte2()
    {
        b_byte2 = (uint8_t)((b_dWordIN >> 16) & 0xff);
    }

    void TypeConv::b_setByte1()
    {
        b_byte1 = (uint8_t)((b_dWordIN >> 8) & 0xff);
    }

    void TypeConv::b_setByte0()
    {
        b_byte0 = (uint8_t)(b_dWordIN & 0xff);
    }

    void TypeConv::b_glue4Bytes()
    {
        b_dWordOUT = b_fGlue4Bytes(b_byte3, b_byte2, b_byte1, b_byte0);
    }

    // Join: the cast to uint16_t widens the byte first, so the shift by 8
    // does not lose bits; OR places the low byte in bits 7 to 0.
    // Example: (3 << 8) | 255 = 768 + 255 = 1023.
    uint16_t TypeConv::b_fGlue2Bytes(uint8_t hi, uint8_t lo)
    {
        return ((((uint16_t)hi << 8) & (uint16_t)0xff00) | (uint16_t)lo);
    }

    // The same for four bytes: each byte is widened, shifted to its place
    // (24, 16, 8, 0), and joined with OR.
    uint32_t TypeConv::b_fGlue4Bytes(uint8_t b3, uint8_t b2,
                                     uint8_t b1, uint8_t b0)
    {
        return ((((uint32_t)b3 << 24) & (uint32_t)0xff000000) |
                (((uint32_t)b2 << 16) & (uint32_t)0x00ff0000) |
                (((uint32_t)b1 << 8) & (uint32_t)0x0000ff00) |
                (uint32_t)b0);
    }
}
#endif
