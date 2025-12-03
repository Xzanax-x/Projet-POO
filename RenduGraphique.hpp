#pragma once

#include <SFML/Graphics.hpp>
#include "Grille.hpp"

class RenduGraphique {
private:
    sf::RenderWindow fenetre;
    int tailleCellule;

public:
    RenduGraphique(int tailleCellule, int largeur, int hauteur);

    bool estOuverte() const;
    bool traiterEvenements();
    void afficher(const Grille& grille);
};
