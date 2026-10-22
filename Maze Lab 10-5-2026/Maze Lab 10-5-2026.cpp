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
#include <windows.h>

const int MAZE_SIZE = 12;
const int DELAY_MS = 200;

enum Direction { DOWN, RIGHT, UP, LEFT };

void mazeTraverse( char maze[][MAZE_SIZE], int mazeSize, int xCoord,
    int yCoord, Direction direction );

bool validMove( char maze[][MAZE_SIZE], int xCoord, int yCoord );

bool isSolved( int arraySize, int xCoord, int yCoord );

void printMaze( char maze[][MAZE_SIZE], int mazeSize );

void clearScreen();

void mazeGenerator( char maze[][MAZE_SIZE], int mazeSize, int *startX,
    int *startY );


int main()
{
    char maze[MAZE_SIZE][MAZE_SIZE];
    int startX, startY;

    // Generate random maze and retrieve starting position.
    mazeGenerator( maze, MAZE_SIZE, &startX, &startY );

    mazeTraverse( maze, MAZE_SIZE, startX, startY, DOWN );

    return 0;
}


void mazeTraverse( char maze[][MAZE_SIZE], int mazeSize, int xCoord,
    int yCoord, Direction direction )
{
    if (xCoord == 0 && yCoord == 0 &&
        maze[xCoord][yCoord] == 'X')
    {
        clearScreen();
        std::cout << "Maze is unsolvable.\n";
        return;
    }

    maze[xCoord][yCoord] = 'X';

    clearScreen();
    printMaze( maze, mazeSize );
    Sleep( DELAY_MS );

    if (isSolved( mazeSize, xCoord, yCoord ) &&
        !(xCoord == 0 && yCoord == 0))
    {
        std::cout << "Maze solved!\n";
        return;
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

        if (validMove( maze, nextX, nextY ))
        {
            Direction nextDirection =
                static_cast<Direction>( (direction + 3) % 4 );
            mazeTraverse( maze, mazeSize, nextX, nextY,
                nextDirection );
            return;
        }

        direction = static_cast<Direction>( (direction + 1) % 4 );
    }
}


bool validMove( char maze[][MAZE_SIZE], int xCoord, int yCoord )
{
    if (xCoord < 0 || xCoord >= MAZE_SIZE || yCoord < 0 ||
        yCoord >= MAZE_SIZE)
    {
        return false;
    }

    return maze[xCoord][yCoord] != '#';
}


bool isSolved( int arraySize, int xCoord, int yCoord )
{
    return xCoord == 0 || xCoord == arraySize - 1 ||
        yCoord == 0 || yCoord == arraySize - 1;
}


void printMaze( char maze[][MAZE_SIZE], int mazeSize )
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
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count, cellCount;
    COORD homeCoords = { 0, 0 };

    if (hConsole == INVALID_HANDLE_VALUE)
    {
        return;
    }

    if (!GetConsoleScreenBufferInfo( hConsole, &csbi ))
    {
        return;
    }

    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter( hConsole, (TCHAR)' ', cellCount,
        homeCoords, &count))
    {
        return;
    }

    if (!FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
        cellCount, homeCoords, &count))
    {
        return;
    }

    SetConsoleCursorPosition( hConsole, homeCoords );
}


void mazeGenerator( char maze[][MAZE_SIZE], int mazeSize, int *startX,
    int *startY )
{
    // Simple linear congruential random number generator.
    auto randomInt = []( int maxVal ) -> int {
        static unsigned seed = GetTickCount();
        seed = seed * 1103515245 + 12345;
        return (seed / 65536) % maxVal;
    };

    // Initialize all cells as walls.
    for (int row = 0; row < mazeSize; ++row)
    {
        for (int col = 0; col < mazeSize; ++col)
        {
            maze[row][col] = '#';
        }
    }

    // Choose random interior starting location.
    *startX = 1 + randomInt( mazeSize - 2 );
    *startY = 1 + randomInt( mazeSize - 2 );
    maze[*startX][*startY] = '.';

    // Choose random exit location on border.
    int exitSide = randomInt( 4 );
    int exitRow, exitCol;

    if (exitSide == 0)
    {
        // Top edge
        exitRow = 0;
        exitCol = 1 + randomInt( mazeSize - 2 );
    }
    else if (exitSide == 1)
    {
        // Right edge
        exitRow = 1 + randomInt( mazeSize - 2 );
        exitCol = mazeSize - 1;
    }
    else if (exitSide == 2)
    {
        // Bottom edge
        exitRow = mazeSize - 1;
        exitCol = 1 + randomInt( mazeSize - 2 );
    }
    else
    {
        // Left edge
        exitRow = 1 + randomInt( mazeSize - 2 );
        exitCol = 0;
    }

    maze[exitRow][exitCol] = '.';
}