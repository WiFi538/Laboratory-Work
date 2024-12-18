// 2. Создать текстовый файл средствами редактора (т.е. в «Блокноте»). Прочитать этот файл построчно и 
// произвести в каждой строке следующие действия: вставить два нуля между каждыми двумя соседними латинскими буквами;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

//функция для вставки двух нулей между латинскими буквами
void inZeroLatin(char *line) {
    int len = strlen(line);
    char result[MAX_LINE_LENGTH * 3]; 
    result[0] = '\0'; 

    for (int i = 0; i < len; i++) {
        strncat(result, &line[i], 1); //добавляем текущий символ

        //проверка являются ли текущий и последующие символы латинскими буквами 
        if (i < len - 1 && isalpha(line[i]) && isalpha(line[i + 1])) {
            strcat(result, "00"); //вставляем два нуля
        }
    }

    //копируем результат обратно в исходную строку
    strcpy(line, result);
}

int main() {
    char inputFileName[256], outputFileName[256];
    char line[MAX_LINE_LENGTH];

    //запрашиваем имена файлов у пользователя
    printf("Введите имя входного файла: ");
    scanf("%255s", inputFileName);
    printf("Введите имя выходного файла: ");
    scanf("%255s", outputFileName);

    //открываем входной файл для чтения
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Ошибка открытия входного файла.\n");
        return 1;
    }

    //открываем выходной файл для записи
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Ошибка открытия выходного файла.\n");
        fclose(inputFile);
        return 1;
    }

    //построчно читаем файл
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        //вставляем нули между латинскими буквами
        inZeroLatin(line);

        //записываем измененную строку в выходной файл
        fprintf(outputFile, "%s", line);
    }

    //закрываем файлы
    fclose(inputFile);
    fclose(outputFile);

    printf("Обработка завершена. Результат записан в файл: %s\n", outputFileName);

    return 0;
}
