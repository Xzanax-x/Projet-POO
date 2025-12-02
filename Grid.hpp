#pragma once

#include <vector>
#include <string>
#include "Cell.hpp"
#include "Rule.hpp"

namespace gol {

class Grid {
private:
    int width;
    int height;
    std::vector<std::vector<Cell>> cells;

public:
    Grid();
    Grid(int w, int h);

    // construction par copie pour la console
    Grid(const Grid& other);
    Grid& operator=(const Grid& other);

    ~Grid() = default;

    void initializeFromFile(const std::string& path);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    int countAliveNeighbours(int x, int y) const;
    void update(const Rule& rule);

    const std::vector<std::vector<Cell>>& getCells() const;

    // pour détecter la stabilité
    std::vector<std::vector<int>> getStateMatrix() const;
};

} // namespace gol
