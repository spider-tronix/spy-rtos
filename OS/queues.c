#include <OS/os.h>
void os_add_semqueue(struct semaphore *head,struct sem_data *temp_sem)
{
	struct sem_data *temp = head->sem_ptr_head;
	if(head->sem_ptr_head==NULL)
	{
		head->sem_ptr_head=temp_sem;
		head->sem_ptr_tail=temp_sem;
	}
	else
	{
		while(temp!= NULL)
		{
			if(temp_sem->tcb_ptr->priority <= temp->tcb_ptr->priority)
			{
				break;
			}
			temp = temp->next;
		}	
		if(temp == NULL)
		{
			head->sem_ptr_tail->next = temp_sem;
			temp_sem->prev = head->sem_ptr_tail;
			head->sem_ptr_tail = temp_sem;
		}
		else if(temp->prev == NULL)
		{
			head->sem_ptr_head->prev = temp_sem;
			temp_sem->next = head->sem_ptr_head;
			head->sem_ptr_head = temp_sem;
		}
		else
		{
			temp->prev->next = temp_sem;
			temp_sem->prev = temp->prev;
			temp->prev = temp_sem;
			temp_sem->next = temp;
		}
	}
}
struct sem_data* os_delete_semqueue(struct semaphore *sem)
{
	struct sem_data *temp = sem->sem_ptr_head;
	if(sem->sem_ptr_head==NULL)
	{
		return NULL;
	}
	else
	{
		temp->next->prev =NULL;
		sem->sem_ptr_head = temp->next;
		return temp;
	}
}
