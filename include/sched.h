/*
 * sched.h - Estructures i macros pel tractament de processos
 */

#ifndef __SCHED_H__
#define __SCHED_H__

#include <list.h>
#include <types.h>
#include <mm_address.h>
#include <stats.h>

#define NR_TASKS      10
#define KERNEL_STACK_SIZE	1024
#define _QUANTUM	100

int pid_count; // Policy: increment by 1 every new process.

int ticks_count; // Current process number of ticks in the CPU

struct list_head freequeue;
struct list_head readyqueue;
union task_union *idle_task;

enum state_t { ST_RUN, ST_READY, ST_BLOCKED };

struct task_struct {
  unsigned long *kernel_ebp;
  int PID;			/* Process ID. This MUST be the first field of the struct. */
  page_table_entry * dir_pages_baseAddr;
  struct list_head list;
  int quantum;
  struct stats task_stats;
};

union task_union {
  struct task_struct task;
  unsigned long stack[KERNEL_STACK_SIZE];    /* pila de sistema, per procés */
};

extern union task_union task[NR_TASKS]; /* Vector de tasques */


#define KERNEL_ESP(t)       	(DWord) &(t)->stack[KERNEL_STACK_SIZE]

#define INITIAL_ESP       	KERNEL_ESP(&task[1])

/* Inicialitza les dades del proces inicial */
void init_task1(void);

void init_idle(void);

void init_sched(void);

void inner_task_switch(union task_union *new);

void init_freequeue(void);
void init_readyqueue(void);

struct task_struct * current();

void task_switch(union task_union*t);

struct task_struct *list_head_to_task_struct(struct list_head *l);

page_table_entry * allocate_DIR(struct task_struct *t);

page_table_entry * get_PT (struct task_struct *t) ;

page_table_entry * get_DIR (struct task_struct *t) ;

/* Headers for the scheduling policy */
/*
void sched_next_rr();
void update_process_state_rr(struct task_struct *t, struct list_head *dest);
int needs_sched_rr();
void update_sched_data_rr();
*/

int get_quantum (struct task_struct *t);
void set_quantum (struct task_struct *t, int new_quantum);
void schedule();

void assign_pid(struct task_struct *t);

void init_stats(struct task_struct *t);

void update_ready_ticks(int Q);

void update_stats_enter();
void update_stats_exit();

struct stats *get_task_stats(struct task_struct *t);
struct list_head *get_task_list (struct task_struct *t);

#endif  /* __SCHED_H__ */
