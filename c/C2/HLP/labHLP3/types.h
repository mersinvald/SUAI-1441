#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>

/* Задание:
 * 1) Ввод массива структур             (SA*)
 * 2) Сортировка массива структур       (SA*)
 * 3) Поиск по параметру                (SA*)
 * 4) Изменение заданой структуры       (SA*)
 * 5) Удаление структуры из массива     (SA*)
 * 6) Вывод на экран массива структур   (SA*)
 * 7) Выход                             (SA*)
 */

#define BUFSIZE 64

typedef unsigned char ubyte;

enum MENU {
    ENTER = 1,
    SORT,
    SEARCH,
    EDIT,
    DELETE,
    PRINT,
    EXIT
};

typedef struct data_s {
    char author[BUFSIZE];
    char title [BUFSIZE];
    char medium[BUFSIZE];
    uint size;
} Data;

typedef struct struct_array_s {
    Data *array;
    uint len;
} StructArray;

#endif // TYPES_H

