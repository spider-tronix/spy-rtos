#ifndef OS_H
#define OS_H
#include <OS/tasks.h>
extern uint8_t os_sched_state;
extern void os_context_switch(void);
extern void os_scheduler();
extern void os_init();
extern void os_first_task();
extern struct tcb *new_high_tcb;
extern struct tcb *current_tcb;
extern uint8_t os_leading_zeros(uint32_t);
extern uint8_t os_get_highest_priority();
extern void os_add_ready_list(struct tcb *temp);
extern void os_start_critical();
extern void os_end_critical();
void os_start(void);
#endif