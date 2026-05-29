#include <stdio.h>

#define MAX 10

int main()
{
    int n, m;

    int allocation[MAX][MAX];
    int maximum[MAX][MAX];
    int need[MAX][MAX];
    int available[MAX];

    int request[MAX];
    int process;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Maximum Matrix:\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    printf("\nEnter Process Number: ");
    scanf("%d", &process);

    printf("Enter Request Vector:\n");
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &request[i]);
    }

    int flag = 1;

    for(int i = 0; i < m; i++)
    {
        if(request[i] > need[process][i])
        {
            flag = 0;
            break;
        }
    }

    if(flag)
    {
        for(int i = 0; i < m; i++)
        {
            if(request[i] > available[i])
            {
                flag = 0;
                break;
            }
        }
    }

    if(flag)
    {
        printf("\nRequest can be granted.\n");
    }
    else
    {
        printf("\nRequest cannot be granted.\n");
    }

    return 0;
}
