#### module 的基本结构和编译 helloworld.c
```c
#include <linux/init.h>
#include <linux/module.h>
module_init();
module_exit();

MODULE_LICENSE();
MODULE_AUTHOR();
```

#### 模块参数 hellopara.c
```c
module_param(name, type, perm);
name: 参数名
type: 参数类型
perm: 权限
```

####  设备编号 hellodev.c
```c
#include <linux/kdev_t.h>
MAJOR(dev_t dev);
MINOR(dev_t dev);

MKDEV(int major, int minor);

#include <linux/fs.h>
int register_chrdev_region(dev_t, unsigned, const char *);
1)需要注册的设备编号
2)连续编号个数
3)设备名，会出现在/proc/devices中
注册成功返回0，失败返回一个错误码

int alloc_chrdev_region(dev_t *, unsigned, unsigned, const char *);
1)设备编号
2)第一个次设备号，常用0
3)连续编号个数
4)设备名
成功注册返回0，失败返回一个错误码

void unregister_chrdev_region(dev_t, unsigned);
1)待注销的设备号
2)连续的设备号个数
```

####  自动创建设备节点 helloudev.c
```c
#include <linux/device.h>

class_create(owner, name)      
owner:当前模块
name：类名称
返回一个struct class类型指针，返回值需要使用IS_ERR()检查，成功创建后可在/sys/class下找到相应的目录

void class_destroy(struct class *cls);

struct device *device_create(struct class *cls, struct device *parent,
                 dev_t devt, void *drvdata,
                 const char *fmt, ...);
cls:类
parent：父设备，没有为NULL
devt：设备号
drvdata：被添加到该设备回调的数据，不能为NULL
fmt：设备名

void device_destroy(struct class *cls, dev_t devt);
```
####  字符设备
```c
#include <linux/cdev.h>

void cdev_init(struct cdev *cdev, struct file_operations *fops);
1)待初始化设备
2)Fops结构

intcdev_add(struct cdev *dev, dev_t num, unsigned int count);
1)待添加的设备
2)设备响应的第一个设备号
3)响应的设备个数

void cdev_del(struct cdev *dev);
1)待删除的设备

#include <linux/fs.h>
static struct file_operations myFops = {
        .owner = THIS_MODULE,
        .read = my_read,
        .write = my_write,
        .open = my_open,
        .release = my_release,
};

int (*open)(struct inode *, struct file *);
1)检查设备特定的错误
2)如果他是第一次打开，初始化该设备

int (*release)(struct inode *, struct file *);

ssize_t (*read)(struct file *file, char __user *user, size_t size, loff_t *offp);

ssize_t (*write)(struct file *fule, const char __user *user, size_t size, loff_t *offp);

static inlinelong copy_from_user(void *to, const void __user * from, unsignedlong n);

static inlinelong copy_to_user(void __user *to, const void *from, unsigned long n);        

```

