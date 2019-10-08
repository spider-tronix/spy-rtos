#ifndef OS_CPU
#define OS_CPU
#include <OS/tasks.h>
extern uint32_t int_disable();
extern void int_enable(uint32_t);

#define intr_alloc() uint32_t psr = 0
#define os_start_critical() do{ psr = int_disable();}while(0)
#define os_end_critical() do{ int_enable(psr);}while(0)

#endif