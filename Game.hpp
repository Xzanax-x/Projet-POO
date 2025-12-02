#pragma once

#include <string>
#include <vector>
#include "Grid.hpp"
#include "Rule.hpp"
#include "GuiRenderer.hpp"

namespace gol {

class Game {
private:
    Grid grid;
    LifeRule rule;
    int maxIterations;

public:
    Game(int maxIter = 100);

    void loadFromFile(const std::string& path);

    void runConsoleMode(const std::string& inputFile);
    void runGuiMode();

private:
    bool isStable(const std::vector<std::vector<int>>& previous,
                  const std::vector<std::vector<int>>& current) const;
};

} // namespace gol
