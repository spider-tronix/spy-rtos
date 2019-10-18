#ifndef BSP_H
#define BSP_H
#include <OS/os.h>
#define PERIPHERAL_BASE 0xE000E000
#define STCTRL_R (*((uint32_t*)(PERIPHERAL_BASE + 0x010)))
#define STRELOAD_R (*((uint32_t*)(PERIPHERAL_BASE + 0x014)))
#define STCURRENT_R (*((uint32_t*)(PERIPHERAL_BASE + 0x018)))
#define NVIC_PRI3_R (*((uint32_t*)(PERIPHERAL_BASE + 0x40C)))

extern void bsp_init(void);
extern void bsp_systick_init(void);

#endif