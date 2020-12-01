#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>

static dev_t devId;
static struct class *cls = NULL;

static __init int hello_init(void)
{
	int result = 0;

	result = alloc_chrdev_region(&devId, 0, 1, "greatwall-alloc-dev");
	if (result)
	{
		printk(KERN_ALERT "alloc dev id error:%d\n", result);
		goto err;
	}
	else
	{
		printk(KERN_ALERT "alloc dev id success!\n");
	}

	cls = class_create(THIS_MODULE, "greatwall-class");
	if (IS_ERR(cls))
	{
		printk(KERN_ALERT "create class error!\n");
		goto err;
	}

	if (device_create(cls, NULL, devId, "", "hello") == NULL)
	{
		printk(KERN_ALERT "create device error!\n");
		goto err;
	}

	printk(KERN_ALERT "helloworld init success!\n");
	return 0;

err:	
	device_destroy(cls, devId);
	class_destroy(cls);
	unregister_chrdev_region(devId, 1);
	
	return -1;
}

static __exit void hello_exit(void)
{

	device_destroy(cls, devId);
	class_destroy(cls);
	unregister_chrdev_region(devId, 1);
	printk(KERN_ALERT "helloworld exit!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("great wall");
