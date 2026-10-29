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

// --- REMAINING FUNCTIONS IMPLEMENTED BELOW ---

void indexedElement() {
    int index;
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }
    printf("Enter index (0 to %d): ", size - 1);
    scanf("%d", &index);

    if (index >= 0 && index < size) {
        printf("Element at index %d is: %d\n", index, arr[index]);
    } else {
        printf("Invalid index!\n");
    }
}

void insertElement() {
    int pos, elem, i;
    printf("Enter position to insert (0 to %d): ", size);
    scanf("%d", &pos);

    printf("Enter element to insert: ");
    scanf("%d", &elem);

    if (pos < 0 || pos > size) {
        printf("Invalid position!\n");
        return;
    }

    // Expand memory for the new element
    int* temp = (int*)realloc(arr, (size + 1) * sizeof(int));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    arr = temp;

    // Shift elements to the right
    for (i = size; i > pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos] = elem;
    size++;
    printf("Element inserted successfully.\n");
}

void deleteElement() {
    int pos, i;
    if (size == 0) {
        printf("Array is empty. Nothing to delete.\n");
        return;
    }
    printf("Enter position to delete (0 to %d): ", size - 1);
    scanf("%d", &pos);

    if (pos < 0 || pos >= size) {
        printf("Invalid position!\n");
        return;
    }

    // Shift elements to the left
    for (i = pos; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    size--;

    // Shrink memory space
    if (size > 0) {
        arr = (int*)realloc(arr, size * sizeof(int));
    } else {
        free(arr);
        arr = NULL;
    }
    printf("Element deleted successfully.\n");
}

void mergeArrays() {
    int size2, i;
    printf("Enter size of the second array to merge: ");
    scanf("%d", &size2);

    if (size2 <= 0) {
        printf("Invalid size.\n");
        return;
    }

    int* arr2 = (int*)malloc(size2 * sizeof(int));
    if (arr2 == NULL) {
        printf("Memory allocation failed for second array!\n");
        return;
    }

    printf("Enter elements of second array:\n");
    for (i = 0; i < size2; i++) {
        scanf("%d", &arr2[i]);
    }

    // Expand primary array to hold both arrays
    int* temp = (int*)realloc(arr, (size + size2) * sizeof(int));
    if (temp == NULL) {
        printf("Memory allocation failed during merge!\n");
        free(arr2);
        return;
    }
    arr = temp;

    // Append second array elements to main array
    for (i = 0; i < size2; i++) {
        arr[size + i] = arr2[i];
    }

    size += size2;
    free(arr2);
    printf("Arrays merged successfully.\n");
}

void splitArray() {
    int splitIdx, i;
    if (size <= 1) {
        printf("Array too small to split.\n");
        return;
    }
    printf("Enter index to split from (1 to %d): ", size - 1);
    scanf("%d", &splitIdx);

    if (splitIdx <= 0 || splitIdx >= size) {
        printf("Invalid split index!\n");
        return;
    }

    printf("First Part: ");
    for (i = 0; i < splitIdx; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nSecond Part: ");
    for (i = splitIdx; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Keeping only the first part in the global array
    size = splitIdx;
    arr = (int*)realloc(arr, size * sizeof(int));
    printf("Global array resized to keep the first part.\n");
}

void sortArray() {
    int i, j, temp;
    if (size <= 1) {
        printf("Array is already sorted.\n");
        return;
    }

    // Simple Bubble Sort implementation
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("Array sorted in ascending order.\n");
}
