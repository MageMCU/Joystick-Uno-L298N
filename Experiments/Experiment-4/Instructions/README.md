# Experiment-4: L298N Two Motors and the Bits Table

*Article 1004, Experiments for Joystick-Uno-L298N, STEM Starter Kit Series, Part 5. This guide is the text of the experiment in the article (DRAFT 3, 20261008). Labels such as Table-n, Code-n, Equation-n, and Circuit-n refer to the article; every Code-n listing is the main.cpp file named beside it in this repository.*

Safety: follow [Article 1009](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr), Safety and Supervision. A supervising adult operates the bench power supply.

**Objective.** Explain how the four flags of the Bits() method route the left and right commands to the pins of the L298N, then wire the second motor and complete the electrical part of L298N Setup.

**Builds on.** Experiment-3; Article 1009, L298N Setup and Table-3.

**Materials.** Six LEDs and six 220 Ω resistors (Lab 3); the second DC motor.

## Lab 1: Bitwise.h, Bits and Masks

**Objective.** Read, set, and clear single bits of an integer with the Bitwise class, and find the behavior of the class outside its bit range.

A bit mask is an integer with a 1 in each bit position to be tested or changed. The class builds the mask for bit n as 2 to the power n, then uses OR (|) to set the bit, AND with NOT (& ~) to clear it, and AND (&) to test it. The L298N class uses Bitwise<int> to read the four flags of a BitsL298N value.

**Code.** Experiments/Experiment-4/Code/src/1_Bitwise/main.cpp, Code-9. Uno and USB cable only. The program creates Bitwise<uint8_t>, an object for an 8 bit unsigned integer, and prints the binary pattern and the value after each of the calls SetBitNumber(0), SetBitNumber(2), GetBitNumber(), ClearBitNumber(0), GetBitNumber(), and SetBitNumber(8).

**Prediction.** Write the binary pattern and the decimal value expected after each call.

1. Run the program and record every line beside the prediction.

2. After SetBitNumber(0) and SetBitNumber(2), the pattern is bits: 0000 0101 and the value is 5. GetBitNumber() returns 0, the lowest bit that is set, not 2. After ClearBitNumber(0) the value is 4 and GetBitNumber() returns 2.

3. SetBitNumber(8) prints Error - bitNumber size, because an 8 bit integer has bits 0 to 7, but the value then reads 5: bit 0 was set. Find the cause in b_powerOfTwo() of include/Bitwise.h, which returns 1 after the error, and 1 is the mask of bit 0. Change the error case to return 0, upload, and confirm that the value stays 4.

4. Read the last two lines, which repeat the operations with the C operators alone: value |= (1 << 0) and value &= ~(1 << 0). The shift operator (<<) moves a 1 left by n places, which is 2 to the power n. This is the form used on the port registers in Article 1002, for example PORTB |= (1 << PB5).

**Expected output and verification.** The recorded values agree with steps 2 and 3, and after the correction in step 3 an out of range bit number no longer changes the value.

## Lab 2: TypeConv.h, Bytes and Words

**Objective.** Split a 16 bit word into two bytes and join them again, as is required to send a 10 bit ADC reading over a link that carries one byte at a time, such as I2C (Article 1002).

A byte is 8 bits; a word, in this class, is 16 bits (uint16_t), and a double word is 32 bits (uint32_t). The high byte of a word is its upper 8 bits, obtained by shifting the word right by 8 places; the low byte is the word AND 0xFF, the mask of the lower 8 bits. The prefix 0x marks a hexadecimal number, in which each digit stands for 4 bits.

**Code.** Experiments/Experiment-4/Code/src/2_TypeConv/main.cpp, Code-10. Uno and USB cable only. The program splits 1023 with WordTo2Bytes(), prints the two bytes in hexadecimal and binary, joins them with BytesToWord(), repeats the round trip for every value from 0 to 1023 and prints the number of mismatches, then splits millis() into four bytes and joins them.

**Prediction.** Predict the high and low bytes of 1023 and the number of mismatches.

1. Run the program and record the output.

2. In loop(), remove the comment marks from the three example lines, so that a local TypeConv object prints BytesToWord() before any conversion has been made. Upload and record the value over several passes. Then compare with the global object conv, whose members were set to zero before the program started.

**Expected output and verification.** 1023 is 0x03FF: high byte 0x3 (bits: 0000 0011), low byte 0xFF (bits: 1111 1111). The round trip produces 0 mismatches. In step 2 the local object prints a value that is not predictable from the code, because its members are never assigned before they are read; TypeConv has no constructor that sets them. A global variable is set to zero before the program starts, so the same mistake is hidden in a global object. The correction is a constructor that initializes every member; the numerics copy of TypeConv.h marks the same line with a REVIEW note.

## Lab 3: L298N.h, Reading the Flags on the Pins

The L298N class encodes four Boolean flags in one value of the BitsL298N enumeration. An enumeration is a C++ type whose values are a fixed list of names; BitsL298N has sixteen values, bits_0000 to bits_1111, written in the order bit 3, bit 2, bit 1, bit 0. Table-6 gives the meaning of each flag, from Article 1009, Table-3, and the L298N class.

**Table-6.** The four flags encoded by Bits(), from Article 1009, Table-3.

| Bit | Name | Value 1 | Value 0 |
|---|---|---|---|
| 3 | EN | _EN_A paired with the left IN pair, _EN_B with the right | Enable pins crossed |
| 2 | PWM | Left IN pair follows the left command | Left and right commands swapped |
| 1 | LeftIN | Positive command sets IN_A LOW, IN_B HIGH | Positive command sets IN_A HIGH, IN_B LOW |
| 0 | RightIN | Same as bit 1, for the right IN pair | Same as bit 1, for the right IN pair |

Bit 3 moves only the enable pins; the direction pins stay with their own commands. When bit 3 is 0, the speed of each channel is set by the command of the other channel while its direction is set by its own command. Lab 3 makes this visible without a motor.

**Wiring.** Circuit-4. The L298N logic header is disconnected and the bench supply is unplugged.

**Circuit-4.** Experiment-4, Lab 3. Six LEDs stand in for the six logic inputs of the L298N. [Circuit placeholder: six LEDs, each anode to one of D5, D6, D7, D8, D9, D10 through 220 Ω, cathodes to GND; L298N logic header disconnected.]

**Code.** Experiments/Experiment-4/Code/src/3_BitsLEDs/main.cpp, Code-11. The program calls PinsL298N(), selects the Bits() value typed as one hexadecimal digit, 0 to f, and applies a fixed test command, left 255 and right −64, with UpdateL298N(). The enable LED that receives 255 is bright and the one that receives 64 is dim; the four direction LEDs show which input of each pair is HIGH. The program also prints the six pins: the duty cycle of D5 and D10, read from the timer registers of the ATmega328P (Article 1002), and the level of D6 to D9.

**Prediction.** For the digits 0, 2, a, and f, use Table-6 to predict the six pins before the digit is sent.

**Table-7.** Pin states printed for the test command, left 255 and right −64 (confirmed in simulation of the ATmega328P). D5 and D10 are duty values; D6 to D9 are logic levels.

| Digit (bits) | D5 | D6 | D7 | D8 | D9 | D10 |
|---|---|---|---|---|---|---|
| 0 (0000) | 255 | 0 | 1 | 1 | 0 | 64 |
| 2 (0010) | 255 | 1 | 0 | 1 | 0 | 64 |
| a (1010) | 64 | 1 | 0 | 1 | 0 | 255 |
| f (1111) | 255 | 0 | 1 | 1 | 0 | 64 |

1. Upload the program. Send each of the digits 0, a, and f, and record the six LEDs and the printed line beside the prediction.

2. Send 2 and then a. The two values differ only in bit 3. Record which LEDs changed and explain the change with Table-6.

3. Disconnect the USB cable and remove the six LEDs.

**Expected output and verification.** The observed pins agree with Table-7. Changing bit 3 exchanges the bright and dim enable LEDs while the direction LEDs do not change.

## Lab 4: Wiring the Second Motor

**Wiring.** Article 1009, Circuit-1, complete. Complete Article 1009, L298N Setup, steps 1 to 4, with both motors connected, then step 6 (apply power in order) and step 8 (measure the motor bus with the motors stopped). Raise the drive so that both wheels turn freely.

**Expected output and verification.** Both motors are connected, the unloaded motor bus voltage is recorded, and no motor turns while the push button state is OFF. The Bits() value is selected in Experiment-5 with the joystick, because the Motor Movement Checklist tests the joystick and the motors together.

**Watch for.** An LED that never lights in Lab 3 (the LED reversed, or a pin number that does not match the wire). A motor that turns at power up (an enable jumper still fitted; unplug the supply at once).


## Related Articles

- [1000 Introduction Robotics](https://drive.google.com/file/d/1zrVOhhQ5teQx9XW6AWrdjCl55dKjni2I)
- [1001 Joystick Algorithm](https://drive.google.com/file/d/1bwthz-K4lz5GrDGjECLExFufym-j3RJO)
- [1002 Arduino Uno: Pins, Ports, and Peripherals](https://drive.google.com/file/d/18wztuThpOEHqyXEClBrly5ab4cSqFqrE)
- [1003 L298N Motor Driver](https://drive.google.com/file/d/1_BPALBsqgglQh7zsPZBlocXSksMZQOUq)
- [1005 Study of Quaternions](https://drive.google.com/file/d/1xQS_DkKx-wXtF7fm8C6GPfF8NV9Qoxnr)
- [1009 Parent, Teacher, and Student Guide to Joystick-Uno-L298N](https://drive.google.com/file/d/14dXfhFfpZYOAXZBTmZFWcl6XGlfDwLkr)
- [1009 Supplemental, Motor Movement Checklist](https://drive.google.com/file/d/1PRdfuvDG60wM1WI8K41EqfcYhycW6bE4)
- [1020 Note, Button.h and Timer.h](https://drive.google.com/file/d/1mLdqeahOOybPuAjdK8CqOVFJma677UWk)

Copyright Jesse Carpenter (Carpenter Software). Software: MIT License; see the repository LICENSE and DISCLAIMER.md.
