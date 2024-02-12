/*
 *	Kendric Agdaca and Dazjuan Butler
 *	kagdaca and dbutler
 *	ECE 3220 Spring
 *	Due 2/25/22
 *	HM1
 *
 *	Purpose: This program takes 3 user inputs: num1, num2, and a char message less than 20 char. One child is then spawned and should run area.c. Another child is then spawned and should perimeter.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/wait.h>


struct Inputs
{
	int num1;
	int num2;
	char message[21];
}Input;


void *ratio()
{
	int R = Input.num1 / Input.num2;
	int *RatioResult = malloc(sizeof(int));
	*RatioResult = R;
	pthread_t ratio_id = pthread_self();
	printf("Thread 1: tig %ld, ratio is %d\n", ratio_id, (int)R);
	pthread_exit((void*)RatioResult);
}


void *reverse()
{
	sleep(1);
	char *a = malloc(21);
	strcpy(a, Input.message);
	int len = strlen(a);
	int i;
	char *start, *end, ch;


	start = a;
	end = a;

	for (i = 0; i < len-1; i++)
	{
		end++;
	}

	for (i = 0; i < (len/2); i++)
	{
		ch = *end;
		*end = *start;
		*start = ch;
		start++;
		end--;
	}	


	pthread_t reverse_id =pthread_self();
	printf("Thread 2: tig %ld, message is \"%s\"\n", reverse_id, a);
	pthread_exit((void*)a);
}


int main (int argc, char* argv[])
{
	if (argc < 4)
	{
	printf("Too few arguments");
	exit(1);
	}

	pthread_t thread1Id;
	pthread_t thread2Id;

	Input.num1 = atoi(argv[1]);
	Input.num2 = atoi(argv[2]);
	strcpy(Input.message, argv[3]);


	int child1 = fork();

	if (child1 == 0)
	{
		printf("Child1: pid: %d, ppid %d, ", getpid(), getppid());
		fflush(stdout);
		execl("./area", "area",argv[1], argv[2], NULL);

	}
	else
	{
		int child2 = fork();

		if (child2 == 0)
		{
			sleep(1);
			printf("Child2: pid: %d, ppid %d, ", getpid(), getppid());
			fflush(stdout);
			execl("./perimeter", "perimeter", argv[1], argv[2], NULL);
		}

		else//parent process
		{
			
			int *t;
			char *b;
			sleep(2);
			wait(NULL);
			pthread_create(&thread1Id, NULL, &ratio, NULL);
			pthread_create(&thread2Id, NULL, &reverse, NULL);

			pthread_join(thread1Id, (void **)&t);
			pthread_join(thread2Id, (void **)&b);
			printf("Parent: pid %d, ratio: %d, message: \"%s\"\n", getpid(), *t, b);

			free(t);
			free(b);
		}
	}
}


