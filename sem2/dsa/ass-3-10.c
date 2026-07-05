#include <stdio.h>
#include <stdlib.h>

#define MAXQ 5
#define SIZE 100

int queue[MAXQ][SIZE];
int front[MAXQ];
int rear[MAXQ];

void initialize()
{
    int i;

    for(i = 0; i < MAXQ; i++)
    {
        front[i] = -1;
        rear[i] = -1;
    }
}

/* Enqueue */
void enqueue(int qno, int value)
{
    if(qno < 1 || qno > MAXQ)
    {
        printf("Invalid Queue Number\n");
        return;
    }

    qno--;

    if(rear[qno] == SIZE - 1)
    {
        printf("Queue Overflow\n");
        return;
    }

    if(front[qno] == -1)
        front[qno] = 0;

    queue[qno][++rear[qno]] = value;

    printf("%d inserted into Queue %d\n",
           value, qno + 1);
}

/* Dequeue */
void dequeue(int qno)
{
    if(qno < 1 || qno > MAXQ)
    {
        printf("Invalid Queue Number\n");
        return;
    }

    qno--;

    if(front[qno] == -1 ||
       front[qno] > rear[qno])
    {
        printf("Queue Underflow\n");
        return;
    }

    printf("Deleted = %d\n",
           queue[qno][front[qno]]);

    front[qno]++;

    if(front[qno] > rear[qno])
    {
        front[qno] = -1;
        rear[qno] = -1;
    }
}

/* Display Queue */
void display(int qno)
{
    int i;

    if(qno < 1 || qno > MAXQ)
    {
        printf("Invalid Queue Number\n");
        return;
    }

    qno--;

    if(front[qno] == -1)
    {
        printf("Queue Empty\n");
        return;
    }

    printf("Queue %d : ", qno + 1);

    for(i = front[qno];
        i <= rear[qno];
        i++)
    {
        printf("%d ",
               queue[qno][i]);
    }

    printf("\n");
}

int main()
{
    int choice;
    int qno;
    int value;

    initialize();

    while(1)
    {
        printf("\n===== MULTIPLE QUEUES =====\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:

                printf("Enter Queue Number (1-%d): ",
                       MAXQ);
                scanf("%d", &qno);

                printf("Enter Value: ");
                scanf("%d", &value);

                enqueue(qno, value);
                break;

            case 2:

                printf("Enter Queue Number (1-%d): ",
                       MAXQ);
                scanf("%d", &qno);

                dequeue(qno);
                break;

            case 3:

                printf("Enter Queue Number (1-%d): ",
                       MAXQ);
                scanf("%d", &qno);

                display(qno);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}