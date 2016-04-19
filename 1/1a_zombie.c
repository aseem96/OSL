#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h>    
#include <stdlib.h>    
#include <unistd.h>

int main(void) {
	int pid;
	printf("BEGIN EXECUTION...\n\n");
	printf("IN PARENT PROCESS | PROCESS ID : %d",getpid());
	printf("\nFORKING...\n");
	pid = fork();
	if(pid == 0) {
		printf("\nIN CHILD PROCESS | MY PROCESS ID : %d",getpid());
		printf("\nMY PARENT PROCESS ID : %d",getppid());
		printf("\nCHILD PROCESS | I AM DYING NOW...");
		printf("\n-------------------------------------------\n");
		system("ps -elf | grep a.out");
	}
	else if(pid > 0) {
		printf("\nIN PARENT PROCESS | MY PROCESS ID : %d",getpid());
		printf("\nPARENT PROCESS | MY CHILD PROCESS ID IS : %d",pid);
		printf("\nPARENT POCESS | I AM SLEEPING NOW...");
		sleep(10);
		printf("\n-------------------------------------------\n");
		system("ps -elf | grep a.out");
	}
}