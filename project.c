#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

struct processs
{
	int burst_time;
	int arrival_time;
	int priority;
};
int main()
{
	system("clear");

	//data types
	int n;
	int i;
	int flag=0;
	struct processs *process_array;

	//asking for number of processes
	printf("\nNumber of Processes : ");
	scanf("%d",&n);

	//allocating number of processes
	process_array=(struct processs*)calloc(n,sizeof(struct processs));

	//asking BURST_TIME
	printf("\nEnter the BURST_TIME :\n\n\tPROCESS\t\tBURST_TIME\n");
	for(i=0;i<n;i++)
	{
		printf("\n\t   P%d\t\t    ",i);
		scanf("%d",&((process_array+i)->burst_time));
	}
/********************************************************************
	 //displaying process_array burst_time value
	for(i=0;i<n;i++)
	printf("%d\t",(process_array+i)->burst_time);
*********************************************************************/


	//asking ARRIVAL_TIME
	system("clear");
	printf("\nNumber of Processes : %d",n);
	printf("\nEnter the ARRIVAL_TIME :\n\n\tPROCESS\t\tBURST_TIME\tARRIVAL_TIME\n");
	for(i=0;i<n;i++)
	{
		printf("\n\t   P%d\t\t   %d\t\t   ",i,((process_array+i)->burst_time));
		scanf("%d",&((process_array+i)->arrival_time));
	}

	//asking PRIORITY
	system("clear");
	printf("\nNumber of Processes : %d",n);
	printf("\nEnter the associated PRIORITY :\n\n\tPROCESS\t\tBURST_TIME\tARRIVAL_TIME\tPRIORITY\n");
	for(i=0;i<n;i++)
	{
		printf("\n\t   P%d\t\t   %d\t\t   %d\t\t   ",i,((process_array+i)->burst_time),((process_array+i)->arrival_time));
		scanf("%d",&((process_array+i)->priority));
	}
}

