/*
 *	Kendric Agdaca and Dazjuan Butler
 *	kagdaca and dbutler
 *	ECE 3220 Spring
 *	Due 4/1/22
 *	HM2
 */

#include <stdio.h>
#include <stdlib.h>

struct task
{
	int task_id;
	int arrival_time;
	int service_time;
	int remaining_time;
	int completion_time;
	int response_time;
	int wait_time;
	struct task *next;
};

void FIFO(FILE *file)
{
	int task_counter = 0;
	struct task *ptr = (struct task*)malloc(sizeof(struct task));
	ptr -> next = NULL;
	struct task *head = ptr;

	while (fscanf(file, "%d %d", &ptr->arrival_time,&ptr->service_time) == 2)
	{
		ptr->task_id = 'A' + task_counter;
//		printf("%d %d\n", ptr->arrival_time,ptr->service_time);
		ptr->remaining_time = ptr->service_time;
		task_counter++;

		if(feof(file)==0)
		{
			ptr->next = (struct task*)malloc(sizeof(struct task));
			ptr=ptr->next;
		}

		ptr->next=NULL;
	}
	ptr=head;	


	int i;
//	int count=1;
//	int wait = 0;

	struct task *temp;
	temp -> next = NULL;
	temp = head;

	while (temp != NULL)
	{
		ptr->wait_time= 0;


		if (temp-> next != NULL)
		{
			if (temp->arrival_time==temp->next->arrival_time)
			{
				ptr->next->wait_time = ptr -> service_time;
			}
		}


		for (i=0; i <= 15; i++)
		{

			if (temp -> arrival_time == i)
			{
				ptr ->response_time = ptr->service_time + ptr->wait_time;
				ptr ->completion_time = i + ptr->service_time + ptr->wait_time;
				printf("%d %d %d %d %d\n\n",ptr ->arrival_time,ptr->service_time,ptr->completion_time,ptr->response_time,ptr->wait_time);
			}
		}
		ptr = ptr ->next;
		temp = temp-> next;
	}

	//response time = service + wait	
}

void SJF()
{

}

void RR()
{

}

int main(int argc, char* argv[])
{
/*
	if (argc < 4)
	{
		printf("Too few arguments");
		exit(1);
	}
*/
	FILE *file = fopen(argv[2],"r");
	if (file == NULL)
	{
		printf("could not find file\n");
		exit(1);
	}
//do file open only in schedule function. Create separate function to create the tasks
	if (argv[1] == "-fifo" || "-FIFO")
	{
		FIFO(file);
	}
	if (argv[1] == "-sjf" || "-SJF")
	{
		SJF();
		//do i sort the tasks by service time first?
		//3 4
		//10 4
		//10 2
	}
	if (argv[1] == "-rr" || "-RR")
	{
		RR();
	}
	else
	{
		printf("Invalid scheduling option");
		exit(1);
	}
}
