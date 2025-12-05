#pragma once // protection pour ne pas inclure ce fichier plusieurs fois

#include "Regle.hpp" // on inclut le fichier parent pour hériter

// classe concrète qui contient les règles officielles du jeu de conway
class RegleDeVie : public Regle { // elle hérite de l'interface regle
public:
    // remplace la méthode du parent pour appliquer la logique (2 ou 3 voisins = vie, etc.)
    EtatCellule* calculerProchainEtat(const EtatCellule* etatCourant,
                                      int nbVoisinesVivantes) const override;
};