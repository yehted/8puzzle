#include "Board.h"

Board::Board() : N_(0), manhattan_(0) {}

Board::Board(int** blocks, int N) : N_(N), manhattan_(0) {
	// Initialize board
	tiles_ = new int*[N];
	for (int i = 0; i < N; ++i)
		tiles_[i] = new int[N];

	// Copy elements from blocks
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			tiles_[i][j] = blocks[i][j];
	}

	// Calculate manhattan
	int cur, x, y;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
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