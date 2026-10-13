#ifndef MYARRAY_H
#define MYARRAY_H

// MyArray class containing the hardcoded maze. This is the 12x12 grid that
// the solver will navigate. '#' is a wall, '.' is an open path, 'X' marks
// cells that have been visited by the solver.
class MyArray {
private:
	char mazeData[12][12];

public:
	MyArray();

	// Get element at [row][col]. Bounds-checked; throws if out of range.
	char &at( int row, int col );

	// Get element without bounds checking (faster, but caller responsible).
	// Provides both const and non-const overloads.
	char &getUnsafe( int row, int col );
	const char &getUnsafe( int row, int col ) const;

	// Set element at [row][col] to value. Bounds-checked.
	void set( int row, int col, char value );
};

#endif // MYARRAY_H
