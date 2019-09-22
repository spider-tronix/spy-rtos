#ifndef OS_H
#define OS_H
#include <OS/Process.h>
extern uint8_t start_flag;
extern void context_switch(void);
extern void scheduler();
extern void os_init();
extern void os_first_task();
extern struct tcb *new_high_tcb;
extern struct tcb *current_tcb;
extern uint8_t os_get_highest_priority(uint32_t);
extern void os_start_critical();
extern void os_end_critical();
void os_start(void);
#endif