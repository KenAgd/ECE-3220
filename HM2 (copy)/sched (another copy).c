/*
 *	Kendric Agdaca and Dazjuan Butler
 *	kagdaca and dbutler
 *	ECE 3220 Spring
 *	Due 4/1/22
 *	HM2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	ptr -> wait_time = 0;
	int i;

	for (i=1;i<=15;i++)
	{
		printf("%d\n",i);
	}


	printf("arrival time | service time | completion time | response time | wait time\n");

	while (ptr != NULL)
	{
//		ptr -> wait_time = 0;
		for(i = 1; i <= 15; i++)
		{
			if (ptr -> arrival_time == i)
			{
				ptr -> response_time = ptr -> service_time + ptr -> wait_time;
				ptr -> completion_time = ptr -> response_time + ptr -> arrival_time;
				printf("%d               %d               %d                  %d                %d\n\n",ptr->arrival_time,ptr->service_time,ptr->completion_time,ptr->response_time,ptr->wait_time);
			}
		}


		if (ptr -> next != NULL)
		{
			if ((ptr -> next -> arrival_time >= ptr -> arrival_time) & (ptr -> next -> arrival_time <= ptr -> completion_time))
			{
				ptr -> next -> wait_time = ptr -> completion_time - ptr -> next -> arrival_time;
			}
		}



		ptr -> wait_time = 0;
		ptr = ptr -> next;
	}


	//response time = service + wait	
}



void swap(struct task *a, struct task *b)
{
	int temp = a -> service_time;
	a -> service_time = b -> service_time;
	b -> service_time = temp;
}




void bubble(struct task *head)
{
	int swapped;
	struct task *temp1;
	struct task *temp2 = NULL;

	if (head == NULL)
	{
		return;
	}

	do
	{
		swapped = 0;
		temp1 = head;

		while (temp1 -> next !=  temp2)
		{
			if (temp1 -> service_time > temp1 -> next -> service_time)
			{
				swap(temp1, temp1 -> next);
				swapped = 1;
			}

			temp1 = temp1 -> next;
		}
		temp2 = temp1;
	}
	while (swapped);
}


void SJF(FILE *file)
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

	bubble(head);

	ptr=head;	
	ptr -> wait_time = 0;
	int i;

	for (i=1;i<=15;i++)
	{
		printf("%d\n",i);
	}


	printf("arrival time | service time | completion time | response time | wait time\n");

	while (ptr != NULL)
	{
//		ptr -> wait_time = 0;
		for(i = 1; i <= 15; i++)
		{
			if (ptr -> arrival_time == i)
			{
				ptr -> response_time = ptr -> service_time + ptr -> wait_time;
				ptr -> completion_time = ptr -> response_time + ptr -> arrival_time;
				printf("%d               %d               %d                  %d                %d\n\n",ptr->arrival_time,ptr->service_time,ptr->completion_time,ptr->response_time,ptr->wait_time);
			}
		}


		if (ptr -> next != NULL)
		{
			if ((ptr -> next -> arrival_time >= ptr -> arrival_time) & (ptr -> next -> arrival_time <= ptr -> completion_time))
			{
				ptr -> next -> wait_time = ptr -> completion_time - ptr -> next -> arrival_time;
			}
		}



		ptr -> wait_time = 0;
		ptr = ptr -> next;
	}



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
	else if (strcmp(argv[1], "-fifo") || strcmp(argv[1], "-FIFO"))
	{
		FIFO(file);
	}
	else if (strcmp(argv[1], "-sjf") || strcmp(argv[1], "-SJF"))
	{
		SJF(file);
		//do i sort the tasks by service time first?
		//3 4
		//10 4
		//10 2
	}
	else if (strcmp(argv[1], "-rr") || strcmp(argv[1], "-RR"))
	{
		RR();
	}
	else
	{
		printf("Invalid scheduling option");
		exit(1);
	}
}
