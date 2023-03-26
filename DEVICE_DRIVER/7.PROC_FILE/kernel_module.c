#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>

#include<linux/kdev_t.h>
#include<linux/device.h>

#include<linux/fs.h> 
#include<linux/cdev.h>

#include<linux/slab.h>
#include<linux/uaccess.h>

#include<linux/ioctl.h>

#include<linux/proc_fs.h>



#define alloc_size 1024

#define WR_VAL _IOW('a','a',int32_t*)
#define RD_VAL _IOW('a','b',int32_t*)


dev_t maj_min_num=0;
uint8_t *alloc_kernel_space;
uint32_t ioctl_space; 

char proc_array[20];
static int len=1;


static struct class *sample_class;
static struct cdev sample_cdev;


/********** module start/end function declaration *******/
static int __init driver_load_fun(void);
static void __exit driver_unload_fun(void);



/***********Declaration of file Operation Functions *********/
static int sample_device_file_open(struct inode *inode, struct file *file);
static int sample_device_file_release(struct inode *inode, struct file *file);
static ssize_t sample_device_file_read(struct file *filp,char __user *buf, size_t len, loff_t * off);
static ssize_t sample_device_file_write(struct file *filp, const char *buf, size_t len, loff_t * off);

/**********Declaration of ioctl function**********************/
static long sample_device_file_ioctl(struct file *file,unsigned int cmd, unsigned long arg);


/************Declaration of proc functions*******************/
static int sample_proc_open(struct inode *inode, struct file *file);
static int sample_proc_release(struct inode *inode, struct file *file);
static ssize_t sample_proc_read(struct file *filp,char __user *buf, size_t len, loff_t * off);
static ssize_t sample_proc_write(struct file *filp,const char *buf, size_t len, loff_t * off);




/*********** creating our own structure variables(in this functions) for file operations ********************/
static struct file_operations sample_file_ops =
{
.owner = THIS_MODULE ,
.read  = sample_device_file_read,
.write = sample_device_file_write,
.open  = sample_device_file_open,
.unlocked_ioctl=sample_device_file_ioctl,
.release = sample_device_file_release,
};


/*********** creating our own structure variables(in this functions) for proc file operations ********************/
static struct file_operations sample_proc_ops =
{
.open  = sample_proc_open,
.read  = sample_proc_read,
.write = sample_proc_write,
.release = sample_proc_release,
};



/****Defenition of file operation functions***********/

static int sample_device_file_open(struct inode *inode, struct file *file)
{

	printk(KERN_INFO "Device File is opened..!");
	return 0;
}
static int sample_device_file_release(struct inode *inode, struct file *file)
{

	printk(KERN_INFO "File is released...!");
	return 0;
}
static ssize_t sample_device_file_read(struct file *filp,char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Data from the file is read");
	return 0;
}
static ssize_t sample_device_file_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "New data is written to the file");
	return 0;
}

/* (to,from,length); format is used in these */
static long sample_device_file_ioctl(struct file *file,unsigned int cmd, unsigned long arg)
{
if(cmd==WR_VAL)
	{
	copy_from_user(&ioctl_space,(int32_t*)arg,sizeof(ioctl_space));
	printk(KERN_INFO "value %d is copied to kernel",ioctl_space);	
	}
else if(cmd==RD_VAL)
	{
	copy_to_user((int32_t*)arg,&ioctl_space,sizeof(ioctl_space));
	printk(KERN_INFO "value %d is copied to user",ioctl_space);	
	}
return 0;
}



/****Defenition of proc file operation functions***********/

static int sample_proc_open(struct inode *inode, struct file *file)
{

	printk(KERN_INFO "Proc File is opened..!");
	return 0;
}

static int sample_proc_release(struct inode *inode, struct file *file)
{

	printk(KERN_INFO "Proc File is released...!");
	return 0;
}
/*in here lengh is used because len is taken for anothr purose*/
static ssize_t sample_proc_read(struct file *filp,char __user *buf, size_t length, loff_t *off)
{
	if(len)
	{
		len=0;
	}
	else
	{
		len=1;
		return 0;
	}
	copy_to_user(buf,proc_array,sizeof(proc_array));
	printk(KERN_INFO "Data is read from proc file");
	return length;
}

static ssize_t sample_proc_write(struct file *filp,const char *buf, size_t len, loff_t * off)
{
	copy_from_user(proc_array,buf,len);
	printk(KERN_INFO "New data is written to the proc file");
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


	/**********Proc file creation ***************/

	proc_create("sample_proc_file",0666,NULL,&sample_proc_ops);
/*proc file in /proc/ location is created using this */ 


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

remove_proc_entry("sample_proc_file",NULL);
/*removing the proc file created*/

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
