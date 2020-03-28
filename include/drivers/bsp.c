#include <drivers/bsp.h>
void bsp_init()
{
	//RCGC2_R = SYSCTL_RCGC2_GPIOF;
	//GPIO_PORTF_DIR_R = 0x0f;
  //GPIO_PORTF_DEN_R = 0x0f;
	//RCGC2_R |= 0x00000020; // activate port F
  //GPIO_PORTF_DIR_R |= 0x04;   // make PF2 output (PF2 built-in LED)
  //GPIO_PORTF_AFSEL_R &= ~0x04;// disable alt funct on PF2
  //GPIO_PORTF_DEN_R |= 0x04;   // enable digital I/O on PF2
                              // configure PF2 as GPIO
  //GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000000;
  //GPIO_PORTF_AMSEL_R = 0;  
	//bsp_systick_init();
}

void tm4c_gpiof_init()
{
	RCGC2_R |= 0x20; // (a) activate clock for Port F
	GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock GPIO Port F
	GPIO_PORTF_CR_R = 0xFF; // allow changes to PF4-0
	GPIO_PORTF_DIR_R = 0x06; // (c) make PF4,PF0 in and PF1 is out
	GPIO_PORTF_DEN_R |= 0x77; // enable digital I/O on PF4,PF0, PF1
	GPIO_PORTF_PUR_R |= 0x71; // pullups on PF4,PF0
	GPIO_PORTF_IS_R &= ~0x71; // (d) PF4,PF0 are edge-sensitive
	GPIO_PORTF_IBE_R &= ~0x71; // PF4,PF0 are not both edges
	GPIO_PORTF_IEV_R &= ~0x71; // PF4,PF0 falling edge event
	GPIO_PORTF_ICR_R = 0x71; // (e) clear flags
	GPIO_PORTF_IM_R |= 0x71; // (f) arm interrupt on PF4,PF0
	NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
	NVIC_EN0_R |= 0x40000000; // (h) enable interrupt 30 in NVIC
}

void tm4c_gpioc_init()
{
	RCGC2_R |= 0x04; 
	GPIO_PORTC_LOCK_R = 0x4C4F434B;
	GPIO_PORTC_CR_R = 0xFF;
	GPIO_PORTC_DIR_R = 0x00; // (c) make PF4,PF0 in and PF1 is out
	GPIO_PORTC_DEN_R |= 0xF0; // enable digital I/O on PF4,PF0, PF1
	GPIO_PORTC_PUR_R |= 0xF0; // pullups on PF4,PF0
	GPIO_PORTC_IS_R &= ~0xF0; // (d) PF4,PF0 are edge-sensitive
	GPIO_PORTC_IBE_R &= ~0xF0; // PF4,PF0 are not both edges
	GPIO_PORTC_IEV_R &= ~0xF0; // PF4,PF0 falling edge event
	GPIO_PORTC_ICR_R = 0xF0; // (e) clear flags
	GPIO_PORTC_IM_R |= 0xF0; // (f) arm interrupt on PF4,PF0
	NVIC_PRI0_R = (NVIC_PRI0_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
	NVIC_EN0_R |= 0x00000004; // (h) enable interrupt 30 in NVIC
}

void bsp_systick_init()
{
	STCTRL_R = 0;        
  STRELOAD_R = 500;
  STCURRENT_R = 0;      
  NVIC_PRI3_R = NVIC_PRI3_R|0x60000000;        
  STCTRL_R = 0x07;
}
