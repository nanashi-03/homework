#include <stdio.h>
#include <stdlib.h>

int* arr = NULL;
int size = 0;

void create();
void display();
void countElements();
void reverse();
void searchElement();
void indexedElement();
void insertElement();
void deleteElement();
void mergeArrays();
void splitArray();
void sortArray();

int main ()
{
	int c;
	
	while (1)
	{
		printf("\nMENU:\n1. Create\n2. Display\n3. Count\n4. Reverse\n5. Index of Element\n6. Indexed Element\n7. Insert\n8. Delete\n9. Merge\n10. Split\n11. Sort\n12. Exit\nEnter your choice: ");
		scanf("%d", &c);
		
		switch(c) {
			case 1: create(); break;
			case 2: display(); break;
			case 3: countElements(); break;
			case 4: reverse(); break;
			case 5: searchElement(); break;
			case 6: indexedElement(); break;
			case 7: insertElement(); break;
			case 8: deleteElement(); break;
			case 9: mergeArrays(); break;
			case 10: splitArray(); break;
			case 11: sortArray(); break;
			case 12: free(arr); printf("Program Exited.\n"); return 0;
			default: printf("Invalid choice!\n");
		}
	}
	return 0;
}

void create() {
    int i;

    printf("Enter number of elements: ");
    scanf("%d", &size);

    arr = (int *)malloc(size * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("Enter elements:\n");
    for (i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Array created successfully.\n");
}

void display() {
    int i;

    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    printf("Array elements are:\n");

    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

void countElements() {
    printf("Total number of elements = %d\n", size);
}

void reverse() {
    int i, temp;

    for (i = 0; i < size / 2; i++) {
        temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }

    printf("Array reversed successfully.\n");
}

void searchElement() {
    int key, i, found = 0;

    printf("Enter element to search: ");
    scanf("%d", &key);

    printf("Element found at index: ");

    for (i = 0; i < size; i++) {
        if (arr[i] == key) {
            printf("%d ", i);
            found = 1;
        }
    }

    if (!found) {
        printf("Not found");
    }

    printf("\n");
}


