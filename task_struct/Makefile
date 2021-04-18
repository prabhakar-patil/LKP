KDIR := /lib/modules/$(shell uname -r)/build

obj-m = task_struct_traversal.o
obj-m += task_struct_list_siblings.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

