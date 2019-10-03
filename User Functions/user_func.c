#include <OS/os.h>
#include <OS/tasks.h>

/*void gpio_init()
{
	
	volatile uint32_t ui32Loop;
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;
	ui32Loop = SYSCTL_RCGC2_R;
  GPIO_PORTF_DIR_R = 0x0f;
  GPIO_PORTF_DEN_R = 0x0f;
	SYSCTL_RCGC2_R |= 0x00000020; // activate port F
  GPIO_PORTF_DIR_R |= 0x04;   // make PF2 output (PF2 built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x04;// disable alt funct on PF2
  GPIO_PORTF_DEN_R |= 0x04;   // enable digital I/O on PF2
                              // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;  
	NVIC_SYS_PRI3_R =(NVIC_SYS_PRI3_R&0xFF00FFFF)|0x00D00000; // priority 6	
//  NVIC_INT_CTRL_R = 0x10000000;
	
	
}*/


void user1(void)
{
	int a=0;
	long int i=0;
	for( ; i<25; i++)
	a = a+1;
	GPIO_PORTF_DATA_R = 0x08;
	for(i=0;i<50;i=i+2)
	a=a+2;
	scheduler();
}

void user2(void)
{
	int b=0,a=0;
	long int i=0;
for( ; i<50;i++)
 {
	a = a+1;
	b = a+2;
	GPIO_PORTF_DATA_R = 0x04; 
  }
}

void user3(void)
{
		int b=0,a=0;
	long int i=0;
for( ; i<500;i++)
 {
	a = a-1;
	b = a+2;
	GPIO_PORTF_DATA_R = 0x02; 
  }
	scheduler();
}

void idle(void)
{
	Systick_Handler();
	while(1)
	{
		GPIO_PORTF_DATA_R = 0x0e;
	}
}



