#include "RenduGraphique.hpp"

// constructeur : ouvre la fenêtre graphique avec la bonne taille
RenduGraphique::RenduGraphique(int taille, int largeur, int hauteur)
    // calcule la taille totale de la fenêtre en pixels (nb cases * taille d'une case)
    : fenetre(sf::VideoMode(largeur * taille, hauteur * taille), "Jeu de la vie"),
      tailleCellule(taille) { // mémorise la taille d'une case (zoom)
    // la fenêtre est maintenant ouverte et prête
}

// demande à la bibliothèque sfml si la fenêtre est toujours là
bool RenduGraphique::estOuverte() const {
    return fenetre.isOpen();
}

// gère les actions de l'utilisateur (clics, clavier)
bool RenduGraphique::traiterEvenements() {
    sf::Event event;
    // regarde s'il y a des évènements en attente (clic sur la croix, etc.)
    while (fenetre.pollEvent(event)) {
        // si l'événement est "clic sur fermer la fenêtre"
        if (event.type == sf::Event::Closed) {
            fenetre.close(); // ferme la fenêtre proprement
            return false; // signale au jeu qu'il faut s'arrêter
        }
    }
    return true; // tout va bien, on continue
}

// fonction principale qui dessine toute la grille à chaque tour
void RenduGraphique::afficher(const Grille& grille) {
    fenetre.clear(); // efface tout ce qu'il y avait avant (fond noir par défaut)

    // prépare la forme géométrique d'une cellule (un carré)
    // on fait -1 pour laisser un petit espace (bordure) entre les cellules
    sf::RectangleShape formeCellule(
        sf::Vector2f(static_cast<float>(tailleCellule - 1),
                     static_cast<float>(tailleCellule - 1)));

    // récupère les infos de la grille pour savoir quoi dessiner
    const auto& cellules = grille.obtenirCellules();
    int larg = grille.obtenirLargeur();
    int haut = grille.obtenirHauteur();

    // parcourt toutes les coordonnées de la grille
    for (int x = 0; x < larg; ++x) {
        for (int y = 0; y < haut; ++y) {
            // on ne dessine que si la cellule est vivante
            if (cellules[x][y].estVivante()) {
                // définit la couleur de la cellule (ici un rose pâle)
                formeCellule.setFillColor(sf::Color(230, 180, 200));
                
                // calcule la position du carré en pixels sur l'écran
                formeCellule.setPosition(
                    static_cast<float>(x * tailleCellule),
                    static_cast<float>(y * tailleCellule)
                );
                
                // dessine le carré dans la mémoire tampon (pas encore visible)
                fenetre.draw(formeCellule);
            }
        }
    }

    // affiche réellement à l'écran tout ce qu'on vient de préparer
    fenetre.display();
}