#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/string.h>
#include <linux/init.h> 
#include <linux/sched.h>
#include <linux/thread_info.h>

#define SYSCALL_TABLE_BASE_ADDR (0x8000fc28)
#define MANAGER_PERMISSION (0xff)

unsigned int ** g_puSysTableAddr = (unsigned int**)SYSCALL_TABLE_BASE_ADDR;
unsigned int g_uPrevAP = 0x00;
unsigned int g_uNewAP = MANAGER_PERMISSION;
unsigned int (* sys_write_orig)(int fd, char *byf, size_t count);

int is_match_PID(void)
{
	unsigned long pid = 0;
	struct task_struct *task;
	//struct task_struct *current;

	if(strcmp(current->comm, "hello_world") == 0 ){ //"target"
		pid = task->pid;
		return true;
	}

/* 2nd how to:
	for_each_process(task){
		if(strcmp(task->comm, "hello_world") == 0 ){ //"target"
			pid = task->pid;
			return true;
		}
	}
*/

/* 3rd how to: 
	//printk("My current process id/pid is %d\n", current->pid);

	for_each_process(task){
		if(strcmp(task->comm, "hello_world") == 0 ){ //"target"
			pid = task->pid;
			if(current->pid == pid)
				return true;
		}
	}
*/
			
	}
	
	//return pid;
	return false;
}

unsigned int sys_write_hooked(int nFD, char * pBuf, size_t nCnt)
{
	if ((nFD==1) && is_match_PID())
	{
		memset(pBuf, 0, nCnt);
		strcpy(pBuf, "Hacked!!!\n");
		return sys_write_orig(nFD, pBuf, nCnt);
	}
	else
		return sys_write_orig(nFD, pBuf, nCnt);
}

int __init Hook_Init(void)
{
	sys_write_orig = (void *)g_puSysTableAddr[__NR_write];

	__asm__ __volatile__("mrc p15, 0, %0, c3, c0" : "=r"(g_uPrevAP));
	__asm__ __volatile__("mcr p15, 0, %0, c3, c0" : :"r"(g_uNewAP));

	g_puSysTableAddr[__NR_write] = (unsigned int *) sys_write_hooked;

	__asm__ __volatile__("mcr p15, 0, %0, c3, c0" : :"r"(g_uPrevAP));
	return 0;
}

void __exit Hook_Exit(void)
{
	__asm__ __volatile__("mrc p15, 0, %0, c3, c0" : "=r"(g_uPrevAP));
	__asm__ __volatile__("mcr p15, 0, %0, c3, c0" : :"r"(g_uNewAP));

	g_puSysTableAddr[__NR_write] = (unsigned int *) sys_write_orig;

	__asm__ __volatile__("mcr p15, 0, %0, c3, c0" : :"r"(g_uPrevAP));
}

module_init(Hook_Init);
module_exit(Hook_Exit);


