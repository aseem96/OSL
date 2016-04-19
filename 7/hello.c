#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("HOME");
MODULE_AUTHOR("ASEEM R");
MODULE_DESCRIPTION("A SIMPLE HELLO WORLD MODULE");

static int __init hello_init(void) {
	printk(KERN_INFO "Hello, world!\n");
	return 0;
}

static void __exit hello_cleanup(void) {
	printk(KERN_INFO "Goodbye.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);