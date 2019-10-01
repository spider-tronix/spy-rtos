#include <OS/tasks.h>
#include <OS/os.h>
void os_mutex_create(struct mutex *mut)
{
	mut->lock = 0;
	mut->mut_ptr_head = NULL;
	mut->mut_ptr_tail = NULL;
}

void os_mutex_lock(struct mutex *mut)
{
	
}