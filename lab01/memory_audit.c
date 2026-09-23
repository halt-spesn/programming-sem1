#include <stdio.h>

int main(void) {
    printf("char: %zu bytes\n", sizeof(char));
    printf("short: %zu bytes\n", sizeof(short));
    printf("int: %zu bytes\n", sizeof(int));
    printf("long: %zu bytes\n", sizeof(long));
    printf("long long: %zu bytes\n", sizeof(long long));
    printf("float: %zu bytes\n", sizeof(float));
    printf("double: %zu bytes\n", sizeof(double));
    printf("void*: %zu bytes\n", sizeof(void*));
    printf("============\n");

    unsigned char byte_test = 255;
    printf("decimal: %u\n", byte_test);
    printf("hex: 0x%X\n", byte_test);

    byte_test = byte_test + 1;
    printf("decimal: %u\n", byte_test);
    printf("hex: 0x%02X\n", byte_test);


    return 0;
}
