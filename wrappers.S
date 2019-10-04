/*
 * wrappers.S
 */

#include <asm.h>
/*
ENTRY(write)
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %ebx
	movl 12(%ebp), %ecx
	movl 16(%ebp), %edx
	movl $0x4, %eax
	int $0x80
	cmpl $0, %eax
	jge end_write
	neg  %eax
    movl %eax, errno
	movl $-1, %eax
end_write:
	movl %ebp, %esp
	popl %ebp
	ret
*/
/*ENTRY(gettime)
	pushl %ebp
	movl %esp, %ebp
	movl $0xa, %eax
	int $0x80
	cmpl $0, %eax
	jge end_gettime
	neg  %eax
    movl %eax, errno
	movl $-1, %eax
end_gettime:
	movl %ebp, %esp
	popl %ebp
	ret
*/
ENTRY(write)
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %ebx
	movl 12(%ebp), %ecx
	movl 16(%ebp), %edx
	pushl %edx //no caldria
	pushl %ecx
	pushl next
	pushl %ebp
	movl %esp, %ebp
	sysenter
next:
	popl %ebp
	popl
	popl %ecx
	popl %edx
	movl %ebp, %esp
	popl %ebp