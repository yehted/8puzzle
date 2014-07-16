#include <iostream>

class Board {
public:
	Board();
	Board(int** blocks, int N);
	int dimension();
	int hamming();
	bool isGoal();
	Board twin();
	bool operator==(const Board &rhs);
	friend std::ostream &operator<<(std::ostream &output, const Board& that);
//	Iterable<Board> neighbors();

private:
	const int N_;
	int** tiles_;
	int manhattan_;
};