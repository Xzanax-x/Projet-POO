#include "EtatVivant.hpp"

bool EtatVivant::estVivante() const {
    return true;
}

EtatCellule* EtatVivant::cloner() const {
    return new EtatVivant(*this);
}
