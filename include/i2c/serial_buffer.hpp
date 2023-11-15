#pragma once

#include <array>
#include <cstdint>

class serial_buffer_t
{
public:
    serial_buffer_t() = default;
    ~serial_buffer_t() = default;

    void
    set_fd(int fd);

    uint32_t
    read(size_t size);

    ssize_t
    write(uint8_t* buf, size_t size);
private:
    int fd = -1;

    const uint32_t err = 1 << 31;

    uint32_t
    process_read_value(uint8_t* buf, size_t size);
};