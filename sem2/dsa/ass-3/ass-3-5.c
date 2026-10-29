#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL;

void push(int x) {
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = x;
    newNode->next = top;
    top = newNode;
}

int pop() {
    if(top == NULL) {
        printf("Stack Empty\n");
        return -1;
    }

    struct Node *temp = top;
    int val = temp->data;

    top = top->next;
    free(temp);

    return val;
}

void display() {
    struct Node *temp = top;

    while(temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {

    int choice, item;

    do {
        printf("\n1.Push\n2.Pop\n3.Display\n4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice) {
            case 1:
                printf("Enter Item: ");
                scanf("%d",&item);
                push(item);
                break;

            case 2:
                printf("Deleted = %d\n", pop());
                break;

            case 3:
                display();
                break;
        }

    } while(choice != 4);
    printf("Exiting program.\n");

    return 0;
}
