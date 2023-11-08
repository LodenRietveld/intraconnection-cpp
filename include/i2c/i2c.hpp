#pragma once

#include <cstdint>

extern "C" {
    #include<wiringPiI2C.h>
}

class i2c
{
public:
    i2c(uint8_t addr);
    virtual ~i2c();

    uint8_t
    read8(uint8_t reg);

    uint16_t
    read16(uint8_t reg);

    int
    read_raw();

    int
    write(uint8_t reg, uint8_t* data, uint8_t size);

    int
    write_raw(uint8_t* data, uint8_t size);

    bool
    connected();
private:
    uint8_t device_addr = 0xff;
    int i2c_fd = 0;
};