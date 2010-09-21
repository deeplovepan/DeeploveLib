/*
 *  myblockDeviceLib.h
 *  DeeploveLib
 *
 *  Created by System Administrator on 9/13/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MY_BLOCK_DEVICE_LIB_H
#define MY_BLOCK_DEVICE_LIB_H

#include <linux/fs.h>
#include <linux/blkdev.h>
#include "myDevice.h"

struct scsi_device* getScsiDevice(int hostNum, int channel,
								  int scsiId, int lun);
void getBdevMajorMinor(struct block_device *bdev,
					   unsigned int *major,
					   unsigned int *minor);
struct block_device* getBdevByMajorMinor(unsigned int major,
										 unsigned int minor);
void sendBioToBlockDevice(struct bio *bio, struct block_device *bdev);
void createBlockDevice(struct MyDevice *myDevice,
					   int(*reqFunc)(request_queue_t*, struct bio*),
					   unsigned int major,
					   unsigned int minor,
					   struct block_device_operations *blockOperations,
					   char *deviceName, sector_t sizeInSector);
sector_t getBlockDeviceSizeInSector(struct block_device *bdev);

#endif