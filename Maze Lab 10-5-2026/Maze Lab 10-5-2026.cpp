/*
Name: Jay Jackson
Date: 10/5/2026
Project: A program that makes a maze using an array and solves that maze using
the algorithm described in the Deitel book. This version uses Windows.h to
pause and clear the screen between steps so the solution can be seen visually.
No cstdlib is used; the console is cleared using the Windows API directly.

I hearby state that this is my work and only my work without outside help such
as AI, Google, Wikipedia, or other plagerism aligned items

Signature: Jay Jackson
*/

#include <iostream>
#include <windows.h>

const int MAZE_SIZE = 12;
const int ENTRANCE_X = 2;
const int ENTRANCE_Y = 0;
const int DELAY_MS = 200;

enum Direction { DOWN, RIGHT, UP, LEFT };

void mazeTraverse(char maze[][MAZE_SIZE], int size, int xCoord, int yCoord,
    Direction direction);
bool validMove(char maze[][MAZE_SIZE], int xCoord, int yCoord);
bool isSolved(int arraySize, int xCoord, int yCoord);
void printMaze(char maze[][MAZE_SIZE], int size);
void clearScreen();


int main()
{
    char maze[MAZE_SIZE][MAZE_SIZE] = {
        {'#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','#','.','.','.','.','.','.','#'},
        {'.','.','#','.','#','.','#','#','#','#','.','#'},
        {'#','#','#','.','#','.','.','.','.','#','.','#'},
        {'#','.','.','.','.','#','#','#','.','#','.','.'},
        {'#','#','#','#','.','#','.','#','.','#','.','#'},
        {'#','.','.','#','.','#','.','#','.','#','.','#'},
        {'#','#','.','#','.','#','.','#','.','#','.','#'},
        {'#','.','.','.','.','.','.','.','.','#','.','#'},
        {'#','#','#','#','#','#','.','#','#','#','.','#'},
        {'#','.','.','.','.','.','.','#','.','.','.','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#'}
    };

    mazeTraverse(maze, MAZE_SIZE, ENTRANCE_X, ENTRANCE_Y, DOWN);

    return 0;
}


void mazeTraverse(char maze[][MAZE_SIZE], int size, int xCoord, int yCoord,
    Direction direction)
{
    if (xCoord == ENTRANCE_X && yCoord == ENTRANCE_Y &&
        maze[xCoord][yCoord] == 'X')
    {
        clearScreen();
        std::cout << "Maze is unsolvable.\n";
        return;
    }

    maze[xCoord][yCoord] = 'X';

    clearScreen();
    printMaze(maze, size);
    Sleep(DELAY_MS);

    if (isSolved(size, xCoord, yCoord) &&
        !(xCoord == ENTRANCE_X && yCoord == ENTRANCE_Y))
    {
        std::cout << "Maze solved!\n";
        return;
    }

    for (int i = 0; i < 4; ++i)
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
            Direction nextDirection = static_cast<Direction>(
                (direction + 3) % 4);
            mazeTraverse(maze, size, nextX, nextY, nextDirection);
            return;
        }

        direction = static_cast<Direction>((direction + 1) % 4);
    }
}


bool validMove(char maze[][MAZE_SIZE], int xCoord, int yCoord)
{
    if (xCoord < 0 || xCoord >= MAZE_SIZE || yCoord < 0 ||
        yCoord >= MAZE_SIZE)
    {
        return false;
    }

    return maze[xCoord][yCoord] != '#';
}


bool isSolved(int arraySize, int xCoord, int yCoord)
{
    return xCoord == 0 || xCoord == arraySize - 1 ||
        yCoord == 0 || yCoord == arraySize - 1;
}


void printMaze(char maze[][MAZE_SIZE], int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            std::cout << maze[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}


void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
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

    if (!FillConsoleOutputCharacter(
        hConsole, (TCHAR)' ', cellCount, homeCoords, &count))
    {
        return;
    }

    if (!FillConsoleOutputAttribute(
        hConsole, csbi.wAttributes, cellCount, homeCoords, &count))
    {
        return;
    }

    SetConsoleCursorPosition(hConsole, homeCoords);
}