#include <cmath>
#include <vector>
#include <iostream>

#include "util/mock_adc.hpp"

mock_adc::mock_adc(uint8_t i2c_addr)
{
    for (int i = 0; i < num_channels; i++){
        this->speeds.push_back(((rand() % 10000) / 1000000.f) + 0.1f);
        this->phases.push_back((rand() % 1000) / 1000.f * 2 * M_PI);
    }
}

bool
mock_adc::read()
{
    for (int i = 0; i < num_channels; i++){
        this->phases[i] += this->speeds.at(i);
    }

    return true;
}

int32_t
mock_adc::get(int index)
{
    float p = this->phases.at(index);
    return ((cos(p) + 1)/ 2.f) * 16383;
}
