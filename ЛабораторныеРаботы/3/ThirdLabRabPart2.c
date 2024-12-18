#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Функция для ввода матрицы
void inputMatrix(int **matrix, int n, int m) {
    printf("Введите элементы матрицы %dx%d:\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Функция для вычисления значения по формуле
int calculateS(int **matrix, int n, int m) {
    int maxMinDiff = INT_MIN;

    for (int i = 0; i < n; i++) {
        int minDiff = INT_MAX;
        for (int j = 0; j < m - 1; j++) {
            int diff = abs(matrix[i][j] - matrix[i][j + 1]);
            if (diff < minDiff) {
                minDiff = diff;
            }
        }
        if (minDiff > maxMinDiff) {
            maxMinDiff = minDiff;
        }
    }

    return maxMinDiff;
}

int main() {
    printf("Лабораторная работа №3, Часть 2\n");

    int n, m;

    // Ввод размеров матрицы
    printf("Введите количество строк n: ");
    scanf("%d", &n);
    printf("Введите количество столбцов m: ");
    scanf("%d", &m);

    // Выделение памяти под матрицу
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(m * sizeof(int));
    }

    // Ввод матрицы
    inputMatrix(matrix, n, m);

    // Вычисление значения S
    int S = calculateS(matrix, n, m);

    printf("Значение S = %d\n", S);

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
