#include <OS/tasks.h>
#include <OS/Queues.h>
#include <OS/os.h>
void os_scheduler()
{
	os_start_critical();
	uint8_t high_priority;
	high_priority= os_get_highest_priority();
	new_high_tcb=os_tcb_lut[high_priority];
	if(current_tcb == new_high_tcb)
	{
		os_end_critical();
		return;
	}
	os_context_switch();
	os_end_critical();
}