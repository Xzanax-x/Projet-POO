#include "Grid.hpp"
#include <fstream>
#include <stdexcept>

namespace gol {

Grid::Grid() : width(0), height(0) {}

Grid::Grid(int w, int h)
    : width(w), height(h), cells(w, std::vector<Cell>(h, Cell(0,0, new DeadState()))) {}

Grid::Grid(const Grid& other)
    : width(other.width), height(other.height),
      cells(other.width, std::vector<Cell>(other.height, Cell(0,0,new DeadState()))) {

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            cells[x][y] = other.cells[x][y];
        }
    }
}

Grid& Grid::operator=(const Grid& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        cells.assign(width, std::vector<Cell>(height, Cell(0,0,new DeadState())));
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                cells[x][y] = other.cells[x][y];
            }
        }
    }
    return *this;
}

void Grid::initializeFromFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Impossible d'ouvrir le fichier d'entree : " + path);
    }

    int hFile, wFile;
    in >> hFile >> wFile; // format: nbLignes nbColonnes

    height = hFile;
    width = wFile;
    cells.clear();
    cells.resize(width, std::vector<Cell>(height, Cell(0,0,new DeadState())));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int v;
            in >> v;
            CellState* s = (v == 1) ? static_cast<CellState*>(new AliveState())
                                    : static_cast<CellState*>(new DeadState());
            cells[x][y] = Cell(x, y, s);
        }
    }
}

int Grid::countAliveNeighbours(int x, int y) const {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                if (cells[nx][ny].isAlive()) {
                    ++count;
                }
            }
        }
    }
    return count;
}

void Grid::update(const Rule& rule) {
    std::vector<std::vector<Cell>> nextCells = cells; // se base sur le constructeur de copie

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            int neighbours = countAliveNeighbours(x, y);
            CellState* currentState = cells[x][y].getState();
            CellState* nextState = rule.computeNext(currentState, neighbours);
            nextCells[x][y].setState(nextState);
        }
    }

    cells.swap(nextCells);
}

const std::vector<std::vector<Cell>>& Grid::getCells() const {
    return cells;
}

std::vector<std::vector<int>> Grid::getStateMatrix() const {
    std::vector<std::vector<int>> m(height, std::vector<int>(width, 0));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            m[y][x] = cells[x][y].isAlive() ? 1 : 0;
        }
    }
    return m;
}

} // namespace gol
