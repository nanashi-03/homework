#include <stdio.h>

int main() {

    int n1, n2, i;
    int s1[100], s2[100];
    int equal = 1;

    printf("Enter Size of Stack1: ");
    scanf("%d", &n1);

    printf("Enter Elements:\n");
    for(i=0;i<n1;i++)
        scanf("%d",&s1[i]);

    printf("Enter Size of Stack2: ");
    scanf("%d",&n2);

    printf("Enter Elements:\n");
    for(i=0;i<n2;i++)
        scanf("%d",&s2[i]);

    if(n1 != n2)
        equal = 0;
    else {
        for(i=0;i<n1;i++) {
            if(s1[i] != s2[i]) {
                equal = 0;
                break;
            }
        }
    }

    if(equal)
        printf("Stacks are Equal\n");
    else
        printf("Stacks are Not Equal\n");

    return 0;
}