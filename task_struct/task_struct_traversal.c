#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/sched/signal.h>

static int __init task_struct_init (void)
{
	struct task_struct *p;
	unsigned long cnt = 0;

	printk (KERN_INFO"Entering: %s\n", __FUNCTION__);

	// traverse through all processes
	for_each_process(p) {
		if (p->pid == 1)
			printk (KERN_INFO"Found init process\n");
		cnt++;
		printk (KERN_INFO"pid[%lu]=%d\n", cnt, p->pid);
	}

	printk (KERN_INFO"process count: %lu\n", cnt);
	printk (KERN_INFO"pid[current: %d, parent: %d]\n", current->pid, current->parent->pid);
	return 0;
}

static void __exit task_struct_exit (void)
{
	printk (KERN_INFO"Exiting task_struct module\n");
	printk (KERN_INFO"pid[current: %d, parent: %d]\n", current->pid, current->parent->pid);
}


module_init (task_struct_init);
module_exit (task_struct_exit);

MODULE_LICENSE ("GPL");
