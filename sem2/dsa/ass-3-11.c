#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* Queue X */
int qx[MAX];
int fx = -1, rx = -1;

/* Queue Y */
int qy[MAX];
int fy = -1, ry = -1;

/* Enqueue in Queue X */
void enqueueX(int value)
{
    if(rx == MAX - 1)
    {
        printf("Queue X Overflow\n");
        return;
    }

    if(fx == -1)
        fx = 0;

    qx[++rx] = value;
}

/* Enqueue in Queue Y */
void enqueueY(int value)
{
    if(ry == MAX - 1)
    {
        printf("Queue Y Overflow\n");
        return;
    }

    if(fy == -1)
        fy = 0;

    qy[++ry] = value;
}

/* Dequeue from Queue X */
int dequeueX()
{
    int value;

    if(fx == -1)
        return -1;

    value = qx[fx++];

    if(fx > rx)
    {
        fx = -1;
        rx = -1;
    }

    return value;
}

/* Display Queue X */
void displayX()
{
    int i;

    if(fx == -1)
    {
        printf("Queue X Empty\n");
        return;
    }

    printf("Queue X : ");

    for(i = fx; i <= rx; i++)
        printf("%d ", qx[i]);

    printf("\n");
}

/* Display Queue Y */
void displayY()
{
    int i;

    if(fy == -1)
    {
        printf("Queue Y Empty\n");
        return;
    }

    printf("Queue Y : ");

    for(i = fy; i <= ry; i++)
        printf("%d ", qy[i]);

    printf("\n");
}

/* Append X to Y */
void appendQueue()
{
    int value;

    if(fx == -1)
    {
        printf("Queue X Empty\n");
        return;
    }

    while(fx != -1)
    {
        value = dequeueX();
        enqueueY(value);
    }

    printf("Queue X appended to Queue Y successfully.\n");
}

int main()
{
    int choice;
    int value;

    while(1)
    {
        printf("\n===== APPEND QUEUES =====\n");
        printf("1. Insert into Queue X\n");
        printf("2. Insert into Queue Y\n");
        printf("3. Display Queue X\n");
        printf("4. Display Queue Y\n");
        printf("5. Append X to Y\n");
        printf("6. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter Value: ");
                scanf("%d", &value);
                enqueueX(value);
                break;

            case 2:
                printf("Enter Value: ");
                scanf("%d", &value);
                enqueueY(value);
                break;

            case 3:
                displayX();
                break;

            case 4:
                displayY();
                break;

            case 5:
                appendQueue();
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}