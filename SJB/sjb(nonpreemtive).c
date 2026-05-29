#include <stdio.h>

struct Process
{
    int pid, at, bt, ct, tat, wt;
};

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
    }

    int completed = 0, time = 0;
    int visited[n];

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    while (completed < n)
    {
        int min_bt = 9999;
        int idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && p[i].at <= time)
            {
                if (p[i].bt < min_bt)
                {
                    min_bt = p[i].bt;
                    idx = i;
                }
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

    float avgTAT = 0, avgWT = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);

        avgTAT += p[i].tat;
        avgWT += p[i].wt;
    }

    printf("\nAverage Turnaround Time = %.2f", avgTAT / n);
    printf("\nAverage Waiting Time = %.2f\n", avgWT / n);

    return 0;
}
