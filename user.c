#include <libc.h>
#include <stats.h>

int set_sched_policy(int policy);
int read (int fd, char *buf, int nbytes);

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

int pid;
char buff[40];

int fib(int f){
	if (f <= 1) return 1;
	else return fib(f-1)+fib(f-2);
}

void workload_1(){
	int ret1, ret2, ret3; //fill 1, fill 2, fill 3 (3, 4, 5)

	ret1 = fork();
	if (ret1 != 0) {
		ret2 = fork();
		if (ret2 != 0) ret3 = fork();
	}

	fib(30);

	if (ret1 != 0 && ret2 != 0 && ret3 != 0){

		print_stats(ret1);
		print_stats(ret2);
		print_stats(ret3);
		print_stats(0);
	}
}

void workload_2(){

}

void workload_3(){

}


int __attribute__ ((__section__(".text.main")))
  main(void)
{
	set_sched_policy(0);
	workload_1();











































































	while(1){
	}

}