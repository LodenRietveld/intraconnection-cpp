#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cinttypes>
#include <iostream>

#include "adc/constants.hpp"
#include "util/util.hpp"

template <class T>
class adcs {
    public:
        adcs(uint8_t addr1, uint8_t addr2, bool prefix_to_string = false);

        bool 
        read();

        std::string
        to_string();

    private:
        uint8_t addr1, addr2;
        std::unique_ptr<T> adc1;
        std::unique_ptr<T> adc2;
        std::vector<float> adc_values;
        bool new_values = false;
        bool scale = true;
        const float max_adc_val = 16838.f;

        bool prefix_to_string = false;
        const uint8_t active_channels = ADC_CHANNELS;
        
        void
        read_single_adc(std::unique_ptr<T>&);
};


template <class T>
adcs<T>::adcs(uint8_t addr1, uint8_t addr2, bool prefix_to_string)
    : addr1(addr1), addr2(addr2), prefix_to_string(prefix_to_string)
{
    adc1 = std::make_unique<T>(addr1);
    adc2 = std::make_unique<T>(addr2);
}


template <class T>
bool
adcs<T>::read()
{
    adc_values.clear();

    read_single_adc(adc1);
    read_single_adc(adc2);

    return new_values;
}


template <class T>
std::string
adcs<T>::to_string()
{
    std::string out = prefix_to_string ? "msg " : "";
    out.append(intra::to_string(adc_values, active_channels));
    out.append(";");
    return out;
}


template <class T>
void
adcs<T>::read_single_adc(std::unique_ptr<T>& adc)
{
    if (adc->read()) {
	    new_values = true;
        for (int i = 0; i < 4; i++){
            uint32_t v = adc->get(i);

            if (v == 0xfefefefe) {
                adc_values.push_back(0);
                continue;
            }

            if (scale) {
                adc_values.push_back(v / max_adc_val);
            } else {
                adc_values.push_back(v);
            }
        }
    }
}

