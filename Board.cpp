#include "Board.h"
//#include <vld.h>

Board::Board() : N_(0), manhattan_(0) {}

Board::Board(int** blocks, int N) : N_(N), manhattan_(0) {
	tiles_ = createBoard(N);

	int cur, x, y;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tiles_[i][j] = blocks[i][j];	// Copies number at (i, j)
			// Calculates manhattan
			if (tiles_[i][j] == 0) continue;
			if (tiles_[i][j] != N * i + j + 1) {
				cur = tiles_[i][j];
				y = (cur - 1) % N;
				x = (cur - y - 1) / N;
				manhattan_ += (abs(x - i) + abs(y - j));
			}
		}
	}
}

Board::~Board() {
	deleteBoard(tiles_, N_);
}

Board::Board(const Board& that) : N_(that.N_), manhattan_(that.manhattan_) {
	tiles_ = createBoard(that.N_);

	for (int i = 0; i < N_; i++) {
		for (int j = 0; j < N_; j++)
			tiles_[i][j] = that.tiles_[i][j];
	}
}

Board& Board::operator=(const Board& that) {
	if (this == &that) return *this;

	// Free memory
	deleteBoard(tiles_, N_);

	// Allocate new memory
	int** newtiles = createBoard(that.N_);

	// Copy elements
	for (int i = 0; i < that.N_; i++) {
		for (int j = 0; j < that.N_; j++)
			newtiles[i][j] = that.tiles_[i][j];
	}

	// Assign variables
	tiles_ = newtiles;
	manhattan_ = that.manhattan_;
	N_ = that.N_;

	return *this;
}

int Board::dimension() { return N_; }

int Board::hamming() {
	int count = 0;
	for (int i = 0; i < N_; i++) {
		for (int j = 0; j < N_; j++) {
			if (tiles_[i][j] == 0) continue;
			if (tiles_[i][j] != N_ * i + j + 1) count++;
		}
	}
	return count;
}

int Board::manhattan() const { return manhattan_; }

bool Board::isGoal() { return manhattan_ == 0; }

Board Board::twin() {
	Board twin(tiles_, N_);
	int i = 0;
	if (twin.tiles_[i][0] == 0 || twin.tiles_[i][1] == 0) i = 1;	// Moves to the next row if a tile to be swapped is 0
	// Swap tiles
	int tmp = twin.tiles_[i][0];
	twin.tiles_[i][0] = twin.tiles_[i][1];
	twin.tiles_[i][1] = tmp;
	return twin;
}

bool Board::operator==(const Board& rhs) {
	if (&rhs == this) return true;
	if (&rhs == NULL) return false;
	if (N_ != rhs.N_) return false;
	for (int i = 0; i < N_; i++) {
		for (int j = 0; j < N_; j++)
			if (tiles_[i][j] != rhs.tiles_[i][j]) return false;
	}
	return true;
}

bool Board::operator!=(const Board& rhs) {
	return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& output, const Board& that) {
	output << that.N_ << std::endl;
	for (int i = 0; i < that.N_; i++) {
		for (int j = 0; j < that.N_; j++) {
			output.width(2);
			output << that.tiles_[i][j] << " ";
		}
		output << std::endl;
	}
	return output;
}

Deque<Board> Board::neighbors() {
	Deque<Board> s;
	int** copy = createBoard(N_);

	int x = 0, y = 0;
	// Copy board and find blanks
	for (int i = 0; i < N_; i++) {
		for (int j = 0; j < N_; j++) {
			copy[i][j] = tiles_[i][j];
			if (tiles_[i][j] == 0) {
				x = i;
				y = j;
			}
		}
	}

	// swap left
	if (x > 0) {
		copy[x][y] = copy[x - 1][y];
		copy[x - 1][y] = 0;
		s.addFirst(Board(copy, N_));
		copy[x - 1][y] = copy[x][y];
		copy[x][y] = 0;
	}

	// swap right
	if (x < N_ - 1) {
		copy[x][y] = copy[x + 1][y];
		copy[x + 1][y] = 0;
		s.addFirst(Board(copy, N_));
		copy[x + 1][y] = copy[x][y];
		copy[x][y] = 0;
	}

	// swap up
	if (y > 0) {
		copy[x][y] = copy[x][y - 1];
		copy[x][y - 1] = 0;
		s.addFirst(Board(copy, N_));
		copy[x][y - 1] = copy[x][y];
		copy[x][y] = 0;
	}

	// swap down
	if (y < N_ - 1) {
		copy[x][y] = copy[x][y + 1];
		copy[x][y + 1] = 0;
		s.addFirst(Board(copy, N_));
		copy[x][y + 1] = copy[x][y];
		copy[x][y] = 0;
	}

	deleteBoard(copy, N_);

	return s;
}

void Board::deleteBoard(int** board, int N) {
	if (N == 0) return;
	for (int i = 0; i < N; ++i)
		delete[] board[i];
	delete[] board;
}

int** Board::createBoard(int N) {
	int** tiles = new int*[N];
	for (int i = 0; i < N; ++i)
		tiles[i] = new int[N];
	return tiles;
}

int test(int argc, char* argv[]){
	int N = 3;
	int** board = new int*[N];
	for (int i = 0; i < N; ++i)
		board[i] = new int[N];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			board[i][j] = N * i + j + 1;
	}
	board[N - 1][N - 1] = 0;
	Board testboard(board, N);
	std::cout << testboard;
	std::cout << "Manhattan: " << testboard.manhattan() << std::endl;
	return 0;
}