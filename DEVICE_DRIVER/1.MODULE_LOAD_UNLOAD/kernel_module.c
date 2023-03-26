#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>




static int __init start_fun(void) /*This functn will execute first when drivr is loaded into the kernal using insmod*/
{				  

printk(KERN_INFO "Module is loaded into the kernal\n");/*printf is user space fun, and it cant be used here,but printk is a kernal level function*/

/**********MESSAGE FORMATS FOR PRINTK()*********/
/*
printk(KERN_ALERT "Alert messages");
printk(KERN_CRIT "critical messages before s/w or h/w failure");
printk(KERN_ERR "message to report an error"); 
*/

return 0;
}



void __exit end_fun(void) /* this function will executes when driver is unloaded from the kernal using rmmod */
{
printk(KERN_INFO "Module is unloaded from the kernal\n");

}

module_init(start_fun);/* using this macro the function start_fun() will register itself */
module_exit(end_fun);




/*******META-INFORMATION ABOUT THE MODULE********/

MODULE_LICENSE("GPL");/*to show that the above module is of free open source license meant for software*/
MODULE_AUTHOR("@J");
MODULE_DESCRIPTION("SampleDriver");
MODULE_VERSION("1.0");
