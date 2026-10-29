#include <stdio.h>
#include <stdlib.h>

#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

/* Enqueue */
void enqueue(int value)
{
    if((front == 0 && rear == MAX - 1) ||
       (front == rear + 1))
    {
        printf("Queue Overflow\n");
        return;
    }

    if(front == -1)
    {
        front = rear = 0;
    }
    else if(rear == MAX - 1)
    {
        rear = 0;
    }
    else
    {
        rear++;
    }

    queue[rear] = value;

    printf("%d inserted successfully.\n", value);
}

/* Dequeue */
void dequeue()
{
    if(front == -1)
    {
        printf("Queue Underflow\n");
        return;
    }

    printf("Deleted Element = %d\n", queue[front]);

    if(front == rear)
    {
        front = rear = -1;
    }
    else if(front == MAX - 1)
    {
        front = 0;
    }
    else
    {
        front++;
    }
}

/* Peek */
void peek()
{
    if(front == -1)
    {
        printf("Queue Empty\n");
        return;
    }

    printf("Front Element = %d\n", queue[front]);
}

/* Display */
void display()
{
    int i;

    if(front == -1)
    {
        printf("Queue Empty\n");
        return;
    }

    printf("Queue Elements : ");

    if(front <= rear)
    {
        for(i = front; i <= rear; i++)
            printf("%d ", queue[i]);
    }
    else
    {
        for(i = front; i < MAX; i++)
            printf("%d ", queue[i]);

        for(i = 0; i <= rear; i++)
            printf("%d ", queue[i]);
    }

    printf("\n");
}

int main()
{
    int choice;
    int value;

    while(1)
    {
        printf("\n===== CIRCULAR QUEUE =====\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter Value: ");
                scanf("%d", &value);

                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                peek();
                break;

            case 4:
                display();
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}