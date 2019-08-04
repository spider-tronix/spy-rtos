#include <OS/Process.h>
#include <OS/Queues.h>
#include <OS/os.h>
void os_task_create(struct tcb *temp,void(*fun_ptr)(),uint32_t **stack_base1,uint32_t stack_size,uint32_t priority)
{
	temp->next=NULL;
	temp->prev=NULL;
	temp->priority=priority;
	temp->process_state=READY;
	temp->stack_base=*stack_base1;
	temp->stack_size=stack_size;
	temp->program_counter=(uint32_t)fun_ptr;
	os_stack_init(temp,stack_base1,fun_ptr);
	start_critical();
	add_ready_queue(temp);
	end_critical();
}
void os_stack_init(struct tcb *temp,uint32_t **stack_base,void(*fun_ptr)())
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
	*stack_base=*stack_base-15;
	temp->stack_base=*stack_base;
}

	