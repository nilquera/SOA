

#include <asm.h>



ENTRY(inner_task_switch_asm)
	pushl %ebp
	movl %esp, %ebp
	movl 0xFFFFF000, %ebx
	and %esp, %ebx
	movl %ebp, (%ebx) #guarda ebp en kernel_ebp
	movl 8(%ebp), %esp
	movl 0(%esp), %esp #enchufa el kernel_esp de new a esp
	movl %ebp, %esp
	popl %ebp
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

