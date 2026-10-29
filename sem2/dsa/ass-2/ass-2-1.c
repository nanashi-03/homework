#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
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
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void createList(Node** head) {
    int n, val;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter value: ");
        scanf("%d", &val);

        Node* newNode = createNode(val);

        if (*head == NULL) {
            *head = newNode;
        } else {
            Node* temp = *head;
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newNode;
        }
    }
}

void insertFront(Node** head, int val) {
    Node* newNode = createNode(val);
    newNode->next = *head;
    *head = newNode;
}

void insertEnd(Node** head, int val) {
    Node* newNode = createNode(val);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
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
    temp->next = newNode;
}

void insertBeforeK(Node** head, int k, int val) {
    if (k == 1) {
        insertFront(head, val);
        return;
    }

    Node* temp = *head;

    for (int i = 1; i < k - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position.\n");
        return;
    }

    Node* newNode = createNode(val);
    newNode->next = temp->next;
    temp->next = newNode;
}

void insertBeforeValue(Node** head, int key, int val) {
    if (*head == NULL)
        return;

    if ((*head)->data == key) {
        insertFront(head, val);
        return;
    }

    Node* temp = *head;

    while (temp->next != NULL && temp->next->data != key)
        temp = temp->next;

    if (temp->next == NULL) {
        printf("Value not found.\n");
        return;
    }

    Node* newNode = createNode(val);
    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteFirst(Node** head) {
    if (*head == NULL)
        return;

    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void deleteLast(Node** head) {
    if (*head == NULL)
        return;

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    Node* temp = *head;

    while (temp->next->next != NULL)
        temp = temp->next;

    free(temp->next);
    temp->next = NULL;
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
    free(del);
}

void deleteBeforeK(Node** head, int k) {
    if (k <= 2 || *head == NULL)
        return;

    Node* temp = *head;

    for (int i = 1; i < k - 2 && temp->next != NULL; i++)
        temp = temp->next;

    Node* del = temp->next;
    temp->next = del->next;
    free(del);
}

void deleteK(Node** head, int k) {
    if (k == 1) {
        deleteFirst(head);
        return;
    }

    Node* temp = *head;

    for (int i = 1; i < k - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL) {
        printf("Invalid position.\n");
        return;
    }

    Node* del = temp->next;
    temp->next = del->next;
    free(del);
}

void deleteValue(Node** head, int key) {
    if (*head == NULL)
        return;

    if ((*head)->data == key) {
        deleteFirst(head);
        return;
    }

    Node* temp = *head;

    while (temp->next != NULL && temp->next->data != key)
        temp = temp->next;

    if (temp->next == NULL) {
        printf("Value not found.\n");
        return;
    }

    Node* del = temp->next;
    temp->next = del->next;
    free(del);
}

void reverseList(Node** head) {
    Node *prev = NULL, *curr = *head, *next;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    *head = prev;
}

void sortList(Node* head) {
    Node *i, *j;
    int temp;

    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

void search(Node* head, int key) {
    int pos = 1;

    while (head != NULL) {
        if (head->data == key) {
            printf("Element found at position %d\n", pos);
            return;
        }

        head = head->next;
        pos++;
    }

    printf("Element not found.\n");
}

Node* mergeLists(Node* l1, Node* l2) {
    Node dummy;
    Node* tail = &dummy;

    dummy.next = NULL;

    while (l1 != NULL && l2 != NULL) {
        if (l1->data < l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }

        tail = tail->next;
    }

    if (l1 != NULL)
        tail->next = l1;
    else
        tail->next = l2;

    return dummy.next;
}

void concatenate(Node** l1, Node* l2) {
    if (*l1 == NULL) {
        *l1 = l2;
        return;
    }

    Node* temp = *l1;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = l2;
}

int areEqual(Node* l1, Node* l2) {
    while (l1 != NULL && l2 != NULL) {
        if (l1->data != l2->data)
            return 0;

        l1 = l1->next;
        l2 = l2->next;
    }

    return (l1 == NULL && l2 == NULL);
}

int main() {
    Node *list1 = NULL, *list2 = NULL, *merged = NULL;

    int choice, val, k, key;

    while (1) {
        printf("\n--- MENU ---\n");
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
        printf("16. Sort List\n");
        printf("17. Search Element\n");
        printf("18. Merge Two Sorted Lists\n");
        printf("19. Concatenate Two Lists\n");
        printf("20. Compare Two Lists\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            list1 = NULL;
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
            break;

        case 16:
            sortList(list1);
            break;

        case 17:
            printf("Enter element to search: ");
            scanf("%d", &key);
            search(list1, key);
            break;

        case 18:
            printf("Create second sorted list:\n");
            createList(&list2);
            sortList(list1);
            sortList(list2);

            merged = mergeLists(list1, list2);
            list2 = NULL;
            list1 = merged;

            printf("Merged List:\n");
            printList(merged);
            break;

        case 19:
            printf("Create second list:\n");
            createList(&list2);

            concatenate(&list1, list2);
            list2 = NULL;

            printf("Concatenated List:\n");
            printList(list1);
            break;

        case 20:
            printf("Create second list:\n");
            createList(&list2);

            if (areEqual(list1, list2))
                printf("Lists are equal.\n");
            else
                printf("Lists are not equal.\n");

            break;

        case 0:
            exit(0);

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
