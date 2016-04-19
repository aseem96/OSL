#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler() {
	int status,id;
	while(1) {
		sleep(1);
		id = waitpid(-1,&status,1);
		if(id <= 0)
			break;
		printf("\nCHILD REAPED | PID : %d",id);
	}
	printf("\n");
}

int main(void) {
	int i,n,pid;
	signal(SIGCHLD,handler);
	printf("ENTER NUMBER OF CHILD PROCESSES : ");
	scanf("%d",&n);
	for(i = 0;i < n;i++) {
		sleep(1);
		pid = fork();
		if(pid == 0) {
			sleep(1);
			printf("\nCHILD PROCESS WITH ID %d PRODUCED\n",getpid());
			sleep(1);
			return;
		}
	}
	sleep(10);
}