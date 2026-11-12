#include <stdio.h>
#include <stddef.h>

// Функція пошуку мінімального та максимального значень
int analyze_array(
    const int *data,
    size_t count,
    int *min_value,
    int *max_value
) {
    // Перевірка вхідних покажчиків та кількості елементів
    if (data == NULL || min_value == NULL ||
        max_value == NULL || count == 0) {
        return 1;
    }

    // Початкові значення мінімуму та максимуму
    *min_value = *data;
    *max_value = *data;

    // Перебір масиву за допомогою покажчика
    const int *ptr = data;

    for (size_t i = 0; i < count; i++, ptr++) {
        if (*ptr < *min_value) {
            *min_value = *ptr;
        }

        if (*ptr > *max_value) {
            *max_value = *ptr;
        }
    }

    return 0;
}

int main(void) {
    // Вхідний масив
    const int numbers[] = {12, -5, 34, 0, 18, -12, 7, 25};

    // Кількість елементів масиву
    size_t count = sizeof(numbers) / sizeof(*numbers);

    // Змінні для результатів
    int min_value;
    int max_value;

    // Виклик функції з передачею адрес змінних
    int result = analyze_array(
        numbers,
        count,
        &min_value,
        &max_value
    );

    if (result == 0) {
        printf("Minimalne znachennya: %d\n", min_value);
        printf("Maksymalne znachennya: %d\n", max_value);
    } else {
        printf("Pomylka obrobky masyvu!\n");
    }

    return 0;
}
