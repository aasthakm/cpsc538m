ifeq ($(KERNELRELEASE),)
KERNELDIR = /lib/modules/`uname -r`/build
PWD := $(shell pwd)

CFLAGS += -Wno-unused-function

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

else

$(info Building with KERNELRELEASE = $(KERNELRELEASE))

obj-m := kmod_lsm.o
kmod_lsm-objs :=	\
	kmod.o

endif
