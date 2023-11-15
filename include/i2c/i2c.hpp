#pragma once

#include <array>
#include <cstdint>

extern "C" {
    #include<wiringPiI2C.h>
}

#include "serial_buffer.hpp"

class i2c
{
public:

    i2c(uint8_t addr);
    virtual ~i2c();

    uint8_t
    read8(uint8_t reg);

    uint16_t
    read16(uint8_t reg);

    uint32_t
    read_raw(uint8_t size);

    int
    write(uint8_t reg, uint8_t* data, uint8_t size);

    ssize_t
    write_raw(uint8_t* data, uint8_t size);

    bool
    connected();
private:
    uint8_t device_addr = 0xff;
    int i2c_fd = 0;
    
    serial_buffer_t read_buf;
};
