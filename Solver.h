#include "Board.h"
class Node;
class Solver {
	friend class compare;
public:
	Solver();
	Solver(Board& initial);
	bool isSolvable();
	int moves();
	Deque<Board*> solution();

private:	
	class Node : public Board {		
	public:		
		Node();
		Node(Board &board, int moves, Node* prev);
		/*~Node();
		Node(const Node& that);
		Node& operator=(const Node& that);*/
		friend bool operator>(const Node& lhs, const Node& rhs) {
			return lhs.priority_ > rhs.priority_;
		}
		friend std::ostream& operator<<(std::ostream& output, const Node& that) {
			output << "This: " << &that << std::endl;
			output << "Priority: " << that.priority_ << std::endl;
			output << "Moves: " << that.moves_ << std::endl;
			output << "manhattan: " << that.manhattan() << std::endl;
			output << "previous: " << that.prev_ << std::endl;
			output << static_cast<const Board&>(that) << std::endl;
			return output;
		}
//	private:
		int moves_;
		int priority_;
//		Board board_;
		Node* prev_;
	};

	int totalmoves_;
	bool solveable_;
	Deque<Board*> s;
};

class compare {
public:
	bool operator()(const Solver::Node* i, const Solver::Node* j) const {
		return (i->priority_ > j->priority_);
	}
};