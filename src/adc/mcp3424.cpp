#include <iostream>
#include <cstdint>
#include <stdexcept>

#include "adc/mcp3424.hpp"

constexpr int mcp3424::num_channels;

mcp3424_control::mcp3424_control()
    : ready(0), channel(0), mode(0), gain(0), rate(0)
{

}

mcp3424_control::mcp3424_control(mcp3424::gain g, mcp3424::mode m, mcp3424::rate r)
    : ready(0), channel(0), mode(((uint8_t) m) & 0x1), gain(((uint8_t) g) & 0x11), rate(((uint8_t) r) & 0x11)
{

}

mcp3424::mcp3424(uint8_t addr, gain g, mode m, rate r) 
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
    mcp3424_control config(g, m, r);
    if (conn.write_raw(&config.raw, 1) < 0) {
        //something went wrong
        return false;
    }

    return true;
}

void
mcp3424::copy_data_from_read(uint8_t* start_of_package, uint8_t channel)
{
    if (r != rate::sr3_75) {
        data[channel] = (start_of_package[0] << 8) | (start_of_package[1]);
    } else {
        data[channel] = (start_of_package[0] << 16) | (start_of_package[1] << 8) | (start_of_package[2]);
    }
}

bool
mcp3424::read()
{
    uint8_t buff[read_buffer_size] = {0};
    uint8_t idx = 0;
    
    while (true) {
        int data = conn.read_raw();

        if (data == -1) {
            std::cout << "error reading data" << std::endl;
            continue;
        }

        buff[idx++] = data;

        if (idx == read_buffer_size) {
            mcp3424_control ctl;
            ctl.raw = buff[idx-1];

            if (!ctl.ready)
                break;
            
            idx = 0;
        }
    }

    for (int i = 0; i < read_buffer_size / data_and_config_size; i++){
        copy_data_from_read(&buff[i * data_and_config_size], i);
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