cmake_minimum_required(VERSION 3.18)
project(intraconnection)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_SHARED_LIBRARY_SUFFIX .so)

set(WIRINGPI_INCLUDE ../wiringPi_mock/wiringPi)
set(ADC_SRC src/adc/main.cpp
    src/adc/mcp3424.cpp
    src/i2c/i2c.cpp
    src/i2c/serial_buffer.cpp)
    

if (APPLE)
    function(my_check validator_result_var item)
        get_filename_component(EXTENSION item LAST_EXT)
        if(NOT ${EXTENSION} MATCHES "so")
            set(${validator_result_var} FALSE PARENT_SCOPE)
        endif()
    endfunction()

    find_library(wiring NAMES wiringPi VALIDATOR my_check REQUIRED)
else()
    find_library(wiring NAMES wiringPi REQUIRED)
endif()



add_executable(intraconnection-adc ${ADC_SRC})

target_include_directories(intraconnection-adc PRIVATE
    include
    ${WIRINGPI_INCLUDE}
)

target_link_libraries(intraconnection-adc PUBLIC
    ${wiring}
)

add_library(mcp3424 SHARED
    src/adc/mcp3424.cpp
    src/i2c/i2c.cpp
    src/i2c/serial_buffer.cpp
)

target_include_directories(mcp3424 PRIVATE
    include
    ${WIRINGPI_INCLUDE}
)

target_link_libraries(mcp3424 PUBLIC
    ${wiring}
)