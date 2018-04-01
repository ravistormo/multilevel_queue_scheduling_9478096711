#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int n,i;
struct processs
{
	int burst_time;
	int arrival_time;
	int priority;
};

void burst_assign(struct processs *pp_array);
void arrival_assign(struct processs *pp_array);
void priority_assign(struct processs *pp_array);
void display(struct processs *pp_array);

int main()
{
	system("clear");
	struct processs *p_array;
	printf("\nNumber of Processes : ");									//asking for number of processes
	scanf("%d",&n);
	p_array=(struct processs*)calloc(n,sizeof(struct processs));		//allocating number of processes
	burst_assign(p_array);												//asking BURST_TIME
	arrival_assign(p_array);											//asking ARRIVAL_TIME
	priority_assign(p_array);											//asking PRIORITY
	display(p_array);													//displaying PROCESSES along with BURST TIME and ARRIVAL TIME and PRIORITY

}

void burst_assign(struct processs *pp_array)
{
	printf("\nEnter the BURST_TIME :\n\n\tPROCESS\t\tBURST_TIME\n");
	for(i=0;i<n;i++)
	{
		printf("\n\t   P%d\t\t    ",i);
		scanf("%d",&((pp_array+i)->burst_time));
	}
}

void arrival_assign(struct processs *pp_array)
{
	system("clear");
	printf("\nNumber of Processes : %d",n);
	printf("\nEnter the ARRIVAL_TIME :\n\n\tPROCESS\t\tBURST_TIME\tARRIVAL_TIME\n");
	for(i=0;i<n;i++)
	{
		printf("\n\t   P%d\t\t   %d\t\t   ",i,((pp_array+i)->burst_time));
		scanf("%d",&((pp_array+i)->arrival_time));
	}
}
void priority_assign(struct processs *pp_array)
{
	system("clear");
	printf("\nNumber of Processes : %d",n);
	printf("\nEnter the associated PRIORITY :\n\n\tPROCESS\t\tBURST_TIME\tARRIVAL_TIME\tPRIORITY\n");
	for(i=0;i<n;i++)
	{
		printf("\n\t   P%d\t\t   %d\t\t   %d\t\t   ",i,((pp_array+i)->burst_time),((pp_array+i)->arrival_time));
		scanf("%d",&((pp_array+i)->priority));
	}
}
void display(struct processs *pp_array)
{
	printf("\n\tPROCESS\t\tBURST_TIME\tARRIVAL_TIME\tPRIORITY\n");
	for(i=0;i<n;i++)
	printf("\n\t  P%d\t\t   %d\t\t   %d\t\t   %d",i,(pp_array+i)->burst_time,(pp_array+i)->arrival_time,(pp_array+i)->priority);
	printf("\n");
}
