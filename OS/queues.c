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

void os_dly_list_insert(struct tcb *temp,int32_t time)
{
	temp->remain_time = time;
	temp->dly_next = NULL;
	temp->dly_prev = NULL;
	struct tcb *dly_list_ptr = os_dly_list_head;
	if(dly_list_ptr == NULL)
	{
		os_dly_list_head = temp;
		os_dly_list_tail = temp;
	}
	else
	{
	  while(dly_list_ptr !=NULL && temp->remain_time >= dly_list_ptr->remain_time)
		{
		  temp->remain_time -= dly_list_ptr->remain_time;
			dly_list_ptr = dly_list_ptr->dly_next;
	  }
		if(dly_list_ptr == NULL)
		{
			os_dly_list_tail->dly_next = temp;
			temp->dly_prev = os_dly_list_tail;
			os_dly_list_tail = temp;
		}
		else if(dly_list_ptr->dly_prev == NULL)
		{
			dly_list_ptr->remain_time -= temp->remain_time;
			dly_list_ptr->dly_prev = temp;
			temp->dly_next = dly_list_ptr;
			os_dly_list_head = temp;
		}
		else
		{
			dly_list_ptr->remain_time-=temp->remain_time;
			dly_list_ptr->dly_prev->dly_next = temp;
			temp->dly_prev = dly_list_ptr->dly_prev;
			temp->dly_next = dly_list_ptr;
			dly_list_ptr->dly_prev = temp;
		}
	}
	temp->task_state=WAITING;
	os_remove_ready_list(temp);
}

void os_dly_list_remove(struct tcb *temp)
 { 
	if(temp->dly_next == NULL)
	{
		os_dly_list_head = NULL;
		os_dly_list_tail = NULL;
	}
	else
	{
	  os_dly_list_head = temp->dly_next;
	  os_dly_list_head->dly_prev = NULL;
	  temp->dly_next = NULL;
		temp->dly_prev = NULL;
	}
	os_add_ready(temp);
}
