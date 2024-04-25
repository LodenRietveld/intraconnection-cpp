cmake_minimum_required(VERSION 3.18)
project(intraconnection)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_SHARED_LIBRARY_SUFFIX .so)

if(DEFINED ENV{CONDA_PREFIX})
  set(CMAKE_IGNORE_PATH $ENV{CONDA_PREFIX}/bin)
endif()

set(WIRINGPI_INCLUDE ../wiringPi_mock/wiringPi)
set(ADC_SRC src/adc/main.cpp
    src/adc/mcp3424.cpp
    src/adc/adcs.cpp
    src/i2c/i2c.cpp
    src/i2c/serial_buffer.cpp
    src/util/util.cpp
    src/util/mock_adc.cpp)


include(FetchContent)

if (APPLE)
    function(my_check validator_result_var item)
        get_filename_component(EXTENSION item LAST_EXT)
        if(NOT ${EXTENSION} MATCHES "so")
            set(${validator_result_var} FALSE PARENT_SCOPE)
        endif()
    endfunction()

    find_library(wiring NAMES wiringPi VALIDATOR my_check REQUIRED)
    add_compile_definitions(MOCK_VALUES)
    find_library(zmq NAMES zmq REQUIRED 
        PATH /usr/local/lib)
else()
    find_library(wiring NAMES wiringPi REQUIRED)
    find_library(zmq NAMES zmq REQUIRED)
endif()


FetchContent_Declare(
    cppzmq
    GIT_REPOSITORY  https://github.com/zeromq/cppzmq.git
    GIT_TAG         c94c20743ed7d4aa37835a5c46567ab0790d4acc
)

option(CPPZMQ_BUILD_TESTS OFF)
set(CPPZMQ_BUILD_TESTS OFF)

FetchContent_MakeAvailable(cppzmq)

add_executable(intraconnection-adc ${ADC_SRC})

target_include_directories(intraconnection-adc PRIVATE
    include
    /usr/local/include/
    ${WIRINGPI_INCLUDE}
    ${cppzmq_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/analog_filter/include
)

target_link_libraries(intraconnection-adc PUBLIC
    ${wiring}
    cppzmq
    ${zmq}
)

add_library(mcp3424 SHARED
    src/adc/mcp3424.cpp
    src/i2c/i2c.cpp
    src/i2c/serial_buffer.cpp
)

target_include_directories(mcp3424 PRIVATE
    include
    ${WIRINGPI_INCLUDE}
    ${CMAKE_SOURCE_DIR}/analog_filter/include
)

target_link_libraries(mcp3424 PUBLIC
    ${wiring}
)
