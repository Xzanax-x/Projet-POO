#pragma once

namespace gol {

class CellState {
public:
    virtual ~CellState() = default;
    virtual bool isAlive() const = 0;
    virtual CellState* clone() const = 0;
};

class AliveState : public CellState {
public:
    bool isAlive() const override;
    CellState* clone() const override;
};

class DeadState : public CellState {
public:
    bool isAlive() const override;
    CellState* clone() const override;
};

} // namespace gol
