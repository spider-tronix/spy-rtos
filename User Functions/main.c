#include <OS/tasks.h>
#include <OS/os.h>

void user1(void *args)
{
	int a=0;
	long int i=0;
	for( ; i<25; i++)
	a = a+1;
	for(i=0;i<50;i=i+2)
	a=a+2;
	os_scheduler();
}

void user2(void *args)
{
	int b=0,a=0;
	long int i=0;
for( ; i<50;i++)
 {
	a = a+1;
	b = a+2;
  }
}

void user3(void *args)
{
		int b=0,a=0;
	long int i=0;
for( ; i<500;i++)
 {
	a = a-1;
	b = a+2;
  }
	os_scheduler();
}

void idle(void *args)
{
	while(1)
	{
	}
}

uint32_t stack1[200];
uint32_t stack20[200];
uint32_t stack3[200];

struct tcb a1,a2,a3;

int main()
{
	os_init();
	struct tcb *temp1=&a1;
  struct tcb *temp2=&a2;
	struct tcb *temp3=&a3;
	uint32_t *stack_base1 = &stack1[199];
	uint32_t priority1 = 1;
	void (*user1_pt)(void*) = &user1;
	os_task_create(temp1,user1_pt,(void*)0,stack_base1,200,priority1);
	
/*		uint32_t stack2[100];
	uint32_t *stack_base2 = &stack2[99];
	uint32_t **stack_base2_1 = &stack_base2;
	uint32_t priority2 = 0;
	void (*user2_pt)(void) = &user2;
	os_task_create(user2_pt,stack_base2_1,100,priority2);
	*/
	uint32_t *stack_base3 = &stack3[99];
	uint32_t priority3 = 2;
	void (*user3_pt)(void*) = &user3;
	os_task_create(temp3,user3_pt,(void*)0,stack_base3,100,priority3);
	
	uint32_t *stack_base20 = &stack20[199];
	uint32_t priority20 = 20;
	void (*user20_pt)(void*) = &idle;
	os_task_create(temp2,user20_pt,(void*)0,stack_base20,200,priority20);
	os_start();
	return 0;
}
