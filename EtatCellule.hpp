#pragma once // évite d'inclure ce fichier deux fois pour pas faire d'erreur

// définition de l'interface qui sert de modèle pour tous les états
class EtatCellule {
public:
    // destructeur virtuel par défaut, obligatoire pour bien nettoyer la mémoire des enfants
    virtual ~EtatCellule() = default;

    // méthode abstraite (=0) qui force les classes filles à dire si elles sont vivantes
    virtual bool estVivante() const = 0;

    // méthode abstraite qui force les classes filles à savoir se recopier (cloner)
    virtual EtatCellule* cloner() const = 0;
};