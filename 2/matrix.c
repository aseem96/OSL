#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX 10

int a[MAX][MAX],b[MAX][MAX];
long int c[MAX][MAX];
int r1,c1,r2,c2;

void accept_matrix(int a[MAX][MAX],int r,int c) {
	int i,j;
	for(i = 0;i < r;i++)
		for(j = 0;j < c;j++)
			scanf("%d",&a[i][j]);
}

void display_matrix(int a[MAX][MAX],int r,int c) {
	int i,j;
	for(i = 0;i < r;i++) {
		for(j = 0;j < c;j++)
			printf("%d\t",a[i][j]);
		printf("\n");
	}
}

void *mult_thread(void *arg) {
	int r,c,i,*rc_args;
	long int ret_val;
	rc_args = (int *)arg;
	r = rc_args[0];
	c = rc_args[1];
	i = rc_args[2];
	ret_val = a[r][i] * b[i][c];
	pthread_exit((void*)ret_val);
}

int main(void) {
	pthread_t p[10][10][10];
	int i,j,k,count = 0,*status,rc_args[3],sum;
	printf("ENTER ORDER OF MATRIX A (row col) : ");
	scanf("%d%d",&r1,&c1);
	printf("\nENTER MATRIX A : \n");
	accept_matrix(a,r1,c1);
	printf("\nENTER ORDER OF MATRIX B (row col) : ");
	scanf("%d%d",&r2,&c2);
	printf("\nENTER MATRIX B : \n");
	accept_matrix(b,r2,c2);
	printf("\nMATRIX A : \n");
	display_matrix(a,r1,c1);
	printf("\nMATRIX B : \n");
	display_matrix(b,r2,c2);
	if(c1 != r2)
		printf("\nMULTIPLICATION NOT POSSIBLE!\n");
	else {
		for(i = 0;i < r1;i++) {
			for(j = 0;j < c2;j++) {
				printf("\nCREATING THREAD : %d",count+1);
				for(k = 0;k < c1;k++) {
					rc_args[0] = i;
					rc_args[1] = j;
					rc_args[2] = k;
					pthread_create(&p[i][j][k],NULL,mult_thread,rc_args);
					sleep(1);
				}
				count++;
			}
		}
	}
	for(i = 0;i < r1;i++) {
		for(j = 0;j < c2;j++) {
			for(k = 0;k < c1;k++) {
				pthread_join(p[i][j][k],(void**)&status);
				c[i][j] += (long int)status;
			}
		}
	}
	sum = 0;
	printf("\n\nTHE RESULT IS : \n\n");
	for(i = 0;i < r1;i++) {
		for(j = 0;j < c2;j++) {
			printf("%2ld\t",c[i][j]);
			sum += c[i][j];
		}
		printf("\n");
	}
	printf("\nFINAL SUM IS : %d\n",sum);
}