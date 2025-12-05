#pragma once

#include "Regle.hpp"

// Implémentation concrète : règles du Jeu de la vie de Conway
class RegleDeVie : public Regle {
public:
    EtatCellule* calculerProchainEtat(const EtatCellule* etatCourant,
                                      int nbVoisinesVivantes) const override;
};
