## Joystick Uno L298N (JUL) and Encoder (JULE) Repository
- namespace ***csjc***
- An acronym for **C**arpenter **S**oftware - **J**esse **C**arpenter.
## Testing Platform
- The MCU chip **Atmega328P** is well known and the price is affordable as well as most of the robotic hardware that is described here. The Arduino Uno board comes with a removable MCU.
- **PlatformIO** is a cross-platform, cross-architecture, multiple framework, professional tool for embedded systems engineers and for software developers who write applications for embedded products. 
- **Visual Studio Code** is a streamlined code editor and it runs on macOS, Linux, and Windows. The best thing about VSCode, it is free.

## MCU Atmega328P chip 
This MCU chip **Atmega328P** is well known and the chip can be pulled out to be used separately on a breadboard. Best to purchase directly from Arduino online store. Beware of fake Arduino boards...

## Joystick 
The analog 2-axis thumb joystick with button. The joystick has two analog(10k potentiometers), you'll need two analog (ADC) reading pins on your microcontroller to determine X and Y. Can be purchased from Amazon online...

## L298N Motor Driver
The double H bridge motor drive module (uses ST company's L298N as the main driver chip). The module features strong driving capability, low heat generation and strong anti-interference ability. Can be purchased from Amazon online...

## Joystick Algorithm Simulation
The Youtube simulation demonstrates the joystick algorithm, used to control a simulated two-wheeled differential drive robot. 

<p align="left";>
- <a href="https://www.youtube.com/watch?v=maIHbdbDBwo&t=2s" target="_blank">Joystick Algorithm Simulation</a>
</p>

## Articles
- [1000 - Introduction Robotics](https://drive.google.com/file/d/1Dmt-Lnc2KMzl4EjL4ihP7fVtk7ZHAiGV)
- [1001 - Joystick Algorithm](https://drive.google.com/file/d/1LDAdAhGVo9aw0Ri38oj3zWppfJkAZNR3)
- [1002 - Uno Cheat Sheet](https://drive.google.com/file/d/1ol310KDfcoGWQ2CjMeH3aOgvzGBN7_cK)
- [1003 - L298N Motor Driver](https://drive.google.com/file/d/1YaN5VEbMAGPCDcwN3kG0DyclgSefXyRf)
- [1005 - Study of Quaternions](https://drive.google.com/file/d/1xQS_DkKx-wXtF7fm8C6GPfF8NV9Qoxnr)
- [1009 - L298N Supplemental](https://drive.google.com/file/d/198UaZYEkChPBUSqaPJ8rLeGR-JGohOEA)

## Issues
- Many header files have been added and updated from other repositories. Some of the code has been moved to new header files.The reason for now is to finish the Wireless Communication repository. These added files may be removed in the near future and will be re-incorporated back into their rightful places once those repositories are updated...
- There may be some issues in the speed in which it was updated. Please send me an email.

## In Development
- UPDATED 20240812
- The repository has been updated that reflects the observations as indicated in article 1009 - L298N Supplemental dated 20240812. Although the project has taken many years, it is still a work in progress. The repository Wireless Communication had difficulty using the ***OLD*** Joysrtick Uno L298N repository, so I decided to finally review it and finsih the testing and observations that fell short. Now that it is completed, I'll return to work on the Wireless Communication specifically nRF24L01+ radios and with that, incorporate this code.

## Disclaimer and Terms
Please follow the ***Disclaimer*** and ***Terms*** in the ***Simplified-Joystick-Arduino-Uno-L298N*** Repository.
   
