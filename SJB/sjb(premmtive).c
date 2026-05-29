#include <stdio.h>

struct Process
{
    int pid, at, bt, rt, ct, tat, wt;
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

        p[i].rt = p[i].bt;
    }

    int complete = 0, time = 0;

    while (complete < n)
    {
        int min = 9999;
        int idx = -1;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time &&
                p[i].rt > 0 &&
                p[i].rt < min)
            {
                min = p[i].rt;
                idx = i;
            }
        }

        if (idx == -1)
        {
            time++;
            continue;
        }

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0)
        {
            complete++;

            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
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
