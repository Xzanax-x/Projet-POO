#include "EtatMort.hpp"

bool EtatMort::estVivante() const {
    return false;
}

EtatCellule* EtatMort::cloner() const {
    return new EtatMort(*this);
}
