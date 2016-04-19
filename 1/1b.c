#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#define MAX 20

int cmpfunc(const void * a,const void * b) {
	return (*(int*)a - *(int*)b);
}

int main(void) {
	int a[MAX],pid,size,i,j,k;
	char *argv[15],str[15];
	printf("BEGIN EXECUTION...\n");
	printf("\nENTER THE SIZE OF ARRAY : ");
	scanf("%d",&size);
	printf("\nENTER %d ELEMENTS : ",size);
	for(i = 0;i < size;i++)
		scanf("%d",&a[i]);
	printf("\nARRAY TO SORT : ");
	for(i = 0;i < size;i++)
		printf("%d ",a[i]);
	printf("\nIN PARENT PROCESS | SORTING...\n");
	qsort(a,size,sizeof(int),cmpfunc);
	printf("\nSORTED ARRAY IS : ");
	for(i = 0;i < size;i++)
		printf("%d ",a[i]);
	printf("\nIN PARENT PROCESS | PARENT PROCESS ID : %d",getpid());
	pid = fork();
	if(pid == 0) {
		printf("\nIN CHILD PROCESS | MY PROCESS ID : %d",getpid());
		printf("\nMY PARENT PROCESS ID : %d",getppid());
		for(k = 0;k < size;++k) {
			sprintf(str,"%d",a[k]);
			argv[k] = (char*)malloc(sizeof(str));
			strcpy(argv[k],str);
		}
		argv[k] = NULL;
		execv("./1b_binarys",argv);
		printf("execv failed");
	}
	else {
		sleep(10);
		wait();
		printf("\nIN PARENT\n");
	}
}
