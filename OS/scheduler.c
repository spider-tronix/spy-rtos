#include <OS/tasks.h>
#include <OS/os.h>
void os_scheduler()
{
	os_start_critical();
	os_remove_ready_list(current_tcb);
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
