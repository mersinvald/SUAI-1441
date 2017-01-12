#include <stdio.h>

void getInput(int &width,
              int &heigth,
              int** &bitmap, //array[w][h], initializing in function;
              int* &exitPoint, //array[2], 0 - x, 1 - y;
              int* &startPoint);

void printBitmap(int **bitmap, int w, int h);

int main()
{
    int width, heigth;
    int* startPoint;
    int* exitPoint;
    int** bitmap;
    getInput(width, heigth, bitmap, exitPoint, startPoint); //передаем ссылки на массивы и переменные, чтобы ф-я могла в них писать
    printBitmap(bitmap, width, heigth);
    return 0;
}

void getInput(int &width, int &heigth, int** &bitmap, int* &exitPoint, int* &startPoint) //получаем указатели на переданные переменные
{
    unsigned int i, j, x, y, bit, valid = 0; //unsigned, чтобы не было отрицательного ввода. Знаю, сурово, ибо сегфолт.

    printf("Enter labyrinth width: ");
    scanf("%i", &width);
    printf("Enter labyrinth heigth: ");
    scanf("%i", &heigth);

    //get WxH bitmam
    printf("Enter labyrinth bitmap:\n");
    bitmap = new int*[heigth]; //резервируем память для $heigth строк
    for(i = 0; i < heigth; i++)
    {
        bitmap[i] = new int[width]; //резервируем память для width ячеек в строке i
        for(j = 0; j < width; j++)
            scanf("%i", &bitmap[i][j]);
    }


    while(!valid) //ввод выходной точки
    {
        printf("\nEnter labyrinth exit point x y: ");
        scanf("%i%i", &x, &y);
        bit = bitmap[x][y];
        if(x <= width && y <= heigth && bit != 0)
            valid = 1;
        else
        printf("Point is out of map bounds or wall!\n");
    }
    //резервируем 2 ячейки по размеру int и пишем в них xy
    exitPoint = new int[2];
    exitPoint[0] = x;
    exitPoint[1] = y;

    valid = 0;

    while(!valid) //ввод стартовой позиции
    {
        printf("\nEnter labyrinth start point x y: ");
        scanf("%i%i", &x, &y);
        bit = bitmap[x][y];
        if(x <= width && y <= heigth && bit != 0)
            valid = 1;
        else
            printf("Point is out of map bounds or wall!\n");
    }

    //резервируем и пишем xy
    startPoint = new int[2];
    startPoint[0] = x;
    startPoint[1] = y;
}

void printBitmap(int **bitmap, int w, int h)
{
    int i, j;
    for(i = 0; i < h; i++){
        for(j = 0; j < w; j++)
            printf("%i", bitmap[i][j]);
        printf("\n");
    }
}
