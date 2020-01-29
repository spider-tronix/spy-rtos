#include <OS/tasks.h>
#include <OS/os.h>

void os_mutex_create(struct mutex *mutex,uint8_t high_prio) // What does the high_prio represent,is the user supposed to give a priority as argument if yes what is that priority?
{

		os_start_critical();
		mut->lock = 1; // does 1 represents a free lock??
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
		/*check this logic for the following case
		TASK A HOLDS A MUTEX THEN
		1. A HIGH PRIORITY TASK B(TASK B > TASK A) REQUESTS THE MUTEX, BY PIP old_prio STORES THE OWNER TASKS PRIORITY AND THE PRIORITY OF OWNER TASK CHANGES
		2. NOW A TASK WITH EVEN HIGHER PRIORITY(TASK C >TASK B) COMES NOW ACCORDING TO THIS LOGIC THE ORIGINAL PRIORITY OF THE TASK WILL OVERWRITTEN
		*/
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
        os_change_prio(mut->owner_tcb, mut->old_prio);
        mut->pip = NULL; //??
    }
    os_end_critical();
}
