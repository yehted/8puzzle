#include <iostream>
#include <Deque.h>

class Board {
public:
	Board();
	Board(int** blocks, int N);
	~Board();
	Board(const Board& that);
	Board& operator=(const Board& that);
	int dimension();
	int hamming();
	int manhattan();
	bool isGoal();
	Board twin();
	bool operator==(const Board &rhs);
	friend std::ostream &operator<<(std::ostream &output, const Board& that);
	Deque<Board> neighbors();

private:
	int N_;
	int** tiles_;
	int manhattan_;

	void deleteBoard(int** board, int N);
	int** createBoard(int N);
};