#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
void input(int **,int,int);
void display(int **,int,int);
void mul(int **,int **,int **,int,int,int);
void *process(void *arg);
typedef struct matrix
{	int r,c,v;
	int **a,**b;
}matrix;
int main(void)
{	int **a,**b,**c,r1,c1,r2,c2,i=0,j=0,sum=0;
	printf("enter order of matrix 1:");
	scanf("%d%d",&r1,&c1);
	printf("\nenter order of matrix 2:");
	scanf("%d%d",&r2,&c2);
	if(c1!=r2)
	{	exit(0);
	}
	a=(int **)malloc(r1*sizeof(int *));
	c=(int **)malloc(r1*sizeof(int *));
	for(i=0;i<r1;i++)
	{	a[i]=(int *)malloc(sizeof(int)*c1);
		c[i]=(int *)malloc(sizeof(int)*c2);
	}
	b=(int **)malloc(r2*sizeof(int *));
	for(i=0;i<r2;i++)
		b[i]=(int *)malloc(sizeof(int)*c2);
	printf("\nEnter Matrix 1:\n");
	input(a,r1,c1);
	printf("\nEnter Matrix 2:\n");
	input(b,r2,c2);
	printf("\nMatrix 1:\n");
	display(a,r1,c1);
	printf("Matrix 2:\n");
	display(b,r2,c2);
	mul(a,b,c,r1,c2,r2);
	printf("\nMatrix 3:\n");
	display(c,r1,c2);
	for(i=0;i<r1;i++){
		for(j=0;j<c2;j++){
			sum+=*(*(c+i)+j);
		}
	}
	printf("\nThe sum of Elements :%d\n",sum);
	return 0;
}
void input(int **p,int r,int c)
{	int i,j;
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{	printf("Matrix[%d][%d]:",i,j);
			scanf("%d",(*(p+i)+j));
		}

}
void display(int **p,int r,int c)
{	int i,j;
	for(i=0;i<r;i++)
	{	for(j=0;j<c;j++)
			printf("%d ",*(*(p+i)+j));
		printf("\n");
	}
}
void mul(int **p,int **q,int **s,int r,int c,int h)
{	int i,j,res,c1=0;
	pthread_t *a=(pthread_t *)malloc(r*c*sizeof(pthread_t));
	matrix *tp;
	void *temp;
	for(i=0;i<r;i++)
	{	for(j=0;j<c;j++)
		{	tp=(matrix *)malloc(sizeof(matrix));
			tp->r=i;
			tp->c=j;
			tp->v=h;
			tp->a=p;
			tp->b=q;
			printf("\nCreating Thread :%d",c1+1);
			res=pthread_create(&a[c1],NULL,&process,(void *)tp);
			sleep(1);
			if(res!=0)
			{	perror("thread creation failed");
				exit(0);
			}
			c1++;
		}
	}
	c1--;
	while(c1>=0)
	{	res=pthread_join(a[c1],&temp);
		sleep(1);
		if(res!=0)
		{	perror("thread join failed");
			exit(0);
		}
		tp=(matrix *)temp;
		printf("\nReceived value for row %d column %d := %d",tp->r+1,tp->c+1,tp->v);
		s[tp->r][tp->c]=tp->v;
		c1--;
	}
}
void *process(void *arg)
{	
	matrix *m;
	m=arg;
	int i=m->r,j=m->c,k,sum=0;
	for(k=0;k<m->v;k++)
		sum+= m->a[i][k] * m->b[k][j] ;
	printf("\nCalculating value of row %d and column %d : sum = %d",(m->r+1),(m->c+1),sum);
	matrix *m1=(matrix *)malloc(sizeof(matrix));
	m1->r=m->r;
	m1->c=m->c;
	m1->v=sum;
	pthread_exit((void *)m1);
}
