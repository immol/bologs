#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t blank,xfull;
#define _SEM_CNT_ 5
int queue[_SEM_CNT_];
int beginnum=100;
void *thr_producter(void*arg){
	int i=0;
	while(1){
		sem_wait(&blank);
		printf("---%s---self=%lu---num---%d\n",__FUNCTION__,pthread_self(),beginnum);
		queue[(i++)%_SEM_CNT_]=beginnum++;
		sem_post(&xfull);
		sleep(rand()%3);
	}
	return NULL;
}
void *thr_customer(void*arg){
	int i=0;
	int num=0;
	while(1){
		sem_wait(&xfull);
		num=queue[(i++)%_SEM_CNT_];
		printf("---%s---self=%lu---num---%d\n",__FUNCTION__,pthread_self(),num);

		sem_post(&blank);
	}
	return NULL;
}

int main(){
	sem_init(&blank,0,_SEM_CNT_);
	sem_init(&xfull,0,0);
	pthread_t tid[2];
	pthread_create(&tid[0],NULL,thr_producter,NULL);
	pthread_create(&tid[0],NULL,thr_customer,NULL);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	sem_destroy(&blank);
	sem_destroy(&xfull);
	return 0;
}
