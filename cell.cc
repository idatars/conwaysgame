#include "cell.h"

Cell::Cell(size_t r, size_t c) {
	info.row = r;
	info.col = c;
	info.state = State::Dead;

}

void Cell::setLiving() {
	info.state = State::Alive;
}

void Cell::reset() {
	neighbours = 0;
}

void Cell::notify() {
	notifyObservers();
}

void Cell::notify(Subject & whoNotified) {
	Info notifiedInfo = whoNotified.getInfo();
	std::vector<Info>::iterator it;
//	it = neighbourInfo.begin();
	bool found = false;
	for (auto &it : neighbourInfo) {
		if (it.row == notifiedInfo.row && it.col == notifiedInfo.col)
		{
			found = true;
			it.state = notifiedInfo.state;
		}
	}

	if (!found) neighbourInfo.emplace_back(notifiedInfo);
	
//	recalculate();
}

Info Cell::getInfo() const {
	return info;
}

void Cell::recalculate() {
	reset();
	size_t i = this->info.row;
	size_t j = this->info.col;
	for (auto& it : neighbourInfo)
	{
		if (it.state == State::Alive) neighbours++;
	}
	if (info.state == State::Alive) {
		if (neighbours < 2 || neighbours > 3) info.state = State::Dead;
	}
	else {
		if (neighbours == 3) info.state = State::Alive;
	}
}
