#include <OS/tasks.h>
#include <OS/os.h>

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
