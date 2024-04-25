#pragma once

#include <cinttypes>

#include "adc/constants.hpp"

class mock_adc {
    public:
        mock_adc(uint8_t i2c_addr);

        bool
        read();

        int32_t
        get(int index);

    private:
        std::vector<float> phases;
        std::vector<float> speeds;
        const int num_channels = ADC_CHANNELS;
};
