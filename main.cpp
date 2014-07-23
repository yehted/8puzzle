/******************************************************
* Program solves sliding 8-puzzle.
* Execution: 8puzzle <file>
* 
* Where <file> is a text file and contains the puzzle to
* be solved. It looks something like :
*
* 3
* 1  2  3
* 4  5  6
* 7  0  8
* 
* This program uses an A* algorithm to find the solution,
* using a priorty queue sorted on moves and manhattan 
* number, a sum of how far away tiles are from their
* solved position. The Solver object contains a Deque
* with a sequence of moves from the initial board to
* the finished solution.
*******************************************************/

#include "Solver.h"
#include <fstream>

int main(int argc, char* argv[]) {
	using namespace std;
	ifstream inFile;
	inFile.open(argv[1]);
	if (!inFile.is_open()) {
		cerr << "File not opened!" << endl;
		exit(1);
	}
	int N;
	inFile >> N;

	// Allocate new memory
	int** tiles = new int*[N];
	for (int i = 0; i < N; ++i)
		tiles[i] = new int[N];

	// Input elements
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			inFile >> tiles[i][j];
	}
	Board board(tiles, N);

	// Solve the puzzle
	Solver solver(board);

	// Print solution to standard output
	if (!solver.isSolvable())
		cout << "No solution possible!" << endl;
	else {
		cout << "Minimum number of moves = " << solver.moves() << endl;
		for (Board* b : solver.solution())
			std::cout << *b << std::endl;
	}

	// Garbage collection
	for (int i = 0; i < N; ++i)
		delete[] tiles[i];
	delete[] tiles;

	return 0;
}