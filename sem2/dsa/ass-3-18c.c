#include <stdio.h>
#include <stdlib.h>

#define PRIORITY 5
#define MAX 10

int pq[PRIORITY][MAX];
int rear[PRIORITY] = {0};

void enqueue(int data, int priority) {
    if (priority < 0 || priority >= PRIORITY) {
        printf("Invalid Priority! Please enter a priority between 0 and %d.\n", PRIORITY - 1);
        return;
    }

    if (rear[priority] == MAX) {
        printf("Queue Overflow for Priority %d\n", priority);
        return;
    }

    pq[priority][rear[priority]++] = data;
    printf("Successfully inserted %d at Priority %d\n", data, priority);
}

void dequeue() {
    for (int i = 0; i < PRIORITY; i++) {
        if (rear[i] > 0) {
            printf("Deleted: %d from Priority %d\n", pq[i][0], i);

            for (int j = 1; j < rear[i]; j++)
                pq[i][j - 1] = pq[i][j];

            rear[i]--;
            return;
        }
    }

    printf("Queue Underflow! All priority queues are empty.\n");
}

void display() {
    int isEmpty = 1;
    printf("\n--- Current Priority Queue Status ---\n");
    for (int i = 0; i < PRIORITY; i++) {
        if (rear[i] > 0) {
            isEmpty = 0;
            printf("Priority %d: ", i);
            for (int j = 0; j < rear[i]; j++)
                printf("%d ", pq[i][j]);
            printf("\n");
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
        printf("\n--- Multi-Queue Priority Queue Menu ---\n");
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
                printf("Exiting program. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }
    }

    return 0;
}
