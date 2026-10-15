#include <stdio.h>

#define ROWS 4
#define COLS 5

static void print_matrix(int a[ROWS][COLS])
{
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%6d", a[i][j]);
        }
        putchar('\n');
    }
}

static void column_minima(int a[ROWS][COLS], int mins[COLS])
{
    for (int j = 0; j < COLS; ++j) {
        mins[j] = a[0][j];
    }
    /* Rows outside, columns inside: sequential row-major access. */
    for (int i = 1; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (a[i][j] < mins[j]) {
                mins[j] = a[i][j];
            }
        }
    }
}

static void swap_outer_rows(int a[ROWS][COLS])
{
    for (int j = 0; j < COLS; ++j) {
        int temp = a[0][j];
        a[0][j] = a[ROWS - 1][j];
        a[ROWS - 1][j] = temp;
    }
}

int main(void)
{
    int a[ROWS][COLS] = {
        { 12, -3,  7,  0,  9},
        {  4,  8, -6, 11,  2},
        { -5,  1, 10, -4,  6},
        {  3, -9,  5,  8, -2}
    };
    int mins[COLS];
    puts("Original matrix:");
    print_matrix(a);
    column_minima(a, mins);
    printf("Column minima: ");
    for (int j = 0; j < COLS; ++j) {
        printf("%6d", mins[j]);
    }
    putchar('\n');
    swap_outer_rows(a);
    puts("After swapping first and last rows:");
    print_matrix(a);
    return 0;
}
