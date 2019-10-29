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

	int ret = fork();

	char fill[40] = "\nSoc el fill\n";
	char pare[40] = "Soc el pare\n";
	if (ret == 0){
		if (write(1, fill, strlen(fill)) == -1){
			perror();
		}
	} else if (ret != 0){
		exit();
		if (write(1, pare, strlen(pare)) == -1){
			perror();
		}
	}
	while(1){  }
}