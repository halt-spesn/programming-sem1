#include <stdio.h>
#include <math.h>

#define MAX_ITER 100000U

int main(void)
{
    double x, eps;
    printf("Enter X epsilon: ");
    if (scanf("%lf %lf", &x, &eps) != 2) {
        fprintf(stderr, "Error: enter two numbers.\n");
        return 1;
    }
    if (!isfinite(x) || !isfinite(eps) || eps <= 0.0) {
        fprintf(stderr, "Error: finite X and epsilon > 0 required.\n");
        return 1;
    }
    double reference = exp(x);
    if (!isfinite(reference) || reference == 0.0) {
        fprintf(stderr, "Error: exp(X) is outside double range.\n");
        return 1;
    }
    double term = 1.0;
    double sum = term;
    unsigned int n = 0;
    int failed = 0;
    while (fabs(term) >= eps) {
        if (n >= MAX_ITER) {
            fprintf(stderr, "Warning: iteration limit reached.\n");
            failed = 1;
            break;
        }
        ++n;
        term *= x / (double)n;

        double next_sum = sum + term;
        if (!isfinite(term) || !isfinite(next_sum)) {
            fprintf(stderr, "Error: intermediate overflow.\n");
            failed = 1;
            break;
        }
        sum = next_sum;
    }
    if (failed) {
        return 2;
    }
    double abs_error = fabs(sum - reference);
    double rel_error = abs_error / fabs(reference);
    printf("Series sum     = %.12g\n", sum);
    printf("exp(X)         = %.12g\n", reference);
    printf("Absolute error = %.12g\n", abs_error);
    printf("Relative error = %.12g\n", rel_error);
    printf("Iterations     = %u\n", n);
    printf("Last term      = %.12g\n", term);
    if (x < -20.0) {
        printf("Warning: cancellation may reduce accuracy.\n");
    }
    return 0;
}
