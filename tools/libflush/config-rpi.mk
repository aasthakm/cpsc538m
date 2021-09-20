# Define RPI specific variables
RPI_TOOLCHAIN_BIN = /usr/bin
#RPI_CC_FLAGS = --sysroot=${RPI_SYSROOT}

RPI_CC = ${RPI_TOOLCHAIN_BIN}/aarch64-linux-gnu-gcc

RPI_INCLUDES = -I /usr/include
RPI_CFLAGS = ${RPI_INCLUDES} -march=armv8-a -fPIE
RPI_LDFLAGS = ${RPI_INCLUDES} -march=armv8-a -fPIE

CC = ${RPI_CC} #${RPI_CC_FLAGS}
CFLAGS += ${RPI_CFLAGS} -g -flto
LDFLAGS += ${RPI_LDFLAGS} -fPIE -flto
