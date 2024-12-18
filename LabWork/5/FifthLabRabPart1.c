// 1. Создать файл для хранения действительных чисел, вводимых с клавиатуры. 
// Ввести данные. Прочитать этот файл, вывести данные на экран и вычислить: минимальное положительное число; 

#include <stdio.h>
#include <stdlib.h>

//ищем минимальный положительный элемент
double findMinPos(FILE *file) {
    double number, minPos = -1;
    rewind(file); //ставим указатель в начале файла

    while (fscanf(file, "%lf", &number) == 1) {
        if (number > 0) {
            if (minPos == -1 || number < minPos) {
                minPos = number;
            }
        }
    }

    return minPos;
}

int main() {
    char inputFileName[256], outputFileName[256];
    FILE *inputFile, *outputFile;
    double number;

    //вводим имена файлов
    printf("Введите имя входного файла: ");
    scanf("%255s", inputFileName);
    printf("Введите имя выходного файла: ");
    scanf("%255s", outputFileName);

    //открываем входной файл для записи
    inputFile = fopen(inputFileName, "w");
    if (inputFile == NULL) {
        printf("Ошибка открытия входного файла для записи.\n");
        return 1;
    }

    printf("Введите действительные числа (введите 0 для завершения):\n");
    while (1) {
        scanf("%lf", &number);
        if (number == 0) break;
        fprintf(inputFile, "%.6lf\n", number);
    }

    fclose(inputFile);

    //открываем входной файл для чтения
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Ошибка открытия входного файла для чтения.\n");
        return 1;
    }

    //открываем выходной файл для записи
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Ошибка открытия выходного файла.\n");
        fclose(inputFile);
        return 1;
    }

    printf("Содержимое файла:\n");
    while (fscanf(inputFile, "%lf", &number) == 1) {
        printf("%.6lf\n", number);
        fprintf(outputFile, "%.6lf\n", number);
    }

    //ищем минимальное положительное число
    double minPos = findMinPos(inputFile);
    if (minPos == -1) {
        printf("В файле нет положительных чисел.\n");
    } else {
        printf("Минимальное положительное число: %.6lf\n", minPos);
    }

    //закрываем файлы
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
