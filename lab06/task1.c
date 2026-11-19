#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    int n;

    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: invalid array size!\n");
        return 1;
    }

    // Allocate memory for the array
    double *arr = malloc(n * sizeof(double));

    // Check whether memory was allocated
    if (arr == NULL) {
        printf("Error: not enough memory (RAM)!\n");
        return 1;
    }

    // Read array elements
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);

        if (scanf("%lf", &arr[i]) != 1) {
            printf("Error: invalid input!\n");
            free(arr);
            arr = NULL;
            return 1;
        }
    }

    // Calculate the sum of logarithms of positive elements
    double log_sum = 0.0;
    int positive_count = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            log_sum += log(arr[i]);
            positive_count++;
        }
    }

    // Calculate geometric mean
    if (positive_count > 0) {
        double geometric_mean = exp(log_sum / positive_count);
        printf("\nGeometric mean of positive elements: %.6lf\n",
               geometric_mean);
    } else {
        printf("\nThere are no positive elements in the array.\n");
    }

    // Free allocated memory
    free(arr);
    arr = NULL;

    return 0;
}
