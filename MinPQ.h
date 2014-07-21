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

#include <assert.h>
#include <stdexcept>

template <class T>
class MinPQ {
public:
	class Iterator;

	// Initializes empty priority queue
	MinPQ() : N_(0), cap_(2) {
		pq_ = new T[2];
	}

	// Destructor
	~MinPQ() { delete[] pq_; }

	// Copy constructor
	MinPQ(const MinPQ& that);

	// Copy assignment operator
	MinPQ& operator=(const MinPQ& that);

	// Initializes a priorty queue with the given initial capacity
	MinPQ(int initCapacity) : N_(0), cap_(initCapacity) {
		pq_ = new T[initCapacity + 1];
	}

	// Initializes a priority queue from an array of keys
	MinPQ(T* keys, int N) : N_(N), cap_(N + 1) {
		pq_ = new T[N + 1];
		for (int i = 0; i < N; i++)
			pq_[i + 1] = keys[i];
		for (int k = N / 2; k >= 1; k--)
			sink(k);
		assert(isMinHeap());
	}

	// Is the priority queue empty?
	bool isEmpty() { return N_ == 0; }

	// Returns the number of keys on the priority queue
	int size() { return N_; }

	// Returns the smallest key on the priority queue
	T min() {
		if (isEmpty()) throw std::out_of_range("Priority queue underflow");
		return pq_[1];
	}

	// Adds a new key to the priority queue
	void insert(T& x) {
		// double size of array if necessary
		if (N_ == cap_ - 1) resize(2 * cap_);
		
		// add x, and percolate it up to maintain heap invariant		
		pq_[++N_] = x;
		swim(N_);
		assert(isMinHeap());
	}

	// Removes and returns smallest key on the priority queue
	T delMin() {
		if (isEmpty()) throw std::out_of_range("Priority queue underflow");
		exch(1, N_);
		T min = pq_[N_--];
		sink(1);
//		pq_[N_ + 1] = NULL; // Can't be done in C++
		if ((N_ > 0) && (N_ == (cap_ - 1) / 4)) resize(cap_ / 2);
		assert(isMinHeap());
		return min;
	}

	Iterator begin() { return Iterator(pq_ + 1); }
	Iterator end() { return Iterator(pq_ + N_ + 1); }

	class Iterator : public std::iterator <std::forward_iterator_tag, T> {
	public:
		Iterator() : ptr_(NULL) {}
		~Iterator() {}
		Iterator(T* p) : ptr_(p) {}
		Iterator(const Iterator& other) : ptr_(other.ptr_) {}
		Iterator& operator=(const Iterator& other) { ptr_ = other.ptr_; }

		Iterator& operator++() { ++ptr_; return *this; }
		Iterator operator++(int) { int* prev = ptr_; ptr_++; return Iterator(prev); }
		bool operator==(const Iterator& other) { return ptr_ == other.ptr_; }
		bool operator!=(const Iterator& other) { return !(ptr_ == other.ptr_); }

		T& operator*() { return *ptr_; }
		T* operator->() { return ptr_; }

	private:
		T* ptr_;
	};

private:
	T* pq_;		// stores items at indices 1 to N
	int N_;		// number of items on priority queue
	int cap_;	// capacity of the priority queue array

	// Helper function to change the size of the heap array
	void resize(int capacity) {
		assert(cap_ > N_);
		T* tmp = new T[capacity];
		for (int i = 1; i <= N_; i++)
			tmp[i] = pq_[i];
//		delete pq_;
		pq_ = tmp;
		cap_ = capacity;
	}

	/***********************************************************
	* Helper functions to maintain heap invariant
	************************************************************/
	void swim(int k) {
		while (k > 1 && greater(k / 2, k)) {
			exch(k, k / 2);
			k = k / 2;
		}
	}

	void sink(int k) {
		while (2 * k <= N_) {
			int j = 2 * k;
			if (j < N_ && greater(j, j + 1)) j++;
			if (!greater(k, j)) break;
			k = j;
		}
	}

	/***********************************************************
	* Helper functions for compares and swaps
	************************************************************/
	bool greater(int i, int j) {
		return (pq_[i] > pq_[j]);
	}

	void exch(int i, int j) {
		T swap = pq_[i];
		pq_[i] = pq_[j];
		pq_[j] = swap;
	}

	bool isMinHeap() { return (isMinHeap(1)); }

	bool isMinHeap(int k) {
		if (k > N_) return true;
		int left = 2 * k, right = 2 * k + 1;
		if (left <= N_ && greater(k, left)) return false;
		if (right <= N_ && greater(k, right)) return false;
		return (isMinHeap(left) && isMinHeap(right));
	}
};