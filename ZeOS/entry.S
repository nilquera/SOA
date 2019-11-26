/*
 * entry.S - Entry point to system mode from user mode
 */

#include <asm.h>
#include <segment.h>


/**************************************************/
/**** Save & Restore ******************************/
/**                                              **/
/** When we change to privilege level 0 (kernel) **/
/** (through an interrupt, a system call, an     **/
/** exception ...) we must save the state of the **/
/** currently running task (save).               **/
/**                                              **/
/** Stack layout in 'systemCall':                **/
/**                                              **/
/**   0(%esp) - %ebx    \                        **/
/**   4(%esp) - %ecx     |                       **/
/**   8(%esp) - %edx     |                       **/
/**   C(%esp) - %esi     | Register saved        **/
/**  10(%esp) - %edi     |  by 'save'            **/
/**  14(%esp) - %ebp     |                       **/
/**  18(%esp) - %eax     |                       **/
/**  1C(%esp) - %ds      |                       **/
/**  20(%esp) - %es      |                       **/
/**  24(%esp) - %fs      |                       **/
/**  28(%esp) - %gs     /                        **/
/**  2C(%esp) - %eip    \                        **/
/**  30(%esp) - %cs      |                       **/
/**  34(%esp) - %eflags  |  Return context saved **/
/**  38(%esp) - %oldesp  |   by the processor.   **/
/**  3C(%esp) - %oldss  /                        **/
/**                                              **/
/**************************************************/

#define SAVE_ALL \
	pushl %gs; \
	pushl %fs; \
	pushl %es; \
	pushl %ds; \
	pushl %eax; \
	pushl %ebp; \
	pushl %edi; \
	pushl %esi; \
	pushl %edx; \
	pushl %ecx; \
	pushl %ebx; \
	movl $__KERNEL_DS, %edx;    \
	movl %edx, %ds;           \
	movl %edx, %es

#define RESTORE_ALL \
	popl %ebx; \
	popl %ecx; \
	popl %edx; \
	popl %esi; \
	popl %edi; \
	popl %ebp; \
	popl %eax; \
	popl %ds; \
	popl %es; \
	popl %fs; \
	popl %gs;

#define SAVE_UPDATE \
	pushl %eax; \
	pushl %ebp; \
	pushl %edi; \
	pushl %esi; \
	pushl %edx; \
	pushl %ecx; \
	pushl %ebx;

#define RESTORE_UPDATE \
	popl %ebx; \
	popl %ecx; \
	popl %edx; \
	popl %esi; \
	popl %edi; \
	popl %ebp; \
	popl %eax;

#define EOI \
	movb $0x20, %al; \
	outb %al, $0x20 ;

ENTRY(keyboard_handler)
	SAVE_ALL
	SAVE_UPDATE
	call update_stats_enter
	RESTORE_UPDATE
	EOI
	call keyboard_routine
	SAVE_UPDATE
	call update_stats_exit
	RESTORE_UPDATE
	RESTORE_ALL
	iret

ENTRY(clock_handler)
	SAVE_ALL
	SAVE_UPDATE
	call update_stats_enter
	RESTORE_UPDATE
	EOI
	call clock_routine
	SAVE_UPDATE
	call update_stats_exit
	RESTORE_UPDATE
	RESTORE_ALL
	iret
	
// definim temporalment ENOSYS, que posteriorment estará a errno.h
.globl ENOSYS
ENOSYS = 78

ENTRY(syscall_handler_sysenter)
	push $__USER_DS
	push %ebp
	pushfl
	push $__USER_CS
	push 4(%EBP)
	SAVE_ALL
	cmpl $0, %eax
	jl sysenter_err
	cmpl $MAX_SYSCALL, %eax
	jg sysenter_err
	SAVE_UPDATE
	call update_stats_enter
	RESTORE_UPDATE
	call *sys_call_table(, %eax, 0x04)
	jmp sysenter_fin
sysenter_err:
	movl $-ENOSYS, %eax
sysenter_fin:
	movl %eax, 0x18(%esp)
	RESTORE_ALL
	movl (%esp), %edx
	movl 12(%esp), %ecx
	SAVE_UPDATE
	call update_stats_exit
	RESTORE_UPDATE
	sti
	sysexit

	

ENTRY(system_call_handler)
SAVE_ALL                            // Save the current context
cmpl $0, %EAX 	// Is syscall number negative?
jl err                              //Ifit is, jump to return an error
cmpl $MAX_SYSCALL, %EAX // Is syscall greater than MAX_SYSCALL (4)?
jg err                              //Ifit is, jump to return an error
call *sys_call_table(, %EAX, 0x04)  //Callthe corresponding service routine
jmp fin                             // Finish
err:
movl $-ENOSYS, %EAX // Move to EAX the ENOSYS error
fin:
movl %EAX, 0x18(%esp)               // Change theEAXvalueinthe stack
RESTORE_ALL                         // Restore the context
iret