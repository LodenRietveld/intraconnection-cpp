#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <chrono>
#include <thread>

#include "adc/mcp3424.hpp"

constexpr int mcp3424::num_channels;

mcp3424_control::mcp3424_control()
    : ready(0), channel(0), mode(0), gain(0), rate(0)
{

}

mcp3424_control::mcp3424_control(gain_t g, conversion_mode_t m, rate_t r)
    : ready(0), channel(0), mode(((uint8_t) m) & 0x1), gain(((uint8_t) g) & 0x11), rate(((uint8_t) r) & 0x11)
{

}

mcp3424_control::mcp3424_control(uint8_t raw)
    : raw(raw)
{

}

mcp3424::mcp3424(uint8_t addr, gain_t g, conversion_mode_t m, rate_t r) 
    : g(g), m(m), r(r), conn(addr)
{
    if (!conn.connected())
        throw std::runtime_error("i2c connection failed");
    
    if (!init())
        throw std::runtime_error("mcp init failed");
}

mcp3424::~mcp3424()
{

}

bool
mcp3424::init()
{
    if (conn.write_raw(&config.raw, 1) < 0) {
        //something went wrong
        return false;
    }

    return true;
}

void
mcp3424::copy_data_from_read(uint8_t* start_of_package, uint8_t channel)
{
    if (r != rate_t::sr3_75) {
        data[channel] = (start_of_package[0] << 8) | (start_of_package[1]);
    } else {
        data[channel] = (start_of_package[0] << 16) | (start_of_package[1] << 8) | (start_of_package[2]);
    }
}

bool
mcp3424::read()
{
    using namespace std::chrono_literals;
    
    for (int i = 0; i < num_channels; i++){
        config.channel = i;
        int channel_select = conn.write_raw(&config.raw, 1);

        while (true) {
            auto res = conn.read_raw(data_and_config_size);
            
            if (res & (1 << 31)) {
                std::cout << "Read raw failed" << std::endl;
                continue;
            }

            auto data = res >> 8;
            mcp3424_control config(res & 0xff);

            if (config.is_ready()) {
                this->data[i] = data;
                break;
            }

            std::this_thread::sleep_for(10us);
        }
    }

    return true;
}

int32_t
mcp3424::get(uint8_t channel)
{
    if (channel < num_channels)
        return data[channel];
    
    return 0xfefefefe;
}