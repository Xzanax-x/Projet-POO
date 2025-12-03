#include <iostream>
#include <string>
#include "Jeu.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage : " << argv[0]
                  << " <fichier_entree> <mode> [nbIterations]\n";
        std::cerr << "mode = console | gui\n";
        return 1;
    }

    std::string fichierEntree = argv[1];
    std::string mode = argv[2];
    int nbIter = 100;

    if (argc >= 4) {
        nbIter = std::stoi(argv[3]);
    }

    try {
        Jeu jeu(nbIter);
        jeu.chargerDepuisFichier(fichierEntree);

        if (mode == "console") {
            jeu.executerModeConsole(fichierEntree);
        } else if (mode == "gui") {
            jeu.executerModeGraphique();
        } else {
            std::cerr << "Mode inconnu : " << mode
                      << " (utiliser console ou gui)\n";
            return 1;
        }

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
        return 1;
    }

    return 0;
}
