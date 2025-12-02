#include "Game.hpp"
#include <fstream>
#include <SFML/System.hpp>
#include <cstdlib>  // pour system()

namespace gol {

Game::Game(int maxIter)
    : grid(), rule(), maxIterations(maxIter) {}

void Game::loadFromFile(const std::string& path) {
    grid.initializeFromFile(path);
}

bool Game::isStable(const std::vector<std::vector<int>>& previous,
                    const std::vector<std::vector<int>>& current) const {
    return previous == current;
}

void Game::runConsoleMode(const std::string& inputFile) {
    // Création du dossier en utilisant system() (compatible partout)
    std::string outDir = inputFile + "_out";
    std::string mkdirCmd = "mkdir -p " + outDir;
    system(mkdirCmd.c_str());

    std::vector<std::vector<int>> previous = grid.getStateMatrix();

    for (int iter = 0; iter < maxIterations; ++iter) {
        // Fichier de sortie
        std::string filename = outDir + "/iter_" + std::to_string(iter) + ".txt";
        std::ofstream out(filename);
        out << grid.getHeight() << " " << grid.getWidth() << "\n";

        const auto& cells = grid.getCells();
        for (int y = 0; y < grid.getHeight(); ++y) {
            for (int x = 0; x < grid.getWidth(); ++x) {
                out << (cells[x][y].isAlive() ? 1 : 0) << " ";
            }
            out << "\n";
        }

        // Mise à jour de la grille
        grid.update(rule);
        auto current = grid.getStateMatrix();

        if (isStable(previous, current)) {
            break;  // l'automate n'évolue plus
        }

        previous = current;
    }
}

void Game::runGuiMode() {
    // 40 pixels par cellule : fenêtre plus grande
    GuiRenderer gui(40, grid.getWidth(), grid.getHeight());

    std::vector<std::vector<int>> previous = grid.getStateMatrix();
    int iter = 0;
    bool stopEvolution = false;

    const int DELAY_MS =400;  // délai entre deux affichages (plus petit = plus rapide)

    // On reste tant que la fenêtre est ouverte
    while (gui.isOpen()) {
        if (!gui.pollEvents()) break;   // fermeture par la croix

        if (!stopEvolution && iter < maxIterations) {
            // Afficher l'état courant
            gui.render(grid);
            sf::sleep(sf::milliseconds(DELAY_MS));

            // Calculer l'état suivant
            grid.update(rule);
            auto current = grid.getStateMatrix();

            // Si la grille devient stable, on fige l'automate
            if (isStable(previous, current)) {
                stopEvolution = true;
            }

            previous = current;
            ++iter;
        } else {
            // Automate figé ou max itérations atteint : on continue juste à afficher
            gui.render(grid);
            sf::sleep(sf::milliseconds(DELAY_MS));
        }
    }
}

} // namespace gol
