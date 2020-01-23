#include <OS/tasks.h>
#include <OS/os.h>

void os_mutex_create(struct mutex *mutex,uint8_t l_prio)
{

		os_start_critical();
		mutex->lock = 1;
		os_end_critical();
		//mutex->highest_prio = l_prio;
		mutex->mut_ptr_head = NULL;
		mutex->mut_ptr_tail = NULL;
		mutex->owner_tcb = NULL;
}

void os_mutex_wait(struct mutex *mut)
{
	os_start_critical();
	if(mut->lock==0)
	{
		//os_block(mut);
		os_end_critical();	
	  os_scheduler();
	}
	else
	{
		os_end_critical();
	}
}