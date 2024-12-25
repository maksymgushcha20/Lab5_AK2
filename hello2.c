#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/moduleparam.h>
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maksym Hushcha");
MODULE_DESCRIPTION("hello2 module that uses print_hello from hello1");

static uint count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "Number of times to call print_hello");

static int __init hello2_init(void)
{
    uint i;
    pr_info("hello2: Module loaded, count=%u\n", count);
    if (count == 0 || (count >= 5 && count <= 10)) {
        pr_warn("hello2: Suspicious count value=%u\n", count);
    }
    if (count > 10) {
        pr_err("hello2: Invalid count value=%u, returning -EINVAL\n", count);
        return -EINVAL;
    }
    for (i = 0; i < count; i++) {
        print_hello();
    }
    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("hello2: Module unloading\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

