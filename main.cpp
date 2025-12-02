#include <iostream>
#include <string>
#include "Game.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage : " << argv[0]
                  << " <fichier_entree> <mode> [maxIterations]\n";
        std::cerr << "mode = console | gui\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string mode = argv[2];
    int maxIter = 100;

    if (argc >= 4) {
        maxIter = std::stoi(argv[3]);
    }

    try {
        gol::Game game(maxIter);
        game.loadFromFile(inputFile);

        if (mode == "console") {
            game.runConsoleMode(inputFile);
        } else if (mode == "gui") {
            game.runGuiMode();
        } else {
            std::cerr << "Mode inconnu : " << mode << " (utiliser console ou gui)\n";
            return 1;
        }
    } catch (const std::exception& ex) {
        std::cerr << "Erreur : " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
