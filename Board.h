#include <iostream>
#include <Deque.h>

class Board {
public:
	Board();								// Default constructor
	Board(int** blocks, int N);				// Constructor from 2d array
	~Board();								// Destructor
	Board(const Board& that);				// Copy constructor
	Board& operator=(const Board& that);	// Copy assignment operator
	int dimension();
	int hamming();
	int manhattan() const;
	bool isGoal();
	Board twin();
	bool operator==(const Board &rhs) const;
	bool operator!=(const Board& rhs) const;
	friend std::ostream &operator<<(std::ostream &output, const Board& that);
	Deque<Board> neighbors();

private:
	int N_;
	int** tiles_;
	int manhattan_;

	void deleteBoard(int** board, int N);
	int** createBoard(int N);
};