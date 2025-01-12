# Nom de l'exécutable
TARGET = test.x

# Liste des fichiers sources
SRCS = test.cpp piece.cpp tetris.cpp color.cpp

# Fichiers objets correspondants
OBJS = $(SRCS:.cpp=.o)

# Commande de compilation
CXX = g++
CXXFLAGS = -Wall -std=c++17 -pthread
CXXLIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
# Règle par défaut
all: $(TARGET)

# Lien final
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXLIBFLAGS)

# Compilation des fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)

