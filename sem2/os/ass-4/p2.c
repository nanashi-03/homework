#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CYLINDERS 200
#define REQ_SIZE 20
#define INITIAL_HEAD 50

void sort_array(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int simulate_scan(int requests[], int n, int head) {
    int total_movement = 0;
    int sorted[REQ_SIZE + 2];
    int size = 0;

    for(int i = 0; i < n; i++) sorted[size++] = requests[i];

    int has_higher = 0;
    for(int i = 0; i < n; i++) if(requests[i] > head) has_higher = 1;
    if(has_higher) sorted[size++] = MAX_CYLINDERS - 1;

    sort_array(sorted, size);

    int pos = 0;
    while (pos < size && sorted[pos] < head) pos++;

    int current_head = head;

    for (int i = pos; i < size; i++) {
        total_movement += abs(sorted[i] - current_head);
        current_head = sorted[i];
    }

    for (int i = pos - 1; i >= 0; i--) {
        total_movement += abs(sorted[i] - current_head);
        current_head = sorted[i];
    }
    return total_movement;
}

int simulate_cscan(int requests[], int n, int head) {
    int total_movement = 0;
    int sorted[REQ_SIZE + 2];
    int size = 0;

    for(int i = 0; i < n; i++) sorted[size++] = requests[i];

    sorted[size++] = MAX_CYLINDERS - 1;

    sort_array(sorted, size);

    int pos = 0;
    while (pos < size && sorted[pos] < head) pos++;

    int current_head = head;

    for (int i = pos; i < size; i++) {
        total_movement += abs(sorted[i] - current_head);
        current_head = sorted[i];
    }

    if (pos > 0) {
        current_head = 0;

        for (int i = 0; i < pos; i++) {
            total_movement += abs(sorted[i] - current_head);
            current_head = sorted[i];
        }
    }
    return total_movement;
}

void evaluate_list(int req[], int n, const char* label) {
    printf("\n%s\nRequests: ", label);
    for(int i = 0; i < n; i++) printf("%d ", req[i]);
    printf("\nSCAN Total Head Movements: %d\n", simulate_scan(req, n, INITIAL_HEAD));
    printf("C-SCAN Total Head Movements: %d\n", simulate_cscan(req, n, INITIAL_HEAD));
}

int read_from_file(const char* filename, int arr[], int max_size) {
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Warning: Could not open file %s\n", filename);
        return 0;
    }
    int i = 0;
    while (i < max_size && fscanf(fptr, "%d", &arr[i]) == 1) {
        i++;
    }
    fclose(fptr);
    return i;
}

int main() {
    srand(time(NULL));
    int req[REQ_SIZE];

    printf("Random Distribution\n");
    for (int l = 1; l <= 3; l++) {
        for (int i = 0; i < REQ_SIZE; i++) {
            req[i] = rand() % MAX_CYLINDERS;
        }
        char label[20];
        sprintf(label, "Random List %d", l);
        evaluate_list(req, REQ_SIZE, label);
    }

    printf("\nFile Distributions\n");

    int ends_req[REQ_SIZE];
    if (read_from_file("ends_requests.txt", ends_req, REQ_SIZE) > 0) {
        evaluate_list(ends_req, REQ_SIZE, "Part C: Concentrated at Ends");
    }

    int mids_req[REQ_SIZE];
    if (read_from_file("mids_requests.txt", mids_req, REQ_SIZE) > 0) {
        evaluate_list(mids_req, REQ_SIZE, "Part D: Concentrated at Center");
    }

    return 0;
}
