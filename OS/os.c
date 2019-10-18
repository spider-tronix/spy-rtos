#include <OS/os.h>
#include <OS/tasks.h>
#include <drivers/bsp.h>
uint8_t os_sched_state;
uint32_t os_int_cntr;
struct tcb *current_tcb;
struct tcb *new_high_tcb;
struct semaphore os_dly_sem;
struct dly_data *os_dly_list;
void os_init()
{
	int i;
	bsp_init();
	os_sched_state = BLOCKED;
  current_tcb = NULL;
  new_high_tcb =NULL;
	os_int_cntr = 0;
	os_dly_list_head = NULL;
	os_dly_list_tail = NULL;
	os_ready_list[0] = 0 ;
	os_ready_list[1] = 0 ;
  for(i=0;i<63;i++)
	{
		
		os_tcb_lut[i] = NULL;
	}
}
void os_start()
{
	new_high_tcb=os_tcb_lut[os_get_highest_priority()];
	os_sched_state = RUNNING;
	os_first_task();
}

void os_add_ready_list(struct tcb *temp_tcb)
{
	temp_tcb->task_state = READY;
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

void os_remove_ready_list(struct tcb *temp_tcb)
{
	if(temp_tcb->priority <=31)
	{
	  *(os_ready_list) &= ~(1<<(31-temp_tcb->priority));
    os_tcb_lut[temp_tcb->priority] = NULL;	
	}
	else
	{
		*(os_ready_list+1) &= ~(1<<(63-temp_tcb->priority));
    os_tcb_lut[temp_tcb->priority] = NULL;
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
