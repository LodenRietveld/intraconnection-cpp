extern "C" {
    #include <unistd.h>
}

#include <cstring>

#include "i2c/serial_buffer.hpp"

void
serial_buffer_t::set_fd(int fd)
{
    this->fd = fd;
}

uint32_t
serial_buffer_t::read(size_t size)
{
    if (size < 3 || size > 4)
        return err;
    
    uint8_t read_buf[size];
    memset(read_buf, 0, size);
    auto res = ::read(fd, reinterpret_cast<void*>(read_buf), size);

    if (res < 0)
        return err;

    return process_read_value(read_buf, size);
}

ssize_t
serial_buffer_t::write(uint8_t* buf, size_t size)
{
    return ::write(fd, buf, size);
}

uint32_t
serial_buffer_t::process_read_value(uint8_t* buf, size_t size)
{
    if (size == 4) {
        return *reinterpret_cast<uint32_t*>(buf);
    } else {
        return (buf[0] << 16) | (buf[1] << 8) | (buf[2]);
    }
}