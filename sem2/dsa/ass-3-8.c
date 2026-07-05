#include <stdio.h>

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

/* Check Matching Pair */
int match(char open, char close)
{
    if(open == '(' && close == ')')
        return 1;

    if(open == '{' && close == '}')
        return 1;

    if(open == '[' && close == ']')
        return 1;

    return 0;
}

int main()
{
    char exp[MAX];
    int i;
    char ch, temp;

    printf("Enter Expression: ");
    scanf("%s", exp);

    for(i = 0; exp[i] != '\0'; i++)
    {
        ch = exp[i];

        /* Opening Brackets */
        if(ch == '(' || ch == '{' || ch == '[')
        {
            push(ch);
        }

        /* Closing Brackets */
        else if(ch == ')' || ch == '}' || ch == ']')
        {
            if(top == -1)
            {
                printf("Not Balanced\n");
                return 0;
            }

            temp = pop();

            if(!match(temp, ch))
            {
                printf("Not Balanced\n");
                return 0;
            }
        }
    }

    if(top == -1)
        printf("Balanced Expression\n");
    else
        printf("Not Balanced\n");

    return 0;
}
