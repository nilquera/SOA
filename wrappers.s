# 1 "wrappers.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "wrappers.S"




# 1 "include/asm.h" 1
# 6 "wrappers.S" 2

.globl gettime; .type gettime, @function; .align 0; gettime:
 pushl %ebp
 movl %esp, %ebp
 movl $0xa, %eax
 pushl %edx
 pushl %ecx
 pushl $next_gettime
 pushl %ebp
 movl %esp, %ebp
 sysenter
next_gettime:
 popl %ebp
 subl $4, %esp
 popl %ecx
 popl %edx
 cmpl $0, %eax
 jge end_gettime
 neg %eax
    movl %eax, errno
 movl $-1, %eax
end_gettime:
 movl %ebp, %esp
 popl %ebp
 ret

.globl write; .type write, @function; .align 0; write:
 pushl %ebp
 movl %esp, %ebp
 movl 8(%ebp), %ebx
 movl 12(%ebp), %ecx
 movl 16(%ebp), %edx
 movl $0x4, %eax
 pushl %edx
 pushl %ecx
 pushl $next_write
 pushl %ebp
 movl %esp, %ebp
 sysenter
next_write:
 popl %ebp
 subl $4, %esp
 popl %ecx
 popl %edx
 cmpl $0, %eax
 jge end_write
 neg %eax
    movl %eax, errno
 movl $-1, %eax
end_write:
 movl %ebp, %esp
 popl %ebp
 ret
