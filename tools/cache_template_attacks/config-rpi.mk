# Define Android specific variables
ROOTDIR = /home/pi/workspace/rpi-sc
RPI_TOOLCHAIN_BIN = /usr/bin
#RPI_SYSROOT = ${RPI_NDK_PATH}/platforms/${RPI_PLATFORM}/arch-arm64
#RPI_CC_FLAGS = --sysroot=${RPI_SYSROOT}

RPI_CC = ${RPI_TOOLCHAIN_BIN}/aarch64-linux-gnu-gcc

RPI_INCLUDES = -I /usr/include -I ${ROOTDIR}/libflush
RPI_CFLAGS = ${RPI_INCLUDES} -march=armv8-a -fPIE
RPI_LDFLAGS = -L ${ROOTDIR}/libflush/build/armv8/release -march=armv8-a -fPIE

CC = ${RPI_CC} #${RPI_CC_FLAGS}
CFLAGS += ${RPI_CFLAGS} -g -flto
LDFLAGS += ${RPI_LDFLAGS} -fPIE -flto
