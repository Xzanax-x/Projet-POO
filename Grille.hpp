#pragma once

#include <vector>
#include <string>
#include "Cellule.hpp"
#include "Regle.hpp"

class Grille {
private:
    int largeur;
    int hauteur;
    std::vector<std::vector<Cellule>> cellules;

public:
    Grille();
    Grille(int larg, int haut);
    Grille(const Grille& autre);
    Grille& operator=(const Grille& autre);
    ~Grille() = default;

    void initialiserDepuisFichier(const std::string& chemin);

    int obtenirLargeur() const { return largeur; }
    int obtenirHauteur() const { return hauteur; }

    int compterVoisinesVivantes(int x, int y) const;
    void mettreAJour(const Regle& regle);

    const std::vector<std::vector<Cellule>>& obtenirCellules() const;

    std::vector<std::vector<int>> obtenirMatriceEtats() const;
};
