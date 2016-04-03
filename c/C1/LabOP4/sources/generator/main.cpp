#include <QtCore>
#include <iostream>
#include <random>

using namespace std;

struct Cell{
    int x;
    int y;
    bool wall;
    bool visited;
    char sym;
};
struct Coordinates{
    Coordinates(int x, int y){
        this->x = x;
        this->y = y;
    }
    Coordinates(){
        this->x = 0;
        this->y = 0;
    }
    const Coordinates operator- (const Coordinates& c) const{
        Coordinates result;
        result.x = this->x - c.x;
        result.y = this->y - c.y;
        return result;
    }

    int x;
    int y;
};

typedef Coordinates              cods;
typedef QVector< QVector<Cell> > mazeArray;
typedef QVector<Cell>            CellArray;

mazeArray init(int width, int heigth);
QStringList input(int argc, char** argv);
void printMaze(mazeArray maze);
int randomRange(int low, int high);
mazeArray generate(mazeArray maze);
CellArray getCells(mazeArray &maze);
CellArray getNeighbours(mazeArray maze, Cell c);
int unvisitedNum(mazeArray maze);
CellArray getUnvisitedCells(mazeArray &maze);
mazeArray removeWall(Cell first, Cell second, mazeArray maze);



int main(int argc, char *argv[])
{
    QStringList args = input(argc, argv);
    quint16 width  = args[1].toInt() * 2 + 2;
    quint16 heigth = args[2].toInt() * 2 + 2;

    mazeArray maze = init(width, heigth);
    maze = generate(maze);
    //printMaze(maze);

    return 0;

}

mazeArray init(int width, int heigth){
    mazeArray maze(heigth);
    QVector<Cell> mazeW(width);

    for(int i = 0; i < heigth; i++){ //инициализируем матрицу и заполняем стенами
        maze[i] = mazeW;
        for(int j = 0; j < width; j++){
            maze[i][j].x = j;
            maze[i][j].y = i;
            maze[i][j].wall = 1;
        }
    }

    for(int i = 1; i < heigth-1; i+=2){ //инициализируем клетки.
        for(int j = 1; j < width-1; j+=2){
            maze[i][j].wall = 0;
        }
    }
    return maze;
}



mazeArray generate(mazeArray maze){
    Cell currentCell = maze[1][1]; maze[1][1].visited = 1;
    Cell &cc = currentCell;
    QStack<Cell> stack;
    int unvisited = unvisitedNum(maze);
    while(unvisited > 0){
        CellArray neighbours = getNeighbours(maze, currentCell);
        if(!neighbours.empty())
        {
            int randNum = randomRange(0, neighbours.size()-1); //-1 - OutOfRange при size()
            Cell nextCell = neighbours[randNum];
            stack.push(currentCell);
            maze = removeWall(currentCell, nextCell, maze);
            currentCell = nextCell;
            maze[cc.y][cc.x].visited = 1;
            unvisited--;
        }
        else if(!stack.empty()){
            currentCell = stack.pop();
        }
        else{
            CellArray unvisited = getUnvisitedCells(maze);
            int randNum = randomRange(0, unvisited.size()-1);
            currentCell = unvisited[randNum];
        }
    }

    return maze;
}

int randomRange(int low, int high){
    std::random_device rd1;
    uniform_int_distribution<int> distribution(low,high);
    return distribution(rd1);
}

mazeArray removeWall(Cell first, Cell second, mazeArray maze){
    cods c1(first.x, first.y);
    cods c2(second.x, second.y);
    cods diff = c2 - c1;
    cods target;
    int addition = 0;

    bool diffx = 0;
    bool diffy = 0;

    if(diff.x != 0) diffx = 1;
    if(diff.y != 0) diffy = 1;

    if(diffx && diffy){
        qDebug() << "removeWall Error: Переданные клетки имеют больше одной общей стены.";
    }

    if(diffx){
        if(diff.x > 0) addition = 1;
        else           addition = -1;
        target.x = c1.x + addition;
        target.y = c1.y;
    }
    else
    if(diffy){
        if(diff.y > 0) addition = 1;
        else           addition = -1;
        target.x = c1.x;
        target.y = c1.y + addition;
    }

    cods &t = target;
    maze[t.y][t.x].wall    = 0;
    maze[t.y][t.x].visited = 1;

    return maze;
}

CellArray getNeighbours(mazeArray maze, Cell c){
    int heigth = maze.size();
    int width  = maze[0].size();
    int x = c.x;
    int y = c.y;
    cods up    (x, y-2);
    cods rt (x+2, y);
    cods dw  (x, y+2);
    cods lt  (x-2, y);
    bool u = 0,
         r = 0,
         d = 0,
         l = 0;

    CellArray neighbours;

    if(up.x >= 0 && up.x <= width && up.y >= 0 && up.y <= heigth) u = 1;
    if(rt.x >= 0 && rt.x <= width && rt.y >= 0 && rt.y <= heigth) r = 1;
    if(dw.x >= 0 && dw.x <= width && dw.y >= 0 && dw.y <= heigth) d = 1;
    if(lt.x >= 0 && lt.x <= width && lt.y >= 0 && lt.y <= heigth) l = 1;

    if(u) if(!maze[up.y][up.x].wall && !maze[up.y][up.x].visited) neighbours.append(maze[up.y][up.x]);
    if(r) if(!maze[rt.y][rt.x].wall && !maze[rt.y][rt.x].visited) neighbours.append(maze[rt.y][rt.x]);
    if(d) if(!maze[dw.y][dw.x].wall && !maze[dw.y][dw.x].visited) neighbours.append(maze[dw.y][dw.x]);
    if(l) if(!maze[lt.y][lt.x].wall && !maze[lt.y][lt.x].visited) neighbours.append(maze[lt.y][lt.x]);

    return neighbours;
}

CellArray getCells(mazeArray &maze){
    int heigth = maze.size();
    int width  = maze[0].size();

    CellArray cells;

    for (int i = 0; i < heigth; i++)
        for (int j = 0; j < width; j++)
            if(!maze[i][j].wall)
                cells.append(maze[i][j]);

    return cells;
}

CellArray getUnvisitedCells(mazeArray &maze){
    CellArray cells = getCells(maze);
    CellArray unvisitedCells;
    for (int i = 0; i < cells.size(); i++){
        if(!cells[i].visited) unvisitedCells.append(cells[i]);
    }
    return unvisitedCells;
}

int unvisitedNum(mazeArray maze){
    int heigth = maze.size();
    int width  = maze[0].size();
    int count = 0;
    for (int i = 0; i < heigth; i++)
        for (int j = 0; j < width; j++)
            if(!maze[i][j].visited && !maze[i][j].wall) count++;
    return count;
}

QStringList input(int argc, char** argv){
    QString     arg;
    QStringList args;

    for(int i = 0; i < argc; i++){
        arg = arg.fromStdString(argv[i]);
        args.append(arg);
        arg.clear();
    }
    return args;
}

void printMaze(mazeArray maze){
    int h = maze.size();
    int w = maze[0].size();
    int randNumS = 0;
    int randNumE = 0;

    cout << w << endl << h << endl;
    cout << endl;
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            cout << maze[i][j].wall << " ";
        }
        cout << endl;
    }

    CellArray cells = getCells(maze);
    cods start(1,1);
    cods exit(w-3,h-3);

    cout << endl << exit.x << " " << exit.y
         << endl << start.x << " " << start.y << endl;
}
