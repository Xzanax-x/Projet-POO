#include "RegleDeVie.hpp"
#include "EtatVivant.hpp" // nécessaire pour créer un état vivant
#include "EtatMort.hpp" // nécessaire pour créer un état mort

// implémente la logique de décision pour le jeu de la vie classique
EtatCellule* RegleDeVie::calculerProchainEtat(const EtatCellule* etatCourant,
                                              int nbVoisinesVivantes) const {
    if (etatCourant->estVivante()) { // cas 1 : si la cellule est actuellement vivante
        
        // règle de survie : il faut 2 ou 3 voisins
        if (nbVoisinesVivantes == 2 || nbVoisinesVivantes == 3) {
            return new EtatVivant(); // elle reste en vie
        } else {
            return new EtatMort(); // sinon elle meurt (isolement ou surpopulation)
        }

    } else { // cas 2 : si la cellule est actuellement morte
        
        // règle de naissance : il faut exactement 3 voisins
        if (nbVoisinesVivantes == 3) {
            return new EtatVivant(); // elle nait (reproduction)
        } else {
            return new EtatMort(); // sinon elle reste morte
        }
    }
}