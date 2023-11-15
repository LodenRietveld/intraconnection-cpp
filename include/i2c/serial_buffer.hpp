#pragma once

#include <array>
#include <cstdint>

class serial_buffer_t
{
public:
    enum class err : int8_t {
        ok = 0,
        read_too_big = -1,
        read_error = -2
    };
    static constexpr int max_read_index = UINT8_MAX;
    static constexpr int buf_size = UINT8_MAX + 1;
    using buffer_t = std::array<uint8_t, buf_size>;

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
    size_t read_index = 0;
    size_t pop_index = 0;
    buffer_t read_buf;
    uint8_t ack = 0;

    ssize_t
    parse_result(ssize_t res);
};