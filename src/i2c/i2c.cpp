#include <iostream>

extern "C" {
    #include <unistd.h>
}

#include "i2c/i2c.hpp"

i2c::i2c(uint8_t addr)
{
    int ret = wiringPiI2CSetup(addr);

    if (ret < 0) {
        std::cout << "Error opening i2c device" << std::endl;
    }

    i2c_fd = ret;
    read_buf.set_fd(i2c_fd);
}

i2c::~i2c()
{
    
}

uint8_t
i2c::read8(uint8_t reg)
{
    return static_cast<uint8_t>(wiringPiI2CReadReg8(i2c_fd, reg));
}

uint16_t
i2c::read16(uint8_t reg)
{
    return static_cast<uint16_t>(wiringPiI2CReadReg16(i2c_fd, reg));
}

uint32_t
i2c::read_raw(uint8_t size)
{
    return read_buf.read(size);
}

int
i2c::write(uint8_t reg, uint8_t* data, uint8_t size)
{
    int ret = 0;
    uint8_t idx = 0;
    while (--size) {
        ret = wiringPiI2CWriteReg8(i2c_fd, reg, data[idx++]);
    }

    return ret;
}

ssize_t
i2c::write_raw(uint8_t* data, uint8_t size)
{
    int ret = 0;
    uint8_t idx = 0;
    while (size--) {
        ret = wiringPiI2CWrite(i2c_fd, data[idx++]);
    }

    return ret;
}

bool
i2c::connected()
{
    return i2c_fd != -1;
}