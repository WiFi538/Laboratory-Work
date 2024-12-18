// 1. Даны n, x, h, a. Вычислить массив R[1:n] в соответствии с формулами: R[i]= 6 cos(ax + ih), i =  1,n

// 2. Из вычисленного массива R удалить все отрицательные элементы, 
// расположенные между первым минимальным и последним положительным элементами.

// 3. В полученном массиве R[1:k], где k - число элементов, оставшихся после удаления, подсчитать среднее 
//арифметическое элементов, расположенных до первого минимального по модулю отрицательного элемента.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Вычисляем массив R[1:n] в соответствии с формулой
double* ArrayCounter(int n, double x, double h, double a) {
    double* array = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        array[i] = 6 * cos(a * x + i * h);
    }
    return array;
}

// Удаляем все отрицательные элементы, расположенные между первым минимальным и последним положительным элементами;
double* ExclusionOfNegative(double* array, int n, int* flagPositive, int* flagNearby) {
    double minValue = 10.0;
    int minIndex = 0;
    int LastPositiveIndex = -1;
    int count = 0;

    //Находим индекс первого минимального
    for (int i = 0; i < n; i++) {
        if (array[i] < minValue) {
            minValue = array[i];
            minIndex = i;
            break;
        }
    }

    //Находим индекс последнего положительного
    for (int i = n - 1; i >= 0; i--) {
        if (array[i] > 0) {
            LastPositiveIndex = i;
            count++;
            *flagPositive = 1;
            break;
        } else if (count == 0) {
            *flagPositive = 0;
        }
    }

    //Переписываем список с помощью сдвига
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (*flagPositive && i < minIndex || *flagPositive && i > LastPositiveIndex || array[i] > 0) {
            array[j] = array[i];
            j++;
        }
    }

    if (LastPositiveIndex - minIndex < 2) {
        *flagNearby = 0;
    }

    return array;
}

// Посчитаем среднее арифметическое до первого минимального по модулю отрицательного элемента
double ArithmeticMean(double* array, int n) {
    double absMin = 1000.0;
    int absMinIndex = 0;
    double AverageAmount = 0.0;
    double count = 0.0;

    //Найдем первый минимальный по модулю отрицательный элемент
    for (int i = 0; i < n; i++) {
        if (array[i] < 0 && fabs(array[i]) < absMin) {
            absMin = fabs(array[i]);
            absMinIndex = i;
        }
    }

    for (int i = 0; i < absMinIndex; i++) {
        AverageAmount += array[i];
        count++;
    }
    return count > 0 ? AverageAmount / count : NAN;
}

int main() {
    double x, h, a;
    int n, limit = 200;
    int flagNearby = 1, flagPositive = 1;

    printf("Лабораторная работа №1\n");
    printf("Задание №1\n");
    printf("Введите длину массива R от 1 до %d\n", limit);
    scanf("%d", &n);

    if (n > limit) {
        printf("Ваше число больше указанного лимита\n");
        return 0;
    } else if (n <= 0) {
        printf("Ваше число меньше лимита\n");
        return 0;
    } else {
        printf("Введите x, h, a:\n");
        scanf("%lf %lf %lf", &x, &h, &a);
        double* startArray = ArrayCounter(n, x, h, a);
        printf("Массив R из %d элементов\n", n);
        for (int i = 0; i < n; i++) {
            printf("%lf ", startArray[i]);
        }
        printf("\n");

        double* modArray = ExclusionOfNegative(startArray, n, &flagPositive, &flagNearby);
        if (!flagPositive) {
            printf("Нет положительного элемента\n");
        } else {
            int modArrayLen = n;
            while (modArrayLen > 0 && modArray[modArrayLen - 1] == 0) {
                modArrayLen--;
            }
            printf("Массив r состоит из %d элементов\n", modArrayLen);
            for (int i = 0; i < modArrayLen; i++) {
                printf("%lf ", modArray[i]);
            }
            printf("\n");
        }

        double result = ArithmeticMean(modArray, n);
        printf("Задание 3\n");
        if (!flagNearby) {
            printf("Первый минимальный и последний положительный расположены рядом или совпадают\n");
        } else if (isnan(result)) {
            printf("Нет среднего значения\n");
        } else {
            printf("Среднее значение: %lf\n", result);
        }

        free(startArray);
    }

    return 0;
}
