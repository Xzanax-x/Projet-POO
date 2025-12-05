#include "Jeu.hpp"
#include <fstream> // pour écrire dans des fichiers texte
#include <SFML/System.hpp> // pour gérer le temps (la pause entre les tours)
#include <cstdlib>  // pour lancer des commandes comme dans le terminal (mkdir)

// constructeur : initialise le jeu avec une grille vide et le nombre max de tours
Jeu::Jeu(int nbIter)
    : grille(), regle(), nbIterationsMax(nbIter) {}

// demande à la grille de se remplir à partir d'un fichier texte
void Jeu::chargerDepuisFichier(const std::string& chemin) {
    grille.initialiserDepuisFichier(chemin);
}

// compare deux grilles pour voir si le jeu est bloqué (plus rien ne bouge)
bool Jeu::estStable(const std::vector<std::vector<int>>& precedent,
                    const std::vector<std::vector<int>>& courant) const {
    return precedent == courant; // renvoie vrai si les deux tableaux sont identiques
}

// lance le jeu sans fenêtre, écrit les résultats dans des fichiers texte
void Jeu::executerModeConsole(const std::string& fichierEntree) {
    std::string dossierSortie = fichierEntree + "_out"; // crée le nom du dossier de sauvegarde
    std::string commandeMkdir = "mkdir -p " + dossierSortie; // prépare la commande pour créer le dossier
    system(commandeMkdir.c_str()); // exécute la commande système (comme dans le terminal)

    // sauvegarde l'état actuel pour comparer plus tard
    std::vector<std::vector<int>> precedent = grille.obtenirMatriceEtats();

    // boucle principale du jeu
    for (int iter = 0; iter < nbIterationsMax; ++iter) {
        // prépare le nom du fichier pour ce tour (ex: iter_0.txt)
        std::string nomFichier = dossierSortie + "/iter_" + std::to_string(iter) + ".txt";
        std::ofstream out(nomFichier); // ouvre le fichier pour écrire dedans
        
        // écrit la taille de la grille en haut du fichier
        out << grille.obtenirHauteur() << " " << grille.obtenirLargeur() << "\n";

        // récupère les cellules pour les écrire
        const auto& cellules = grille.obtenirCellules();
        // double boucle pour écrire des 0 et des 1 dans le fichier
        for (int y = 0; y < grille.obtenirHauteur(); ++y) {
            for (int x = 0; x < grille.obtenirLargeur(); ++x) {
                out << (cellules[x][y].estVivante() ? 1 : 0) << " "; // 1 si vivant, 0 si mort
            }
            out << "\n"; // saute une ligne à la fin de chaque ligne de la grille
        }

        grille.mettreAJour(regle); // calcule le tour suivant
        auto courant = grille.obtenirMatriceEtats(); // récupère le nouvel état

        // si le jeu n'a pas changé par rapport au tour d'avant, on arrête
        if (estStable(precedent, courant)) {
            break; // sort de la boucle
        }

        precedent = courant; // met à jour l'état précédent pour le prochain tour
    }
}

// lance le jeu avec une fenêtre graphique
void Jeu::executerModeGraphique() {
    // ouvre la fenêtre avec la bonne taille
    RenduGraphique rendu(150, grille.obtenirLargeur(), grille.obtenirHauteur());

    std::vector<std::vector<int>> precedent = grille.obtenirMatriceEtats(); // sauvegarde l'état de départ
    int iter = 0; // compteur de tours
    bool evolutionTerminee = false; // pour savoir si le jeu est fini
    const int DELAI_MS = 300; // temps d'attente entre deux images (vitesse du jeu)

    // tant que la fenêtre est ouverte
    while (rendu.estOuverte()) {
        if (!rendu.traiterEvenements()) break; // gère les clics (fermer la fenêtre, etc.)

        // si le jeu n'est pas fini et qu'on n'a pas atteint le max de tours
        if (!evolutionTerminee && iter < nbIterationsMax) {
            rendu.afficher(grille); // dessine la grille à l'écran
            sf::sleep(sf::milliseconds(DELAI_MS)); // attend un peu pour qu'on ait le temps de voir

            grille.mettreAJour(regle); // passe au tour suivant
            auto courant = grille.obtenirMatriceEtats(); // récupère le nouvel état

            // vérifie si le jeu est bloqué
            if (estStable(precedent, courant)) {
                evolutionTerminee = true; // marque le jeu comme fini
            }

            precedent = courant; // met à jour la mémoire
            ++iter; // compte un tour de plus
        } else {
            // si le jeu est fini, on continue juste d'afficher l'image fixe
            rendu.afficher(grille);
            sf::sleep(sf::milliseconds(DELAI_MS));
        }
    }
}

// permet de récupérer la grille pour la modifier
Grille& Jeu::obtenirGrille() {
    return grille;
}

// permet de récupérer la grille juste pour la lire
const Grille& Jeu::obtenirGrille() const {
    return grille;
}