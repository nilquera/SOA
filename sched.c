/*
 * sched.c - initializes struct for task 0 anda task 1
 */

#include <sched.h>
#include <mm.h>
#include <io.h>

void inner_task_switch_asm(union task_union *new);
void writeMSR(int msr_name, long unsigned int address);

union task_union task[NR_TASKS]
  __attribute__((__section__(".data.task")));

#if 0
struct task_struct *list_head_to_task_struct(struct list_head *l)
{
  return list_entry( l, struct task_struct, list);
}
#endif

extern struct list_head blocked;


/* get_DIR - Returns the Page Directory address for task 't' */
page_table_entry * get_DIR (struct task_struct *t) 
{
	return t->dir_pages_baseAddr;
}

/* get_PT - Returns the Page Table address for task 't' */
page_table_entry * get_PT (struct task_struct *t) 
{
	return (page_table_entry *)(((unsigned int)(t->dir_pages_baseAddr->bits.pbase_addr))<<12);
}


page_table_entry * allocate_DIR(struct task_struct *t)
{
	int pos;

	pos = ((int)t-(int)task)/sizeof(union task_union);

	return (page_table_entry*) &dir_pages[pos];
}





struct task_struct *list_head_to_task_struct(struct list_head *l){
	return (struct task_struct*) ((int)l & 0xfffff000);
}


void cpu_idle(void)
{
	__asm__ __volatile__("sti": : :"memory");
	printk("ESTIC A IDLE!!!!");
	while(1)
	{
	;
	}
}

void init_idle (void)
{
 	struct list_head *first_elem = list_first(&freequeue);
	list_del(first_elem); // hay que quitar el list_head de la freequeue, sino el init pilla el mismo

	struct task_struct *free_ts = list_head_to_task_struct(first_elem);
	free_ts->PID = 0;

	// Allocate an empty DIR for the free_ts
	// page_table_entry *pte = allocate_DIR(free_ts);
	free_ts->dir_pages_baseAddr = allocate_DIR(free_ts);

	// Get address of stack
	union task_union *free_tu = (union task_union *)free_ts; //cast free_ts to task_union pointer
	unsigned long *stack = free_tu->stack; //get a copy of (address of) stack

	// Put address of cpu_idle and fake ebp (0) at the bottom of the stack
	stack[KERNEL_STACK_SIZE-2] = 0;
	stack[KERNEL_STACK_SIZE-1] = (unsigned long) &cpu_idle;

	// Point free_ts' kernel_ebp to the position of the fake ebp.
	free_ts->kernel_ebp = &stack[KERNEL_STACK_SIZE-2];

	// Initialize idle_task
	idle_task = free_tu;

	/*
		free_ts->kernel_ebp=&(((union task_union *)free_ts)->stack[KERNEL_STACK_SIZE-1]);
		//free_ts->kernel_ebp=(unsigned long *) ((unsigned long)free_ts|(unsigned long)4095);

		*(free_ts->kernel_ebp)=(unsigned long) &cpu_idle;

		free_ts->kernel_ebp=&(((union task_union *)free_ts)->stack[KERNEL_STACK_SIZE-2]);
		//free_ts->kernel_ebp-=4;

		*(free_ts->kernel_ebp)=0;
	*/
}

void init_task1(void)
{
	struct list_head *first_elem = list_first(&freequeue);
	list_del(first_elem);

	struct task_struct *free_ts = list_head_to_task_struct(first_elem);
	free_ts->PID = 1;

	free_ts->dir_pages_baseAddr = allocate_DIR(free_ts);
	set_user_pages(free_ts);

	//no diu a la guia que s'hagi de fer això
	//suposo que quan es fanci un switch de init a un altre process
	//... el kernel_ebp es modifica al final, per tant és igual el que valgui al principi 
	//... El kernel_ebp serveix per ENTRAR a la CPU, però init la primera vegada no entra amb task_switch
	free_ts->kernel_ebp=&(((union task_union *)free_ts)->stack[KERNEL_STACK_SIZE-1]); //apunta abaix

	tss.esp0 = (unsigned long)free_ts->kernel_ebp;
	writeMSR(0x175, tss.esp0);
	set_cr3(free_ts->dir_pages_baseAddr);
}

void init_freequeue()
{
	INIT_LIST_HEAD(&freequeue);
	for (int i = 0; i < NR_TASKS; ++i){
		list_add_tail(&task[i].task.list, &freequeue);
	}
}

void init_readyqueue()
{
	INIT_LIST_HEAD(&readyqueue);
}


void init_sched()
{
	pid_count = 2; 
	init_freequeue();
	init_readyqueue();
}

struct task_struct* current()
{
  int ret_value;
  
  __asm__ __volatile__(
  	"movl %%esp, %0"
	: "=g" (ret_value)
  );
  return (struct task_struct*)(ret_value&0xfffff000);
}

// modificar inner_task_switch_asm i fer servir current()
void inner_task_switch(union task_union *new){
	tss.esp0 = (unsigned long)(new->task).kernel_ebp;
	writeMSR(0x175, tss.esp0);
	set_cr3((new->task).dir_pages_baseAddr);
	inner_task_switch_asm(new);
}

void assign_pid(struc task_struct *t){
	t.PID = pid_count;
	++pid_count;
	if (pid_count == NR_TASKS) pid_count = 2;
}

