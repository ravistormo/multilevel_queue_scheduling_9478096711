#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

struct processs						//structure to hold the attributes of process
{
	int pid;						//process_id
	int burst_time;					//burst time of processes
	int arrival_time;					//arrival time of processes
	int priority;					//priority of processes
	int waiting_time;					//to store the waiting time of process
}*p_array,*queue_one, *queue_two, *queue_thr,*ready_q1,*ready_q2,*ready_q3,temp;

//*p_array is for containing total 'n' processes along with pid, burst_time,arrival_time,priority,waiting_time
//*queue_one,*queue_two,*queue_thr are to store processes based on priority
//*ready_q1,*ready_q2,*ready_q3 are ready queues for queue_one,queue_two,queue_thr

//*************************************GLOBAL VARIABLES************************************************
int n,i,j;							// n is total nnumber of processes, i and j are counters in loop
int q1=0,q2=0,q3=0;					// q1,q2,q3 are total number of processes in each queue
int turn=1,time_count=-1;				//'turn' is for checking which queue to process next 
int r1=-1,r2=-1,r3=-1;					//time_count is variable for time(always increases)
								//r1,r2,r3 are for index of ready_q1,ready_q2,ready_q3
int qq1,qq2,qq3;						//this is to keep track of processes left in respective queues
int avg=0;							//this is to store average waiting time
int in_ten_qt;						//this is to check if any process comes in time_quantum range
//**************************************FUNCTIONS******************************************************
void heading();
void pid_assign();					//function to assign process id
void burst_assign();					//function to assign burst time
void arrival_assign();					//function to assign arrival time
void priority_assign();					//function to assign priority
//------------------------------------------------------------------------------------------------------
void display(struct processs *pp_array,int k);//function to display all processes
void display_waiting_time(struct processs *pp_array,int k);	//function to display waiting time of each process
//------------------------------------------------------------------------------------------------------
void queue_size();					//function to determine the size of each queue
void queue_assign();					//function for assigning queue
void sort_queue(struct processs *pp_array,int k);//sorts the processes based on priority time
void sort_queue_arrival(struct processs *pp_array,int k); //sorts the processes based on arrival_time
//------------------------------------------------------------------------------------------------------
void ready_queue();					//function to add processes in respective ready queues
void round_robin();					//function for round robin scheduing in queue_one
void priority_scheduling();				//function for priority scheduling in queue_two
void first_come_first_serve();			//function for first_come_first_serve scheduling in queue_thr
void wait_time();						//function to claculate waiting time of processes
void average_wait();					//function to claculate average waiting time of all processes
void scheduling();					//function to schedule the processes
void pop(struct processs *ready,int r);		//function to pop processes from ready queue
void push(struct processs *ready,struct processs tempp,int r);//function to push processes in ready queue
//**************************************MAIN************************************************************
int main()
{
	int process_flag=0;				//if wrong value is entered, process_flag changes to 1
	do							//and error message is displayed
	{
		system("clear");				//to clear console screen
		heading();					//to print heading message
		if(process_flag==1)			//for printing error message
		printf("\nEnter a number > 0 \n");
		printf("\nNumber of Processes : ");
		scanf("%d",&n);				//asking for number of processes
		if(n<=0)
		process_flag=1;				//changing process_flag value to 1
	}while(n<=0);
	p_array=(struct processs*)calloc(n,sizeof(struct processs));	//allocating number of processes
	
	pid_assign();					//asking PID
	burst_assign();					//asking BURST_TIME
	arrival_assign();					//asking ARRIVAL_TIME
	priority_assign();				//asking PRIORITY
	system("clear");
	printf("\nNumber of Processes : %d",n);
	display(p_array,n);				//displaying PROCESSES

	queue_size();					//determining size of each queue q1,q2,q3
	queue_one=(struct processs*)calloc(q1,sizeof(struct processs));//allocating memory to queue_one
	queue_two=(struct processs*)calloc(q2,sizeof(struct processs));//allocating memory to queue_two
	queue_thr=(struct processs*)calloc(q3,sizeof(struct processs));//allocating memory to queue_thr
	queue_assign();					//assigning processes to respective queue
	
	printf("\nDividing processes on basis of PRIORITY.");
	printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\tPress ENTER to continue...");
	getchar();						//to hold screen
	getchar();
	printf("\n\nPRIORITY\t\tQUEUE\n");
	printf(" [1,3]\t\t\t Q1\n [4,7]\t\t\t Q2\n[8, 10]\t\t\t Q3\n");
	
	printf("\nThe generated QUEUES are :");
	printf("\n\nQUEUE 1 : (%d processes)\n",q1);
	display(queue_one,q1);			//displaying processes in queue_one
	printf("\n\nQUEUE 2 : (%d processes)\n",q2);
	display(queue_two,q2);			//displaying processes in queue_two
	printf("\n\nQUEUE 3 : (%d processes)\n",q3);
	display(queue_thr,q3);			//displaying processes in queue_thr	
	
sort_queue_arrival(queue_one,q1);
sort_queue_arrival(queue_two,q2);
sort_queue_arrival(queue_thr,q3);

printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\tPress ENTER to continue...\n");
	getchar();
	printf("\n\nScheduling :\n\n\t  TIME\t\t\tPROCESS\n");
	printf(" ___________________________________________\n");
	scheduling();				//TO schedule the processes, print gantt chart
	printf("\n\t\t\t\t\t\t\t\t\t\t\t\t\tPress ENTER to display waiting time...\n");
	getchar();
printf("\n\tPROCESS_ID\t\tWAITING_TIME\n");
	display_waiting_time(queue_one,q1);
	display_waiting_time(queue_two,q2);
	display_waiting_time(queue_thr,q3);
	average_wait();
	printf("\nAverage waiting time : %f ",(float)avg/n);
}
//******************************************************************************************************
void heading()
{
	printf("\n\t||_________________________________________________________________________________________________||\n");
	printf("\t||_________________________________________________________________________________________________||\n");
	printf("\t||                            MULTILEVEL QUEUE SCHEDULING                                          ||\n");
	printf("\t||                                 By- Ravishankar Singh                                           ||\n");
	printf("\t||_________________________________________________________________________________________________||\n");
	printf("\t||_________________________________________________________________________________________________||\n");
	printf("\t||_________________________________________________________________________________________________||\n");
}
//*****************************************************************************************************
void pid_assign()
{
	system("clear");					//clear console
	heading();
	printf("\nNumber of Processes : %d",n);	
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the PID :\n\n\tPROCESS_ID\n\n");
	int flag;						//flag to check if entered PID already exists or not
	for(i=0;i<n;i++)
	{
		do
		{
			flag=0;
			printf("\t   ");
			scanf("%d",&((p_array+i)->pid));	//assigning value entered by user
			
			for(j=0;j<i;j++)
			if(((p_array+i)->pid)==((p_array+j)->pid))//checking if pid already exists in queue
			{
				printf("\t\t\t\t\tPID already exists!! Enter Again... \n");
				flag=1;				//flag is set to 1 ,i.e value already exists
			}
			if(((p_array+i)->pid)<=0)		//constrain on input value
			printf("\t\t\t\t\tPID can not be <=0 !!Enter Again...\n");
		}while((((p_array+i)->pid)<=0)||(flag==1));
	}
}
//******************************************************************************************************
void burst_assign()
{
	system("clear");
	heading();
	printf("\nNumber of Processes : %d",n);
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the BURST_TIME :\n\n\tPROCESS_ID\t\tBURST_TIME\n\n");
	for(i=0;i<n;i++)
	{
		do
		{
			printf("\t     %d     \t\t    ",(p_array+i)->pid);				
			scanf("%d",&((p_array+i)->burst_time));		//assigning value to burst time
			if(((p_array+i)->burst_time)<=0)			//constrain on input value
			printf("\t\t\t\t\tBURST_TIME can not be <=0 !!Enter Again...\n");
		}while(((p_array+i)->burst_time)<=0);
	}
}
//******************************************************************************************************
void arrival_assign()
{
	system("clear");
	heading();
	printf("\nNumber of Processes : %d",n);
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the ARRIVAL_TIME :\n\n\tPROCESS_ID\t\tBURST_TIME\t\tARRIVAL_TIME\n\n");
	for(i=0;i<n;i++)
	{
		do
		{
			printf("\t     %d     \t\t     %d     \t\t     ",((p_array+i)->pid),((p_array+i)->burst_time));
			scanf("%d",&((p_array+i)->arrival_time));		//assigning value to arrival time	
			if(((p_array+i)->arrival_time)<0)			//constrain on input value
			printf("\t\t\t\t\t\tARRIVAL_TIME can not be <0 !!Enter Again...\n");
		}while(((p_array+i)->arrival_time)<0);
	}
}
//******************************************************************************************************
void priority_assign()
{
	system("clear");
	heading();
	printf("\nNumber of Processes : %d",n);
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the associated PRIORITY[1-10]:\n\n\tPROCESS_ID\t\tBURST_TIME\t\tARRIVAL_TIME\t\tPRIORITY\n\n");
	for(i=0;i<n;i++)
	{
		do
		{
			printf("\t     %d     \t\t     %d     \t\t     %d     \t\t     ",((p_array+i)->pid),((p_array+i)->burst_time),((p_array+i)->arrival_time));
			scanf("%d",&((p_array+i)->priority));					//assigning value to priority
			if((((p_array+i)->priority)<1)||(((p_array+i)->priority)>10))	//constrain on input value
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
void display_waiting_time(struct processs *pp_array,int k)
{
	for(i=0;i<k;i++)
	printf("\n\t     %d     \t\t     %d     ",((pp_array+i)->pid),((pp_array+i)->waiting_time));
}
//******************************************************************************************************
void queue_size()
{
	for(i=0;i<n;i++)
	{
		if((((p_array+i)->priority)>=1)&&(((p_array+i)->priority)<=3))//if       1<=priority<=3
		q1++;										//increment the count of processes to be added in queue_one
		else if((((p_array+i)->priority)>=4)&&(((p_array+i)->priority)<=7))//if		4<=priority<=7
		q2++;										//increment the count of processes to be added in queue_two
		else										// all other cases i.e  8<=priority<=10	
		q3++;										//increment the count of processes to be added in queue_thr
	}
}
//******************************************************************************************************
void queue_assign()
{
	int j1=-1,j2=-1,j3=-1;								//these are for index value of queue_one,queue_two,queue_thr
	for(i=0;i<n;i++)
	{
		if((((p_array+i)->priority)>=1)&&(((p_array+i)->priority)<=3))//if       1<=priority<=3
		{
			j1++;									//incrementing index value for queue_one
			*((queue_one+j1))=*((p_array+i));				//assigning queue_one with process
		}
		else if((((p_array+i)->priority)>=4)&&(((p_array+i)->priority)<=7))	//if		  4<=priority<=7
		{
			j2++;									//incrementing index value for queue_two
			*((queue_two+j2))=*((p_array+i));				//assigning queue_two with process
		}
		else										//if 8<=priority<=10	
		{
			j3++;									//incrementing index value for queue_thr
			*((queue_thr+j3))=*((p_array+i));				//assigning queue_two with process
		}
	}
}
//******************************************************************************************************
void sort_queue(struct processs *pp_array,int k)
{
	struct processs tempp;
	
	for(i=0;i<k;i++)
	for(j=0;j<(k-1-i);j++)
	if(((pp_array+j)->priority)>((pp_array+(j+1))->priority))		//applying bubble sort based on priority
	{
		tempp=*(pp_array+j);
		*(pp_array+j)=*(pp_array+(j+1));
		*(pp_array+(j+1))=tempp;
	}
}
//******************************************************************************************************
void sort_queue_arrival(struct processs *pp_array,int k)
{
	struct processs tempp;
	
	for(i=0;i<k;i++)
	for(j=0;j<(k-1-i);j++)
	if(((pp_array+j)->arrival_time)>((pp_array+(j+1))->arrival_time))	//applying bubble sort based on arrival time
	{
		tempp=*(pp_array+j);
		*(pp_array+j)=*(pp_array+(j+1));
		*(pp_array+(j+1))=tempp;
	}
}
//******************************************************************************************************
void pop(struct processs *ready,int r)
{
	for(i=1;i<=r;i++)
	{
		*(ready+(i-1))=*(ready+i);			//left shift the values in readu queue 
	}
}
//******************************************************************************************************
void push(struct processs *ready,struct processs tempp,int r)
{
	*(ready+r)=tempp;						//adding the temp value to last index of array
}
//******************************************************************************************************
void wait_time()
{
	for(i=0;i<q1;i++)
	for(j=0;j<=r1;j++)
	{
		if(((queue_one+i)->pid)==((ready_q1+j)->pid))
		{
			if(j!=0)
			(queue_one+i)->waiting_time++;
			if((j==0)&&(turn!=1))
			(queue_one+i)->waiting_time++;
		}
	}
	for(i=0;i<q2;i++)
	for(j=0;j<=r2;j++)
	{
		if(((queue_two+i)->pid)==((ready_q2+j)->pid))
		{
			if(j!=0)
			(queue_two+i)->waiting_time++;
			if((j==0)&&(turn!=2))
			(queue_two+i)->waiting_time++;
		}
	}
	for(i=0;i<q3;i++)
	for(j=0;j<=r3;j++)
	{
		if(((queue_thr+i)->pid)==((ready_q3+j)->pid))
		{
			if(j!=0)
			(queue_thr+i)->waiting_time++;
			if((j==0)&&(turn!=3))
			(queue_thr+i)->waiting_time++;
		}
	}
}
//******************************************************************************************************
void average_wait()
{
	for(i=0;i<q1;i++)
	{
		avg+=(queue_one+i)->waiting_time;
	}
	for(i=0;i<q2;i++)
	{
		avg+=(queue_two+i)->waiting_time;
	}
	for(i=0;i<q3;i++)
	{
		avg+=(queue_thr+i)->waiting_time;
	}
}
//******************************************************************************************************
void ready_queue()
{
	for(j=0;j<q1;j++)						//checking if any process arrives at this time_count in queue_one
	if(((queue_one+j)->arrival_time)==time_count)	// if yes then add that process to ready_q1
	{
		r1++;							//incrementing index vaue for ready_q1
		*(ready_q1+r1)=*(queue_one+j);		//adding process to ready_q1
	}
	for(j=0;j<q2;j++)						//checking if any process arrives at this time_count in queue_two
	if(((queue_two+j)->arrival_time)==time_count)	// if yes then add that process to ready_q2
	{
		r2++;							//incrementing the index value for ready_q2
		*(ready_q2+r2)=*(queue_two+j);		//adding process to ready_q2
	}
	for(j=0;j<q3;j++)						//checking if any process arrives at this time_count in queue_thr
	if(((queue_thr+j)->arrival_time)==time_count)	// if yes then add that process to ready_q3
	{	
		r3++;							//incrementing the index value for ready_q3
		*(ready_q3+r3)=*(queue_thr+j);		//adding process to ready_q3
	}
}
//******************************************************************************************************
void round_robin()
{
	in_ten_qt=0;
	int temp_tc=time_count+1;				//in_ten_qt is to check whether a process will come... 
	for(j=0;j<q1;j++)						//within time_quantum of queue_one or not
	{
		if((((queue_one+j)->arrival_time)>=(temp_tc))&&((((queue_one+j)->arrival_time)<(temp_tc+10))))
		if((ready_q1+0)->pid==0)
		{
			in_ten_qt++;					//if any process will come in current time quantum, value increases
			for(i=0;i<((queue_one+j)->arrival_time)-temp_tc;i++)
			{
				time_count++;
				printf("\n\t   %d-%d     \t\tIDLEaaaa",time_count,time_count+1);
			}
			if(qq1==0)
			in_ten_qt=1;				//if all processes are processed so that idle is not printed
			break;						 
		}
	}
	int time_quantum=0;					//queue_one undergoes Round Robin, this is for counting time quantum
	for(i=0;i<=10;i++)					// each queue has time quantum of 10 seconds
	{
		if(qq1==0 || in_ten_qt==0)			//checking if processes are left in ready_q1 or not, or...
		{							//if a process will come in ready_q1 within 10 time_quantum
			if((ready_q1+0)->pid==0)
			{	turn=2;				//if no process is left then switch the turn to queue_two
				break;													
			}
		}
		//if processes are left then process queue_one
		{	
			time_count++;				//time always increases time_count was (-1) 
			ready_queue();				//adding processes in ready queues
			printf("\n\t   %d-%d     ",time_count,time_count+1);
//displaying the current interval for which the process is being processed
			
			if(((ready_q1+0)->pid)!=0)		//if ready queue is not empty
			{
				wait_time();
				printf("\t         %d",((ready_q1+0)->pid));
//displaying the current process being processed for the above time interval
				(ready_q1+0)->burst_time--;	//decrementing the value of burst_time after of current process 
				time_quantum++;			//incrementing the value of time_quantum, since it is round robin scheduling
				if(((ready_q1+0)->burst_time)==0)//THREE CASES ARISE 1. burst_time < time_quantum
				{					// 2. burst_time = time_quantum3. burst_time > time_quantum
					pop(ready_q1,r1+1);	//this is case 1.  process is removed from ready_q1
					r1--;				//decrementing the index of ready_q1
					qq1--;			//decrementing the count of remaining processes
					time_quantum=0;		//resetting the time_quantum to 0
				}
				if(time_quantum==4)		//case 2 + case 3
				{
					temp=*(ready_q1+0);	//store the current process with updated burst_time in temp
					pop(ready_q1,r1+1);	//remove this process from ready_q1
					push(ready_q1,temp,r1);	//add the remaining part of process to end of ready_q1,i.e add temp at end
					time_quantum=0;		//reset the value of time_quantum to 0
				}
			}
			else
			printf("\t\tIDLE");			// if no process is in the ready_q1 then CPU is IDLE
			if((time_count+1)==(temp_tc+10))	// after every 10 seconds, tuen of next queue comes
			{
				turn=2;				//giving turn to queue_two
				break;				//come out of queue_one
			}
		}
	}
}
//******************************************************************************************************
void priority_scheduling()
{
	in_ten_qt=0;
	int temp_tc=time_count+1;				//in_ten_qt is to check whether a process will come... 
	for(j=0;j<q2;j++)						//within time_quantum of queue_two or not
	{
		if((((queue_two+j)->arrival_time)>=(temp_tc))&&((((queue_two+j)->arrival_time)<(temp_tc+10))))
		if((ready_q2+0)->pid==0)
		{
			in_ten_qt++;					//if any process will come in current time quantum, value increases
			for(i=0;i<((queue_two+j)->arrival_time)-temp_tc;i++)
			{
				time_count++;
				printf("\n\t   %d-%d     \t\tIDLEbbbb",time_count,time_count+1);
			}
			if(qq2==0)
			in_ten_qt=1;
			break;						//if all processes are processed so that idle is not printed 
		}	
}
	for(i=0;i<=10;i++)					//each queue has time quantum of 10 seconds												
	{
		if(qq2==0 || in_ten_qt==0)			//checking if there are processes remaining in ready_q2 or...
		{							//if any process will come in ready_q2 within 10 time_quantum
			if((ready_q2+0)->pid==0)
			{	turn=3;				//if no process remaining switch to queue_thr
				break;				//switch to queue_thr
			}
		}
									//else continue processing of queue_two
		{	
			time_count++;				//counting time quantum for queue_two
			ready_queue();				//adding processes in ready queues
			printf("\n\t   %d-%d     ",time_count,time_count+1);//printing the current time interval of process
			
			sort_queue(ready_q2,r2+1);//sorting ready_q2 according to priority, since queue_two undergoes PRIORITY SCHEDULING 
			if(((ready_q2+0)->pid)!=0)		//if ready queue is not empty
			{
				wait_time();
				printf("\t         %d",((ready_q2+0)->pid));//printing current process under processing
				(ready_q2+0)->burst_time--;	//decrementing the value of burst_time after processing
				if(((ready_q2+0)->burst_time)==0)//checking if burst_time of 0,if 0 then remove the process from ready_q2
				{
					pop(ready_q2,r2+1);	//removing process from ready_q2
					r2--;				//decrementing index of ready_q2
					qq2--;			//decrementing count of remaining processes
				}
			}
			else
			printf("\t\tIDLE");			//if ready_q2 is empty then print CPU is IDLE
			if((time_count+1)==(temp_tc+10))	//if 10 seconds are over then switch to queue_thr
			{
				turn=3;				//assign turn to queue_thr
				break;				//stop processing queue_two
			}
		}
	}
}
//******************************************************************************************************
void first_come_first_serve()
{
	in_ten_qt=0;
	int temp_tc=time_count+1;			//in_ten_qt is to check whether a process will come... 
	for(j=0;j<q3;j++)					//within time_quantum of queue_thr or not
	{
		if((((queue_thr+j)->arrival_time)>=(temp_tc))&&((((queue_thr+j)->arrival_time)<(temp_tc+10))))
		if((ready_q3+0)->pid==0)
		{
			in_ten_qt++;				//if any process will come in current time quantum, value increases
			for(i=0;i<((queue_thr+j)->arrival_time)-temp_tc;i++)
			{
				time_count++;
				printf("\n\t   %d-%d     \t\tIDLEcccc",time_count,time_count+1);
			}
			if(qq3==0)
			in_ten_qt=1;
			break;						//if all processes are processed so that idle is not printed 
		}	
}
	for(i=0;i<=10;i++)				//each queue has time quantum of 10 seconds
	{
		if(qq3==0 || in_ten_qt==0)		//checking if there are processes remaining in ready_q3 or 
		{						//if any process will come in ready_q3 within 10 time_quantum
			if((ready_q3+0)->pid==0)
			{
				turn=1;			//if no process remaining switch to queue_one
				break;			//switch to queue_one
			}
		}
								//else continue processing of queue_thr
		{
			time_count++;			//counting time quantum for queue_thr
			ready_queue();			//adding processes to ready queues
			printf("\n\t   %d-%d     ",time_count,time_count+1);//printing the current time interval of process

			if(((ready_q3+0)->pid)!=0)	//if ready_q3 is not empty
			{
				wait_time();
				printf("\t         %d",((ready_q3+0)->pid));	//printing current process under processing
				(ready_q3+0)->burst_time--;				//decrementing the value of burst_time after processing
				if(((ready_q3+0)->burst_time)==0)//checking if burst_time of 0,if 0 then remove the process from ready_q3
				{
					pop(ready_q3,r3+1);	//removing process from ready_q3
					r3--;				//decrementing index of ready_q3
					qq3--;			//decrementing count of remaining processes
				}
			}
			else
			printf("\t\tIDLE");			//if ready_q3 is empty then print CPU is IDLE
			if((time_count+1)==(temp_tc+10))	//if 10 seconds are over then switch to queue_thr
			{
				turn=1;				//assign turn to queue_one
				break;				//stop processing queue_thr
			}
		}
	}
}
//******************************************************************************************************
void scheduling()
{
	qq1=q1;qq2=q2;qq3=q3;
	ready_q1=(struct processs*)calloc(q1+1,sizeof(struct processs));	//allocating memory to queue_one
	ready_q2=(struct processs*)calloc(q2+1,sizeof(struct processs));	//allocating memory to queue_two
	ready_q3=(struct processs*)calloc(q3+1,sizeof(struct processs));	//allocating memory to queue_thr
	
	do							//this loop will execute until all the processes are processed
	{
		if(turn==1)					//if turn is of queue_one
			round_robin();
		if(turn==2)					//if turn is of queue_two
			priority_scheduling();
		if(turn==3)					//if turn is of queue_thr
			first_come_first_serve();
		if((in_ten_qt==0)&&((ready_q1+0)->pid==0)&&((ready_q2+0)->pid==0)&&((ready_q3+0)->pid==0))
		{
			time_count++;//the value of time_count will only increase if no processes comes in queue at current time quantum...
			printf("\n\t   %d-%d     \t\tIDLE",time_count,time_count+1); //and no process is residing in ready queue
		}
	}while((qq1>0)||(qq2>0)||(qq3>0));//contine switching between queues until all processes are processed
}


