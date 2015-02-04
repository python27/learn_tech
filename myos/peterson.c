#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int flag[2] = {0, 0};
int turn = 0;

void* Callback00(void *p)
{
	do{
		// entry section
		flag[0] = 1;
		turn = 1;
		while (flag[1] && turn == 1);

		// critical section
		printf("I am pthread 00 ...\n");
		printf("I am pthread 00 in running\n");

		// exit section
		flag[0] = 0;

	}while(1);

}

void* Callback01(void *p)
{
	do{
		// entry section
		flag[1] = 1;
		turn = 0;
		while (flag[0] && turn == 0);
		
		// critical section
		printf("I am pthread 11 ...\n");
		printf("I am pthread 11 in running\n");

		// exit section
		flag[1] = 0;
		
	}while(1);

}

int main()
{
	pthread_t tid1, tid2;
	int err;

	printf("Start...\n");

	err = pthread_create(&tid1, NULL, Callback00, NULL);
	err = pthread_create(&tid2, NULL, Callback01, NULL);

	sleep(10);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
