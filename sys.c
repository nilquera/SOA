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

int sys_fork()
{
	int PID=-1;

	if (is_empty(&freequeue)) return -1;

	struct list_head *first_elem = list_first(&freequeue);
	list_del(first_elem);
	struct task_struct *child_ts = list_head_to_task_struct(first_elem);

	// Inherit system data from parent to child
	copy_data((void *)current(), (void *)child_ts, KERNEL_STACK_SIZE);

	// Initialize child's dir_pages_baseAddr
	child_ts->dir_pages_baseAddr = allocate_DIR(child_ts);

	// Initialize pages
	page_table_entry *child_PT =  get_PT(child_ts);
 	page_table_entry *father_PT = get_PT(current());
	int pag;
	int new_ph_pag;
	/* SYSTEM CODE pages are initialized for all processes in init_mm() */
	/* CODE: copy page entries from father process to child */
	for (pag=0;pag<NUM_PAG_CODE;pag++){
		child_PT[PAG_LOG_INIT_CODE+pag] = father_PT[PAG_LOG_INIT_CODE+pag];
	}
	/* DAT: finds a free page in father + maps new frames to child and father page table + transfers data */ 
	int free_father_pag;
	int found = 0;
	for (int free_father_pag = 0; free_father_pag < NUM_PAG_DATA && found == 0; ++free_father_pag){
		if (father_PT[PAG_LOG_INIT_DATA+free_father_pag].bits.pbase_addr = 20) found = 1;
	}
	if (found == 0) return -1;
	for (pag=0;pag<NUM_PAG_DATA;pag++){
		new_ph_pag=alloc_frame();
		if (new_ph_pag == -1) return -1; //potser tambe caldria desmapejar pagines
		set_ss_pag(child_PT, pag, new_ph_pag);
		set_ss_pag(father_PT, free_father_pag, new_ph_pag);
		// copy page from father no child
		copy_data(PAG_LOG_INIT_DATA+pag, PAG_LOG_INIT_DATA+free_father_pag, PAGE_SIZE);
	}
	del_ss_pag(father_PT, free_father_pag);
	set_cr3(current()->dir_pages_baseAddr);

	assign_pid(child_ts);

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

/* set_ss_pag - Associates logical page 'page' with physical page 'frame' */
void set_ss_pag(page_table_entry *PT, unsigned page,unsigned frame)
{
	PT[page].entry=0;
	PT[page].bits.pbase_addr=frame;
	PT[page].bits.user=1;
	PT[page].bits.rw=1;
	PT[page].bits.present=1;

}