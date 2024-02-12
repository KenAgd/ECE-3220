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


struct task *swap(struct task *a, struct task *b)
{
	struct task *temp = b -> next;
	b -> next = a;
	a -> next = temp;
	return b;
}

/*
void ResponseBubble(struct task **head, int count)
{
	struct task **temp;
	int i,j,swapped;
	
	for (i=0;i<=count;i++)
	{
		temp = head;
		swapped=0;
		
		for (j=0;j<count-i-1;j++)
		{
			struct task *p1=*temp;
			struct task *p2=p1->next;
			
			if (p1->response_time > p2->response_time)
			{
				*temp=swap(p1,p2);
				swapped=1;
			}
			
			temp=&(*temp)->next;
		}
		
		if(swapped==0)
		{
			break;
		}
	}
}
*/
void ServiceBubble(struct task **head, int count)
{
	struct task **temp;
	int i, j, swapped;
	
	for (i=0; i<=count; i++)
	{
		temp = head;
		swapped = 0;
		
		for (j=0; j<count-i-1; j++)
		{
			struct task *p1=*temp;
			struct task *p2=p1 -> next;
			
			if (p1 -> service_time > p2 -> service_time)
			{
				*temp = swap(p1,p2);
				swapped = 1;
			}
			
			temp = &(*temp) -> next;
		}
		
		if(swapped == 0)
		{
			break;
		}
	}
}







void FIFO(FILE *fileR, FILE *fileW)
{
	fprintf(fileW,"FIFO scheduling results\n");
	int task_counter = 0;
	struct task *ptr = (struct task*)malloc(sizeof(struct task));
	ptr -> next = NULL;
	struct task *head = ptr;

	while (fscanf(fileR, "%d %d", &ptr -> arrival_time, &ptr -> service_time) == 2)
	{
		ptr -> task_id = 'A' + task_counter;
		ptr -> remaining_time = ptr -> service_time;
		task_counter++;

		if(feof(fileR) == 0)
		{
			ptr -> next = (struct task*)malloc(sizeof(struct task));
			ptr = ptr -> next;
		}

		ptr -> next=NULL;
	}
	ptr = head;	
	ptr -> wait_time = 0;
	int i;


	fprintf(fileW,"tid | arrival time | service time | completion time | response time | wait time\n");
	fprintf(fileW,"-------------------------------------------------------------------------------\n");
	while (ptr != NULL)
	{
//		ptr -> wait_time = 0;
		for(i = 1; i <= 15; i++)
		{
			if (ptr -> arrival_time == i)
			{
				ptr -> response_time = ptr -> service_time + ptr -> wait_time;
				ptr -> completion_time = ptr -> response_time + ptr -> arrival_time;
				fprintf(fileW,"%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",ptr->task_id,ptr->arrival_time,ptr->service_time,ptr->completion_time,ptr->response_time,ptr->wait_time);
			}
		}


		if (ptr -> next != NULL)
		{
			if ((ptr -> next -> arrival_time >= ptr -> arrival_time) & (ptr -> next -> arrival_time <= ptr -> completion_time))
			{
				ptr -> next -> wait_time = ptr -> completion_time - ptr -> next -> arrival_time;
			}
		}
		ptr = ptr -> next;
	}
	
	ptr=head;
	//cpu table
	

/*	
	//tid table
	ptr=head;
	fprintf(fileW,"tid | arrival time | service time | completion time | response time | wait time\n");
	printf("-------------------------------------------------------------------------------\n");
	for (i=0;i<task_counter;i++)
	{
		fprintf(fileW,"%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",ptr->task_id,ptr->arrival_time,ptr->service_time,ptr->completion_time,ptr->response_time,ptr->wait_time);
		ptr=ptr->next;
	}*/
	
	//summary table
	ServiceBubble(&head,task_counter);	
	ptr = head;
	fprintf(fileW,"\nservice time | wait time\n");
	fprintf(fileW,"------------------------\n");
	for (i=0; i<task_counter; i++)
	{
		fprintf(fileW,"%d\t\t%d\n",ptr->service_time,ptr->wait_time);
		ptr = ptr -> next;
	}		
}


void tidBubble(struct task **head, int count)
{
	struct task **temp;
	int i, j, swapped;
	
	for (i=0; i<=count; i++)
	{
		temp = head;
		swapped = 0;
		
		for (j=0; j<count - i - 1; j++)
		{
			struct task *p1 = *temp;
			struct task *p2 = p1 -> next;
			
			if (p1 -> task_id > p2 -> task_id)
			{
				*temp = swap(p1,p2);
				swapped = 1;
			}
			
			temp = &(*temp) -> next;
		}
		
		if(swapped == 0)
		{
			break;
		}
	}
}

void SJF(FILE *fileR,FILE*fileW)
{
	fprintf(fileW,"SJF scheduling results\n");
	int task_counter = 0;
	struct task *ptr = (struct task*)malloc(sizeof(struct task));
	ptr -> next = NULL;
	struct task *head = ptr;
	int cpu_time = 0;


	while (fscanf(fileR, "%d %d", &ptr->arrival_time, &ptr -> service_time) == 2)
	{
		ptr -> task_id = 'A' + task_counter;
		ptr -> remaining_time = ptr -> service_time;
		ptr -> response_time = ptr -> service_time;
		task_counter++;

		if(feof(fileR) == 0)
		{
			ptr -> next = (struct task*)malloc(sizeof(struct task));
			ptr = ptr -> next;
		}

		ptr -> next=NULL;
	}
	ptr = head;	

	struct task *min;
	int i;
	int end = 0;
	
	while (ptr -> next != NULL)
	{
		ptr = ptr -> next;
	}
	ptr -> remaining_time = 9999;
	
	struct task *last = ptr;
	
	int count = 0;
	
	for (int time = 0;count != task_counter; time++)
	{
		min = last;
		ptr = head;
		
		for(i=0; i < task_counter; i++)
		{
			if(ptr -> arrival_time <= time && ptr -> remaining_time < min -> remaining_time && ptr -> remaining_time > 0)
			{
				min = ptr;
			}
			ptr = ptr -> next;
		}
		min -> remaining_time--;
		
		if (min -> remaining_time == 0)
		{
			count++;
			end = time+1;
			min -> completion_time = end;
			min -> wait_time = end - min -> arrival_time - min -> service_time;
			min -> response_time = end - min -> arrival_time;

			if (cpu_time <= min -> completion_time)
			{
				cpu_time = min -> completion_time;
			}
		}
		

	}
	/*
	printf("highest Cpu time: %d\n", cpu_time);
	ptr=head;
	//cpu table
	printf("tid | cpu | ready | queue | response time | wait time\n");
	printf("-------------------------------------------------------------------------------\n");	
	for (i=0;i<cpu_time;i++)
	{
		
	}*/

	
	//tid table
	ptr = head;
	fprintf(fileW,"tid | arrival time | service time | completion time | response time | wait time\n");
	fprintf(fileW,"-------------------------------------------------------------------------------\n");
	for (i=0; i < task_counter; i++)
	{
		fprintf(fileW,"%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",ptr -> task_id, ptr -> arrival_time, ptr -> service_time, ptr -> completion_time, ptr -> response_time, ptr -> wait_time);
		ptr = ptr -> next;
	}
	
	//summary table
	ServiceBubble(&head,task_counter);	
	ptr = head;
	fprintf(fileW,"\nservice time | wait time\n");
	fprintf(fileW,"------------------------\n");
	for (i=0; i < task_counter; i++)
	{
		fprintf(fileW,"%d\t\t%d\n",ptr -> service_time, ptr->wait_time);
		ptr = ptr->next;
	}
}



void RR(FILE *fileR, FILE *fileW)
{

	fprintf(fileW,"RR scheduling results\n");
	int task_counter = 0;
	struct task *ptr = (struct task*)malloc(sizeof(struct task));
	ptr -> next = NULL;
	struct task *head = ptr;

	while (fscanf(fileR, "%d %d", &ptr -> arrival_time, &ptr -> service_time) == 2)
	{
		ptr -> task_id = 'A' + task_counter;
		ptr -> remaining_time = ptr -> service_time;
		ptr -> response_time = ptr -> service_time;
		task_counter++;

		if(feof(fileR) == 0)
		{
			ptr -> next = (struct task*)malloc(sizeof(struct task));
			ptr = ptr -> next;
		}

		ptr -> next=NULL;
	}
	ptr = head;	
	while (ptr != NULL)
	{
		for(int i = 1; i <= 15; i++)
		{
			if (ptr -> arrival_time == i)
			{
				ptr -> response_time = ptr -> service_time + ptr -> wait_time;
				ptr -> completion_time = ptr -> response_time + ptr -> arrival_time;
			}
		}


		if (ptr -> next != NULL)
		{
			if ((ptr -> next -> arrival_time >= ptr -> arrival_time) & (ptr -> next -> arrival_time <= ptr -> completion_time))
			{
				ptr -> next -> wait_time = ptr -> completion_time - ptr -> next -> arrival_time;
			}
		}
		ptr = ptr -> next;
	}

	int j, flag=0, tq=1, it=0, time=0;
	ptr = head;
	struct task *robin, *a;
	robin = head;		
	do
	{
		j = 0;
		flag = 0;
		 
		for(a = robin; a -> next != NULL; a = a -> next)
		{
			if ((a -> arrival_time <= time) && (a -> remaining_time > 0))
			{
				j = 1;
				time = time + tq;
				
				if(a -> remaining_time < tq)
				{
					time = time - (tq - a -> remaining_time);
				}
				a -> remaining_time = a -> remaining_time - tq;
				a -> completion_time = time;
			}
		}
		
		if (j == 0)
		{
			it = it + 1;
			time = time + 1;
		}
		
		for(a = robin; a -> next != NULL; a = a-> next)
		{
			if(a -> remaining_time > 0)
			{
				flag = 1;
			}
		}
	}while(flag == 1);
	fprintf(fileW,"tid | arrival time | service time | completion time | response time | wait time\n");
	fprintf(fileW,"-------------------------------------------------------------------------------\n");
	
	ptr = head;
	while(ptr != NULL)
	{
		fprintf(fileW,"%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",ptr -> task_id, ptr -> arrival_time, ptr -> service_time, ptr -> completion_time, ptr -> response_time, ptr -> wait_time);		
		ptr = ptr -> next;
	}
	
}

int main(int argc, char* argv[])
{

	if (argc < 4)
	{
		printf("Too few arguments");
		exit(1);
	}

	
	FILE *fileR = fopen(argv[2],"r");
	FILE *fileW = fopen(argv[3],"w");
	if (fileR == NULL)
	{
		printf("could not find file\n");
		exit(1);
	}
//do file open only in schedule function. Create separate function to create the tasks
	if (strcmp(argv[1], "-fifo") == 0 || strcmp(argv[1], "-FIFO")==0)
	{
		FIFO(fileR,fileW);
	}
	else if (strcmp(argv[1], "-sjf") ==0|| strcmp(argv[1], "-SJF")==0)
	{
		SJF(fileR,fileW);
	}
	else if (strcmp(argv[1], "-rr") ==0|| strcmp(argv[1], "-RR")==0)
	{
		RR(fileR,fileW);
	}
	else
	{
		printf("Invalid scheduling option");
		exit(1);
	}
}
