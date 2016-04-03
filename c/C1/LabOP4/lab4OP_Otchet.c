1: //Исходный код
2: 
3: #include <stdio.h>
4: #include <stdlib.h>
5: 
6: void getInput(int *width, int *heigth,
7:               int** *bitmap, //array[w][h], инициализируется в ф-и
8:               int* *startPoint, int* *exitPoint); //array[2], 0 - x, 1 - y
9: 
10: int* trace(int *startPoint, int* exitpoint,text to pdf
11:            int width, int heigth,
12:            int** visited, //битовый массив закрашенных точек
13:            int* way); //путь, пройденный ф-ей"
14: 
15: void printBitmap(int **bitmap, int w, int h, int* way, int* startPoint, int* exitPoint);
16: void increaseWay(int* way, int x, int y);
17: void invert(int** original, int** *inverted, int w, int h);
18: 
19: int main(){
20:     int width, heigth;
21:     int* startPoint;
22:     int* exitPoint;
23:     int* way;
24:     int** bitmap;
25:     int** visited;
26: 
27:     getInput(&width, &heigth, &bitmap, &startPoint, &exitPoint); //передаем ссылки на массивы и переменные, чтобы ф-я могла в них писать
28:     invert(bitmap, &visited, width, heigth);//инвертируем, чтобы закрасить стенки
29: 
30:     way = (int*) malloc(sizeof(int) * width * heigth);
31:     way[0] = 0;
32:     trace(startPoint, exitPoint, width, heigth, visited, way);
33: 
34:     printBitmap(bitmap, width, heigth, way, startPoint, exitPoint);
35:     return 0;
36: }
37: 
38: void getInput(int *width, int *heigth, int** *bitmap, int* *startPoint, int* *exitPoint){ //получаем указатели на переданные переменные
39:     int i, j;
40:     int sx, sy, ex, ey;
41:     int bit, valid = 0;
42: 
43:     //временные переменные
44:     int tWidth, tHeigth;
45:     int* tExitPoint;
46:     int* tStartPoint;
47:     int** tBitmap;
48: 
49:     scanf("%i", &tWidth);
50:     scanf("%i", &tHeigth);
51: 
52:     //Получаем bitmap WxH
53:     tBitmap = (int**) malloc(tHeigth * sizeof(int *)); //резервируем память для $heigth строк
54:     for(i = 0; i < tHeigth; i++)
55:     {
56:         tBitmap[i] = (int*)malloc(tWidth * sizeof(int));//резервируем память для width ячеек в строке i
57:         for(j = 0; j < tWidth; j++)
58:             scanf("%i", &tBitmap[i][j]);
59:     }
60: 
61:     scanf("%i%i", &ex, &ey); //ввод выходной точки
62:     scanf("%i%i", &sx, &sy); //ввод стартовой позиции
63: 
64:     //резервируем 2 ячейки по размеру int и пишем в них xy
65:     tExitPoint = (int*) malloc(2 * sizeof(int));
66:     tExitPoint[1] = ex;
67:     tExitPoint[0] = ey;
68:     //резервируем и пишем xy
69:     tStartPoint = (int*) malloc(2 * sizeof(int));
70:     tStartPoint[1] = sx;
71:     tStartPoint[0] = sy;
72:     //возвращаем значения временных переменных
73:     *width = tWidth;
74:     *heigth = tHeigth;
75:     *startPoint = tStartPoint;
76:     *exitPoint = tExitPoint;
77:     *bitmap = tBitmap;
78: }
79: 
80: void printBitmap(int **bitmap, int w, int h, int* way, int* startPoint, int* exitPoint){
81:     int i, j, t, p = 0;
82:     printf("\n\t\tMaze map\n\t");
83:     for(i = 0; i < h; i++){
84:         for(j = 0; j < w; j++){
85:             if(startPoint[0] == i && startPoint[1] == j)
86:                 printf("%s ", "S");
87:             else if(exitPoint[0] == i && exitPoint[1] == j)
88:                 printf("%s ", "X");
89:             else
90:                 printf("%i ", bitmap[i][j]);
91:         }
92:         printf("\n\t");
93:     }
94: 
95:     printf("\n\t\tSolved maze\n\t");
96:     for(i = 0; i < h; i++){
97:         for(j = 0; j < w; j++){
98:             for(t = 1; t < way[0]; t+=2)
99:                 if(way[t] == i && way[t+1] == j)
100:                     p = 1;
101:             if(p)
102:                 printf("%s ", "X");
103:             else
104:                 printf("%i ", bitmap[i][j]);
105:             p = 0;
106:         }
107:         printf("\n\t");
108:     }
109:     printf("\n");
110: }
111: 
112: int* trace(int *startPoint, int* exitpoint, int width, int heigth, int** visited, int* way){
113:     int x = startPoint[1];
114:     int y = startPoint[0];
115:     int routes[4] = {0, 0, 0, 0}; // 0 - вверх, 1 - вправо, 2 - вниз, 3 - влево
116: 
117:     int up[2]    = {y-1, x}; //стартовые точки для передачи в дочерние функции
118:     int right[2] = {y, x+1};
119:     int down[2]  = {y+1, x};
120:     int left[2]  = {y, x-1};
121: 
122:     int* result = NULL;
123: 
124:     //проверка направлений
125:     if(visited[y-1][x] == 0)   routes[0] = 1; //вверх
126:     if(visited[y][x+1] == 0)   routes[1] = 1; //вправо
127:     if(visited[y+1][x] == 0)   routes[2] = 1; //вниз
128:     if(visited[y][x-1] == 0)   routes[3] = 1; //влево
129: 
130:     visited[y][x] = 1; //закрашиваем текущую точку
131: 
132:     if(y == exitpoint[0] && x == exitpoint[1]){ //записываем найденный выход в way
133:         increaseWay(way, x, y);
134:         return way;
135:     }
136: 
137:     if(routes[0] && result == NULL) result = trace(up, exitpoint, width, heigth, visited, way); //скармливание дочерним функциям путей из текущей точки.
138:     if(routes[1] && result == NULL) result = trace(right, exitpoint, width, heigth, visited, way);
139:     if(routes[2] && result == NULL) result = trace(down, exitpoint, width, heigth, visited, way);
140:     if(routes[3] && result == NULL) result = trace(left, exitpoint, width, heigth, visited, way);
141: 
142:     if(result != NULL){//записывываем текущую точку, если функция вызывалась на точке, пренадлежащей пути.
143:         increaseWay(way, x, y);
144:     }
145: 
146:     return result; //возвращаем NULL, если тупик, после путь от выхода.
147: }
148: 
149: void increaseWay(int* way, int x, int y){
150:     int size    = way[0] + 2;
151:     way[size-1] = y;
152:     way[size]   = x;
153:     way[0]      = size;
154: }
155: 



156: void invert(int** original, int** *inverted, int w, int h){
157:     int i, j;
158:     int** temp = (int**) malloc(h * sizeof(int*));
159:     for(i = 0; i < h; i++){
160:         temp[i] = (int*) malloc(w * sizeof(int));
161:         for(j = 0; j < w; j++)
162:             temp[i][j] = !original[i][j];
163:     }
164:     *inverted = temp;
165: }
