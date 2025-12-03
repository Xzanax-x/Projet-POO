#pragma once

// Interface représentant l'état d'une cellule
class EtatCellule {
public:
    virtual ~EtatCellule() = default;

    // Indique si la cellule est vivante dans cet état
    virtual bool estVivante() const = 0;

    // Permet de cloner l'état (utile pour les copies de Cellule)
    virtual EtatCellule* cloner() const = 0;
};
