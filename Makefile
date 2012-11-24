obj-m += nttgps.o
#generate the path
CURRENT_PATH:=$(shell pwd)
#the current kernel version number

#the absolute path
LINUX_KERNEL_PATH:=/home/chenwenjin/pkgbuild/test/android_kernel_samsung_smdk4210/
#complie object
all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) ARCH=arm CROSS_COMPILE=arm-eabi- $(LINUX_KERNEL_PATH).config modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean

