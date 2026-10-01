#include <stdio.h>
#include <math.h>

#define MAX_ROWS 100000U

static void print_row(double x)
{
    double y;
    if (x <= 0.0) {
        y = -x;
    } else if (x <= 2.0) {
        y = x * x;
    } else {
        y = 4.0;
    }
    if (!isfinite(y)) {
        printf("%12.6g | [Не визначено]\n", x);
    } else {
        printf("%12.6g | %12.6f\n", x, y);
    }
}

int main(void)
{
    double start, end, dx;
    printf("Enter X_start X_end dX: ");
    if (scanf("%lf %lf %lf", &start, &end, &dx) != 3) {
        fprintf(stderr, "Error: enter three numbers.\n");
        return 1;
    }
    if (!isfinite(start) || !isfinite(end) ||
        !isfinite(dx) || start >= end || dx <= 0.0) {
        fprintf(stderr, "Error: finite values, start < end, dX > 0.\n");
        return 1;
    }
    long double steps = ((long double)end - start) / dx;
    if (steps > MAX_ROWS - 2U) {
        fprintf(stderr, "Error: too many rows; increase dX.\n");
        return 1;
    }
    printf("%12s | %12s\n", "X", "Y(X)");
    unsigned int rows = 0;
    for (double x = start; x <= end; ) {
        if (++rows > MAX_ROWS) {
            fprintf(stderr, "Error: row limit reached.\n");
            return 1;
        }
        print_row(x);
        if (x == end) {
            break;
        }
        double next = x + dx;
        if (next <= x) {
            fprintf(stderr, "Error: dX too small for double.\n");
            return 1;
        }
        if (!isfinite(next) || next > end) {
            print_row(end);
            break;
        }
        x = next;
    }
    return 0;
}
