extern "C" {
    #include <unistd.h>
}

#include "i2c/serial_buffer.hpp"

void
serial_buffer_t::set_fd(int fd)
{
    this->fd = fd;
}

ssize_t
serial_buffer_t::parse_result(ssize_t res)
{
    if (res > 0) {
        return res;
    } else {
        return static_cast<int>(res);
    }
}

uint32_t
serial_buffer_t::read(size_t size)
{
    uint8_t read_buf[size] = {0};
    auto res = ::read(fd, reinterpret_cast<void*>(read_buf), size);
    uint8_t err = ((int) res < 0) << 8;

    if (size == 4) {
        return *reinterpret_cast<uint32_t*>(read_buf) | (err << 24);
    } else if (size == 3) {
        return (err < 24) | (read_buf[0] << 16) | (read_buf[1] << 8) | (read_buf[2]);
    } else {
        return 1 << 31;
    }
}

ssize_t
serial_buffer_t::write(uint8_t* buf, size_t size)
{
    return ::write(fd, buf, size);
}