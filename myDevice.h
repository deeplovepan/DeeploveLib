myDevice.h
code
linux driver create block device


/*
 *  myDevice.h
 *  DeeploveLib
 *
 *  Created by System Administrator on 9/14/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MY_DEVICE_H
#define MY_DEVICE_H

struct MyDevice {
	request_queue_t *queue;
	struct gendisk *disk;
};

#endif