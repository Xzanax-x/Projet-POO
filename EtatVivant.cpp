#include "EtatVivant.hpp" // on inclut la définition de la classe

// fonction qui dit si la cellule est vivante
bool EtatVivant::estVivante() const {
    return true; // on répond oui car c'est un état vivant
}

// fonction pour créer une copie de cet état
EtatCellule* EtatVivant::cloner() const {
    return new EtatVivant(*this); // on crée un nouvel objet etatvivant identique en mémoire
}