#include <iostream> // pour afficher du texte dans la console
#include <string> // pour manipuler des chaines de caractères
#include "Jeu.hpp" // on inclut la classe principale du jeu

// fonction principale, c'est là que le programme commence
int main(int argc, char* argv[]) {
    // vérifie si l'utilisateur a donné assez d'arguments (au moins 3)
    if (argc < 3) {
        // affiche comment utiliser le programme si on s'est trompé
        std::cerr << "Usage : " << argv[0]
                  << " <fichier_entree> <mode> [nbIterations]\n";
        std::cerr << "mode = console | gui\n";
        return 1; // arrête le programme avec une erreur
    }

    // récupère le nom du fichier (premier argument après le nom du programme)
    std::string fichierEntree = argv[1];
    // récupère le mode choisi (console ou graphique)
    std::string mode = argv[2];
    int nbIter = 100; // valeur par défaut si l'utilisateur ne précise rien

    // si l'utilisateur a donné un 4ème argument (le nombre de tours)
    if (argc >= 4) {
        nbIter = std::stoi(argv[3]); // convertit le texte en nombre entier
    }

    try { // essaie d'exécuter le code suivant et surveille les erreurs
        Jeu jeu(nbIter); // crée l'objet jeu
        jeu.chargerDepuisFichier(fichierEntree); // charge la grille

        if (mode == "console") { // si on veut le mode texte
            jeu.executerModeConsole(fichierEntree); // lance le jeu dans le terminal
        } else if (mode == "gui") { // si on veut le mode graphique
            jeu.executerModeGraphique(); // lance la fenêtre graphique
        } else { // si le mode n'est pas reconnu
            std::cerr << "Mode inconnu : " << mode
                      << " (utiliser console ou gui)\n";
            return 1; // erreur
        }

    } catch (const std::exception& e) { // si une erreur survient (ex: fichier introuvable)
        std::cerr << "Erreur : " << e.what() << "\n"; // affiche le message d'erreur
        return 1; // quitte avec une erreur
    }

    return 0; // tout s'est bien passé, fin normale
}