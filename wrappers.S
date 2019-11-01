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
	mov %esp, %ebp
	sysenter
next_fork:
	pop %ebp
	sub $4, %esp
	pop %ecx
	pop %edx
	cmp $0, %eax
	jge end_fork
	neg  %eax
    mov %eax, errno
	mov $-1, %eax
end_fork:
	mov %ebp, %esp
	pop %ebp
	ret

ENTRY(exit)
	push %ebp
	mov %esp, %ebp
	mov $0x1, %eax
	push %edx
	push %ecx
	push $next_exit
	push %ebp
	mov %esp, %ebp
	sysenter
next_exit:
	pop %ebp
	sub $4, %esp
	pop %ecx
	pop %edx
	cmp $0, %eax
	jge end_exit
	neg  %eax
    mov %eax, errno
	mov $-1, %eax
end_exit:
	mov %ebp, %esp
	pop %ebp
	ret

ENTRY(getpid)
	push %ebp
	mov %esp, %ebp
	mov $0x14, %eax
	push %edx
	push %ecx
	push $next_getpid
	push %ebp
	mov %esp, %ebp
	sysenter
next_getpid:
	pop %ebp
	sub $4, %esp
	pop %ecx
	pop %edx
	cmp $0, %eax
	jge end_getpid
	neg  %eax
    mov %eax, errno
	mov $-1, %eax
end_getpid:
	mov %ebp, %esp
	pop %ebp
	ret

ENTRY(gettime)
	push %ebp
	mov %esp, %ebp
	mov $0xa, %eax
	push %edx
	push %ecx
	push $next_gettime
	push %ebp
	mov %esp, %ebp
	sysenter
next_gettime:
	pop %ebp
	sub $4, %esp
	pop %ecx
	pop %edx
	cmp $0, %eax
	jge end_gettime
	neg  %eax
    mov %eax, errno
	mov $-1, %eax
end_gettime:
	mov %ebp, %esp
	pop %ebp
	ret

ENTRY(write)
	push %ebp
	mov %esp, %ebp
	mov 8(%ebp), %ebx
	mov 12(%ebp), %ecx
	mov 16(%ebp), %edx
	mov $0x4, %eax
	push %edx
	push %ecx
	push $next_write
	push %ebp
	mov %esp, %ebp
	sysenter
next_write:
	pop %ebp
	sub $4, %esp
	pop %ecx
	pop %edx
	cmp $0, %eax
	jge end_write
	neg  %eax
    mov %eax, errno
	mov $-1, %eax
end_write:
	mov %ebp, %esp
	pop %ebp
	ret

ENTRY(get_stats)
	push %ebp
	mov %esp, %ebp
	mov 8(%ebp), %ebx
	mov 12(%ebp), %ecx
	mov $0x23, %eax
	push %edx
	push %ecx
	push $next_get_stats
	push %ebp
	mov %esp, %ebp
	sysenter
next_get_stats:
	pop %ebp
	sub $4, %esp
	pop %ecx
	pop %edx
	cmp $0, %eax
	jge end_get_stats
	neg  %eax
    mov %eax, errno
	mov $-1, %eax
end_get_stats:
	mov %ebp, %esp
	pop %ebp
	ret