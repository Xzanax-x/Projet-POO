#include "Grille.hpp"
#include <fstream> // pour lire les fichiers
#include <stdexcept> // pour gérer les erreurs
#include "EtatVivant.hpp"
#include "EtatMort.hpp"
#include "Regle.hpp"

// constructeur vide : crée une grille de taille 0
Grille::Grille()
    : largeur(0), hauteur(0) {}

// constructeur avec taille : crée la grille et la remplit de cellules mortes
Grille::Grille(int larg, int haut)
    : largeur(larg), hauteur(haut),
      // crée 'larg' colonnes, et dans chaque colonne 'haut' cellules mortes en (0,0)
      cellules(larg, std::vector<Cellule>(haut, Cellule(0, 0, new EtatMort()))) {}

// constructeur de copie : crée une nouvelle grille identique à une autre
Grille::Grille(const Grille& autre)
    : largeur(autre.largeur), hauteur(autre.hauteur),
      cellules(autre.largeur, std::vector<Cellule>(autre.hauteur)) { // prépare la taille

    // parcourt toute la grille pour copier chaque cellule une par une
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            cellules[x][y] = autre.cellules[x][y]; // utilise la copie de cellule
        }
    }
}

// remplace cette grille par une autre (opérateur égal)
Grille& Grille::operator=(const Grille& autre) {
    if (this != &autre) { // vérifie qu'on ne se copie pas soi-même
        largeur = autre.largeur;
        hauteur = autre.hauteur;
        // redimensionne le tableau pour qu'il ait la même taille que l'autre
        cellules.assign(largeur, std::vector<Cellule>(hauteur));

        // boucle pour copier le contenu de chaque case
        for (int x = 0; x < largeur; ++x) {
            for (int y = 0; y < hauteur; ++y) {
                cellules[x][y] = autre.cellules[x][y];
            }
        }
    }
    return *this;
}

// charge le jeu depuis un fichier texte
void Grille::initialiserDepuisFichier(const std::string& chemin) {
    std::ifstream in(chemin); // ouvre le fichier
    if (!in) { // si le fichier n'existe pas, erreur
        throw std::runtime_error("Impossible d'ouvrir le fichier d'entree : " + chemin);
    }

    int hFichier, lFichier;
    in >> hFichier >> lFichier; // lit la hauteur et la largeur au début du fichier

    hauteur = hFichier;
    largeur = lFichier;

    cellules.clear(); // vide la grille actuelle
    cellules.resize(largeur, std::vector<Cellule>(hauteur)); // prépare la nouvelle taille

    // lit le fichier case par case
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            int v = 0;
            in >> v; // lit un chiffre (0 ou 1)
            // si 1 -> vivant, sinon -> mort
            EtatCellule* e = (v == 1)
                             ? static_cast<EtatCellule*>(new EtatVivant())
                             : static_cast<EtatCellule*>(new EtatMort());
            // place la cellule avec son nouvel état dans la grille
            cellules[x][y] = Cellule(x, y, e);
        }
    }
}

// compte combien de voisins sont vivants autour de x,y
int Grille::compterVoisinesVivantes(int x, int y) const {
    int compteur = 0;
    // double boucle pour regarder les 8 cases autour (-1 à +1)
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // on ignore la cellule elle-même

            int nx = x + dx; // coordonnée du voisin x
            int ny = y + dy; // coordonnée du voisin y
            
            // vérifie qu'on ne sort pas des limites du tableau (sécurité)
            if (nx >= 0 && nx < largeur && ny >= 0 && ny < hauteur) {
                if (cellules[nx][ny].estVivante()) {
                    ++compteur; // on ajoute 1 si le voisin est vivant
                }
            }
        }
    }
    return compteur;
}

// passe au tour suivant (le coeur du jeu)
void Grille::mettreAJour(const Regle& regle) {
    // crée une copie de la grille actuelle pour stocker le futur (double tampon)
    std::vector<std::vector<Cellule>> prochaineGrille = cellules;

    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            // calcule les voisins sur la grille ACTUELLE (pas la copie)
            int nbVoisines = compterVoisinesVivantes(x, y);
            EtatCellule* etatCourant = cellules[x][y].obtenirEtat();
            
            // demande à la règle quel sera le nouvel état
            EtatCellule* nouvelEtat = regle.calculerProchainEtat(etatCourant, nbVoisines);
            
            // applique le changement sur la COPIE
            prochaineGrille[x][y].definirEtat(nouvelEtat);
        }
    }

    // remplace la grille actuelle par la nouvelle grille calculée
    cellules.swap(prochaineGrille);
}

// donne accès aux cellules (lecture seule)
const std::vector<std::vector<Cellule>>& Grille::obtenirCellules() const {
    return cellules;
}

// convertit la grille en tableau de 0 et 1 (pour l'affichage)
std::vector<std::vector<int>> Grille::obtenirMatriceEtats() const {
    // crée un tableau d'entiers de la bonne taille
    std::vector<std::vector<int>> matrice(hauteur, std::vector<int>(largeur, 0));
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            // remplit avec 1 si vivant, 0 si mort
            matrice[y][x] = cellules[x][y].estVivante() ? 1 : 0;
        }
    }
    return matrice;
}