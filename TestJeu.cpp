#include <iostream>
#include <vector>
#include "Jeu.hpp"
#include "RegleDeVie.hpp"
#include "Grille.hpp"

using namespace std;

// -----------------------------------------------
// MATRICE ATTENDUE POUR L'ITÉRATION 5
// À MODIFIER selon ton fichier input.txt !
// -----------------------------------------------
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
bool matricesEgales(const vector<vector<int>>& a,
                    const vector<vector<int>>& b) {
    if (a.size() != b.size()) return false;
    if (a[0].size() != b[0].size()) return false;

    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a[0].size(); ++j) {
            if (a[i][j] != b[i][j]) return false;
        }
    }
    return true;
}

// --------------------------------------------------
// PROGRAMME DE TEST
// --------------------------------------------------
int main() {
    try {
        // Charger le jeu avec 10 itérations maximum
        Jeu jeu(10);
        jeu.chargerDepuisFichier("input.txt");

        Grille& grille = jeu.obtenirGrille();
        RegleDeVie regle;

        // Appliquer 5 itérations
        for (int i = 0; i < 5; ++i) {
            grille.mettreAJour(regle);
        }

        // Récupérer la matrice obtenue
        vector<vector<int>> matriceObtenue = grille.obtenirMatriceEtats();

        // Comparaison
        if (matricesEgales(matriceObtenue, matriceAttendue5)) {
            cout << "TEST OK : L’itération 5 est correcte." << endl;
            return 0;
        } else {
            cout << "TEST ECHEC : La matrice de l’itération 5 ne correspond pas à la matrice attendue." << endl;
            return 1;
        }

    } catch (exception& e) {
        cout << "ERREUR pendant le test : " << e.what() << endl;
        return 2;
    }
}
