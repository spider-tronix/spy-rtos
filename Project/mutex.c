#include <OS/tasks.h>
#include <OS/os.h>

void os_mutex_create(struct mutex *mut)
{

		os_start_critical();
		mut->lock = 1;// 1 -> indicates resource available
		os_end_critical();
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
		mut->old_prio = mut->owner_tcb->priority;// logic problem fixed
		os_end_critical();	
	}
	else
	{
		os_block(mut); // need to fixed
		if (current_tcb->priority < mut->owner_tcb->priority) // PIP implemented
		{		
			os_change_prio(mut->owner_tcb, current_tcb->priority);
		}
		os_end_critical();
	}
}

void os_mutex_signal(struct mutex *mut)
{
	os_start_critical();
	if(mut->owner_tcb == current_tcb)
	{
		mut->lock=1;
		os_change_prio(mut->owner_tcb, mut->old_prio);
	}
	os_end_critical();
}
