/*
 * fork.S
 */

#include <asm.h>

ENTRY(ret_from_fork)
	push %ebp
	mov %esp, %ebp
	mov $0, %eax
	pop %ebp
	ret


	