#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int queue[MAX];
int front = -1;
int rear = -1;

/* Enqueue */
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
        printf("%d ", queue[i]);

    printf("\n");
}

/* replace(p,e,x) */
void replaceElement(int e, int x)
{
    int i;
    int found = 0;

    if(front == -1)
    {
        printf("Queue Empty\n");
        return;
    }

    for(i = front; i <= rear; i++)
    {
        if(queue[i] == e)
        {
            queue[i] = x;
            found = 1;
        }
    }

    if(found)
        printf("All occurrences replaced successfully.\n");
    else
        printf("Element not found in queue.\n");
}

int main()
{
    int choice;
    int value;
    int e, x;

    while(1)
    {
        printf("\n===== REPLACE IN QUEUE =====\n");
        printf("1. Enqueue\n");
        printf("2. Display Queue\n");
        printf("3. Replace Element\n");
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
                printf("Enter element to replace (e): ");
                scanf("%d", &e);

                printf("Enter new value (x): ");
                scanf("%d", &x);

                replaceElement(e, x);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}