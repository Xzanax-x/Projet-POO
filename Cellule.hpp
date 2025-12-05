#pragma once

#include "EtatCellule.hpp"

class Cellule {
private:
    int x;
    int y;
    EtatCellule* etat;

public:
    Cellule();
    Cellule(int x, int y, EtatCellule* e);
    Cellule(const Cellule& autre);
    Cellule& operator=(const Cellule& autre);
    ~Cellule();

    bool estVivante() const;

    void definirEtat(EtatCellule* e);
    EtatCellule* obtenirEtat() const;

    int obtenirX() const { return x; }
    int obtenirY() const { return y; }
};
