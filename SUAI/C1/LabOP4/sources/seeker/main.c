#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void getInput(int *width, int *heigth,
              int** *bitmap, //array[w][h], инициализируется в ф-и
              int* *startPoint, int* *exitPoint); //array[2], 0 - x, 1 - y

int* trace(int *startPoint, int* exitpoint,
           int width, int heigth,
           int** bitmap,
           int** visited, //битовый массив закрашенных точек
           int* way); //путь, пройденный ф-ей"

void printBitmap(int **bitmap, int w, int h, int* way, int* startPoint, int* exitPoint);
void increaseWay(int* way, int x, int y);
int** invert(int** original, int w, int h);

int main(){
    int width, heigth, i;
    int* startPoint;
    int* exitPoint;
    int* way;
    int** bitmap;
    int** visited;

    getInput(&width, &heigth, &bitmap, &startPoint, &exitPoint); //передаем ссылки на массивы и переменные, чтобы ф-я могла в них писать

    visited = (int**) malloc(heigth * sizeof(int*));
    for(i = 0; i < width; i++)
        visited[i] = (int*) malloc(width * sizeof(int));

    visited = invert(bitmap, width, heigth); //инвертируем карту, чтобы присвоить стенкам статус посещенных точек.

    way = (int*) malloc(sizeof(int) * width * heigth);
    way[0] = 0;
    trace(startPoint, exitPoint, width, heigth, bitmap, visited, way);

    printBitmap(bitmap, width, heigth, way, startPoint, exitPoint);
    return 0;
}

void getInput(int *width, int *heigth, int** *bitmap, int* *startPoint, int* *exitPoint){ //получаем указатели на переданные переменные
    int i, j;
    int sx, sy, ex, ey;

    //временные переменные
    int tWidth, tHeigth;
    int* tExitPoint;
    int* tStartPoint;
    int** tBitmap;

    //printf("Enter labyrinth width: ");
    scanf("%i", &tWidth);
    //printf("Enter labyrinth heigth: ");
    scanf("%i", &tHeigth);

    //Получаем bitmap WxH
    //printf("Enter labyrinth bitmap:\n");
    tBitmap = (int**) malloc(tHeigth * sizeof(int *)); //резервируем память для $heigth строк
    for(i = 0; i < tHeigth; i++)
    {
        tBitmap[i] = (int*) malloc(tWidth * sizeof(int)); //резервируем память для width ячеек в строке i
        for(j = 0; j < tWidth; j++)
            scanf("%i", &tBitmap[i][j]);
    }

    scanf("%i%i", &ex, &ey); //задается стартовая точка
    scanf("%i%i", &sx, &sy); //задается выходная точка

    //резервируем 2 ячейки по размеру int и пишем в них xy
    tExitPoint = (int*) malloc(2 * sizeof(int));
    tExitPoint[1] = ex;
    tExitPoint[0] = ey;
    //резервируем и пишем xy
    tStartPoint = (int*) malloc(2 * sizeof(int));
    tStartPoint[1] = sx;
    tStartPoint[0] = sy;
    //возвращаем значения временных переменных
    *width = tWidth;
    *heigth = tHeigth;
    *startPoint = tStartPoint;
    *exitPoint = tExitPoint;
    *bitmap = tBitmap;
}

void printBitmap(int **bitmap, int w, int h, int* way, int* startPoint, int* exitPoint){
    int i, j, t, p = 0;

    /*for(i = 0; i < h-1; i++){
        printf("\n\t");
        for(j = 0; j < w-1; j++){
            if(startPoint[0] == i && startPoint[1] == j)
                printf("%s ", "S");
            else if(exitPoint[0] == i && exitPoint[1] == j)
                printf("%s ", "X");
            else
                if(bitmap[i][j] == 1)
                    printf("\033[32m%s\033[0m ", "\u00A0");
                else
                    printf("\033[34m\u25A0\033[0m ");
        }
    }*/

    printf("\n\n");
    for(i = 0; i < h; i++){
        printf("\n\t");
        for(j = 0; j < w; j++){
            for(t = 1; t < way[0]; t+=2)
                if(way[t] == i && way[t+1] == j)
                    p = 1;
            if(p)
                printf("\033[32m%s\033[0m ", "\u25A0");
            else
                if(bitmap[i][j] == 1)
                    printf("\033[31m%s\033[0m ", "\u00A0");
                else
                    printf("\033[34m%s\033[0m ", "\u25A0");
            p = 0;
        }
    }
    printf("\n");
}

int* trace(int *startPoint, int* exitpoint, int width, int heigth, int** bitmap, int** visited, int* way){
    static int depth;
    depth++;
    int x = startPoint[1];
    int y = startPoint[0];
    int routes[4] = {0, 0, 0, 0}; // 0 - вверх, 1 - вправо, 2 - вниз, 3 - влево

    int up[2]    = {y-1, x}; //стартовые точки для передачи в дочерние функции
    int right[2] = {y, x+1};
    int down[2]  = {y+1, x};
    int left[2]  = {y, x-1};

    int* result = NULL;

    //проверка направлений
    if(visited[y-1][x] == 0)   routes[0] = 1; //вверх
    if(visited[y][x+1] == 0)   routes[1] = 1; //вправо
    if(visited[y+1][x] == 0)   routes[2] = 1; //вниз
    if(visited[y][x-1] == 0)   routes[3] = 1; //влево

    visited[y][x] = 1; //закрашиваем текущую точку

    if(y == exitpoint[0] && x == exitpoint[1]){ //записываем найденный выход в way
        increaseWay(way, x, y);
        //printBitmap(bitmap, width, heigth, way, startPoint, exitpoint);
        return way;
    }

    if(routes[0] && result == NULL) result = trace(up, exitpoint, width, heigth, bitmap, visited, way); //скармливание дочерним функциям путей из текущей точки.
    if(routes[1] && result == NULL) result = trace(right, exitpoint, width, heigth, bitmap, visited, way);
    if(routes[2] && result == NULL) result = trace(down, exitpoint, width, heigth, bitmap, visited, way);
    if(routes[3] && result == NULL) result = trace(left, exitpoint, width, heigth, bitmap, visited, way);

    if(result != NULL){//записывываем текущую точку, если функция вызывалась на точке, пренадлежащей пути.
        increaseWay(way, x, y);
        //printBitmap(bitmap, width, heigth, way, startPoint, exitpoint);
    }

    return result; //возвращаем NULL, если тупик, после путь от выхода.
}

void increaseWay(int* way, int x, int y){
    int size    = way[0] + 2;
    way[size-1] = y;
    way[size]   = x;
    way[0]      = size;
}

int** invert(int** original, int w, int h){
    int i, j;
    int** temp = (int**) malloc(h * sizeof(int*));
    for(i = 0; i < h; i++){
        temp[i] = (int*) malloc(w * sizeof(int));
        for(j = 0; j < w; j++)
            temp[i][j] = !original[i][j];
    }
    return temp;
}
