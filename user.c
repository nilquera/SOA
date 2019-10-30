#include <libc.h>
#include <stats.h>

int pid;
char buff[40];


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
	
/*
		struct stats st;
		char string[40] = "\n Hola";
		write(1, string, strlen(string));
		get_stats(1, &st);
		char string2[40] = "\n Hola";
		write(1, string2, strlen(string2));
		int value = st.total_trans;
		itoa(value, string);
		if (write(1, string, strlen(string)) == -1){
			perror();
		}
		*/

	while(1){
	}
}