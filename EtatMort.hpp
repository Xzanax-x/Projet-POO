#pragma once

#include "EtatCellule.hpp"

// Etat concret : cellule morte
class EtatMort : public EtatCellule {
public:
    bool estVivante() const override;
    EtatCellule* cloner() const override;
};
