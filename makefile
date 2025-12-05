CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

# --- Fichiers sources communs au jeu ---
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

# --- Programme principal ---
MAIN_SRCS = main.cpp $(CORE_SRCS)
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)

# --- Programme de test ---
TEST_SRCS = TestJeu.cpp $(CORE_SRCS)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Cible par défaut
all: main

# Binaire principal
main: $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# Binaire de test
test-bin: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# Lancer les tests
test: test-bin
	./test-bin

# Compilation générique
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	@rm -f $(MAIN_OBJS) $(TEST_OBJS) main test-bin
	@rm -rf *_out
	@echo "Nettoyage terminé."

# Raccourcis d'exécution
run-console: main
	./main input.txt console 50

run-gui: main
	./main input.txt gui 100
