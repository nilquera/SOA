# 1 "wrappers.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "wrappers.S"




# 1 "include/asm.h" 1
# 6 "wrappers.S" 2


.global errno

.globl write; .type write, @function; .align 0; write:
 pushl %ebp
 movl %esp, %ebp
 movl 8(%ebp), %ebx
 movl 12(%ebp), %ecx
 movl 16(%ebp), %edx
 movl $0x04, %eax
 int $0x80
 cmpl $0, %eax
 jge end
 neg %eax
    movl %eax, errno
 movl $-1, %eax
end:
 movl %ebp, %esp
 popl %ebp
 ret
