#include <OS/Process.h>
#include <OS/Queues.h>
#include <OS/os.h>
void scheduler()
{
	os_start_critical();
	uint8_t high_priority;
	high_priority= os_get_highest_priority(*os_ready_list_point);
	new_high_tcb=os_tcb_lut[high_priority];
	if(current_tcb == new_high_tcb)
	{
		os_end_critical();
		return;
	}
	context_switch();
	os_end_critical();
}