# Motor Movement Checklist (MMC)
- updated for clarity - 20240814
- [MMC](https://drive.google.com/file/d/1Cs-94KHmOfRT9C4QJFMCgcuQ93iygg6h)
## MMC Results for JUL
- [Results](https://drive.google.com/file/d/17yNw5FNRORWgtDyey11OeKGRMB9qV0SZ)
## How to Use
- The article 1009 - L298N Supplemental has information that explains how to use the MMC in conjunction while using the Step1_Joystick and Step2_JUL code.
## History
- The history in the development in the joystick algorithm took many years and many more to understand. See article **1001 - Joystick Algorithm**. The problem once understood was how to quickly setup the devices, (1) Joystick, (2) Arduino Uno and (3) L298N driver. The frustration for each new project was setting this system up, each every time. See article **1003 - L298N**. Over the last four years, I studied how the inputs giving 16 differ combinations for ***EN***, ***PWM***, ***LeftIN*** & ***RightIN*** which effected how the motors moved. Because of the joystick algorithm as described in the article (8 octants), there are a possible 128 combinations for the motors' output. See article **1009 - L298N Supplemental**. Setup for these devices today is much easier with the help of the **Motor Movement Checklist** posted here for your use. Have fun. No more frustration...
## Code Snippet

    '''
    // Joystick Algorithm
    joystick = Joystick<float>();

    // Constructor setup the x-range and the y-range
    mapInputFromDigital = LinearMap<float>(0, 1023, -1.0, 1.0);
    mapOutFromJoystick = LinearMap<float>(-1.0, 1.0, -255, 255);

    // New Code ----------------------------------L298N Setup
    // Arduino PINS
    int8_t ENA = 5;
    int8_t IN1 = 6;
    int8_t IN2 = 7;
    int8_t IN3 = 8;
    int8_t IN4 = 9;
    int8_t ENB = 10;
    // L298N PINS
    int8_t LeftEN = ENA;
    int8_t LeftA = IN1;
    int8_t LeftB = IN2;
    int8_t RightA = IN3;
    int8_t RightB = IN4;
    int8_t RightEN = ENB;

    // L298N Constructor
    motors = L298N(LeftEN, LeftA, LeftB,
                   RightA, RightB, RightEN);
    // Initiate L298N Pins
    motors.PinsL298N();

    // There are 16 combinations for EN, PWM, LeftIN & RightIN
    // USE: analogWrite(EN, PWM) & digitalWrite(LeftIN1, LOW)...
    // The Boolean Order (3, 2, 1, 0)
    // (3) EN (AB):         (Bit-3)
    // (2) PWM Inputs (AB): (Bit-2)
    // (1) LeftIN (1 & 2): ( Bit-1)
    // (0) Right N (3 & 4): (Bit-0)
    // EN A & B ---------------------------------------------
    // Bits-Value:  0     1     2     3     4     5     6     7
    // Bits:       0000  0001  0010  0011  0100  0101  0110  0111
    // EN B & A ----------------------------------------------
    // Bits-Value:  8     9     10    11    12    13    14    15
    // Bits:       1000  1001  1010  1011  1100  1101  1110  1111
    // -----------------------------------------------------------
    // NOTICE: Changing the BITS is much easier than switching
    // the actual wires around on the L298N module....
    // For my setup, bits 1010 was used...
    motors.Bits(BitsL298N::bits_1010);
    '''
