#include <stdio.h>
#include <stdlib.h>

/* Node Structure */
struct Node
{
    int data;
    struct Node *next;
};

typedef struct Node Node;

Node *front = NULL;
Node *rear = NULL;

/* Enqueue */
void enqueue(int value)
{
    Node *newNode;

    newNode = (Node *)malloc(sizeof(Node));

    if(newNode == NULL)
    {
        printf("Memory Allocation Failed\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if(front == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    printf("%d inserted successfully.\n", value);
}

/* Dequeue */
void dequeue()
{
    Node *temp;

    if(front == NULL)
    {
        printf("Queue Underflow\n");
        return;
    }

    temp = front;

    printf("Deleted Element = %d\n", front->data);

    front = front->next;

    if(front == NULL)
        rear = NULL;

    free(temp);
}

/* Peek */
void peek()
{
    if(front == NULL)
    {
        printf("Queue Empty\n");
        return;
    }

    printf("Front Element = %d\n", front->data);
}

/* Display */
void display()
{
    Node *temp;

    if(front == NULL)
    {
        printf("Queue Empty\n");
        return;
    }

    temp = front;

    printf("Queue : ");

    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int main()
{
    int choice, value;

    while(1)
    {
        printf("\n===== QUEUE USING LINKED LIST =====\n");
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
                printf("Program Terminated.\n");
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}