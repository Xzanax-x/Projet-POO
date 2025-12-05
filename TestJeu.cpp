#include <iostream>
#include <vector>
#include "Jeu.hpp"
#include "RegleDeVie.hpp"
#include "Grille.hpp"

using namespace std; // évite d'écrire std:: partout

// -----------------------------------------------
// MATRICE ATTENDUE POUR L'ITÉRATION 5
// À MODIFIER selon ton fichier input.txt !
// -----------------------------------------------
// c'est la "correction" : on écrit en dur ce qu'on est censé trouver après 5 tours
// sert à vérifier si le programme calcule juste
vector<vector<int>> matriceAttendue5 = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0},
    {0,0,1,1,0,0,1,1,0,0},
    {0,0,1,1,1,1,1,1,0,0},
    {0,0,1,1,0,0,1,1,0,0},
    {0,0,0,0,1,1,0,0,0,0}
};

// --------------------------------------------------
// FONCTION DE COMPARAISON DE MATRICES
// --------------------------------------------------
// petit utilitaire pour vérifier si deux grilles sont exactement pareilles
bool matricesEgales(const vector<vector<int>>& a,
                    const vector<vector<int>>& b) {
    // vérifie d'abord si les dimensions sont les mêmes
    if (a.size() != b.size()) return false;
    if (a[0].size() != b[0].size()) return false;

    // parcourt chaque case pour voir si le contenu est identique
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a[0].size(); ++j) {
            if (a[i][j] != b[i][j]) return false; // si une case diffère, c'est raté
        }
    }
    return true; // tout est pareil
}

// --------------------------------------------------
// PROGRAMME DE TEST
// --------------------------------------------------
int main() {
    try {
        // prépare le jeu (max 10 tours, mais on va gérer manuellement)
        Jeu jeu(10);
        jeu.chargerDepuisFichier("input.txt"); // charge la situation de départ

        // récupère les outils pour manipuler le jeu directement
        Grille& grille = jeu.obtenirGrille();
        RegleDeVie regle;

        // fait avancer le jeu de 5 tours (simulation)
        for (int i = 0; i < 5; ++i) {
            grille.mettreAJour(regle);
        }

        // récupère l'état de la grille après ces 5 tours (le résultat réel)
        vector<vector<int>> matriceObtenue = grille.obtenirMatriceEtats();

        // compare le résultat réel avec le résultat théorique attendu
        if (matricesEgales(matriceObtenue, matriceAttendue5)) {
            cout << "TEST OK : L’itération 5 est correcte." << endl; // ça marche
            return 0;
        } else {
            // ça ne marche pas, il y a un bug dans la logique du jeu
            cout << "TEST ECHEC : La matrice de l’itération 5 ne correspond pas à la matrice attendue." << endl;
            return 1; // retourne un code d'erreur
        }

    } catch (exception& e) { // en cas de plantage (fichier introuvable, etc.)
        cout << "ERREUR pendant le test : " << e.what() << endl;
        return 2;
    }
}