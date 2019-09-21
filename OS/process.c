#include <OS/Process.h>
#include <OS/Queues.h>
#include <OS/os.h>
void os_task_create(struct tcb *temp_tcb,void(*fun_ptr)(void *args),void *args,uint32_t *stack_base,uint32_t stack_size,uint32_t priority)
{
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
	
	os_end_critical();
}
void os_stack_init(uint32_t **stack_base,void(*fun_ptr)(void *args),void *args)
{
	*(*stack_base)=0x01000000;
	*(*stack_base-1)=(uint32_t)*(fun_ptr);
	*(*stack_base-2)=0x14141414;
	*(*stack_base-3)=0x14141414;
	*(*stack_base-4)=0x14141414;
	*(*stack_base-5)=0x14141414;
	*(*stack_base-6)=0x14141414;
	*(*stack_base-7)=0x14141414;
	*(*stack_base-8)=0x14141414;
	*(*stack_base-9)=0x14141414;
	*(*stack_base-10)=0x14141414;
	*(*stack_base-11)=0x14141414;
	*(*stack_base-12)=0x14141414;
	*(*stack_base-13)=0x14141414;
	*(*stack_base-14)=0x14141414;
	*(*stack_base-15)=0x14141414;
	*stack_base = *stack_base-15;
}

	