#include <stdio.h>

void printFrames(int frame[], int frames)
{
    for(int i = 0; i < frames; i++)
    {
        if(frame[i] == -1)
            printf("-\t");
        else
            printf("%d\t", frame[i]);
    }
}

void FIFO(int pages[], int n, int frames)
{
    int frame[frames];
    int faults = 0, pos = 0;

    for(int i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\n\nFIFO PAGE REPLACEMENT\n");
    printf("Page\t");

    for(int i = 0; i < frames; i++)
        printf("F%d\t", i + 1);

    printf("Status\n");

    for(int i = 0; i < n; i++)
    {
        int hit = 0;

        for(int j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                hit = 1;
                break;
            }
        }

        if(!hit)
        {
            frame[pos] = pages[i];
            pos = (pos + 1) % frames;
            faults++;
        }

        printf("%d\t", pages[i]);
        printFrames(frame, frames);

        if(hit)
            printf("Hit");
        else
            printf("PF");

        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

void LRU(int pages[], int n, int frames)
{
    int frame[frames];
    int recent[frames];
    int faults = 0;

    for(int i = 0; i < frames; i++)
    {
        frame[i] = -1;
        recent[i] = -1;
    }

    printf("\n\nLRU PAGE REPLACEMENT\n");
    printf("Page\t");

    for(int i = 0; i < frames; i++)
        printf("F%d\t", i + 1);

    printf("Status\n");

    for(int i = 0; i < n; i++)
    {
        int hit = 0;

        for(int j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                recent[j] = i;
                hit = 1;
                break;
            }
        }

        if(!hit)
        {
            int pos = -1;

            for(int j = 0; j < frames; j++)
            {
                if(frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            if(pos == -1)
            {
                pos = 0;

                for(int j = 1; j < frames; j++)
                {
                    if(recent[j] < recent[pos])
                        pos = j;
                }
            }

            frame[pos] = pages[i];
            recent[pos] = i;
            faults++;
        }

        printf("%d\t", pages[i]);
        printFrames(frame, frames);

        if(hit)
            printf("Hit");
        else
            printf("PF");

        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

void OPTIMAL(int pages[], int n, int frames)
{
    int frame[frames];
    int faults = 0;

    for(int i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\n\nOPTIMAL PAGE REPLACEMENT\n");
    printf("Page\t");

    for(int i = 0; i < frames; i++)
        printf("F%d\t", i + 1);

    printf("Status\n");

    for(int i = 0; i < n; i++)
    {
        int hit = 0;

        for(int j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                hit = 1;
                break;
            }
        }

        if(!hit)
        {
            int pos = -1;

            for(int j = 0; j < frames; j++)
            {
                if(frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            if(pos == -1)
            {
                int farthest = -1;

                for(int j = 0; j < frames; j++)
                {
                    int nextUse = 9999;

                    for(int k = i + 1; k < n; k++)
                    {
                        if(frame[j] == pages[k])
                        {
                            nextUse = k;
                            break;
                        }
                    }

                    if(nextUse > farthest)
                    {
                        farthest = nextUse;
                        pos = j;
                    }
                }
            }

            frame[pos] = pages[i];
            faults++;
        }

        printf("%d\t", pages[i]);
        printFrames(frame, frames);

        if(hit)
            printf("Hit");
        else
            printf("PF");

        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);
}

int main()
{
    int n, frames;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter page reference string:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    FIFO(pages, n, frames);
    LRU(pages, n, frames);
    OPTIMAL(pages, n, frames);

    return 0;
}
