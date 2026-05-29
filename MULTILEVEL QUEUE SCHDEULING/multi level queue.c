#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 100
#define SYSTEM_TYPE 0
#define USER_TYPE 1
#define MAX_TIME 1000

typedef struct
{
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int type;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

typedef struct
{
    int data[MAX_PROCESSES];
    int front, rear, size;
} Queue;

void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isEmpty(Queue *q)
{
    return q->size == 0;
}

void enqueue(Queue *q, int val)
{
    q->rear = (q->rear + 1) % MAX_PROCESSES;
    q->data[q->rear] = val;
    q->size++;
}

int dequeue(Queue *q)
{
    int val = q->data[q->front];
    q->front = (q->front + 1) % MAX_PROCESSES;
    q->size--;
    return val;
}

int compareArrival(const void *a, const void *b)
{
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;

    if (p1->arrival_time != p2->arrival_time)
        return p1->arrival_time - p2->arrival_time;

    return p1->process_id - p2->process_id;
}

int main()
{
    Process process_list[MAX_PROCESSES];
    Queue systemQueue, userQueue;

    int n, i;

    initQueue(&systemQueue);
    initQueue(&userQueue);

    printf("Multi-Level Queue Scheduling (FCFS)\n");
    printf("System Queue > User Queue\n");
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    printf("\nNote: Type 0 = System Process, 1 = User Process\n\n");

    for (i = 0; i < n; i++)
    {
        printf("Process %d\n", i + 1);

        printf("Process ID: ");
        scanf("%d", &process_list[i].process_id);

        printf("Arrival Time: ");
        scanf("%d", &process_list[i].arrival_time);

        printf("Burst Time: ");
        scanf("%d", &process_list[i].burst_time);

        printf("Type (0=System,1=User): ");
        scanf("%d", &process_list[i].type);

        process_list[i].remaining_time =
            process_list[i].burst_time;

        process_list[i].completion_time = 0;
        process_list[i].waiting_time = 0;
        process_list[i].turnaround_time = 0;

        printf("\n");
    }

    qsort(process_list, n, sizeof(Process), compareArrival);

    int current_time = 0;
    int completed = 0;
    int idx = 0;
    int current_process_idx = -1;

    int gantt[MAX_TIME];
    int gantt_len = 0;

    while (completed < n)
    {
        while (idx < n &&
               process_list[idx].arrival_time <= current_time)
        {
            if (process_list[idx].type == SYSTEM_TYPE)
                enqueue(&systemQueue, idx);
            else
                enqueue(&userQueue, idx);

            idx++;
        }

        if (current_process_idx != -1)
        {
            if (process_list[current_process_idx].type ==
                    USER_TYPE &&
                !isEmpty(&systemQueue))
            {
                enqueue(&userQueue, current_process_idx);
                current_process_idx = -1;
            }
        }

        if (current_process_idx == -1)
        {
            if (!isEmpty(&systemQueue))
            {
                current_process_idx =
                    dequeue(&systemQueue);
            }
            else if (!isEmpty(&userQueue))
            {
                current_process_idx =
                    dequeue(&userQueue);
            }
            else
            {
                gantt[gantt_len++] = -1;
                current_time++;
                continue;
            }
        }

        process_list[current_process_idx]
            .remaining_time--;

        gantt[gantt_len++] =
            process_list[current_process_idx]
                .process_id;

        current_time++;

        if (process_list[current_process_idx]
                .remaining_time == 0)
        {
            process_list[current_process_idx]
                .completion_time = current_time;

            process_list[current_process_idx]
                .turnaround_time =
                current_time -
                process_list[current_process_idx]
                    .arrival_time;

            process_list[current_process_idx]
                .waiting_time =
                process_list[current_process_idx]
                    .turnaround_time -
                process_list[current_process_idx]
                    .burst_time;

            completed++;
            current_process_idx = -1;
        }
    }

    printf("\nGantt Chart\n");

    printf("|");
    for (i = 0; i < gantt_len; i++)
    {
        if (i == 0 || gantt[i] != gantt[i - 1])
        {
            if (gantt[i] == -1)
                printf(" IDLE |");
            else
                printf(" P%d |", gantt[i]);
        }
    }

    printf("\n");

    int time = 0;
    printf("%d", time);

    for (i = 0; i < gantt_len; i++)
    {
        time++;

        if (i == gantt_len - 1 ||
            gantt[i] != gantt[i + 1])
        {
            printf("%5d", time);
        }
    }

    printf("\n");

    printf("\nResults Summary\n");
    printf("%-5s %-6s %-6s %-6s %-6s %-5s %-5s\n",
           "PID", "Type", "AT", "BT",
           "CT", "TAT", "WT");

    float total_tat = 0;
    float total_wt = 0;

    for (i = 0; i < n; i++)
    {
        printf("P%-4d %-6s %-6d %-6d %-6d %-5d %-5d\n",
               process_list[i].process_id,
               process_list[i].type == SYSTEM_TYPE
                   ? "SYS"
                   : "USER",
               process_list[i].arrival_time,
               process_list[i].burst_time,
               process_list[i].completion_time,
               process_list[i].turnaround_time,
               process_list[i].waiting_time);

        total_tat += process_list[i].turnaround_time;
        total_wt += process_list[i].waiting_time;
    }

    printf("\nAverage Turnaround Time : %.2f\n",
           total_tat / n);

    printf("Average Waiting Time    : %.2f\n",
           total_wt / n);

    return 0;
}
