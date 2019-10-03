/*
 * wrappers.S
 */

#include <asm.h>

ENTRY(write) \
	movl 8(%ebp), %ebx;	\
	movl 12(%ebp), %ecx; \
	movl 16(%ebp), %edx; \
	movl $1, %eax; \
	int $0x80; \
	cmpl $0, %eax; \
	jl error; \


	jmp end; \
error:

end:
	ret;