#include <linux/init.h>
#include <linux/module.h>

static int num = 0;
static char *name = NULL;

module_param(num, int, S_IRUGO);
module_param(name, charp, S_IRUGO);


static __init int hello_init(void)
{
	printk(KERN_ALERT "helloworld init!\n");
	printk(KERN_ALERT "num=%d\nname=%s\n", num, name);
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