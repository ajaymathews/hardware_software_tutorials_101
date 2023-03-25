#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>

#include<linux/kdev_t.h>
#include<linux/device.h>
#include<linux/fs.h> 
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

#include<linux/sysfs.h>     
#include<linux/kobject.h>


#define alloc_size 1024



dev_t maj_min_num=0;
uint8_t *alloc_kernel_space;

volatile int sys_value=0;


static struct class *sample_class;
static struct cdev sample_cdev;

struct kobject *kobj_fold;/* this is used to createa folder at /sys */




/********** module start/end function declaration *******/
static int __init driver_load_fun(void);
static void __exit driver_unload_fun(void);



/***********Declaration of file Operation Functions *********/
static int sample_device_file_open(struct inode *inode, struct file *file);
static int sample_device_file_release(struct inode *inode, struct file *file);
static ssize_t sample_device_file_read(struct file *filp,char __user *buf, size_t len, loff_t * off);
static ssize_t sample_device_file_write(struct file *filp, const char *buf, size_t len, loff_t * off);


/*************declaration of sysfs functions************/

static ssize_t sysfs_show(struct kobject *kobj,struct kobj_attribute *attr,char *buf);

static ssize_t sysfs_store(struct kobject *kobj,struct kobj_attribute *attr,const char *buf,size_t count);
/*sysfs_show/store are the 2 functions that reads and writes into the system file */



struct kobj_attribute sysfs_file = __ATTR(sys_value, 0660,sysfs_show, sysfs_store); 
/* here sysfs_file is used to crete the file under the /sys folder */



/*********** creating our own structure variables(in this functions) for file operations ********************/
static struct file_operations sample_file_ops =
{
.owner = THIS_MODULE ,
.read  = sample_device_file_read,
.write = sample_device_file_write,
.open  = sample_device_file_open,
.release = sample_device_file_release,
};

/*************definition os sysfs functions***************/
static ssize_t sysfs_show(struct kobject *kobj,struct kobj_attribute *attr,char *buf)
{
printk(KERN_INFO "Reading from Sysfs");
return sprintf(buf,"%d",sys_value);
}

static ssize_t sysfs_store(struct kobject *kobj,struct kobj_attribute *attr,const char *buf,size_t count)
{
printk(KERN_INFO "Writing to Sysfs");
sscanf(buf,"%d",&sys_value);
return count;
}



/****Defenition of file operation functions***********/

static int sample_device_file_open(struct inode *inode, struct file *file)
{
	if((alloc_kernel_space =kmalloc(alloc_size, GFP_KERNEL))==0)
	{
		printk(KERN_INFO "Cannot allocate space on kernel");
		return -1;
	}
	printk(KERN_INFO "Device File is opened..!");
	return 0;
}
static int sample_device_file_release(struct inode *inode, struct file *file)
{
	kfree(alloc_kernel_space);
	printk(KERN_INFO "File is released...!");
	return 0;
}
static ssize_t sample_device_file_read(struct file *filp,char __user *buf, size_t len, loff_t *off)
{
	copy_to_user(buf, alloc_kernel_space, alloc_size);
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


/******************creating folder under the sys ***************/

kobj_fold = kobject_create_and_add("sample_sysyfs_folder",kernel_kobj);

/*sample_sysfs_folder is created under the /sys , kernel_kobj is to choose which folder inside the /sys should the directory creates,
kernel_kobj : /sys/kernel/
firmware_kobjto : /sys/firmware/
fs_kobjto : /sys/fs/
NULL :/sys/
*/

/*********************creating sysfile *****************/
if(sysfs_create_file(kobj_fold,&sysfs_file.attr))
	{
	printk(KERN_INFO "Cannot create sysfile");
	goto sys_fail;
	}



	printk(KERN_INFO "Driver is loaded into the kernal\n");
	return 0;




	/************** In case of any failure ****************/

	sys_fail:
		kobject_put(kobj_fold); /* removes the folder*/
		sysfs_remove_file(kernel_kobj,&sysfs_file.attr);
		/*removes file in the directory */


	device_fail:
		class_destroy(sample_class);

	class_fail:
		unregister_chrdev_region(maj_min_num,1);

	maj_min_fail:
	  
	       return -1;
}



void __exit driver_unload_fun(void) 
{

kobject_put(kobj_fold); /* removes the folder*/
sysfs_remove_file(kernel_kobj,&sysfs_file.attr);
/*removes file in the directory */


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
