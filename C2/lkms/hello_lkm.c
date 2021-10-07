#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/jiffies.h>


int simple_init(void) {
    printk(KERN_INFO "Loading A LKM\n");
    printk(KERN_ERR "value of GOLDEN_RATIO_PRIME is %llu \n", GOLDEN_RATIO_PRIME);
    printk(KERN_INFO "value of HZ is %u, value of jiffies if %lu \n ", HZ, jiffies);
    return 0;
}

void simple_exit(void) {
    printk(KERN_INFO "Removing LKM\n");
    printk(KERN_ERR "gcd of 3000 and 25 is %lu\n", gcd(3000, 25));
    printk(KERN_ERR "value of jiffies is %lu\n", jiffies);
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple LKM");
MODULE_AUTHOR("YUANBAO");

