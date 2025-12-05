#pragma once // protection pour ne pas inclure ce fichier plusieurs fois

#include "EtatCellule.hpp" // on inclut le fichier du parent pour hériter

// classe concrète qui définit le comportement d'une cellule morte
class EtatMort : public EtatCellule { // elle hérite de l'interface etatcellule
public:
    // remplace la méthode du parent pour dire qu'on n'est pas vivant
    bool estVivante() const override;

    // remplace la méthode du parent pour créer une copie de cet état mort
    EtatCellule* cloner() const override;
};