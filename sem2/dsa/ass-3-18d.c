#include <stdio.h>
#include <stdlib.h>

#define PRIORITY 5

struct Node {
    int data;
    struct Node *next;
};

struct Node *front[PRIORITY] = {NULL};
struct Node *rear[PRIORITY] = {NULL};

void enqueue(int data, int priority) {
    if (priority < 0 || priority >= PRIORITY) {
        printf("Invalid Priority! Please enter a value between 0 and %d.\n", PRIORITY - 1);
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed! Queue Overflow\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (front[priority] == NULL) {
        front[priority] = rear[priority] = newNode;
    } else {
        rear[priority]->next = newNode;
        rear[priority] = newNode;
    }
    printf("Successfully inserted %d at Priority %d\n", data, priority);
}

void dequeue() {
    for (int i = 0; i < PRIORITY; i++) {
        if (front[i] != NULL) {
            struct Node *temp = front[i];

            printf("Deleted: %d from Priority %d\n", temp->data, i);

            front[i] = front[i]->next;

            if (front[i] == NULL)
                rear[i] = NULL;

            free(temp);
            return;
        }
    }

    printf("Queue Underflow! All priority queues are empty.\n");
}

void display() {
    int isEmpty = 1;
    printf("\n--- Current Priority Queue Status ---\n");
    for (int i = 0; i < PRIORITY; i++) {
        struct Node *temp = front[i];

        if (temp != NULL) {
            isEmpty = 0;
            printf("Priority %d: ", i);
            while (temp != NULL) {
                printf("%d -> ", temp->data);
                temp = temp->next;
            }
            printf("NULL\n");
        } else {
            printf("Priority %d: [Empty]\n", i);
        }
    }
    if (isEmpty) {
        printf("Entire Queue is completely empty.\n");
    }
}

int main() {
    int choice, data, priority;

    while (1) {
        printf("\n--- Linked List Multi-Queue Menu ---\n");
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
                printf("Enter priority (0 to %d, where 0 is highest): ", PRIORITY - 1);
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
                printf("Exiting program. Cleaning up memory...\n");
                for (int i = 0; i < PRIORITY; i++) {
                    while (front[i] != NULL) {
                        struct Node *temp = front[i];
                        front[i] = front[i]->next;
                        free(temp);
                    }
                }
                printf("Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }
    }

    return 0;
}
