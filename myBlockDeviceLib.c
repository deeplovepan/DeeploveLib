/*
 *  myblockDeviceLib.c
 *  DeeploveLib
 *
 *  Created by System Administrator on 9/13/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "myBlockDeviceLib.h"
#include "myDevice.h"

sector_t getBlockDeviceSizeInSector(struct block_device *bdev)
{
	return get_capacity(bdev->bd_disk);
}

void createBlockDevice(struct MyDevice *myDevice,
					   int(*reqFunc)(request_queue_t*, struct bio*),
					   unsigned int major,
					   unsigned int minor,
					   struct block_device_operations *blockOperations,
					   char *deviceName,
					   sector_t sizeInSector)
{
	request_queue_t *queue = blk_alloc_queue(GFP_KERNEL);
	if (!queue)
	{
		goto ERROR;
	}
	myDevice->queue = queue;
	queue->queuedata = myDevice;
	queue->backing_dev_info.congested_fn = NULL;
	queue->backing_dev_info.congested_data = NULL;
	queue->unplug_fn = NULL;
	queue->issue_flush_fn = NULL;

	blk_queue_make_request(queue, reqFunc);
	
	struct gendisk *disk = alloc_disk(1);
	if(!disk)
	{
		goto ERROR;
	}
	myDevice->disk = disk;
	disk->major = major;
	disk->first_minor = minor;
	disk->fops = blockOperations;
	disk->queue = queue;
	disk->private_data = myDevice;	
	
	set_capacity(disk, sizeInSector);

	
	sprintf(disk->disk_name, "%s-%d", deviceName, minor);
	add_disk(disk);
	
	return;
	
ERROR:
	printk("error\n");
}

void sendBioToBlockDevice(struct bio *bio, struct block_device *bdev)
{
	bio->bi_bdev = bdev;
	generic_make_request(bio);
}

void getBdevMajorMinor(struct block_device *bdev,
					   unsigned int *major,
					   unsigned int *minor)
{
	dev_t majorMinor = bdev->bd_dev;
	*major = MAJOR(majorMinor);
	*minor = MINOR(majorMinor);
}

struct block_device* getBdevByMajorMinor(unsigned int major,
							 unsigned int minor)
{
	dev_t majorMinor = MKDEV(major, minor);
	struct block_device *bdev = bdget(majorMinor);
	int err = -ENOMEM;
	if(bdev)
	{
		unsigned mode = FMODE_READ|FMODE_WRITE;
		int flags =  O_RDWR | O_SYNC;
		err = blkdev_get(bdev, mode, flags);
	}
	if(err)
	{
		bdev = NULL;
	}
	return bdev;
}

