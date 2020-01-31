#include <OS/tasks.h>
#include <OS/os.h>

void os_mutex_create(struct mutex *mut)
{

		os_start_critical();
		mut->lock = 1;// 1 -> indicates resource available - ok
		os_end_critical(); // extend the critical section till the end of the function
		mut->old_prio = NULL;
		mut->mut_ptr_head = NULL;
		mut->mut_ptr_tail = NULL;
		mut->owner_tcb = NULL;
}

void os_mutex_wait(struct mutex *mut)
{
	os_start_critical();
	if(mut->lock)
	{
		mut->lock = 0; // locked
		mut->owner_tcb = current_tcb;
		mut->old_prio = mut->owner_tcb->priority;// logic problem fixed - ok
		os_end_critical();	
	}
	else
	{
		if (current_tcb->priority < mut->owner_tcb->priority) // PIP implemented -ok
		{		
			os_change_prio(mut->owner_tcb, current_tcb->priority);
		}
		os_end_critical();
		os_block(mut);
	}
}

void os_mutex_signal(struct mutex *mut)
{
	os_start_critical();
	if(mut->owner_tcb == current_tcb)
	{
		mut->lock=1;
		os_change_prio(mut->owner_tcb, mut->old_prio);
		os_release(mut);
	}
	os_end_critical();
	os_scheduler();
}
