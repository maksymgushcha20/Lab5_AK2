#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maksym Hushcha");
MODULE_DESCRIPTION("hello1 module that exports print_hello");

struct my_list_item {
    struct list_head list;
    ktime_t start_time;
    ktime_t end_time;
};

static LIST_HEAD(my_list_head);

void print_hello(void)
{
    struct my_list_item *item;
    item = kmalloc(sizeof(*item), GFP_KERNEL);
    if (!item)
        return;
    item->start_time = ktime_get();
    pr_info("Hello, world!\n");
    item->end_time = ktime_get();
    list_add_tail(&item->list, &my_list_head);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
    pr_info("hello1: Module loaded\n");
    return 0;
}

static void __exit hello1_exit(void)
{
    struct my_list_item *ptr, *tmp;
    pr_info("hello1: Module unloading\n");
    list_for_each_entry_safe(ptr, tmp, &my_list_head, list) {
        s64 diff_ns = ktime_to_ns(ktime_sub(ptr->end_time, ptr->start_time));
        pr_info("hello1: start_time=%lld ns, end_time=%lld ns, diff=%lld ns\n",
                ktime_to_ns(ptr->start_time),
                ktime_to_ns(ptr->end_time),
                diff_ns);
        list_del(&ptr->list);
        kfree(ptr);
    }
}

module_init(hello1_init);
module_exit(hello1_exit);

