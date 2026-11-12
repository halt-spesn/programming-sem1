#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

// Функція конфігурації 32-бітного регістра
void configure_register(uint32_t *reg) {
    // Перевірка покажчика
    if (reg == NULL) {
        return;
    }

    // Встановлення біта 4 у значення 1
    *reg |= (UINT32_C(1) << 4);

    // Скидання біта 11 у значення 0
    *reg &= ~(UINT32_C(1) << 11);

    // Інвертування біта 23
    *reg ^= (UINT32_C(1) << 23);
}

// Функція перевірки стану біта
int check_status_flag(const uint32_t *reg, uint8_t bit_pos) {
    // Перевірка покажчика та позиції біта
    if (reg == NULL || bit_pos >= 32) {
        return -1;
    }

    // Повернення стану біта
    return (int)((*reg >> bit_pos) & UINT32_C(1));
}

int main(void) {
    // Початкове значення 32-бітного регістра
    uint32_t reg = UINT32_C(0x80800800);

    printf("Register before: 0x%08" PRIX32 "\n", reg);

    // Перевірка біта 31 до модифікації
    int status_before = check_status_flag(&reg, 31);

    printf("Bit 31 before: %d\n", status_before);

    // Виконання конфігурації регістра
    configure_register(&reg);

    printf("Register after:  0x%08" PRIX32 "\n", reg);

    // Перевірка біта 31 після модифікації
    int status_after = check_status_flag(&reg, 31);

    printf("Bit 31 after: %d\n", status_after);

    return 0;
}
