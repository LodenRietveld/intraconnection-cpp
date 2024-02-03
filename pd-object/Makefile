# Makefile for mcp3424 puredate object

lib.name = intraconnection_adc

WIRING_DIR=../../wiringPi${MOCK}/wiringPi

class.sources = intraconnection_adc.cpp
shared.sources = ../src/adc/mcp3424.cpp \
../src/i2c/i2c.cpp 	\
../src/i2c/serial_buffer.cpp \
${WIRING_DIR}/wiringPi.c \
${WIRING_DIR}/wiringSerial.c \
${WIRING_DIR}/wiringShift.c \
${WIRING_DIR}/piHiPri.c \
${WIRING_DIR}/piThread.c \
${WIRING_DIR}/wiringPiSPI.c \
${WIRING_DIR}/wiringPiI2C.c \
${WIRING_DIR}/softPwm.c \
${WIRING_DIR}/softTone.c				

datafiles = mcp3424.pd README.txt LICENSE.txt


cflags?=-mmacosx-version-min=13.2

CFLAGS=?=-I../include \
-I${WIRING_DIR}

c.flags:=-std=gnu11 \
-stdlib=libc

CPPFLAGS?=-I../include \
-I${WIRING_DIR}

CXXFLAGS:=-std=gnu++17 \
-stdlib=libc++

CC=gcc
CXX=g++

PDLIBBUILDER_DIR=../pd-lib-builder

export MACOSX_DEPLOYMENT_TARGET=13.2

include ${PDLIBBUILDER_DIR}/Makefile.pdlibbuilder