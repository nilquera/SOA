#include <libc.h>
#include <stats.h>

int pid;
char buff[40];

int fib(int f){
	if (f <= 1) return 1;
	else return fib(f-1)+fib(f-2);
}

void print_stats(int pid){
	char buff2[40];
	struct stats st;

	if (pid < 0) return;
	if (get_stats(pid, &st) == -1) {
		perror();
		return;
	}

	write(1, "\n\nSTATS FOR PID ", strlen("\n\nSTATS FOR PID "));
	itoa(pid, buff2);
	write(1, buff2, strlen(buff2));
	
	write(1, "\nUser_ticks: ", strlen("\nUser_ticks: "));
	itoa(st.user_ticks, buff2);
	write(1, buff2, strlen(buff2));

	write(1, "\nSystem_ticks: ", strlen("\nSystem_ticks: "));
	itoa(st.system_ticks, buff2);
	write(1, buff2, strlen(buff2));

	write(1, "\nBlocked_ticks: ", strlen("\nBlocked_ticks: "));
	itoa(st.blocked_ticks, buff2);
	write(1, buff2, strlen(buff2));

	write(1, "\nReady_ticks: ", strlen("\nReady_ticks: "));
	itoa(st.ready_ticks, buff2);
	write(1, buff2, strlen(buff2));

	write(1, "\nElapsed_total_ticks: ", strlen("\nElapsed_total_ticks: "));
	itoa(st.elapsed_total_ticks, buff2);
	write(1, buff2, strlen(buff2));

	write(1, "\nTotal_trans: ", strlen("\nTotal_trans: "));
	itoa(st.total_trans, buff2);
	write(1, buff2, strlen(buff2));

	write(1, "\nRemaining_ticks: ", strlen("\nRemaining_ticks: "));
	itoa(st.remaining_ticks, buff2);
	write(1, buff2, strlen(buff2));
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
	int f = fork();
	while(1){
		if (f != 0) {
			write(1, "padre\n", strlen("padre\n"));
		} else {
			write(1, "hijo\n", strlen("hijo\n"));
		}
	}
}