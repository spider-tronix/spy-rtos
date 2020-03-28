#include <OS/tasks.h>
#include <OS/os.h>

uint32_t os_ready_list[2];
struct tcb* os_tcb_lut[64];
void os_task_create(struct tcb *temp_tcb,void(*fun_ptr)(void *args),void *args,uint32_t *stack_base,uint32_t stack_size,uint32_t priority)
{
	intr_alloc();
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
	os_stack_init(&temp_tcb->stack_base,fun_ptr,args);
	os_start_critical();
	os_add_ready(temp_tcb);
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
