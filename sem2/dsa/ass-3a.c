#include <stdbool.h>
#include <stdio.h>

#define MAX 10

struct Stack {
  int arr[MAX];
  int top;
};

void initStack(struct Stack *stack) { stack->top = -1; }

bool isFull(struct Stack *stack) { return stack->top == MAX - 1; }

bool isEmpty(struct Stack *stack) { return stack->top == -1; }

void push(struct Stack *stack, int value) {
  if (isFull(stack)) {
    printf("Stack Overflow! Cannot push %d.\n", value);
    return;
  }
  stack->top++;
  stack->arr[stack->top] = value;
  printf("Pushed %d onto the stack.\n", value);
}

int pop(struct Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack Underflow! Cannot pop from an empty stack.\n");
    return -1; // Return a sentinel value indicating failure
  }
  int poppedValue = stack->arr[stack->top];
  stack->top--;
  return poppedValue;
}

int peek(struct Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack is empty.\n");
    return -1;
  }
  return stack->arr[stack->top];
}

void display(struct Stack *stack) {
  if (isEmpty(stack)) {
    printf("Stack is empty.\n");
    return;
  }
  printf("Current Stack (Top -> Bottom): ");
  for (int i = stack->top; i >= 0; i--) {
    printf("%d ", stack->arr[i]);
  }
  printf("\n");
}

int main() {
  struct Stack myStack;
  initStack(&myStack);

  push(&myStack, 10);
  push(&myStack, 20);
  push(&myStack, 30);
  display(&myStack);

  printf("Top element is: %d\n", peek(&myStack));

  printf("Popped element: %d\n", pop(&myStack));
  display(&myStack);

  push(&myStack, 40);
  push(&myStack, 50);
  push(&myStack, 60);
  push(&myStack, 70);

  return 0;
}
