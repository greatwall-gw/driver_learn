#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

static dev_t devId;
static struct class *cls = NULL;
static struct cdev myDev;

static int my_open(struct inode *inode, struct file *file)
{
	printk("open file success!\n");
	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	printk("release file success!\n");
	return 0;
}

static int my_read(struct file *file, char __user *user, size_t size, loff_t *offp)
{
	char buf[] = "read kernel data!";
	size_t read_size = (sizeof(buf) > size ? size : sizeof(buf));
	if (copy_to_user(user, buf, read_size) != 0)
	{
		printk("read error!\n");
		return -1;
	}
	return read_size;
}

static int my_write(struct file *fule, const char __user *user, size_t size, loff_t *offp)
{
	char buf[64];
	size_t write_size = (sizeof(buf) > size ? size : sizeof(buf));
	if (copy_from_user(buf, user, write_size) != 0)
	{
		printk("write error!\n");
		return -1;
	}

	printk(KERN_ALERT "kernel read data: %s\n", buf);
	return write_size;
}

static struct file_operations my_ops = 
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_release,
	.read = my_read,
	.write = my_write
};

static void hello_cleanup(void)
{
	cdev_del(&myDev);
	device_destroy(cls, devId);
	class_destroy(cls);
	unregister_chrdev_region(devId, 1);
}

static __init int hello_init(void)
{
	int result = 0;
	result = alloc_chrdev_region(&devId, 0, 1, "great-wall-dev");
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

	if (device_create(cls, NULL, devId, "", "hello%d", 0) == NULL)
	{
		printk(KERN_ALERT "create device error!\n");
		goto err;
	}
	else
	{
		printk(KERN_ALERT "create device success!\n");
	}

	myDev.owner = THIS_MODULE;
	myDev.ops = &my_ops;

	cdev_init(&myDev, &my_ops);
	result = cdev_add(&myDev, devId, 1);
	if (result != 0)
	{
		printk(KERN_WARNING "add cdev error!\n");
  			goto err;
	}



	printk(KERN_ALERT "init hello success!\n");

	return 0;

err:
	hello_cleanup();
	return -1;
}

static __exit void hello_exit(void)
{
	hello_cleanup();
	printk(KERN_ALERT "exit hello success!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("great wall");
