#include <stdio.h>

void firstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[processes];

    for(int i = 0; i < processes; i++)
        allocation[i] = -1;

    int temp[blocks];
    for(int i = 0; i < blocks; i++)
        temp[i] = blockSize[i];

    for(int i = 0; i < processes; i++)
    {
        for(int j = 0; j < blocks; j++)
        {
            if(temp[j] >= processSize[i])
            {
                allocation[i] = j;
                temp[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nFIRST FIT\n");
    printf("Process\tSize\tBlock\n");

    for(int i = 0; i < processes; i++)
    {
        printf("P%d\t%d\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[processes];

    for(int i = 0; i < processes; i++)
        allocation[i] = -1;

    int temp[blocks];
    for(int i = 0; i < blocks; i++)
        temp[i] = blockSize[i];

    for(int i = 0; i < processes; i++)
    {
        int best = -1;

        for(int j = 0; j < blocks; j++)
        {
            if(temp[j] >= processSize[i])
            {
                if(best == -1 || temp[j] < temp[best])
                    best = j;
            }
        }

        if(best != -1)
        {
            allocation[i] = best;
            temp[best] -= processSize[i];
        }
    }

    printf("\nBEST FIT\n");
    printf("Process\tSize\tBlock\n");

    for(int i = 0; i < processes; i++)
    {
        printf("P%d\t%d\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[processes];

    for(int i = 0; i < processes; i++)
        allocation[i] = -1;

    int temp[blocks];
    for(int i = 0; i < blocks; i++)
        temp[i] = blockSize[i];

    for(int i = 0; i < processes; i++)
    {
        int worst = -1;

        for(int j = 0; j < blocks; j++)
        {
            if(temp[j] >= processSize[i])
            {
                if(worst == -1 || temp[j] > temp[worst])
                    worst = j;
            }
        }

        if(worst != -1)
        {
            allocation[i] = worst;
            temp[worst] -= processSize[i];
        }
    }

    printf("\nWORST FIT\n");
    printf("Process\tSize\tBlock\n");

    for(int i = 0; i < processes; i++)
    {
        printf("P%d\t%d\t", i + 1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main()
{
    int blocks, processes;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);

    int blockSize[blocks];

    printf("Enter block sizes:\n");
    for(int i = 0; i < blocks; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &processes);

    int processSize[processes];

    printf("Enter process sizes:\n");
    for(int i = 0; i < processes; i++)
        scanf("%d", &processSize[i]);

    firstFit(blockSize, blocks, processSize, processes);
    bestFit(blockSize, blocks, processSize, processes);
    worstFit(blockSize, blocks, processSize, processes);

    return 0;
}
