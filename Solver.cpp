#include "Solver.h"
#include "MinPQ.h"
#include <fstream>
#include <iostream>

// Empty constructor
Solver::Node::Node() : moves_(0), priority_(0), prev_(NULL) {}

// Default constructor from board, moves, and previous state
Solver::Node::Node(Board& board, int moves, Node* prev) : moves_(moves), prev_(prev), Board(board) {
	priority_ = moves_ + board.manhattan();
}

// Empty solver constructor
Solver::Solver() : totalmoves_(0), solveable_(false) {}

// Destructor
Solver::~Solver() {
	deleteNodes();
}

// Default solver constructor
Solver::Solver(Board& initial) : totalmoves_(-1), solveable_(false) {
	MinPQ<Node*, compare> pq;
	MinPQ<Node*, compare> twinpq;

	Board twin = initial.twin();

	Node* first = new Node(initial, 0, NULL);
	Node* firsttwin = new Node(twin, 0, NULL);

	nodes_.addLast(first);
	nodes_.addLast(firsttwin);

	pq.insert(first);
	twinpq.insert(firsttwin);

	Node* node = pq.delMin();
	Node* twinnode = twinpq.delMin();

	// Initial node check
//	std::cout << *node << std::endl;
//	std::cout << "-------------------" << std::endl;
	
	while (!node->isGoal() && !twinnode->isGoal()) {
		// Main solver
		for (Board near : node->neighbors()) {
			Node* next = new Node(near, node->moves_ + 1, node);
			nodes_.addLast(next);
			if (node->moves_ == 0 || *next != *node->prev_)
				pq.insert(next);
		}

		// Prints priority queue
//		for (MinPQ<Node*, compare>::Iterator it = pq.begin(); it != pq.end(); ++it)
//			std::cout << **it << std::endl;
//		std::cout << "---------------------" << std::endl;

		node = pq.delMin();

		// Twin solver, to check for solvability. If twin pops out first, then origina puzzle is not solvable.
		for (Board twinnear : twinnode->neighbors()) {
			Node* twinnext = new Node(twinnear, twinnode->moves_ + 1, twinnode);
			nodes_.addLast(twinnext);
			if (twinnode->moves_ == 0 || *twinnext != *twinnode->prev_)
				twinpq.insert(twinnext);
		}
		twinnode = twinpq.delMin();
	}

	if (node->isGoal()) solveable_ = true;

	totalmoves_ = node->moves_;
	solution_.addFirst(node);

	// Populates solution deque by tracing completed puzzle back to start.
	while (node->prev_ != NULL) {
		solution_.addFirst(node->prev_);
		node = node->prev_;
	}
}

bool Solver::isSolvable() { return solveable_; }

int Solver::moves() {
	if (solveable_) return totalmoves_;
	else return -1;
}

Deque<Board*> Solver::solution() {
	if (solveable_) return solution_;
	else return Deque<Board*>();
}

void Solver::deleteNodes() {
	for (Node* n : nodes_)
		delete n;
}

int SolverTest(int argc, char* argv[]) {
	using namespace std;
	ifstream inFile;
//	inFile.open("8puzzle\\puzzle04.txt");		// For debugging, preselect file
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