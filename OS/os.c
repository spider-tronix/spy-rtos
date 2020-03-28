#include <OS/os.h>
#include <OS/tasks.h>

uint8_t os_sched_state;
uint32_t os_int_cntr;
uint32_t os_clk_cntr;
struct tcb os_dly_tcb;
uint32_t os_dly_stack[200];
struct tcb *current_tcb;
struct tcb *new_high_tcb;
struct semaphore os_dly_sem;
struct tcb *os_dly_list_head;
struct tcb *os_dly_list_tail;
void os_init()
{
	int i;
	bsp_init();
	os_sched_state = BLOCKED;
  current_tcb = NULL;
  new_high_tcb =NULL;
	os_int_cntr = 0;
	os_clk_cntr = 0;
	os_dly_list_head = NULL;
	os_dly_list_tail = NULL;
	os_ready_list[0] = 0 ;
	os_ready_list[1] = 0 ;
	os_sem_create(&os_dly_sem,0);
	
  for(i=0;i<63;i++)
	{
		
		os_tcb_lut[i] = NULL;
	}
	os_task_create(&os_dly_tcb,&os_dly_update,(void*)0,&os_dly_stack[199],200,6);
}
void os_start()
{
	new_high_tcb=os_tcb_lut[os_get_highest_priority()];
	os_sched_state = RUNNING;
	os_first_task();
}

void os_add_ready(struct tcb *temp_tcb)
{
				/*if(temp_tcb->priority == 1)
	   {int i;
			 GPIO_PORTF_DATA_R = 0x02;
			 for(i=0;i<500000;i++);
	   }
	 else if(temp_tcb->priority == 2)
	 {
		 int i;
		 GPIO_PORTF_DATA_R = 0x04;
		 for(i=0;i<500000;i++);
	 }*/
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
