# 1 "wrappers.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "wrappers.S"




# 1 "include/asm.h" 1
# 6 "wrappers.S" 2
# 40 "wrappers.S"
.globl write; .type write, @function; .align 0; write:
 pushl %ebp
 movl %esp, %ebp
 movl 8(%ebp), %ebx
 movl 12(%ebp), %ecx
 movl 16(%ebp), %edx
 movl $0x4, %eax
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
 movl %ebp, %esp
 popl %ebp
