#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* Queue */
int queue[MAX];
int front = -1;
int rear = -1;

/* Stack */
int stack[MAX];
int top = -1;

/* Queue Operations */
void enqueue(int value)
{
    if(rear == MAX - 1)
    {
        printf("Queue Overflow\n");
        return;
    }

    if(front == -1)
        front = 0;

    queue[++rear] = value;
}

int dequeue()
{
    int value;

    if(front == -1)
    {
        printf("Queue Underflow\n");
        return -1;
    }

    value = queue[front++];

    if(front > rear)
    {
        front = -1;
        rear = -1;
    }

    return value;
}

/* Stack Operations */
void push(int value)
{
    if(top == MAX - 1)
    {
        printf("Stack Overflow\n");
        return;
    }

    stack[++top] = value;
}

int pop()
{
    if(top == -1)
    {
        printf("Stack Underflow\n");
        return -1;
    }

    return stack[top--];
}

/* Display Queue */
void display()
{
    int i;

    if(front == -1)
    {
        printf("Queue Empty\n");
        return;
    }

    printf("Queue : ");

    for(i = front; i <= rear; i++)
    {
        printf("%d ", queue[i]);
    }

    printf("\n");
}

/* Reverse Queue */
void reverseQueue()
{
    int value;

    if(front == -1)
    {
        printf("Queue Empty\n");
        return;
    }

    /* Queue -> Stack */
    while(front != -1)
    {
        value = dequeue();
        push(value);
    }

    /* Stack -> Queue */
    while(top != -1)
    {
        value = pop();
        enqueue(value);
    }

    printf("Queue Reversed Successfully\n");
}

int main()
{
    int choice, value;

    while(1)
    {
        printf("\n===== REVERSE QUEUE =====\n");
        printf("1. Enqueue\n");
        printf("2. Display Queue\n");
        printf("3. Reverse Queue\n");
        printf("4. Exit\n");

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
                display();
                break;

            case 3:
                reverseQueue();
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}