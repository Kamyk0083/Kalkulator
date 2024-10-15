#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT 1000

int check_digits_and_spaces(const char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i]) && !isspace(input[i])) {
            return 0;
        }
    }
    return 1;
}

int check_single_space(const char *input) {
    int space_count = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isspace(input[i])) {
            space_count++;
        }
    }
    return space_count == 1;
}

int validate_input(const char *input) {
    if (!check_digits_and_spaces(input)) {
        printf("Error: Input contains invalid characters.\n");
        return 0;
    }
    if (!check_single_space(input)) {
        printf("Error: Input must contain exactly two numbers separated by a single space.\n");
        return 0;
    }
    return 1;
}

int split_input(const char *input, char *num1, char *num2) {
    char *space_pos = strchr(input, ' ');
    if (space_pos == NULL) {
        return 0;
    }
    strncpy(num1, input, space_pos - input);
    num1[space_pos - input] = '\0';
    strcpy(num2, space_pos + 1);
    return 1;
}

void multiply_digits(const char *num1, const char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    int max_len = len1 + len2;
    memset(result, '0', max_len);
    result[max_len] = '\0';

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int digit1 = num1[i] - '0';
            int digit2 = num2[j] - '0';
            int result_idx = i + j + 1;

            int product = digit1 * digit2 + (result[result_idx] - '0');
            result[result_idx] = (product % 10) + '0';
            result[result_idx - 1] += (product / 10);
        }
    }
}

void remove_leading_zeros(char *result) {
    int start_idx = 0;
    while (result[start_idx] == '0' && result[start_idx + 1] != '\0') {
        start_idx++;
    }
    printf("Wynik: %s\n", result + start_idx);
}

int main() {
    char input[MAX_INPUT];
    char num1[MAX_INPUT], num2[MAX_INPUT];
    char result[MAX_INPUT * 2];

    printf("Podaj dwie liczby oddzielone spacją: ");
    if (!fgets(input, MAX_INPUT, stdin)) {
        printf("Błąd odczytu.\n");
        return 1;
    }

    input[strcspn(input, "\n")] = 0;

    if (!validate_input(input)) {
        return 1;
    }

    if (!split_input(input, num1, num2)) {
        printf("Błąd podczas rozdzielania liczb.\n");
        return 1;
    }

    multiply_digits(num1, num2, result);

    remove_leading_zeros(result);

    return 0;
}
