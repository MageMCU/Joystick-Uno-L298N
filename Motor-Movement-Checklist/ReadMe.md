# Motor Movement Checklist (MMC)
- updated 20240814
- [MMC](https://drive.google.com/file/d/1Cs-94KHmOfRT9C4QJFMCgcuQ93iygg6h)
## MMC Results for JUL
- [Results](https://drive.google.com/file/d/17yNw5FNRORWgtDyey11OeKGRMB9qV0SZ)
## How to Use
- The article 1009 - L298N Supplemental has information that explains how to use the MMC in conjunction while using the Step1_Joystick and Step2_JUL code.
## History
- The history in the development in the joystick algorithm took many years and many more to understand. See article 1001 - Joystick Algorithm. The problem once understood was how to quickly setup the devices, (1) Joystick, (2) Arduino Uno and (3) L298N driver. The frustration for each new project was setting this system it up, each every time. See article 1003 - L298N. Over the last four years, I studied how the inputs giving 16 differ combinations for EN, PWM, LeftIN & RightIN which effected how the motors moved. Because of the joystick algorithm as described in the article (8 octants), there are a possible 128 combinations for the motors' output. See article 1009 - L298N Supplemental. 
## Code Snippet
'''
void setup()
{
#ifdef DEBUG_MAIN
    Serial.begin(9600);
    while (!Serial)
    {
    }
#endif

    // Button & Button-LED
    int buttonPin = 2; // UNO D2 (CHIP-PD2)
    int ledPin = 3;    // UNO D3 (CHIP-PD3)
    buttonDebug = Button(buttonPin, ledPin);

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
}

void updateJoystick()
{
    if (buttonDebug.isButtonOn())
    {
#ifdef DEBUG_MAIN
        Debug("Button ON");
#endif

        int xDigital = analogRead(A1);
        int yDigital = analogRead(A0);

        // MAP
        float inputX = mapInputFromDigital.Map((float)xDigital);
        float inputY = mapInputFromDigital.Map((float)yDigital);

        // Center Joystick to Zero
        float X_OFFSET = 0.05; // (0 < OFFSET < 1)
        float Y_OFFSET = 0.06; // (0 < OFFSET < 1)
        if (absT<float>(inputX) < X_OFFSET)
            inputX = 0;
        if (absT<float>(inputY) < Y_OFFSET)

        // Process Joystick Inputs
        joystick.UpdateInputs(inputX, inputY);
        // Process Joystick Outputs
        float outputLeft = joystick.OutLeft();
        float outputRight = joystick.OutRight();

        // MAP
        int outMapLeft = (int)mapOutFromJoystick.Map(outputLeft);
        int outMapRight = (int)mapOutFromJoystick.Map(outputRight);

        // NEW CODE ------------------------------- FLAG_WATCH
        // For safety reasons, the UpdateL298N() method has a
        // Power Motors Flag set to false which de-activates
        // the motors...
        // SAFETY COMES FIRST (WATCH YOUR FINGERS)
        motors.UpdateL298N(outMapLeft, outMapRight, true);
    }
    else
    {
        // SAFETY COMES FIRST (WATCH YOUR FINGERS)
        motors.PowerDownL298N();
    }
}
'''
