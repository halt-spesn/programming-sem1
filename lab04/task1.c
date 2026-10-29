#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

// Структура дозволяє повернути результат і лічильник без вихідних покажчиків.
typedef struct {
    uint64_t value;
    uint64_t multiplications;
    int valid;
} FactorialResult;

// Прототипи повідомляють компілятору типи функцій до їхнього виклику.
int read_number(unsigned int *n);
FactorialResult factorial(unsigned int n);

int main(void)
{
    unsigned int n;
    puts("Factorial session: enter one integer 0..20 per line.");
    puts("Finish input with EOF (or use a pipe).");
    for (;;) {
        printf("n: ");
        int status = read_number(&n);
        if (status == 0) {
            putchar('\n');
            return 0;
        }
        if (status < 0) {
            fputs("Error: enter one integer from 0 to 20.\n", stderr);
            return 1;
        }
        // Передаємо n за значенням: factorial отримує його копію.
        FactorialResult result = factorial(n);
        if (!result.valid) {
            fputs("Error: factorial or counter is out of range.\n", stderr);
            return 1;
        }
        printf("%u! = %" PRIu64 "\n", n, result.value);
        printf("Total multiplications: %" PRIu64 "\n",
               result.multiplications);
        printf("n in main is still: %u\n", n);
    }
}

int read_number(unsigned int *n)
{
    char line[128];
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return feof(stdin) ? 0 : -1;
    }
    if (strchr(line, '\n') == NULL && !feof(stdin)) {
        return -1;  // Не приймаємо частково зчитаний довгий рядок.
    }
    char *end;
    errno = 0;
    long value = strtol(line, &end, 10);
    if (end == line || errno == ERANGE) {
        return -1;
    }
    while (isspace((unsigned char)*end)) {
        ++end;
    }
    if (*end != '\0' || value < 0 || value > 20) {
        return -1;
    }
    *n = (unsigned int)value;
    return 1;
}

FactorialResult factorial(unsigned int n)
{
    // Ініціалізується один раз і зберігається між викликами в цій сесії.
    static uint64_t total = 0;
    FactorialResult result = {1, total, 0};
    if (n > 20) {
        return result;  // 21! уже не вміщується в uint64_t.
    }
    unsigned int needed = n > 1 ? n - 1 : 0;
    if (total > UINT64_MAX - needed) {
        return result;  // Захищаємо і накопичувальний лічильник.
    }
    // 0! = 1 і 1! = 1: для них цикл не виконується.
    for (unsigned int i = 2; i <= n; ++i) {
        result.value *= i;
        ++total;  // Рахуємо саме виконане множення, а не виклик функції.
    }
    result.multiplications = total;
    result.valid = 1;
    return result;
}
