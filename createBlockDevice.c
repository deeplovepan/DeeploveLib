createBlockDevice.c
code
linux driver create block device

#include <linux/module.h>
#include "myBlockDeviceLib.h"
#include "myDevice.h"

struct block_device *targetBdev = NULL;

int blockDeviceRequest(request_queue_t *q, struct bio *bio)
{
	sendBioToBlockDevice(bio, targetBdev);
}

int blkOpen(struct inode *inode, struct file *file)
{
	return 0;
}

int blkClose(struct inode *inode, struct file *file)
{
	return 0;
}

int blkIoctl(struct inode *inode, struct file *file,
						unsigned int cmd, unsigned long arg)
{
	int result = -ENOTTY;
	result = ioctl_by_bdev(targetBdev, cmd, arg );
	return result;
}

struct block_device_operations blockOps = {
	.open = blkOpen,
	.release = blkClose,
	.ioctl = blkIoctl, 
	.owner = THIS_MODULE
};


struct MyDevice *myDevice;

static int hello_init(void) 
{ 
	printk(KERN_ALERT "Hello, world\n"); 
	if(targetBdev == NULL)
	{
		// use sd device as target bdev
		targetBdev = getBdevByMajorMinor(8, 16);
		
	}
	myDevice = kmalloc(sizeof(struct MyDevice), GFP_KERNEL);
	createBlockDevice(myDevice,
					  blockDeviceRequest, 231, 0,
					  &blockOps, "myBlock", 
					  get_capacity(targetBdev->bd_disk)); 
	
	return 0; 
} 


static void hello_exit(void) 
{ 
	printk(KERN_ALERT "Goodbye, cruel world\n"); 
	del_gendisk(myDevice->disk);
	put_disk(myDevice->disk);
	blk_cleanup_queue(myDevice->queue);
	kfree(myDevice);
	
} 

module_init(hello_init); 
module_exit(hello_exit); 