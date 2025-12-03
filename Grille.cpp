#include "Grille.hpp"
#include <fstream>
#include <stdexcept>
#include "EtatVivant.hpp"
#include "EtatMort.hpp"
#include "Regle.hpp"


Grille::Grille()
    : largeur(0), hauteur(0) {}

Grille::Grille(int larg, int haut)
    : largeur(larg), hauteur(haut),
      cellules(larg, std::vector<Cellule>(haut, Cellule(0, 0, new EtatMort()))) {}

Grille::Grille(const Grille& autre)
    : largeur(autre.largeur), hauteur(autre.hauteur),
      cellules(autre.largeur, std::vector<Cellule>(autre.hauteur)) {

    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            cellules[x][y] = autre.cellules[x][y];
        }
    }
}

Grille& Grille::operator=(const Grille& autre) {
    if (this != &autre) {
        largeur = autre.largeur;
        hauteur = autre.hauteur;
        cellules.assign(largeur, std::vector<Cellule>(hauteur));

        for (int x = 0; x < largeur; ++x) {
            for (int y = 0; y < hauteur; ++y) {
                cellules[x][y] = autre.cellules[x][y];
            }
        }
    }
    return *this;
}

void Grille::initialiserDepuisFichier(const std::string& chemin) {
    std::ifstream in(chemin);
    if (!in) {
        throw std::runtime_error("Impossible d'ouvrir le fichier d'entree : " + chemin);
    }

    int hFichier, lFichier;
    in >> hFichier >> lFichier;

    hauteur = hFichier;
    largeur = lFichier;

    cellules.clear();
    cellules.resize(largeur, std::vector<Cellule>(hauteur));

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            int v = 0;
            in >> v;
            EtatCellule* e = (v == 1)
                             ? static_cast<EtatCellule*>(new EtatVivant())
                             : static_cast<EtatCellule*>(new EtatMort());
            cellules[x][y] = Cellule(x, y, e);
        }
    }
}

int Grille::compterVoisinesVivantes(int x, int y) const {
    int compteur = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < largeur && ny >= 0 && ny < hauteur) {
                if (cellules[nx][ny].estVivante()) {
                    ++compteur;
                }
            }
        }
    }
    return compteur;
}

void Grille::mettreAJour(const Regle& regle) {
    std::vector<std::vector<Cellule>> prochaineGrille = cellules;

    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < hauteur; ++y) {
            int nbVoisines = compterVoisinesVivantes(x, y);
            EtatCellule* etatCourant = cellules[x][y].obtenirEtat();
            EtatCellule* nouvelEtat = regle.calculerProchainEtat(etatCourant, nbVoisines);
            prochaineGrille[x][y].definirEtat(nouvelEtat);
        }
    }

    cellules.swap(prochaineGrille);
}

const std::vector<std::vector<Cellule>>& Grille::obtenirCellules() const {
    return cellules;
}

std::vector<std::vector<int>> Grille::obtenirMatriceEtats() const {
    std::vector<std::vector<int>> matrice(hauteur, std::vector<int>(largeur, 0));
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            matrice[y][x] = cellules[x][y].estVivante() ? 1 : 0;
        }
    }
    return matrice;
}
