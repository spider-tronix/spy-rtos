#include <OS/tasks.h>
#include <OS/os.h>

inline void os_time_dly(int32_t ticks)
{
	intr_alloc();
	os_start_critical();
	os_dly_list_insert(current_tcb,ticks);
	os_end_critical();
	os_scheduler();
}

void os_dly_update(void *args)
{
	
	struct tcb *dly_list_ptr;
	struct tcb *dummy_tcb_ptr;
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
		else
		
		{
			dly_list_ptr->remain_time = dly_list_ptr->remain_time-1;
			if(dly_list_ptr->remain_time <= 0)
		  {
			  while(dly_list_ptr!=NULL && dly_list_ptr->remain_time <=0)
				{
					dummy_tcb_ptr = dly_list_ptr->dly_next;
					os_dly_list_remove(dly_list_ptr);
					dly_list_ptr=dummy_tcb_ptr;
				}
			}
		}
	
    os_end_critical();
    os_scheduler();		
	}
}
