#pragma once // protection pour ne pas inclure ce fichier plusieurs fois

#include <string> // pour gérer les noms de fichiers
#include <vector> // pour utiliser des tableaux dynamiques
#include "Grille.hpp" // inclut la grille pour pouvoir l'utiliser
#include "Regle.hpp" // inclut l'interface des règles
#include "RegleDeVie.hpp" // inclut les règles précises du jeu de la vie
#include "RenduGraphique.hpp" // inclut le module d'affichage graphique

// classe principale qui gère le déroulement complet d'une partie
class Jeu {
private: // les objets que le jeu possède en interne
    Grille grille; // l'objet grille qui contient toutes les cellules
    RegleDeVie regle; // l'objet qui connait les lois de la vie et de la mort
    int nbIterationsMax; // limite le nombre de tours pour pas que ça tourne à l'infini

public:
    // constructeur : on définit le nombre de tours max (100 par défaut si on précise rien)
    Jeu(int nbIter = 100);

    // permet de charger la configuration initiale depuis un fichier
    void chargerDepuisFichier(const std::string& chemin);

    // lance la boucle du jeu en mode texte (affichage dans le terminal)
    void executerModeConsole(const std::string& fichierEntree);
    // lance la boucle du jeu en mode graphique (avec une fenêtre)
    void executerModeGraphique();
    
    // accesseur pour récupérer la grille et pouvoir la modifier
    Grille& obtenirGrille();
    // accesseur pour récupérer la grille en lecture seule (const)
    const Grille& obtenirGrille() const;

private:
    // petite fonction interne pour vérifier si le jeu est bloqué (si rien ne change entre deux tours)
    bool estStable(const std::vector<std::vector<int>>& precedent,
                   const std::vector<std::vector<int>>& courant) const;
};