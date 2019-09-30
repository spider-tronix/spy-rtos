#include <OS/tasks.h>
#include <OS/os.h>

void os_sem_create(struct semaphore *sem,uint16_t count)
{
	sem->sem_count = count;
	sem->sem_ptr_head = NULL;
	sem->sem_ptr_tail = NULL;
}

void os_release(struct semaphore *sem)
{
	os_add_ready_list(os_delete_semqueue(sem)->tcb_ptr);
}
