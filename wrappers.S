/*
 * wrappers.S
 */

#include <asm.h>
//include <libc.c>

.global errno

ENTRY(write)
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %ebx
	movl 12(%ebp), %ecx
	movl 16(%ebp), %edx
	movl $0x04, %eax
	int $0x80
	cmpl $0, %eax
	jge end
	neg  %eax
    movl %eax, errno
	movl $-1, %eax
end:
	movl %ebp, %esp
	popl %ebp
	ret