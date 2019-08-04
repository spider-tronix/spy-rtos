#include <OS/os.h>
#include <OS/Queues.h>
uint8_t start_flag=0;
struct tcb *current_tcb = NULL;
struct tcb *new_high_tcb = NULL;
void os_start()
{
	new_high_tcb=ready_queue_head;
	delete_head(&ready_queue_head);
	start_flag=1;
	os_first_task();
}