#include <OS/tasks.h>
#include <OS/os.h>
void os_scheduler()
{ 
	intr_alloc();
	os_start_critical();
	uint8_t high_priority;
	high_priority= os_get_highest_priority();
	new_high_tcb=os_tcb_lut[high_priority];
	if(current_tcb == new_high_tcb)
	{
		os_end_critical();
		return;
	}
	else if(current_tcb->task_state == RUNNING)
	{
		current_tcb->task_state = READY;
	}
	new_high_tcb->task_state = RUNNING;
	os_context_switch();
	os_end_critical();
}

void os_int_scheduler()
{
	intr_alloc();
	os_start_critical();
	int i;
	if(os_int_cntr > 1)
	{
		os_int_cntr--;
		os_end_critical();
		return;
	}
	else
	{
	   new_high_tcb = os_tcb_lut[os_get_highest_priority()];
     if(current_tcb == new_high_tcb)
	   {
			  os_int_cntr--;
		    os_end_critical();
		    return;
	   }
		 else if(current_tcb->task_state == RUNNING)
	   {
		    current_tcb->task_state = READY;
	   }
   	 new_high_tcb->task_state = RUNNING;
	   os_context_switch();
	   os_int_cntr--;
	   os_end_critical();
	}
}
