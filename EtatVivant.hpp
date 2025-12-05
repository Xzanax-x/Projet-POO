#pragma once // empêche d'inclure ce fichier plusieurs fois pour éviter les bugs

#include "EtatCellule.hpp" // on inclut le fichier du parent pour hériter

// classe concrète qui définit le comportement d'une cellule vivante
class EtatVivant : public EtatCellule { // elle hérite de l'interface etatcellule
public:
    // remplace la méthode du parent pour dire qu'on est vivant
    bool estVivante() const override;

    // remplace la méthode du parent pour créer une copie de cet état vivant
    EtatCellule* cloner() const override;
};