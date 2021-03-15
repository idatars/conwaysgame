#include "grid.h"

Grid::~Grid() {

}

void Grid::init(size_t n) {
	data.clear();
	if (td != nullptr) delete td;
	td = new TextDisplay(n);
	size = n;
	size_t x = 0;
	size_t y = 0;
	data.resize(n);

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			data[i].emplace_back(i, j);
		}
	}
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			data[i][j].attach(td);
			if (j >= 1) data[i][j].attach(&data[i][j - 1]); // N
			if (i+1 < n && j >= 1) data[i][j].attach(&data[i+1][j-1]); // NE
			if (i+1 < n) data[i][j].attach(&data[i+1][j]); // E
			if (i+1 < n && j+1 < n) data[i][j].attach(&data[i+1][j+1]); // SE
			if (j+1 < n) data[i][j].attach(&data[i][j+1]); // S
			if (i >= 1 && j+1 < n) data[i][j].attach(&data[i-1][j+1]); // SW
			if (i >= 1) data[i][j].attach(&data[i-1][j]); // W
			if (i >= 1 && j >= 1) data[i][j].attach(&data[i-1][j-1]); // NW
		}
	}
}

void Grid::turnOn(size_t r, size_t c) {
	data[r][c].setLiving();
	data[r][c].notify();
}

void Grid::tick() {
	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j) {
			data[i][j].recalculate();
		}
	}
	for (size_t i = 0; i < size; ++i) {
		for (size_t j = 0; j < size; ++j) {
			data[i][j].notify();
		}
	}
}

std::ostream& operator<<(std::ostream& out, const Grid& g) {
	out << *g.td;
	return out;
}