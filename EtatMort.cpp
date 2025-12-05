#include "EtatMort.hpp" // on inclut la définition de la classe pour que ça marche

// fonction qui dit si la cellule est vivante
bool EtatMort::estVivante() const {
    return false; // on répond non car c'est un état mort
}

// fonction pour créer une copie de cet état
EtatCellule* EtatMort::cloner() const {
    return new EtatMort(*this); // on crée un nouvel objet etatmort identique en mémoire
}