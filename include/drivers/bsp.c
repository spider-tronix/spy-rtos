#include <drivers/bsp.h>
void bsp_init()
{
	bsp_systick_init();
}

void bsp_systick_init()
{
	STCTRL_R = 0;        
  STRELOAD_R = 500;
  STCURRENT_R = 0;      
  NVIC_PRI3_R = NVIC_PRI3_R|0x60000000;        
  STCTRL_R = 0x07;
}
