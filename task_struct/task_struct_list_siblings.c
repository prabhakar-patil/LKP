#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/sched/task.h>
#include <linux/sched/signal.h>

static int __init task_struct_init (void)
{
	struct task_struct *p;
	unsigned long cnt = 0;
	struct list_head *head;
	//struct list_head *pos; //uncomment when using other ways

	printk (KERN_INFO"Enter: %s\n", __FUNCTION__);

	if (list_empty(&current->parent->children))
		printk (KERN_INFO"No siblings\n");

	// traverse through all sibling
	head = &current->parent->children;

	//way 1
	/*for(pos=head->next; pos != head; pos = pos->next) {
		p = list_entry(pos, struct task_struct, sibling);
		cnt++;
		printk (KERN_INFO"sibling[%lu]: pid=%d, comm=%s, ppid=%d, parent_comm=%s\n", cnt, p->pid, p->comm, p->parent->pid, p->parent->comm);
	}*/

	// way 2	
	/*list_for_each(pos, head) {
		p = list_entry(pos, struct task_struct, sibling);
		cnt++;
		printk (KERN_INFO"sibling[%lu]: pid=%d, comm=%s, ppid=%d, parent_comm=%s\n", cnt, p->pid, p->comm, p->parent->pid, p->parent->comm);
	}*/
	
	// way 3
	/*list_for_each_entry(p, head, sibling) {
		cnt++;
		printk (KERN_INFO"sibling[%lu]: pid=%d, comm=%s, ppid=%d, parent_comm=%s\n", cnt, p->pid, p->comm, p->parent->pid, p->parent->comm);
	}*/

	//way 4
	for(p = list_entry(head->next, struct task_struct, sibling); \
			(&p->sibling) != head; \
			p = list_entry(p->sibling.next, struct task_struct, sibling)) {
		cnt++;
		printk (KERN_INFO"sibling[%lu]: pid=%d, comm=%s, ppid=%d, parent_comm=%s\n", cnt, p->pid, p->comm, p->parent->pid, p->parent->comm);
	}


	printk (KERN_INFO"sibling count: %lu\n", cnt);
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
