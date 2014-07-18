#include "Solver.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Solver::Node::Node() : moves_(0), priority_(0), prev_(NULL) {}

Solver::Node::Node(Board& board, int moves, Node* prev) : moves_(moves), prev_(prev) {
	board_ = board;
	priority_ = moves_ + board.manhattan();
}

Solver::Node::~Node() {
	
}

bool Solver::Node::operator>(const Node& rhs) {
	if (priority_ > rhs.priority_) return true;
	else return false;
}

Solver::Solver() : totalmoves_(0), solveable_(false) {}

Solver::Solver(Board& initial) {
	MinPQ<Node> pq;
	MinPQ<Node> twinpq;

	Board twin = initial.twin();
	std::stack<Board> s;

	Node first(initial, 0, NULL);
	pq.insert(first);

	Node node = pq.delMin();

}

bool Solver::isSolvable() { return solveable_; }

int Solver::moves() {
	if (solveable_) return totalmoves_;
	else return -1;
}

int test(int argc, char* argv[]) {
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
	//	for_each()
	}
	return 0;
}