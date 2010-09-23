/*
 *  testWorkQueue.c
 *  DeeploveLib
 *
 *  Created by System Administrator on 9/14/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <linux/module.h> 
#include <linux/workqueue.h> 
#include <linux/version.h>

// we can sleep in work's function 

#define TIME_INTERVAL_IN_MILLISEC  10000

#if LINUX_VERSION_CODE < KERNEL_VERSION (2,6,27)	
	struct work_struct *currentWork;
#else
	struct delayed_work *currentWork;
#endif

struct MyWork {
#if LINUX_VERSION_CODE < KERNEL_VERSION (2,6,27)	
	struct work_struct work;
#else	
	struct delayed_work work;
#endif
};

struct workqueue_struct *myWorkQueue = NULL;

//void myWorkFunc(void *data)
void myWorkFunc(struct delayed_work *workArg)
{
	//struct MyWork *newWork = data;
	struct MyWork *newWork = container_of(workArg, struct MyWork, work);
	
	printk("myWorkFunc %p\n", newWork);
	kfree(newWork);
	newWork = kmalloc(sizeof(struct MyWork), GFP_KERNEL);
#if LINUX_VERSION_CODE < KERNEL_VERSION (2,6,27)	
	INIT_WORK(&newWork->work, myWorkFunc, newWork);
#else
	INIT_DELAYED_WORK(&newWork->work, myWorkFunc);
#endif
	currentWork = &newWork->work;
	queue_delayed_work(myWorkQueue, &newWork->work, 
					   msecs_to_jiffies(TIME_INTERVAL_IN_MILLISEC) );
}


void createWorkQueue()
{
	myWorkQueue = create_workqueue("myWorkQueue");
	struct MyWork *newWork = kmalloc(sizeof(struct MyWork), GFP_KERNEL);
#if LINUX_VERSION_CODE < KERNEL_VERSION (2,6,27)	
	INIT_WORK(&newWork->work, myWorkFunc, newWork);
#else
	INIT_DELAYED_WORK(&newWork->work, myWorkFunc);
#endif
	currentWork = &newWork->work;
	queue_delayed_work(myWorkQueue, &newWork->work, 
					   msecs_to_jiffies(TIME_INTERVAL_IN_MILLISEC) );

}


static int hello_init(void) 
{ 
	printk(KERN_ALERT "Hello, world\n"); 
	createWorkQueue();
	
	return 0; 
} 


static void hello_exit(void) 
{ 
	printk(KERN_ALERT "Goodbye, cruel world\n"); 
	cancel_delayed_work(currentWork);
	flush_workqueue(myWorkQueue);
	destroy_workqueue(myWorkQueue);
} 

module_init(hello_init); 
module_exit(hello_exit); 

MODULE_LICENSE("GPL");

