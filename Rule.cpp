#include "Rule.hpp"

namespace gol {

CellState* LifeRule::computeNext(const CellState* current, int aliveNeighbours) const {
    // Règles classiques de Conway :
    // - cellule vivante : survit si 2 ou 3 voisins
    // - cellule morte   : naît si 3 voisins
    if (current->isAlive()) {
        if (aliveNeighbours == 2 || aliveNeighbours == 3) {
            return new AliveState();
        } else {
            return new DeadState();
        }
    } else {
        if (aliveNeighbours == 3) {
            return new AliveState();
        } else {
            return new DeadState();
        }
    }
}

} // namespace gol
