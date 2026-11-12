#include <stdio.h>
#include <stddef.h>

// Функція пошуку мінімального елемента через покажчики
int find_min_by_pointer(
    const int *start,
    size_t count,
    int *min_value,
    ptrdiff_t *min_index
) {
    // Перевірка вхідних параметрів
    if (start == NULL || min_value == NULL ||
        min_index == NULL || count == 0) {
        return 1;
    }

    // Створення покажчиків на початок та кінець буфера
    const int *ptr = start;
    const int *end = start + count;

    // Покажчик на мінімальний елемент
    const int *min_ptr = start;

    // Перебір елементів масиву
    while (ptr < end) {
        if (*ptr < *min_ptr) {
            min_ptr = ptr;
        }

        // Перехід до наступного елемента
        ptr++;
    }

    // Передача мінімального значення
    *min_value = *min_ptr;

    // Визначення індексу через різницю покажчиків
    *min_index = min_ptr - start;

    return 0;
}

int main(void) {
    // Вхідний масив
    const int numbers[] = {12, -5, 34, 0, 18, -12, 7, 25};

    // Визначення кількості елементів без індексації
    size_t count = sizeof(numbers) / sizeof(*numbers);

    // Змінні для результатів
    int min_value;
    ptrdiff_t min_index;

    // Виклик функції
    int result = find_min_by_pointer(
        numbers,
        count,
        &min_value,
        &min_index
    );

    if (result == 0) {
        printf("Minimalny element: %d\n", min_value);
        printf("Index (vid 0): %td\n", min_index);
        printf("Poryadkovyi nomer (vid 1): %td\n", min_index + 1);
    } else {
        printf("Pomylka obrobky bufera!\n");
    }

    return 0;
}
