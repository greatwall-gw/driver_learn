#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

#define IS_ALLOC_DEV 0

dev_t devId;

static __init int hello_init(void)
{
	int result = 0;
#if IS_ALLOC_DEV

	result = alloc_chrdev_region(&devId, 0, 1, "greatwall-alloc-dev");
	if (result)
	{
		printk(KERN_ALERT "alloc dev id error:%d\n", result);
	}
	else
	{
		printk(KERN_ALERT "alloc dev id success!\n");
	}
	
#else
	result = register_chrdev_region(MKDEV(400, 0), 10, "greatwall-dev");
	if (result)
	{
		printk(KERN_ALERT "register dev id error:%d!\n", result);
	}
	else
	{
		printk(KERN_ALERT "register dev id success!\n");
	}
#endif
	
	return 0;
}

static __exit void hello_exit(void)
{

#if IS_ALLOC_DEV
	unregister_chrdev_region(devId, 1);
#else 
	unregister_chrdev_region(MKDEV(400, 0), 10);
#endif

	printk(KERN_ALERT "helloworld exit!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("great wall");
