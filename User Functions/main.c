#include <OS/tasks.h>
#include <OS/os.h>
#include <OS/Nokia5110.h>

struct semaphore gpioc4_sem,gpioc5_sem,gpioc6_sem,gpioc7_sem;

int paddle_A=0,paddle_B=0;

void paddle_A_inc(void *args)
{
	int i;
	intr_alloc();
	while(1)
	{
		//GPIO_PORTF_DATA_R = 0x08;
		//for(i=0;i<5000000;i++);
		os_sem_wait(&gpioc4_sem);
		
		Nokia5110_paddleA_clear(paddle_A);
		os_start_critical();
		paddle_A++;
		if(paddle_A >= 8)
			paddle_A =8;
		Nokia5110_paddleA(paddle_A);
		os_end_critical();
		//for(i=0;i<500;i++);
		//Nokia5110_Ball(0,0);
	}
}

void paddle_A_dec(void *args)
{
	int i;
	intr_alloc();
	while(1)
	{
		//GPIO_PORTF_DATA_R = 0x00;
		//for(i=0;i<5000000;i++);
		os_sem_wait(&gpioc5_sem);
		Nokia5110_paddleA_clear(paddle_A);
		os_start_critical();
		paddle_A--;
		if(paddle_A <= 0)
			paddle_A =0;
		Nokia5110_paddleA(paddle_A);
		os_end_critical();
		//GPIO_PORTF_DATA_R = 0x02;
		//for(i=0;i<500;i++);
	}
}

void paddle_B_inc(void *args)
{
	int i;
	intr_alloc();
	//os_sem_create(&gpiof0_sem,0);
	while(1)
	{
		//GPIO_PORTF_DATA_R = 0x00;
		//for(i=0;i<5000000;i++);
		os_sem_wait(&gpioc6_sem);
		
		Nokia5110_paddleB_clear(paddle_B);
		os_start_critical();
		paddle_B++;
		if(paddle_B >= 8)
			paddle_B =8;
		Nokia5110_paddleB(paddle_B);
		os_end_critical();
		//GPIO_PORTF_DATA_R = 0x02;
		//for(i=0;i<500;i++);
	}
}

void paddle_B_dec(void *args)
{
	int i;
	intr_alloc();
	//os_sem_create(&gpiof0_sem,0);
	while(1)
	{
		//GPIO_PORTF_DATA_R = 0x00;
		//for(i=0;i<5000000;i++);
		os_sem_wait(&gpioc7_sem);

		Nokia5110_paddleB_clear(paddle_B);
		os_start_critical();
		paddle_B--;
		if(paddle_B <= 0)
			paddle_B =0;
		Nokia5110_paddleB(paddle_B);
		os_end_critical();
		//GPIO_PORTF_DATA_R = 0x02;
		//for(i=0;i<500;i++);
	}
}

void idle(void *args)
{
	while(1)
	{
		//GPIO_PORTF_DATA_R = 0x02;
	}
}


void screen_update(void *args)
{
	int ball_x =5,ball_y =3;
	int ball_dx =1,ball_dy = 1;
	int score_A=48 ,score_B =48;
	Nokia5110_paddleA(0);
	Nokia5110_paddleB(5);
	while(1)
	{
		Nokia5110_Ball_clear(ball_x,ball_y);
		ball_x = ball_x + ball_dx;
		ball_y = ball_y + ball_dy;
		if(ball_y>=4 && ball_x>=paddle_B && ball_x<= paddle_B+3)
		{
			ball_y = 4;
			ball_dy = -1;
		}
		else if(ball_y<=1 && ball_x>=paddle_A && ball_x<= paddle_A+3)
		{
			ball_y = 1;
			ball_dy = 1;
		}
		else if(ball_y ==5 || ball_y ==0)
		{
			if(ball_y)
				score_A++;
			else 
				score_B++;
			
			Nokia5110_Clear();
			Nokia5110_Score(score_A,score_B);
			os_time_dly(100000);
			Nokia5110_Clear();
			
			Nokia5110_paddleA(0);
			paddle_A=0;
			Nokia5110_paddleB(5);	
			paddle_B=5;
			
			ball_x =5;
			ball_y =3;
			//for(int j=0;j<5500000;j++);
				//some delay				
		}
		else if(score_A >9+48 || score_B>9+48 )
		{
			Nokia5110_Clear();
			break;
		}
		if(ball_x>11) // edge reflection
		{
			ball_x=11;
			ball_dx = -1;
		}
		if(ball_x <0)
		{
			ball_x=0;
			ball_dx = 1;
		}
		
		Nokia5110_Ball(ball_x,ball_y);
		os_time_dly(50000);	//some delay				
	}
}

uint32_t screen_update_stack[200];
uint32_t paddleA_inc_stack[200];
uint32_t paddleA_dec_stack[200];
uint32_t paddleB_inc_stack[200];
uint32_t paddleB_dec_stack[200];
uint32_t stack20[200];

struct tcb a1,a2,a3,a4,a5,a6;

int main()
{	
	os_init();
	
	tm4c_gpiof_init();
	tm4c_gpioc_init();
	bsp_systick_init();
	
	Nokia5110_Init();
	Nokia5110_Clear();
	
	os_sem_create(&gpioc4_sem,0);
	os_sem_create(&gpioc5_sem,0);
	os_sem_create(&gpioc6_sem,0);
	os_sem_create(&gpioc7_sem,0);
		
	struct tcb *screen_update_tcb=&a6;
	struct tcb *paddleA_inc_tcb=&a1;
  struct tcb *paddleA_dec_tcb=&a2;
	struct tcb *paddleB_inc_tcb=&a3;
	struct tcb *paddleB_dec_tcb=&a4;
	struct tcb *temp2=&a5;

	uint32_t *stack_base0 = &screen_update_stack[199];
	uint32_t priority0 = 5;
	void (*screen_update_pt)(void*) = &screen_update;
	os_task_create(screen_update_tcb,screen_update_pt,(void*)0,stack_base0,200,priority0);
	
	uint32_t *stack_base1 = &paddleA_inc_stack[199];
	uint32_t priority1 = 1;
	void (*paddle_A_inc_pt)(void*) = &paddle_A_inc;
	os_task_create(paddleA_inc_tcb,paddle_A_inc_pt,(void*)0,stack_base1,200,priority1);
		
	uint32_t *stack_base2 = &paddleA_dec_stack[199];
	uint32_t priority2 = 2;
	void (*paddle_A_dec_pt)(void*) = &paddle_A_dec;
	os_task_create(paddleA_dec_tcb,paddle_A_dec_pt,(void*)0,stack_base2,200,priority2);
	
	uint32_t *stack_base3 = &paddleB_inc_stack[199];
	uint32_t priority3 = 3;
	void (*paddle_B_inc_pt)(void*) = &paddle_B_inc;
	os_task_create(paddleB_inc_tcb,paddle_B_inc_pt,(void*)0,stack_base3,200,priority3);
	
	uint32_t *stack_base4 = &paddleB_dec_stack[199];
	uint32_t priority4 = 4;
	void (*paddle_B_dec_pt)(void*) = &paddle_B_dec;
	os_task_create(paddleB_dec_tcb,paddle_B_dec_pt,(void*)0,stack_base4,200,priority4);
	
	uint32_t *stack_base20 = &stack20[199];
	uint32_t priority20 = 20;
	void (*user20_pt)(void*) = &idle;
	os_task_create(temp2,user20_pt,(void*)0,stack_base20,200,priority20);
	
	os_start();
	
	return 0; 
}
