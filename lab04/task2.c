#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t set_bit(uint32_t reg, unsigned int n);
uint32_t clear_bit(uint32_t reg, unsigned int n);
uint32_t toggle_bit(uint32_t reg, unsigned int n);
int check_bit(uint32_t reg, unsigned int n);
void print_binary(uint32_t reg);
void show_register(const char *label, uint32_t reg);
int other_bits_preserved(uint32_t before, uint32_t after, unsigned int n);

int main(void)
{
    // Біти 7 і 15 початково увімкнені, щоб скидання біта 7 було видимим.
    uint32_t reg = UINT32_C(0x00008080);
    uint32_t before = reg;
    int ok = 1;
    show_register("Before set bit 3", reg);
    reg = set_bit(reg, 3);
    show_register("After set bit 3", reg);
    ok &= other_bits_preserved(before, reg, 3);

    before = reg;
    show_register("Before clear bit 7", reg);
    reg = clear_bit(reg, 7);
    show_register("After clear bit 7", reg);
    ok &= other_bits_preserved(before, reg, 7);

    before = reg;
    show_register("Before toggle bit 12", reg);
    reg = toggle_bit(reg, 12);
    show_register("After toggle bit 12", reg);
    ok &= other_bits_preserved(before, reg, 12);

    before = reg;
    printf("Bit 15 state: %d\n", check_bit(reg, 15));
    printf("Check did not change register: %s\n", before == reg ? "PASS" : "FAIL");
    printf("All other-bit checks: %s\n", ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}

uint32_t set_bit(uint32_t reg, unsigned int n)
{
    if (n >= 32) return reg;  // Не можна зсувати на 32 або більше бітів.
    return reg | (UINT32_C(1) << n);  // АБО примусово встановлює цільовий біт.
}

uint32_t clear_bit(uint32_t reg, unsigned int n)
{
    if (n >= 32) return reg;
    return reg & ~(UINT32_C(1) << n);  // І з інверсією маски скидає біт.
}

uint32_t toggle_bit(uint32_t reg, unsigned int n)
{
    if (n >= 32) return reg;
    return reg ^ (UINT32_C(1) << n);  // XOR змінює 0 на 1 або 1 на 0.
}

int check_bit(uint32_t reg, unsigned int n)
{
    if (n >= 32) return 0;
    return (reg & (UINT32_C(1) << n)) != 0;  // Повертаємо саме 0 або 1.
}

void print_binary(uint32_t reg)
{
    for (int i = 31; i >= 0; --i) {
        putchar(check_bit(reg, (unsigned int)i) ? '1' : '0');
        if (i % 4 == 0 && i != 0) putchar(' ');  // Групуємо по 4 біти.
    }
    putchar('\n');
}

void show_register(const char *label, uint32_t reg)
{
    printf("%-22s 0x%08" PRIX32 "  ", label, reg);
    print_binary(reg);
}

int other_bits_preserved(uint32_t before, uint32_t after, unsigned int n)
{
    if (n >= 32) return 0;
    uint32_t mask = UINT32_C(1) << n;
    // XOR знаходить змінені біти; ~mask прибирає з перевірки цільовий біт.
    int ok = ((before ^ after) & ~mask) == 0;
    printf("Other bits preserved: %s\n", ok ? "PASS" : "FAIL");
    return ok;
}
