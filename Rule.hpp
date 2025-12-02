#pragma once
#include "CellState.hpp"

namespace gol {

class Rule {
public:
    virtual ~Rule() = default;
    virtual CellState* computeNext(const CellState* current, int aliveNeighbours) const = 0;
};

class LifeRule : public Rule {
public:
    CellState* computeNext(const CellState* current, int aliveNeighbours) const override;
};

} // namespace gol
