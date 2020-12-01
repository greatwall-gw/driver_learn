#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/device.h>

static dev_t my_dev;
static struct class *cls = NULL;

static __init int hello_init(void)
{
	int result = 0;
	result = alloc_chrdev_region(&my_dev, 0, 1, "great-wall-dev");
	if (result)
	{
		printk(KERN_ALERT "alloc char dev error %d\n", result);
		goto err;
	}
	else
	{
		printk(KERN_ALERT "alloc char dev success!\n");
	}

	cls = class_create(THIS_MODULE, "great-wall-class");
	if (IS_ERR(cls))
	{
		printk(KERN_ALERT "create class error!\n");
		goto err;
	}
	else
	{	
		printk(KERN_ALERT "create class success!\n");
	}

	if (device_create(cls, NULL, my_dev, "", "hello%d", 0) == NULL)
	{
		printk(KERN_ALERT "create device error!\n");
		goto err;
	}
	else
	{
		printk(KERN_ALERT "create device success!\n");
	}


	printk(KERN_ALERT "init hello success!\n");

	return 0;

err:
	device_destroy(cls, my_dev);
	class_destroy(cls);
	unregister_chrdev_region(my_dev, 1);
	return -1;
}

static __exit void hello_exit(void)
{
	device_destroy(cls, my_dev);
	class_destroy(cls);
	unregister_chrdev_region(my_dev, 1);
	printk(KERN_ALERT "exit hello success!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("great wall");
