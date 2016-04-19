#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define MAX 100

sem_t eat[MAX];
sem_t room;
pthread_t pid[MAX];

void init() {
	int i;
	for(i = 0;i < 5;i++)
		sem_init(&eat[i],0,1);
	sem_init(&room,0,4);
}

void* philospher(void* arg) {
	int p = *(int *) arg;
	while(1) {
		sem_wait(&room);
		printf("PHILOSOPHER %d IS HUNGRY\n",p);
		sem_wait(&eat[p]);
		sem_wait(&eat[(p+1)%5]);
		printf("PHILOSOPHER %d IS EATING\n",p);
		sleep(2);
		printf("PHILOSOPHER %d IS DONE EATING, NOW THINKING\n",p);
		sem_post(&eat[(p+1)%5]);
		sem_post(&eat[p]);
		sem_post(&room);
		sleep(2);
	}
}

int main(void) {
	int i;
	int c[] = {0,1,2,3,4};
	init();
	for(i = 0;i < 5;i++)
		pthread_create(&pid[i],NULL,philospher,&c[i]);
	for(i = 0;i < 5;i++)
		pthread_join(pid[i],NULL);
}