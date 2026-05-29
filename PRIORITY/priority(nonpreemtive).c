#include <stdio.h>

struct Process
{
    int pid, at, bt, pr;
    int ct, tat, wt;
};

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    int completed = 0, time = 0;
    int visited[n];

    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
        p[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Priority: ");
        scanf("%d", &p[i].pr);
    }

    while (completed < n)
    {
        int idx = -1;
        int highestPriority = 9999;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] &&
                p[i].at <= time &&
                p[i].pr < highestPriority)
            {
                highestPriority = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1)
        {
            time++;
            continue;
        }

        time += p[idx].bt;

        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        visited[idx] = 1;
        completed++;
    }

    float avgWT = 0, avgTAT = 0;

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].pr, p[i].ct,
               p[i].tat, p[i].wt);

        avgWT += p[i].wt;
        avgTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}
