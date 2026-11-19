#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int capacity = 2;
    int count = 0;
    int number;

    // Allocate initial buffer for 2 integers
    int *arr = malloc(capacity * sizeof(int));

    if (arr == NULL) {
        printf("Error: not enough memory (RAM)!\n");
        return 1;
    }

    printf("Enter integers (-999 to stop):\n");

    while (1) {
        printf("Number: ");

        if (scanf("%d", &number) != 1) {
            printf("Error: invalid input!\n");
            free(arr);
            arr = NULL;
            return 1;
        }

        // Check termination condition
        if (number == -999) {
            break;
        }

        // Check whether the buffer is full
        if (count == capacity) {
            int new_capacity = capacity * 2;

            // Reallocate memory using a temporary pointer
            int *temp = realloc(
                arr, new_capacity * sizeof(int)
            );

            if (temp == NULL) {
                printf("Error: cannot allocate more memory!\n");
                free(arr);
                arr = NULL;
                return 1;
            }

            // Update the main pointer after successful allocation
            arr = temp;
            capacity = new_capacity;

            printf("Buffer expanded to %d elements.\n", capacity);
        }

        // Store the new number
        arr[count] = number;
        count++;
    }

    // Display all entered numbers
    printf("\nEntered elements:\n");

    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }

    printf("\nTotal number of elements: %d\n", count);
    printf("Final buffer capacity: %d\n", capacity);

    // Free allocated memory
    free(arr);
    arr = NULL;

    return 0;
}
