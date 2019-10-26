/*
 * sys.c - Syscalls implementation
 */
#include <devices.h>

#include <utils.h>

#include <io.h>

#include <mm.h>

#include <mm_address.h>

#include <sched.h>

#include <stats.h> //necessari per zeos_ticks variable

#define LECTURA 0
#define ESCRIPTURA 1

int check_fd(int fd, int permissions)
{
  if (fd!=1) return -9; /*EBADF*/
  if (permissions!=ESCRIPTURA) return -13; /*EACCES*/
  return 0;
}

int sys_ni_syscall()
{
	return -38; /*ENOSYS*/
}

int sys_getpid()
{
	return current()->PID;
}

void ret_from_fork();

int sys_fork()
{
	int PID=current()->PID;

	if (is_empty(&freequeue)) return ENOMEM;

	struct list_head *first_elem = list_first(&freequeue);
	list_del(first_elem);
	struct task_struct *child_ts = list_head_to_task_struct(first_elem);

	// Inherit system data from parent to child
	copy_data((void *)current(), (void *)child_ts, sizeof(union task_union)); // use KERNEL_STACK_SIZE instead?

	// Initialize child's dir_pages_baseAddr
	child_ts->dir_pages_baseAddr = allocate_DIR(child_ts);

	// Set child's pages using father
	int ret = fork_set_pages(current(), child_ts);
	if (ret != 0) return ret;

	// Assign new PID
	assign_pid(child_ts);

	/* Modify child's system stack
	   We need to know where to make modifications in his stack
		
		|    0   |
		|--------|
		|ret_fork| <-- [KERNEL_STACK_SIZE - 18]
		|--------|
		|@handler|
		|--------| 
		| ctx sw | 11 pos (registers)
		|--------|
		| ctx hw | 5 pos (cpu state, stack pointer and ins pointer)

	*/
	union task_union *child_tu = (union task_union *)child_ts;
	child_tu->stack[KERNEL_STACK_SIZE-18] = &ret_from_fork;
	child_tu->stack[KERNEL_STACK_SIZE-19] = 0;
	child_ts->kernel_ebp = &stack[KERNEL_STACK_SIZE-19];

	return PID;
}

void sys_exit()
{  
}

int sys_write(int fd,char *buffer,int size){
	int check = check_fd(fd, ESCRIPTURA);
	if (check < 0) return check;
	else if (*buffer == NULL || size <= 0) return -4; /*EINTR*/
	else return sys_write_console(buffer, size);
}

int sys_gettime(){
	if (zeos_ticks < 0) return -4; /*EINTR*/
	else return zeos_ticks;
}