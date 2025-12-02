# Compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

# Librairies SFML
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Toutes les sources
SRCS = main.cpp \
       Game.cpp \
       Grid.cpp \
       Cell.cpp \
       CellState.cpp \
       Rule.cpp \
       GuiRenderer.cpp

# Objets générés
OBJS = $(SRCS:.cpp=.o)

# Cible par défaut
all: main

# Edition de liens
main: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# Compilation générique
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS) main

# Exécution console
run-console: main
	./main input.txt console 50

# Exécution graphique
run-gui: main
	./main input.txt gui 100
