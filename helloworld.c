#include <linux/init.h>
#include <linux/module.h>

static __init int hello_init(void)
{
	printk(KERN_ALERT "helloworld!\n");
	return 0;
}

static __exit void hello_exit(void)
{
	printk(KERN_ALERT "helloworld exit!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("great wall");
