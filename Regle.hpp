#pragma once // protection pour ne pas inclure ce fichier plusieurs fois

#include "EtatCellule.hpp" // on a besoin de connaitre les états possibles (vivant/mort)

// interface (modèle) qui sert à définir n'importe quelle règle du jeu
class Regle {
public:
    // destructeur virtuel obligatoire pour les interfaces
    virtual ~Regle() = default;

    // méthode abstraite (=0) : c'est l'arbitre qui décide du futur de la cellule
    // elle prend l'état actuel et le nombre de voisins, et renvoie le nouvel état
    virtual EtatCellule* calculerProchainEtat(const EtatCellule* etatCourant,
                                              int nbVoisinesVivantes) const = 0;
};