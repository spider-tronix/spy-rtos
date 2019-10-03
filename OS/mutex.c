#include <OS/tasks.h>
#include <OS/os.h>
void os_mutex_create(struct mutex *mut)
{
	mut->lock = 0;
	mut->mut_ptr_head = NULL;
	mut->mut_ptr_tail = NULL;
	mut->owner_tcb = NULL;
}

void os_mutex_lock(struct mutex *mut)
{
	os_start_critical();
	if (mut->lock == 1)
	{
		os_block(mut);
		if (mut->owner_tcb->priority > current_tcb->priority)
		{
			os_change_prio(current_tcb, mut->owner_tcb->priority);
		}
		os_end_critical();
		os_scheduler();
	}
	else
	{
		mut->lock = 1;
		mut->owner_tcb = current_tcb;
		mut->owner_tcb->priority = mut->highest_prio;
		os_end_critical();
	}
}

void os_mutex_release(struct mutex *mut)
{
	os_start_critical();
	if (mut->owner_tcb == current_tcb)
	{
		mut->lock = 0;
	}
}