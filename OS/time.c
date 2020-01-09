#include <OS/tasks.h>
#include <OS/os.h>

inline void os_time_dly(uint32_t ticks)
{
	os_dly_list_insert(current_tcb,ticks);
	os_scheduler();
}

void os_dly_update(void *args)
{
	struct tcb *dly_list_ptr;
	intr_alloc();
	while(1)
	{
		os_sem_wait(&os_dly_sem);
		os_start_critical();
		dly_list_ptr = os_dly_list_head;
		if(dly_list_ptr == NULL)
		{
			os_end_critical();
			return;
		}
		dly_list_ptr->remain_time--;
		if(dly_list_ptr->remain_time == 0)
		{
			while(dly_list_ptr->remain_time ==0)
			{
				os_dly_list_remove(dly_list_ptr);
				dly_list_ptr=dly_list_ptr->dly_next;
			}
		}
    os_end_critical();		
	}
}
