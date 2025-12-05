# choix du compilateur (g++ est le standard pour le c++)
CXX = g++
# options de compilation :
# -std=c++17 : utilise la version moderne de c++
# -Wall -Wextra : affiche tous les avertissements si le code est bizarre
# -I. : cherche les fichiers header (.hpp) dans le dossier courant
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

# bibliothèques à inclure (sfml pour le graphisme, la fenêtre et le système)
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

# --- liste des fichiers qui contiennent la logique du jeu ---
CORE_SRCS = \
    Jeu.cpp \
    Grille.cpp \
    Cellule.cpp \
    EtatCellule.cpp \
    EtatVivant.cpp \
    EtatMort.cpp \
    Regle.cpp \
    RegleDeVie.cpp \
    RenduGraphique.cpp

# --- configuration pour le programme principal ---
# on prend le main.cpp et on ajoute toute la logique du jeu
MAIN_SRCS = main.cpp $(CORE_SRCS)
# transforme la liste des .cpp en .o (fichiers objets compilés)
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)

# --- configuration pour le programme de test ---
# on prend le fichier de test et on ajoute la logique du jeu
TEST_SRCS = TestJeu.cpp $(CORE_SRCS)
# transforme la liste des .cpp de test en .o
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# cible par défaut : si tu tapes juste 'make', ça lance la construction de 'main'
all: main

# règle pour créer l'exécutable 'main'
main: $(MAIN_OBJS)
    # commande qui assemble tous les .o pour créer le programme final
    $(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# règle pour créer l'exécutable des tests
test-bin: $(TEST_OBJS)
    # assemble les fichiers de test pour créer l'exécutable 'test-bin'
    $(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# raccourci pour compiler les tests ET les lancer direct
test: test-bin
    ./test-bin

# règle générique (la magie) : explique comment transformer n'importe quel .cpp en .o
%.o: %.cpp
    # compile le fichier source (-c) en fichier objet (-o)
    $(CXX) $(CXXFLAGS) -c $< -o $@

# commande de nettoyage pour supprimer les fichiers générés
clean:
    @rm -f $(MAIN_OBJS) $(TEST_OBJS) main test-bin # supprime les .o et les exécutables
    @rm -rf *_out # supprime les dossiers de résultats
    @echo "Nettoyage terminé." # affiche un message

# raccourci pour lancer le jeu en mode console rapidement
run-console: main
    ./main input.txt console 50

# raccourci pour lancer le jeu en mode graphique rapidement
run-gui: main
    ./main input.txt gui 100