#pragma once

#include "EtatCellule.hpp"

// Interface pour une règle d'évolution
class Regle {
public:
    virtual ~Regle() = default;

    // Calcule le prochain état à partir de l'état courant
    // et du nombre de voisines vivantes
    virtual EtatCellule* calculerProchainEtat(const EtatCellule* etatCourant,
    int nbVoisinesVivantes) const = 0;
};
