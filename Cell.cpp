#include "Cell.hpp"

namespace gol {

Cell::Cell(int x_, int y_, CellState* s)
    : x(x_), y(y_), state(s) {}

Cell::Cell(const Cell& other)
    : x(other.x), y(other.y), state(nullptr) {
    if (other.state) {
        state = other.state->clone();
    }
}

Cell& Cell::operator=(const Cell& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        delete state;
        state = other.state ? other.state->clone() : nullptr;
    }
    return *this;
}

Cell::~Cell() {
    delete state;
}

bool Cell::isAlive() const {
    return state && state->isAlive();
}

void Cell::setState(CellState* s) {
    delete state;
    state = s;
}

CellState* Cell::getState() const {
    return state;
}

} // namespace gol
