/*
 * wrappers.S
 */

#include <asm.h>

ENTRY(fork)
	push %ebp
	mov %esp, %ebp
	mov $0x2, %eax
	push %edx
	push %ecx
	push $next_fork
	push %ebp
	movl %esp, %ebp
	sysenter
next_fork:
	popl %ebp
	subl $4, %esp
	popl %ecx
	popl %edx
	cmpl $0, %eax
	jge end_fork
	neg  %eax
    movl %eax, errno
	movl $-1, %eax
end_fork:
	movl %ebp, %esp
	popl %ebp
	ret

ENTRY(getpid)
	push %ebp
	mov %esp, %ebp
	mov $0x14, %eax
	push %edx
	push %ecx
	push $next_getpid
	push %ebp
	movl %esp, %ebp
	sysenter
next_getpid:
	popl %ebp
	subl $4, %esp
	popl %ecx
	popl %edx
	cmpl $0, %eax
	jge end_getpid
	neg  %eax
    movl %eax, errno
	movl $-1, %eax
end_getpid:
	movl %ebp, %esp
	popl %ebp
	ret

ENTRY(gettime)
	push %ebp
	movl %esp, %ebp
	movl $0xa, %eax
	push %edx
	push %ecx
	push $next_gettime
	push %ebp
	movl %esp, %ebp
	sysenter
next_gettime:
	popl %ebp
	subl $4, %esp
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
	ret

ENTRY(write)
	push %ebp
	movl %esp, %ebp
	movl 8(%ebp), %ebx
	movl 12(%ebp), %ecx
	movl 16(%ebp), %edx
	movl $0x4, %eax
	push %edx //no caldria
	push %ecx
	push $next_write
	push %ebp
	movl %esp, %ebp
	sysenter
next_write:
	popl %ebp
	subl $4, %esp
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
	ret