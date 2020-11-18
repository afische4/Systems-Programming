#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int num_run;

void handle_sigusr1(int sig, siginfo_t *siginfo, void *context)
{
	num_run++;
	printf("got signal %d, from pid %d uid %d num_run %d\n", sig, siginfo->si_pid, siginfo->si_uid, num_run);
}

int main()
{
	num_run = 0;

	int pid = getpid();
	printf("my pid %d\n", pid);

	struct sigaction act1;
	act1.sa_sigaction = &handle_sigusr1;
	act1.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &act1, NULL);
	while(1) { }
	return 0;
}

