#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data;
    int priority;
} Node;

Node pq[MAX];
int size = 0;

void enqueue(int data, int priority) {
    if (size == MAX) {
        printf("Queue Overflow\n");
        return;
    }

    int i = size - 1;

    while (i >= 0 && pq[i].priority > priority) {
        pq[i + 1] = pq[i];
        i--;
    }

    pq[i + 1].data = data;
    pq[i + 1].priority = priority;
    size++;
    printf("Successfully inserted %d with priority %d\n", data, priority);
}

void dequeue() {
    if (size == 0) {
        printf("Queue Underflow\n");
        return;
    }

    printf("Deleted: %d (Priority: %d)\n", pq[0].data, pq[0].priority);

    for (int i = 1; i < size; i++)
        pq[i - 1] = pq[i];

    size--;
}

void display() {
    if (size == 0) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Priority Queue: ");
    for (int i = 0; i < size; i++)
        printf("%d(P%d) ", pq[i].data, pq[i].priority);
    printf("\n");
}

int main() {
    int choice, data, priority;

    while (1) {
        printf("\n--- Priority Queue Menu ---\n");
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
                exit(0);

            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }
    }

    return 0;
}
