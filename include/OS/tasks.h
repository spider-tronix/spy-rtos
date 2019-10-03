#ifndef TASKS_H
#define TASKS_H
#include <stdint.h>
/* 
    This header file is compiler dependent and is used to obtain fixed size datatypes
*/
#define NULL 0
#define READY 0
#define WAITING 1
#define RUNNING 2
#define BLOCKED 3
extern uint32_t os_ready_list[2];
extern struct tcb* os_tcb_lut[64];
struct tcb
{
	uint32_t *stack_base;
	uint32_t *task_args;
	struct tcb *next_tcb;
	struct tcb *prev_tcb;     
	uint32_t stack_size;
	uint32_t program_counter;
	uint8_t priority;
	uint8_t task_state;
	uint8_t task_id;
	uint8_t del_req;
};
extern void os_task_create(struct tcb *temp,void(*fun_ptr)(void *args),void *args,uint32_t *stack_base,uint32_t stack_size,uint32_t priority);
extern void os_stack_init(uint32_t **stack_base,void(*fun_ptr)(void *args),void *args);
#endif
