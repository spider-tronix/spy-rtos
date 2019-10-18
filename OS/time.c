#include <OS/tasks.h>
#include <OS/os.h>

void os_dly_update()
{
	while(1)
	{
		os_sem_wait(&os_dly_sem);
		
	}
}