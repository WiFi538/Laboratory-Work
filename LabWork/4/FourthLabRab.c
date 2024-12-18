// 1. Выделить из каждой строки и напечатать подстроки: заключенные в фигурные скобки;

// 2. Среди выделенных подстрок найти подстроку (если таких подстрок несколько, выбирается первая из них): 
// начинающуюся с четного (но не нулевого) числа цифр;

// 3. Преобразовать исходную строку, которой принадлежит найденная подстрока, следующим образом: 
// удалить путем сдвига все символы, отличные от русских букв;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 1000
#define MAX_SUBSTRINGS 100

// Часть 1: Функция для извлечения подстрок, заключенных в фигурные скобки
void extract_braces_substrings(char strings[][MAX_STRING_LENGTH], int k, char substrings[][MAX_STRING_LENGTH], int *count) {
    *count = 0;
    for (int i = 0; i < k; i++) {
        char *start = strchr(strings[i], '{');
        while (start != NULL) {
            char *end = strchr(start, '}');
            if (end != NULL) {
                int len = end - start - 1;
                if (len > 0) {
                    strncpy(substrings[*count], start + 1, len);
                    substrings[*count][len] = '\0';
                    (*count)++;
                }
                start = strchr(end + 1, '{');
            } else {
                break;
            }
        }
    }
}

// Часть 2: Функция для поиска подстроки, начинающейся с четного числа цифр
char* find_even_digit_substring(char substrings[][MAX_STRING_LENGTH], int count) {
    for (int i = 0; i < count; i++) {
        int digit_count = 0;
        while (isdigit(substrings[i][digit_count])) {
            digit_count++;
        }
        if (digit_count % 2 == 0 && digit_count != 0) {
            return substrings[i];
        }
    }
    return NULL;
}

// Часть 3: Функция для удаления всех символов, кроме русских букв, из строки
void remove_non_russian_letters(char *str) {
    char *src = str;
    char *dst = str;

    while (*src) {
        if ((*src >= 'А' && *src <= 'Я') || (*src >= 'а' && *src <= 'я')) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int main() {
    int k;
    printf("Введите количество строк: ");
    scanf("%d", &k);
    getchar(); 
    char strings[k][MAX_STRING_LENGTH];
    for (int i = 0; i < k; i++) {
        printf("Введите строку %d: ", i + 1);
        fgets(strings[i], MAX_STRING_LENGTH, stdin);
        strings[i][strcspn(strings[i], "\n")] = '\0'; 
    }

    char substrings[MAX_SUBSTRINGS][MAX_STRING_LENGTH];
    int count;

    // Часть 1: Выделение подстрок, заключенных в фигурные скобки
    extract_braces_substrings(strings, k, substrings, &count);
    if (count > 0) {
        printf("\nПодстроки, заключенные в фигурные скобки:\n");
        for (int i = 0; i < count; i++) {
            printf("%s\n", substrings[i]);
        }
    } else {
        printf("Нет подстрок, заключенных в фигурные скобки.\n");
    }

    // Часть 2: Поиск подстроки, начинающейся с четного числа цифр
    char *even_digit_substring = find_even_digit_substring(substrings, count);
    if (even_digit_substring) {
        printf("\nПервая подстрока, начинающаяся с четного числа цифр: %s\n", even_digit_substring);

        // Часть 3: Преобразование исходной строки, содержащей найденную подстроку
        for (int i = 0; i < k; i++) {
            if (strstr(strings[i], even_digit_substring) != NULL) {
                remove_non_russian_letters(strings[i]);
                printf("\nПреобразованная строка: %s\n", strings[i]);
                break;
            }
        }
    } else {
        printf("Нет подстрок, начинающихся с четного числа цифр.\n");
    }

    return 0;
}
