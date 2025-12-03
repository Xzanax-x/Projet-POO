CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = main.cpp \
       Jeu.cpp \
       Grille.cpp \
       Cellule.cpp \
       EtatCellule.cpp \
       EtatVivant.cpp \
       EtatMort.cpp \
       Regle.cpp \
       RegleDeVie.cpp \
       RenduGraphique.cpp

OBJS = $(SRCS:.cpp=.o)

all: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) main
	@rm -rf *_out
	@echo "Nettoyage terminé."

run-console: main
	./main input.txt console 50

run-gui: main
	./main input.txt gui 100

