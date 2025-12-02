# Projet-POO
Projet POO
classDiagram
    %% --- Cellules ---
    class Cell {
        -int x
        -int y
        -CellState* state
        +Cell(int x, int y, CellState* s)
        +bool isAlive()
        +void setState(CellState* s)
        +CellState* getState()
    }

    class CellState {
        <<interface>>
        +bool isAlive()
        +CellState* nextState(int aliveNeighbours)
    }

    class AliveState {
        +bool isAlive()
        +CellState* nextState(int aliveNeighbours)
    }

    class DeadState {
        +bool isAlive()
        +CellState* nextState(int aliveNeighbours)
    }

    CellState <|-- AliveState : implémente
    CellState <|-- DeadState : implémente
    Cell --> CellState : possède

    %% --- Règles ---
    class Rule {
        <<interface>>
        +CellState computeNext(CellState* current, int aliveNeighbours)
    }

    class LifeRule {
        +CellState* computeNext(CellState* current, int aliveNeighbours)
    }

    Rule <|-- LifeRule : implémente

    %% --- Grille ---
    class Grid {
        -int width
        -int height
        -vector<vector<Cell>> cells
        +Grid(int w, int h)
        +void initializeFromFile(string path)
        +int countAliveNeighbours(int x, int y)
        +void update(Rule rule)
        +vector<vector<Cell>> getCells()
    }

    Grid --> Cell : contient
    Grid --> Rule : utilise

    %% --- Jeu ---
    class Game {
        -Grid grid
        -Rule* rule
        -int maxIterations
        +void runConsoleMode()
        +void runGuiMode()
        +bool hasEvolutionStopped()
    }

    Game --> Grid : utilise
    Game --> Rule : applique

    %% --- Interface graphique ---
    class GuiRenderer {
        -sf::RenderWindow window
        +GuiRenderer(int cellSize)
        +void render(Grid* grid)
        +bool pollEvents()
    }

    GuiRenderer --> Grid : affiche
    GuiRenderer ..> Cell : lit
