/* The MinPQ class represents a priority queue of generic keys.
It supports the usual insert and delete-the-minimum
operations, along with methods for peeking at the mininum key,
testing if the priority queue is empty, and iterating through
the keys.

This Implimentation uses a binary heap. 
The insert and delete-the-mininum operations take
logarithmic amortized time.
The min, size, and is-empty operations take constant time.
Construction takes time proportional to the specified capacity or the number of
items used to initialize the data structure.

For additional informaton, see Section 2.4 of Algorithms, 4th Edition, by Robert
Sedgewick and Kevin Wayne.*/

template <class T>
class MinPQ {
public:
	MinPQ();
	MinPQ(int initCapacity);


private:
	T* pq;		// stores items at indices 1 to N
	int N;		// number of items on priority queue

};
