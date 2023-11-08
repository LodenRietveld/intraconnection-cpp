#pragma once

#include <cstdint>

#include "i2c/i2c.hpp"

class mcp3424
{
public:
    enum class gain : uint8_t
    {
        x1 = 0,
        x2,
        x4,
        x8
    };

    enum class mode : uint8_t
    {
        one_shot = 0,
        continuous
    };

    enum class rate : uint8_t
    {
        sr240 = 0,
        sr60,
        sr15,
        sr3_75
    };

    enum class data_size : uint8_t
    {
        sz3 = 0,
        sz2
    };

    mcp3424(uint8_t addr, gain g = gain::x1, mode m = mode::continuous, rate r = rate::sr60);
    ~mcp3424();

    bool
    init();

    bool
    read();

    int32_t
    get(uint8_t channel);
private:
    gain g = gain::x1;
    mode m = mode::continuous;
    rate r = rate::sr60;


    static constexpr int num_channels = 4;
    const int data_and_config_size = r == rate::sr3_75 ? 4 : 3;
    const int read_buffer_size = num_channels * data_and_config_size;

    i2c conn;

    int32_t data[num_channels];

    void
    copy_data_from_read(uint8_t* start_of_package, uint8_t channel);
};


struct mcp3424_control
{
    union {
        struct {
            uint8_t ready:1;
            uint8_t channel:2;
            uint8_t mode:1;
            uint8_t gain:2;
            uint8_t rate:2;
        };
        uint8_t raw;
    };

    mcp3424_control();
    mcp3424_control(mcp3424::gain g, mcp3424::mode m, mcp3424::rate r);
};