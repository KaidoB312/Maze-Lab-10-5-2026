/*
Name: Jay Jackson
Date: 10/5/2026
Project: A program that makes a maze using an array and solves that maze using
the algorithm described in the Deitel book. This version uses Windows.h to
pause and clear the screen between steps so the solution can be seen visually.

I hearby state that this is my work and only my work without outside help such
as AI, Google, Wikipedia, or other plagerism aligned items

Signature: Jay Jackson
*/

#include <iostream>
#include <vector>
#include <windows.h>

const int MAZE_SIZE = 12;
const int DELAY_MS = 200;

enum Direction { DOWN, RIGHT, UP, LEFT };

struct Wall
{
    int xCoord;
    int yCoord;
};

bool mazeTraverse(char maze[][MAZE_SIZE], int mazeSize, int xCoord,
    int yCoord, Direction direction);

bool validMove(char maze[][MAZE_SIZE], int xCoord, int yCoord);

bool isSolved(int arraySize, int xCoord, int yCoord);

void printMaze(char maze[][MAZE_SIZE], int mazeSize);

void clearScreen();

void mazeGenerator(char maze[][MAZE_SIZE], int mazeSize, int* startX,
    int* startY);


int main()
{
    char maze[MAZE_SIZE][MAZE_SIZE];
    int startX = 0, startY = 0;

    // Generate random maze and retrieve starting position.
    mazeGenerator(maze, MAZE_SIZE, &startX, &startY);

    if (!mazeTraverse(maze, MAZE_SIZE, startX, startY, DOWN))
    {
        std::cout << "Maze is unsolvable.\n";
    }

    return 0;
}


bool mazeTraverse(char maze[][MAZE_SIZE], int mazeSize, int xCoord,
    int yCoord, Direction direction)
{
    maze[xCoord][yCoord] = 'X';

    clearScreen();
    printMaze(maze, mazeSize);
    Sleep(DELAY_MS);

    if (isSolved(mazeSize, xCoord, yCoord) &&
        !(xCoord == 0 && yCoord == 0))
    {
        std::cout << "Maze solved!\n";
        return true;
    }

    for (int step = 0; step < 4; ++step)
    {
        int nextX = xCoord;
        int nextY = yCoord;

        switch (direction)
        {
        case DOWN:
            ++nextX;
            break;
        case RIGHT:
            ++nextY;
            break;
        case UP:
            --nextX;
            break;
        case LEFT:
            --nextY;
            break;
        }

        if (validMove(maze, nextX, nextY))
        {
            Direction nextDirection =
                static_cast<Direction>((direction + 3) % 4);
            if (mazeTraverse(maze, mazeSize, nextX, nextY,
                nextDirection))
            {
                return true;
            }
        }

        direction = static_cast<Direction>((direction + 1) % 4);
    }

    return false;
}


bool validMove(char maze[][MAZE_SIZE], int xCoord, int yCoord)
{
    if (xCoord < 0 || xCoord >= MAZE_SIZE || yCoord < 0 ||
        yCoord >= MAZE_SIZE)
    {
        return false;
    }

    return maze[xCoord][yCoord] == '.';
}


bool isSolved(int arraySize, int xCoord, int yCoord)
{
    return xCoord == 0 || xCoord == arraySize - 1 ||
        yCoord == 0 || yCoord == arraySize - 1;
}


void printMaze(char maze[][MAZE_SIZE], int mazeSize)
{
    for (int row = 0; row < mazeSize; ++row)
    {
        for (int col = 0; col < mazeSize; ++col)
        {
            std::cout << maze[row][col] << ' ';
        }

        std::cout << '\n';
    }

    std::cout << '\n';
}


void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count, cellCount;
    COORD homeCoords = { 0, 0 };

    if (hConsole == INVALID_HANDLE_VALUE)
    {
        return;
    }

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount,
        homeCoords, &count))
    {
        return;
    }

    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
        cellCount, homeCoords, &count))
    {
        return;
    }

    SetConsoleCursorPosition(hConsole, homeCoords);
}


void mazeGenerator(char maze[][MAZE_SIZE], int mazeSize, int* startX,
    int* startY)
{
    // Simple linear congruential random number generator.
    auto randomInt = [](int maxVal) -> int {
        static unsigned seed = GetTickCount();
        seed = seed * 1103515245 + 12345;
        return (seed / 65536) % maxVal;
        };

    std::vector<Wall> wallList;
    int startCellX = 1 + randomInt((mazeSize - 1) / 2) * 2;
    int startCellY = 1 + randomInt((mazeSize - 1) / 2) * 2;
    int exitSide = 0, exitRow = 0, exitCol = 0;
    int lastCell = 0, cellCoord = 0, cellIndex = 0;

    auto addWalls = [&](int cellX, int cellY) {
        const int directions[4][2] = {
            { -2, 0 }, { 2, 0 }, { 0, -2 }, { 0, 2 }
        };

        for (int i = 0; i < 4; ++i)
        {
            int neighborX = cellX + directions[i][0];
            int neighborY = cellY + directions[i][1];

            if (neighborX >= 1 && neighborX <= mazeSize - 2 &&
                neighborY >= 1 && neighborY <= mazeSize - 2)
            {
                Wall wall;
                wall.xCoord = cellX + directions[i][0] / 2;
                wall.yCoord = cellY + directions[i][1] / 2;
                wallList.push_back(wall);
            }
        }
        };

    // Initialize all cells.
    for (int row = 0; row < mazeSize; ++row)
    {
        for (int col = 0; col < mazeSize; ++col)
        {
            maze[row][col] = '#';
        }
    }

    // Start Randomized Prim's algorithm from one random interior cell.
    maze[startCellX][startCellY] = '.';
    addWalls(startCellX, startCellY);

    // Expand outward by processing random walls.
    while (!wallList.empty())
    {
        int wallIndex = randomInt(
            static_cast<int>(wallList.size()));
        Wall wall = wallList[wallIndex];
        wallList[wallIndex] = wallList.back();
        wallList.pop_back();

        int cellAX = 0, cellAY = 0, cellBX = 0, cellBY = 0;

        if (wall.xCoord % 2 == 0)
        {
            cellAX = wall.xCoord - 1;
            cellAY = wall.yCoord;
            cellBX = wall.xCoord + 1;
            cellBY = wall.yCoord;
        }
        else
        {
            cellAX = wall.xCoord;
            cellAY = wall.yCoord - 1;
            cellBX = wall.xCoord;
            cellBY = wall.yCoord + 1;
        }

        bool aVisited = maze[cellAX][cellAY] == '.';
        bool bVisited = maze[cellBX][cellBY] == '.';

        if (aVisited != bVisited)
        {
            maze[wall.xCoord][wall.yCoord] = '.';

            if (!aVisited)
            {
                maze[cellAX][cellAY] = '.';
                addWalls(cellAX, cellAY);
            }
            else
            {
                maze[cellBX][cellBY] = '.';
                addWalls(cellBX, cellBY);
            }
        }
    }

    // Connect a random border exit to the carved maze.
    lastCell = ((mazeSize - 1) / 2) * 2 - 1;
    cellIndex = randomInt((mazeSize - 1) / 2);
    cellCoord = 1 + cellIndex * 2;
    exitSide = randomInt(4);

    if (exitSide == 0)
    {
        // Top edge.
        exitRow = 0;
        exitCol = cellCoord;
        maze[exitRow][exitCol] = '.';
    }
    else if (exitSide == 1)
    {
        // Right edge.
        exitRow = cellCoord;
        exitCol = mazeSize - 1;

        for (int col = lastCell + 1; col <= exitCol; ++col)
        {
            maze[exitRow][col] = '.';
        }
    }
    else if (exitSide == 2)
    {
        // Bottom edge.
        exitRow = mazeSize - 1;
        exitCol = cellCoord;

        for (int row = lastCell + 1; row <= exitRow; ++row)
        {
            maze[row][exitCol] = '.';
        }
    }
    else
    {
        // Left edge.
        exitRow = cellCoord;
        exitCol = 0;
        maze[exitRow][exitCol] = '.';
    }

    *startX = startCellX;
    *startY = startCellY;
}