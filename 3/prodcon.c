#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#define SIZE 10

struct prc {
	sem_t full,empty;
	int buffer[SIZE],in,out;
	pthread_mutex_t lock;
}prc;

int item = 1;

void init() {
	prc.in = 0;
	prc.out = 0;
	sem_init(&prc.empty,0,10);
	sem_init(&prc.full,0,0);
	pthread_mutex_init(&prc.lock,NULL);
}

void *producer(void	*arg) {
	int i,j;
	i = *(int *) arg;
	while(1) {
		sleep(rand()%10);
		sem_wait(&prc.empty);
		pthread_mutex_lock(&prc.lock);
		printf("PRODUCER %d PRODUCED ITEM NO. %d \n",i,item);
		prc.buffer[(prc.in++)%10] = item++;
		pthread_mutex_unlock(&prc.lock);
		sem_post(&prc.full);
	}
}

void *consumer(void *arg) {
	int i,j,k,c=0;
	i = *(int *) arg;
	int value;
	while(1) {
		sleep(rand()%10);
		sem_wait(&prc.full);
		pthread_mutex_lock(&prc.lock);
		k = (prc.out++)%10;
		value = prc.buffer[k];
		prc.buffer[k] = 0;
		printf("CONSUMER %d CONSUMED ITEM NO. %d \n",i,value);
		pthread_mutex_unlock(&prc.lock);
		sem_post(&prc.empty);
	}
}

int main(void) {
	int prod,cons,i,*arg;
	pthread_t p[10],c[10];
	printf("ENTER NUMBER OF PRODUCERS : ");
	scanf("%d",&prod);
	printf("ENTER NUMBER OF CONSUMERS : ");
	scanf("%d",&cons);
	init();	
	for(i = 0;i < prod;i++) {
		arg = &i;
		pthread_create(&p[i],NULL,*producer,(void*)arg);
	}
	for(i = 0;i < cons;i++) {
		arg = &i;
		pthread_create(&c[i],NULL,*consumer,(void*)arg);
	}
	for(i = 0;i < prod;i++)
		pthread_join(p[i],NULL);
	for(i = 0;i < cons;i++)
		pthread_join(c[i],NULL);
}