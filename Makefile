obj-m := lcd_platform.o
lcd_platform-objs += gpio-platform.o lcd.o
## some variables for the recipies defined below
ARCH            = arm
CROSS_COMPILE   = arm-none-linux-gnueabihf-
KERNEL_DIR_ARM  = /home/wrafique/Linux_source_code/linux_5.4/linux
KERNEL_DIR_HOST = /lib/modules/$(shell uname -r)/build

all:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR_ARM) M=$(PWD) modules

clean:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR_ARM) M=$(PWD) clean
	
help:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL_DIR_ARM) M=$(PWD) help
	
host:
	make CROSS_COMPILE=x86_64-linux-gnu- -C $(KERNEL_DIR_HOST) M=$(PWD) modules

scp:
	scp *.ko debian@192.168.7.2:/home/debian/kernel_modules