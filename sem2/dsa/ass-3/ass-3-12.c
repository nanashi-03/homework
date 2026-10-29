#include <stdio.h>
#include <stdlib.h>

#define MAX 100

/* Queue 1 */
int q1[MAX];
int f1 = -1, r1 = -1;

/* Queue 2 */
int q2[MAX];
int f2 = -1, r2 = -1;

/* Enqueue Queue 1 */
void enqueueQ1(int value)
{
    if(r1 == MAX - 1)
    {
        printf("Queue 1 Overflow\n");
        return;
    }

    if(f1 == -1)
        f1 = 0;

    q1[++r1] = value;
}

/* Enqueue Queue 2 */
void enqueueQ2(int value)
{
    if(r2 == MAX - 1)
    {
        printf("Queue 2 Overflow\n");
        return;
    }

    if(f2 == -1)
        f2 = 0;

    q2[++r2] = value;
}

/* Display Queue 1 */
void displayQ1()
{
    int i;

    if(f1 == -1)
    {
        printf("Queue 1 Empty\n");
        return;
    }

    printf("Queue 1 : ");

    for(i = f1; i <= r1; i++)
        printf("%d ", q1[i]);

    printf("\n");
}

/* Display Queue 2 */
void displayQ2()
{
    int i;

    if(f2 == -1)
    {
        printf("Queue 2 Empty\n");
        return;
    }

    printf("Queue 2 : ");

    for(i = f2; i <= r2; i++)
        printf("%d ", q2[i]);

    printf("\n");
}

/* Boolean Function eq(q1,q2) */
int eq()
{
    int i, j;

    int size1, size2;

    if(f1 == -1 && f2 == -1)
        return 1;

    if(f1 == -1 || f2 == -1)
        return 0;

    size1 = r1 - f1 + 1;
    size2 = r2 - f2 + 1;

    if(size1 != size2)
        return 0;

    i = f1;
    j = f2;

    while(i <= r1 && j <= r2)
    {
        if(q1[i] != q2[j])
            return 0;

        i++;
        j++;
    }

    return 1;
}

int main()
{
    int choice, value;

    while(1)
    {
        printf("\n===== QUEUE COMPARISON =====\n");
        printf("1. Insert into Queue 1\n");
        printf("2. Insert into Queue 2\n");
        printf("3. Display Queue 1\n");
        printf("4. Display Queue 2\n");
        printf("5. Compare Queues\n");
        printf("6. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter Value: ");
                scanf("%d", &value);
                enqueueQ1(value);
                break;

            case 2:
                printf("Enter Value: ");
                scanf("%d", &value);
                enqueueQ2(value);
                break;

            case 3:
                displayQ1();
                break;

            case 4:
                displayQ2();
                break;

            case 5:
                if(eq())
                    printf("Queues are Equal\n");
                else
                    printf("Queues are NOT Equal\n");
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}