#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 15

static void print_array(const int a[SIZE])
{
    for (int i = 0; i < SIZE; ++i) {
        printf("%4d", a[i]);
    }
    putchar('\n');
}

static void analyze(const int a[SIZE])
{
    int min_value = a[0];
    int min_index = 0;
    int first_negative = -1;
    int sum = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (abs(a[i]) < abs(min_value)) {
            min_value = a[i];
            min_index = i;
        }
        if (first_negative >= 0) {
            sum += a[i];
        } else if (a[i] < 0) {
            first_negative = i;
        }
    }
    printf("Minimum by absolute value: %d; index: %d\n",
           min_value, min_index);
    if (first_negative < 0) {
        puts("No negative element; sum is not calculated.");
    } else {
        printf("First negative index: %d\n", first_negative);
        printf("Sum after first negative: %d\n", sum);
    }
}

int main(int argc, char *argv[])
{
    int a[SIZE];
    if (argc == 2 && strcmp(argv[1], "--demo") == 0) {
        /* Reproducible test; the ordinary run uses rand(). */
        const int demo[SIZE] = {
            12, 7, -8, 4, -3, 0, 15, -2, 9, 6, -1, 5, -4, 11, 2
        };
        for (int i = 0; i < SIZE; ++i) {
            a[i] = demo[i];
        }
        puts("Mode: fixed demonstration");
    } else if (argc == 1) {
        srand((unsigned int)time(NULL));
        for (int i = 0; i < SIZE; ++i) {
            a[i] = rand() % 101 - 50;
        }
        puts("Mode: random values in [-50; 50]");
    } else {
        fprintf(stderr, "Usage: %s [--demo]\n", argv[0]);
        return 1;
    }
    printf("Original array: ");
    print_array(a);
    analyze(a);
    printf("Array after analysis: ");
    print_array(a);  /* This variant does not change the array. */
    return 0;
}
