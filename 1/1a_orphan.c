#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int cmpfunc(const void * a, const void * b) {
   return (*(int*)a - *(int*)b);
}

int main(void) {
	int a[10],pid,ppid,size,i;
	printf("\nParent | My process id is : %d",getpid());
	printf("\nEnter the size of array : ");
	scanf("%d",&size);
	printf("\nEnter %d elements : ",size );
	for(i = 0;i < size;i++)
		scanf("%d",&a[i]);
	// forking
	printf("\nForking...\n");
	pid = fork();
	if(pid == 0) {
		// child process
		printf("\nChild | My process id is : %d",getpid());
		printf("\nChild | My parent process pid is : %d\n",getppid());
		qsort(a,size,sizeof(int),cmpfunc);
		for(i = 0;i < size;i++)
			printf("%d  ",a[i]);
		printf("\n");
		printf("\nChild | I am dying now..\n");
		// Orphan
		printf("\nI am sleeping now...");
		sleep(10);
		system("ps -elf | grep a.out");
	}
	else if(pid > 0) {
		system("wait");		
		printf("\nParent | I am parent...");
		printf("\nMy process pid is : %d",getpid());
		partition(a,0,size-1);
		printf("\nThe sorted array | parent :\n");
		for(i = 0;i < size;i++)
			printf("%d  ",a[i]);
		printf("\n");
		// Orphan
		system("ps -elf | grep a.out");
		exit(0);
	}
}

void partition(int a[10],int low,int high) {
	int mid;
	if(low < high) {
		mid = (low+high)/2;
		partition(a,low,mid);
		partition(a,mid+1,high);
		merge(a,low,mid,high);
	}
}

void merge(int a[10],int low,int mid,int high) {
	int i,m,k,l,temp[10];
	l=low;
	i=low;
	m=mid+1;
	while((l<=mid)&&(m<=high)){
		if(a[l]<=a[m]){
			temp[i]=a[l];
			l++;
		}
		else{
			temp[i]=a[m];
			m++;
		}
		i++;
	}
	if(l>mid){
		for(k=m;k<=high;k++){
			temp[i]=a[k];
			i++;
		}
	}
	else{
		for(k=l;k<=mid;k++){
			temp[i]=a[k];
			i++;
		}
	}
	for(k=low;k<=high;k++){
		a[k]=temp[k];
	}
}