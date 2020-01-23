#include <OS/tasks.h>
#include <OS/os.h>

void os_stack_init(uint32_t **stack_base,void(*fun_ptr)(void *args),void *args)
{
	*(*stack_base)=0x01000000; //PSR
	*(*stack_base-1)=(uint32_t)*(fun_ptr);//RETURN ADD
	*(*stack_base-2)=0x14141414;//LR/R14
	*(*stack_base-3)=0x14141414;//R12
	*(*stack_base-4)=0x14141414;//R3
	*(*stack_base-5)=0x14141414;//R2
	*(*stack_base-6)=0x14141414;//R1
	*(*stack_base-7)=(uint32_t)args;//R0
	*(*stack_base-8)=0x14141414;//R11
	*(*stack_base-9)=0x14141414;//R10
	*(*stack_base-10)=0x14141414;//R9
	*(*stack_base-11)=0x14141414;//R8
	*(*stack_base-12)=0x14141414;//R7
	*(*stack_base-13)=0x14141414;//R6
	*(*stack_base-14)=0x14141414;//R5
	*(*stack_base-15)=0x14141414;//R4
	*stack_base = *stack_base-15;
}

void SysTick_Handler()
{
	intr_alloc();
	os_start_critical();
	if(os_sched_state == BLOCKED)
	{ 
		os_end_critical();
		return;
	}
	os_int_cntr++;
	os_clk_cntr++;
	os_end_critical();
	if(os_dly_list_head !=NULL)
	{
   	os_sem_signal(&os_dly_sem);
	}
	os_int_scheduler();
}
