#include <libc.h>

char buff[24];

int pid;

int __attribute__ ((__section__(".text.main")))
  main(void)
{
	/* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
	/* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */
	char buffer[40] = "\nEl PID de init es: ";
	if (write(1, buffer, strlen(buffer)) == -1){
		perror();
	}
	itoa(getpid(), buffer);
	if (write(1, buffer, strlen(buffer)) == -1){
		perror();
	}
	char buffer2[40] = "\nLa llamada a fork devuelve: ";
	if (write(1, buffer2, strlen(buffer2)) == -1){
		perror();
	}
	itoa(fork(), buffer2);
	if (write(1, buffer2, strlen(buffer2)) == -1){
		perror();
	}

	while(1){ }
}