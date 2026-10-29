#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int stack[MAX];
int top = -1;

int isFull() {
    return (top == MAX - 1);
}

int isEmpty() {
    return (top == -1);
}

int peek(){
    return stack[top];
}

void push(int val){
    if (isFull()){
        printf("Stack Overflow\n");
    }else {
        stack[++top] = val;
    }
}

int pop() {
    if (isEmpty()){
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];
}

void display(){
    if (isEmpty()){
        printf("Stack Empty\n");
    }else {
        for (int i = top; i >= 0; i--){
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}

int main(){
    int choice, value;

    while (1) {
        printf("\n*** STACK OPERATIONS MENU ***\n");
        printf("1. Push (Insert)\n");
        printf("2. Pop (Delete)\n");
        printf("3. Peek (Top Element)\n");
        printf("4. Display Stack\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:

                printf("Popped element: %d\n", pop());
                break;

            case 3:
                if (isEmpty()) {
                    printf("Stack is empty.\n");
                } else {
                    printf("Top element is: %d\n", peek());
                }
                break;

            case 4:
                display();
                break;

            case 5:
                printf("Exiting program. Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice! Please select between 1 and 5.\n");
        }
    }
    return 0;
}