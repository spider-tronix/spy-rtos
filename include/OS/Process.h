#ifndef PROCESS_H
#define PROCESS_H
#include <stdint.h>
__packed struct tcb
{
	uint32_t *stack_base;
	struct tcb *next;
	struct tcb *prev;
	uint8_t priority;
	uint32_t process_state;     
	uint32_t stack_size;
	uint32_t program_counter;
};
void os_task_create(struct tcb *temp,void(*fun_ptr)(),uint32_t **stack_base,uint32_t stack_size,uint32_t priority);
void os_stack_init(struct tcb *temp,uint32_t **stack_base,void(*fun_ptr)());
#endif