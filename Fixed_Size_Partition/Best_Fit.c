#include <stdio.h>
#include <stdlib.h>

void main()
{
    int part[10];
    int num_partition,num_process,best_index;
    printf("Memory Allocation using Best Fit Fixed Size partitioning scheme.\n");
    printf("Enter the number of partitions : ");
    scanf("%d",&num_partition);
    if(num_partition>10)
    {
        printf("Sorry!! Maximum 10 partition you can have...");
    }
    else
    {
        printf("Enter the number of process : ");
        scanf("%d",&num_process);
        int proc[num_process];
        int allocation[num_process];
        printf("Enter the size of partition : \n");
        for(int i=0;i<num_partition;i++)
        {
            printf("Size of %d partition : ",i+1);
            scanf("%d",&part[i]);

        }
        printf("Enter the size of process : \n");
        for (int i=0;i<num_process;i++)
        {
            printf("Size of %d process : ",i+1);
            scanf("%d",&proc[i]);
        }
        for(int i =0;i<num_process;i++)
        {
            best_index=-1;
            for(int j=0;j<num_partition;j++)
            {
                if(part[j]>proc[i])
                {
                    if(best_index==-1)
                    {
                        best_index=j;
                    }
                    else
                    {
                        if(part[j]<part[best_index])
                        {
                            best_index=j;
                        }
                    }
                }
            }
             allocation[i]=best_index+1;
             part[best_index]=part[best_index]-proc[i];

        }

        printf("\nProcess List \tProcess Size \t Allocated Block\n");
        for(int i=0;i<num_process;i++)
        {

            printf("\t%d\t  %d\t\t\t",i+1,proc[i]);
            if(allocation[i]!=0)
            {
                printf("%d",allocation[i]);
            }
            else
            {
                printf("Not Allocated");
            }
            printf("\n");
        }
    }
}

