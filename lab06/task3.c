#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int rows, cols;

    printf("Enter number of rows: ");
    if (scanf("%d", &rows) != 1 || rows <= 0) {
        printf("Error: invalid number of rows!\n");
        return 1;
    }

    printf("Enter number of columns: ");
    if (scanf("%d", &cols) != 1 || cols <= 0) {
        printf("Error: invalid number of columns!\n");
        return 1;
    }

    // Allocate memory for an array of row pointers
    int **matrix = calloc(rows, sizeof(int *));

    if (matrix == NULL) {
        printf("Error: not enough memory (RAM)!\n");
        return 1;
    }

    // Allocate memory for each row separately
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));

        if (matrix[i] == NULL) {
            printf("Error: cannot allocate memory for row %d!\n", i);

            // Free all previously allocated rows
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
                matrix[j] = NULL;
            }

            free(matrix);
            matrix = NULL;

            return 1;
        }
    }

    // Fill the matrix
    printf("\nEnter matrix elements:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("matrix[%d][%d] = ", i, j);

            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Error: invalid input!\n");

                // Free all allocated memory
                for (int k = 0; k < rows; k++) {
                    free(matrix[k]);
                    matrix[k] = NULL;
                }

                free(matrix);
                matrix = NULL;

                return 1;
            }
        }
    }

    // Display the matrix
    printf("\nMatrix:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    // Free memory allocated for each row
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
        matrix[i] = NULL;
    }

    // Free the array of pointers
    free(matrix);
    matrix = NULL;

    printf("\nMemory successfully freed!\n");

    return 0;
}
