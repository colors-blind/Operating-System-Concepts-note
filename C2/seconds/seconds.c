#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/jiffies.h>

#define BUF_SIZE 256
#define PROC_NAME "seconds"

ssize_t proc_read(struct file *file, char __user *usr_buf,
size_t count, loff_t *pos);

static long unsigned first_load_jiffies = 0;

static struct file_operations proc_ops = {
	.owner = THIS_MODULE,
	.read = proc_read,
};

// init function module is loaded
int proc_init(void) {
	proc_create(PROC_NAME, 0666, NULL, &proc_ops);
        first_load_jiffies = jiffies;
        printk(KERN_INFO "%lu\n", first_load_jiffies);
	return 0;
}

void proc_exit(void) {
	remove_proc_entry(PROC_NAME, NULL);
}


/* Since /proc/hello can be accessed from user space, we must copy the
contents of buffer to user space using the kernel function copy to user() */ 

ssize_t proc_read(struct file *file, char __user *usr_buf,
  size_t count, loff_t *pos) {
	int rv = 0;
	char buffer[BUF_SIZE];
	static int completed = 0;
	
	if (completed) {
		completed = 0;
		return 0;
	}

	completed = 1;
	rv = sprintf(buffer, "current value of jiffies if %lu first_load_jiffies is %lu seconds pass %lu\n", jiffies, first_load_jiffies, (jiffies - first_load_jiffies) / HZ);	
	raw_copy_to_user(usr_buf, buffer, rv);	

	return rv;
}


module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple LKM");
MODULE_AUTHOR("YUANBAO");

