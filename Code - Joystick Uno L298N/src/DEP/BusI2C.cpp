//
// Carpenter Software
// File: Class BusI2C.cpp (requires header file)
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

// NOTICE: BYTE WORD METHODS MOVED TO TypeConv.h

#include <Arduino.h>
#include <Wire.h>
#include "BusI2C.h"

// Carpenter Software - Jesse Carpenter
using namespace csjc;

    BusI2C::BusI2C()
    {
        m_errorI2C = 0;
    }

    void BusI2C::Begin(uint8_t address)
    {
        Wire.begin(address);
        delay(6);
    }

    void BusI2C::Begin(uint8_t address, uint32_t timeout, bool reset)
    {
        Wire.begin(address);
        delay(6);
        // 3 ms timeout
        Wire.setWireTimeout(timeout, reset);
    }

    void BusI2C::ClearTimeout()
    {
        if (Wire.getWireTimeoutFlag())
        {
            Wire.clearWireTimeoutFlag();
            // Less than timer at 6ms
            delay(6);
        }
    }

    String BusI2C::IsDevice(uint8_t deviceAddress)
    {
        m_scanningI2C(deviceAddress);
        if (m_errorI2C == 0)
        {
            String str = "Found address: " + String(deviceAddress, HEX);
            return str;
        }
        return m_errorMessageI2C();
    }

    String BusI2C::ErrorMsg()
    {
        return m_errorMessageI2C();
    }

    uint8_t BusI2C::GetErrorNumberI2C()
    {
        return m_errorI2C;
    }

    void BusI2C::ReceiveMessage(uint8_t *pMessage, uint8_t size)
    {
        int bufIndex = 0;
        while (Wire.available())
        {
            pMessage[bufIndex] = Wire.read();
            bufIndex++;
        };
    }

    uint8_t BusI2C::RequestMessage(uint8_t addr, uint8_t msg[], uint8_t size)
    {
        int bufIndex = 0;
        Wire.beginTransmission(addr);
        Wire.requestFrom(addr, size);
        while (!Wire.available())
        {
        };
        while (Wire.available())
        {
            msg[bufIndex] = Wire.read();
            bufIndex++;
        };
        m_errorI2C = Wire.endTransmission();
        return (bufIndex - 1);
    }

    void BusI2C::TransmitMessage(uint8_t addr, uint8_t msg[], uint8_t size)
    {
        Wire.beginTransmission(addr);
        for (uint8_t bIdx = 0; bIdx < size; bIdx++)
        {
            Wire.write(msg[bIdx]);
        }
        m_errorI2C = Wire.endTransmission();
    }

    uint8_t BusI2C::RecieveDeviceMessage(uint8_t addr, uint8_t reg, uint8_t msg[], uint8_t size)
    {
        int bufIndex = 0;

        Wire.beginTransmission(addr);
        Wire.write(reg);
        m_errorI2C = Wire.endTransmission();
        if (m_errorI2C == 0)
        {
            Wire.requestFrom(addr, size);
            while (!Wire.available())
            {
            };
            while (Wire.available())
            {
                msg[bufIndex] = Wire.read();
                bufIndex++;
            };
            m_errorI2C = Wire.endTransmission();
        }
        return (bufIndex - 1);
    }

    String BusI2C::m_errorMessageI2C()
    {
        String message = "";
        if (m_errorI2C >= 0 && m_errorI2C <= 5)
        {
            switch (m_errorI2C)
            {
            case 0:
                message = "twiErr0: success";
                break;
            case 1:
                message = "twiErr1: length to long for buffer";
                break;
            case 2:
                message = "twiErr2: address send, NACK received";
                break;
            case 3:
                message = "twiErr3: data send, NACK received";
                break;
            case 4:
                message = "twiErr4:(lost bus arbitration, bus error, ..)";
                break;
            case 5:
                message = "twiErr5: timeout";
                break;
            default:
                message = "twiErrDefault: Not an Address";
                break;
            }
        }
        return message;
    }

    void BusI2C::m_scanningI2C(uint8_t deviceAddress)
    {
        uint8_t lowerAddress = 0x08;
        uint8_t upperAddress = 0x77;
        if (deviceAddress >= lowerAddress && deviceAddress <= upperAddress)
        {
            Wire.beginTransmission(deviceAddress);
            m_errorI2C = Wire.endTransmission();
        }
    }
    