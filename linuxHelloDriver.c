linuxHelloDriver.c
code
linux hello driver

/*
 *  linuxHelloDriver.c
 *  DeeploveLib
 *
 *  Created by System Administrator on 9/15/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <linux/module.h> 

static int hello_init(void) 
{ 
	printk(KERN_ALERT "Hello, world\n"); 
	
	return 0; 
} 


static void hello_exit(void) 
{ 
	printk(KERN_ALERT "Goodbye, cruel world\n"); 
} 

module_init(hello_init); 
module_exit(hello_exit); 

