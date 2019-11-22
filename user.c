#include <libc.h>
#include <stats.h>

int set_sched_policy(int policy);
int read (int fd, char *buf, int nbytes);



void print_stats(int pid){
	struct stats st;
	char buff2[40];

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

char buff[40];

int fib(int f){
	if (f <= 1) return 1;
	else return fib(f-1)+fib(f-2);
}

// CPU
void workload_1(){
	int pid;

	pid = fork();
	if (pid != 0) {
		pid = fork();
		if (pid != 0) pid = fork();
	}

	fib(32);

	if (pid > 0) print_stats(0);

	if (pid == 0) {
		print_stats(getpid());
		exit();
	}
	return;
}

// I/O
void workload_2(){
	int pid;

	pid = fork();

	if (pid != 0) {
		pid = fork();
		if (pid != 0) pid = fork();
	}


	read(0, 0, 300);

	if (pid > 0) print_stats(0);

	if (pid == 0) {
		print_stats(getpid());
		exit();
	}
	return;
}

// mix I/O and CPU
void workload_3(){
	int pid;

	pid = fork();

	if (pid != 0) {
		pid = fork();
		if (pid != 0) pid = fork();
	}

	read(0, 0, 500);
	fib(32);

	if (pid > 0) print_stats(0);

	if (pid == 0) {
		print_stats(getpid());
		exit();
	}
	return;
}

void workload_4(){
	int pid;

	read(0, 0, 500);

	print_stats(0);

	return;
}

int __attribute__ ((__section__(".text.main")))
  main(void)
{
	set_sched_policy(0);
	workload_3();
	while(1){
	}
}	