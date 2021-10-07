## Introduction to Linux Kernel Modules

 sudo lsmod

lsmod - Show the status of modules in the Linux Kernel

```
$ sudo lsmod
Module                  Size  Used by
btrfs                1261568  0
xor                    24576  1 btrfs
zstd_compress         167936  1 btrfs
raid6_pq              114688  1 btrfs
ufs                    81920  0
qnx4                   16384  0
hfsplus               110592  0
hfs                    61440  0
minix                  36864  0
ntfs                  106496  0
msdos                  20480  0
jfs                   188416  0
xfs                  1282048  0
cpuid                  16384  0
xt_conntrack           16384  1
xt_MASQUERADE          20480  1
nf_conntrack_netlink    45056  0
nfnetlink              16384  2 nf_conntrack_netlink
xfrm_user              36864  1
xfrm_algo              16384  1 xfrm_user
xt_addrtype            16384  2
iptable_filter         16384  1
iptable_nat            16384  1
nf_nat                 40960  2 iptable_nat,xt_MASQUERADE
nf_conntrack          139264  4 xt_conntrack,nf_nat,nf_conntrack_netlink,xt_MASQUERADE
nf_defrag_ipv6         24576  1 nf_conntrack
nf_defrag_ipv4         16384  1 nf_conntrack
libcrc32c              16384  4 nf_conntrack,nf_nat,btrfs,xfs
bpfilter               32768  0
br_netfilter           28672  0
bridge                172032  1 br_netfilter
stp                    16384  1 bridge
llc                    16384  2 bridge,stp
aufs                  262144  0
overlay               114688  0
binfmt_misc            24576  1
nls_iso8859_1          16384  1
snd_intel8x0           45056  0
snd_ac97_codec        131072  1 snd_intel8x0
ac97_bus               16384  1 snd_ac97_codec
snd_pcm               106496  2 snd_intel8x0,snd_ac97_codec
intel_rapl_msr         20480  0
snd_seq_midi           20480  0
snd_seq_midi_event     16384  1 snd_seq_midi
intel_rapl_common      24576  1 intel_rapl_msr
crct10dif_pclmul       16384  1
ghash_clmulni_intel    16384  0
snd_rawmidi            36864  1 snd_seq_midi
joydev                 24576  0
snd_seq                69632  2 snd_seq_midi,snd_seq_midi_event
aesni_intel           372736  0
crypto_simd            16384  1 aesni_intel
cryptd                 24576  2 crypto_simd,ghash_clmulni_intel
snd_seq_device         16384  3 snd_seq,snd_seq_midi,snd_rawmidi
glue_helper            16384  1 aesni_intel
snd_timer              36864  2 snd_seq,snd_pcm
snd                    90112  7 snd_seq,snd_seq_device,snd_intel8x0,snd_timer,snd_ac97_codec,snd_pcm,snd_rawmidi
input_leds             16384  0
serio_raw              20480  0
vboxguest             352256  0
soundcore              16384  1 snd
mac_hid                16384  0
sch_fq_codel           20480  3
vmwgfx                299008  1
ttm                   106496  1 vmwgfx
drm_kms_helper        184320  1 vmwgfx
fb_sys_fops            16384  1 drm_kms_helper
syscopyarea            16384  1 drm_kms_helper
sysfillrect            16384  1 drm_kms_helper
sysimgblt              16384  1 drm_kms_helper
msr                    16384  0
parport_pc             40960  0
ppdev                  24576  0
lp                     20480  0
parport                53248  3 parport_pc,lp,ppdev
drm                   491520  4 vmwgfx,drm_kms_helper,ttm
sunrpc                393216  1
ip_tables              32768  2 iptable_filter,iptable_nat
x_tables               40960  5 xt_conntrack,iptable_filter,xt_addrtype,ip_tables,xt_MASQUERADE
autofs4                45056  2
hid_generic            16384  0
usbhid                 57344  0
hid                   131072  2 usbhid,hid_generic
video                  49152  0
crc32_pclmul           16384  0
psmouse               155648  0
e1000                 147456  0
ahci                   40960  2
i2c_piix4              28672  0
libahci                32768  1 ahci
pata_acpi              16384  0

```



hello_lkm.c

```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>


int simple_init(void) {
    printk(KERN_INFO "Loading A LKM\n");
    return 0;
}

void simple_exit(void) {
    printk(KERN_INFO "Removing LKM\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple LKM");
MODULE_AUTHOR("YUANBAO");



```

Makefile

```makefile
obj-m += hello_lkm.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

```

安装插件：

```bash
$ sudo insmod hello_lkm.ko 
```



运行插件

dmesg :  dmesg - print or control the kernel ring buffer

```

[  512.539711] hello_lkm: module verification failed: signature and/or required key missing - tainting kernel
[  512.540139] Loading A LKM

```



删除插件：

sudo rmmod hello_lkm



查看卸载的信息

```bash
sudo dmseg -c

[  512.539711] hello_lkm: module verification failed: signature and/or required key missing - tainting kernel
[  512.540139] Loading A LKM
[  938.606006] Removing LKM
```



## 练习

```bash
$ sudo dmesg -c
[ 1369.722783] Loading A LKM
[ 1369.722784] 7046029254386353131 
[ 1408.669347] Removing LKM
[ 1408.669348] gcd of 3000 and 25 is 25

```

新增代码：

```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>


int simple_init(void) {
    printk(KERN_INFO "Loading A LKM\n");
    printk(KERN_ERR "%llu \n", GOLDEN_RATIO_PRIME);
    return 0;
}

void simple_exit(void) {
    printk(KERN_INFO "Removing LKM\n");
    printk(KERN_ERR "gcd of 3000 and 25 is %lu\n", gcd(3000, 25));
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple LKM");
MODULE_AUTHOR("YUANBAO");

```



```c
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

```





```bash
$ sudo dmesg -c           
[ 1943.166211] value of HZ is 250
                
[ 1971.289834] Removing LKM
[ 1971.289835] gcd of 3000 and 25 is 25
[ 1974.525264] Loading A LKM
[ 1974.525266] value of GOLDEN_RATIO_PRIME is 7046029254386353131 
[ 1974.525283] value of HZ is 250
                
[ 2068.446343] Removing LKM
[ 2068.446344] gcd of 3000 and 25 is 25
[ 2095.852097] Loading A LKM
[ 2095.852099] value of GOLDEN_RATIO_PRIME is 7046029254386353131 
[ 2095.852118] value of HZ is 250, value of jiffies if 4295416191 
                
[ 2115.829954] Removing LKM
[ 2115.829955] gcd of 3000 and 25 is 25
[ 2115.829969] value of jiffies is 4295421185
[ 2119.165065] Loading A LKM
[ 2119.165066] value of GOLDEN_RATIO_PRIME is 7046029254386353131 
[ 2119.165084] value of HZ is 250, value of jiffies if 4295422019 
                
[ 2143.440856] Removing LKM
[ 2143.440857] gcd of 3000 and 25 is 25
[ 2143.440870] value of jiffies is 4295428088

```





## proc相关

```
The /proc file system is a “pseudo” file system that exists only in kernel memory
and used for process info statistics.
```

构建一个 /proc/hello 的一个模块：

hello.c

```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define BUF_SIZE 256
#define PROC_NAME "hello"

ssize_t proc_read(struct file *file, char __user *usr_buf,
size_t count, loff_t *pos);


static struct file_operations proc_ops = {
	.owner = THIS_MODULE,
	.read = proc_read,
};

// init function module is loaded
int proc_init(void) {
	proc_create(PROC_NAME, 0666, NULL, &proc_ops);
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
	rv = sprintf(buffer, "Hello world\n");
	
	raw_copy_to_user(usr_buf, buffer, rv);	

	return rv;
}


module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple LKM");
MODULE_AUTHOR("YUANBAO");

```





## 练习1

Design a kernel module that creates a /proc file named /proc/jiffies
that reports the current value of jiffies when the /proc/jiffies file
is read, such as with the command

```c
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/jiffies.h>

#define BUF_SIZE 256
#define PROC_NAME "jiffies"

ssize_t proc_read(struct file *file, char __user *usr_buf,
size_t count, loff_t *pos);


static struct file_operations proc_ops = {
	.owner = THIS_MODULE,
	.read = proc_read,
};

// init function module is loaded
int proc_init(void) {
	proc_create(PROC_NAME, 0666, NULL, &proc_ops);
	return 0;
}

void proc_exit(void) {
	remove_proc_entry(PROC_NAME, NULL);
}


/* Since /proc/hello can be accessed from user space, we must copy the
contents of buffer to user space using the kernel function raw_copy_to_user() */ 

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
	rv = sprintf(buffer, "current value of jiffies if %lu\n", jiffies);
	
	raw_copy_to_user(usr_buf, buffer, rv);	

	return rv;
}


module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple LKM");
MODULE_AUTHOR("YUANBAO");

```



```bash
$ cat /proc/jiffies
current value of jiffies if 4296653760
		
```



## 练习二

Design a kernel module that creates a proc file named /proc/seconds
that reports the number of elapsed seconds since the kernel module was
loaded. This will involve using the value of jiffies as well as the HZ
rate. When a user enters the command



```c
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

```


