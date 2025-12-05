#include "Cellule.hpp"
#include "EtatMort.hpp"
#include "EtatVivant.hpp"

// constructeur par défaut de la cellule
Cellule::Cellule()
    : x(0), y(0), // initialise les coordonnées à zéro
      etat(new EtatMort()) {} // crée un état mort par défaut

// constructeur avec des paramètres précis
Cellule::Cellule(int x_, int y_, EtatCellule* e)
    : x(x_), y(y_), // copie les coordonnées données
      etat(e) {} // affecte directement le pointeur d'état

// constructeur de copie pour dupliquer une cellule
Cellule::Cellule(const Cellule& autre)
    : x(autre.x), y(autre.y), // copie les x et y de l'autre
      etat(nullptr) { // met le pointeur à null par sécurité au début
    if (autre.etat) { // vérifie si l'autre cellule a un état
        etat = autre.etat->cloner(); // crée une copie unique de l'état en mémoire
    } else { // si l'autre n'a pas d'état
        etat = new EtatMort(); // on met un état mort par défaut
    }
}

// surcharge de l'opérateur égal pour copier une cellule existante
Cellule& Cellule::operator=(const Cellule& autre) {
    if (this != &autre) { // vérifie qu'on ne se copie pas soi-même
        x = autre.x; // copie la coordonnée x
        y = autre.y; // copie la coordonnée y
        delete etat; // supprime l'ancien état pour nettoyer la mémoire
        // si l'autre a un état on le clone, sinon on met mort
        etat = autre.etat ? autre.etat->cloner() : new EtatMort();
    }
    return *this; // retourne la cellule modifiée
}

// destructeur appelé quand la cellule disparait
Cellule::~Cellule() {
    delete etat; // libère la mémoire occupée par l'état
}

// demande si la cellule est vivante
bool Cellule::estVivante() const {
    // vérifie si l'état existe et demande à l'état s'il est vivant
    return etat && etat->estVivante();
}

// récupère le pointeur vers l'état actuel
EtatCellule* Cellule::obtenirEtat() const {
    return etat; // retourne l'adresse de l'état
}

// force un nouvel état pour la cellule
void Cellule::definirEtat(EtatCellule* e) {
    if (etat != e) { // vérifie si c'est bien un état différent
        delete etat; // supprime l'ancien état
        etat = e; // remplace par le nouveau pointeur
    }
}