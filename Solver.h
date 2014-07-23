#include "Board.h"

class Solver {
	friend class compare;
public:
	Solver();						// Empty constructor
	~Solver();						// Destructor, deletes all nodes created by neighbor()
	Solver(Board& initial);			// Default constructor from initial board
	bool isSolvable();				// Returns whether board is solvable
	int moves();					// Returns minimum number of moves to solve puzzle
	Deque<Board*> solution();		// Deque containing sequence of moves for solution

private:	
	class Node : public Board {		
	public:		
		Node();
		Node(Board &board, int moves, Node* prev);
		friend std::ostream& operator<<(std::ostream& output, const Node& that)	{
			output << "This: " << &that << std::endl;
			output << "Priority: " << that.priority_ << std::endl;
			output << "Moves: " << that.moves_ << std::endl;
			output << "manhattan: " << that.manhattan() << std::endl;
			output << "previous: " << that.prev_ << std::endl;
			const Board* b = &that;		// Upcast to print board
			output << *b;
			return output;
		}
	
		int moves_;				// Moves so far
		int priority_;			// Moves + manhattan
		Node* prev_;			// Pointer to previous node before swap
	};

	int totalmoves_;			// Total moves to solution
	bool solveable_;			// Whether the board is solveable
	Deque<Board*> solution_;	// Deque containing sequence of moves to solution
	Deque<Node*> nodes_;		// Deque of all the created nodes, for easier garbage collection

	void deleteNodes();			// Helper function to clean up memory
};

class compare {		// Custom comparator for Node pointers
public:
	bool operator()(const Solver::Node* i, const Solver::Node* j) const {
		return (i->priority_ > j->priority_);
	}
};