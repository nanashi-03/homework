#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    temp->data = data;
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}

void printList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void insertFront(Node** head, int val) {
    Node* newNode = createNode(val);
    newNode->next = *head;

    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void insertEnd(Node** head, int val) {
    Node* newNode = createNode(val);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

void createList(Node** head) {
    int n, val;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter value: ");
        scanf("%d", &val);
        insertEnd(head, val);
    }
}

void insertAfterK(Node** head, int k, int val) {
    Node* temp = *head;

    for (int i = 1; i < k && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Invalid position.\n");
        return;
    }

    Node* newNode = createNode(val);
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

void insertAfterValue(Node** head, int key, int val) {
    Node* temp = *head;

    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL) {
        printf("Value not found.\n");
        return;
    }

    Node* newNode = createNode(val);
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

void insertBeforeK(Node** head, int k, int val) {
    if (k == 1) {
        insertFront(head, val);
        return;
    }

    Node* temp = *head;
    for (int i = 1; i < k && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Invalid position.\n");
        return;
    }

    Node* newNode = createNode(val);
    newNode->next = temp;
    newNode->prev = temp->prev;
    temp->prev->next = newNode;
    temp->prev = newNode;
}

void insertBeforeValue(Node** head, int key, int val) {
    if (*head == NULL) return;

    if ((*head)->data == key) {
        insertFront(head, val);
        return;
    }

    Node* temp = *head;
    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL) {
        printf("Value not found.\n");
        return;
    }

    Node* newNode = createNode(val);
    newNode->next = temp;
    newNode->prev = temp->prev;

    temp->prev->next = newNode;
    temp->prev = newNode;
}

void deleteFirst(Node** head) {
    if (*head == NULL) return;

    Node* temp = *head;
    *head = (*head)->next;

    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}

void deleteLast(Node** head) {
    if (*head == NULL) return;

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->prev->next = NULL;
    free(temp);
}

void deleteAfterK(Node** head, int k) {
    Node* temp = *head;

    for (int i = 1; i < k && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL) {
        printf("Deletion not possible.\n");
        return;
    }

    Node* del = temp->next;
    temp->next = del->next;

    if (del->next != NULL) {
        del->next->prev = temp;
    }
    free(del);
}

void deleteBeforeK(Node** head, int k) {
    if (k <= 1 || *head == NULL) {
        printf("Deletion not possible.\n");
        return;
    }

    Node* temp = *head;
    for (int i = 1; i < k && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL || temp->prev == NULL) {
        printf("Deletion not possible.\n");
        return;
    }

    Node* del = temp->prev;

    if (del->prev == NULL) {
        *head = temp;
        temp->prev = NULL;
    } else {
        del->prev->next = temp;
        temp->prev = del->prev;
    }
    free(del);
}

void deleteK(Node** head, int k) {
    if (*head == NULL) return;

    if (k == 1) {
        deleteFirst(head);
        return;
    }

    Node* temp = *head;
    for (int i = 1; i < k && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Invalid position.\n");
        return;
    }

    temp->prev->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
}

void deleteValue(Node** head, int key) {
    if (*head == NULL) return;

    if ((*head)->data == key) {
        deleteFirst(head);
        return;
    }

    Node* temp = *head;
    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL) {
        printf("Value not found.\n");
        return;
    }

    temp->prev->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
}

void reverseList(Node** head) {
    if (*head == NULL) return;

    Node* current = *head;
    Node* temp = NULL;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        current = current->prev;
    }

    if (temp != NULL) {
        *head = temp->prev;
    }
}

int main() {
    Node* list1 = NULL;
    int choice, val, k, key;

    while (1) {
        printf("\n--- MENU (Doubly Linked List) ---\n");
        printf("1. Create List 1\n");
        printf("2. Print List 1\n");
        printf("3. Insert Front\n");
        printf("4. Insert End\n");
        printf("5. Insert After kth Node\n");
        printf("6. Insert After Value\n");
        printf("7. Insert Before kth Node\n");
        printf("8. Insert Before Value\n");
        printf("9. Delete First\n");
        printf("10. Delete Last\n");
        printf("11. Delete After kth Node\n");
        printf("12. Delete Before kth Node\n");
        printf("13. Delete kth Node\n");
        printf("14. Delete By Value\n");
        printf("15. Reverse List\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            createList(&list1);
            break;
        case 2:
            printList(list1);
            break;
        case 3:
            printf("Enter value: ");
            scanf("%d", &val);
            insertFront(&list1, val);
            break;
        case 4:
            printf("Enter value: ");
            scanf("%d", &val);
            insertEnd(&list1, val);
            break;
        case 5:
            printf("Enter k and value: ");
            scanf("%d%d", &k, &val);
            insertAfterK(&list1, k, val);
            break;
        case 6:
            printf("Enter key and value: ");
            scanf("%d%d", &key, &val);
            insertAfterValue(&list1, key, val);
            break;
        case 7:
            printf("Enter k and value: ");
            scanf("%d%d", &k, &val);
            insertBeforeK(&list1, k, val);
            break;
        case 8:
            printf("Enter key and value: ");
            scanf("%d%d", &key, &val);
            insertBeforeValue(&list1, key, val);
            break;
        case 9:
            deleteFirst(&list1);
            break;
        case 10:
            deleteLast(&list1);
            break;
        case 11:
            printf("Enter k: ");
            scanf("%d", &k);
            deleteAfterK(&list1, k);
            break;
        case 12:
            printf("Enter k: ");
            scanf("%d", &k);
            deleteBeforeK(&list1, k);
            break;
        case 13:
            printf("Enter k: ");
            scanf("%d", &k);
            deleteK(&list1, k);
            break;
        case 14:
            printf("Enter value: ");
            scanf("%d", &key);
            deleteValue(&list1, key);
            break;
        case 15:
            reverseList(&list1);
            printf("List reversed.\n");
            break;
        case 0:
            // Dynamic allocation cleanup before exit
            while(list1 != NULL) {
                deleteFirst(&list1);
            }
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
