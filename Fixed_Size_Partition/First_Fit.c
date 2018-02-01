#include<stdio.h>
int main()
{
        int num_partition,num_process;
        int part[10],proc[10];
        int partition_check[10]={0,0,0,0,0,0,0,0,0,0}; 
            printf("\n Memory Allocation Using First Fit Method in Fixed Size Partitioning!!\n");
        printf("Enter the number of partitions:");
        scanf("%d",&num_partition);
        if(num_partition>10)
        {
                printf("Sorry!!! Maximum 10 partition you can have......");
        }
        else
        {
                printf("Enter the number of process:");
                scanf("%d",&num_process);
                int allocation[num_process];
                for(int i=0;i<num_process;i++)
                {
                        allocation[i]=0;
                 }
                
                printf("Enter the sizes of all the partitions:\n");
                for(int i=0;i<num_partition;i++)
                {
                        printf("Size of %d partition : ", i+1);
                        scanf("%d",&part[i]);
                }
                
                printf("Enter the sizes of all the process: \n");
                for(int i=0;i<num_process;i++)
                {
                        printf("Size of %d process : " ,i+1);
                        scanf("%d",&proc[i]);
                 }
                 
                 for(int i=0;i<num_process;i++)
                 {
                        for(int j=0;j<num_partition;j++)
                        {
                                if(part[j]>=proc[i])
                                {
                                        allocation[i]=j+1;
                                        part[j]=part[j]-proc[i];
                                        //partition_check[j]=1;
                                        break;
                                  }
                        }
                }
                
               printf("\nProcess List \tProcess Size \t Allocated Block\n");
               for(int i=0;i<num_process;i++)
               {
               
                        printf("\t%d\t\t%d\t\t\t",i+1,proc[i]);
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
  
         return 0;

}

