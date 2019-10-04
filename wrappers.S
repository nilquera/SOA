/*
 * wrappers.S
 */

#include <asm.h>

ENTRY(gettime)
	pushl %ebp
	movl %esp, %ebp
	movl $0xa, %eax
	pushl %edx
	pushl %ecx
	pushl next
	pushl %ebp
	movl %esp, %ebp
	sysenter
next:
	popl %ebp
	subl 4, %esp
	popl %ecx
	popl %edx
	cmpl $0, %eax
	jge end_gettime
	neg  %eax
    movl %eax, errno
	movl $-1, %eax
end_gettime:
	movl %ebp, %esp
	popl %ebp

ENTRY(write)
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %ebx
	movl 12(%ebp), %ecx
	movl 16(%ebp), %edx
	movl $0x4, %eax
	pushl %edx //no caldria
	pushl %ecx
	pushl next
	pushl %ebp
	movl %esp, %ebp
	sysenter
next:
	popl %ebp
	subl 4, %esp
	popl %ecx
	popl %edx
	cmpl $0, %eax
	jge end_write
	neg  %eax
    movl %eax, errno
	movl $-1, %eax
end_write:
	movl %ebp, %esp
	popl %ebp