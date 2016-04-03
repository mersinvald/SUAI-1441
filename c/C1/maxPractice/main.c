/*Нахождение циклического сдвига в массиве.
 *На вход подается двумерный массив, затем выбирается одна из строк массива,
 *Для каждой строки массива, если таковая является циклическим сдвигом от выбранной,
 *выводится значение сдвига: положительное, если сдвиг вправо, отрицательное, если влево.
 *Автор программы: mersinvald.
 *Дата: 30.06.15
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 99999999

int  checkCycle(int* lFirst, int* lSecond, int size);
int  checkShift(int* lFirst, int* lSecond, int size, int shift);
void commitShift     (int* line, int size, int shift);

void printLine(int* line, int size);

int main(void)
{
    int** array;
    int shift;
    int line;
    int sizeX, sizeY;
    int i, j;

    printf("Enter array size HxW: ");
    scanf("%i%i", &sizeY, &sizeX);

    printf("Enter array:\n");

    array = malloc(sizeY * sizeof(int*)); //аллокация памяти и ввод массива
    for(i = 0; i < sizeY; i++){
        printf("Line %i: ", i);
        array[i] = malloc(sizeX * sizeof(int));
        for(j = 0; j < sizeX; j++){
            scanf("%i", &array[i][j]);
        }
    }

    printf("\nEnter target line: ");
    scanf("%i", &line);

    printf("\nShifts:\n");

    for(i = 0; i < sizeY; i++){
        shift = checkCycle(array[line], array[i], sizeX); //получаем значение сдвига, если есть, INF, если нет
        if(shift != INF){ //выводим сдвиг от целевой строки к строке i, если он есть
            printf("Shift from %i to %i is %i\n", line, i, shift);
        }
    }
    return 0;
}



int checkCycle(int* lFirst, int* lSecond, int size){
    /* Здесь находится кратчайший сдвиг. И отрицательный и положительный.
     * Например 1 2 3 4 5 можно сдвинуть до 2 3 4 5 1 двумя свособами:
     * либо на 1 влево(-1), либо на 4 вправо (4)
     * Если нужно получить только сдвиги вправо или только влево, просто измени значения минимального и максимального сдвигов
     */
    int shift    = (-size)+1; //минимальный сдвиг. Отрицателен, равен минимальному неполному циклу
    int maxShift = size-1; //максимальный сдвиг равен size-1, size или 0 - полный цикл, обрабатывается в порядке исключения.

    int caught = INF; //найденный сдвиг, инициализируем бесконечностью


    for(; shift <= maxShift; shift++){
        if(checkShift(lFirst, lSecond, size, shift))//проверяем, есть ли сдвиг и
            if(abs(shift) < abs(caught)) //если есть, меньше ли он по модулю уже найденного. См ремарку в начале ф-и
                caught = shift;
        }

    return caught; //возвращаем сдвиг, если есть, иначе -1;
}


int checkShift(int *lFirst, int *lSecond, int size, int shift){
    int* tempFirstLine = malloc(size * sizeof(int)); //создаем временный массив
    int i;
    int result = 1;

    for(i = 0; i < size; i++){
        tempFirstLine[i] = lFirst[i]; //копируем данные из первого массива в временный
    }

    commitShift(tempFirstLine, size, shift); //сдвигаем временный массив на переданное значение shift

    for(i = 0; i < size; i++){ //сравниваем временный массив со вторым массивом
        if(tempFirstLine[i] != lSecond[i]) result = 0; // если хоть один элемент не совпадает, результат отрицателен -> сдвига нет
    }

    free(tempFirstLine); //освобождаем память временного массива
    return result;
}

void commitShift(int *line, int size, int shift){
    int i, j;
    int t;
    //printf("\n");
    //printLine(line, size);
    if(shift >= 0){
        for(i = 0; i < shift; i++){
            t = line[size-1];
            for(j = size-1; j > 0; j--){
                line[j] = line[j-1];
                //printLine(line, size);
            }
            line[0] = t;
            //printLine(line, size);
        }
    }
    else{
        shift = abs(shift);
        for(i = 0; i < shift; i++){
            t = line[0];
            for(j = 0; j < size-1; j++){
                line[j] = line[j+1];
                //printLine(line, size);
            }
            line[size-1] = t;
            //printLine(line, size);
        }
    }

}

void printLine(int *line, int size){
    int i;
    printf("\n");
    for(i = 0; i < size; i++){
        printf("%i ", line[i]);
    }
    fflush(stdout); //выводит на экран все, что было в буффере (по дефолту stdout выводится при смене строки)
}

/*
1 2 3

1 : 3 1 2
-1: 2 3 1
*/
