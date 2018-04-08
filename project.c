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
void pid_assign();														//function to assign process id
void burst_assign();													//function to assign burst time
void arrival_assign();													//function to assign arrival time
void priority_assign();													//function to assign priority
//------------------------------------------------------------------------------------------------------
void display(struct processs *pp_array,int k);							//function to display all processes
//------------------------------------------------------------------------------------------------------
void queue_size();														//function to determine the size of each queue
void queue_assign();													//function for assigning queue
void sort_queue(struct processs *pp_array,int k);						//sorts the processes based on arrival time
//------------------------------------------------------------------------------------------------------
void scheduling();														//function to schedule the processes
void pop(struct processs *ready,int r);									//function to pop processes from ready queue
void push(struct processs *ready,struct processs tempp,int r);			//function to push processes in ready queue
//******************************************************************************************************

//**************************************MAIN************************************************************
int main()
{
	system("cls");	

	printf("\nNumber of Processes : ");scanf("%d",&n);					//asking for number of processes
	p_array=(struct processs*)calloc(n,sizeof(struct processs));		//allocating number of processes
	
	pid_assign();														//asking PID
	burst_assign();														//asking BURST_TIME
	arrival_assign();													//asking ARRIVAL_TIME
	priority_assign();													//asking PRIORITY
	system("cls");
	printf("\nNumber of Processes : %d",n);
	display(p_array,n);													//displaying PROCESSES along with BURST TIME and ARRIVAL TIME and PRIORITY

	queue_size();														//determining size of each queue q1,q2,q3
	queue_one=(struct processs*)calloc(q1,sizeof(struct processs));		//allocating memory to queue_one
	queue_two=(struct processs*)calloc(q2,sizeof(struct processs));		//allocating memory to queue_two
	queue_thr=(struct processs*)calloc(q3,sizeof(struct processs));		//allocating memory to queue_thr
	queue_assign();														//assigning processes to respective queue
	
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
	
	/*
	sort_arrival(queue_one,q1);											//sorting queue_one based on arrival time
	sort_arrival(queue_two,q2);											//sorting queue_two based on arrival time
	sort_arrival(queue_thr,q3);											//sorting queue_thr based on arrival time
	*/
	
	printf("\n\nScheduling :\n\n\t  TIME\t\t\tPROCESS\n");				//sheduling queue_one,queue_two,queue_thr
	printf(" ___________________________________________\n");
	scheduling();
}
//******************************************************************************************************
void pid_assign()
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
			scanf("%d",&((p_array+i)->pid));
			
			for(j=0;j<i;j++)
			if(((p_array+i)->pid)==((p_array+j)->pid))
			{
				printf("\t\t\t\t\tPID already exists!! Enter Again... \n");
				flag=1;
			}
			if(((p_array+i)->pid)<=0)
			printf("\t\t\t\t\tPID can not be <=0 !!Enter Again...\n");
		}while((((p_array+i)->pid)<=0)||(flag==1));
	}
}
//******************************************************************************************************
void burst_assign()
{
	system("cls");
	printf("\nNumber of Processes : %d",n);
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the BURST_TIME :\n\n\tPROCESS_ID\t\tBURST_TIME\n\n");
	for(i=0;i<n;i++)
	{
		do
		{
			printf("\t     %d     \t\t    ",(p_array+i)->pid);
			scanf("%d",&((p_array+i)->burst_time));
			if(((p_array+i)->burst_time)<=0)
			printf("\t\t\t\t\tBURST_TIME can not be <=0 !!Enter Again...\n");
		}while(((p_array+i)->burst_time)<=0);
	}
}
//******************************************************************************************************
void arrival_assign()
{
	system("cls");
	printf("\nNumber of Processes : %d",n);
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the ARRIVAL_TIME :\n\n\tPROCESS_ID\t\tBURST_TIME\t\tARRIVAL_TIME\n\n");
	for(i=0;i<n;i++)
	{
		do
		{
			printf("\t     %d     \t\t     %d     \t\t     ",((p_array+i)->pid),((p_array+i)->burst_time));
			scanf("%d",&((p_array+i)->arrival_time));
			if(((p_array+i)->arrival_time)<0)
			printf("\t\t\t\t\t\tARRIVAL_TIME can not be <0 !!Enter Again...\n");
		}while(((p_array+i)->arrival_time)<0);
	}
}
//******************************************************************************************************
void priority_assign()
{
	system("cls");
	printf("\nNumber of Processes : %d",n);
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the associated PRIORITY[1-10]:\n\n\tPROCESS_ID\t\tBURST_TIME\t\tARRIVAL_TIME\t\tPRIORITY\n\n");
	for(i=0;i<n;i++)
	{
		do
		{
			printf("\t     %d     \t\t     %d     \t\t     %d     \t\t     ",((p_array+i)->pid),((p_array+i)->burst_time),((p_array+i)->arrival_time));
			scanf("%d",&((p_array+i)->priority));
			if((((p_array+i)->priority)<1)||(((p_array+i)->priority)>10))
			printf("\t\t\t\t\t\t\tPRIORITY should be in range [1,10] !!Enter Again...\n");
		}while((((p_array+i)->priority)<1)||(((p_array+i)->priority)>10));
	}
}
//******************************************************************************************************
void display(struct processs *pp_array,int k)
{
	printf("\n\tPROCESS_ID\t\tBURST_TIME\t\tARRIVAL_TIME\t\tPRIORITY\n");
	for(i=0;i<k;i++)
	printf("\n\t     %d     \t\t     %d     \t\t     %d     \t\t     %d",((pp_array+i)->pid),(pp_array+i)->burst_time,(pp_array+i)->arrival_time,(pp_array+i)->priority);
	printf("\n");
}
//******************************************************************************************************
void queue_size()
{
	for(i=0;i<n;i++)
	{
		if((((p_array+i)->priority)>=1)&&(((p_array+i)->priority)<=3))
		q1++;
		else if((((p_array+i)->priority)>=4)&&(((p_array+i)->priority)<=7))
		q2++;
		else
		q3++;
	}
}
//******************************************************************************************************
void queue_assign()
{
	int j1=-1,j2=-1,j3=-1;															//these are for count of queue_one,queue_two,queue_thr
	for(i=0;i<n;i++)
	{
		if((((p_array+i)->priority)>=1)&&(((p_array+i)->priority)<=3))
		{
			j1++;
			*((queue_one+j1))=*((p_array+i));
		}
		else if((((p_array+i)->priority)>=4)&&(((p_array+i)->priority)<=7))
		{
			j2++;
			*((queue_two+j2))=*((p_array+i));
		}
		else
		{
			j3++;
			*((queue_thr+j3))=*((p_array+i));
		}
	}
}
//******************************************************************************************************
void sort_queue(struct processs *pp_array,int k)
{
	struct processs temp;
	
	for(i=0;i<k;i++)
	for(j=0;j<(k-1-i);j++)
	if(((pp_array+j)->priority)>((pp_array+(j+1))->priority))
	{
		temp=*(pp_array+j);
		*(pp_array+j)=*(pp_array+(j+1));
		*(pp_array+(j+1))=temp;
	}
}
//******************************************************************************************************
void pop(struct processs *ready,int r)
{
	for(i=1;i<=r;i++)
	{
		*(ready+(i-1))=*(ready+i);
	}
}
//******************************************************************************************************
void push(struct processs *ready,struct processs tempp,int r)
{
	*(ready+r)=tempp;
}
//******************************************************************************************************
void scheduling()
{
	int turn=1,time_count=-1;
	int r1=-1,r2=-1,r3=-1;													//these are for count of ready_q1,ready_q2,ready_q3
	int qq1=q1,qq2=q2,qq3=q3;
	struct processs *ready_q1,*ready_q2,*ready_q3,temp;
	
	ready_q1=(struct processs*)calloc(q1+1,sizeof(struct processs));		//allocating memory to queue_one
	ready_q2=(struct processs*)calloc(q2+1,sizeof(struct processs));		//allocating memory to queue_two
	ready_q3=(struct processs*)calloc(q3+1,sizeof(struct processs));		//allocating memory to queue_thr
	
	do
	{
		if(turn==1)
		{
			int time_quantum=0;
			for(i=0;i<=10;i++)
			{
				if(qq1==0)
				{
					turn=2;
					break;
				}
				else
				{	
					time_count++;
					{
						for(j=0;j<q1;j++)
						if(((queue_one+j)->arrival_time)==time_count)
						{
							r1++;
							*(ready_q1+r1)=*(queue_one+j);
						}
						for(j=0;j<q2;j++)
						if(((queue_two+j)->arrival_time)==time_count)
						{
							r2++;
							*(ready_q2+r2)=*(queue_two+j);
						}
						for(j=0;j<q3;j++)
						if(((queue_thr+j)->arrival_time)==time_count)
						{
							r3++;
							*(ready_q3+r3)=*(queue_thr+j);
						}
					}
					printf("\t   %d-%d     ",time_count,time_count+1);
					
					if(((ready_q1+0)->pid)!=0)											//if ready queue is not empty
					{
						printf("\t         %d\n",((ready_q1+0)->pid));
						(ready_q1+0)->burst_time--;
						time_quantum++;
						if(((ready_q1+0)->burst_time)==0)								//three cases arise
						{																//1. burst_time < time_quantum
							pop(ready_q1,r1+1);											//2. burst_time = time_quantum
							r1--;														//3. burst_time > time_quantum
							qq1--;
							time_quantum=0;
						}
						if(time_quantum==4)
						{
							temp=*(ready_q1+0);
							pop(ready_q1,r1+1);
							push(ready_q1,temp,r1);
						time_quantum=0;
						}
					}
					else
					printf("\t\tIDLE\n");
					if((time_count+1)%10==0)
					{
						turn=2;
						break;
					}
				}
			}
		}
		if(turn==2)
		{	
			for(i=0;i<=10;i++)
			{
				if(qq2==0)
				{
					turn=3;
					break;
				}
				else
				{
					time_count++;
					{
						for(j=0;j<q1;j++)
						if(((queue_one+j)->arrival_time)==time_count)
						{
							r1++;
							*(ready_q1+r1)=*(queue_one+j);
						}
						for(j=0;j<q2;j++)
						if(((queue_two+j)->arrival_time)==time_count)
						{
							r2++;
							*(ready_q2+r2)=*(queue_two+j);
						}
						for(j=0;j<q3;j++)
						if(((queue_thr+j)->arrival_time)==time_count)
						{
							r3++;
							*(ready_q3+r3)=*(queue_thr+j);
						}
					}
					printf("\t   %d-%d     ",time_count,time_count+1);
					
					if(((ready_q2+0)->pid)!=0)											//if ready queue is not empty
					{
						sort_queue(ready_q2,r2+1);
						printf("\t         %d\n",((ready_q2+0)->pid));
						(ready_q2+0)->burst_time--;
						if(((ready_q2+0)->burst_time)==0)
						{
							pop(ready_q2,r2+1);
							r2--;
							qq2--;
						}
					}
					else
					printf("\t\tIDLE\n");
					if((time_count+1)%10==0)
					{
						turn=3;
						break;
					}
				}
			}
		}
		if(turn==3)
		{
			for(i=0;i<=10;i++)
			{
				if(qq3==0)
				{
					turn=1;
					break;
				}
				else
				{
					time_count++;
					{
						for(j=0;j<q1;j++)
						if(((queue_one+j)->arrival_time)==time_count)
						{
							r1++;
							*(ready_q1+r1)=*(queue_one+j);
						}
						for(j=0;j<q2;j++)
						if(((queue_two+j)->arrival_time)==time_count)
						{
							r2++;
							*(ready_q2+r2)=*(queue_two+j);
						}
						for(j=0;j<q3;j++)
						if(((queue_thr+j)->arrival_time)==time_count)
						{
							r3++;
							*(ready_q3+r3)=*(queue_thr+j);
						}
					}
					printf("\t   %d-%d     ",time_count,time_count+1);
					
					if(((ready_q3+0)->pid)!=0)
					{
						printf("\t         %d\n",((ready_q3+0)->pid));
						(ready_q3+0)->burst_time--;
						if(((ready_q3+0)->burst_time)==0)
						{
							pop(ready_q3,r3+1);
							r3--;
							qq3--;
						}
					}
					else
					printf("\t\tIDLE\n");
					if((time_count+1)%10==0)
					{
						turn=1;
						break;
					}
				}
			}
		}
	}while((qq1>0)||(qq2>0)||(qq3>0));
}
