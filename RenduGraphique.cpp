#include "RenduGraphique.hpp"

RenduGraphique::RenduGraphique(int taille, int largeur, int hauteur)
    : fenetre(sf::VideoMode(largeur * taille, hauteur * taille), "Jeu de la vie"),
      tailleCellule(taille) {
    // pas de limitation de framerate pour éviter les warnings sur certaines VM
}

bool RenduGraphique::estOuverte() const {
    return fenetre.isOpen();
}

bool RenduGraphique::traiterEvenements() {
    sf::Event event;
    while (fenetre.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            fenetre.close();
            return false;
        }
    }
    return true;
}

void RenduGraphique::afficher(const Grille& grille) {
    fenetre.clear();

    sf::RectangleShape formeCellule(
        sf::Vector2f(static_cast<float>(tailleCellule - 1),
                     static_cast<float>(tailleCellule - 1)));

    const auto& cellules = grille.obtenirCellules();
    int larg = grille.obtenirLargeur();
    int haut = grille.obtenirHauteur();

    for (int x = 0; x < larg; ++x) {
        for (int y = 0; y < haut; ++y) {
            if (cellules[x][y].estVivante()) {
                formeCellule.setFillColor(sf::Color(230, 180, 200));
                formeCellule.setPosition(
                    static_cast<float>(x * tailleCellule),
                    static_cast<float>(y * tailleCellule)
                );
                fenetre.draw(formeCellule);
            }
        }
    }

    fenetre.display();
}
