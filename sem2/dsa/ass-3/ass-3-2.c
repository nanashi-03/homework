#include <stdio.h>

#define K 3
#define SIZE 100

int arr[SIZE];
int top[K];
int next[SIZE];
int freeTop;

void initialize() {
    int i;

    for(i=0;i<K;i++)
        top[i] = -1;

    for(i=0;i<SIZE-1;i++)
        next[i] = i + 1;

    next[SIZE-1] = -1;
    freeTop = 0;
}

void push(int item, int sn) {
    if(freeTop == -1) {
        printf("Stack Overflow\n");
        return;
    }

    int i = freeTop;
    freeTop = next[i];

    arr[i] = item;
    next[i] = top[sn];
    top[sn] = i;
}

int pop(int sn) {
    if(top[sn] == -1) {
        printf("Stack Underflow\n");
        return -1;
    }

    int i = top[sn];
    top[sn] = next[i];

    next[i] = freeTop;
    freeTop = i;

    return arr[i];
}

void display(int sn) {
    int i = top[sn];

    if(i == -1) {
        printf("Stack Empty\n");
        return;
    }

    while(i != -1) {
        printf("%d ", arr[i]);
        i = next[i];
    }
    printf("\n");
}

int main() {
    int choice, stackNo, item;

    initialize();

    do {
        printf("\n1.Push\n2.Pop\n3.Display\n4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter Stack Number(0-2): ");
                scanf("%d", &stackNo);
                printf("Enter Item: ");
                scanf("%d", &item);
                push(item, stackNo);
                break;

            case 2:
                printf("Enter Stack Number(0-2): ");
                scanf("%d", &stackNo);
                printf("Deleted = %d\n", pop(stackNo));
                break;

            case 3:
                printf("Enter Stack Number(0-2): ");
                scanf("%d", &stackNo);
                display(stackNo);
                break;
        }

    } while(choice != 4);

    return 0;
}