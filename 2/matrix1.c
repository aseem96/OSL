/*
 ============================================================================
 Name        : matrix1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int a[10][10],b[10][10];
long int c[10][10];
void accept(int a[10][10],int row,int col)
{
	int i,j;
	printf("\n ENTER THE ELEMENTS OF MATRIX:\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
}
void display(int a[10][10],int row,int col)
{
	int i,j;
	printf("\n MATRIX IS:->\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			printf("%d\t",a[i][j]);
		}
		printf("\n");
	}
}
void *mult_thread(void *arg)
{
	int row,col,i,*rcArgs;
	rcArgs=(int *)arg;
	long int return_val;
	row=rcArgs[0];
	col=rcArgs[1];
	i=rcArgs[2];
	return_val=a[row][i]*b[i][col];
	pthread_exit((void*)return_val);
}
int main()
{
	int rowa,cola,rowb,colb,rcArgs[3],i,j,k,*status,count=0;
	pthread_t P[10][10][10];

	printf("\nENTER THE ROWS OF MATRIX A:->\n");
	scanf("%d",&rowa);
	printf("\nENTER THE COLS OF MATRIX A:->\n");
	scanf("%d",&cola);
	accept(a,rowa,cola);
	display(a,rowa,cola);

	printf("\nENTER THE ROWS OF MATRIX B:->\n");
	scanf("%d",&rowb);
	printf("\nENTER THE COLS OF MATRIX B:->\n");
	scanf("%d",&colb);
	accept(b,rowb,colb);
	display(b,rowb,colb);

	if(cola==rowb)
	{
		for(i=0;i<rowa;i++)
		{
			for(j=0;j<colb;j++)
			{
				printf("\nCREATING THREAD->%d",count+1);
				for(k=0;k<cola;k++)
				{
					rcArgs[0]=i;
					rcArgs[1]=j;
					rcArgs[2]=k;
					if(pthread_create(&P[i][j][k],NULL,mult_thread,rcArgs)!=0)
					{
						printf("\nTHREAD CANNOT BE CREATED...\n");
					}
					else
					{
						sleep(1);
					}
				}
				count++;
			}
		}
	}
	else
	{
		printf("\nMULTIPLICATION IS NOT POSSIBLE...\n");
		exit(1);
	}
	for(i=0;i<rowa;i++)
	{
		for(j=0;j<colb;j++)
		{
			for(k=0;k<cola;k++)
			{
				if(pthread_join(P[i][j][k],(void**)&status)!=0)  //remember ** and &status is return value
					perror("\nJOIN CANNOT BE CREATED..\n");
				c[i][j]+=(long int)status;
			}
		}
	}
	printf("\nTHE RESULTANT MATRIX IS->\n");
	int sum=0;
	for(i=0;i<rowa;i++)
	{
		for(j=0;j<colb;j++)
		{
			printf("%2ld\t",c[i][j]);
			sum+=c[i][j];
		}
		printf("\n");
	}
	printf("\nFINAL SUM IS->%d",sum);
return 0;
}
