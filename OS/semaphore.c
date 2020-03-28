#include <OS/tasks.h>
#include <OS/os.h>

void os_sem_create(struct semaphore *sem,uint16_t count)
{
	sem->sem_count = count;
	sem->sem_ptr_head = NULL;
	sem->sem_ptr_tail = NULL;
}

void os_sem_wait(struct semaphore *sem)
{
	intr_alloc();
	struct sem_data sem_block;
	os_start_critical();
	sem->sem_count--;
	if(sem->sem_count < 0)
	{
		os_sem_block(sem,&sem_block);
		os_end_critical();
	  os_scheduler();
	}
	else
	{
		os_end_critical();
	}
}

void os_sem_signal(struct semaphore *sem)
{
	intr_alloc();
	os_start_critical();
	sem->sem_count++;
	if(sem->sem_count <= 0)
	{
		if(os_int_cntr >0)
		{
			os_release(sem);
		  os_end_critical();
			return;
		}
		os_release(sem);
		os_end_critical();
	  os_scheduler();
	}
	else
	{
		os_end_critical();
	}
}

void os_sem_block(struct semaphore *sem,struct sem_data *sem_block)
{
	sem_block->tcb_ptr = current_tcb;
	sem_block->next = NULL;
	sem_block->prev = NULL;
	os_add_semqueue(sem,sem_block);
	os_remove_ready_list(current_tcb);
	current_tcb->task_state = WAITING;
}

void os_release(struct semaphore *sem)
{
	os_add_ready(os_delete_semqueue(sem)->tcb_ptr);
}
