#include "MyArray.h"
#include <stdexcept>

MyArray::MyArray() {
	/*
	Initialize the maze with hardcoded data. Rows are stored as follows:
	'#' = wall (impassable), '.' = open path (passable), 'X' = visited cell.
	The entrance is at row 2, column 0.
	*/
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j) {
			mazeData[i][j] = '.';
		}
	}

	// Row 0: all walls
	char row0[] = { '#','#','#','#','#','#','#','#','#','#','#','#' };
	for (int j = 0; j < 12; ++j) mazeData[0][j] = row0[j];

	// Row 1
	char row1[] = { '#','.','.','.','#','.','.','.','.','.','.','#' };
	for (int j = 0; j < 12; ++j) mazeData[1][j] = row1[j];

	// Row 2 (entrance row)
	char row2[] = { '.','.','#','.','#','.','#','#','#','#','.','#' };
	for (int j = 0; j < 12; ++j) mazeData[2][j] = row2[j];

	// Row 3
	char row3[] = { '#','#','#','.','#','.','.','.','.','#','.','#' };
	for (int j = 0; j < 12; ++j) mazeData[3][j] = row3[j];

	// Row 4
	char row4[] = { '#','.','.','.','.','#','#','#','.','#','.','.' };
	for (int j = 0; j < 12; ++j) mazeData[4][j] = row4[j];

	// Row 5
	char row5[] = { '#','#','#','#','.','#','.','#','.','#','.','#' };
	for (int j = 0; j < 12; ++j) mazeData[5][j] = row5[j];

	// Row 6
	char row6[] = { '#','.','.','#','.','#','.','#','.','#','.','#' };
	for (int j = 0; j < 12; ++j) mazeData[6][j] = row6[j];

	// Row 7
	char row7[] = { '#','#','.','#','.','#','.','#','.','#','.','#' };
	for (int j = 0; j < 12; ++j) mazeData[7][j] = row7[j];

	// Row 8
	char row8[] = { '#','.','.','.','.','.','.','.','.','#','.','#' };
	for (int j = 0; j < 12; ++j) mazeData[8][j] = row8[j];

	// Row 9
	char row9[] = { '#','#','#','#','#','#','.','#','#','#','.','#' };
	for (int j = 0; j < 12; ++j) mazeData[9][j] = row9[j];

	// Row 10
	char row10[] = { '#','.','.','.','.','.','.','#','.','.','.','#' };
	for (int j = 0; j < 12; ++j) mazeData[10][j] = row10[j];

	// Row 11: all walls
	char row11[] = { '#','#','#','#','#','#','#','#','#','#','#','#' };
	for (int j = 0; j < 12; ++j) mazeData[11][j] = row11[j];
}


char &MyArray::at( int row, int col ) {
	if (row < 0 || row >= 12 || col < 0 || col >= 12) {
		throw std::out_of_range( "MyArray::at index out of range" );
	}

	return mazeData[row][col];
}


char &MyArray::getUnsafe( int row, int col ) {
	return mazeData[row][col];
}


const char &MyArray::getUnsafe( int row, int col ) const {
	return mazeData[row][col];
}


void MyArray::set( int row, int col, char value ) {
	if (row < 0 || row >= 12 || col < 0 || col >= 12) {
		throw std::out_of_range( "MyArray::set index out of range" );
	}

	mazeData[row][col] = value;
}
