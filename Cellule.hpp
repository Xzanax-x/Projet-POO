#pragma once // empêche d'inclure ce fichier plusieurs fois pour éviter les bugs

#include "EtatCellule.hpp" // on a besoin de connaitre la classe etatcellule

// définition de la classe qui représente une case du jeu
class Cellule {
private: // les variables cachées que seul l'objet peut modifier
    int x; // la position horizontale de la cellule
    int y; // la position verticale de la cellule
    EtatCellule* etat; // pointeur vers l'état (mort ou vivant), c'est le cerveau de la cellule

public: // les fonctions accessibles par tout le monde (comme la grille)
    Cellule(); // constructeur vide pour créer une cellule par défaut
    Cellule(int x, int y, EtatCellule* e); // constructeur pour créer une cellule précise
    Cellule(const Cellule& autre); // constructeur de copie pour cloner une cellule
    Cellule& operator=(const Cellule& autre); // permet de remplacer une cellule par une autre avec le signe égal
    ~Cellule(); // destructeur pour nettoyer la mémoire quand l'objet disparait

    bool estVivante() const; // demande si la cellule est vivante ou morte

    void definirEtat(EtatCellule* e); // change l'état de la cellule (la tue ou la fait naitre)
    EtatCellule* obtenirEtat() const; // récupère l'état actuel pour voir ce qu'il y a dedans

    int obtenirX() const { return x; } // donne la position x
    int obtenirY() const { return y; } // donne la position y
};