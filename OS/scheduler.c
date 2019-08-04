#include <OS/Process.h>
#include <OS/Queues.h>
#include <OS/os.h>
void scheduler()
{
	start_critical();
	new_high_tcb=ready_queue_head;
	delete_head(&ready_queue_head);
	context_switch();
	end_critical();
}