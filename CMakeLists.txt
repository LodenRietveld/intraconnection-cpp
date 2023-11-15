cmake_minimum_required(VERSION 3.18)
project(intraconnection)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(WIRINGPI_INCLUDE ../WiringPi/wiringPi)
set(ADC_SRC src/adc/main.cpp
    src/adc/mcp3424.cpp
    src/i2c/i2c.cpp
    src/i2c/serial_buffer.cpp)
    

find_library(wiring NAMES wiringPi REQUIRED)

add_executable(intraconnection-adc ${ADC_SRC})

target_include_directories(intraconnection-adc PRIVATE
    include
    ${WIRINGPI_INCLUDE})

target_link_libraries(intraconnection-adc PUBLIC
    ${wiring})