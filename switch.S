#include <asm.h>

ENTRY(inner_task_switch_asm)
	pushl %ebp
	movl %esp, %ebp
	movl $0xFFFFF000, %ebx
	and %esp, %ebx
	movl %ebp, (%ebx) # 1) guarda ebp en kernel_ebp
	movl 8(%ebp), %esp # 2) Enchufa el kernel_ebp de new a esp
	movl 0(%esp), %esp #	+
	popl %ebp 		   #	Cambia de pila de sistema :)
	ret	


ENTRY(task_switch)
	push %ebp
	movl %esp, %ebp
	push %esi
	push %edi
	push %ebx
	movl 8(%ebp), %eax
	pushl %eax
	call inner_task_switch
	popl %ebx
	popl %edi
	popl %esi
	movl %ebp, %esp
	popl %ebp
	ret

## crec que això s'ha de borrar
ENTRY(init_idle_switch)
	pushl cpu_idle
	pushl $0
	ret