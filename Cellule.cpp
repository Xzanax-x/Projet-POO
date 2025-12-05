#include "Cellule.hpp"
#include "EtatMort.hpp"
#include "EtatVivant.hpp"

Cellule::Cellule()
    : x(0), y(0), etat(new EtatMort()) {}

Cellule::Cellule(int x_, int y_, EtatCellule* e)
    : x(x_), y(y_), etat(e) {}

Cellule::Cellule(const Cellule& autre)
    : x(autre.x), y(autre.y), etat(nullptr) {
    if (autre.etat) {
        etat = autre.etat->cloner();
    } else {
        etat = new EtatMort();
    }
}

Cellule& Cellule::operator=(const Cellule& autre) {
    if (this != &autre) {
        x = autre.x;
        y = autre.y;
        delete etat;
        etat = autre.etat ? autre.etat->cloner() : new EtatMort();
    }
    return *this;
}

Cellule::~Cellule() {
    delete etat;
}

bool Cellule::estVivante() const {
    return etat && etat->estVivante();
}

EtatCellule* Cellule::obtenirEtat() const {
    return etat;
}

void Cellule::definirEtat(EtatCellule* e) {
    if (etat != e) {
        delete etat;
        etat = e;
    }
}
