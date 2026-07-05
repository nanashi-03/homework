#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

typedef struct Node Node;

Node *front = NULL;
Node *rear = NULL;

/* Insert at Front */
void insertFront(int value)
{
    Node *newNode;

    newNode = (Node*)malloc(sizeof(Node));

    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = front;

    if(front == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        front->prev = newNode;
        front = newNode;
    }

    printf("%d inserted at front.\n", value);
}

/* Insert at Rear */
void insertRear(int value)
{
    Node *newNode;

    newNode = (Node*)malloc(sizeof(Node));

    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = rear;

    if(rear == NULL)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    printf("%d inserted at rear.\n", value);
}

/* Delete Front */
void deleteFront()
{
    Node *temp;

    if(front == NULL)
    {
        printf("Deque Underflow\n");
        return;
    }

    temp = front;

    printf("Deleted = %d\n", front->data);

    front = front->next;

    if(front == NULL)
    {
        rear = NULL;
    }
    else
    {
        front->prev = NULL;
    }

    free(temp);
}

/* Delete Rear */
void deleteRear()
{
    Node *temp;

    if(rear == NULL)
    {
        printf("Deque Underflow\n");
        return;
    }

    temp = rear;

    printf("Deleted = %d\n", rear->data);

    rear = rear->prev;

    if(rear == NULL)
    {
        front = NULL;
    }
    else
    {
        rear->next = NULL;
    }

    free(temp);
}

/* Display */
void display()
{
    Node *temp;

    if(front == NULL)
    {
        printf("Deque Empty\n");
        return;
    }

    temp = front;

    printf("Deque : ");

    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int main()
{
    int choice;
    int value;

    while(1)
    {
        printf("\n===== DEQUE MENU =====\n");
        printf("1. Insert Front\n");
        printf("2. Insert Rear\n");
        printf("3. Delete Front\n");
        printf("4. Delete Rear\n");
        printf("5. Display\n");
        printf("6. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter Value: ");
                scanf("%d", &value);

                insertFront(value);
                break;

            case 2:
                printf("Enter Value: ");
                scanf("%d", &value);

                insertRear(value);
                break;

            case 3:
                deleteFront();
                break;

            case 4:
                deleteRear();
                break;

            case 5:
                display();
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}