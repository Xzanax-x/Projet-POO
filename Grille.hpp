#pragma once // empêche d'inclure ce fichier plusieurs fois pour éviter les bugs

#include <vector> // bibliothèque pour faire des tableaux dynamiques
#include <string> // bibliothèque pour gérer du texte (noms de fichiers)
#include "Cellule.hpp" // on a besoin de connaitre l'objet cellule
#include "Regle.hpp" // on a besoin de connaitre les règles du jeu

// classe qui représente le plateau de jeu entier
class Grille {
private: // données internes cachées
    int largeur; // le nombre de colonnes du plateau
    int hauteur; // le nombre de lignes du plateau
    // tableau à deux dimensions (matrice) qui contient toutes les cellules
    std::vector<std::vector<Cellule>> cellules;

public:
    Grille(); // constructeur vide pour créer une grille sans taille
    Grille(int larg, int haut); // constructeur pour créer une grille d'une taille précise
    Grille(const Grille& autre); // constructeur de copie pour cloner toute la grille
    Grille& operator=(const Grille& autre); // permet de remplacer une grille par une autre avec le signe égal
    ~Grille() = default; // destructeur automatique (le vecteur se nettoie tout seul)

    // charge la configuration du jeu depuis un fichier texte
    void initialiserDepuisFichier(const std::string& chemin);

    int obtenirLargeur() const { return largeur; } // récupère la largeur
    int obtenirHauteur() const { return hauteur; } // récupère la hauteur

    // compte combien de voisins sont vivants autour de la case x,y
    int compterVoisinesVivantes(int x, int y) const;
    // calcule le tour suivant en appliquant les règles du jeu
    void mettreAJour(const Regle& regle);

    // permet de lire le tableau de cellules sans pouvoir le modifier
    const std::vector<std::vector<Cellule>>& obtenirCellules() const;

    // transforme la grille en un tableau simple de 0 et 1 (utile pour l'affichage)
    std::vector<std::vector<int>> obtenirMatriceEtats() const;
};