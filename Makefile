# Nom de l'exécutable
TARGET = launcher.x
CLIENT_TARGET = client.x
SERVER_TARGET = server.x

# Liste des fichiers sources (communs à solo et multijouer)
COMMON_SRCS = window.cpp piece.cpp tetris.cpp color.cpp network.cpp


# Fichiers objets correspondants
#OBJS = $(COMMON_SRCS:.cpp=.o)

# Commande de compilation
CXX = g++
CXXFLAGS = -Wall -std=c++17 -pthread
CXXLIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

# Règle par défaut
all: $(TARGET)

# Lien final pour le programme principal (solo)
$(TARGET): $(COMMON_SRCS) launcher.cpp
	$(CXX) $(CXXFLAGS) launcher.cpp $(COMMON_SRCS) -o $(TARGET) $(CXXLIBFLAGS)

# Règle pour le client
client: $(COMMON_SRCS) test_client.cpp
	$(CXX) $(CXXFLAGS) test_client.cpp $(COMMON_SRCS) -o $(CLIENT_TARGET) $(CXXLIBFLAGS)

# Règle pour le serveur
server: $(COMMON_SRCS) test_server.cpp
	$(CXX) $(CXXFLAGS) test_server.cpp $(COMMON_SRCS) -o $(SERVER_TARGET) $(CXXLIBFLAGS)

# Compilation des fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f *.o $(TARGET) $(CLIENT_TARGET) $(SERVER_TARGET)

