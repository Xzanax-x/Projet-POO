#include "Jeu.hpp"
#include <fstream>
#include <SFML/System.hpp>
#include <cstdlib>  // system()

Jeu::Jeu(int nbIter)
    : grille(), regle(), nbIterationsMax(nbIter) {}

void Jeu::chargerDepuisFichier(const std::string& chemin) {
    grille.initialiserDepuisFichier(chemin);
}

bool Jeu::estStable(const std::vector<std::vector<int>>& precedent,
                    const std::vector<std::vector<int>>& courant) const {
    return precedent == courant;
}

void Jeu::executerModeConsole(const std::string& fichierEntree) {
    std::string dossierSortie = fichierEntree + "_out";
    std::string commandeMkdir = "mkdir -p " + dossierSortie;
    system(commandeMkdir.c_str());

    std::vector<std::vector<int>> precedent = grille.obtenirMatriceEtats();

    for (int iter = 0; iter < nbIterationsMax; ++iter) {
        std::string nomFichier = dossierSortie + "/iter_" + std::to_string(iter) + ".txt";
        std::ofstream out(nomFichier);
        out << grille.obtenirHauteur() << " " << grille.obtenirLargeur() << "\n";

        const auto& cellules = grille.obtenirCellules();
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            for (int x = 0; x < grille.obtenirLargeur(); ++x) {
                out << (cellules[x][y].estVivante() ? 1 : 0) << " ";
            }
            out << "\n";
        }

        grille.mettreAJour(regle);
        auto courant = grille.obtenirMatriceEtats();

        if (estStable(precedent, courant)) {
            break;
        }

        precedent = courant;
    }
}

void Jeu::executerModeGraphique() {
    RenduGraphique rendu(150, grille.obtenirLargeur(), grille.obtenirHauteur());

    std::vector<std::vector<int>> precedent = grille.obtenirMatriceEtats();
    int iter = 0;
    bool evolutionTerminee = false;
    const int DELAI_MS = 300;

    while (rendu.estOuverte()) {
        if (!rendu.traiterEvenements()) break;

        if (!evolutionTerminee && iter < nbIterationsMax) {
            rendu.afficher(grille);
            sf::sleep(sf::milliseconds(DELAI_MS));

            grille.mettreAJour(regle);
            auto courant = grille.obtenirMatriceEtats();

            if (estStable(precedent, courant)) {
                evolutionTerminee = true;
            }

            precedent = courant;
            ++iter;
        } else {
            rendu.afficher(grille);
            sf::sleep(sf::milliseconds(DELAI_MS));
        }
    }
}
