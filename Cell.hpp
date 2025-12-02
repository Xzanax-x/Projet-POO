#pragma once
#include "CellState.hpp"

namespace gol {

class Cell {
private:
    int x;
    int y;
    CellState* state;

public:
    Cell(int x, int y, CellState* s);
    Cell(const Cell& other);
    Cell& operator=(const Cell& other);
    ~Cell();

    bool isAlive() const;
    void setState(CellState* s);
    CellState* getState() const;

    int getX() const { return x; }
    int getY() const { return y; }
};

} // namespace gol
