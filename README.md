# Joystick - Arduino Uno - L298N Depository

The Joystick-Uno-L298N depository is a complete C++ code for the **Thumb Joystick** and for the **L298N Motor Driver Module** using the **MCU Atmega329P (Uno)** for the  VS Code PlatformIO (or Arduino IDE). There are two versions, Debug and Release.

## MCU Atmega328P chip 

This MCU chip **Atmega328P** is well known and it can be used separately on a breadboard.

## Joystick 

The analog 2-axis thumb joystick with button by Makerfabs (China). The joystick has two analog(10k potentiometers), you'll need two analog (ADC) reading pins on your microcontroller to determine X and Y.

## L298N Motor Driver

The double H bridge motor drive module (uses ST company's L298N as the main driver chip) by Album (China). The module is featuring strong driving capability, low heat generation and strong anti-interference ability. This module can use the built-in 78M05 to take power through the drive power supply part, but in order to avoid the damage of the voltage regulator chip, when using **the drive voltage greater than 12V**, please use the **external** 5V logic power supply. This module uses a large-capacity filter capacitor and a freewheeling protection diode to improve reliability. You'll need two PWM pins for ENA and ENB and four digital pins for IN1, IN2, IN3 and IN4.

**Notice:** *Never use any combination of input pins on **HIGH** at any one time or something may begin to smell or worse **smoke**. Always setup the input pins to **LOW**. When changing a pair of input pins from **LOW** to **HIGH** always set the top input pin to **LOW** first, then the next input pin to **HIGH**. This way no two pins are ever **HIGH** at the same time. This is referenced to Arduino's digitalWrite() when pinmode() is set to OUTPUT for the L298N input pins.*

### Carpenter Software Updates

- 1000 Introduction Robotics - updated pdf 20211110
- 1001 Joystick              - new pdf 20211110
- 1002 Uno                   - new pdf 20211110
- 1003 L298N                 - new pdf 20211202 (new material)
- Release Code               - updated Class L298N 20211110
- Debug Code                 - updated Class L298N 20211114
   
