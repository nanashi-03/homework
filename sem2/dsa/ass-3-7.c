#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int x)
{
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = x;
}

int pop()
{
    if(top == -1)
    {
        printf("Stack Underflow\n");
        return -1;
    }

    return stack[top--];
}

int main()
{
    char postfix[MAX];
    int op1, op2, result;

    printf("Enter Space-Separated Postfix Expression: ");
    fgets(postfix, MAX, stdin);

    char *token = strtok(postfix, " \n");

    while (token != NULL)
    {
        if (strlen(token) == 1 && (token[0] == '+' || token[0] == '-' ||
                                   token[0] == '*' || token[0] == '/' || token[0] == '^'))
        {
            char ch = token[0];
            op2 = pop();
            op1 = pop();

            switch(ch)
            {
                case '+':
                    result = op1 + op2;
                    break;

                case '-':
                    result = op1 - op2;
                    break;

                case '*':
                    result = op1 * op2;
                    break;

                case '/':
                    if (op2 == 0) {
                        printf("Error: Division by zero\n");
                        return 1;
                    }
                    result = op1 / op2;
                    break;

                case '^':
                    result = (int)pow(op1, op2);
                    break;
            }

            push(result);
        }
        else
        {
            push(atoi(token));
        }
\
        token = strtok(NULL, " \n");
    }

    printf("Result = %d\n", pop());

    return 0;
}
