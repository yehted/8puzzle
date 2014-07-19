#include "Board.h"

class Solver {
public:
	Solver();
	Solver(Board& initial);
	bool isSolvable();
	int moves();
//	Iterable<Board> solution();

private:
	class Node {
	public:
		Node();
		Node(Board &board, int moves, Node* prev);
		bool operator>(const Node& rhs);
		friend std::ostream& operator<<(std::ostream& output, const Node& that) {
			output << "Priority: " << that.priority_ << std::endl;
			output << that.board_ << std::endl;
			return output;
		}
//	private:
		int moves_;
		int priority_;
		Board board_;
		Node* prev_;
	};

	int totalmoves_;
	bool solveable_;
	Deque<Board> s;
};