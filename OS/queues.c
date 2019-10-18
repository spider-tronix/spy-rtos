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

void os_dly_list_insert(struct tcb *temp,uint32_t time)
{
	struct dly_data dly_temp;
	dly_temp.dly_tcb = temp;
	dly_temp.remain_time = time;
	dly_temp.next = NULL;
	dly_temp.prev = NULL;
	struct dly_data *dly_list_ptr = os_dly_list_head;
	if(dly_list_ptr == NULL)
	{
		os_dly_list_head = &dly_temp;
		os_dly_list_tail = &dly_temp;
	}
	else
	{
	  while(dly_list_ptr !=NULL && dly_temp.remain_time >= dly_list_ptr->remain_time)
		{
		  dly_temp.remain_time-=dly_list_ptr->remain_time;
			dly_list_ptr = dly_list_ptr->next;
	  }
		if(dly_list_ptr == NULL)
		{
			os_dly_list_tail->next = &dly_temp;
			dly_temp.prev = os_dly_list_tail;
			os_dly_list_tail = os_dly_list_tail->next;
		}
		else
		{
			dly_list_ptr->remain_time-=dly_temp.remain_time;
			dly_list_ptr->prev->next = &dly_temp;
			dly_temp.prev = dly_list_ptr->prev;
			dly_temp.next = dly_list_ptr;
			dly_list_ptr->prev =&dly_temp;
		}
	}
}