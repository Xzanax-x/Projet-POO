#include "CellState.hpp"

namespace gol {

bool AliveState::isAlive() const {
    return true;
}

CellState* AliveState::clone() const {
    return new AliveState(*this);
}

bool DeadState::isAlive() const {
    return false;
}

CellState* DeadState::clone() const {
    return new DeadState(*this);
}

} // namespace gol
