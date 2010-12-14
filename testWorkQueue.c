testWorkQueue.c
code
linux driver test workqueue

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

// (1)we can sleep in work's function 
// (2)we can use queue_work to add work to queue.
//	  the works in queue are executed by sequence 

char isRemoveDriver = 0;


#define TIME_INTERVAL_IN_MILLISEC  10000

#if LINUX_VERSION_CODE < KERNEL_VERSION (2,6,27)	
	struct work_struct *currentWork;
#else
	#ifdef USE_DELAY
		struct delayed_work *currentWork;
	#else
		struct work_struct *currentWork;
	#endif
#endif

struct MyWork {
#if LINUX_VERSION_CODE < KERNEL_VERSION (2,6,27)	
	struct work_struct work;
#else	
	#ifdef USE_DELAY
		struct delayed_work work;
	#else
		struct work_struct work;
	#endif
#endif
};

struct workqueue_struct *myWorkQueue = NULL;

#if LINUX_VERSION_CODE < KERNEL_VERSION (2,6,27)	
void myWorkFunc(void *data)
#else
#ifdef USE_DELAY
void myWorkFunc(struct delayed_work *workArg)
#else
void myWorkFunc(struct work_struct *workArg)
#endif
#endif
{
#if LINUX_VERSION_CODE < KERNEL_VERSION (2,6,27)	
	struct MyWork *newWork = data;
#else	
	struct MyWork *newWork = container_of(workArg, struct MyWork, work);
#endif
	
	printk("myWorkFunc %p\n", newWork);
	kfree(newWork);
	
#ifndef USE_DELAY
	if(isRemoveDriver)
	{
		return;
	}
#endif
	
	newWork = kmalloc(sizeof(struct MyWork), GFP_KERNEL);
#if LINUX_VERSION_CODE < KERNEL_VERSION (2,6,27)	
	INIT_WORK(&newWork->work, myWorkFunc, newWork);
#else
	#ifdef USE_DELAY
		INIT_DELAYED_WORK(&newWork->work, myWorkFunc);
	#else
		INIT_WORK(&newWork->work, myWorkFunc);
	#endif	
#endif
	currentWork = &newWork->work;
#ifdef USE_DELAY
	queue_delayed_work(myWorkQueue, &newWork->work, 
					   msecs_to_jiffies(TIME_INTERVAL_IN_MILLISEC) );
#else
	queue_work(myWorkQueue, &newWork->work);
#endif
}


void createWorkQueue()
{
	myWorkQueue = create_workqueue("myWorkQueue");
	struct MyWork *newWork = kmalloc(sizeof(struct MyWork), GFP_KERNEL);
#if LINUX_VERSION_CODE < KERNEL_VERSION (2,6,27)	
	INIT_WORK(&newWork->work, myWorkFunc, newWork);
#else
	#ifdef USE_DELAY
		INIT_DELAYED_WORK(&newWork->work, myWorkFunc);
	#else
		INIT_WORK(&newWork->work, myWorkFunc);
	#endif	
#endif
	currentWork = &newWork->work;
#ifdef USE_DELAY
	queue_delayed_work(myWorkQueue, &newWork->work, 
					   msecs_to_jiffies(TIME_INTERVAL_IN_MILLISEC) );
#else
	queue_work(myWorkQueue, &newWork->work);
#endif
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
#ifdef USE_DELAY
	cancel_delayed_work(currentWork);
#else
	isRemoveDriver = 1;
#endif
	flush_workqueue(myWorkQueue);
	destroy_workqueue(myWorkQueue);
} 

module_init(hello_init); 
module_exit(hello_exit); 

MODULE_LICENSE("GPL");

