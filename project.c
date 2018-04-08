#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int n,i,j;
int q1=0,q2=0,q3=0;
struct processs
{
	int pid;
	int burst_time;
	int arrival_time;
	int priority;
}*p_array,*queue_one, *queue_two, *queue_thr;

//******************************************************************************************************
void pid_assign(struct processs *pp_array);				//function to assign process id
void burst_assign(struct processs *pp_array);			//function to assign burst time
void arrival_assign(struct processs *pp_array);			//function to assign arrival time
void priority_assign(struct processs *pp_array);		//function to assign priority
//------------------------------------------------------------------------------------------------------
void display(struct processs *pp_array,int k);			//function to display all processes
//------------------------------------------------------------------------------------------------------
void queue_size(struct processs *pp_array);				//function to determine the size of each queue
void queue_assign(struct processs *pp_array);			//function for assigning queue
void sort_arrival(struct processs *pp_array,int k);		//sorts the processes based on arrival time
//------------------------------------------------------------------------------------------------------
void sheduling(struct processs *queue_1, struct processs *queue_2, struct processs *queue_3); //function to schedule the processes
//******************************************************************************************************

//**************************************MAIN************************************************************
int main()
{
	system("cls");	

	printf("\nNumber of Processes : ");scanf("%d",&n);					//asking for number of processes
	p_array=(struct processs*)calloc(n,sizeof(struct processs));		//allocating number of processes
	
	pid_assign(p_array);												//asking PID
	burst_assign(p_array);												//asking BURST_TIME
	arrival_assign(p_array);											//asking ARRIVAL_TIME
	priority_assign(p_array);											//asking PRIORITY
	system("cls");
	printf("\nNumber of Processes : %d",n);
	display(p_array,n);													//displaying PROCESSES along with BURST TIME and ARRIVAL TIME and PRIORITY
	
	queue_size(p_array);												//determining size of each queue q1,q2,q3
	queue_one=(struct processs*)calloc(q1,sizeof(struct processs));		//allocating memory to queue_one
	queue_two=(struct processs*)calloc(q2,sizeof(struct processs));		//allocating memory to queue_two
	queue_thr=(struct processs*)calloc(q3,sizeof(struct processs));		//allocating memory to queue_thr
	queue_assign(p_array);												//assigning processes to respective queue
	
	printf("\nDividing processes on basis of PRIORITY...");
	printf("\n\nPRIORITY\t\tQUEUE\n");
	printf(" [1,3]\t\t\t Q1\n [4,7]\t\t\t Q2\n[8, 10]\t\t\t Q3\n");
	
	printf("\nThe generated QUEUES are :");
	printf("\n\nQUEUE 1 : (%d processes)\n",q1);
	display(queue_one,q1);
	printf("\n\nQUEUE 2 : (%d processes)\n",q2);
	display(queue_two,q2);
	printf("\n\nQUEUE 3 : (%d processes)\n",q3);
	display(queue_thr,q3);
	
	sort_arrival(queue_one,q1);											//sorting queue_one based on arrival time
	sort_arrival(queue_two,q2);											//sorting queue_two based on arrival time
	sort_arrival(queue_thr,q3);											//sorting quueue_thr based on arrival time
		
	printf("\n\nScheduling :\n\n");										//sheduling(queue_one,queue_two,queue_thr);

}
//******************************************************************************************************
void pid_assign(struct processs *pp_array)
{
	system("cls");
	printf("\nNumber of Processes : %d",n);
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the PID :\n\n\tPROCESS_ID\n\n");
	int flag;
	for(i=0;i<n;i++)
	{
		do
		{
			flag=0;
			printf("\t   ");
			scanf("%d",&((pp_array+i)->pid));
			
			for(j=0;j<i;j++)
			if(((pp_array+i)->pid)==((pp_array+j)->pid))
			{
				printf("\t\t\t\t\tPID already exists!! Enter Again... \n");
				flag=1;
			}
			if(((pp_array+i)->pid)<=0)
			printf("\t\t\t\t\tPID can not be <=0 !!Enter Again...\n");
		}while((((pp_array+i)->pid)<=0)||(flag==1));
	}
}
//******************************************************************************************************
void burst_assign(struct processs *pp_array)
{
	system("cls");
	printf("\nNumber of Processes : %d",n);
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the BURST_TIME :\n\n\tPROCESS_ID\tBURST_TIME\n\n");
	for(i=0;i<n;i++)
	{
		do
		{
			printf("\t   %d\t\t       ",(pp_array+i)->pid);
			scanf("%d",&((pp_array+i)->burst_time));
			if(((pp_array+i)->burst_time)<=0)
			printf("\t\t\t\t\tBURST_TIME can not be <=0 !!Enter Again...\n");
		}while(((pp_array+i)->burst_time)<=0);
	}
}
//******************************************************************************************************
void arrival_assign(struct processs *pp_array)
{
	system("cls");
	printf("\nNumber of Processes : %d",n);
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the ARRIVAL_TIME :\n\n\tPROCESS_ID\tBURST_TIME\tARRIVAL_TIME\n\n");
	for(i=0;i<n;i++)
	{
		do
		{
			printf("\t   %d\t\t      %d\t\t   ",((pp_array+i)->pid),((pp_array+i)->burst_time));
			scanf("%d",&((pp_array+i)->arrival_time));
			if(((pp_array+i)->arrival_time)<0)
			printf("\t\t\t\t\t\tARRIVAL_TIME can not be <0 !!Enter Again...\n");
		}while(((pp_array+i)->arrival_time)<0);
	}
}
//******************************************************************************************************
void priority_assign(struct processs *pp_array)
{
	system("cls");
	printf("\nNumber of Processes : %d",n);
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the associated PRIORITY[1-10]:\n\n\tPROCESS_ID\tBURST_TIME\tARRIVAL_TIME\tPRIORITY\n\n");
	for(i=0;i<n;i++)
	{
		do
		{
			printf("\t   %d\t\t      %d\t\t   %d\t\t   ",((pp_array+i)->pid),((pp_array+i)->burst_time),((pp_array+i)->arrival_time));
			scanf("%d",&((pp_array+i)->priority));
			if((((pp_array+i)->priority)<1)||(((pp_array+i)->priority)>10))
			printf("\t\t\t\t\t\t\tPRIORITY should be in range [1,10] !!Enter Again...\n");
		}while((((pp_array+i)->priority)<1)||(((pp_array+i)->priority)>10));
	}
}
//******************************************************************************************************
void display(struct processs *pp_array,int k)
{
	printf("\n\tPROCESS_ID\tBURST_TIME\tARRIVAL_TIME\tPRIORITY\n");
	for(i=0;i<k;i++)
	printf("\n\t  %d\t\t      %d\t\t   %d\t\t   %d",((pp_array+i)->pid),(pp_array+i)->burst_time,(pp_array+i)->arrival_time,(pp_array+i)->priority);
	printf("\n");
}
//******************************************************************************************************
void queue_size(struct processs *pp_array)
{
	for(i=0;i<n;i++)
	{
		if((((pp_array+i)->priority)>=1)&&(((pp_array+i)->priority)<=3))
		q1++;
		else if((((pp_array+i)->priority)>=4)&&(((pp_array+i)->priority)<=7))
		q2++;
		else
		q3++;
	}
}
//******************************************************************************************************
void queue_assign(struct processs *pp_array)
{
	int j1=-1,j2=-1,j3=-1;
	for(i=0;i<n;i++)
	{
		if((((pp_array+i)->priority)>=1)&&(((pp_array+i)->priority)<=3))
		{
			j1++;
			*((queue_one+j1))=*((pp_array+i));
		}
		else if((((pp_array+i)->priority)>=4)&&(((pp_array+i)->priority)<=7))
		{
			j2++;
			*((queue_two+j2))=*((pp_array+i));
		}
		else
		{
			j3++;
			*((queue_thr+j3))=*((pp_array+i));
		}
	}
}
//******************************************************************************************************
void sort_arrival(struct processs *pp_array,int k)
{
	struct processs temp;
	
	for(i=0;i<k;i++)
	for(j=0;j<(k-1-i);j++)
	if(((pp_array+j)->arrival_time)>((pp_array+(j+1))->arrival_time))
	{
		temp=*(pp_array+j);
		*(pp_array+j)=*(pp_array+(j+1));
		*(pp_array+(j+1))=temp;
	}	
}
//******************************************************************************************************
void sheduling(struct processs *queue_1, struct processs *queue_2, struct processs *queue_3)
{
	int turn=1,time_count=0;
	do
	{
		if(turn==1)
		{
			for(i=0;i<10;i++)
			{
				time_count++;
				printf("%d ",time_count);
				if(time_count%10==0)
				{
					turn==2;
					printf("\nQueue 1 done. Next turn is Queue 2.\n");
					break;
				}
			}
		}
		if(turn==1)
		{
			for(i=0;i<10;i++)
			{
				time_count++;
				printf("%d ",time_count);
				if(time_count%10==0)
				{
					turn==3;
					printf("\nQueue 2 done. Next turn is Queue 3.\n");
					break;
				}
			}
		}
		if(turn==1)
		{
			for(i=0;i<10;i++)
			{
				time_count++;
				printf("%d ",time_count);
				if(time_count%10==0)
				{
					turn==1;
					printf("\nQueue 3 done. Next turn is Queue 1.\n");
					break;
				}
			}
		}
	}while(time_count<200);
}
