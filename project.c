#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int n,i;
int q1=0,q2=0,q3=0;
struct processs
{
	int burst_time;
	int arrival_time;
	int priority;
}*p_array;
struct queuee
{
	char pro[3];
	int burst_time;
	int arrival_time;
	int priority;
}*queue_one, *queue_two, *queue_three;
//**********************************************************************************************
void burst_assign(struct processs *pp_array);		//function to assign burst time
void arrival_assign(struct processs *pp_array);		//function to assign arrival time
void priority_assign(struct processs *pp_array);	//function to assign priority
void display(struct processs *pp_array);			//function to display all processes
void display1(struct queuee *qq_array,int q);		//function to display queue wise processes
void queue_size(struct processs *pp_array);			//function to determine the size of each queue
void queue_assign(struct processs *pp_array);		//function for assigning queue
//***********************************************************************************************
//**************************************MAIN*****************************************************
int main()
{
	system("cls");	

	printf("\nNumber of Processes : ");scanf("%d",&n);				//asking for number of processes
	p_array=(struct processs*)calloc(n,sizeof(struct processs));	//allocating number of processes
	burst_assign(p_array);											//asking BURST_TIME
	arrival_assign(p_array);										//asking ARRIVAL_TIME
	priority_assign(p_array);										//asking PRIORITY
	system("cls");
	display(p_array);												//displaying PROCESSES along with BURST TIME and ARRIVAL TIME and PRIORITY
	
	queue_size(p_array);											//determining size of each queue q1,q2,q3
	queue_one=(struct queuee*)calloc(q1,sizeof(struct queuee));		//allocating memory to queue_one
	queue_two=(struct queuee*)calloc(q2,sizeof(struct queuee));		//allocating memory to queue_two
	queue_three=(struct queuee*)calloc(q3,sizeof(struct queuee));	//allocating memory to queue_three
	queue_assign(p_array);											//assigning processes to respective queue
	printf("\nDividing processes on basis of PRIORITY.\n\nPRIORITY\t\tQUEUE\n [1,3]\t\t\t Q1\n [4,7]\t\t\t Q2\n[8, 10]\t\t\t Q3\n");
	printf("\nThe generated QUEUES are :\nQUEUE 1 : (%d pocesses)\n",q1);
	display1(queue_one,q1);
	printf("\n\nQUEUE 2 : (%d processes)\n",q2);
	display1(queue_two,q2);
	printf("\n\nQUEUE 3 : (%d processes)\n",q3);
	display1(queue_three,q3);

}
//*************************************************************************************************
void burst_assign(struct processs *pp_array)
{
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the BURST_TIME :\n\n\tPROCESS\t\tBURST_TIME\n");
	for(i=0;i<n;i++)
	{
		do
		{
			printf("\t   P%d\t\t    ",i);
			scanf("%d",&((pp_array+i)->burst_time));
			if(((pp_array+i)->burst_time)<=0)
			printf("\t\t\t\t\tBURST_TIME can not be <=0 !!Enter Again...\n");
		}while(((pp_array+i)->burst_time)<=0);
	}
}
//**************************************************************************************************
void arrival_assign(struct processs *pp_array)
{
	system("cls");
	printf("\nNumber of Processes : %d",n);
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the ARRIVAL_TIME :\n\n\tPROCESS\t\tBURST_TIME\tARRIVAL_TIME\n");
	for(i=0;i<n;i++)
	{
		do
		{
			printf("\t   P%d\t\t   %d\t\t   ",i,((pp_array+i)->burst_time));
			scanf("%d",&((pp_array+i)->arrival_time));
			if(((pp_array+i)->arrival_time)<0)
			printf("\t\t\t\t\t\tARRIVAL_TIME can not be <0 !!Enter Again...\n");
		}while(((pp_array+i)->arrival_time)<0);
	}
}
//**************************************************************************************************
void priority_assign(struct processs *pp_array)
{
	system("cls");
	printf("\nNumber of Processes : %d",n);
	printf("\n\t\t\t\t\tINPUT ONLY INTEGER VALUES !!!\n");
	printf("\nEnter the associated PRIORITY[1-10]:\n\n\tPROCESS\t\tBURST_TIME\tARRIVAL_TIME\tPRIORITY\n");
	for(i=0;i<n;i++)
	{
		do
		{
			printf("\t   P%d\t\t   %d\t\t   %d\t\t   ",i,((pp_array+i)->burst_time),((pp_array+i)->arrival_time));
			scanf("%d",&((pp_array+i)->priority));
			if((((pp_array+i)->priority)<1)||(((pp_array+i)->priority)>10))
			printf("\t\t\t\t\t\t\tPRIORITY should be in range [1,10] !!Enter Again...\n");
		}while((((pp_array+i)->priority)<1)||(((pp_array+i)->priority)>10));
	}
}
//*****************************************************************************************************
void display(struct processs *pp_array)
{
	system("cls");
	printf("\nNumber of Processes : %d",n);
	printf("\n\tPROCESS\t\tBURST_TIME\tARRIVAL_TIME\tPRIORITY\n");
	for(i=0;i<n;i++)
	printf("\n\t  P%d\t\t   %d\t\t   %d\t\t   %d",i,(pp_array+i)->burst_time,(pp_array+i)->arrival_time,(pp_array+i)->priority);
	printf("\n");
}
//******************************************************************************************************
void display1(struct queuee *qq_array,int q)
{
	printf("\n\tPROCESS\t\tBURST_TIME\tARRIVAL_TIME\tPRIORITY\n");
	for(i=0;i<q;i++)
	printf("\n\t  %s\t\t   %d\t\t   %d\t\t   %d",(qq_array+i)->pro,(qq_array+i)->burst_time,(qq_array+i)->arrival_time,(qq_array+i)->priority);
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
			{
				((queue_one+j1)->pro[0])='P';
				((queue_one+j1)->pro[1])=i+'0';
				((queue_one+j1)->pro[2])='\0';
			}
			((queue_one+j1)->burst_time)  =((pp_array+i)->burst_time);
			((queue_one+j1)->arrival_time)=((pp_array+i)->arrival_time);
			((queue_one+j1)->priority)    =((pp_array+i)->priority);
		}
		else if((((pp_array+i)->priority)>=4)&&(((pp_array+i)->priority)<=7))
		{
			j2++;	
			{
				((queue_two+j2)->pro[0])='P';
				((queue_two+j2)->pro[1])=i+'0';
				((queue_two+j2)->pro[2])='\0';
			}
			((queue_two+j2)->burst_time)  =((pp_array+i)->burst_time);
			((queue_two+j2)->arrival_time)=((pp_array+i)->arrival_time);
			((queue_two+j2)->priority)    =((pp_array+i)->priority);
		}
		else
		{
			j3++;	
			{
				((queue_three+j3)->pro[0])='P';
				((queue_three+j3)->pro[1])=i+'0';
				((queue_three+j3)->pro[2])='\0';
			}
			((queue_three+j3)->burst_time)  =((pp_array+i)->burst_time);
			((queue_three+j3)->arrival_time)=((pp_array+i)->arrival_time);
			((queue_three+j3)->priority)    =((pp_array+i)->priority);
		}
	}	
}
//********************************************************************************************************
