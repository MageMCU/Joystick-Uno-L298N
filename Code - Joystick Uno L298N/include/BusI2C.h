//
// Carpenter Software
// File: Class BusI2C.h (requries BusI2C.cpp file - src/DEP/ folder)
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

#ifndef BUS_I2C_h
#define BUS_I2C_h

#include <Arduino.h>
#include <Wire.h>

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    class BusI2C
    {
    public:
        // Public Properties
        // Constructor
        BusI2C();
        ~BusI2C() = default;

        // Public Methods
        void Begin(uint8_t address);
        void Begin(uint8_t address, uint32_t timeout, bool reset);
        void ClearTimeout();
        String IsDevice(uint8_t deviceAddress);
        String ErrorMsg();
        uint8_t GetErrorNumberI2C();
        void ReceiveMessage(uint8_t *pMessage, uint8_t size);
        uint8_t RequestMessage(uint8_t addr, uint8_t msg[], uint8_t size);
        void TransmitMessage(uint8_t addr, uint8_t msg[], uint8_t size);
        uint8_t RecieveDeviceMessage(uint8_t addr, uint8_t reg, uint8_t msg[], uint8_t size);

    private:
        // Private Properties
        uint8_t m_errorI2C;
        // Private Methods
        String m_errorMessageI2C();
        void m_scanningI2C(uint8_t deviceAddress);
    };
}
#endif
