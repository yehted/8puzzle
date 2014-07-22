#include "Solver.h"
#include "MinPQ.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Solver::Node::Node() : moves_(0), priority_(0), prev_(NULL) {}

Solver::Node::Node(Board& board, int moves, Node* prev) : moves_(moves), prev_(prev), Board(board) {
//	board_ = board;
//	Board::Board(board);
	priority_ = moves_ + board.manhattan();
}

//Solver::Node::~Node() {
//	
//}
//
//Solver::Node::Node(const Node& that) : moves_(that.moves_), priority_(that.priority_), prev_(that.prev_), board_(that.board_) {
//	
//}
//
//Solver::Node& Solver::Node::operator=(const Node& that) {
//	if (this == &that) return *this;
//	moves_ = that.moves_;
//	priority_ = that.priority_;
//	prev_ = that.prev_;
//	board_ = that.board_;
//
//
//	return *this;
//}

//bool Solver::Node::operator>(const Node& rhs) {
//	if (priority_ > rhs.priority_) return true;
//	else return false;
//}

Solver::Solver() : totalmoves_(0), solveable_(false) {}

Solver::Solver(Board& initial) {
	MinPQ<Node*, compare> pq;
//	MinPQ<Node*> twinpq;

//	Board twin = initial.twin();

	Node* first = new Node(initial, 0, NULL);
//	Node* firsttwin = new Node(twin, 0, NULL);
//	Node first(initial, 0, NULL);
//	Node firsttwin(twin, 0, NULL);

	pq.insert(first);
//	twinpq.insert(firsttwin);

	Node* node = pq.delMin();
//	Node* twinnode = twinpq.delMin();
//	std::cout << *node << std::endl;
//	std::cout << "-------------------" << std::endl;
	while (!node->isGoal() /*&& !twinnode->isGoal()*/) {
		// Main solver
		for (Board near : node->neighbors()) {
			Node* next = new Node(near, node->moves_ + 1, node);
			//Node next(near, node->moves_ + 1, node);
			if (node->moves_ == 0)
				pq.insert(next);
			else {
				if (next != node->prev_)
					pq.insert(next);
			}
		}
//		for (MinPQ<Node*, compare>::Iterator it = pq.begin(); it != pq.end(); ++it)
//			std::cout << **it << std::endl;
//		std::cout << "---------------------" << std::endl;
		node = pq.delMin();
//		std::cout << *node << std::endl;

		// Twin solver
		/*for (Board twinnear : twinnode.neighbors()) {
			Node twinnext(twinnear, twinnode.moves_ + 1, &twinnode);
			if (twinnode.moves_ == 0)
				twinpq.insert(twinnext);
			else {
				if (&twinnext != twinnode.prev_)
					twinpq.insert(twinnext);
			}
		}
		twinnode = twinpq.delMin();*/
	}

	/*if (node.isGoal()) solveable_ = true;
	else solveable_ = false;*/
	solveable_ = true;

	totalmoves_ = node->moves_;
	s.addFirst(node);

	while (node->prev_ != NULL) {
		s.addFirst(node->prev_);
		node = node->prev_;
	}
}

bool Solver::isSolvable() { return solveable_; }

int Solver::moves() {
	if (solveable_) return totalmoves_;
	else return -1;
}

Deque<Board*> Solver::solution() {
	if (solveable_) return s;
	else return Deque<Board*>();
}

int main(int argc, char* argv[]) {
	using namespace std;
	ifstream inFile;
	inFile.open("8puzzle\\puzzle04.txt");
//	inFile.open(argv[1]);
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
	return 0;
}