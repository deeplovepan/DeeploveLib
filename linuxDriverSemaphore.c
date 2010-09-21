#include <linux/module.h> 
#include <linux/workqueue.h> 
#include <linux/delay.h> 

// we can sleep in critical section of semaphore

struct MyWork {
	struct work_struct work;
	int index;
};

struct workqueue_struct *myWorkQueue = NULL;
struct semaphore sem; 

void myWorkFunc(void *data)
{
	struct MyWork *newWork = data;
		
	printk("myWorkFunc%d before count %d\n", newWork->index, sem.count);
	down_interruptible(&sem);
	printk("myWorkFunc%d enter count %d\n", newWork->index, sem.count);
	msleep(10000);
	up(&sem);
	printk("myWorkFunc%d after count %d\n", newWork->index, sem.count);
	
	kfree(newWork);


}


void createWorkQueue(int index)
{
	myWorkQueue = create_workqueue("myWorkQueue");
	struct MyWork *newWork = kmalloc(sizeof(struct MyWork), GFP_KERNEL);
	newWork->index = index;
	INIT_WORK(&newWork->work, myWorkFunc, newWork);
	queue_delayed_work(myWorkQueue, &newWork->work, 
					   msecs_to_jiffies(1000) );
	
}


static int hello_init(void) 
{ 
	printk(KERN_ALERT "Hello, world\n"); 
	
	init_MUTEX(&sem);

	createWorkQueue(1);
	createWorkQueue(2);
	
	printk("hello_init before count %d\n", sem.count);
	down_interruptible(&sem);
	printk("hello_init enter count %d\n", sem.count);
	msleep(10000);
	up(&sem);
	printk("hello_init after count %d\n", sem.count);

	return 0; 
} 


static void hello_exit(void) 
{ 
	printk(KERN_ALERT "Goodbye, cruel world\n"); 
	flush_workqueue(myWorkQueue);
	destroy_workqueue(myWorkQueue);

} 

module_init(hello_init); 
module_exit(hello_exit); 

MODULE_LICENSE("GPL");

