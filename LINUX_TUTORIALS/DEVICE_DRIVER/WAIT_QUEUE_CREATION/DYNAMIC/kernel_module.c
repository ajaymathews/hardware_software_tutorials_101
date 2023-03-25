#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>

#include<linux/kdev_t.h>
#include<linux/device.h>

#include<linux/fs.h> 
#include<linux/cdev.h>

#include<linux/slab.h> /* for kmalloc() and kfree() */
#include<linux/uaccess.h>/* for copy_to/from_user() */

#include<linux/kthread.h>
#include<linux/wait.h>


#define alloc_size 1024


dev_t maj_min_num=0;
uint8_t *alloc_kernel_space;

static struct class *sample_class;
static struct cdev sample_cdev;


static struct task_struct *wait_thread; /*a structure variable used  */


/*********** wait variable declaration ************/
wait_queue_head_t sample_wait_queue;
int wait_flag=0;



/********** module start/end function declaration *******/
static int __init driver_load_fun(void);
static void __exit driver_unload_fun(void);



/***********Declaration of file Operation Functions *********/
static int sample_device_file_open(struct inode *inode, struct file *file);
static int sample_device_file_release(struct inode *inode, struct file *file);
static ssize_t sample_device_file_read(struct file *filp,char __user *buf, size_t len, loff_t * off);
static ssize_t sample_device_file_write(struct file *filp, const char *buf, size_t len, loff_t * off);




/*********** creating our own structure variables(in this functions) for file operations ********************/
static struct file_operations sample_file_ops =
{
.owner = THIS_MODULE ,
.read  = sample_device_file_read,
.write = sample_device_file_write,
.open  = sample_device_file_open,
.release = sample_device_file_release,
};

/************Definition of Wait Function**************/ 

static int wait_function(void *unused) 
{	/* void *unused need to be written other wise it will show error while using passing function through thread_create() as an argument */
	while(1)
	{
		printk(KERN_INFO "Waiting.....!");
		wait_event_interruptible(sample_wait_queue,wait_flag!=0);
		if(wait_flag==1)
		{
		printk(KERN_INFO "Wait is interrupted by read operation");
		wait_flag=0;
		}
		else if(wait_flag==2)
		{
		printk(KERN_INFO "Wait is interrupted by Driver Unload command");
		return 0;
		}

	}
	return 0;

}


/****Defenition of file operation functions***********/

static int sample_device_file_open(struct inode *inode, struct file *file)
{
	if((alloc_kernel_space =kmalloc(alloc_size, GFP_KERNEL))==0)
	{/*this function allocates space on the kernal to read and write data to/from device files,and the address of alocated space is passed
	   to 'alloc_kernel_space' variable */
		printk(KERN_INFO "Cannot allocate space on kernel");
		return -1;
	}
	printk(KERN_INFO "Device File is opened..!");
	return 0;
}


static int sample_device_file_release(struct inode *inode, struct file *file)
{
	kfree(alloc_kernel_space);/* the allocated space from kernel is released */
	printk(KERN_INFO "File is released...!");
	return 0;
}


static ssize_t sample_device_file_read(struct file *filp,char __user *buf, size_t len, loff_t *off)
{
	copy_to_user(buf, alloc_kernel_space, alloc_size); /*used to copy data from the kernel_space to user_space  this is in format 
							    copy_to_user(to,from,data_size)*/
	wait_flag=1;
	wake_up_interruptible(&sample_wait_queue);
	printk(KERN_INFO "Data from the file is read");
	return 0;
}


static ssize_t sample_device_file_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
	copy_from_user(alloc_kernel_space, buf, len);
	printk(KERN_INFO "New data is written to the file");
	return len;
}




static int __init driver_load_fun(void)
{	

	/*********** creating maj/min number ******************/

	if(alloc_chrdev_region(&maj_min_num,0,1, "sample_device")>=0)
	{
		printk(KERN_INFO "Major_Number and Minor_Number assigned are %d %d \n",MAJOR(maj_min_num),MINOR(maj_min_num));
			
	}
	else
	{	printk(KERN_CRIT "Major_Minor NUmber assigning is failed\n");
		goto maj_min_fail;					      }



	/*creating cdev structure by cdev_init()along with the file operations possible*/
	
	cdev_init(&sample_cdev,&sample_file_ops);




	/*adding the device to the system before the device file, by assigning it with the min/maj number*/

	if((cdev_add(&sample_cdev,maj_min_num,1))<0)
	{
		printk(KERN_CRIT "Cannot add device to system");
		goto maj_min_fail;
	}






	/************ creating class for the device **************/

	if((sample_class = class_create( THIS_MODULE , "sample_device_class"))==NULL)
	{
	 	printk(KERN_CRIT "Device Class Creation failed \n");
	 	goto class_fail;
	}
	printk(KERN_INFO "Class for the device file is created\n");





	/************ creating device file for device ************/
	
	if((device_create(sample_class,NULL,maj_min_num,NULL,"sample_device"))==NULL)
	{
	 	printk(KERN_CRIT "Device Creation failed \n");
	 	goto device_fail;
	}
	printk(KERN_INFO "Device file is created,Check '/dev/' \n");



	/********wait queue creation*************/
	init_waitqueue_head(&sample_wait_queue);


	/***********creating thread***************/
	wait_thread = kthread_create(wait_function, NULL, "WaitThread");
	if(wait_thread)
	{
		printk(KERN_INFO "Thread Created Successfully\n");
		wake_up_process(wait_thread);
	}
	else
	{
		printk(KERN_INFO "Thread Creation Failed\n");
	}



	printk(KERN_INFO "Driver is loaded into the kernal\n");
	return 0;




	/************** In case of any failure ****************/

	device_fail:
		class_destroy(sample_class);

	class_fail:
		unregister_chrdev_region(maj_min_num,1);

	maj_min_fail:
	  
	       return -1;
}



void __exit driver_unload_fun(void) 
{
wait_flag=2;
wake_up_interruptible(&sample_wait_queue);

device_destroy(sample_class,maj_min_num);
printk(KERN_INFO "Device file is destroyed \n");

class_destroy(sample_class);
printk(KERN_INFO "Class is destroyed \n");

cdev_del(&sample_cdev);


unregister_chrdev_region(maj_min_num,1);


printk(KERN_INFO "Major/Minimum Number is Unregistered \n");


printk(KERN_INFO "Driver is unloaded from the kernal\n");

}

module_init(driver_load_fun);
module_exit(driver_unload_fun);



/************DRIVER META-INFORMATIONS*************/

MODULE_LICENSE("GPL");
MODULE_AUTHOR("@J");
MODULE_DESCRIPTION("SampleDriver");
MODULE_VERSION("1.0");
