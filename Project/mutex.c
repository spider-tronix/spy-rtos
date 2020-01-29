#include <OS/tasks.h>
#include <OS/os.h>

void os_mutex_create(struct mutex *mut,uint8_t high_prio)
{

		os_start_critical();
		mut->lock = 1;
		os_end_critical();
		mut->highest_prio = high_prio;
		mut->old_prio = NULL;
		mut->mut_ptr_head = NULL;
		mut->mut_ptr_tail = NULL;
		mut->owner_tcb = NULL;
}

void os_mutex_wait(struct mutex *mut)
{
	os_start_critical();
	if(!mut->lock)
	{
		mut->lock = 1;
		mut->owner_tcb = current_tcb;
		os_end_critical();	
	}
	else
	{
		os_block(mut);
		if (current_tcb->priority < mut->owner_tcb->priority) // current_tcb prority more than owner implies next is current_tcb is the s
		{
			mut->old_prio = mut->owner_tcb->priority;
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
		mut->lock=0;
		if(mut->old_prio!=NULL)
		{
			os_change_prio(mut->owner_tcb, mut->old_prio);
			mut->old_prio = NULL;
		}
	}
	os_end_critical();
}
