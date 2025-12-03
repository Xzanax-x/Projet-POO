#include "RegleDeVie.hpp"
#include "EtatVivant.hpp"
#include "EtatMort.hpp"

// Règles de Conway :
// - cellule vivante : survit si 2 ou 3 voisines vivantes
// - cellule morte   : naît si exactement 3 voisines vivantes
EtatCellule* RegleDeVie::calculerProchainEtat(const EtatCellule* etatCourant,
                                              int nbVoisinesVivantes) const {
    if (etatCourant->estVivante()) {
        // Survie
        if (nbVoisinesVivantes == 2 || nbVoisinesVivantes == 3) {
            return new EtatVivant();
        } else {
            return new EtatMort();
        }
    } else {
        // Naissance
        if (nbVoisinesVivantes == 3) {
            return new EtatVivant();
        } else {
            return new EtatMort();
        }
    }
}
