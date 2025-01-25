#include <SFML/Network.hpp>
#include <iostream>
#include <unistd.h>
#include "window.hpp"
#include "tetris.hpp"
#include "piece.hpp"
#include "network.hpp"

int main()
{
    sf::TcpListener listener;

    // Attribuer un port
    if (listener.listen(53000) != sf::Socket::Done)
    {
        std::cerr << "Erreur lors de la mise en écoute sur le port 53000" << std::endl;
        return -1;
    }
    std::cout << "En attente d'une connexion sur le port 53000..." << std::endl;

    sf::TcpSocket client;
    // Accepter (et attendre) une nouvelle connexion
    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cerr << "Erreur lors de la connexion" << std::endl;
        return -1;
    }
    std::cout << "Client connecté : " << client.getRemoteAddress() << std::endl;

    // Envoi de données
    std::string message = "Bienvenue dans Tetris!";
    if (client.send(message.c_str(), message.size() + 1) != sf::Socket::Done)
    {
        std::cerr << "Erreur lors de l'envoi du message" << std::endl;
    }

    // Combiner le PID et le temps actuel pour créer une graine unique
    unsigned seed = static_cast<unsigned>(std::time(0)) + getpid(); 
    std::srand(seed);

    Grid gamegrid(22, 10);

    Game game(gamegrid, true, client);

    
    // on lance le thread d'envoi
    
    game.startGame();

    

    return 0;
}