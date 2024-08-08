#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define MYDEV_NAME "miralis driver"

MODULE_LICENSE("GPL");

static struct file_operations fops = {
    .owner = THIS_MODULE, 
};

static int __init driver_init(void) /* Constructor */
{
    printk(KERN_INFO "Loading driver...\n");

    int err;
    err = register_chrdev(0, MYDEV_NAME, &fops);

    if(err < 0)
    {
        printk(KERN_ERR "Failed to register device!\n");
        return err;
    }

    printk(KERN_INFO "Successfully registered miralis device.\n");  

     asm volatile (
        "li a6, 3\n"           // Miralis ABI FID: benchmark final result
        "li a7, 0x08475bcd\n"  // Miralis ABI EID
        "ecall\n"
    );

    return 0;
}

static void __exit driver_exit(void) /* Destructor */
{
    unregister_chrdev(0, MYDEV_NAME); 
    printk(KERN_INFO "Goodbye from driver!\n");
}

module_init(driver_init);
module_exit(driver_exit);