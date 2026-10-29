#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int priority;
    struct Node *next;
};

struct Node *front = NULL;

void enqueue(int data, int priority) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed! Queue Overflow\n");
        return;
    }
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;

    if (front == NULL || priority < front->priority) {
        newNode->next = front;
        front = newNode;
        printf("Successfully inserted %d with priority %d\n", data, priority);
        return;
    }

    struct Node *temp = front;

    while (temp->next != NULL && temp->next->priority <= priority)
        temp = temp->next;

    newNode->next = temp->next;
    temp->next = newNode;
    printf("Successfully inserted %d with priority %d\n", data, priority);
}

void dequeue() {
    if (front == NULL) {
        printf("Queue Underflow! Queue Empty\n");
        return;
    }

    struct Node *temp = front;

    printf("Deleted: %d (Priority: %d)\n", temp->data, temp->priority);

    front = front->next;

    free(temp);
}

void display() {
    if (front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node *temp = front;

    printf("Priority Queue: ");
    while (temp != NULL) {
        printf("%d(P%d) -> ", temp->data, temp->priority);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int choice, data, priority;

    while (1) {
        printf("\n--- Priority Queue Menu (Linked List) ---\n");
        printf("1. Insert (Enqueue)\n");
        printf("2. Delete (Dequeue)\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter priority (lower number = higher priority): ");
                scanf("%d", &priority);
                enqueue(data, priority);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting program. Goodbye!\n");

                while (front != NULL) {
                    dequeue();
                }
                exit(0);

            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }
    }

    return 0;
}
