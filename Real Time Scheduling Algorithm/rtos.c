#include <stdio.h>
#include <string.h>

struct Process
{
    int id;
    int burst;
    int deadline;
    int period;
    int ct, wt, tat;
};

void EDF(struct Process p[], int n)
{
    printf("\nEarliest Deadline First (EDF) Scheduling\n");
    printf("ID\tBT\tDeadline\tCT\tWT\tTAT\n");

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].deadline > p[j].deadline)
            {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;

    for (int i = 0; i < n; i++)
    {
        time += p[i].burst;

        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].burst;

        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id,
               p[i].burst,
               p[i].deadline,
               p[i].ct,
               p[i].wt,
               p[i].tat);
    }
}

void RMS(struct Process p[], int n)
{
    printf("\nRate Monotonic Scheduling (RMS)\n");
    printf("ID\tBT\tPeriod\tCT\tWT\tTAT\n");

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].period > p[j].period)
            {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;

    for (int i = 0; i < n; i++)
    {
        time += p[i].burst;

        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].burst;

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].burst,
               p[i].period,
               p[i].ct,
               p[i].wt,
               p[i].tat);
    }
}

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n], p1[n], p2[n];

    printf("Enter process details:\n");

    for (int i = 0; i < n; i++)
    {
        p[i].id = i;

        printf("\nProcess %d\n", i);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);
    }

    memcpy(p1, p, sizeof(p));
    memcpy(p2, p, sizeof(p));

    EDF(p1, n);
    RMS(p2, n);

    return 0;
}

