#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;

Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

void clearPolynomial(Node** headRef) {
    Node* current = *headRef;
    while (current != NULL) {
        Node* nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *headRef = NULL;
}

void insertTerm(Node** headRef, int coeff, int exp) {
    if (coeff == 0) return;

    if (*headRef == NULL || exp > (*headRef)->exp) {
        Node* newNode = createNode(coeff, exp);
        newNode->next = *headRef;
        *headRef = newNode;
        return;
    }

    if ((*headRef)->exp == exp) {
        (*headRef)->coeff += coeff;
        if ((*headRef)->coeff == 0) {
            Node* temp = *headRef;
            *headRef = (*headRef)->next;
            free(temp);
        }
        return;
    }

    Node* current = *headRef;
    while (current->next != NULL && current->next->exp > exp) {
        current = current->next;
    }

    if (current->next != NULL && current->next->exp == exp) {
        current->next->coeff += coeff;
        if (current->next->coeff == 0) {
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
    } else {
        Node* newNode = createNode(coeff, exp);
        newNode->next = current->next;
        current->next = newNode;
    }
}

void displayPolynomial(Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    Node* current = head;
    int isFirst = 1;

    while (current != NULL) {
        if (current->coeff > 0 && !isFirst) {
            printf(" + ");
        } else if (current->coeff < 0) {
            printf(isFirst ? "-" : " - ");
        }

        int absCoeff = abs(current->coeff);

        if (absCoeff != 1 || current->exp == 0) {
            printf("%d", absCoeff);
        }

        if (current->exp > 0) {
            printf("x");
            if (current->exp > 1) {
                printf("^%d", current->exp);
            }
        }

        isFirst = 0;
        current = current->next;
    }
    printf("\n");
}

Node* addPolynomials(Node* p1, Node* p2) {
    Node* result = NULL;
    Node* t1 = p1;
    Node* t2 = p2;

    while (t1 != NULL && t2 != NULL) {
        if (t1->exp > t2->exp) {
            insertTerm(&result, t1->coeff, t1->exp);
            t1 = t1->next;
        } else if (t1->exp < t2->exp) {
            insertTerm(&result, t2->coeff, t2->exp);
            t2 = t2->next;
        } else {
            insertTerm(&result, t1->coeff + t2->coeff, t1->exp);
            t1 = t1->next;
            t2 = t2->next;
        }
    }

    while (t1 != NULL) {
        insertTerm(&result, t1->coeff, t1->exp);
        t1 = t1->next;
    }
    while (t2 != NULL) {
        insertTerm(&result, t2->coeff, t2->exp);
        t2 = t2->next;
    }

    return result;
}

Node* subtractPolynomials(Node* p1, Node* p2) {
    Node* result = NULL;
    Node* t1 = p1;
    Node* t2 = p2;

    while (t1 != NULL && t2 != NULL) {
        if (t1->exp > t2->exp) {
            insertTerm(&result, t1->coeff, t1->exp);
            t1 = t1->next;
        } else if (t1->exp < t2->exp) {
            insertTerm(&result, -t2->coeff, t2->exp); // Negate the term being subtracted
            t2 = t2->next;
        } else {
            insertTerm(&result, t1->coeff - t2->coeff, t1->exp);
            t1 = t1->next;
            t2 = t2->next;
        }
    }

    while (t1 != NULL) {
        insertTerm(&result, t1->coeff, t1->exp);
        t1 = t1->next;
    }
    while (t2 != NULL) {
        insertTerm(&result, -t2->coeff, t2->exp);
        t2 = t2->next;
    }

    return result;
}

Node* multiplyPolynomials(Node* p1, Node* p2) {
    Node* result = NULL;

    for (Node* t1 = p1; t1 != NULL; t1 = t1->next) {
        for (Node* t2 = p2; t2 != NULL; t2 = t2->next) {
            int targetCoeff = t1->coeff * t2->coeff;
            int targetExp = t1->exp + t2->exp;
            insertTerm(&result, targetCoeff, targetExp);
        }
    }
    return result;
}

void inputPolynomial(Node** headRef) {
    clearPolynomial(headRef);
    int terms, coeff, exp;

    printf("Enter the number of terms: ");
    scanf("%d", &terms);

    for (int i = 0; i < terms; i++) {
        printf("  Enter coefficient and exponent for term %d (space separated): ", i + 1);
        scanf("%d %d", &coeff, &exp);
        insertTerm(headRef, coeff, exp);
    }
}

int main() {
    Node* p1 = NULL;
    Node* p2 = NULL;
    Node* result = NULL;
    int choice;

    do {
        printf("\n================================");
        printf("\n   POLYNOMIAL OPERATIONS MENU");
        printf("\n================================");
        printf("\n1. Input Polynomials (P1 and P2)");
        printf("\n2. Display Current Polynomials");
        printf("\n3. Add (P1 + P2)");
        printf("\n4. Subtract (P1 - P2)");
        printf("\n5. Multiply (P1 * P2)");
        printf("\n6. Exit");
        printf("\nEnter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- Inputting Polynomial 1 ---\n");
                inputPolynomial(&p1);
                printf("\n--- Inputting Polynomial 2 ---\n");
                inputPolynomial(&p2);
                printf("\nPolynomials stored successfully!\n");
                break;

            case 2:
                printf("\nP1: "); displayPolynomial(p1);
                printf("P2: "); displayPolynomial(p2);
                break;

            case 3:
                clearPolynomial(&result);
                result = addPolynomials(p1, p2);
                printf("\nResult (P1 + P2): ");
                displayPolynomial(result);
                break;

            case 4:
                clearPolynomial(&result);
                result = subtractPolynomials(p1, p2);
                printf("\nResult (P1 - P2): ");
                displayPolynomial(result);
                break;

            case 5:
                clearPolynomial(&result);
                result = multiplyPolynomials(p1, p2);
                printf("\nResult (P1 * P2): ");
                displayPolynomial(result);
                break;

            case 6:
                printf("\nExiting program. Freeing memory...\n");
                break;

            default:
                printf("\nInvalid choice! Please select an option between 1 and 6.\n");
        }
    } while (choice != 6);

    clearPolynomial(&p1);
    clearPolynomial(&p2);
    clearPolynomial(&result);

    return 0;
}
