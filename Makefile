CONFIG_MODULE_SIG=n
 
obj-m:=hello.o
#hello-objs:=helloworld.o
hello-objs:=hellochrdev.o
 
KERN_DIR=/lib/modules/`uname -r`/build/
PWD_DIR=$(shell pwd)
 
default:
		$(MAKE) -C $(KERN_DIR) M=$(PWD_DIR) modules
 
clean:
		rm -rf *.o *.ko *.mod.c .*.cmd .*.cmd.c modules.* Module.* .tmp_versions