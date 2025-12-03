#pragma once

#include "EtatCellule.hpp"

// Etat concret : cellule vivante
class EtatVivant : public EtatCellule {
public:
    bool estVivante() const override;
    EtatCellule* cloner() const override;
};
