#ifndef OS_H
#define OS_H
#define NULL (void*)(0)
#define READY 0
#define WAITING 1
#define RUNNING 2
#define BLOCKED 3
#include <stdint.h>
extern uint8_t start_flag;
extern void context_switch(void);
extern void scheduler();
extern void os_init();
extern void os_first_task();
extern struct tcb *new_high_tcb;
extern struct tcb *current_tcb;
//extern uint32_t counter;
extern void start_critical();
extern void end_critical();
void os_start(void);
#endif