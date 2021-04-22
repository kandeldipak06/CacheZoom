obj-m += cachezoom_kernel.o

# sudo cat /proc/kallsyms | grep lapic_next_deadline | awk '{print $$1}'
# sudo cat /proc/kallsyms | grep local_apic_timer_interrupt | awk '{print $$1}'

KBUILD_CFLAGS += -w -msse4 -mpreferred-stack-boundary=9

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules  #The default target for external modules. Build the modules in the current directory
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean  #Remove all generated files in the module directory only.
