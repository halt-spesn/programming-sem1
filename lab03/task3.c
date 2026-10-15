#include <stdio.h>

#define MAX_TEXT 255

static int count_words(const char str[])
{
    int count = 0;
    int in_word = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ' ') {
            in_word = 0;
        } else if (!in_word) {
            ++count;
            in_word = 1;
        }
    }
    return count;
}

int main(void)
{
    char str[MAX_TEXT + 1];  /* 255 text bytes plus '\0'. */
    printf("Enter text (up to %d bytes): ", MAX_TEXT);
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fputs("Error: no input line.\n", stderr);
        return 1;
    }
    int length = 0;
    while (str[length] != '\0' && str[length] != '\n') {
        ++length;
    }
    if (str[length] == '\n') {
        str[length] = '\0';
    } else if (length == MAX_TEXT) {
        int ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* Discard the remainder of an overlong line. */
            }
            fputs("Error: text exceeds 255 bytes.\n", stderr);
            return 1;
        }
    }
    /* Also remove CR if the input uses CRLF line endings. */
    if (length > 0 && str[length - 1] == '\r') {
        str[--length] = '\0';
    }
    printf("Text: [%s]\n", str);
    printf("Word count: %d\n", count_words(str));
    return 0;
}
