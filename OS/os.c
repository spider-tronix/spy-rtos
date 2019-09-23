#include <OS/os.h>
#include <OS/Queues.h>
#include <OS/tasks.h>
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

void os_add_ready_list(struct tcb *temp_tcb)
{
	if(temp_tcb->priority <=31)
	{
	  *(os_ready_list) |= (1<<(31-temp_tcb->priority));
    os_tcb_lut[temp_tcb->priority] = temp_tcb;	
	}
	else
	{
		*(os_ready_list+1) |= (1<<(63-temp_tcb->priority));
    os_tcb_lut[temp_tcb->priority] = temp_tcb;
	}
}

uint8_t os_get_highest_priority()
{
	if(*os_ready_list!=0)
	{
		return os_leading_zeros(*os_ready_list);
	}
	else
	{
		return os_leading_zeros(*(os_ready_list+ 1));
	}
}
	