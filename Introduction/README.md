## Joystick-Uno-L298N 
### by Jesse Carpenter

File name: **Intro Robotics.pdf**

There are two file sizes where the smaller one about 970 KB posted here (*can download*). The other is about 6.5 MB located at Google Drive (*cannot download*).

### Notice 20210910

The code attached to this article, *Joystick-Uno-L298N*, has been updated in the *RELEASE* code. After careful review, the update to updateAnalog() was done out of **SATETY** concerns.

* **Updated main.cpp file** *
```C++
void updateAnalog()
{
    if (btnMotors.isButtonOn())
    {
        int xAnalog = analogRead(A1);
        int yAnalog = analogRead(A0);
        stk.UpdateInputs(xAnalog, yAnalog);

        int left = stk.GetOutputLeftInteger(255);
        int right = stk.GetOutputRightInteger(255);
        mtr.updateL298N(left, right);
    }
    else
    {
        mtr.PowerDownL298N(); // < --------------- New Call Method 20210910 Notice
    }
}
```
* **Updated L298.h file** *
```C++
class L298N
    {
    private:
        uint8_t _ZERO;

        uint8_t _LeftMotorPWM;
        uint8_t _LeftMotorIN1;
        uint8_t _LeftMotorIN2;

        uint8_t _RightMotorIN1;
        uint8_t _RightMotorIN2;
        uint8_t _RightMotorPWM;

        int _PWM_LeftMotor;
        int _PWM_RightMotor;

        void _setDirectionPins();
        void _powerDownL298N();

    public:
        L298N();
        L298N(uint8_t LeftMotorPWM,
              uint8_t LeftMotorIN1,
              uint8_t LeftMotorIN2,
              uint8_t RightMotorIN1,
              uint8_t RightMotorIN2,
              uint8_t RightMotorPWM);
        void SetupPinsL298N();
        void updateL298N(int UnoPWM_ToENA, int UnoPWM_ToENB);
        void PowerDownL298N(); // < --------------- New Method 20210910 Notice
    };
```
