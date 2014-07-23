#include <iostream>
#include <Deque.h>

class Board {
public:
	Board();								// Default constructor
	Board(int** blocks, int N);				// Constructor from 2d array
	~Board();								// Destructor
	Board(const Board& that);				// Copy constructor
	Board& operator=(const Board& that);	// Copy assignment operator
	bool operator==(const Board &rhs) const;
	bool operator!=(const Board& rhs) const;
	friend std::ostream &operator<<(std::ostream &output, const Board& that);

	int dimension();						// Returns board dimension, N
	int hamming();							// Returns Hamming distance, based on number of misplaced tiles
	int manhattan() const;					// Returns manhattan distance
	bool isGoal();							// Returns whether the board is in solved position
	Board twin();							// Generates twin board with two non-zero tiles swapped
	Deque<Board> neighbors();				// Returns deque of possible boards after next legal move

private:
	int N_;									// Dimension of board
	int** tiles_;							// 2D array containing board numbers
	int manhattan_;							// Cached manhattan number of board

	void deleteBoard(int** board, int N);	// Helper function for deleting 2D arrays
	int** createBoard(int N);				// Helper function for creating 2D arrays
};