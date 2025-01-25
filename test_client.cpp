#include <SFML/Network.hpp>
#include <iostream>
#include <unistd.h>
#include "piece.hpp"
#include "tetris.hpp"

int main()
{
    sf::TcpSocket socket;

    // Connecte le socket au serveur
    if (socket.connect("127.0.0.1", 53000) != sf::Socket::Done)
    {
        std::cerr << "Erreur lors de la connexion au serveur" << std::endl;
        return -1;
    }
    std::cout << "Connecté au serveur!" << std::endl;

    // Combiner le PID et le temps actuel pour créer une graine unique
    unsigned seed = static_cast<unsigned>(std::time(0)) + getpid(); 
    std::srand(seed);

    Grid gamegrid(22, 10);

    Game game(gamegrid, true, socket);

    
    // on lance le thread d'envoi
    
    game.startGame();

    return 0;
}
