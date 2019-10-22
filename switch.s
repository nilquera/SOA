# 1 "switch.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "switch.S"
# 1 "include/asm.h" 1
# 2 "switch.S" 2

.globl inner_task_switch_asm; .type inner_task_switch_asm, @function; .align 0; inner_task_switch_asm:
 pushl %ebp
 movl %esp, %ebp
 movl 0xFFFFF000, %ebx
 and %esp, %ebx
 movl %ebp, (%ebx) #guarda ebp en kernel_ebp
 movl 8(%ebp), %esp
 movl 0(%esp), %esp #enchufa el kernel_esp de new a esp
 movl %ebp, %esp
 popl %ebp
 ret


.globl task_switch; .type task_switch, @function; .align 0; task_switch:
 push %ebp
 movl %esp, %ebp
 push %esi
 push %edi
 push %ebx
 movl 8(%ebp), %eax
 pushl %eax
 call inner_task_switch
 popl %ebx
 popl %edi
 popl %esi
 movl %ebp, %esp
 popl %ebp

.globl init_idle_switch; .type init_idle_switch, @function; .align 0; init_idle_switch:
 pushl cpu_idle
 pushl $0
