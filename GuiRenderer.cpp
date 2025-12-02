#include "GuiRenderer.hpp"

namespace gol {

GuiRenderer::GuiRenderer(int cs, int width, int height)
    : window(sf::VideoMode(width * cs, height * cs), "Game of Life"),
      cellSize(cs) 
{
    // Suppression de la limite de framerate :
    // window.setFramerateLimit(60);
}

bool GuiRenderer::isOpen() const {
    return window.isOpen();
}

bool GuiRenderer::pollEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return false;
        }
    }
    return true;
}

void GuiRenderer::render(const Grid& grid) {
    window.clear();

    sf::RectangleShape cellShape(
        sf::Vector2f(static_cast<float>(cellSize - 1),
                     static_cast<float>(cellSize - 1))
    );

    const auto& cells = grid.getCells();
    int width = grid.getWidth();
    int height = grid.getHeight();

    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {

            if (cells[x][y].isAlive()) {
                cellShape.setPosition(
                    static_cast<float>(x * cellSize),
                    static_cast<float>(y * cellSize)
                );
                window.draw(cellShape);
            }
        }
    }

    window.display();
}

} // namespace gol
