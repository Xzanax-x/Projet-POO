#pragma once // protection pour ne pas inclure ce fichier plusieurs fois

#include <SFML/Graphics.hpp> // on inclut la librairie graphique sfml
#include "Grille.hpp" // on a besoin de connaitre la grille pour l'afficher

// classe qui gère l'affichage du jeu dans une fenêtre
class RenduGraphique {
private:
    sf::RenderWindow fenetre; // l'objet qui représente la fenêtre sur l'écran
    int tailleCellule; // la taille en pixels d'un petit carré (le zoom)

public:
    // constructeur : prépare la fenêtre en fonction de la taille de la grille
    RenduGraphique(int tailleCellule, int largeur, int hauteur);

    bool estOuverte() const; // dit si la fenêtre est encore là ou si on l'a fermée
    bool traiterEvenements(); // gère les clics de l'utilisateur (ex: croix pour fermer)
    void afficher(const Grille& grille); // fonction qui dessine les cellules vivantes à l'écran
};