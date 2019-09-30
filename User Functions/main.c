#include <OS/tasks.h>
#include <OS/os.h>
#include <OS/Queues.h>
#include <gpio.h>
uint32_t stack1[200];
uint32_t stack20[200];
uint32_t stack3[200];

struct tcb a1,a2,a3;

int main()
{
	//void os_task_create(void(*fun_ptr)(),uint32_t *stack_base,uint32_t stack_size,uint32_t priority);
	
	struct tcb *temp1=&a1;
  struct tcb *temp2=&a2;
	struct tcb *temp3=&a3;
	uint32_t *stack_base1 = &stack1[199];
		uint32_t **stack_base1_0 = &stack_base1;
	uint32_t priority1 = 1;
	void (*user1_pt)(void) = &user1;
	os_task_create(temp1,user1_pt,stack_base1_0,200,priority1);
	
/*		uint32_t stack2[100];
	uint32_t *stack_base2 = &stack2[99];
	uint32_t **stack_base2_1 = &stack_base2;
	uint32_t priority2 = 0;
	void (*user2_pt)(void) = &user2;
	os_task_create(user2_pt,stack_base2_1,100,priority2);
	*/
	uint32_t *stack_base3 = &stack3[99];
		uint32_t **stack_base3_2 = &stack_base3;
	uint32_t priority3 = 2;
	void (*user3_pt)(void) = &user3;
	os_task_create(temp3,user3_pt,stack_base3_2,100,priority3);
	
	uint32_t *stack_base20 = &stack20[199];
		uint32_t **stack_base20_3 = &stack_base20;
	uint32_t priority20 = 20;
	void (*user20_pt)(void) = &idle;
	os_task_create(temp2,user20_pt,stack_base20_3,200,priority20);
	gpio_init();
	os_start();
	return 0;
}
