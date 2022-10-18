//
// Carpenter Software
// File: MAIN-  main.cpp (debug version)
// Folder: joystick_L298N_debug
// Purpose: Github Depository (MageMCU)
//
// Teacher's and Parent's copy...
// Dedicated to Parents and Teachers of the USA.
// Teachers Note: The _BEGIN_DEBUG is defined (see
//                DEBUG.h file), also MAIN _ANALOG_
//                is defined for debugging the
//                analog readings. For safety
//                reasons while debugging, the
//                motors are conditioned not to
//                operate. Be warned. the Student's
//                copy has no safety feature.
//
// Hardware
// MCU: Atmega328P (Microchip)
// * Board: Arduino Uno (Italy)
// Thumb Joystick: (China)
// Motor Driver: L298N (ST)
// * Motor Module: (China)
// 12V Geared Motors (ratio 1:75) (China)
// Note: motors: current peaks on average 1.14 amps
//       for static friction, and it levels down to
//       about 0.29 amps for dynamic friction. When
//       joystick with hands-off (center position),
//       is about 0.10 amps. The robot was sitting
//       on stand with no weight on wheels, otherwise,
//       the electrical currents would have increased.
// Battery 12V - APX1250 (12V 5.0Ah) Sealed Lead-Acid
// Note: battery: with five years design life (using
//       now for 7 years.) Requires special battery
//       charger from APEX.
//
// By Jesse Carpenter (Github as MageMCU)
//
// CHANGELOG
// August 30, 2021 - debug comments
// August 24, 2021 - editing
// June 19, 2021 - programming debug version
//
// Atmega328P Total Usgae
// RAM : [==] 15.3 % (used 314 bytes from 2048 bytes)
// Flash : [==] 21.2 % (used 6846 bytes from 32256 bytes)
//
// MIT LICENSE
//

#include <Arduino.h>
#include "L298N.h"
#include "Joystick.h"
#include "Timer.h"
#include "Button.h"
#include "DEBUG.h"

// Using Adruino Uno
// GLOBAL VARIABLES
uno::L298N mtr;
uno::Joystick stk;
uno::Timer tmrMotors;
uno::Timer tmrMainDebug;
uno::Button btnMotors;

void setup()
{
// Debug
#ifdef _dM_
    Serial.begin(9600);
    while (!Serial)
    {
    }
    Serial.println("Serial 9600");
#endif

    // STUB --RADIO-CONTROL---       TODO
    // BY-PASS THUMB-JOYSTICK

    // STUB --I2C--                  TODO
    // MOVE TO PROTOBOARD
    // AS SLAVE DEVICE AS MOTOR
    // MANAGER - THERE IS ROOM FOR
    // A SERVO...

    // To make it less difficult to get the code up and running,
    // use L298N Assignments as discussed below. I have found it
    // much easier to PROGRAM the code whether than re-wiriing
    // the hardware.
    //
    // Record the Wired Connections from Uno to L298N and
    // from L298N to the Motors. OTHERWISE, JOYSTICK CODE
    // WILL BREAK. EVERYTHING IS PROGRAMMED AROUND THE JOYSTICK
    // CODE.
    //
    // (1) WIRING ARDUINO UNO to L298N...
    // ENA-Set
    // int8_t ENA = Uno-Pin? ;
    // int8_t IN1 = Uno-Pin? ;
    // int8_t IN2 = Uno-Pin ?;
    // ENB-Set
    // int8_t IN3 = Uno-Pin? ;
    // int8_t IN4 = Uno-Pin? ;
    // int8_t ENB = Uno-Pin? ;

    // (2) L298N to MOTORS...
    // Set ENA
    //      (a) L298N-Motor-Outs(1 & 2) matches to ENA.
    //      (b) Assigned to (Left/Right)__________ Motor.
    //      (c) The Motor assigned gets set (ENA, IN1, IN2).
    // Set ENB
    //      (a) L298N-Motor-Outs(3 & 4) matches to ENB.
    //      (b) Assigned to(Left/Right) __________ Motor.
    //      (c) The Motor assigned gets set (ENB, IN3, IN4).

    // (3a) Based on (1 & 2), is this set (ENA/ENB)_____________?
    // Instead of using (Uno-Pin), use assigned variables above.
    // int8_t LeftMotorPWM = Uno-Pin? ;
    // int8_t LeftMotorIN1 = Uno-Pin? ;
    // int8_t LeftMotorIN2 = Uno-Pin? ;

    // (3b) ) Based on (1 & 2), is this set (ENA/ENB)_____________?
    // Instead of using (Uno-Pin), use assigned variables above.
    // int8_t RightMotorIN1 = Uno-Pin? ;
    // int8_t RightMotorIN2 = Uno-Pin? ;
    // int8_t RightMotorPWM = Uno-Pin? ;

    // (4) L298N Instantiation
    // mtr = uno::L298N(LeftMotorPWM, LeftMotorIN1, LeftMotorIN2,
    //                  RightMotorIN1, RightMotorIN2, RightMotorPWM);

    // EXAMPLE
    // SCOPE - ALL DECLARED VARIABLE HERE ARE LOST ONCE OUT OF SCOPE...
    // An example (based on author's (robot) hardware setup.)
    // Set ENA
    int8_t ENA = 10;
    int8_t IN1 = 9;
    int8_t IN2 = 8;
    // Set ENB
    int8_t IN3 = 7;
    int8_t IN4 = 6;
    int8_t ENB = 5;

    // (2) L298N to MOTORS...
    // ENA-Set
    //      (a) L298N-Motor-Outs(1 & 2) matches to ENA-Set.
    //      (b) Assigned to (Left/Right)**RIGHT** Motor.
    //      (c) The Motor assigned gets set (ENA, IN1, IN2).
    // ENB-Set
    //      (a) L298N-Motor-Outs(3 & 4) matches to ENB-Set.
    //      (b) Assigned to(Left/Right) **LEFT** Motor.
    //      (c) The Motor assigned gets set (ENB, IN3, IN4).

    // (3a) Based on (1 & 2), is this set (ENA/ENB) **ENB** ?
    int8_t LeftMotorPWM = ENB;
    int8_t LeftMotorIN1 = IN4;
    int8_t LeftMotorIN2 = IN3;
    // (3b) ) Based on (1 & 2), is this set (ENA/ENB) **ENA** ?
    int8_t RightMotorIN1 = IN1;
    int8_t RightMotorIN2 = IN2;
    int8_t RightMotorPWM = ENA;

    // L298N Instantiation (mtr was declared as a global variable. See abvoe.)
    mtr = uno::L298N(LeftMotorPWM, LeftMotorIN1, LeftMotorIN2,
                     RightMotorIN1, RightMotorIN2, RightMotorPWM);
    // L298N Setup
    mtr.SetupPinsL298N();

    // Joystick setup
    stk = uno::Joystick();
    // NOTICE: Joystick Calibration
    // Hands-Off Stick..., about
    // a second, press Arduino reset to
    // re-calibrate. HANDS-OFF...

    // Timer setup
    tmrMotors = uno::Timer();
    tmrMainDebug = uno::Timer();

    // Button setup
    // buttonPin 2
    // ledPin 12
    btnMotors = uno::Button(2, 12);
}
// BEGIN //////////////////////////////////////////////////////////////////// DEBUG
void _debug(int xAnalog, int yAnalog, int left, int right)
{
#ifdef _dM_
#ifdef _ANALOG_
    // USE SERIAL (9600) to Debug.
    //
    //  (STEP-1) ---- MAIN ANALOG -------
    // -------------------------------------------------------------------
    // HARDWARE usually solved with the software.
    // -------------------------------------------------------------------
    // SOFTWARE
    // Joystick Movements ADC Readings
    // from 0 to 1023...
    // The ideal analog readings may not display as shown yet the
    // readings should closely match the ideal values.
    // -----------------------------------------------------------
    // Center (Hands-Off) ------ Center between 0 and 1023.
    // (x, y) = (511, 511).
    // -----------------------------------------------------------
    // Up (Forward)    --------- y-changes in (x, y).
    // (x, y) = (511, 1023)(+) or ((511, 0)(-) (where x is constant).
    // -----------------------------------------------------------
    // Down (Backward) --------- y-changes in (x, y).
    // (x, y) = (511, 0)(+) or (511, 1023)(-) (where x is constant).
    // -----------------------------------------------------------
    // Left            --------- x-changes in (x, y).
    // (x, y) = (0, 511)(+) or (1023, 511)(-) (where y is constant).
    // -----------------------------------------------------------
    // Right           --------- x-changes in (x, y).
    // (x, y) = (1023, 511)(+) or (0, 511)(-) (where y is constant).
    // -----------------------------------------------------------
    // If (x, y) changes are reversed, exchange the analogRead() from (A0)
    // to (A1) or the other way around inside the main.cpp file.
    // (+) Good...
    // (-) May have to reverse either (x = 1023 - x) or the same with (y).
    // if the readings are OK, then go to MAIN JOYSTICK.
    // SEE DEBUG.h file.

    Serial.print("MAIN(xA,yA)=(");
    Serial.print(xAnalog);
    Serial.print(" , ");
    Serial.print(yAnalog);
    Serial.println(")");
#endif

#ifdef _JOYSTICK_
    //  (STEP-2) ---- MAIN JOYSTICK -------
    // -------------------------------------------------------------------
    // SOFTWARE - ALGORITHM (NO HARDWARE)
    // -------------------------------------------------------------------
    // Normalized Joystick Values from -1 to 1...
    // Hands-Off          ---------
    // [L, R] = [0, 0]   Octant 100 means [0, 0]
    // Up (Forward)       ---------
    // [L, R] = [1, 1]   Octant 101 means [0, R]
    // Down (Backward)    ---------
    // [L, R] = [-1, -1] Octant 101 means [0, R]
    // Left               ---------
    // [L, R] = [-1, 1]  Octant 110 means [L, 0]
    // Right              ---------
    // [L, R] = [1, -1]  Octant 110 means [L, 0]
    // Starting from Right Joystick Position, octants
    // should read CCW(1 to 8). Ignore octant values.
    // Should work based on MAIN ANALOG DEBUG (+), otherwise
    // in DEBUG.h, under HEADERS define _dJ_ and undefine
    // all others under MAIN definitions.
    // If OK - Go To MAIN N298N. SEE DEBUG.h
    //
    // EXAMPLES from Serial 9600
    //     (Analog)- transformed >[Joystick Normalized]   (octant)
    // Hands-Off
    // MAIN (xA,yA)=(534, 524)->[nL,nR]=[0.00, 0.00] from octant(100)
    // Up (Forward)
    // MAIN (xA,yA)=(534, 1023)->[nL,nR]=[1.00, 1.00] from octant(101)
    // Down (Backward)
    // MAIN (xA,yA)=(534, 0)->[nL,nR]=[-1.00, -1.00] from octant(101)
    // Left
    // MAIN (xA,yA)=(0, 524)->[nL,nR]=[-1.00, 1.00] from octant(110)
    // Right
    // MAIN (xA,yA)=(1023, 524)->[nL,nR]=[1.00, -1.00] from octant(110)

    int octant = stk.GetOctantCondition();
    double normalLeft = stk.GetOutputLeft();
    double normalRight = stk.GetOutputRight();
    Serial.print("MAIN (xA,yA)=(");
    Serial.print(xAnalog);
    Serial.print(", ");
    Serial.print(yAnalog);
    Serial.print(")->[nL,nR]=[");
    Serial.print(normalLeft);
    Serial.print(", ");
    Serial.print(normalRight);
    Serial.print("] from octant(");
    Serial.print(octant);
    Serial.println(")");
#endif

#ifdef _L298N_
    // (STEP-3) ----MAIN L298N-- -----
    // -------------------------------------------------------------------
    // SOFTWARE. Easy where Re-wiring the hardware can be a hassle.
    // -------------------------------------------------------------------
    // The default constructor L298N() assigns the Uno and L298N Pins as:
    // (Use this as a reference.)
    // L298N::L298N()
    // {
    //     ...
    //     _LeftMotorPWM = 10; // Arduino Pin 10  wired to L298N Pin ENA
    //     _LeftMotorIN1 = 9;  // Arduino Pin 9  wired to L298N Pin IN1
    //     _LeftMotorIN2 = 8;  // Arduino Pin 8  wired to L298N Pin IN2
    //     _RightMotorIN1 = 7; // Arduino Pin 7  wired to L298N Pin IN3
    //     _RightMotorIN2 = 6; // Arduino Pin 6  wired to L298N Pin IN4
    //     _RightMotorPWM = 5; // Arduino Pin 5  wired to L298N Pin ENB
    //      ...
    // }

    // The other L298N() constructor allows for assignment of arduino pins:
    // (Of course use the same pins as the default but assign one of the
    // two sets of pins to the other motor.)
    // Assign Arduino Pins to Constructor
    // Assign Arduino Pins to Constructor
    // Assign Arduino Pins to Constructor
    // L298N::L298N(uint8_t LeftMotorPWM,
    //              uint8_t LeftMotorIN1,
    //              uint8_t LeftMotorIN2,
    //              uint8_t RightMotorIN1,
    //              uint8_t RightMotorIN2,
    //              uint8_t RightMotorPWM)
    // {
    //     ...
    //     _LeftMotorPWM = LeftMotorPWM; // Uno-PWM-To-L298N-PWM
    //     _LeftMotorIN1 = LeftMotorIN1; // Uno-Output-To-L298N-Digital-Input
    //     _LeftMotorIN2 = LeftMotorIN2; // Uno-Output-To-L298N-Digital-Input
    //     _RightMotorIN1 = RightMotorIN1; // Uno-Output-To-L298N-Digital-Input
    //     _RightMotorIN2 = RightMotorIN2; // Uno-Output-To-L298N-Digital-Input
    //     _RightMotorPWM = RightMotorPWM; // Uno-PWM-To-L298N-PWM
    //     ...
    // }
    //
    // Trouble-shooting:
    // (1) Add Uno's Pin Numbers to Instantiate mtr = uno::L298N():
    // Example: mtr = uno::L298N(10, 9, 8, 7, 6, 5);
    // This is exactly the same as L298N() without the integers.
    // (2) If the Left Motor in connected to ENB, invert the Order of
    // Uno Pins as follows:
    //     mtr = uno::L298N(5, 6, 7, 8, 9, 10);
    // (3) Position the Joystick in the Up (Forward). If both motors
    // move forward, then OK. Otherwise, if the left moves back. swap
    // LeftIn1 and LeftIn2.
    // Example: mtr = uno::L298N(5, 7, 6, 8, 9, 10);
    // Notice: Just remember that the pin order for L298N() is associated
    // from the left motor to the right motor. If not, this will break
    // Joystick Algorithm.
    // Therefore:
    // L298N(LeftMotorPWM, LeftMotorIN1,  LeftMotorIN2,
    //       RightMotorIN1, RightMotorIN2, RightMotorPWM)
    // where LeftMotorPWM & RightMotorPWM are either ENA or ENB.
    // If LeftMotorPWM is ENB, then LeftMotorIN1 & LeftMotorIN2 must be
    // either IN3 or IN4 which belong to ENB.

    int in1 = mtr.GetIN1();
    int in2 = mtr.GetIN2();
    int in3 = mtr.GetIN3();
    int in4 = mtr.GetIN4();
    Serial.print("MAIN Left: ");
    Serial.print(left);
    Serial.print(" -> <IN1, IN2> = <");
    Serial.print(in1);
    Serial.print(", ");
    Serial.print(in2);
    Serial.println(">");
    Serial.print("MAIN Right: ");
    Serial.print(right);
    Serial.print(" -> <IN3, IN4> = <");
    Serial.print(in3);
    Serial.print(", ");
    Serial.print(in4);
    Serial.println(">");
    Serial.println("");

    // For those who want to play with the hardware
    // ----------------------------------------------------------------
    // The L298N Motor-OUTS will change voltage polarity depending
    // on the Joystick Position. Connect the Motor Leads to the L298N.
    // When the Joystick is held in the forward position, observe
    // whether either motor rotates forward. If not, then simply swap
    // leads for the left and/or the right motor.
    // ----------------------------------------------------------------
    //                       Left Motor                Right Motor
    // Arduino Pins           10  9   8                 7   6   5
    // L298N Pins            ENA IN1 IN2               IN3 IN4 ENB
    // L298N Motor-outs       OUT1  OUT2                OUT3  OUT4
    // Joystick Forward     yes-OK/no-swap             yes-OK/no-swap
    // ----------------------------------------------------------------
    // Define MAIN L298N in the DEBUG.h file. Everthing else is undefined.
    // The debug output shows how the L298N inputs behave relative either to
    // the left or the right motor. The furstration is knowing which is the
    // software issue or which is the hardware issue. Always start with the
    // Hardware. The hardware is easy.
    // -------------------------------------------------------------------
    // L298N MOTOR MODULE BOARD - TECHNICAL NOTES
    // -------------------------------------------------------------------
    // 12V Geared Ratio 1:75 Motors (China)
    // 12V Battery (USA)
    // NOTICE 1: JUMPER - If Battery is greater then 12V, then
    //                    remove jumper. (1) Jumper-PLUGGED-IN. The purpose
    //                    for the jumper is to supply 5V to the L298N Logic
    //                    circuits. (2) Jumper-PULLED-OFF. You have to supply
    //                    the L298N logic 5V either directly from the Arduino
    //                    or an external battery 5V regulator supply. (See 5V Out).
    // NOTICE 2: IF MOTORS BEGIN TO MOVE ON THEIR OWN, PRESS UNO-RESET BUTTON
    //           FOR RE-CALIBRATION TO CENTER JOYSTICK. HANDS-OFF JOYSTICK WHEN
    //           CALIBRATING.
    //                         -------------------------
    //                         |     |   L298N   |     |
    //                         |     |           |     |
    //                         |     -------------     |
    //              LEFT-MOTOR |----               ----| RIGHT-MOTOR
    //                   OUT1  | O |               | O |  OUT4
    //                   OUT2  | O | jumper        | O |  OUT3
    //                         |-------------      ----|
    //                         |    | O O O |  A1234B  |<- LOGIC A - ENA
    //                         -------------------------         1 - IN1
    //                        Battery(+)(-)(5V Out)              2 - IN2 etc.
    //
    // -------------------------------------------------------------------
    // SOFTWARE
    // -------------------------------------------------------------------
    // Software Examples.
    // LOW = 0, HIGH = 1..., MAX PWM 255
    // Serial 9600 - LAB-RESULTS                |  INTERPRETATION
    // JOYSTICK CENTER POSITION - HANDS OFF ---- MOTOR-OUTS - MULTIMETER
    // MAIN Left: 0 -> <IN1, IN2> = <0, 0>      | 1(-) 2(-)   No Voltage
    // MAIN Right: 0 -> <IN3, IN4> = <0, 0>     | 3(-) 4(-)   No Voltage
    // JOYSTICK UP POSITION - FORWARD ----------------CHECK-TWICE-[jc]--
    // MAIN Left: 255 -> <IN1, IN2> = <0, 1>    | 1(-) 2(+) +14V Forward
    // MAIN Right: 255 -> <IN3, IN4> = <0, 1>   | 3(-) 4(+) +14V Forward
    // JOYSTICK DOWN POSITION - BACKWARD --------------CHECK-TWICE-[jc]--
    // MAIN Left: -253 -> <IN1, IN2> = <1, 0>   | 1(+) 2(-) -14V Backward
    // MAIN Right: -253 -> <IN3, IN4> = <1, 0>  | 3(+) 4(-) -14V Backward
    // JOYSTICK LEFT POSITION            --------------CHECK-TWICE-[jc]--
    // MAIN Left : -254 -> <IN1, IN2> = <1, 0>  | 1(+) 2(-) -14V Backward
    // MAIN Right : 254 -> <IN3, IN4> = <0, 1>  | 1(-) 2(+) +14V Forward
    // JOYSTICK RIGHT POSITION            -------------CHECK-TWICE-[jc]--
    // MAIN Left : 255 -> <IN1, IN2> = <0, 1>   | 1(-) 2(+) +14V Forward
    // MAIN Right : -255 -> <IN3, IN4> = <1, 0> | 1(+) 2(-) -14V Backward
    // -------------------------------------------------------------------
    // NOTICE 3: If there are issues with the motor behavior and
    //           if the debug show consistent values shown above, then
    //           the problem is not the software but it is the hardware.
    // -------------------------------------------------------------------
    // NOTICE 4: L298N INPUT WITH <1, 1> VALUES ARE NOT NECESSARY.
    // -------------------------------------------------------------------
    // NOTICE 5: L298N does not use negative values but before the
    // software math absolute abs() on the PWM Left & PWM Right values,
    // the negative values are used here for debug. The signs on
    // the Left & Right tells which direction the motors are heading.
    // The angle-brackets are the HIGH & LOW for the L298N Input pins.
    // Again this is not easy, but you are almost there.
    /////////////////////////////////////////////////////////////////////
    // Final note: These three steps ought to solve most issues,
    // otherwise read the code and start debugging.
    /////////////////////////////////////////////////////////////////////
    // The orientation of the joystick or the L298N board as presented
    // relative to the MCU or motors may not be the same, but this guide
    // can still be used to help.
    /////////////////////////////////////////////////////////////////////
#endif
#endif
}
// END ////////////////////////////////////////////////////////////////////// DEBUG

void updateAnalog(bool debugMotors)
{
    // ---- ANALOG -------
    // Must Read ADC while
    // JoystickCalibrating Center...
    //    * KEEP-IN-MIND *
    // * HANDS-OFF-OF-JOYSTICK *
    //
    // Thumb-Joystick Orientation
    // sometimes give unexpected
    // analog readings. Therefore
    // use DEBUG.h (undefine everything
    // except MAIN ANALOG) to test
    // analog as described in _debug() in
    // main.cpp file.
    // * x-analog reads from 0 to 1023 *
    int xAnalog = analogRead(A1);
    // Uncomment if x-analog reads from 1023 to 0.
    // xAnalog = _1023 - xAnalog;
    // * y-analog reads from 0 to 1023 *
    int yAnalog = analogRead(A0);
    // Uncomment if analog reads from 1023 to 0.
    // yAnalog = _1023 - yAnalog;
    // For furhter details see _debug() ANALOG.

    // Joystick-IN
    //
    stk.UpdateInputs(xAnalog, yAnalog);
    // Joystick-OUT - L298N PWM 255
    int const left = stk.GetOutputLeftInteger(255);
    int const right = stk.GetOutputRightInteger(255);

    if (debugMotors)
    {
        if (tmrMainDebug.isTimer(2500))
        {
            // Scope TRUE Variable
            bool debugL298N = true;

            // Update Motors
            mtr.updateL298N(debugL298N, left, right); // FIXME 20221017 jc
            _debug(xAnalog, yAnalog, left, right);
            // Motors Off - Safety Reasons
            // Notice: While debugging, the motors
            // are conditioned not to operate.
            // See L298N updateL298N().
            // Evething works as though if the
            // motors were active...
        }
    }
    else if (btnMotors.isButtonOn())
    {
        // Scope FALSE Variable
        bool debugL298N = false;

        // Update Motors
        mtr.updateL298N(debugL298N, left, right);
    }
}

void loop()
{
    btnMotors.updateButton();
    // 50ms timer cycles at 20Hz
    // Enough time for motors...
    if (tmrMotors.isTimer(50))
    {
#ifdef _dM_ // See _debug() & DEBUG.h
        // Scope TRUE Variable
        bool debugMotors = true;
        updateAnalog(debugMotors);
#else
        // Scope FALSE Variable
        bool debugMotors = false;
        updateAnalog(debugMotors);
#endif
    }
}