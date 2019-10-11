#include <drivers/bsp.h>
void bsp_init()
{
	bsp_systick_init();
}

void bsp_systick_init()
{
	STCTRL = 0;        
  STRELOAD = 24000;
  STCURRENT = 0;      
  NVIC_PRI3_R = NVIC_PRI3_R|0x60000000;        
  STCTRL = 0x07;
}