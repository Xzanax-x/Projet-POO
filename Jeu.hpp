#pragma once

#include <string>
#include <vector>
#include "Grille.hpp"
#include "Regle.hpp"
#include "RegleDeVie.hpp"
#include "RenduGraphique.hpp"

class Jeu {
private:
    Grille grille;
    RegleDeVie regle;
    int nbIterationsMax;

public:
    Jeu(int nbIter = 100);

    void chargerDepuisFichier(const std::string& chemin);

    void executerModeConsole(const std::string& fichierEntree);
    void executerModeGraphique();
    Grille& obtenirGrille();
    const Grille& obtenirGrille() const;

private:
    bool estStable(const std::vector<std::vector<int>>& precedent,
                   const std::vector<std::vector<int>>& courant) const;
};
