#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    struct Node* next;
} Node;

typedef struct DNode {
    int id;
    struct DNode* prev;
    struct DNode* next;
} DNode;

int D2Array(int n, int k) {
    int** arr = (int**)malloc(2 * sizeof(int*));
    arr[0] = (int*)malloc(n * sizeof(int));
    arr[1] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[0][i] = i + 1;
        arr[1][i] = 1;
    }

    int remaining = n;
    int index = 0;

    while (remaining > 1) {
        int count = 0;
        while (count < k) {
            if (arr[1][index] == 1) {
                count++;
                if (count == k) {
                    arr[1][index] = 0;
                    remaining--;
                }
            }
            if (remaining == 1) break;
            index = (index + 1) % n;
        }
    }

    int survivor = -1;
    for (int i = 0; i < n; i++) {
        if (arr[1][i] == 1) {
            survivor = arr[0][i];
            break;
        }
    }

    free(arr[0]);
    free(arr[1]);
    free(arr[2]);
    free(arr);

    return survivor;
}


int CircularList(int n, int k) {
    if (n == 1) return 1;

    Node* head = (Node*)malloc(sizeof(Node));
    head->id = 1;
    head->next = head;
    Node* tail = head;

    for (int i = 2; i <= n; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->id = i;
        newNode->next = head;
        tail->next = newNode;
        tail = newNode;
    }

    Node* curr = head;
    Node* prev = tail;

    while (curr->next != curr) {
        for (int count = 1; count < k; count++) {
            prev = curr;
            curr = curr->next;
        }

        prev->next = curr->next;
        Node* temp = curr;
        curr = curr->next;
        free(temp);
    }

    int survivor = curr->id;
    free(curr);

    return survivor;
}


int CircularDLList(int n, int k) {
    if (n == 1) return 1;

    DNode* head = (DNode*)malloc(sizeof(DNode));
    head->id = 1;
    head->next = head;
    head->prev = head;
    DNode* tail = head;

    for (int i = 2; i <= n; i++) {
        DNode* newNode = (DNode*)malloc(sizeof(DNode));
        newNode->id = i;

        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;

        tail = newNode;
    }

    DNode* curr = head;

    while (curr->next != curr) {
        for (int count = 1; count < k; count++) {
            curr = curr->next;
        }

        DNode* temp = curr;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        curr = curr->next;
        free(temp);
    }

    int survivor = curr->id;
    free(curr);

    return survivor;
}

int main() {
    int choice, n, k;

    while (1) {
        printf("\nPick method:");
        printf("\n1. Solve using 2D Array");
        printf("\n2. Solve using Circular Singly Linked List");
        printf("\n3. Solve using Circular Doubly Linked List");
        printf("\n0. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        if (choice >= 1 && choice <= 3) {
            printf("Enter total number of people (n): ");
            scanf("%d", &n);
            printf("Enter elimination step size (k): ");
            scanf("%d", &k);

            if (n <= 0 || k <= 0) {
                printf("Invalid configuration parameters. Try values > 0.\n");
                continue;
            }
        }

        switch (choice) {
            case 1:
                printf("\n[2D Array] The survivor is person #%d\n", D2Array(n, k));
                break;
            case 2:
                printf("\n[Circular SLL] The survivor is person #%d\n", CircularList(n, k));
                break;
            case 3:
                printf("\n[Circular DLL] The survivor is person #%d\n", CircularDLList(n, k));
                break;
            default:
                printf("\nInvalid selection. Choose an option from 0 to 3.\n");
        }
    }
    return 0;
}
