#include <stdio.h>
#include <stdlib.h>
#define SIZE 100
const int width =  10;
const int heigth = 12;




void getInput(int bitmap[heigth][width], //array[w][h], initializing in function;
              int exitPoint[2], //array[2], 0 - x, 1 - y;
              int startPoint[2]);

int* trace(int startPoint[2], int* visited[heigth][width], int exitpoint[2], int way[SIZE], int waySize){
    int x = startPoint[0];
    int y = startPoint[1];
    int i;
    int routesNum = 0;
    int routes[4] = {0, 0, 0, 0}; // 0 - вверх, 1 - вправо, 2 - вниз, 3 - влево
    int up[2]    = {x, y+1};
    int right[2] = {x+1, y};
    int down[2]  = {x, y-1};
    int left[2]  = {x-1, y};
    int result[100];
    int tVisited[heigth][width] = *visited;

    //проверка направлений
    if(!tVisited[y+1][x]) { //вверх
        routesNum++;
        routes[0] = 1;
    }
    if(!tVisited[y][x+1]) { //вправо
        routesNum++;
        routes[1] = 1;
    }
    if(!tVisited[y-1][x]) { //вниз
        routesNum++;
        routes[2] = 1;
    }
    if(!tVisited[y][x-1]) { //влево
        routesNum++;
        routes[3] = 1;
    }

    *visited[y][x] = 1; //закрашиваем текущую точку
    //записываем текущую точку в way
    waySize += 2;
    way[waySize-1]  = x;
    way[waySize]    = y;

    if(x == exitpoint[0] && y == exitpoint[1]) return way;
    if(!routesNum) return NULL;

    for(i = 0; i < routesNum; i++){
        if(routes[0] && result == NULL) result = trace(up, visited, exitpoint, way, waySize);
        if(routes[1] && result == NULL) result = trace(right, visited, exitpoint, way, waySize);
        if(routes[2] && result == NULL) result = trace(down, visited, exitpoint, way, waySize);
        if(routes[4] && result == NULL) result = trace(left, visited, exitpoint, way, waySize);
    }
}



int main()
{
    int i, j;
    int width, heigth;
    int startPoint[2];
    int exitPoint[2];
    int way[SIZE];
    int bitmap[heigth][width];
    int visited[heigth][width];

    for(i = 0; i < heigth; i++)
        for(j = 0; j < width; j++)
            scanf("%i", &bitmap[i][j]);


    for(i = 0; i < heigth; i++){ //инвертируем карту, чтобы присвоить стенкам статус посещенных точек
        for(j = 0; j < width; j++)
            visited[i][j] = !bitmap[i][j];
    }
    scanf("%i%i", &exitPoint[0], &exitPoint[1]);
    scanf("%i%i", &startPoint[0], &startPoint[1]);

    way = trace(startPoint, &visited, exitPoint, way, 0);
    return 0;
}



