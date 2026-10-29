#include <stdio.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int x) {
    stack[++top] = x;
}

int pop() {
    return stack[top--];
}

int main() {

    FILE *fp;
    int num;
    char filename[50];

    printf("Enter File Name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("File Not Found\n");
        return 0;
    }

    while(fscanf(fp, "%d", &num) != EOF)
        push(num);

    fclose(fp);

    printf("Reverse Order:\n");

    while(top != -1)
        printf("%d ", pop());
    printf("\n");

    return 0;
}