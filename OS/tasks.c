#include <OS/tasks.h>
#include <OS/os.h>

uint32_t os_ready_list[2];
struct tcb* os_tcb_lut[64];

uint8_t stack_free_list;
uint32_t *stack_base[8];

void os_task_create(struct tcb *temp_tcb,void(*fun_ptr)(void *args),void *args,uint32_t *stack_base,uint32_t stack_size,uint32_t priority)
{
	os_stack_init(&stack_base,fun_ptr,args);//stack intialized before tcb intialization.
	temp_tcb->stack_base = stack_base;
	temp_tcb->task_args = args;
	temp_tcb->next_tcb = NULL;
	temp_tcb->prev_tcb = NULL;
	temp_tcb->stack_size = stack_size;
	temp_tcb->program_counter = (uint32_t)fun_ptr;
	temp_tcb->priority = priority;
	temp_tcb->task_state = READY;
	temp_tcb->task_id = 1;
	temp_tcb->del_req = 0;
	
	os_start_critical();
	os_add_ready_list(temp_tcb);
	if(os_sched_state == RUNNING)
	{
		os_scheduler();
		os_end_critical();
	}
	else
	{
	  os_end_critical();
	}
}

void os_task_delete(uint32_t priority)
{
	struct tcb *temp_tcb;
	os_start_critical();
	temp_tcb = os_tcb_lut[priority];
	if(temp_tcb != NULL)
	{
		os_remove_ready_list(temp_tcb);
	}
	temp_tcb -> task_state = READY;
	//scheduler switching prevention (lock nesting)??
	os_end_critical();
	os_dummy();
	//asm { NOP } // os_dummy
	os_start_critical();
	os_tcb_lut[priority] = (void *)0;
	
	/*
	if(temp_tcb -> next_tcb == NULL)
	{
		temp_tcb -> next_tcb -> prev_tcb = NULL; 
		// temp_tcb -> next_tcb ?
	}
	else
	{
		temp_tcb -> next_tcb -> prev_tcb = temp_tcb -> prev_tcb; 
		temp_tcb -> prev_tcb -> next_tcb = temp_tcb -> next_tcb;
	}	
	*/
	
	os_end_critical();
	os_scheduler();
}