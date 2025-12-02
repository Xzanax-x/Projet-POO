#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.hpp"

namespace gol {

class GuiRenderer {
private:
    sf::RenderWindow window;
    int cellSize;

public:
    GuiRenderer(int cellSize, int width, int height);

    bool isOpen() const;
    bool pollEvents();
    void render(const Grid& grid);
};

} // namespace gol
