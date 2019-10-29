/*
 * sched.c - initializes struct for task 0 anda task 1
 */

#include <sched.h>
#include <mm.h>
#include <io.h>
#include <stats.h>

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

void init_stats(struct task_struct *t){
	(t->task_stats).user_ticks = 0;
	(t->task_stats).system_ticks = 0;
	(t->task_stats).blocked_ticks = 0;
	(t->task_stats).ready_ticks = 0;
	(t->task_stats).elapsed_total_ticks = 0;
	(t->task_stats).total_trans = 0;
	(t->task_stats).remaining_ticks = _QUANTUM;
}



struct task_struct *list_head_to_task_struct(struct list_head *l){
	return (struct task_struct*) ((int)l & 0xfffff000);
}


void cpu_idle(void)
{
	__asm__ __volatile__("sti": : :"memory");
	while(1)
	{
		printk("Idle\n");
	}
}

void init_idle (void)
{
 	struct list_head *first_elem = list_first(&freequeue);
	list_del(first_elem); // hay que quitar el list_head de la freequeue, sino el init pilla el mismo

	struct task_struct *free_ts = list_head_to_task_struct(first_elem);
	free_ts->PID = 0;
	set_quantum(free_ts, _QUANTUM);

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
	set_quantum(free_ts, _QUANTUM);

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

	init_stats(free_ts);
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
	ticks_count = _QUANTUM;
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

void assign_pid(struct task_struct *t){
	t->PID = pid_count;
	++pid_count;
	if (pid_count == NR_TASKS) pid_count = 2;
}

/**/
int get_quantum (struct task_struct *t){
	return t->quantum;
}

void set_quantum (struct task_struct *t, int new_quantum){
	t->quantum = new_quantum;
}

/* sched_next_rr - selects next process to execute and invokes context switch. */
void sched_next_rr(){
	struct list_head *first_elem = list_first(&readyqueue);
	list_del(first_elem);
	struct task_struct *ready_ts = list_head_to_task_struct(first_elem);
	ticks_count = ready_ts->quantum;
	(ready_ts->task_stats).total_trans++;
	task_switch((union task_union*)ready_ts);
}

/* update_process_state_rr - update current state of process to new state */
void update_process_state_rr(struct task_struct *t, struct list_head *dest){
	if (current() != t) list_del(&(t->list));
	if (dest != NULL){
		list_add_tail(&(t->list), dest);
	}
	(t->task_stats).elapsed_total_ticks = zeos_ticks;
}

/* needs_sched_rr - decides if it is necessary to change current process */
int needs_sched_rr(){
	if (ticks_count <= 0) return 1;
	else return 0;

}

/* update_sched_data_rr - updates relevant info to take scheduling decisions */
void update_sched_data_rr(){
	--ticks_count;
	(current()->task_stats).remaining_ticks = ticks_count;
}

void update_ready_ticks(int Q) {
	struct list_head *pos;
	list_for_each(pos, &readyqueue){
		struct task_struct * ts = list_head_to_task_struct(pos);
		(ts->task_stats).ready_ticks += Q;
	}
}


void schedule(){
	update_sched_data_rr();
	if (needs_sched_rr()){
		if (list_empty(&readyqueue)) {
			ticks_count = current()->quantum;
		} else {
			update_ready_ticks(current()->quantum);
			if (current()->PID != 0) update_process_state_rr(current(), &readyqueue);
			sched_next_rr();

		}	
	}
}