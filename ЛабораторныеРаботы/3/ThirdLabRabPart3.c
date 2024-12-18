#include <stdio.h>
#include <stdlib.h>

// Функция для подсчета количества повторений каждого элемента
void countElements(int *arr, int n, int *count) {
    for (int i = 0; i < n; i++) {
        count[arr[i] + 10000]++; // Предполагаем, что элементы в диапазоне [-10000, 10000]
    }
}

// Функция для удаления повторяющихся элементов
void removeDuplicates(int *arr, int *n) {
    int *count = (int *)calloc(20001, sizeof(int)); // Диапазон [-10000, 10000]

    countElements(arr, *n, count);

    int writeIndex = 0;
    for (int i = 0; i < *n; i++) {
        if (count[arr[i] + 10000] == 1) {
            arr[writeIndex++] = arr[i];
        }
    }

    *n = writeIndex;
    free(count);
}

int main() {
    // Сообщение в начале выполнения
    printf("Лабораторная работа №3, Часть 3\n");

    int n;

    // Ввод размера массива
    printf("Введите количество элементов n: ");
    scanf("%d", &n);

    // Выделение памяти под массив
    int *arr = (int *)malloc(n * sizeof(int));

    // Ввод элементов массива
    printf("Введите элементы массива через пробел: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Удаление повторяющихся элементов
    removeDuplicates(arr, &n);

    // Вывод результата
    printf("Массив после удаления повторяющихся элементов:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Освобождение памяти
    free(arr);

    return 0;
}
