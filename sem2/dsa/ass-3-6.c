#include <stdio.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

/* Stack Operations */
void push(char ch)
{
    stack[++top] = ch;
}

char pop()
{
    if(top == -1)
        return '\0';

    return stack[top--];
}

char peek()
{
    if(top == -1)
        return '\0';

    return stack[top];
}

/* Precedence Function */
int precedence(char op)
{
    switch(op)
    {
        case '^':
            return 3;

        case '*':
        case '/':
            return 2;

        case '+':
        case '-':
            return 1;

        default:
            return 0;
    }
}

int main()
{
    char infix[MAX];
    char postfix[MAX];
    int i, j = 0;

    printf("Enter Infix Expression: ");
    scanf("%s", infix);

    for(i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];

        /* Operand */
        if(isalnum(ch))
        {
            postfix[j++] = ch;
        }

        /* Left Parenthesis */
        else if(ch == '(')
        {
            push(ch);
        }

        /* Right Parenthesis */
        else if(ch == ')')
        {
            while(top != -1 && peek() != '(')
            {
                postfix[j++] = pop();
            }

            pop(); // remove '('
        }

        /* Operator */
        else
        {
            while(top != -1 && precedence(peek()) >= precedence(ch))
            {
                postfix[j++] = pop();
            }

            push(ch);
        }
    }

    /* Pop Remaining Operators */
    while(top != -1)
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';

    printf("Postfix Expression = %s\n", postfix);

    return 0;
}
