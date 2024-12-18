#include <stdio.h>

// Функция для вычисления знаменателя (ae - bd)
double calculateDenominator(double a, double b, double d, double e) {
    return a * e - b * d;
}

int main() {
    printf("Лабораторная работа №3, Часть 1\n");

    double a, b, c, d, e, f;
    double x, y;

    // Ввод данных
    printf("Введите значения a, b, c, d, e, f: ");
    scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f);

    // Вычисление знаменателя
    double denominator = calculateDenominator(a, b, d, e);

    // Проверка на нулевой знаменатель
    if (denominator == 0) {
        printf("Ошибка: знаменатель равен нулю.\n");
        return 1;
    }

    // Вычисление x и y
    x = (c * e - b * f) / denominator;
    y = (a * f - c * d) / denominator;

    printf("x = %lf\n", x);
    printf("y = %lf\n", y);

    return 0;
}
