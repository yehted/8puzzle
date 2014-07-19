#include "Solver.h"
#include "MinPQ.h"
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

Solver::Node::Node(const Node& that) {

}

Solver::Node& Solver::Node::operator=(const Node& that) {
	if (this == &that) return *this;
	return *this;
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

	Deque<Board> s;

	Node* first = new Node(initial, 0, NULL);
	Node* firsttwin = new Node(twin, 0, NULL);

	pq.insert(*first);
	twinpq.insert(*firsttwin);

	Node& node = pq.delMin();
	Node &twinnode = twinpq.delMin();

	while (!node.board_.isGoal() && !twinnode.board_.isGoal()) {
		// Main solver
		for (Board near : node.board_.neighbors()) {
			Node* next = new Node(near, node.moves_ + 1, &node);
			if (node.moves_ == 0)
				pq.insert(*next);
			else {
				if (next->board_ == node.prev_->board_)
					pq.insert(*next);
			}
		}
		node = pq.delMin();

		// Twin solver
		for (Board twinnear : twinnode.board_.neighbors()) {
			Node* twinnext = new Node(twinnear, twinnode.moves_ + 1, &twinnode);
			if (twinnode.moves_ == 0)
				pq.insert(*twinnext);
			else {
				if (twinnext->board_ == twinnode.prev_->board_)
					pq.insert(*twinnext);
			}
		}
		twinnode = twinpq.delMin();
	}

	if (node.board_.isGoal()) solveable_ = true;
	else solveable_ = false;

	totalmoves_ = node.moves_;
	s.addFirst(node.board_);

	while (node.prev_ != NULL) {
		s.addFirst(node.prev_->board_);
		node = *node.prev_;
	}
}

bool Solver::isSolvable() { return solveable_; }

int Solver::moves() {
	if (solveable_) return totalmoves_;
	else return -1;
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
	//	for_each()
	}
	return 0;
}