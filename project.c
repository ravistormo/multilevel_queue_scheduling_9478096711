#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	system("clear");
	int i,n,*burst_array,*arrival_array,*priority_array;
	printf("\nNumber of Processes : ");
	scanf("%d",&n);

	printf("\nEnter the BURST_TIME :\n\n\tPROCESS\t\tBURST_TIME\n");
	burst_array=(int*)calloc(n,sizeof(int));
	for(i=0;i<n;i++)
	{
		printf("\n\t   P%d\t\t    ",i);
		scanf("%d",burst_array+i);
	}

	system("clear");
	printf("\nNumber of Processes : %d",n);
	printf("\nEnter the ARRIVAL_TIME :\n\n\tPROCESS\t\tBURST_TIME\tARRIVAL_TIME\n");
	arrival_array=(int*)calloc(n,sizeof(int));
	for(i=0;i<n;i++)
	{
		printf("\n\t   P%d\t\t    %d\t\t   ",i,*(burst_array+i));
		scanf("%d",&(*(arrival_array+i)));
	}

	system("clear");
	printf("\nNumber of Processes : %d",n);
	printf("\nEnter the PRIORITY associated:\n\n\tPROCESS\t\tBURST_TIME\tARRIVAL_TIME\tPRIORITY\n");
	priority_array=(int*)calloc(n,sizeof(int));
	for(i=0;i<n;i++)
	{
		printf("\n\t   P%d\t\t   %d\t\t   %d\t\t   ",i,*(burst_array+i),*(arrival_array+i));
		scanf("%d",&(*(priority_array+i)));
	}
}