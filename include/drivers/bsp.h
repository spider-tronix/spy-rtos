#ifndef BSP_H
#define BSP_H
#include <OS/os.h>

extern struct semaphore gpioc4_sem,gpioc5_sem,gpioc6_sem,gpioc7_sem;
//extern struct semaphore gpiof0_sem;
//extern int paddle_A,paddle_B;

#define SYSCTL_BASE 0x400FE000
#define PERIPHERAL_BASE 0xE000E000
#define STCTRL_R (*((uint32_t*)(PERIPHERAL_BASE + 0x010)))
#define STRELOAD_R (*((uint32_t*)(PERIPHERAL_BASE + 0x014)))
#define STCURRENT_R (*((uint32_t*)(PERIPHERAL_BASE + 0x018)))
#define NVIC_PRI3_R (*((uint32_t*)(PERIPHERAL_BASE + 0x40C)))
#define RCGC2_R (*((uint32_t*)(SYSCTL_BASE + 0x108)))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // Port F Clock Gating Control
#define GPIO_PORTF_DIR_R        (*((volatile uint32_t *)0x40025400))
#define GPIO_PORTF_DEN_R        (*((volatile uint32_t *)0x4002551C))
#define GPIO_PORTF_AFSEL_R      (*((volatile uint32_t *)0x40025420))	
#define GPIO_PORTF_PCTL_R       (*((volatile uint32_t *)0x4002552C))
#define GPIO_PORTF_AMSEL_R      (*((volatile uint32_t *)0x40025528))
#define GPIO_PORTF_DATA_R       (*((volatile uint32_t *)0x400253FC))
#define GPIO_PORTF_LOCK_R       (*((volatile uint32_t *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile uint32_t *)0x40025524))
#define GPIO_PORTF_PUR_R        (*((volatile uint32_t *)0x40025510))	
#define GPIO_PORTF_IS_R         (*((volatile uint32_t *)0x40025404))
#define GPIO_PORTF_IBE_R        (*((volatile uint32_t *)0x40025408))
#define GPIO_PORTF_IEV_R        (*((volatile uint32_t *)0x4002540C))
#define GPIO_PORTF_IM_R         (*((volatile uint32_t *)0x40025410))
#define GPIO_PORTF_RIS_R        (*((volatile uint32_t *)0x40025414))
#define GPIO_PORTF_ICR_R        (*((volatile uint32_t *)0x4002541C))
	
#define GPIO_PORTC_LOCK_R       (*((volatile uint32_t *)0x40006520))
#define GPIO_PORTC_CR_R         (*((volatile uint32_t *)0x40006524))
#define GPIO_PORTC_DIR_R        (*((volatile uint32_t *)0x40006400))	
#define GPIO_PORTC_PUR_R        (*((volatile uint32_t *)0x40006510))
#define GPIO_PORTC_DEN_R        (*((volatile uint32_t *)0x4000651C))
#define GPIO_PORTC_IS_R         (*((volatile uint32_t *)0x40006404))
#define GPIO_PORTC_IBE_R        (*((volatile uint32_t *)0x40006408))
#define GPIO_PORTC_IEV_R        (*((volatile uint32_t *)0x4000640C))
#define GPIO_PORTC_IM_R         (*((volatile uint32_t *)0x40006410))
#define GPIO_PORTC_RIS_R        (*((volatile uint32_t *)0x40006414))
#define GPIO_PORTC_ICR_R        (*((volatile uint32_t *)0x4000641C))
	
#define NVIC_PRI7_R             (*((volatile uint32_t *)0xE000E41C))
#define NVIC_PRI0_R             (*((volatile uint32_t *)0xE000E400))
#define NVIC_EN0_R              (*((volatile uint32_t *)0xE000E100))

extern void bsp_init(void);
extern void bsp_systick_init(void);
extern void tm4c_gpiof_init(void);
extern void tm4c_gpioc_init(void);
#endif
